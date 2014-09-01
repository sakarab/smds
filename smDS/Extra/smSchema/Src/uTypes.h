#ifndef UTYPES_H
#define UTYPES_H

#include <string>

namespace sm
{

#if defined (UNICODE)

typedef wchar_t                 tchar;
typedef std::string<tchar>      tstring;

#else

typedef char                    tchar;
typedef std::string<tchar>      tstring;

#endif

typedef std::string<wchar_t>    ustring;
typedef std::string<char>       sstring;

};

#endif
