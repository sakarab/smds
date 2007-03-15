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

  Please read the "readme" file in the root directory of this
  package for more copyright and license information.
****************************************************************************/
//---------------------------------------------------------------------------
#pragma hdrstop
#include "dsStream.h"
#include "dsExceptions.h"
//---------------------------------------------------------------------------
namespace ds
{

//***********************************************************************
//******    cStreamBuff
//***********************************************************************
CDFASTCALL cStreamBuff::~cStreamBuff()
{
}

cStreamBuff::size_type FASTCALL cStreamBuff::GetPosition()
{
    return ( Seek( 0, po_current ) );
}

void FASTCALL cStreamBuff::SetPosition( size_type pos )
{
    Seek( pos, po_begin );
}

cStreamBuff::size_type FASTCALL cStreamBuff::GetSize()
{
    size_type   result, pos;

    pos = Seek( 0, po_current );
    result = Seek( 0, po_end );
    Seek( pos, po_begin );
    return ( result );
}

void FASTCALL cStreamBuff::SetSize( size_type new_size )
{
}

//***********************************************************************
//******    cAttachedStreamBuffer
//***********************************************************************
CDFASTCALL cAttachedStreamBuffer::cAttachedStreamBuffer()
    : cStreamBuff(), mBuffer(0), mPosition(0)
{
}

cStreamBuff::size_type FASTCALL cAttachedStreamBuffer::GetPosition()
{
    return ( mPosition );
}

void FASTCALL cAttachedStreamBuffer::SetPosition( size_type pos )
{
    if ( pos <= mBuffer->size() )
        mPosition = pos;
    else
        mPosition = mBuffer->size();
}

cStreamBuff::size_type FASTCALL cAttachedStreamBuffer::GetSize()
{
    return ( mBuffer->size() );
}

void FASTCALL cAttachedStreamBuffer::SetSize( size_type new_size )
{
    mBuffer->resize( new_size );
    SetPosition( mPosition );
}

cStreamBuff::size_type FASTCALL cAttachedStreamBuffer::Read( void *buffer, size_type count )
{
    size_type   result = 0;

    if ( count > 0 )
    {
        if ( (result = mBuffer->size() - mPosition) > 0 )
        {
            if ( result > count )
                result = count;
            std::memcpy( buffer, &(mBuffer->front()) + mPosition, result );
            mPosition += result;
        }
    }
    return ( result );
}

cStreamBuff::size_type FASTCALL cAttachedStreamBuffer::Write( const void *buffer, size_type count )
{
    size_type   new_pos;

    if ( count > 0 )
    {
        if ( (new_pos = mPosition + count) > 0 )
        {
            std::vector<char>::size_type    old_capacity = mBuffer->capacity();

            if ( new_pos > old_capacity )
                mBuffer->reserve( old_capacity * 2 );
            if ( new_pos > mBuffer->size() )
                mBuffer->resize( new_pos );
            std::memcpy( &(mBuffer->front()) + mPosition, buffer, count );
            mPosition = new_pos;
        }
    }
    return ( count );
}

cStreamBuff::size_type FASTCALL cAttachedStreamBuffer::Seek( seek_size_type offset, seek_mode origin )
{
    switch ( origin )
    {
        case po_begin	: mPosition = offset;                       break;
        case po_current	: mPosition += offset;                      break;
        case po_end		: mPosition = mBuffer->size() + offset;     break;
    }
    if ( mPosition > mBuffer->size() )
        mBuffer->resize( mPosition );
    return ( mPosition );
}

//***********************************************************************
//******    cMemoryStreamBuffer
//***********************************************************************
CDFASTCALL cMemoryStreamBuffer::cMemoryStreamBuffer()
    : cAttachedStreamBuffer(), mBuffer()
{
    InitBuffer( &mBuffer );
}

CDFASTCALL cMemoryStreamBuffer::~cMemoryStreamBuffer()
{
    DoneBuffer();
}

//***********************************************************************
//******    cStream
//***********************************************************************
CDFASTCALL cStream::cStream( const shared_ptr<cStreamBuff>& stream_buffer )
    : mStreamBuffer(stream_buffer)
{
}

CDFASTCALL cStream::cStream( const cStream& src )
    : mStreamBuffer(src.mStreamBuffer)
{
}

CDFASTCALL cStream::~cStream()
{
}

cStream& FASTCALL cStream::operator = ( const cStream& src )
{
    shared_ptr<cStreamBuff>     tmp( src.mStreamBuffer );

    std::swap( mStreamBuffer, tmp );
    return ( *this );
}

cStream& FASTCALL cStream::ReadBuffer( void *buffer, cStreamBuff::size_type count )
{
    if ( count != 0 && Read( buffer, count ) != count )
        throw eIOReadError();
    return ( *this );
}

cStream& FASTCALL cStream::WriteBuffer( const void *buffer, cStreamBuff::size_type count )
{
    if ( count != 0 && Write( buffer, count ) != count )
        throw eIOWriteError();
    return ( *this );
}

//--    Write   ----
cStream& FASTCALL operator << ( cStream& st, const char *a )
{
    unsigned int    size = std::strlen(a);

    st << size;
    if ( size != 0 )
        st.WriteBuffer( a, size );
    return ( st );
}

//--    Read    ----
//cStream& FASTCALL operator >> ( cStream& st, const char *a )
//{
//    return ( st );
//}

//***********************************************************************
//******    cMemoryStream
//***********************************************************************
CDFASTCALL cMemoryStream::cMemoryStream()
    : cStream( shared_ptr<cStreamBuff>( new cMemoryStreamBuffer() ) )
{
}

CDFASTCALL cMemoryStream::~cMemoryStream()
{
}

};
//---------------------------------------------------------------------------

