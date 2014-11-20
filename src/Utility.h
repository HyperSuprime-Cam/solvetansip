#ifndef  gc3b5318a_affe_4ca1_b45e_5717bfb25a93
#define  gc3b5318a_affe_4ca1_b45e_5717bfb25a93

/** Miscellaneous utilities
*/

#include <string>
#include <cstdarg>

namespace hsc { namespace meas {
namespace tansip {

/** vsprintf wrapper (returned string is truncated by 127 chars)
*/
inline
std::string vfmt(char const* format, std::va_list va){
    char str[128];
    std::vsnprintf(str, sizeof(str)/sizeof(str[0]) - 1, format, va);
    str[sizeof(str)/sizeof(str[0]) - 1] = char();

    return std::string(str);
}

/** sprintf wrapper.
    The returned string has limitation in its length: see vfmt().
*/
inline
std::string fmt(char const* format, ...){
    std::va_list va;
    va_start(va, format);

    std::string s = vfmt(format, va);

    va_end(va);
    return s;
}


} // namespace tansip
}} // namespace hsc::meas
#endif //gc3b5318a_affe_4ca1_b45e_5717bfb25a93
