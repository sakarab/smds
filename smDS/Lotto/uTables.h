//---------------------------------------------------------------------------
#ifndef uTablesH
#define uTablesH
//---------------------------------------------------------------------------
#include <dsData.h>
//---------------------------------------------------------------------------

//***********************************************************************
//******    DRAWS
//***********************************************************************
class DRAWS_map
{
private:
    DRAWS_map();
    DRAWS_map( const DRAWS_map& src );
    DRAWS_map& operator = ( const DRAWS_map& src );
public:
    int                 ID_;
    smds::cDateTime     DDate_;
    char                Num_1_;
    char                Num_2_;
    char                Num_3_;
    char                Num_4_;
    char                Num_5_;
    char                Num_6_;
};

class DRAWS_data
{
protected:
    static const smds::detail::cFieldDef_   DRAWS_Fields[];
    static const smds::detail::cFieldDefs_  DRAWS_FieldDef;
};

class DRAWS_raw : public DRAWS_data, public smds::detail::cRawRecordPtr
{
public:
    CDFASTCALL DRAWS_raw( smds::detail::cRawBuffer& raw_buffer )
        : smds::detail::cRawRecordPtr(raw_buffer)
    {
    }
    DRAWS_raw * FASTCALL operator->()                           { return ( this ); }
    const DRAWS_raw * FASTCALL operator->() const               { return ( this ); }

    int FASTCALL getID() const                                  { return ( ReadInteger( DRAWS_Fields[0] ) ); }
    bool FASTCALL IsNull_ID() const                             { return ( IsNull( DRAWS_Fields[0] ) ); }

    const smds::cDateTime FASTCALL getDate() const              { return ( ReadDate( DRAWS_Fields[1] ) ); }
    bool FASTCALL IsNull_Date() const                           { return ( IsNull( DRAWS_Fields[1] ) ); }

    char FASTCALL getNum_1() const                              { return ( ReadChar( DRAWS_Fields[2] ) ); }
    bool FASTCALL IsNull_Num_1() const                          { return ( IsNull( DRAWS_Fields[2] ) ); }

    char FASTCALL getNum_2() const                              { return ( ReadChar( DRAWS_Fields[3] ) ); }
    bool FASTCALL IsNull_Num_2() const                          { return ( IsNull( DRAWS_Fields[3] ) ); }

    char FASTCALL getNum_3() const                              { return ( ReadChar( DRAWS_Fields[4] ) ); }
    bool FASTCALL IsNull_Num_3() const                          { return ( IsNull( DRAWS_Fields[4] ) ); }

    char FASTCALL getNum_4() const                              { return ( ReadChar( DRAWS_Fields[5] ) ); }
    bool FASTCALL IsNull_Num_4() const                          { return ( IsNull( DRAWS_Fields[5] ) ); }

    char FASTCALL getNum_5() const                              { return ( ReadChar( DRAWS_Fields[6] ) ); }
    bool FASTCALL IsNull_Num_5() const                          { return ( IsNull( DRAWS_Fields[6] ) ); }

    char FASTCALL getNum_6() const                              { return ( ReadChar( DRAWS_Fields[7] ) ); }
    bool FASTCALL IsNull_Num_6() const                          { return ( IsNull( DRAWS_Fields[7] ) ); }
};

class DRAWS_rec : public DRAWS_data, public smds::detail::cRecordPtr
{
public:
    typedef DRAWS_raw    raw;
public:
    CDFASTCALL DRAWS_rec( smds::detail::DoubleBuffer& double_buffer )
        : smds::detail::cRecordPtr(double_buffer)
    {
    }
    DRAWS_rec * FASTCALL operator->()                           { return ( this ); }
    const DRAWS_rec * FASTCALL operator->() const               { return ( this ); }
    static const smds::detail::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL getID() const                                  { return ReadInteger( DRAWS_Fields[0] ); }
    void FASTCALL setID( int value )                            { return WriteInteger( DRAWS_Fields[0], value ); }
    bool FASTCALL IsNull_ID() const                             { return IsNull( DRAWS_Fields[0] ); }

    const smds::cDateTime FASTCALL getDate() const              { return ReadDate( DRAWS_Fields[1] ); }
    void FASTCALL setDate( const smds::cDateTime& value )       { WriteDate( DRAWS_Fields[1], value ); }
    bool FASTCALL IsNull_Date() const                           { return IsNull( DRAWS_Fields[1] ); }

    char FASTCALL getNum_1() const                              { return ReadChar( DRAWS_Fields[2] ); }
    void FASTCALL setNum_1( char value )                        { WriteChar( DRAWS_Fields[2], value ); }
    bool FASTCALL IsNull_Num_1() const                          { return IsNull( DRAWS_Fields[2] ); }

    char FASTCALL getNum_2() const                              { return ReadChar( DRAWS_Fields[3] ); }
    void FASTCALL setNum_2( char value )                        { WriteChar( DRAWS_Fields[3], value ); }
    bool FASTCALL IsNull_Num_2() const                          { return IsNull( DRAWS_Fields[3] ); }

    char FASTCALL getNum_3() const                              { return ReadChar( DRAWS_Fields[4] ); }
    void FASTCALL setNum_3( char value )                        { WriteChar( DRAWS_Fields[4], value ); }
    bool FASTCALL IsNull_Num_3() const                          { return IsNull( DRAWS_Fields[4] ); }

    char FASTCALL getNum_4() const                              { return ReadChar( DRAWS_Fields[5] ); }
    void FASTCALL setNum_4( char value )                        { WriteChar( DRAWS_Fields[5], value ); }
    bool FASTCALL IsNull_Num_4() const                          { return IsNull( DRAWS_Fields[5] ); }

    char FASTCALL getNum_5() const                              { return ReadChar( DRAWS_Fields[6] ); }
    void FASTCALL setNum_5( char value )                        { WriteChar( DRAWS_Fields[6], value ); }
    bool FASTCALL IsNull_Num_5() const                          { return IsNull( DRAWS_Fields[6] ); }

    char FASTCALL getNum_6() const                              { return ReadChar( DRAWS_Fields[7] ); }
    void FASTCALL setNum_6( char value )                        { WriteChar( DRAWS_Fields[7], value ); }
    bool FASTCALL IsNull_Num_6() const                          { return IsNull( DRAWS_Fields[7] ); }
};

typedef smds::cuTable<DRAWS_rec>                    tDRAWS;
typedef smds::shared_ptr<tDRAWS>                    spDRAWS;
//---------------------------------------------------------------------------
#endif
