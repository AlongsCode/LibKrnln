//
//#include <vector>
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <cstring>
//#include <chrono>
//#include <ctime>
//#include <set>
//#include <filesystem>
//#include <map>
//#include <unordered_set>
//#pragma pack(1)//边界对齐
//
//#include"edbs.h"
//
//
//
//#pragma region 内部宏
//
//
//#define EDBCHECK { 'W', 'E', 'D', 'B', 0x00, 0x00, 0x01, 0x00 }
//#define EDTCHECK { 'W', 'E', 'D', 'T', 0x00, 0x00, 0x01, 0x00 }
//static const char pCheckSizeNeverUse[] = EDBCHECK;
//#define EDBCHECKSIZE sizeof(pCheckSizeNeverUse)
//
//
//
//#pragma endregion
//
//
//#pragma region 结构体
//
//struct EDBHEADER {
//
//	double m_createTime;//OLE时间
//	int m_recordNum;//当前记录数量
//	int m_unusedPrimaryKey;//可使用的主键,每次插入空数据会自增1,用不重复
//	int  m_totalLength;//所有字段所需的长度,单位字节
//	unsigned char  m_blankBYTE[84];//预留空间
//	int m_validColumnNum;//有效字段数了
//	EDBHEADER() {
//		m_createTime = 0;
//		m_recordNum = 0;
//		m_unusedPrimaryKey = 1;
//		m_totalLength = 0;
//		memset(m_blankBYTE, 0, sizeof(m_blankBYTE));
//		m_validColumnNum = 0;
//	}
//};
//struct EDTHEADER//EDT创建数据
//{
//	EDTHEADER() {
//		m_createTime = 0;//COleDateTime::GetTickCount()，每次打开会刷新，兼容原版EDB;;
//		m_recordNum = 1;//分隔符
//		memset(m_data, 0, 492);
//	}
//	double  m_createTime;//COleDateTime::GetTickCount()，每次打开会刷新，兼容原版EDB;;
//	int m_recordNum;//分隔符0000 0;//分隔符1000 1;
//	unsigned char m_data[492];
//};
//struct COLIMNDATA
//{
//	char m_ColumnName[16];  // 名称最大16字节,
//	int m_delimiter;    // 分隔符
//	DataType m_ColumnType;       // 起始偏移位置
//	int m_offset;           // 非文本型需求数据长度;
//	int m_strlenth;         // 如为文本类型则需要长度;
//	unsigned char m_Table[40];
//	COLIMNDATA() {
//		memset(this, 0, sizeof(*this));
//	}
//};
//#pragma endregion
//
//
//#pragma region 映射
//
//
///*映射字段长度,文本型可自行设置*/
//std::map<DataType, int> type_lengths = {
//	{DataType::BYTE, 1},
//	{DataType::SHORT_INT, 2},
//	{DataType::INT, 4},
//	{DataType::LONG_INT, 8},
//	{DataType::FLOAT, 4},
//	{DataType::DOUBLE, 8},
//	{DataType::BOOLEAN, 1},
//	{DataType::DATE_TIME, 4},
//	{DataType::PTR, 4},
//	{DataType::BYTE_ARRAY, 4},
//	{DataType::REMARK, 4},
//	{DataType::PRIMARY_KEY, 4} // 主键型默认长度为4
//};
//#pragma endregion
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////获取时间并转化为OLE时间,此代码为兼容EDB原版
//inline double get_nowtm_to_oletm() {
//	auto now = std::chrono::system_clock::now();
//	auto time_t_now = std::chrono::system_clock::to_time_t(now);
//	auto  t = static_cast<__time64_t>(time_t_now);
//	return static_cast<double>(25569 + t / 86400.0 + 8.0 / 24.0);
//
//}
//
//
//
//
////bool isEDBFile(const char* filename) {
////	EDBHEADER data;
////	std::ifstream file(filename, std::ios::binary);
////
////	if (!file) {
////		std::cout << "Failed to open file: " << filename << std::endl;
////		return false;
////	}
////
////	file.read((char*)&data, sizeof(data));
////	file.close();
////
////	return (strncmp(data.Typename, "WEDB", 4) == 0 && data.delimiter1 == 0x00010000);
////}
///*EDBS并不会进行过多限制，但会进行严格的规则审查，不满足则不允许创建*/
//bool is_vaild_name(const std::string& text) {
//	if (text.empty()
//		|| text.size() > 16
//		|| text.find(" ") != std::string::npos
//		)
//	{
//		return false;
//	}
//	if ((text[0] >= '0' && text[0] <= '9') || text[0] == '.') {
//		return false;
//	}
//	return true;
//}
//
//
//
///*修改文件拓展名*/
//std::string rename_file_ext(const std::string& filename, const std::string& extensionname) {
//
//	std::filesystem::path filepath(filename);
//	std::string suffix = extensionname;
//	if (extensionname[0] != '.') {
//		suffix = "." + suffix;
//	}
//	filepath.replace_extension(suffix);
//	return filepath.string();
//}
//
//
//KrnlnApi int create_edbs(const std::string& nfilename, const std::vector< ColumnInfo>& columns) {
//
//	/*对于字段的有效性验证和数据提取*/
//	std::unordered_set<std::string> columnNames;
//
//	std::vector<COLIMNDATA> wFileCoumns;
//
//	//默认要对数据库进行一个主键大小,同时也是偏移和拓展出去的长度
//	std::uint32_t all_columns_datasize = type_lengths[DataType::PRIMARY_KEY];
//	//有效字段数量
//	std::uint32_t valid_column_num = 0;
//
//	bool bIsHaveBigData = false;
//
//	for (ColumnInfo column : columns)
//	{
//
//		// 判断字段名是否已经出现过
//		if (columnNames.count(column.m_name) > 0)
//		{
//			return EDB_ERROR_DUPLICATE_COLUMN_NAME;
//		}
//		columnNames.insert(column.m_name);
//
//
//		if (!is_vaild_name(column.m_name))
//		{
//
//			return  EDB_ERROR_INVALID_COLUMN_NAME;
//		}
//
//
//		if (column.m_dataType< DataType::BYTE || column.m_dataType > DataType::REMARK)
//		{
//			return EDB_ERROR_INVALID_COLUMN_TYPE;
//		}
//
//
//
//		//准备将其写入文件中的字段数据
//		COLIMNDATA TempwFileCoumns;
//		TempwFileCoumns.m_ColumnType = column.m_dataType;
//
//		strcpy_s(TempwFileCoumns.m_ColumnName, column.m_name.c_str());
//		TempwFileCoumns.m_ColumnName[15] = '\0';
//		if (strlen(TempwFileCoumns.m_ColumnName) < 15)
//		{
//			memset(&TempwFileCoumns.m_ColumnName[strlen(TempwFileCoumns.m_ColumnName)], 0, 15 - strlen(TempwFileCoumns.m_ColumnName));
//		}
//
//		//通过名称和类型判断则进行长度验证
//		//首先是判断是否为文本型
//		std::uint32_t TempColumnSize = 0;
//		//EDBS不对文本型最大长度进行限制
//		if (column.m_dataType == DataType::TEXT)
//		{
//			//验证
//			TempColumnSize = column.m_strDataLength;
//			//准备写入二进制数据
//			TempwFileCoumns.m_strlenth = column.m_strDataLength;
//		}
//		else
//		{
//			TempColumnSize = type_lengths[column.m_dataType];
//		}
//
//		if (TempColumnSize == 0)
//		{
//			return EDB_ERROR_INVALID_COLUMN_SIZE;
//		}
//
//		if (column.m_dataType == DataType::REMARK || column.m_dataType == DataType::BYTE_ARRAY)
//		{
//			bIsHaveBigData = true;
//		}
//		TempwFileCoumns.m_offset = all_columns_datasize;
//		wFileCoumns.push_back(TempwFileCoumns);
//		all_columns_datasize += TempColumnSize;
//		valid_column_num++;
//	}
//
//	auto filename = rename_file_ext(nfilename, ".edbs");
//
//	std::ofstream file(filename, std::ios::binary);
//	if (!file)
//	{
//		// 创建EDT文件失败
//		return EDB_ERROR_CREATE_EDBS;
//	}
//	EDBHEADER EDB;
//	auto time = get_nowtm_to_oletm();
//	EDB.m_createTime = time;
//	EDB.m_validColumnNum = valid_column_num;
//	EDB.m_totalLength = all_columns_datasize;
//	char check_edb[] = EDBCHECK;
//	file.write(check_edb, sizeof(check_edb));
//	file.write(reinterpret_cast<char*>(&EDB), sizeof(EDBHEADER));
//	// 然后写入字段数据
//	for (auto& column : wFileCoumns)
//	{
//		file.write(reinterpret_cast<char*>(&column), sizeof(COLIMNDATA));
//	}
//	file.close();
//
//	if (bIsHaveBigData)
//	{
//		// 创建EDT文件
//		std::string edtFileName = rename_file_ext(nfilename, ".edt");
//		std::ofstream edtFile(edtFileName, std::ios::binary);
//		if (!edtFile)
//		{
//			// 创建EDT文件失败
//			return EDB_ERROR_CREATE_EDT;
//		}
//		// 写入EDT文件头部信息
//		EDTHEADER edtHeader;
//		char check_edt[] = EDTCHECK;
//		edtHeader.m_createTime = time;
//		edtFile.write(check_edt, sizeof(check_edt));
//		edtFile.write(reinterpret_cast<char*>(&edtHeader), sizeof(EDTHEADER));
//		edtFile.close();
//	}
//	return EDB_ERROR_SUCCESS;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//class Edbs
//{
//public:
//	Edbs& operator = (const Edbs& n_copy) {
//		if (this != &n_copy) {
//			// 先关闭当前文件，防止资源泄漏
//			if (m_file.is_open()) m_file.close();
//			// 复制错误码和偏移量等信息
//			m_errorCode = n_copy.m_errorCode;
//			m_fileName = n_copy.m_fileName;
//			m_dataOffset = n_copy.m_dataOffset;
//			m_cur_off = n_copy.m_cur_off;
//			m_isTransactionOpened = n_copy.m_isTransactionOpened;
//			// 复制列信息
//			m_allCoLimns = n_copy.m_allCoLimns;
//			// 复制 EDB 头信息
//			m_edbInf = n_copy.m_edbInf;
//			// 打开文件
//			m_file.open(n_copy.m_fileName);
//			if (!m_file.is_open()) {
//				// 文件无法打开
//				m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
//			}
//		}
//		return *this;
//	}
//	Edbs() :m_errorCode(EDB_ERROR_SUCCESS), m_dataOffset(0), m_cur_off(0), m_isTransactionOpened(false) {};
//	Edbs(const std::string& filename) :m_errorCode(EDB_ERROR_SUCCESS), m_dataOffset(0), m_cur_off(0), m_isTransactionOpened(false) {
//		m_file.open(filename);
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
//			return;
//		}
//		if (!is_edbs_file())
//		{
//			m_file.close();
//			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
//			return;
//		}
//		//获取EDB信息
//		m_file.seekg(EDBCHECKSIZE);
//		m_file.read(reinterpret_cast<char*>(&m_edbInf), sizeof(EDBHEADER));
//		//无有效字段
//		if (m_edbInf.m_validColumnNum <= 0)
//		{
//			m_file.close();
//			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
//			return;
//		}
//		auto  allCoLimnsize = m_edbInf.m_validColumnNum * sizeof(COLIMNDATA);
//		auto allRowsize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;
//		//再次验证文件大小
//		m_file.seekg(0, std::ios::end);
//		auto fileSize = m_file.tellg();
//
//
//		if (fileSize < sizeof(EDBHEADER) + EDBCHECKSIZE + allCoLimnsize + allRowsize)
//		{
//			// 文件太小，不可能读取所有列信息和当前足够的信息数据
//			m_file.close();
//			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
//			return;
//		}
//		m_file.seekg(sizeof(EDBHEADER) + EDBCHECKSIZE);
//		m_allCoLimns.resize(m_edbInf.m_validColumnNum);
//		m_file.read(reinterpret_cast<char*>(m_allCoLimns.data()), allCoLimnsize);
//		m_dataOffset = m_file.tellg();
//
//
//		/*处理初始化数据*/
//		m_cur_off = 1;
//		m_fileName = filename;
//	};
//	~Edbs() { if (m_file.is_open())m_file.close(); };
//public:
//	bool open(const std::string& filename) {
//		//已经打开就不在打开
//		if (m_file.is_open()) {
//			m_errorCode = EDB_ERROR_HASBEEN_OPEN_EDBS;
//			return false;
//		}
//
//
//		m_file.open(filename);
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
//			return false;
//		}
//		if (!is_edbs_file())
//		{
//			m_file.close();
//			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
//			return false;
//		}
//		//获取EDB信息
//		m_file.seekg(EDBCHECKSIZE);
//		m_file.read(reinterpret_cast<char*>(&m_edbInf), sizeof(EDBHEADER));
//		//无有效字段
//		if (m_edbInf.m_validColumnNum <= 0)
//		{
//			m_file.close();
//			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
//			return false;;
//		}
//		auto  allCoLimnsize = m_edbInf.m_validColumnNum * sizeof(COLIMNDATA);
//		auto allRowsize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;
//		//再次验证文件大小
//		m_file.seekg(0, std::ios::end);
//		auto fileSize = m_file.tellg();
//
//
//		if (fileSize < sizeof(EDBHEADER) + EDBCHECKSIZE + allCoLimnsize + allRowsize)
//		{
//			// 文件太小，不可能读取所有列信息和当前足够的信息数据
//			m_file.close();
//			m_errorCode = EDB_ERROR_INVALID_EDBSFILE;
//			return false;;
//		}
//		m_file.seekg(sizeof(EDBHEADER) + EDBCHECKSIZE);
//		m_allCoLimns.resize(m_edbInf.m_validColumnNum);
//		m_file.read(reinterpret_cast<char*>(m_allCoLimns.data()), allCoLimnsize);
//		m_dataOffset = m_file.tellg();
//
//
//		/*处理初始化数据*/
//		m_cur_off = 1;
//		m_fileName = filename;
//		return true;;
//
//	}
//	//保证不会出现容量不足，因为给易用，需要牺牲部分性能来保证用户不会进行傻逼操作
//	void Read(int nIndex_column, int nIndex_row, std::vector<unsigned char>* pData) {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return;
//		}
//		if ((nIndex_row >= 0 && nIndex_row + 1 > m_edbInf.m_recordNum) || (nIndex_column + 1 > m_edbInf.m_validColumnNum && nIndex_column >= 0))
//		{
//			m_errorCode = EDB_ERROR_INVALID_INDEX;
//			return;
//		}
//		m_file.seekg(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);
//
//		//文本型长度需特殊处理
//		int needsize = m_allCoLimns[nIndex_column].m_strlenth;
//		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::TEXT)
//		{	//否则默认长度
//			needsize = type_lengths[m_allCoLimns[nIndex_column].m_ColumnType];
//		}
//
//		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::BYTE_ARRAY && m_allCoLimns[nIndex_column].m_ColumnType != DataType::REMARK)
//		{
//			pData->resize(needsize, 0);
//			m_file.read(reinterpret_cast<char*>(pData->data()), pData->size());
//		}
//		else
//		{
//			/*处理字节集和备注型*/
//		}
//
//
//	};
//	bool Write(int nIndex_column, int nIndex_row, const std::vector<unsigned char>& data) {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return false;
//		}
//		if (nIndex_row + 1 > m_edbInf.m_recordNum || nIndex_column + 1 > m_edbInf.m_validColumnNum)
//		{
//			m_errorCode = EDB_ERROR_INVALID_INDEX;
//			return false;
//		}
//		m_file.seekp(m_dataOffset + nIndex_row * m_edbInf.m_totalLength + m_allCoLimns[nIndex_column].m_offset);
//		//文本型长度需特殊处理
//		int needsize = m_allCoLimns[nIndex_column].m_strlenth;
//		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::TEXT)
//		{	//否则默认长度
//			needsize = type_lengths[m_allCoLimns[nIndex_column].m_ColumnType];
//		}
//
//		if (m_allCoLimns[nIndex_column].m_ColumnType != DataType::BYTE_ARRAY && m_allCoLimns[nIndex_column].m_ColumnType != DataType::REMARK)
//		{
//			/*非字节集和备注型*/
//			if (data.size() >= needsize) {
//				// 长度超过会截断
//				m_file.write(reinterpret_cast<const char*>(data.data()), needsize);
//			}
//			else {
//				// 长度不足会填充
//				m_file.write(reinterpret_cast<const char*>(data.data()), data.size());
//				if (data.size() < needsize) {
//					// 填充剩余空间
//					//std::vector<unsigned char> padData(needsize - data.size(), 0);
//					auto padData = new char[needsize - data.size()]{ 0 };
//					m_file.write(padData, needsize - data.size());
//					delete[]padData;
//				}
//			}
//		}
//		else
//		{
//			/*处理字节集和备注型*/
//		}
//		if (!m_isTransactionOpened)
//		{
//			m_file.flush();
//		}
//
//		return  true;
//	}
//	bool Insert(const std::vector<std::vector<unsigned char>>& data) {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return false;
//		}
//		if (data.empty()) {
//			// 无数据要插入
//			return true;
//		}
//		if (data.front().size() != m_edbInf.m_validColumnNum) {
//			// 新数据的列数不匹配
//			m_errorCode = EDB_ERROR_INVALID_COLUMN_NUM;
//			return false;
//		}
//		if (m_isTransactionOpened) {
//			// 已开启事务，不能插入
//			m_errorCode = EDB_ERROR_TRANSACTION_OPENED;
//			return false;
//		}
//		auto totalRowSize = m_edbInf.m_totalLength * m_edbInf.m_recordNum;
//		// 计算插入新行后文件的总大小
//		auto newFileSize = sizeof(EDBHEADER) + EDBCHECKSIZE + m_allCoLimns.size() * sizeof(COLIMNDATA) +
//			(m_edbInf.m_recordNum + data.size()) * m_edbInf.m_totalLength;
//		// 调整文件大小
//		m_file.seekp(newFileSize - 1);
//		m_file.write("", 1);
//		// 读取文件尾部的数据，以便将其移动到新的位置
//		auto tailSize = static_cast<int> (m_file.tellg()) - (m_dataOffset + totalRowSize);
//		std::vector<unsigned char> tailData(tailSize);
//		m_file.seekg(m_dataOffset + totalRowSize);
//		m_file.read(reinterpret_cast<char*>(tailData.data()), tailSize);
//		// 将尾部数据移动到新的位置
//		m_file.seekp(newFileSize - tailSize);
//		m_file.write(reinterpret_cast<char*>(tailData.data()), tailSize);
//		// 将新数据写入文件
//		m_file.seekp(m_dataOffset + m_edbInf.m_recordNum * m_edbInf.m_totalLength);
//		for (const auto& row : data) {
//			for (int i = 0; i < m_allCoLimns.size(); ++i) {
//				const auto& col = row;
//				const auto& colInfo = m_allCoLimns[i];
//				int needsize = colInfo.m_strlenth;
//				if (colInfo.m_ColumnType != DataType::TEXT) {
//					needsize = type_lengths[colInfo.m_ColumnType];
//				}
//
//				if (colInfo.m_ColumnType != DataType::BYTE_ARRAY && colInfo.m_ColumnType != DataType::REMARK)
//				{
//					if (col.size() < needsize) {
//						// 数据长度不足，补零
//						std::vector<unsigned char> paddedData(needsize, 0);
//						std::copy(col.begin(), col.end(), paddedData.begin());
//						m_file.write(reinterpret_cast<char*>(paddedData.data()), needsize);
//					}
//					else {
//						m_file.write(reinterpret_cast<const char*>(col.data()), needsize);
//					}
//				}
//				else
//				{
//					/*处理字节集和备注型*/
//				}
//
//
//
//			}
//		}
//		// 更新记录数和文件大小信息
//		m_edbInf.m_recordNum++;
//		updata_heade();
//		if (!m_isTransactionOpened)
//		{
//			m_file.flush();
//		}
//	}
//	bool AppendBlank(int nCount) {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return false;
//		}
//		if (nCount <= 0)
//		{
//			m_errorCode = EDB_ERROR_INVALID_ROWS_NUM;
//			return false;
//		}
//		//文件头处理
//		m_edbInf.m_recordNum += nCount;
//		m_file.seekp(0, std::ios::end);
//		//文本型长度需特殊处理
//
//		char* pData_nop = new char[nCount * m_edbInf.m_totalLength]{ 0 };
//		// 长度超过会截断
//		m_file.write(reinterpret_cast<const char*>(pData_nop), nCount * m_edbInf.m_totalLength);
//
//		if (!m_isTransactionOpened)
//		{
//			m_file.flush();
//		}
//		delete[]pData_nop;
//		updata_heade();
//		return  true;
//	}
//
//	//开启事务
//	void begin() {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return;
//		}
//		if (m_isTransactionOpened) {
//			m_errorCode = EDB_ERROR_TRANSACTION_OPENED;
//			return;
//		}
//		m_isTransactionOpened = true;
//	}
//	//提交事务
//	void commit() {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return;
//		}
//		if (!m_isTransactionOpened) {
//			m_errorCode = EDB_ERROR_TRANSACTION_NOT_OPENED;
//			return;
//		}
//		m_file.flush();
//	}
//	std::string Get_column_name(int nIndex_column)const {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			return std::string();
//		}
//		if (nIndex_column < 0 || nIndex_column >= m_allCoLimns.size())
//		{
//			return std::string();
//		}
//		return m_allCoLimns[nIndex_column].m_ColumnName;
//	}
//private:
//	std::string m_fileName;
//	std::fstream m_file;  //文件流
//	int m_dataOffset;//数据开始位置
//	int m_errorCode;//错误码
//	EDBHEADER m_edbInf;//数据表信息
//	std::vector<COLIMNDATA> m_allCoLimns;//字段信息
//	bool m_isTransactionOpened;//是否开启事务
//	//下方为包装操作
//public:
//	int get_error_code() const {
//		return m_errorCode;
//	}
//	int get_column_num()const {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			return 0;
//		}
//		return m_edbInf.m_validColumnNum;
//	}
//	std::string get_column_name(int nIndex_column) {
//		return Get_column_name(nIndex_column - 1);
//	}
//	int get_row_num()const {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			return 0;
//		}
//		return m_edbInf.m_recordNum;
//	}
//	void current(int cur_off) {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return;
//		}
//		if (cur_off < 0)cur_off = 0;
//		else if (cur_off > m_edbInf.m_recordNum)cur_off = m_edbInf.m_recordNum;
//		m_cur_off = cur_off;
//	};
//	void next() {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return;
//		}
//
//		if (m_cur_off + 1 > m_edbInf.m_recordNum)
//		{
//			return;
//		}
//		m_cur_off++;
//	}
//	void previous() {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return;
//		}
//		if (m_cur_off - 1 <= 0)
//		{
//			return;
//		}
//		m_cur_off--;
//	}
//	int current() const {
//		return m_cur_off;
//	}
//	std::vector<unsigned char>& read(int nIndex_column) {
//		std::vector<unsigned char> p_get_data;
//		Read(m_cur_off, nIndex_column - 1, &p_get_data);
//		return p_get_data;
//	}
//	bool write(int nIndex_column, const std::vector<unsigned char>& pData) {
//		return Write(m_cur_off, nIndex_column - 1, pData);
//	}
//private:
//	int m_cur_off = 0;
//private:
//	//处理文件头部,每次增减记录时需要操作
//	inline void updata_heade() {
//		if (!m_file.is_open()) {
//			// 文件无法打开
//			m_errorCode = EDB_ERROR_NOOPEN_EDBS;
//			return;
//		}
//		//记录现在位置
//		auto now = m_file.tellp();
//		//移到文件头,不包括文件标识位置+
//		m_file.seekp(EDBCHECKSIZE, std::ios::beg);
//		m_file.write(reinterpret_cast<const char*>(&m_edbInf), sizeof(EDBHEADER));
//		//移动回之前的位置
//		m_file.seekp(now, std::ios::beg);
//
//		if (!m_isTransactionOpened)
//		{
//			m_file.flush();
//		}
//	}
//	//help,最后不会暴漏在头文件接口中
//	inline  bool is_edbs_file() {
//
//		// 确认文件大小
//		m_file.seekg(0, std::ios::end);
//		const char edb_flag[] = { 'W', 'E', 'D', 'B', 0x00, 0x00, 0x01, 0x00 };
//		if (m_file.tellg() < sizeof(EDBHEADER) + EDBCHECKSIZE) {
//			// 文件太小，不可能是有效的 edbs 文件
//
//			return false;
//		}
//
//		m_file.seekg(0, std::ios::beg);
//		char rfile_flag[EDBCHECKSIZE]{ 0 };
//		m_file.read(rfile_flag, EDBCHECKSIZE);
//
//		if (std::memcmp(rfile_flag, edb_flag, EDBCHECKSIZE) != 0) {
//			// 文件不是 edbs 文件
//			return false;
//		}
//		//如果是edbs文件需要移到文件首继续，因为后续操作需要，如果不是则不用管理，返回时会自动关闭
//		m_file.seekg(0, std::ios::beg);
//		return true;
//	}
//};
//
//KrnlnApi bool 打开EDB(const std::string& filename) {
//	Edbs EDB(filename);
//	std::vector<unsigned char> data = { 30,0,0,0 };
//	EDB.Write(0, 0, data);
//	EDB.Read(0, 0, &data);
//	std::cout << "\n";
//	for (const auto c : data)
//	{
//		std::cout << (int)c << ",";
//	}
//
//	system("pause");
//	return 0;
//};