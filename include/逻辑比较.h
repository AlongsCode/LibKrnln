#pragma once
#define 真 true  
#define 假 false
#define 或 ||
#define 且 &&
#define 取反(x) !x

bool 近似等于(std::wstring 被比较文本, std::wstring 比较文本);
bool 近似等于(std::string 被比较文本, std::string 比较文本);
bool 约等于(std::string 参1, std::string 参2);
bool 约等于(std::wstring 参1, std::wstring 参2);
bool 文本对比(std::string 文本1, std::string 文本2);
bool 文本对比(std::string 文本1, std::string 文本2);