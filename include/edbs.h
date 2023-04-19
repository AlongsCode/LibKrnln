//#pragma once
//#pragma region 宏和枚举
//enum class DataType {
//	BYTE = 1,         // 字节型
//	SHORT_INT,    // 短整数型
//	INT,          // 整数型
//	LONG_INT,     // 长整数型
//	FLOAT,        // 小数型
//	DOUBLE,       // 双精度小数型
//	BOOLEAN,      // 逻辑型
//	DATE_TIME,    // 日期时间型
//	PTR,		  // 指针型，数据库不会用到
//	TEXT,         // 文本型
//	BYTE_ARRAY,   // 字节集型
//	REMARK,		  // 备注型
//	PRIMARY_KEY	  // 主键
//};
//
//
///*验证宏*/
//
//
///*失败宏*/
//#define EDB_ERROR_SUCCESS 0
//#define EDB_ERROR_INVALID_COLUMN_NAME -1 //字段名称错误
//#define EDB_ERROR_INVALID_COLUMN_TYPE -2 //数据类型错误
//#define EDB_ERROR_INVALID_COLUMN_SIZE -3 //数据长度为0
//#define EDB_ERROR_DUPLICATE_COLUMN_NAME -4//字段名重复
//#define EDB_ERROR_CREATE_EDBS -5//创建EDB失败
//#define EDB_ERROR_CREATE_EDT -6//创建EDT失败
//#define EDB_ERROR_INVALID_EDBSFILE -7//无效edb文件
//#define EDB_ERROR_NOOPEN_EDBS -8//没打开文件
//#define EDB_ERROR_INVALID_INDEX -9//无效的字段或记录索引
//#define EDB_ERROR_INVALID_DATA_SIZE -10 //写入错误的数据长度
//#define EDB_ERROR_INVALID_DATA_TYPE -11 //写入错误的数据类型
//#define EDB_ERROR_TRANSACTION_OPENED -12 //事务已开启
//#define EDB_ERROR_TRANSACTION_NOT_OPENED -13 //事务未开启
//#define EDB_ERROR_INVALID_COLUMN_NUM -14 //插入数据数量不匹配
//#define EDB_ERROR_HASBEEN_OPEN_EDBS -15//没打开文件
//#define EDB_ERROR_INVALID_ROWS_NUM -16//加入无效数量的记录
//
//#pragma endregion
//
//
//
//
//struct ColumnInfo {
//	std::string m_name;
//	DataType m_dataType;
//	unsigned int m_strDataLength = 20;
//
//	ColumnInfo() = default;
//	ColumnInfo(const std::string& n, DataType t, int l = 20) : m_name(n), m_dataType(t), m_strDataLength(l) {}
//};
//
//
//
//
//
//
//
//struct _Is_slash_oper { // predicate testing if input is a preferred-separator or fallback-separator
//	_NODISCARD constexpr bool operator()(
//		const wchar_t _Ch) const { // test if _Ch is a preferred-separator or fallback-separator
//		return _Ch == L'\\' || _Ch == L'/';
//	}
//};
//
//_NODISCARD inline const wchar_t* _Find_relative_path(const wchar_t* const _First, const wchar_t* const _Last) {
//	// attempt to parse [_First, _Last) as a path and return the start of relative-path
//	return _STD find_if_not(_Find_root_name_end(_First, _Last), _Last, _Is_slash);
//}
//_NODISCARD inline const wchar_t* _Find_filename(const wchar_t* const _First, const wchar_t* _Last) {
//	// attempt to parse [_First, _Last) as a path and return the start of filename if it exists; otherwise, _Last
//	const auto _Relative_path = _Find_relative_path(_First, _Last);
//	while (_Relative_path != _Last && !_Is_slash(_Last[-1])) {
//		--_Last;
//	}
//
//	return _Last;
//}
//
//std::string& replace_extension(std::string _Text) {
//	const char* _First = _Text.data();
//	const auto _Last = _First + _Text.size();
//	const auto _Filename = _Find_filename(_First, _Last);
//	const auto _Ads = std::find(_Filename, _Last, ':');
//	const auto _Extension = _Find_extension(_Filename, _Ads);
//	_Text._Orphan_all();
//	_Text.erase(static_cast<size_t>(_Extension - _First));
//	return *this;
//}
//std::string& replace_extension(std::string _Text, std::string _Replacement) {
//	// remove any extension() (and alternate data stream references) from *this's filename(), and concatenate
//	// _Replacement
//	replace_extension();
//	if (!_Replacement.empty() && _Replacement._Text[0] != L'.') {
//		_Text.push_back(L'.');
//	}
//
//	return _Replacement;
//}