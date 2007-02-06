//---------------------------------------------------------------------------
#pragma hdrstop
#include "dsExceptions.h"
//---------------------------------------------------------------------------
namespace ds
{

CDFASTCALL eExceptionBase::eExceptionBase()
    : mMessage()
{
}

CDFASTCALL eExceptionBase::eExceptionBase( const char *message )
    : mMessage(message)
{
}

CDFASTCALL eExceptionBase::eExceptionBase( const ds_string& message )
    : mMessage(message)
{
}

CDFASTCALL eExceptionBase::eExceptionBase( const eExceptionBase& src )
    : mMessage(src.mMessage)
{
}

};
