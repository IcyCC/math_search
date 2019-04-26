#ifndef __UTF_H
#define __UTF_H

#include <type_traits>
#include <string>
#include <iostream>

namespace utf
{

std::string to_utf8(const std::string &s);
std::string to_utf8(const std::u16string &s);
std::string to_utf8(const std::u32string &s);
std::string to_utf8(const std::wstring &s);

std::wstring to_wstring(const std::wstring &s);
std::wstring to_wstring(const std::string &s);
std::wstring to_wstring(const std::u32string &s);

std::u16string to_utf16(const std::string &s);
std::u16string to_utf16(const std::u16string &s);

std::u32string to_utf32(const std::string &s);
std::u32string to_utf32(const std::wstring &s);
std::u32string to_utf32(const std::u32string &s);

} // namespace utf

// output string
template<typename CharT, typename Traits, typename Allocator, 
         typename = std::enable_if_t<!std::is_same_v<CharT, char>>>
std::ostream&
    operator<<(std::ostream& os,
               const std::basic_string<CharT, Traits, Allocator>& str)
{
    os << utf::to_utf8(str);
    return os;
}

#endif // __UTF_H

