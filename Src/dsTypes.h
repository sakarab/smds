#if ! defined (SM_DS_TYPES_H)
#define SM_DS_TYPES_H

#include "dsConfig.h"
#include "dsSmartPtr.h"

/*
#if defined (__BORLANDC__) && ! defined (_NO_VCL)
    #include    <System.hpp>

    typedef AnsiString      ds_string;
#else
    #include    <string>

    typedef std::string     ds_string;
#endif
*/

#include <dsString.h>

typedef ds::string_tag     ds_sstring;
typedef ds::wstring_tag    ds_wstring;

#if defined ( SM_UNICODE )
    typedef ds_wstring      ds_string;
#else
    typedef ds_sstring      ds_string;
#endif

// foward declaration of types

namespace ds
{

class cDoubleBuffer;
typedef shared_ptr< cDoubleBuffer >     cDoubleBuffer_ptr;
typedef cDoubleBuffer_ptr               cData_value_type;

namespace detail
{

class SortControler;

};

};


#endif


 