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
#ifndef uTablesH
#define uTablesH
//---------------------------------------------------------------------------
#include <dsData.h>
//---------------------------------------------------------------------------

//***********************************************************************
//******    tblLocation
//***********************************************************************
class tblLocation_map
{
private:
    tblLocation_map();
    tblLocation_map( const tblLocation_map& src );
    tblLocation_map& operator = ( const tblLocation_map& src );
public:
    // enum FieldNames { LocationID, LocTypeID, IsUser, SerialNo, Drive };

    int     LocationID_;
    short   LocTypeID_;
    short   IsUser_;
    int     SerialNo_;
    wchar_t Drive_[2];
};

class tblLocation_data
{
protected:
    static const smds::detail::cFieldDef_   tblLocation_Fields[];
    static const smds::detail::cFieldDefs_  tblLocation_FieldDef;
};

class tblLocation_raw : public tblLocation_data, public smds::detail::cRawRecordPtr
{
public:
    CDFASTCALL tblLocation_raw( smds::detail::cRawBuffer& raw_buffer )
        : smds::detail::cRawRecordPtr(raw_buffer)
    {
    }
    tblLocation_raw * FASTCALL operator->()                         { return ( this ); }
    const tblLocation_raw * FASTCALL operator->() const             { return ( this ); }
    //static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetLocationID() const                              { return ( ReadInteger( tblLocation_Fields[0] ) ); }
    short FASTCALL GetLocTypeID() const                             { return ( ReadShort( tblLocation_Fields[1] ) ); }
    short FASTCALL GetIsUser() const                                { return ( ReadShort( tblLocation_Fields[2] ) ); }
    int FASTCALL GetSerialNo() const                                { return ( ReadInteger( tblLocation_Fields[3] ) ); }
};

class tblLocation_rec : public tblLocation_data, public smds::detail::cRecordPtr
{
public:
    typedef tblLocation_raw    raw;
public:
    CDFASTCALL tblLocation_rec( smds::detail::DoubleBuffer& double_buffer )
        : smds::detail::cRecordPtr(double_buffer)
    {
    }
    tblLocation_rec * FASTCALL operator->()                         { return ( this ); }
    const tblLocation_rec * FASTCALL operator->() const             { return ( this ); }
    static const smds::detail::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetLocationID() const                              { return ( ReadInteger( tblLocation_Fields[0] ) ); }
    short FASTCALL GetLocTypeID() const                             { return ( ReadShort( tblLocation_Fields[1] ) ); }
    short FASTCALL GetIsUser() const                                { return ( ReadShort( tblLocation_Fields[2] ) ); }
    int FASTCALL GetSerialNo() const                                { return ( ReadInteger( tblLocation_Fields[3] ) ); }
};

typedef smds::cuTable<tblLocation_rec>      tblLocation;
typedef smds::shared_ptr<tblLocation>       tblLocation_ptr;
//---------------------------------------------------------------------------

//***********************************************************************
//******    tblFiles
//***********************************************************************
class tblFiles_map
{
private:
    tblFiles_map();
    tblFiles_map( const tblFiles_map& src );
    tblFiles_map& operator = ( const tblFiles_map& src );
public:
    int             FileID_;
    int             PathID_;
#ifdef SM_DS_STRING_AS_STRING
    ds_string       LongFileName_;
#else
    char            LongFileName_[255];
#endif
    int             fSize_;
    smds::cDateTime fDate_;
#ifdef SM_DS_STRING_AS_STRING
    ds_string       Description_;
#else
    char            Description_[255];
#endif
    int             zipID_;
};

class tblFiles_data
{
protected:
    static const smds::detail::cFieldDef_   tblFiles_Fields[];
    static const smds::detail::cFieldDefs_  tblFiles_FieldDef;
public:
    // enum FieldNames { FileID, PathID, LongFileName, fSize, fDate, Description, zipID };
};

class tblFiles_raw : public tblFiles_data, public smds::detail::cRawRecordPtr
{
public:
    CDFASTCALL tblFiles_raw( smds::detail::cRawBuffer& raw_buffer )
        : smds::detail::cRawRecordPtr(raw_buffer)
    {
    }
    tblFiles_raw * FASTCALL operator->()                         { return ( this ); }
    const tblFiles_raw * FASTCALL operator->() const             { return ( this ); }
    //static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetFileID() const                          { return ( ReadInteger( tblFiles_Fields[0] ) ); }
    bool FASTCALL FileID_IsNull() const                     { return ( IsNull( tblFiles_Fields[0] ) ); }

    int FASTCALL GetPathID() const                          { return ( ReadInteger( tblFiles_Fields[1] ) ); }
    bool FASTCALL PathID_IsNull() const                     { return ( IsNull( tblFiles_Fields[1] ) ); }

    ds_string FASTCALL GetLongFileName() const              { return ( ReadString( tblFiles_Fields[2] ) ); }
    bool FASTCALL LongFileName_IsNull() const               { return ( IsNull( tblFiles_Fields[2] ) ); }

    int  FASTCALL GetfSize() const                          { return ( ReadInteger( tblFiles_Fields[3] ) ); }
    bool FASTCALL fSize_IsNull() const                      { return ( IsNull( tblFiles_Fields[3] ) ); }

    const smds::cDateTime FASTCALL GetfDate() const         { return ( ReadDate( tblFiles_Fields[4] ) ); }
    bool FASTCALL fDate_IsNull() const                      { return ( IsNull( tblFiles_Fields[4] ) ); }

    ds_string FASTCALL GetDescription() const               { return ( ReadString( tblFiles_Fields[5] ) ); }
    bool FASTCALL Description_IsNull() const                { return ( IsNull( tblFiles_Fields[5] ) ); }

    int  FASTCALL GetzipID() const                          { return ( ReadInteger( tblFiles_Fields[6] ) ); }
    bool FASTCALL zipID_IsNull() const                      { return ( IsNull( tblFiles_Fields[6] ) ); }
};

class tblFiles_rec : public tblFiles_data, public smds::detail::cRecordPtr
{
public:
    typedef tblFiles_raw    raw;
public:
    CDFASTCALL tblFiles_rec( smds::detail::DoubleBuffer& double_buffer )
        : smds::detail::cRecordPtr(double_buffer)
    {
    }
    tblFiles_rec * FASTCALL operator->()                         { return ( this ); }
    const tblFiles_rec * FASTCALL operator->() const             { return ( this ); }
    static const smds::detail::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetFileID() const                               { return ( ReadInteger( tblFiles_Fields[0] ) ); }
    void FASTCALL SetFileID( int value )                         { WriteInteger( tblFiles_Fields[0], value ); }
    bool FASTCALL FileID_IsNull() const                          { return ( IsNull( tblFiles_Fields[0] ) ); }

    int FASTCALL GetPathID() const                              { return ( ReadInteger( tblFiles_Fields[1] ) ); }
    void FASTCALL SetPathID( int value )                        { WriteInteger( tblFiles_Fields[1], value ); }
    bool FASTCALL PathID_IsNull() const                         { return ( IsNull( tblFiles_Fields[1] ) ); }

    ds_string FASTCALL GetLongFileName() const                  { return ( ReadString( tblFiles_Fields[2] ) ); }
    void FASTCALL SetLongFileName( const ds_string& value )     { WriteString( tblFiles_Fields[2], value ); }
    void FASTCALL SetLongFileName( const char *value )          { WriteString( tblFiles_Fields[2], value ); }
    bool FASTCALL LongFileName_IsNull() const                   { return ( IsNull( tblFiles_Fields[2] ) ); }

    int  FASTCALL GetfSize() const                              { return ( ReadInteger( tblFiles_Fields[3] ) ); }
    void FASTCALL SetfSize( int value )                         { WriteInteger( tblFiles_Fields[3], value ); }
    bool FASTCALL fSize_IsNull() const                          { return ( IsNull( tblFiles_Fields[3] ) ); }

    smds::cDateTime FASTCALL GetfDate() const                   { return ( ReadDate( tblFiles_Fields[4] ) ); }
    void FASTCALL SetfDate( const smds::cDateTime& value )      { WriteDate( tblFiles_Fields[4], value ); }
    bool FASTCALL fDate_IsNull() const                          { return ( IsNull( tblFiles_Fields[4] ) ); }

    ds_string FASTCALL GetDescription() const                   { return ( ReadString( tblFiles_Fields[5] ) ); }
    void FASTCALL SetDescription( const ds_string& value )      { WriteString( tblFiles_Fields[5], value ); }
    void FASTCALL SetDescription( const char *value )           { WriteString( tblFiles_Fields[5], value ); }
    bool FASTCALL Description_IsNull() const                    { return ( IsNull( tblFiles_Fields[5] ) ); }

    int  FASTCALL GetzipID() const                              { return ( ReadInteger( tblFiles_Fields[6] ) ); }
    void FASTCALL SetzipID( int value )                         { WriteInteger( tblFiles_Fields[6], value ); }
    bool FASTCALL zipID_IsNull() const                          { return ( IsNull( tblFiles_Fields[6] ) ); }
};

typedef smds::cuTable<tblFiles_rec>                 tblFiles;
typedef smds::shared_ptr<tblFiles>                  tblFiles_ptr;
//---------------------------------------------------------------------------
#endif
