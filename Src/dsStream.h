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
//---------------------------------------------------------------------------
#ifndef SM_DS_STREAM_H
#define SM_DS_STREAM_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include "dsSmartPtr.h"
#include <vector>
//---------------------------------------------------------------------------
namespace smds
{

//***********************************************************************
//******    cStreamBuff
//***********************************************************************
class cStreamBuff
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
public:
	enum seek_mode { po_begin = 0, po_current = 1, po_end = 2 };
    typedef unsigned long       size_type;
    typedef long                seek_size_type;
    // non copyable
    CDFASTCALL cStreamBuff( const cStreamBuff& src );
    cStreamBuff& FASTCALL operator = ( const cStreamBuff& src );
public:
    CDFASTCALL cStreamBuff()                                            {} // empty
    virtual CDFASTCALL ~cStreamBuff();

	virtual size_type FASTCALL GetPosition();
	virtual void FASTCALL SetPosition( size_type pos );
	virtual size_type FASTCALL GetSize();
	virtual void FASTCALL SetSize( size_type new_size );

	virtual size_type FASTCALL Read( void *buffer, size_type count ) = 0;
	virtual size_type FASTCALL Write( const void *buffer, size_type count ) = 0;
	virtual size_type FASTCALL Seek( seek_size_type offset, seek_mode origin ) = 0;
};

//***********************************************************************
//******    cAttachedStreamBuffer
//***********************************************************************
class cAttachedStreamBuffer : public cStreamBuff
{
private:
    std::vector<char>   *mBuffer;
    size_type           mPosition;
protected:
    void FASTCALL InitBuffer( std::vector<char> *buffer )       { mBuffer = buffer; }
    void FASTCALL DoneBuffer()                                  { mBuffer = 0; }
public:
    CDFASTCALL cAttachedStreamBuffer();

	virtual size_type FASTCALL GetPosition();
	virtual void FASTCALL SetPosition( size_type pos );
	virtual size_type FASTCALL GetSize();
	virtual void FASTCALL SetSize( size_type new_size );

	virtual size_type FASTCALL Read( void *buffer, size_type count );
	virtual size_type FASTCALL Write( const void *buffer, size_type count );
	virtual size_type FASTCALL Seek( seek_size_type offset, seek_mode origin );
};

//***********************************************************************
//******    cMemoryStreamBuffer
//***********************************************************************
class cMemoryStreamBuffer : public cAttachedStreamBuffer
{
private:
    std::vector<char>   mBuffer;
public:
    CDFASTCALL cMemoryStreamBuffer();
    CDFASTCALL ~cMemoryStreamBuffer();
};

//***********************************************************************
//******    cStream
//***********************************************************************
class cStream
{
private:
	enum { MAX_BUF_SIZE = 0x0000F000 };
    shared_ptr<cStreamBuff>     mStreamBuffer;

	cStreamBuff::size_type FASTCALL InternalCopyFrom( cStream& source, cStreamBuff::size_type count );
protected:
public:
	CDFASTCALL cStream( const shared_ptr<cStreamBuff>& stream_buffer );
    CDFASTCALL cStream( const cStream& src );
	CDFASTCALL ~cStream();
    cStream& FASTCALL operator = ( const cStream& src );

	cStreamBuff::size_type FASTCALL GetPosition()                   { return ( mStreamBuffer->GetPosition() ); }
	void FASTCALL SetPosition( cStreamBuff::size_type pos )         { mStreamBuffer->SetPosition( pos ); }
	cStreamBuff::size_type FASTCALL GetSize()                       { return ( mStreamBuffer->GetSize() ); }
	void FASTCALL SetSize( cStreamBuff::size_type new_size )        { mStreamBuffer->SetSize( new_size ); }

	cStreamBuff::size_type FASTCALL Read( void *buffer, cStreamBuff::size_type count )
    {
        return ( mStreamBuffer->Read( buffer, count ) );
    }
	cStreamBuff::size_type FASTCALL Write( const void *buffer, cStreamBuff::size_type count )
    {
        return ( mStreamBuffer->Write( buffer, count ) );
    }
	cStreamBuff::size_type FASTCALL Seek( cStreamBuff::seek_size_type offset, cStreamBuff::seek_mode origin )
    {
        return ( mStreamBuffer->Seek( offset, origin ) );
    }

	cStream& FASTCALL ReadBuffer( void *buffer, cStreamBuff::size_type count );
	cStream& FASTCALL WriteBuffer( const void *buffer, cStreamBuff::size_type count );
	// cStreamBuff::size_type FASTCALL CopyFrom( cStream& source, cStreamBuff::size_type count );
};

inline cStream& FASTCALL operator << ( cStream& st, const bool a )              { return ( st.WriteBuffer( &a, sizeof(bool) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const char a )              { return ( st.WriteBuffer( &a, sizeof(char) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const unsigned char a )     { return ( st.WriteBuffer( &a, sizeof(unsigned char) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const wchar_t a )           { return ( st.WriteBuffer( &a, sizeof(wchar_t) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const short a )             { return ( st.WriteBuffer( &a, sizeof(short) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const unsigned short a )    { return ( st.WriteBuffer( &a, sizeof(unsigned short) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const int a )               { return ( st.WriteBuffer( &a, sizeof(int) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const unsigned int a )      { return ( st.WriteBuffer( &a, sizeof(unsigned int) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const long a )              { return ( st.WriteBuffer( &a, sizeof(long) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const unsigned long a )     { return ( st.WriteBuffer( &a, sizeof(unsigned long) ) ); }
inline cStream& FASTCALL operator << ( cStream& st, const double a )            { return ( st.WriteBuffer( &a, sizeof(double) ) ); }
cStream& FASTCALL operator << ( cStream& st, const char *a );

inline cStream& FASTCALL operator >> ( cStream& st, bool& a )               { return ( st.ReadBuffer( &a, sizeof(bool) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, char& a )               { return ( st.ReadBuffer( &a, sizeof(char) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, unsigned char& a )      { return ( st.ReadBuffer( &a, sizeof(unsigned char) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, wchar_t& a )            { return ( st.ReadBuffer( &a, sizeof(wchar_t) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, short& a )              { return ( st.ReadBuffer( &a, sizeof(short) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, unsigned short& a )     { return ( st.ReadBuffer( &a, sizeof(unsigned short) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, int& a )                { return ( st.ReadBuffer( &a, sizeof(int) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, unsigned int& a )       { return ( st.ReadBuffer( &a, sizeof(unsigned int) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, long& a )               { return ( st.ReadBuffer( &a, sizeof(long) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, unsigned long& a )      { return ( st.ReadBuffer( &a, sizeof(unsigned long) ) ); }
inline cStream& FASTCALL operator >> ( cStream& st, double& a )             { return ( st.ReadBuffer( &a, sizeof(double) ) ); }
// cStream& FASTCALL operator >> ( cStream& st, const char *a );

//***********************************************************************
//******    cMemoryStream
//***********************************************************************
class cMemoryStream : public cStream
{
public:
	CDFASTCALL cMemoryStream();
	CDFASTCALL ~cMemoryStream();
};

};
//---------------------------------------------------------------------------
#endif
