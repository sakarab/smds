/****************************************************************************
  smds - the openSource Memory DataSet

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Please read the "Doc\License.txt" for more copyright and license
  information.
****************************************************************************/
#ifndef SM_DS_EXCEPTIONS_H
#define SM_DS_EXCEPTIONS_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <exception>
#include "dsTypes.h"

namespace ds
{

class eExceptionBase : public std::exception
{
private:
    ds_string   mMessage;
public:
    CDFASTCALL eExceptionBase();
    CDFASTCALL eExceptionBase( const char *message );
    CDFASTCALL eExceptionBase( const ds_string& message );
    CDFASTCALL eExceptionBase( const eExceptionBase& src );
    eExceptionBase& FASTCALL operator = ( const eExceptionBase& src );

    const char *MessageChars() const                            { return ( mMessage.c_str() ); }
    const ds_string& Message() const                            { return ( mMessage ); }
};

class eDebug : public eExceptionBase
{
public:
    CDFASTCALL eDebug() : eExceptionBase()                                                      {} // empty
    CDFASTCALL eDebug( const char *message ) : eExceptionBase(message)                          {} // empty
    CDFASTCALL eDebug( const ds_string& message ) : eExceptionBase(message)                     {} // empty
};

class eInvalidOperation : public eExceptionBase
{
public:
    CDFASTCALL eInvalidOperation() : eExceptionBase()                                           {} // empty
    CDFASTCALL eInvalidOperation( const char *message ) : eExceptionBase(message)               {} // empty
    CDFASTCALL eInvalidOperation( const ds_string& message ) : eExceptionBase(message)          {} // empty
};

class eDllLoadError : public eExceptionBase
{
public:
    CDFASTCALL eDllLoadError() : eExceptionBase()                                               {} // empty
    CDFASTCALL eDllLoadError( const char *message ) : eExceptionBase(message)                   {} // empty
    CDFASTCALL eDllLoadError( const ds_string& message ) : eExceptionBase(message)              {} // empty
};

class eFieldNotFound : public eExceptionBase
{
public:
    CDFASTCALL eFieldNotFound() : eExceptionBase()                                              {} // empty
    CDFASTCALL eFieldNotFound( const char *message ) : eExceptionBase(message)                  {} // empty
    CDFASTCALL eFieldNotFound( const ds_string& message ) : eExceptionBase(message)             {} // empty
};

class eFieldExists : public eExceptionBase
{
public:
    CDFASTCALL eFieldExists() : eExceptionBase()                                                {} // empty
    CDFASTCALL eFieldExists( const char *message ) : eExceptionBase(message)                    {} // empty
    CDFASTCALL eFieldExists( const ds_string& message ) : eExceptionBase(message)               {} // empty
};

class eUnknownFieldType : public eExceptionBase
{
public:
    CDFASTCALL eUnknownFieldType() : eExceptionBase()                                           {} // empty
    CDFASTCALL eUnknownFieldType( const char *message ) : eExceptionBase(message)               {} // empty
    CDFASTCALL eUnknownFieldType( const ds_string& message ) : eExceptionBase(message)          {} // empty
};

class eVariantConversion : public eExceptionBase
{
public:
    CDFASTCALL eVariantConversion() : eExceptionBase()                                          {} // empty
    CDFASTCALL eVariantConversion( const char *message ) : eExceptionBase(message)              {} // empty
    CDFASTCALL eVariantConversion( const ds_string& message ) : eExceptionBase(message)         {} // empty
};

class eNotApplicableOperation : public eExceptionBase
{
public:
    CDFASTCALL eNotApplicableOperation() : eExceptionBase()                                     {} // empty
    CDFASTCALL eNotApplicableOperation( const char *message ) : eExceptionBase(message)         {} // empty
    CDFASTCALL eNotApplicableOperation( const ds_string& message ) : eExceptionBase(message)    {} // empty
};

class eNullFieldValue : public eExceptionBase
{
public:
    CDFASTCALL eNullFieldValue() : eExceptionBase()                                             {} // empty
    CDFASTCALL eNullFieldValue( const char *message ) : eExceptionBase(message)                 {} // empty
    CDFASTCALL eNullFieldValue( const ds_string& message ) : eExceptionBase(message)            {} // empty
};

class eIOError : public eExceptionBase
{
public:
    CDFASTCALL eIOError() : eExceptionBase()                                                    {} // empty
    CDFASTCALL eIOError( const char *message ) : eExceptionBase(message)                        {} // empty
    CDFASTCALL eIOError( const ds_string& message ) : eExceptionBase(message)                   {} // empty
};

class eIOReadError : public eIOError
{
public:
    CDFASTCALL eIOReadError() : eIOError()                                                      {} // empty
    CDFASTCALL eIOReadError( const char *message ) : eIOError(message)                          {} // empty
    CDFASTCALL eIOReadError( const ds_string& message ) : eIOError(message)                     {} // empty
};

class eIOWriteError : public eIOError
{
public:
    CDFASTCALL eIOWriteError() : eIOError()                                                     {} // empty
    CDFASTCALL eIOWriteError( const char *message ) : eIOError(message)                         {} // empty
    CDFASTCALL eIOWriteError( const ds_string& message ) : eIOError(message)                    {} // empty
};

class ePacketError : public eIOError
{
public:
    CDFASTCALL ePacketError() : eIOError()                                                      {} // empty
    CDFASTCALL ePacketError( const char *message ) : eIOError(message)                          {} // empty
    CDFASTCALL ePacketError( const ds_string& message ) : eIOError(message)                     {} // empty
};

};
//---------------------------------------------------------------------------
#endif

