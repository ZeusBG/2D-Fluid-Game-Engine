#include <string>
#include <locale> 
#include <codecvt>

std::wstring StrToWstr(const char* str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;

	std::wstring name = convert.from_bytes(str);
	return name;
}