#include "utf.h"

#include <string>
#include <codecvt>
#include <locale>

std::string utf::to_utf8(const std::string &s)
{
    return s;
}

std::string utf::to_utf8(const std::wstring &s)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    auto const p = reinterpret_cast<wchar_t const *>(s.data());
    return convert.to_bytes(p, p + s.size());
}

std::string utf::to_utf8(const std::u16string &s)
{
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> conv;
    return conv.to_bytes(s);
}

std::string utf::to_utf8(const std::u32string &s)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.to_bytes(s);
}


std::u16string utf::to_utf16(const std::string &s)
{
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> convert;
    return convert.from_bytes(s);
}

std::u16string utf::to_utf16(const std::u16string &s)
{
    return s;
}

std::u32string utf::to_utf32(const std::string &s)
{
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv;
    return conv.from_bytes(s);
}

std::u32string utf::to_utf32(const std::u32string &s)
{
    return s;
}

std::u32string utf::to_utf32(const std::wstring &s)
{
    return utf::to_utf32(utf::to_utf8(s));
}

std::wstring utf::to_wstring(const std::wstring &s)
{
    return s;
}

std::wstring utf::to_wstring(const std::string &s)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    auto asInt = convert.from_bytes(s);
    return std::wstring(reinterpret_cast<wchar_t const *>(asInt.data()), asInt.length());
}

std::wstring utf::to_wstring(const std::u32string &s)
{
    return utf::to_wstring(utf::to_utf8(s));
}


