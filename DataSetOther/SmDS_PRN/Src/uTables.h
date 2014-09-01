//---------------------------------------------------------------------------
#ifndef PRN_TABLES_H
#define PRN_TABLES_H
//---------------------------------------------------------------------------
#include <dsConfig.h>
#include <ssport.h>
#include <dsData.h>
//---------------------------------------------------------------------------
#ifdef SM_DS_STRING_AS_STRING
    #define STRING_FM(name,size)    ds_string name
    typedef ds_string               STRING_RET;
#else
    #define STRING_FM(name,size)    char    name[size]
    typedef ds_string               STRING_RET;
#endif

//***********************************************************************
//******    tblCAN
//***********************************************************************
class tblCAN_map
{
private:
    tblCAN_map();
    tblCAN_map( const tblCAN_map& src );
    tblCAN_map& operator = ( const tblCAN_map& src );
public:
    int            CANID_;
    int            CALID_;
    short          CANDAY_;
    ds::cDateTime  CANSTARTTIME_;
    double         CANDURATION_;
    int            SHTID_;
    STRING_FM      (SHTCODE_,20);
};

class tblCAN_data
{
protected:
    static const ds::cFieldDef_   tblCAN_Fields[];
    static const ds::cFieldDefs_  tblCAN_FieldDef;
};

class tblCAN_raw : public tblCAN_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblCAN_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)             {} // empty
    tblCAN_raw * FASTCALL operator->()              { return ( this ); }
    const tblCAN_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetCANID() const                   { return ( ReadInteger( tblCAN_Fields[0] ) ); }
    bool FASTCALL CANID_IsNull() const              { return ( IsNull( tblCAN_Fields[0] ) ); }

    int FASTCALL GetCALID() const                   { return ( ReadInteger( tblCAN_Fields[1] ) ); }
    bool FASTCALL CALID_IsNull() const              { return ( IsNull( tblCAN_Fields[1] ) ); }

    short FASTCALL GetCANDAY() const                { return ( ReadShort( tblCAN_Fields[2] ) ); }
    bool FASTCALL CANDAY_IsNull() const             { return ( IsNull( tblCAN_Fields[2] ) ); }

    ds::cDateTime FASTCALL GetCANSTARTTIME() const  { return ( ReadDate( tblCAN_Fields[3] ) ); }
    bool FASTCALL CANSTARTTIME_IsNull() const       { return ( IsNull( tblCAN_Fields[3] ) ); }

    double FASTCALL GetCANDURATION() const          { return ( ReadFloat( tblCAN_Fields[4] ) ); }
    bool FASTCALL CANDURATION_IsNull() const        { return ( IsNull( tblCAN_Fields[4] ) ); }

    int FASTCALL GetSHTID() const                   { return ( ReadInteger( tblCAN_Fields[5] ) ); }
    bool FASTCALL SHTID_IsNull() const              { return ( IsNull( tblCAN_Fields[5] ) ); }

    ds_string FASTCALL GetSHTCODE() const           { return ( ReadString( tblCAN_Fields[6] ) ); }
    bool FASTCALL SHTCODE_IsNull() const            { return ( IsNull( tblCAN_Fields[6] ) ); }
};

class tblCAN_rec : public tblCAN_data, public ds::cRecordPtr
{
public:
    typedef tblCAN_raw    raw;
public:
    CDFASTCALL tblCAN_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblCAN_rec * FASTCALL operator->()              { return ( this ); }
    const tblCAN_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetCANID() const                                { return ( ReadInteger( tblCAN_Fields[0] ) ); }
    bool FASTCALL CANID_IsNull() const                           { return ( IsNull( tblCAN_Fields[0] ) ); }
    void FASTCALL SetCANID( int value )                          { WriteInteger( tblCAN_Fields[0], value ); }

    int FASTCALL GetCALID() const                                { return ( ReadInteger( tblCAN_Fields[1] ) ); }
    bool FASTCALL CALID_IsNull() const                           { return ( IsNull( tblCAN_Fields[1] ) ); }
    void FASTCALL SetCALID( int value )                          { WriteInteger( tblCAN_Fields[1], value ); }

    short FASTCALL GetCANDAY() const                             { return ( ReadShort( tblCAN_Fields[2] ) ); }
    bool FASTCALL CANDAY_IsNull() const                          { return ( IsNull( tblCAN_Fields[2] ) ); }
    void FASTCALL SetCANDAY( short value )                       { WriteShort( tblCAN_Fields[2], value ); }

    ds::cDateTime FASTCALL GetCANSTARTTIME() const               { return ( ReadDate( tblCAN_Fields[3] ) ); }
    bool FASTCALL CANSTARTTIME_IsNull() const                    { return ( IsNull( tblCAN_Fields[3] ) ); }
    void FASTCALL SetCANSTARTTIME( const ds::cDateTime& value )  { WriteDate( tblCAN_Fields[3], value ); }

    double FASTCALL GetCANDURATION() const                       { return ( ReadFloat( tblCAN_Fields[4] ) ); }
    bool FASTCALL CANDURATION_IsNull() const                     { return ( IsNull( tblCAN_Fields[4] ) ); }
    void FASTCALL SetCANDURATION( double value )                 { WriteFloat( tblCAN_Fields[4], value ); }

    int FASTCALL GetSHTID() const                                { return ( ReadInteger( tblCAN_Fields[5] ) ); }
    bool FASTCALL SHTID_IsNull() const                           { return ( IsNull( tblCAN_Fields[5] ) ); }
    void FASTCALL SetSHTID( int value )                          { WriteInteger( tblCAN_Fields[5], value ); }

    ds_string FASTCALL GetSHTCODE() const                        { return ( ReadString( tblCAN_Fields[6] ) ); }
    bool FASTCALL SHTCODE_IsNull() const                         { return ( IsNull( tblCAN_Fields[6] ) ); }
    void FASTCALL SetSHTCODE( const ds_string& value )           { WriteString( tblCAN_Fields[6], value ); }
};

typedef ds::cuTable<tblCAN_rec>  tblCAN;
typedef ds::shared_ptr<tblCAN>   tblCAN_ptr;
//***********************************************************************
//******    tblCEX
//***********************************************************************
class tblCEX_map
{
private:
    tblCEX_map();
    tblCEX_map( const tblCEX_map& src );
    tblCEX_map& operator = ( const tblCEX_map& src );
public:
    int            CEXID_;
    int            CALID_;
    ds::cDateTime  CEXDATE_;
    double         CEXDURATION_;
    ds::cDateTime  CEXSTARTTIME_;
    int            SHTID_;
    STRING_FM      (SHTCODE_,20);
    STRING_FM      (SHTDESCRIPTION_,40);
};

class tblCEX_data
{
protected:
    static const ds::cFieldDef_   tblCEX_Fields[];
    static const ds::cFieldDefs_  tblCEX_FieldDef;
};

class tblCEX_raw : public tblCEX_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblCEX_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)             {} // empty
    tblCEX_raw * FASTCALL operator->()              { return ( this ); }
    const tblCEX_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetCEXID() const                   { return ( ReadInteger( tblCEX_Fields[0] ) ); }
    bool FASTCALL CEXID_IsNull() const              { return ( IsNull( tblCEX_Fields[0] ) ); }

    int FASTCALL GetCALID() const                   { return ( ReadInteger( tblCEX_Fields[1] ) ); }
    bool FASTCALL CALID_IsNull() const              { return ( IsNull( tblCEX_Fields[1] ) ); }

    ds::cDateTime FASTCALL GetCEXDATE() const       { return ( ReadDate( tblCEX_Fields[2] ) ); }
    bool FASTCALL CEXDATE_IsNull() const            { return ( IsNull( tblCEX_Fields[2] ) ); }

    double FASTCALL GetCEXDURATION() const          { return ( ReadFloat( tblCEX_Fields[3] ) ); }
    bool FASTCALL CEXDURATION_IsNull() const        { return ( IsNull( tblCEX_Fields[3] ) ); }

    ds::cDateTime FASTCALL GetCEXSTARTTIME() const  { return ( ReadDate( tblCEX_Fields[4] ) ); }
    bool FASTCALL CEXSTARTTIME_IsNull() const       { return ( IsNull( tblCEX_Fields[4] ) ); }

    int FASTCALL GetSHTID() const                   { return ( ReadInteger( tblCEX_Fields[5] ) ); }
    bool FASTCALL SHTID_IsNull() const              { return ( IsNull( tblCEX_Fields[5] ) ); }

    ds_string FASTCALL GetSHTCODE() const           { return ( ReadString( tblCEX_Fields[6] ) ); }
    bool FASTCALL SHTCODE_IsNull() const            { return ( IsNull( tblCEX_Fields[6] ) ); }

    ds_string FASTCALL GetSHTDESCRIPTION() const    { return ( ReadString( tblCEX_Fields[7] ) ); }
    bool FASTCALL SHTDESCRIPTION_IsNull() const     { return ( IsNull( tblCEX_Fields[7] ) ); }
};

class tblCEX_rec : public tblCEX_data, public ds::cRecordPtr
{
public:
    typedef tblCEX_raw    raw;
public:
    CDFASTCALL tblCEX_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblCEX_rec * FASTCALL operator->()              { return ( this ); }
    const tblCEX_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetCEXID() const                                { return ( ReadInteger( tblCEX_Fields[0] ) ); }
    bool FASTCALL CEXID_IsNull() const                           { return ( IsNull( tblCEX_Fields[0] ) ); }
    void FASTCALL SetCEXID( int value )                          { WriteInteger( tblCEX_Fields[0], value ); }

    int FASTCALL GetCALID() const                                { return ( ReadInteger( tblCEX_Fields[1] ) ); }
    bool FASTCALL CALID_IsNull() const                           { return ( IsNull( tblCEX_Fields[1] ) ); }
    void FASTCALL SetCALID( int value )                          { WriteInteger( tblCEX_Fields[1], value ); }

    ds::cDateTime FASTCALL GetCEXDATE() const                    { return ( ReadDate( tblCEX_Fields[2] ) ); }
    bool FASTCALL CEXDATE_IsNull() const                         { return ( IsNull( tblCEX_Fields[2] ) ); }
    void FASTCALL SetCEXDATE( const ds::cDateTime& value )       { WriteDate( tblCEX_Fields[2], value ); }

    double FASTCALL GetCEXDURATION() const                       { return ( ReadFloat( tblCEX_Fields[3] ) ); }
    bool FASTCALL CEXDURATION_IsNull() const                     { return ( IsNull( tblCEX_Fields[3] ) ); }
    void FASTCALL SetCEXDURATION( double value )                 { WriteFloat( tblCEX_Fields[3], value ); }

    ds::cDateTime FASTCALL GetCEXSTARTTIME() const               { return ( ReadDate( tblCEX_Fields[4] ) ); }
    bool FASTCALL CEXSTARTTIME_IsNull() const                    { return ( IsNull( tblCEX_Fields[4] ) ); }
    void FASTCALL SetCEXSTARTTIME( const ds::cDateTime& value )  { WriteDate( tblCEX_Fields[4], value ); }

    int FASTCALL GetSHTID() const                                { return ( ReadInteger( tblCEX_Fields[5] ) ); }
    bool FASTCALL SHTID_IsNull() const                           { return ( IsNull( tblCEX_Fields[5] ) ); }
    void FASTCALL SetSHTID( int value )                          { WriteInteger( tblCEX_Fields[5], value ); }

    ds_string FASTCALL GetSHTCODE() const                        { return ( ReadString( tblCEX_Fields[6] ) ); }
    bool FASTCALL SHTCODE_IsNull() const                         { return ( IsNull( tblCEX_Fields[6] ) ); }
    void FASTCALL SetSHTCODE( const ds_string& value )           { WriteString( tblCEX_Fields[6], value ); }

    ds_string FASTCALL GetSHTDESCRIPTION() const                 { return ( ReadString( tblCEX_Fields[7] ) ); }
    bool FASTCALL SHTDESCRIPTION_IsNull() const                  { return ( IsNull( tblCEX_Fields[7] ) ); }
    void FASTCALL SetSHTDESCRIPTION( const ds_string& value )    { WriteString( tblCEX_Fields[7], value ); }
};

typedef ds::cuTable<tblCEX_rec>  tblCEX;
typedef ds::shared_ptr<tblCEX>   tblCEX_ptr;
//***********************************************************************
//******    tblHLD
//***********************************************************************
class tblHLD_map
{
private:
    tblHLD_map();
    tblHLD_map( const tblHLD_map& src );
    tblHLD_map& operator = ( const tblHLD_map& src );
public:
    int            HLDID_;
    STRING_FM      (HLDCODE_,20);
    STRING_FM      (HLDDESCRIPTION_,40);
    ds::cDateTime  HLDDATE_;
};

class tblHLD_data
{
protected:
    static const ds::cFieldDef_   tblHLD_Fields[];
    static const ds::cFieldDefs_  tblHLD_FieldDef;
};

class tblHLD_raw : public tblHLD_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblHLD_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)             {} // empty
    tblHLD_raw * FASTCALL operator->()              { return ( this ); }
    const tblHLD_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetHLDID() const                   { return ( ReadInteger( tblHLD_Fields[0] ) ); }
    bool FASTCALL HLDID_IsNull() const              { return ( IsNull( tblHLD_Fields[0] ) ); }

    ds_string FASTCALL GetHLDCODE() const           { return ( ReadString( tblHLD_Fields[1] ) ); }
    bool FASTCALL HLDCODE_IsNull() const            { return ( IsNull( tblHLD_Fields[1] ) ); }

    ds_string FASTCALL GetHLDDESCRIPTION() const    { return ( ReadString( tblHLD_Fields[2] ) ); }
    bool FASTCALL HLDDESCRIPTION_IsNull() const     { return ( IsNull( tblHLD_Fields[2] ) ); }

    ds::cDateTime FASTCALL GetHLDDATE() const       { return ( ReadDate( tblHLD_Fields[3] ) ); }
    bool FASTCALL HLDDATE_IsNull() const            { return ( IsNull( tblHLD_Fields[3] ) ); }
};

class tblHLD_rec : public tblHLD_data, public ds::cRecordPtr
{
public:
    typedef tblHLD_raw    raw;
public:
    CDFASTCALL tblHLD_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblHLD_rec * FASTCALL operator->()              { return ( this ); }
    const tblHLD_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetHLDID() const                              { return ( ReadInteger( tblHLD_Fields[0] ) ); }
    bool FASTCALL HLDID_IsNull() const                         { return ( IsNull( tblHLD_Fields[0] ) ); }
    void FASTCALL SetHLDID( int value )                        { WriteInteger( tblHLD_Fields[0], value ); }

    ds_string FASTCALL GetHLDCODE() const                      { return ( ReadString( tblHLD_Fields[1] ) ); }
    bool FASTCALL HLDCODE_IsNull() const                       { return ( IsNull( tblHLD_Fields[1] ) ); }
    void FASTCALL SetHLDCODE( const ds_string& value )         { WriteString( tblHLD_Fields[1], value ); }

    ds_string FASTCALL GetHLDDESCRIPTION() const               { return ( ReadString( tblHLD_Fields[2] ) ); }
    bool FASTCALL HLDDESCRIPTION_IsNull() const                { return ( IsNull( tblHLD_Fields[2] ) ); }
    void FASTCALL SetHLDDESCRIPTION( const ds_string& value )  { WriteString( tblHLD_Fields[2], value ); }

    ds::cDateTime FASTCALL GetHLDDATE() const                  { return ( ReadDate( tblHLD_Fields[3] ) ); }
    bool FASTCALL HLDDATE_IsNull() const                       { return ( IsNull( tblHLD_Fields[3] ) ); }
    void FASTCALL SetHLDDATE( const ds::cDateTime& value )     { WriteDate( tblHLD_Fields[3], value ); }
};

typedef ds::cuTable<tblHLD_rec>  tblHLD;
typedef ds::shared_ptr<tblHLD>   tblHLD_ptr;
//***********************************************************************
//******    tblBOM
//***********************************************************************
class tblBOM_map
{
private:
    tblBOM_map();
    tblBOM_map( const tblBOM_map& src );
    tblBOM_map& operator = ( const tblBOM_map& src );
public:
    int            BOMID_;
    STRING_FM      (BOMCODE_,20);
    STRING_FM      (BOMDESCRIPTION_,40);
    double         BOMREFQUANTITY_;
    double         BOMREFQUANTITYB_;
    short          BOMQUANTITYDEP_;
    short          BOMTYPE_;
    int            MCIID_;
    STRING_FM      (CODCODE_,30);
    STRING_FM      (ITMNAME_,60);
    STRING_FM      (DFVCODE1_,20);
    STRING_FM      (DFVCODE2_,20);
    STRING_FM      (DFVCODE3_,20);
    STRING_FM      (DFVCODE4_,20);
    STRING_FM      (DFVCODE5_,20);
    STRING_FM      (DFVCODE6_,20);
    STRING_FM      (DFVCODE7_,20);
    int            TSFID_;
    STRING_FM      (TSFCODE_,20);
    STRING_FM      (TSFDESCRIPTION_,40);
    int            ROTID_;
    STRING_FM      (ROTCODE_,20);
    STRING_FM      (ROTDESCRIPTION_,40);
    int            WRHID_;
    short          BOMISACTIVE_;
    STRING_FM      (WRHCODE_,4);
    STRING_FM      (WRHNAME_,40);
    STRING_FM      (UNISHORTNAMEA_,4);
    STRING_FM      (UNISHORTNAMEB_,4);
    ds::cDateTime  BOMVALSTARTDATE_;
    ds::cDateTime  BOMVALENDDATE_;
    double         BOMDIFFICULTYFACTOR_;
    STRING_FM      (UNINAMEA_,30);
    STRING_FM      (UNINAMEB_,30);
    int            BTGID_;
    STRING_FM      (BTGCODE_,20);
    STRING_FM      (BTGDESCRIPTION_,40);
    int            DFTID_;
    int            DFAID1_;
    int            DFAID2_;
    int            DFAID3_;
    int            DFAID4_;
    int            DFAID5_;
    int            DFAID6_;
    int            DFAID7_;
    int            UNIIDA_;
    int            UNIIDB_;
    short          BOMISRECYCLE_;
};

class tblBOM_data
{
protected:
    static const ds::cFieldDef_   tblBOM_Fields[];
    static const ds::cFieldDefs_  tblBOM_FieldDef;
};

class tblBOM_raw : public tblBOM_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblBOM_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                {} // empty
    tblBOM_raw * FASTCALL operator->()                 { return ( this ); }
    const tblBOM_raw * FASTCALL operator->() const     { return ( this ); }

    int FASTCALL GetBOMID() const                      { return ( ReadInteger( tblBOM_Fields[0] ) ); }
    bool FASTCALL BOMID_IsNull() const                 { return ( IsNull( tblBOM_Fields[0] ) ); }

    ds_string FASTCALL GetBOMCODE() const              { return ( ReadString( tblBOM_Fields[1] ) ); }
    bool FASTCALL BOMCODE_IsNull() const               { return ( IsNull( tblBOM_Fields[1] ) ); }

    ds_string FASTCALL GetBOMDESCRIPTION() const       { return ( ReadString( tblBOM_Fields[2] ) ); }
    bool FASTCALL BOMDESCRIPTION_IsNull() const        { return ( IsNull( tblBOM_Fields[2] ) ); }

    double FASTCALL GetBOMREFQUANTITY() const          { return ( ReadFloat( tblBOM_Fields[3] ) ); }
    bool FASTCALL BOMREFQUANTITY_IsNull() const        { return ( IsNull( tblBOM_Fields[3] ) ); }

    double FASTCALL GetBOMREFQUANTITYB() const         { return ( ReadFloat( tblBOM_Fields[4] ) ); }
    bool FASTCALL BOMREFQUANTITYB_IsNull() const       { return ( IsNull( tblBOM_Fields[4] ) ); }

    short FASTCALL GetBOMQUANTITYDEP() const           { return ( ReadShort( tblBOM_Fields[5] ) ); }
    bool FASTCALL BOMQUANTITYDEP_IsNull() const        { return ( IsNull( tblBOM_Fields[5] ) ); }

    short FASTCALL GetBOMTYPE() const                  { return ( ReadShort( tblBOM_Fields[6] ) ); }
    bool FASTCALL BOMTYPE_IsNull() const               { return ( IsNull( tblBOM_Fields[6] ) ); }

    int FASTCALL GetMCIID() const                      { return ( ReadInteger( tblBOM_Fields[7] ) ); }
    bool FASTCALL MCIID_IsNull() const                 { return ( IsNull( tblBOM_Fields[7] ) ); }

    ds_string FASTCALL GetCODCODE() const              { return ( ReadString( tblBOM_Fields[8] ) ); }
    bool FASTCALL CODCODE_IsNull() const               { return ( IsNull( tblBOM_Fields[8] ) ); }

    ds_string FASTCALL GetITMNAME() const              { return ( ReadString( tblBOM_Fields[9] ) ); }
    bool FASTCALL ITMNAME_IsNull() const               { return ( IsNull( tblBOM_Fields[9] ) ); }

    ds_string FASTCALL GetDFVCODE1() const             { return ( ReadString( tblBOM_Fields[10] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const              { return ( IsNull( tblBOM_Fields[10] ) ); }

    ds_string FASTCALL GetDFVCODE2() const             { return ( ReadString( tblBOM_Fields[11] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const              { return ( IsNull( tblBOM_Fields[11] ) ); }

    ds_string FASTCALL GetDFVCODE3() const             { return ( ReadString( tblBOM_Fields[12] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const              { return ( IsNull( tblBOM_Fields[12] ) ); }

    ds_string FASTCALL GetDFVCODE4() const             { return ( ReadString( tblBOM_Fields[13] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const              { return ( IsNull( tblBOM_Fields[13] ) ); }

    ds_string FASTCALL GetDFVCODE5() const             { return ( ReadString( tblBOM_Fields[14] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const              { return ( IsNull( tblBOM_Fields[14] ) ); }

    ds_string FASTCALL GetDFVCODE6() const             { return ( ReadString( tblBOM_Fields[15] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const              { return ( IsNull( tblBOM_Fields[15] ) ); }

    ds_string FASTCALL GetDFVCODE7() const             { return ( ReadString( tblBOM_Fields[16] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const              { return ( IsNull( tblBOM_Fields[16] ) ); }

    int FASTCALL GetTSFID() const                      { return ( ReadInteger( tblBOM_Fields[17] ) ); }
    bool FASTCALL TSFID_IsNull() const                 { return ( IsNull( tblBOM_Fields[17] ) ); }

    ds_string FASTCALL GetTSFCODE() const              { return ( ReadString( tblBOM_Fields[18] ) ); }
    bool FASTCALL TSFCODE_IsNull() const               { return ( IsNull( tblBOM_Fields[18] ) ); }

    ds_string FASTCALL GetTSFDESCRIPTION() const       { return ( ReadString( tblBOM_Fields[19] ) ); }
    bool FASTCALL TSFDESCRIPTION_IsNull() const        { return ( IsNull( tblBOM_Fields[19] ) ); }

    int FASTCALL GetROTID() const                      { return ( ReadInteger( tblBOM_Fields[20] ) ); }
    bool FASTCALL ROTID_IsNull() const                 { return ( IsNull( tblBOM_Fields[20] ) ); }

    ds_string FASTCALL GetROTCODE() const              { return ( ReadString( tblBOM_Fields[21] ) ); }
    bool FASTCALL ROTCODE_IsNull() const               { return ( IsNull( tblBOM_Fields[21] ) ); }

    ds_string FASTCALL GetROTDESCRIPTION() const       { return ( ReadString( tblBOM_Fields[22] ) ); }
    bool FASTCALL ROTDESCRIPTION_IsNull() const        { return ( IsNull( tblBOM_Fields[22] ) ); }

    int FASTCALL GetWRHID() const                      { return ( ReadInteger( tblBOM_Fields[23] ) ); }
    bool FASTCALL WRHID_IsNull() const                 { return ( IsNull( tblBOM_Fields[23] ) ); }

    short FASTCALL GetBOMISACTIVE() const              { return ( ReadShort( tblBOM_Fields[24] ) ); }
    bool FASTCALL BOMISACTIVE_IsNull() const           { return ( IsNull( tblBOM_Fields[24] ) ); }

    ds_string FASTCALL GetWRHCODE() const              { return ( ReadString( tblBOM_Fields[25] ) ); }
    bool FASTCALL WRHCODE_IsNull() const               { return ( IsNull( tblBOM_Fields[25] ) ); }

    ds_string FASTCALL GetWRHNAME() const              { return ( ReadString( tblBOM_Fields[26] ) ); }
    bool FASTCALL WRHNAME_IsNull() const               { return ( IsNull( tblBOM_Fields[26] ) ); }

    ds_string FASTCALL GetUNISHORTNAMEA() const        { return ( ReadString( tblBOM_Fields[27] ) ); }
    bool FASTCALL UNISHORTNAMEA_IsNull() const         { return ( IsNull( tblBOM_Fields[27] ) ); }

    ds_string FASTCALL GetUNISHORTNAMEB() const        { return ( ReadString( tblBOM_Fields[28] ) ); }
    bool FASTCALL UNISHORTNAMEB_IsNull() const         { return ( IsNull( tblBOM_Fields[28] ) ); }

    ds::cDateTime FASTCALL GetBOMVALSTARTDATE() const  { return ( ReadDate( tblBOM_Fields[29] ) ); }
    bool FASTCALL BOMVALSTARTDATE_IsNull() const       { return ( IsNull( tblBOM_Fields[29] ) ); }

    ds::cDateTime FASTCALL GetBOMVALENDDATE() const    { return ( ReadDate( tblBOM_Fields[30] ) ); }
    bool FASTCALL BOMVALENDDATE_IsNull() const         { return ( IsNull( tblBOM_Fields[30] ) ); }

    double FASTCALL GetBOMDIFFICULTYFACTOR() const     { return ( ReadFloat( tblBOM_Fields[31] ) ); }
    bool FASTCALL BOMDIFFICULTYFACTOR_IsNull() const   { return ( IsNull( tblBOM_Fields[31] ) ); }

    ds_string FASTCALL GetUNINAMEA() const             { return ( ReadString( tblBOM_Fields[32] ) ); }
    bool FASTCALL UNINAMEA_IsNull() const              { return ( IsNull( tblBOM_Fields[32] ) ); }

    ds_string FASTCALL GetUNINAMEB() const             { return ( ReadString( tblBOM_Fields[33] ) ); }
    bool FASTCALL UNINAMEB_IsNull() const              { return ( IsNull( tblBOM_Fields[33] ) ); }

    int FASTCALL GetBTGID() const                      { return ( ReadInteger( tblBOM_Fields[34] ) ); }
    bool FASTCALL BTGID_IsNull() const                 { return ( IsNull( tblBOM_Fields[34] ) ); }

    ds_string FASTCALL GetBTGCODE() const              { return ( ReadString( tblBOM_Fields[35] ) ); }
    bool FASTCALL BTGCODE_IsNull() const               { return ( IsNull( tblBOM_Fields[35] ) ); }

    ds_string FASTCALL GetBTGDESCRIPTION() const       { return ( ReadString( tblBOM_Fields[36] ) ); }
    bool FASTCALL BTGDESCRIPTION_IsNull() const        { return ( IsNull( tblBOM_Fields[36] ) ); }

    int FASTCALL GetDFTID() const                      { return ( ReadInteger( tblBOM_Fields[37] ) ); }
    bool FASTCALL DFTID_IsNull() const                 { return ( IsNull( tblBOM_Fields[37] ) ); }

    int FASTCALL GetDFAID1() const                     { return ( ReadInteger( tblBOM_Fields[38] ) ); }
    bool FASTCALL DFAID1_IsNull() const                { return ( IsNull( tblBOM_Fields[38] ) ); }

    int FASTCALL GetDFAID2() const                     { return ( ReadInteger( tblBOM_Fields[39] ) ); }
    bool FASTCALL DFAID2_IsNull() const                { return ( IsNull( tblBOM_Fields[39] ) ); }

    int FASTCALL GetDFAID3() const                     { return ( ReadInteger( tblBOM_Fields[40] ) ); }
    bool FASTCALL DFAID3_IsNull() const                { return ( IsNull( tblBOM_Fields[40] ) ); }

    int FASTCALL GetDFAID4() const                     { return ( ReadInteger( tblBOM_Fields[41] ) ); }
    bool FASTCALL DFAID4_IsNull() const                { return ( IsNull( tblBOM_Fields[41] ) ); }

    int FASTCALL GetDFAID5() const                     { return ( ReadInteger( tblBOM_Fields[42] ) ); }
    bool FASTCALL DFAID5_IsNull() const                { return ( IsNull( tblBOM_Fields[42] ) ); }

    int FASTCALL GetDFAID6() const                     { return ( ReadInteger( tblBOM_Fields[43] ) ); }
    bool FASTCALL DFAID6_IsNull() const                { return ( IsNull( tblBOM_Fields[43] ) ); }

    int FASTCALL GetDFAID7() const                     { return ( ReadInteger( tblBOM_Fields[44] ) ); }
    bool FASTCALL DFAID7_IsNull() const                { return ( IsNull( tblBOM_Fields[44] ) ); }

    int FASTCALL GetUNIIDA() const                     { return ( ReadInteger( tblBOM_Fields[45] ) ); }
    bool FASTCALL UNIIDA_IsNull() const                { return ( IsNull( tblBOM_Fields[45] ) ); }

    int FASTCALL GetUNIIDB() const                     { return ( ReadInteger( tblBOM_Fields[46] ) ); }
    bool FASTCALL UNIIDB_IsNull() const                { return ( IsNull( tblBOM_Fields[46] ) ); }

    short FASTCALL GetBOMISRECYCLE() const             { return ( ReadShort( tblBOM_Fields[47] ) ); }
    bool FASTCALL BOMISRECYCLE_IsNull() const          { return ( IsNull( tblBOM_Fields[47] ) ); }
};

class tblBOM_rec : public tblBOM_data, public ds::cRecordPtr
{
public:
    typedef tblBOM_raw    raw;
public:
    CDFASTCALL tblBOM_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblBOM_rec * FASTCALL operator->()              { return ( this ); }
    const tblBOM_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetBOMID() const                                   { return ( ReadInteger( tblBOM_Fields[0] ) ); }
    bool FASTCALL BOMID_IsNull() const                              { return ( IsNull( tblBOM_Fields[0] ) ); }
    void FASTCALL SetBOMID( int value )                             { WriteInteger( tblBOM_Fields[0], value ); }

    ds_string FASTCALL GetBOMCODE() const                           { return ( ReadString( tblBOM_Fields[1] ) ); }
    bool FASTCALL BOMCODE_IsNull() const                            { return ( IsNull( tblBOM_Fields[1] ) ); }
    void FASTCALL SetBOMCODE( const ds_string& value )              { WriteString( tblBOM_Fields[1], value ); }

    ds_string FASTCALL GetBOMDESCRIPTION() const                    { return ( ReadString( tblBOM_Fields[2] ) ); }
    bool FASTCALL BOMDESCRIPTION_IsNull() const                     { return ( IsNull( tblBOM_Fields[2] ) ); }
    void FASTCALL SetBOMDESCRIPTION( const ds_string& value )       { WriteString( tblBOM_Fields[2], value ); }

    double FASTCALL GetBOMREFQUANTITY() const                       { return ( ReadFloat( tblBOM_Fields[3] ) ); }
    bool FASTCALL BOMREFQUANTITY_IsNull() const                     { return ( IsNull( tblBOM_Fields[3] ) ); }
    void FASTCALL SetBOMREFQUANTITY( double value )                 { WriteFloat( tblBOM_Fields[3], value ); }

    double FASTCALL GetBOMREFQUANTITYB() const                      { return ( ReadFloat( tblBOM_Fields[4] ) ); }
    bool FASTCALL BOMREFQUANTITYB_IsNull() const                    { return ( IsNull( tblBOM_Fields[4] ) ); }
    void FASTCALL SetBOMREFQUANTITYB( double value )                { WriteFloat( tblBOM_Fields[4], value ); }

    short FASTCALL GetBOMQUANTITYDEP() const                        { return ( ReadShort( tblBOM_Fields[5] ) ); }
    bool FASTCALL BOMQUANTITYDEP_IsNull() const                     { return ( IsNull( tblBOM_Fields[5] ) ); }
    void FASTCALL SetBOMQUANTITYDEP( short value )                  { WriteShort( tblBOM_Fields[5], value ); }

    short FASTCALL GetBOMTYPE() const                               { return ( ReadShort( tblBOM_Fields[6] ) ); }
    bool FASTCALL BOMTYPE_IsNull() const                            { return ( IsNull( tblBOM_Fields[6] ) ); }
    void FASTCALL SetBOMTYPE( short value )                         { WriteShort( tblBOM_Fields[6], value ); }

    int FASTCALL GetMCIID() const                                   { return ( ReadInteger( tblBOM_Fields[7] ) ); }
    bool FASTCALL MCIID_IsNull() const                              { return ( IsNull( tblBOM_Fields[7] ) ); }
    void FASTCALL SetMCIID( int value )                             { WriteInteger( tblBOM_Fields[7], value ); }

    ds_string FASTCALL GetCODCODE() const                           { return ( ReadString( tblBOM_Fields[8] ) ); }
    bool FASTCALL CODCODE_IsNull() const                            { return ( IsNull( tblBOM_Fields[8] ) ); }
    void FASTCALL SetCODCODE( const ds_string& value )              { WriteString( tblBOM_Fields[8], value ); }

    ds_string FASTCALL GetITMNAME() const                           { return ( ReadString( tblBOM_Fields[9] ) ); }
    bool FASTCALL ITMNAME_IsNull() const                            { return ( IsNull( tblBOM_Fields[9] ) ); }
    void FASTCALL SetITMNAME( const ds_string& value )              { WriteString( tblBOM_Fields[9], value ); }

    ds_string FASTCALL GetDFVCODE1() const                          { return ( ReadString( tblBOM_Fields[10] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                           { return ( IsNull( tblBOM_Fields[10] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )             { WriteString( tblBOM_Fields[10], value ); }

    ds_string FASTCALL GetDFVCODE2() const                          { return ( ReadString( tblBOM_Fields[11] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                           { return ( IsNull( tblBOM_Fields[11] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )             { WriteString( tblBOM_Fields[11], value ); }

    ds_string FASTCALL GetDFVCODE3() const                          { return ( ReadString( tblBOM_Fields[12] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                           { return ( IsNull( tblBOM_Fields[12] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )             { WriteString( tblBOM_Fields[12], value ); }

    ds_string FASTCALL GetDFVCODE4() const                          { return ( ReadString( tblBOM_Fields[13] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                           { return ( IsNull( tblBOM_Fields[13] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )             { WriteString( tblBOM_Fields[13], value ); }

    ds_string FASTCALL GetDFVCODE5() const                          { return ( ReadString( tblBOM_Fields[14] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                           { return ( IsNull( tblBOM_Fields[14] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )             { WriteString( tblBOM_Fields[14], value ); }

    ds_string FASTCALL GetDFVCODE6() const                          { return ( ReadString( tblBOM_Fields[15] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                           { return ( IsNull( tblBOM_Fields[15] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )             { WriteString( tblBOM_Fields[15], value ); }

    ds_string FASTCALL GetDFVCODE7() const                          { return ( ReadString( tblBOM_Fields[16] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                           { return ( IsNull( tblBOM_Fields[16] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )             { WriteString( tblBOM_Fields[16], value ); }

    int FASTCALL GetTSFID() const                                   { return ( ReadInteger( tblBOM_Fields[17] ) ); }
    bool FASTCALL TSFID_IsNull() const                              { return ( IsNull( tblBOM_Fields[17] ) ); }
    void FASTCALL SetTSFID( int value )                             { WriteInteger( tblBOM_Fields[17], value ); }

    ds_string FASTCALL GetTSFCODE() const                           { return ( ReadString( tblBOM_Fields[18] ) ); }
    bool FASTCALL TSFCODE_IsNull() const                            { return ( IsNull( tblBOM_Fields[18] ) ); }
    void FASTCALL SetTSFCODE( const ds_string& value )              { WriteString( tblBOM_Fields[18], value ); }

    ds_string FASTCALL GetTSFDESCRIPTION() const                    { return ( ReadString( tblBOM_Fields[19] ) ); }
    bool FASTCALL TSFDESCRIPTION_IsNull() const                     { return ( IsNull( tblBOM_Fields[19] ) ); }
    void FASTCALL SetTSFDESCRIPTION( const ds_string& value )       { WriteString( tblBOM_Fields[19], value ); }

    int FASTCALL GetROTID() const                                   { return ( ReadInteger( tblBOM_Fields[20] ) ); }
    bool FASTCALL ROTID_IsNull() const                              { return ( IsNull( tblBOM_Fields[20] ) ); }
    void FASTCALL SetROTID( int value )                             { WriteInteger( tblBOM_Fields[20], value ); }

    ds_string FASTCALL GetROTCODE() const                           { return ( ReadString( tblBOM_Fields[21] ) ); }
    bool FASTCALL ROTCODE_IsNull() const                            { return ( IsNull( tblBOM_Fields[21] ) ); }
    void FASTCALL SetROTCODE( const ds_string& value )              { WriteString( tblBOM_Fields[21], value ); }

    ds_string FASTCALL GetROTDESCRIPTION() const                    { return ( ReadString( tblBOM_Fields[22] ) ); }
    bool FASTCALL ROTDESCRIPTION_IsNull() const                     { return ( IsNull( tblBOM_Fields[22] ) ); }
    void FASTCALL SetROTDESCRIPTION( const ds_string& value )       { WriteString( tblBOM_Fields[22], value ); }

    int FASTCALL GetWRHID() const                                   { return ( ReadInteger( tblBOM_Fields[23] ) ); }
    bool FASTCALL WRHID_IsNull() const                              { return ( IsNull( tblBOM_Fields[23] ) ); }
    void FASTCALL SetWRHID( int value )                             { WriteInteger( tblBOM_Fields[23], value ); }

    short FASTCALL GetBOMISACTIVE() const                           { return ( ReadShort( tblBOM_Fields[24] ) ); }
    bool FASTCALL BOMISACTIVE_IsNull() const                        { return ( IsNull( tblBOM_Fields[24] ) ); }
    void FASTCALL SetBOMISACTIVE( short value )                     { WriteShort( tblBOM_Fields[24], value ); }

    ds_string FASTCALL GetWRHCODE() const                           { return ( ReadString( tblBOM_Fields[25] ) ); }
    bool FASTCALL WRHCODE_IsNull() const                            { return ( IsNull( tblBOM_Fields[25] ) ); }
    void FASTCALL SetWRHCODE( const ds_string& value )              { WriteString( tblBOM_Fields[25], value ); }

    ds_string FASTCALL GetWRHNAME() const                           { return ( ReadString( tblBOM_Fields[26] ) ); }
    bool FASTCALL WRHNAME_IsNull() const                            { return ( IsNull( tblBOM_Fields[26] ) ); }
    void FASTCALL SetWRHNAME( const ds_string& value )              { WriteString( tblBOM_Fields[26], value ); }

    ds_string FASTCALL GetUNISHORTNAMEA() const                     { return ( ReadString( tblBOM_Fields[27] ) ); }
    bool FASTCALL UNISHORTNAMEA_IsNull() const                      { return ( IsNull( tblBOM_Fields[27] ) ); }
    void FASTCALL SetUNISHORTNAMEA( const ds_string& value )        { WriteString( tblBOM_Fields[27], value ); }

    ds_string FASTCALL GetUNISHORTNAMEB() const                     { return ( ReadString( tblBOM_Fields[28] ) ); }
    bool FASTCALL UNISHORTNAMEB_IsNull() const                      { return ( IsNull( tblBOM_Fields[28] ) ); }
    void FASTCALL SetUNISHORTNAMEB( const ds_string& value )        { WriteString( tblBOM_Fields[28], value ); }

    ds::cDateTime FASTCALL GetBOMVALSTARTDATE() const               { return ( ReadDate( tblBOM_Fields[29] ) ); }
    bool FASTCALL BOMVALSTARTDATE_IsNull() const                    { return ( IsNull( tblBOM_Fields[29] ) ); }
    void FASTCALL SetBOMVALSTARTDATE( const ds::cDateTime& value )  { WriteDate( tblBOM_Fields[29], value ); }

    ds::cDateTime FASTCALL GetBOMVALENDDATE() const                 { return ( ReadDate( tblBOM_Fields[30] ) ); }
    bool FASTCALL BOMVALENDDATE_IsNull() const                      { return ( IsNull( tblBOM_Fields[30] ) ); }
    void FASTCALL SetBOMVALENDDATE( const ds::cDateTime& value )    { WriteDate( tblBOM_Fields[30], value ); }

    double FASTCALL GetBOMDIFFICULTYFACTOR() const                  { return ( ReadFloat( tblBOM_Fields[31] ) ); }
    bool FASTCALL BOMDIFFICULTYFACTOR_IsNull() const                { return ( IsNull( tblBOM_Fields[31] ) ); }
    void FASTCALL SetBOMDIFFICULTYFACTOR( double value )            { WriteFloat( tblBOM_Fields[31], value ); }

    ds_string FASTCALL GetUNINAMEA() const                          { return ( ReadString( tblBOM_Fields[32] ) ); }
    bool FASTCALL UNINAMEA_IsNull() const                           { return ( IsNull( tblBOM_Fields[32] ) ); }
    void FASTCALL SetUNINAMEA( const ds_string& value )             { WriteString( tblBOM_Fields[32], value ); }

    ds_string FASTCALL GetUNINAMEB() const                          { return ( ReadString( tblBOM_Fields[33] ) ); }
    bool FASTCALL UNINAMEB_IsNull() const                           { return ( IsNull( tblBOM_Fields[33] ) ); }
    void FASTCALL SetUNINAMEB( const ds_string& value )             { WriteString( tblBOM_Fields[33], value ); }

    int FASTCALL GetBTGID() const                                   { return ( ReadInteger( tblBOM_Fields[34] ) ); }
    bool FASTCALL BTGID_IsNull() const                              { return ( IsNull( tblBOM_Fields[34] ) ); }
    void FASTCALL SetBTGID( int value )                             { WriteInteger( tblBOM_Fields[34], value ); }

    ds_string FASTCALL GetBTGCODE() const                           { return ( ReadString( tblBOM_Fields[35] ) ); }
    bool FASTCALL BTGCODE_IsNull() const                            { return ( IsNull( tblBOM_Fields[35] ) ); }
    void FASTCALL SetBTGCODE( const ds_string& value )              { WriteString( tblBOM_Fields[35], value ); }

    ds_string FASTCALL GetBTGDESCRIPTION() const                    { return ( ReadString( tblBOM_Fields[36] ) ); }
    bool FASTCALL BTGDESCRIPTION_IsNull() const                     { return ( IsNull( tblBOM_Fields[36] ) ); }
    void FASTCALL SetBTGDESCRIPTION( const ds_string& value )       { WriteString( tblBOM_Fields[36], value ); }

    int FASTCALL GetDFTID() const                                   { return ( ReadInteger( tblBOM_Fields[37] ) ); }
    bool FASTCALL DFTID_IsNull() const                              { return ( IsNull( tblBOM_Fields[37] ) ); }
    void FASTCALL SetDFTID( int value )                             { WriteInteger( tblBOM_Fields[37], value ); }

    int FASTCALL GetDFAID1() const                                  { return ( ReadInteger( tblBOM_Fields[38] ) ); }
    bool FASTCALL DFAID1_IsNull() const                             { return ( IsNull( tblBOM_Fields[38] ) ); }
    void FASTCALL SetDFAID1( int value )                            { WriteInteger( tblBOM_Fields[38], value ); }

    int FASTCALL GetDFAID2() const                                  { return ( ReadInteger( tblBOM_Fields[39] ) ); }
    bool FASTCALL DFAID2_IsNull() const                             { return ( IsNull( tblBOM_Fields[39] ) ); }
    void FASTCALL SetDFAID2( int value )                            { WriteInteger( tblBOM_Fields[39], value ); }

    int FASTCALL GetDFAID3() const                                  { return ( ReadInteger( tblBOM_Fields[40] ) ); }
    bool FASTCALL DFAID3_IsNull() const                             { return ( IsNull( tblBOM_Fields[40] ) ); }
    void FASTCALL SetDFAID3( int value )                            { WriteInteger( tblBOM_Fields[40], value ); }

    int FASTCALL GetDFAID4() const                                  { return ( ReadInteger( tblBOM_Fields[41] ) ); }
    bool FASTCALL DFAID4_IsNull() const                             { return ( IsNull( tblBOM_Fields[41] ) ); }
    void FASTCALL SetDFAID4( int value )                            { WriteInteger( tblBOM_Fields[41], value ); }

    int FASTCALL GetDFAID5() const                                  { return ( ReadInteger( tblBOM_Fields[42] ) ); }
    bool FASTCALL DFAID5_IsNull() const                             { return ( IsNull( tblBOM_Fields[42] ) ); }
    void FASTCALL SetDFAID5( int value )                            { WriteInteger( tblBOM_Fields[42], value ); }

    int FASTCALL GetDFAID6() const                                  { return ( ReadInteger( tblBOM_Fields[43] ) ); }
    bool FASTCALL DFAID6_IsNull() const                             { return ( IsNull( tblBOM_Fields[43] ) ); }
    void FASTCALL SetDFAID6( int value )                            { WriteInteger( tblBOM_Fields[43], value ); }

    int FASTCALL GetDFAID7() const                                  { return ( ReadInteger( tblBOM_Fields[44] ) ); }
    bool FASTCALL DFAID7_IsNull() const                             { return ( IsNull( tblBOM_Fields[44] ) ); }
    void FASTCALL SetDFAID7( int value )                            { WriteInteger( tblBOM_Fields[44], value ); }

    int FASTCALL GetUNIIDA() const                                  { return ( ReadInteger( tblBOM_Fields[45] ) ); }
    bool FASTCALL UNIIDA_IsNull() const                             { return ( IsNull( tblBOM_Fields[45] ) ); }
    void FASTCALL SetUNIIDA( int value )                            { WriteInteger( tblBOM_Fields[45], value ); }

    int FASTCALL GetUNIIDB() const                                  { return ( ReadInteger( tblBOM_Fields[46] ) ); }
    bool FASTCALL UNIIDB_IsNull() const                             { return ( IsNull( tblBOM_Fields[46] ) ); }
    void FASTCALL SetUNIIDB( int value )                            { WriteInteger( tblBOM_Fields[46], value ); }

    short FASTCALL GetBOMISRECYCLE() const                          { return ( ReadShort( tblBOM_Fields[47] ) ); }
    bool FASTCALL BOMISRECYCLE_IsNull() const                       { return ( IsNull( tblBOM_Fields[47] ) ); }
    void FASTCALL SetBOMISRECYCLE( short value )                    { WriteShort( tblBOM_Fields[47], value ); }
};

typedef ds::cuTable<tblBOM_rec>  tblBOM;
typedef ds::shared_ptr<tblBOM>   tblBOM_ptr;
//***********************************************************************
//******    tblBMA
//***********************************************************************
class tblBMA_map
{
private:
    tblBMA_map();
    tblBMA_map( const tblBMA_map& src );
    tblBMA_map& operator = ( const tblBMA_map& src );
public:
    int        BMAID_;
    int        BOMID_;
    double     BMAQUANTITYA_;
    double     BMAQUANTITYB_;
    double     BMALOSS_;
    short      BMALOSSTYPE_;
    STRING_FM  (BMAINSTRUCTIONS_,50);
    short      BMAQUANTIZETYPE_;
    double     BMASIGNIFICANCE_;
    int        MCIID_;
    STRING_FM  (CODCODE_,30);
    STRING_FM  (ITMNAME_,60);
    STRING_FM  (DFVCODE1_,20);
    STRING_FM  (DFVCODE2_,20);
    STRING_FM  (DFVCODE3_,20);
    STRING_FM  (DFVCODE4_,20);
    STRING_FM  (DFVCODE5_,20);
    STRING_FM  (DFVCODE6_,20);
    STRING_FM  (DFVCODE7_,20);
    int        WRHID_;
    STRING_FM  (WRHCODE_,4);
    STRING_FM  (WRHNAME_,40);
    int        ROTID_;
    int        ROAID_;
    STRING_FM  (OPRCODE_,20);
    STRING_FM  (OPRDESCRIPTION_,40);
    int        ROALINENO_;
    short      BMACONSREPTYPE_;
    int        WRHIDCONS_;
    STRING_FM  (WRHCONSCODE_,4);
    STRING_FM  (WRHCONSNAME_,40);
    STRING_FM  (UNISHORTNAMEA_,4);
    STRING_FM  (UNISHORTNAMEB_,4);
    double     BMANETQUANTITYA_;
    double     BMANETQUANTITYB_;
    int        BMACOSTBEHAVIOUR_;
    int        DFTID_;
    int        DFAID1_;
    int        DFAID2_;
    int        DFAID3_;
    int        DFAID4_;
    int        DFAID5_;
    int        DFAID6_;
    int        DFAID7_;
    short      BMADFAID1SLAVE_;
    short      BMADFAID2SLAVE_;
    short      BMADFAID3SLAVE_;
    short      BMADFAID4SLAVE_;
    short      BMADFAID5SLAVE_;
    short      BMADFAID6SLAVE_;
    short      BMADFAID7SLAVE_;
    int        UNIIDA_;
    int        UNIIDB_;
    int        BMALINENO_;
    short      BMAISRECYCLE_;
};

class tblBMA_data
{
protected:
    static const ds::cFieldDef_   tblBMA_Fields[];
    static const ds::cFieldDefs_  tblBMA_FieldDef;
};

class tblBMA_raw : public tblBMA_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblBMA_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)             {} // empty
    tblBMA_raw * FASTCALL operator->()              { return ( this ); }
    const tblBMA_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetBMAID() const                   { return ( ReadInteger( tblBMA_Fields[0] ) ); }
    bool FASTCALL BMAID_IsNull() const              { return ( IsNull( tblBMA_Fields[0] ) ); }

    int FASTCALL GetBOMID() const                   { return ( ReadInteger( tblBMA_Fields[1] ) ); }
    bool FASTCALL BOMID_IsNull() const              { return ( IsNull( tblBMA_Fields[1] ) ); }

    double FASTCALL GetBMAQUANTITYA() const         { return ( ReadFloat( tblBMA_Fields[2] ) ); }
    bool FASTCALL BMAQUANTITYA_IsNull() const       { return ( IsNull( tblBMA_Fields[2] ) ); }

    double FASTCALL GetBMAQUANTITYB() const         { return ( ReadFloat( tblBMA_Fields[3] ) ); }
    bool FASTCALL BMAQUANTITYB_IsNull() const       { return ( IsNull( tblBMA_Fields[3] ) ); }

    double FASTCALL GetBMALOSS() const              { return ( ReadFloat( tblBMA_Fields[4] ) ); }
    bool FASTCALL BMALOSS_IsNull() const            { return ( IsNull( tblBMA_Fields[4] ) ); }

    short FASTCALL GetBMALOSSTYPE() const           { return ( ReadShort( tblBMA_Fields[5] ) ); }
    bool FASTCALL BMALOSSTYPE_IsNull() const        { return ( IsNull( tblBMA_Fields[5] ) ); }

    ds_string FASTCALL GetBMAINSTRUCTIONS() const   { return ( ReadString( tblBMA_Fields[6] ) ); }
    bool FASTCALL BMAINSTRUCTIONS_IsNull() const    { return ( IsNull( tblBMA_Fields[6] ) ); }

    short FASTCALL GetBMAQUANTIZETYPE() const       { return ( ReadShort( tblBMA_Fields[7] ) ); }
    bool FASTCALL BMAQUANTIZETYPE_IsNull() const    { return ( IsNull( tblBMA_Fields[7] ) ); }

    double FASTCALL GetBMASIGNIFICANCE() const      { return ( ReadFloat( tblBMA_Fields[8] ) ); }
    bool FASTCALL BMASIGNIFICANCE_IsNull() const    { return ( IsNull( tblBMA_Fields[8] ) ); }

    int FASTCALL GetMCIID() const                   { return ( ReadInteger( tblBMA_Fields[9] ) ); }
    bool FASTCALL MCIID_IsNull() const              { return ( IsNull( tblBMA_Fields[9] ) ); }

    ds_string FASTCALL GetCODCODE() const           { return ( ReadString( tblBMA_Fields[10] ) ); }
    bool FASTCALL CODCODE_IsNull() const            { return ( IsNull( tblBMA_Fields[10] ) ); }

    ds_string FASTCALL GetITMNAME() const           { return ( ReadString( tblBMA_Fields[11] ) ); }
    bool FASTCALL ITMNAME_IsNull() const            { return ( IsNull( tblBMA_Fields[11] ) ); }

    ds_string FASTCALL GetDFVCODE1() const          { return ( ReadString( tblBMA_Fields[12] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const           { return ( IsNull( tblBMA_Fields[12] ) ); }

    ds_string FASTCALL GetDFVCODE2() const          { return ( ReadString( tblBMA_Fields[13] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const           { return ( IsNull( tblBMA_Fields[13] ) ); }

    ds_string FASTCALL GetDFVCODE3() const          { return ( ReadString( tblBMA_Fields[14] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const           { return ( IsNull( tblBMA_Fields[14] ) ); }

    ds_string FASTCALL GetDFVCODE4() const          { return ( ReadString( tblBMA_Fields[15] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const           { return ( IsNull( tblBMA_Fields[15] ) ); }

    ds_string FASTCALL GetDFVCODE5() const          { return ( ReadString( tblBMA_Fields[16] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const           { return ( IsNull( tblBMA_Fields[16] ) ); }

    ds_string FASTCALL GetDFVCODE6() const          { return ( ReadString( tblBMA_Fields[17] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const           { return ( IsNull( tblBMA_Fields[17] ) ); }

    ds_string FASTCALL GetDFVCODE7() const          { return ( ReadString( tblBMA_Fields[18] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const           { return ( IsNull( tblBMA_Fields[18] ) ); }

    int FASTCALL GetWRHID() const                   { return ( ReadInteger( tblBMA_Fields[19] ) ); }
    bool FASTCALL WRHID_IsNull() const              { return ( IsNull( tblBMA_Fields[19] ) ); }

    ds_string FASTCALL GetWRHCODE() const           { return ( ReadString( tblBMA_Fields[20] ) ); }
    bool FASTCALL WRHCODE_IsNull() const            { return ( IsNull( tblBMA_Fields[20] ) ); }

    ds_string FASTCALL GetWRHNAME() const           { return ( ReadString( tblBMA_Fields[21] ) ); }
    bool FASTCALL WRHNAME_IsNull() const            { return ( IsNull( tblBMA_Fields[21] ) ); }

    int FASTCALL GetROTID() const                   { return ( ReadInteger( tblBMA_Fields[22] ) ); }
    bool FASTCALL ROTID_IsNull() const              { return ( IsNull( tblBMA_Fields[22] ) ); }

    int FASTCALL GetROAID() const                   { return ( ReadInteger( tblBMA_Fields[23] ) ); }
    bool FASTCALL ROAID_IsNull() const              { return ( IsNull( tblBMA_Fields[23] ) ); }

    ds_string FASTCALL GetOPRCODE() const           { return ( ReadString( tblBMA_Fields[24] ) ); }
    bool FASTCALL OPRCODE_IsNull() const            { return ( IsNull( tblBMA_Fields[24] ) ); }

    ds_string FASTCALL GetOPRDESCRIPTION() const    { return ( ReadString( tblBMA_Fields[25] ) ); }
    bool FASTCALL OPRDESCRIPTION_IsNull() const     { return ( IsNull( tblBMA_Fields[25] ) ); }

    int FASTCALL GetROALINENO() const               { return ( ReadInteger( tblBMA_Fields[26] ) ); }
    bool FASTCALL ROALINENO_IsNull() const          { return ( IsNull( tblBMA_Fields[26] ) ); }

    short FASTCALL GetBMACONSREPTYPE() const        { return ( ReadShort( tblBMA_Fields[27] ) ); }
    bool FASTCALL BMACONSREPTYPE_IsNull() const     { return ( IsNull( tblBMA_Fields[27] ) ); }

    int FASTCALL GetWRHIDCONS() const               { return ( ReadInteger( tblBMA_Fields[28] ) ); }
    bool FASTCALL WRHIDCONS_IsNull() const          { return ( IsNull( tblBMA_Fields[28] ) ); }

    ds_string FASTCALL GetWRHCONSCODE() const       { return ( ReadString( tblBMA_Fields[29] ) ); }
    bool FASTCALL WRHCONSCODE_IsNull() const        { return ( IsNull( tblBMA_Fields[29] ) ); }

    ds_string FASTCALL GetWRHCONSNAME() const       { return ( ReadString( tblBMA_Fields[30] ) ); }
    bool FASTCALL WRHCONSNAME_IsNull() const        { return ( IsNull( tblBMA_Fields[30] ) ); }

    ds_string FASTCALL GetUNISHORTNAMEA() const     { return ( ReadString( tblBMA_Fields[31] ) ); }
    bool FASTCALL UNISHORTNAMEA_IsNull() const      { return ( IsNull( tblBMA_Fields[31] ) ); }

    ds_string FASTCALL GetUNISHORTNAMEB() const     { return ( ReadString( tblBMA_Fields[32] ) ); }
    bool FASTCALL UNISHORTNAMEB_IsNull() const      { return ( IsNull( tblBMA_Fields[32] ) ); }

    double FASTCALL GetBMANETQUANTITYA() const      { return ( ReadFloat( tblBMA_Fields[33] ) ); }
    bool FASTCALL BMANETQUANTITYA_IsNull() const    { return ( IsNull( tblBMA_Fields[33] ) ); }

    double FASTCALL GetBMANETQUANTITYB() const      { return ( ReadFloat( tblBMA_Fields[34] ) ); }
    bool FASTCALL BMANETQUANTITYB_IsNull() const    { return ( IsNull( tblBMA_Fields[34] ) ); }

    int FASTCALL GetBMACOSTBEHAVIOUR() const        { return ( ReadInteger( tblBMA_Fields[35] ) ); }
    bool FASTCALL BMACOSTBEHAVIOUR_IsNull() const   { return ( IsNull( tblBMA_Fields[35] ) ); }

    int FASTCALL GetDFTID() const                   { return ( ReadInteger( tblBMA_Fields[36] ) ); }
    bool FASTCALL DFTID_IsNull() const              { return ( IsNull( tblBMA_Fields[36] ) ); }

    int FASTCALL GetDFAID1() const                  { return ( ReadInteger( tblBMA_Fields[37] ) ); }
    bool FASTCALL DFAID1_IsNull() const             { return ( IsNull( tblBMA_Fields[37] ) ); }

    int FASTCALL GetDFAID2() const                  { return ( ReadInteger( tblBMA_Fields[38] ) ); }
    bool FASTCALL DFAID2_IsNull() const             { return ( IsNull( tblBMA_Fields[38] ) ); }

    int FASTCALL GetDFAID3() const                  { return ( ReadInteger( tblBMA_Fields[39] ) ); }
    bool FASTCALL DFAID3_IsNull() const             { return ( IsNull( tblBMA_Fields[39] ) ); }

    int FASTCALL GetDFAID4() const                  { return ( ReadInteger( tblBMA_Fields[40] ) ); }
    bool FASTCALL DFAID4_IsNull() const             { return ( IsNull( tblBMA_Fields[40] ) ); }

    int FASTCALL GetDFAID5() const                  { return ( ReadInteger( tblBMA_Fields[41] ) ); }
    bool FASTCALL DFAID5_IsNull() const             { return ( IsNull( tblBMA_Fields[41] ) ); }

    int FASTCALL GetDFAID6() const                  { return ( ReadInteger( tblBMA_Fields[42] ) ); }
    bool FASTCALL DFAID6_IsNull() const             { return ( IsNull( tblBMA_Fields[42] ) ); }

    int FASTCALL GetDFAID7() const                  { return ( ReadInteger( tblBMA_Fields[43] ) ); }
    bool FASTCALL DFAID7_IsNull() const             { return ( IsNull( tblBMA_Fields[43] ) ); }

    short FASTCALL GetBMADFAID1SLAVE() const        { return ( ReadShort( tblBMA_Fields[44] ) ); }
    bool FASTCALL BMADFAID1SLAVE_IsNull() const     { return ( IsNull( tblBMA_Fields[44] ) ); }

    short FASTCALL GetBMADFAID2SLAVE() const        { return ( ReadShort( tblBMA_Fields[45] ) ); }
    bool FASTCALL BMADFAID2SLAVE_IsNull() const     { return ( IsNull( tblBMA_Fields[45] ) ); }

    short FASTCALL GetBMADFAID3SLAVE() const        { return ( ReadShort( tblBMA_Fields[46] ) ); }
    bool FASTCALL BMADFAID3SLAVE_IsNull() const     { return ( IsNull( tblBMA_Fields[46] ) ); }

    short FASTCALL GetBMADFAID4SLAVE() const        { return ( ReadShort( tblBMA_Fields[47] ) ); }
    bool FASTCALL BMADFAID4SLAVE_IsNull() const     { return ( IsNull( tblBMA_Fields[47] ) ); }

    short FASTCALL GetBMADFAID5SLAVE() const        { return ( ReadShort( tblBMA_Fields[48] ) ); }
    bool FASTCALL BMADFAID5SLAVE_IsNull() const     { return ( IsNull( tblBMA_Fields[48] ) ); }

    short FASTCALL GetBMADFAID6SLAVE() const        { return ( ReadShort( tblBMA_Fields[49] ) ); }
    bool FASTCALL BMADFAID6SLAVE_IsNull() const     { return ( IsNull( tblBMA_Fields[49] ) ); }

    short FASTCALL GetBMADFAID7SLAVE() const        { return ( ReadShort( tblBMA_Fields[50] ) ); }
    bool FASTCALL BMADFAID7SLAVE_IsNull() const     { return ( IsNull( tblBMA_Fields[50] ) ); }

    int FASTCALL GetUNIIDA() const                  { return ( ReadInteger( tblBMA_Fields[51] ) ); }
    bool FASTCALL UNIIDA_IsNull() const             { return ( IsNull( tblBMA_Fields[51] ) ); }

    int FASTCALL GetUNIIDB() const                  { return ( ReadInteger( tblBMA_Fields[52] ) ); }
    bool FASTCALL UNIIDB_IsNull() const             { return ( IsNull( tblBMA_Fields[52] ) ); }

    int FASTCALL GetBMALINENO() const               { return ( ReadInteger( tblBMA_Fields[53] ) ); }
    bool FASTCALL BMALINENO_IsNull() const          { return ( IsNull( tblBMA_Fields[53] ) ); }

    short FASTCALL GetBMAISRECYCLE() const          { return ( ReadShort( tblBMA_Fields[54] ) ); }
    bool FASTCALL BMAISRECYCLE_IsNull() const       { return ( IsNull( tblBMA_Fields[54] ) ); }
};

class tblBMA_rec : public tblBMA_data, public ds::cRecordPtr
{
public:
    typedef tblBMA_raw    raw;
public:
    CDFASTCALL tblBMA_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblBMA_rec * FASTCALL operator->()              { return ( this ); }
    const tblBMA_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetBMAID() const                               { return ( ReadInteger( tblBMA_Fields[0] ) ); }
    bool FASTCALL BMAID_IsNull() const                          { return ( IsNull( tblBMA_Fields[0] ) ); }
    void FASTCALL SetBMAID( int value )                         { WriteInteger( tblBMA_Fields[0], value ); }

    int FASTCALL GetBOMID() const                               { return ( ReadInteger( tblBMA_Fields[1] ) ); }
    bool FASTCALL BOMID_IsNull() const                          { return ( IsNull( tblBMA_Fields[1] ) ); }
    void FASTCALL SetBOMID( int value )                         { WriteInteger( tblBMA_Fields[1], value ); }

    double FASTCALL GetBMAQUANTITYA() const                     { return ( ReadFloat( tblBMA_Fields[2] ) ); }
    bool FASTCALL BMAQUANTITYA_IsNull() const                   { return ( IsNull( tblBMA_Fields[2] ) ); }
    void FASTCALL SetBMAQUANTITYA( double value )               { WriteFloat( tblBMA_Fields[2], value ); }

    double FASTCALL GetBMAQUANTITYB() const                     { return ( ReadFloat( tblBMA_Fields[3] ) ); }
    bool FASTCALL BMAQUANTITYB_IsNull() const                   { return ( IsNull( tblBMA_Fields[3] ) ); }
    void FASTCALL SetBMAQUANTITYB( double value )               { WriteFloat( tblBMA_Fields[3], value ); }

    double FASTCALL GetBMALOSS() const                          { return ( ReadFloat( tblBMA_Fields[4] ) ); }
    bool FASTCALL BMALOSS_IsNull() const                        { return ( IsNull( tblBMA_Fields[4] ) ); }
    void FASTCALL SetBMALOSS( double value )                    { WriteFloat( tblBMA_Fields[4], value ); }

    short FASTCALL GetBMALOSSTYPE() const                       { return ( ReadShort( tblBMA_Fields[5] ) ); }
    bool FASTCALL BMALOSSTYPE_IsNull() const                    { return ( IsNull( tblBMA_Fields[5] ) ); }
    void FASTCALL SetBMALOSSTYPE( short value )                 { WriteShort( tblBMA_Fields[5], value ); }

    ds_string FASTCALL GetBMAINSTRUCTIONS() const               { return ( ReadString( tblBMA_Fields[6] ) ); }
    bool FASTCALL BMAINSTRUCTIONS_IsNull() const                { return ( IsNull( tblBMA_Fields[6] ) ); }
    void FASTCALL SetBMAINSTRUCTIONS( const ds_string& value )  { WriteString( tblBMA_Fields[6], value ); }

    short FASTCALL GetBMAQUANTIZETYPE() const                   { return ( ReadShort( tblBMA_Fields[7] ) ); }
    bool FASTCALL BMAQUANTIZETYPE_IsNull() const                { return ( IsNull( tblBMA_Fields[7] ) ); }
    void FASTCALL SetBMAQUANTIZETYPE( short value )             { WriteShort( tblBMA_Fields[7], value ); }

    double FASTCALL GetBMASIGNIFICANCE() const                  { return ( ReadFloat( tblBMA_Fields[8] ) ); }
    bool FASTCALL BMASIGNIFICANCE_IsNull() const                { return ( IsNull( tblBMA_Fields[8] ) ); }
    void FASTCALL SetBMASIGNIFICANCE( double value )            { WriteFloat( tblBMA_Fields[8], value ); }

    int FASTCALL GetMCIID() const                               { return ( ReadInteger( tblBMA_Fields[9] ) ); }
    bool FASTCALL MCIID_IsNull() const                          { return ( IsNull( tblBMA_Fields[9] ) ); }
    void FASTCALL SetMCIID( int value )                         { WriteInteger( tblBMA_Fields[9], value ); }

    ds_string FASTCALL GetCODCODE() const                       { return ( ReadString( tblBMA_Fields[10] ) ); }
    bool FASTCALL CODCODE_IsNull() const                        { return ( IsNull( tblBMA_Fields[10] ) ); }
    void FASTCALL SetCODCODE( const ds_string& value )          { WriteString( tblBMA_Fields[10], value ); }

    ds_string FASTCALL GetITMNAME() const                       { return ( ReadString( tblBMA_Fields[11] ) ); }
    bool FASTCALL ITMNAME_IsNull() const                        { return ( IsNull( tblBMA_Fields[11] ) ); }
    void FASTCALL SetITMNAME( const ds_string& value )          { WriteString( tblBMA_Fields[11], value ); }

    ds_string FASTCALL GetDFVCODE1() const                      { return ( ReadString( tblBMA_Fields[12] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                       { return ( IsNull( tblBMA_Fields[12] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )         { WriteString( tblBMA_Fields[12], value ); }

    ds_string FASTCALL GetDFVCODE2() const                      { return ( ReadString( tblBMA_Fields[13] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                       { return ( IsNull( tblBMA_Fields[13] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )         { WriteString( tblBMA_Fields[13], value ); }

    ds_string FASTCALL GetDFVCODE3() const                      { return ( ReadString( tblBMA_Fields[14] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                       { return ( IsNull( tblBMA_Fields[14] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )         { WriteString( tblBMA_Fields[14], value ); }

    ds_string FASTCALL GetDFVCODE4() const                      { return ( ReadString( tblBMA_Fields[15] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                       { return ( IsNull( tblBMA_Fields[15] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )         { WriteString( tblBMA_Fields[15], value ); }

    ds_string FASTCALL GetDFVCODE5() const                      { return ( ReadString( tblBMA_Fields[16] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                       { return ( IsNull( tblBMA_Fields[16] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )         { WriteString( tblBMA_Fields[16], value ); }

    ds_string FASTCALL GetDFVCODE6() const                      { return ( ReadString( tblBMA_Fields[17] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                       { return ( IsNull( tblBMA_Fields[17] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )         { WriteString( tblBMA_Fields[17], value ); }

    ds_string FASTCALL GetDFVCODE7() const                      { return ( ReadString( tblBMA_Fields[18] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                       { return ( IsNull( tblBMA_Fields[18] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )         { WriteString( tblBMA_Fields[18], value ); }

    int FASTCALL GetWRHID() const                               { return ( ReadInteger( tblBMA_Fields[19] ) ); }
    bool FASTCALL WRHID_IsNull() const                          { return ( IsNull( tblBMA_Fields[19] ) ); }
    void FASTCALL SetWRHID( int value )                         { WriteInteger( tblBMA_Fields[19], value ); }

    ds_string FASTCALL GetWRHCODE() const                       { return ( ReadString( tblBMA_Fields[20] ) ); }
    bool FASTCALL WRHCODE_IsNull() const                        { return ( IsNull( tblBMA_Fields[20] ) ); }
    void FASTCALL SetWRHCODE( const ds_string& value )          { WriteString( tblBMA_Fields[20], value ); }

    ds_string FASTCALL GetWRHNAME() const                       { return ( ReadString( tblBMA_Fields[21] ) ); }
    bool FASTCALL WRHNAME_IsNull() const                        { return ( IsNull( tblBMA_Fields[21] ) ); }
    void FASTCALL SetWRHNAME( const ds_string& value )          { WriteString( tblBMA_Fields[21], value ); }

    int FASTCALL GetROTID() const                               { return ( ReadInteger( tblBMA_Fields[22] ) ); }
    bool FASTCALL ROTID_IsNull() const                          { return ( IsNull( tblBMA_Fields[22] ) ); }
    void FASTCALL SetROTID( int value )                         { WriteInteger( tblBMA_Fields[22], value ); }

    int FASTCALL GetROAID() const                               { return ( ReadInteger( tblBMA_Fields[23] ) ); }
    bool FASTCALL ROAID_IsNull() const                          { return ( IsNull( tblBMA_Fields[23] ) ); }
    void FASTCALL SetROAID( int value )                         { WriteInteger( tblBMA_Fields[23], value ); }

    ds_string FASTCALL GetOPRCODE() const                       { return ( ReadString( tblBMA_Fields[24] ) ); }
    bool FASTCALL OPRCODE_IsNull() const                        { return ( IsNull( tblBMA_Fields[24] ) ); }
    void FASTCALL SetOPRCODE( const ds_string& value )          { WriteString( tblBMA_Fields[24], value ); }

    ds_string FASTCALL GetOPRDESCRIPTION() const                { return ( ReadString( tblBMA_Fields[25] ) ); }
    bool FASTCALL OPRDESCRIPTION_IsNull() const                 { return ( IsNull( tblBMA_Fields[25] ) ); }
    void FASTCALL SetOPRDESCRIPTION( const ds_string& value )   { WriteString( tblBMA_Fields[25], value ); }

    int FASTCALL GetROALINENO() const                           { return ( ReadInteger( tblBMA_Fields[26] ) ); }
    bool FASTCALL ROALINENO_IsNull() const                      { return ( IsNull( tblBMA_Fields[26] ) ); }
    void FASTCALL SetROALINENO( int value )                     { WriteInteger( tblBMA_Fields[26], value ); }

    short FASTCALL GetBMACONSREPTYPE() const                    { return ( ReadShort( tblBMA_Fields[27] ) ); }
    bool FASTCALL BMACONSREPTYPE_IsNull() const                 { return ( IsNull( tblBMA_Fields[27] ) ); }
    void FASTCALL SetBMACONSREPTYPE( short value )              { WriteShort( tblBMA_Fields[27], value ); }

    int FASTCALL GetWRHIDCONS() const                           { return ( ReadInteger( tblBMA_Fields[28] ) ); }
    bool FASTCALL WRHIDCONS_IsNull() const                      { return ( IsNull( tblBMA_Fields[28] ) ); }
    void FASTCALL SetWRHIDCONS( int value )                     { WriteInteger( tblBMA_Fields[28], value ); }

    ds_string FASTCALL GetWRHCONSCODE() const                   { return ( ReadString( tblBMA_Fields[29] ) ); }
    bool FASTCALL WRHCONSCODE_IsNull() const                    { return ( IsNull( tblBMA_Fields[29] ) ); }
    void FASTCALL SetWRHCONSCODE( const ds_string& value )      { WriteString( tblBMA_Fields[29], value ); }

    ds_string FASTCALL GetWRHCONSNAME() const                   { return ( ReadString( tblBMA_Fields[30] ) ); }
    bool FASTCALL WRHCONSNAME_IsNull() const                    { return ( IsNull( tblBMA_Fields[30] ) ); }
    void FASTCALL SetWRHCONSNAME( const ds_string& value )      { WriteString( tblBMA_Fields[30], value ); }

    ds_string FASTCALL GetUNISHORTNAMEA() const                 { return ( ReadString( tblBMA_Fields[31] ) ); }
    bool FASTCALL UNISHORTNAMEA_IsNull() const                  { return ( IsNull( tblBMA_Fields[31] ) ); }
    void FASTCALL SetUNISHORTNAMEA( const ds_string& value )    { WriteString( tblBMA_Fields[31], value ); }

    ds_string FASTCALL GetUNISHORTNAMEB() const                 { return ( ReadString( tblBMA_Fields[32] ) ); }
    bool FASTCALL UNISHORTNAMEB_IsNull() const                  { return ( IsNull( tblBMA_Fields[32] ) ); }
    void FASTCALL SetUNISHORTNAMEB( const ds_string& value )    { WriteString( tblBMA_Fields[32], value ); }

    double FASTCALL GetBMANETQUANTITYA() const                  { return ( ReadFloat( tblBMA_Fields[33] ) ); }
    bool FASTCALL BMANETQUANTITYA_IsNull() const                { return ( IsNull( tblBMA_Fields[33] ) ); }
    void FASTCALL SetBMANETQUANTITYA( double value )            { WriteFloat( tblBMA_Fields[33], value ); }

    double FASTCALL GetBMANETQUANTITYB() const                  { return ( ReadFloat( tblBMA_Fields[34] ) ); }
    bool FASTCALL BMANETQUANTITYB_IsNull() const                { return ( IsNull( tblBMA_Fields[34] ) ); }
    void FASTCALL SetBMANETQUANTITYB( double value )            { WriteFloat( tblBMA_Fields[34], value ); }

    int FASTCALL GetBMACOSTBEHAVIOUR() const                    { return ( ReadInteger( tblBMA_Fields[35] ) ); }
    bool FASTCALL BMACOSTBEHAVIOUR_IsNull() const               { return ( IsNull( tblBMA_Fields[35] ) ); }
    void FASTCALL SetBMACOSTBEHAVIOUR( int value )              { WriteInteger( tblBMA_Fields[35], value ); }

    int FASTCALL GetDFTID() const                               { return ( ReadInteger( tblBMA_Fields[36] ) ); }
    bool FASTCALL DFTID_IsNull() const                          { return ( IsNull( tblBMA_Fields[36] ) ); }
    void FASTCALL SetDFTID( int value )                         { WriteInteger( tblBMA_Fields[36], value ); }

    int FASTCALL GetDFAID1() const                              { return ( ReadInteger( tblBMA_Fields[37] ) ); }
    bool FASTCALL DFAID1_IsNull() const                         { return ( IsNull( tblBMA_Fields[37] ) ); }
    void FASTCALL SetDFAID1( int value )                        { WriteInteger( tblBMA_Fields[37], value ); }

    int FASTCALL GetDFAID2() const                              { return ( ReadInteger( tblBMA_Fields[38] ) ); }
    bool FASTCALL DFAID2_IsNull() const                         { return ( IsNull( tblBMA_Fields[38] ) ); }
    void FASTCALL SetDFAID2( int value )                        { WriteInteger( tblBMA_Fields[38], value ); }

    int FASTCALL GetDFAID3() const                              { return ( ReadInteger( tblBMA_Fields[39] ) ); }
    bool FASTCALL DFAID3_IsNull() const                         { return ( IsNull( tblBMA_Fields[39] ) ); }
    void FASTCALL SetDFAID3( int value )                        { WriteInteger( tblBMA_Fields[39], value ); }

    int FASTCALL GetDFAID4() const                              { return ( ReadInteger( tblBMA_Fields[40] ) ); }
    bool FASTCALL DFAID4_IsNull() const                         { return ( IsNull( tblBMA_Fields[40] ) ); }
    void FASTCALL SetDFAID4( int value )                        { WriteInteger( tblBMA_Fields[40], value ); }

    int FASTCALL GetDFAID5() const                              { return ( ReadInteger( tblBMA_Fields[41] ) ); }
    bool FASTCALL DFAID5_IsNull() const                         { return ( IsNull( tblBMA_Fields[41] ) ); }
    void FASTCALL SetDFAID5( int value )                        { WriteInteger( tblBMA_Fields[41], value ); }

    int FASTCALL GetDFAID6() const                              { return ( ReadInteger( tblBMA_Fields[42] ) ); }
    bool FASTCALL DFAID6_IsNull() const                         { return ( IsNull( tblBMA_Fields[42] ) ); }
    void FASTCALL SetDFAID6( int value )                        { WriteInteger( tblBMA_Fields[42], value ); }

    int FASTCALL GetDFAID7() const                              { return ( ReadInteger( tblBMA_Fields[43] ) ); }
    bool FASTCALL DFAID7_IsNull() const                         { return ( IsNull( tblBMA_Fields[43] ) ); }
    void FASTCALL SetDFAID7( int value )                        { WriteInteger( tblBMA_Fields[43], value ); }

    short FASTCALL GetBMADFAID1SLAVE() const                    { return ( ReadShort( tblBMA_Fields[44] ) ); }
    bool FASTCALL BMADFAID1SLAVE_IsNull() const                 { return ( IsNull( tblBMA_Fields[44] ) ); }
    void FASTCALL SetBMADFAID1SLAVE( short value )              { WriteShort( tblBMA_Fields[44], value ); }

    short FASTCALL GetBMADFAID2SLAVE() const                    { return ( ReadShort( tblBMA_Fields[45] ) ); }
    bool FASTCALL BMADFAID2SLAVE_IsNull() const                 { return ( IsNull( tblBMA_Fields[45] ) ); }
    void FASTCALL SetBMADFAID2SLAVE( short value )              { WriteShort( tblBMA_Fields[45], value ); }

    short FASTCALL GetBMADFAID3SLAVE() const                    { return ( ReadShort( tblBMA_Fields[46] ) ); }
    bool FASTCALL BMADFAID3SLAVE_IsNull() const                 { return ( IsNull( tblBMA_Fields[46] ) ); }
    void FASTCALL SetBMADFAID3SLAVE( short value )              { WriteShort( tblBMA_Fields[46], value ); }

    short FASTCALL GetBMADFAID4SLAVE() const                    { return ( ReadShort( tblBMA_Fields[47] ) ); }
    bool FASTCALL BMADFAID4SLAVE_IsNull() const                 { return ( IsNull( tblBMA_Fields[47] ) ); }
    void FASTCALL SetBMADFAID4SLAVE( short value )              { WriteShort( tblBMA_Fields[47], value ); }

    short FASTCALL GetBMADFAID5SLAVE() const                    { return ( ReadShort( tblBMA_Fields[48] ) ); }
    bool FASTCALL BMADFAID5SLAVE_IsNull() const                 { return ( IsNull( tblBMA_Fields[48] ) ); }
    void FASTCALL SetBMADFAID5SLAVE( short value )              { WriteShort( tblBMA_Fields[48], value ); }

    short FASTCALL GetBMADFAID6SLAVE() const                    { return ( ReadShort( tblBMA_Fields[49] ) ); }
    bool FASTCALL BMADFAID6SLAVE_IsNull() const                 { return ( IsNull( tblBMA_Fields[49] ) ); }
    void FASTCALL SetBMADFAID6SLAVE( short value )              { WriteShort( tblBMA_Fields[49], value ); }

    short FASTCALL GetBMADFAID7SLAVE() const                    { return ( ReadShort( tblBMA_Fields[50] ) ); }
    bool FASTCALL BMADFAID7SLAVE_IsNull() const                 { return ( IsNull( tblBMA_Fields[50] ) ); }
    void FASTCALL SetBMADFAID7SLAVE( short value )              { WriteShort( tblBMA_Fields[50], value ); }

    int FASTCALL GetUNIIDA() const                              { return ( ReadInteger( tblBMA_Fields[51] ) ); }
    bool FASTCALL UNIIDA_IsNull() const                         { return ( IsNull( tblBMA_Fields[51] ) ); }
    void FASTCALL SetUNIIDA( int value )                        { WriteInteger( tblBMA_Fields[51], value ); }

    int FASTCALL GetUNIIDB() const                              { return ( ReadInteger( tblBMA_Fields[52] ) ); }
    bool FASTCALL UNIIDB_IsNull() const                         { return ( IsNull( tblBMA_Fields[52] ) ); }
    void FASTCALL SetUNIIDB( int value )                        { WriteInteger( tblBMA_Fields[52], value ); }

    int FASTCALL GetBMALINENO() const                           { return ( ReadInteger( tblBMA_Fields[53] ) ); }
    bool FASTCALL BMALINENO_IsNull() const                      { return ( IsNull( tblBMA_Fields[53] ) ); }
    void FASTCALL SetBMALINENO( int value )                     { WriteInteger( tblBMA_Fields[53], value ); }

    short FASTCALL GetBMAISRECYCLE() const                      { return ( ReadShort( tblBMA_Fields[54] ) ); }
    bool FASTCALL BMAISRECYCLE_IsNull() const                   { return ( IsNull( tblBMA_Fields[54] ) ); }
    void FASTCALL SetBMAISRECYCLE( short value )                { WriteShort( tblBMA_Fields[54], value ); }
};

typedef ds::cuTable<tblBMA_rec>  tblBMA;
typedef ds::shared_ptr<tblBMA>   tblBMA_ptr;
//***********************************************************************
//******    tblSPN
//***********************************************************************
class tblSPN_map
{
private:
    tblSPN_map();
    tblSPN_map( const tblSPN_map& src );
    tblSPN_map& operator = ( const tblSPN_map& src );
public:
    int        MCIID_;
    short      SPNPRODTYPE_;
    short      SPNCONSREPTYPE_;
    short      SPNPRODREPTYPE_;
    short      SPNTIMEREPTYPE_;
    int        SPNLLC_;
    STRING_FM  (CODCODE_,30);
    STRING_FM  (ITMNAME_,60);
    int        PICID_;
    STRING_FM  (PICCODE_,25);
    STRING_FM  (PICDESCRIPTION_,40);
    STRING_FM  (UNISHORTNAMEA_,4);
    STRING_FM  (UNISHORTNAMEB_,4);
    short      SPNDFVGROUP_;
    int        SPNCOSTBEHAVIOUR_;
    short      SPNORDERTRACKING_;
};

class tblSPN_data
{
protected:
    static const ds::cFieldDef_   tblSPN_Fields[];
    static const ds::cFieldDefs_  tblSPN_FieldDef;
};

class tblSPN_raw : public tblSPN_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblSPN_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)             {} // empty
    tblSPN_raw * FASTCALL operator->()              { return ( this ); }
    const tblSPN_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetMCIID() const                   { return ( ReadInteger( tblSPN_Fields[0] ) ); }
    bool FASTCALL MCIID_IsNull() const              { return ( IsNull( tblSPN_Fields[0] ) ); }

    short FASTCALL GetSPNPRODTYPE() const           { return ( ReadShort( tblSPN_Fields[1] ) ); }
    bool FASTCALL SPNPRODTYPE_IsNull() const        { return ( IsNull( tblSPN_Fields[1] ) ); }

    short FASTCALL GetSPNCONSREPTYPE() const        { return ( ReadShort( tblSPN_Fields[2] ) ); }
    bool FASTCALL SPNCONSREPTYPE_IsNull() const     { return ( IsNull( tblSPN_Fields[2] ) ); }

    short FASTCALL GetSPNPRODREPTYPE() const        { return ( ReadShort( tblSPN_Fields[3] ) ); }
    bool FASTCALL SPNPRODREPTYPE_IsNull() const     { return ( IsNull( tblSPN_Fields[3] ) ); }

    short FASTCALL GetSPNTIMEREPTYPE() const        { return ( ReadShort( tblSPN_Fields[4] ) ); }
    bool FASTCALL SPNTIMEREPTYPE_IsNull() const     { return ( IsNull( tblSPN_Fields[4] ) ); }

    int FASTCALL GetSPNLLC() const                  { return ( ReadInteger( tblSPN_Fields[5] ) ); }
    bool FASTCALL SPNLLC_IsNull() const             { return ( IsNull( tblSPN_Fields[5] ) ); }

    ds_string FASTCALL GetCODCODE() const           { return ( ReadString( tblSPN_Fields[6] ) ); }
    bool FASTCALL CODCODE_IsNull() const            { return ( IsNull( tblSPN_Fields[6] ) ); }

    ds_string FASTCALL GetITMNAME() const           { return ( ReadString( tblSPN_Fields[7] ) ); }
    bool FASTCALL ITMNAME_IsNull() const            { return ( IsNull( tblSPN_Fields[7] ) ); }

    int FASTCALL GetPICID() const                   { return ( ReadInteger( tblSPN_Fields[8] ) ); }
    bool FASTCALL PICID_IsNull() const              { return ( IsNull( tblSPN_Fields[8] ) ); }

    ds_string FASTCALL GetPICCODE() const           { return ( ReadString( tblSPN_Fields[9] ) ); }
    bool FASTCALL PICCODE_IsNull() const            { return ( IsNull( tblSPN_Fields[9] ) ); }

    ds_string FASTCALL GetPICDESCRIPTION() const    { return ( ReadString( tblSPN_Fields[10] ) ); }
    bool FASTCALL PICDESCRIPTION_IsNull() const     { return ( IsNull( tblSPN_Fields[10] ) ); }

    ds_string FASTCALL GetUNISHORTNAMEA() const     { return ( ReadString( tblSPN_Fields[11] ) ); }
    bool FASTCALL UNISHORTNAMEA_IsNull() const      { return ( IsNull( tblSPN_Fields[11] ) ); }

    ds_string FASTCALL GetUNISHORTNAMEB() const     { return ( ReadString( tblSPN_Fields[12] ) ); }
    bool FASTCALL UNISHORTNAMEB_IsNull() const      { return ( IsNull( tblSPN_Fields[12] ) ); }

    short FASTCALL GetSPNDFVGROUP() const           { return ( ReadShort( tblSPN_Fields[13] ) ); }
    bool FASTCALL SPNDFVGROUP_IsNull() const        { return ( IsNull( tblSPN_Fields[13] ) ); }

    int FASTCALL GetSPNCOSTBEHAVIOUR() const        { return ( ReadInteger( tblSPN_Fields[14] ) ); }
    bool FASTCALL SPNCOSTBEHAVIOUR_IsNull() const   { return ( IsNull( tblSPN_Fields[14] ) ); }

    short FASTCALL GetSPNORDERTRACKING() const      { return ( ReadShort( tblSPN_Fields[15] ) ); }
    bool FASTCALL SPNORDERTRACKING_IsNull() const   { return ( IsNull( tblSPN_Fields[15] ) ); }
};

class tblSPN_rec : public tblSPN_data, public ds::cRecordPtr
{
public:
    typedef tblSPN_raw    raw;
public:
    CDFASTCALL tblSPN_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblSPN_rec * FASTCALL operator->()              { return ( this ); }
    const tblSPN_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetMCIID() const                              { return ( ReadInteger( tblSPN_Fields[0] ) ); }
    bool FASTCALL MCIID_IsNull() const                         { return ( IsNull( tblSPN_Fields[0] ) ); }
    void FASTCALL SetMCIID( int value )                        { WriteInteger( tblSPN_Fields[0], value ); }

    short FASTCALL GetSPNPRODTYPE() const                      { return ( ReadShort( tblSPN_Fields[1] ) ); }
    bool FASTCALL SPNPRODTYPE_IsNull() const                   { return ( IsNull( tblSPN_Fields[1] ) ); }
    void FASTCALL SetSPNPRODTYPE( short value )                { WriteShort( tblSPN_Fields[1], value ); }

    short FASTCALL GetSPNCONSREPTYPE() const                   { return ( ReadShort( tblSPN_Fields[2] ) ); }
    bool FASTCALL SPNCONSREPTYPE_IsNull() const                { return ( IsNull( tblSPN_Fields[2] ) ); }
    void FASTCALL SetSPNCONSREPTYPE( short value )             { WriteShort( tblSPN_Fields[2], value ); }

    short FASTCALL GetSPNPRODREPTYPE() const                   { return ( ReadShort( tblSPN_Fields[3] ) ); }
    bool FASTCALL SPNPRODREPTYPE_IsNull() const                { return ( IsNull( tblSPN_Fields[3] ) ); }
    void FASTCALL SetSPNPRODREPTYPE( short value )             { WriteShort( tblSPN_Fields[3], value ); }

    short FASTCALL GetSPNTIMEREPTYPE() const                   { return ( ReadShort( tblSPN_Fields[4] ) ); }
    bool FASTCALL SPNTIMEREPTYPE_IsNull() const                { return ( IsNull( tblSPN_Fields[4] ) ); }
    void FASTCALL SetSPNTIMEREPTYPE( short value )             { WriteShort( tblSPN_Fields[4], value ); }

    int FASTCALL GetSPNLLC() const                             { return ( ReadInteger( tblSPN_Fields[5] ) ); }
    bool FASTCALL SPNLLC_IsNull() const                        { return ( IsNull( tblSPN_Fields[5] ) ); }
    void FASTCALL SetSPNLLC( int value )                       { WriteInteger( tblSPN_Fields[5], value ); }

    ds_string FASTCALL GetCODCODE() const                      { return ( ReadString( tblSPN_Fields[6] ) ); }
    bool FASTCALL CODCODE_IsNull() const                       { return ( IsNull( tblSPN_Fields[6] ) ); }
    void FASTCALL SetCODCODE( const ds_string& value )         { WriteString( tblSPN_Fields[6], value ); }

    ds_string FASTCALL GetITMNAME() const                      { return ( ReadString( tblSPN_Fields[7] ) ); }
    bool FASTCALL ITMNAME_IsNull() const                       { return ( IsNull( tblSPN_Fields[7] ) ); }
    void FASTCALL SetITMNAME( const ds_string& value )         { WriteString( tblSPN_Fields[7], value ); }

    int FASTCALL GetPICID() const                              { return ( ReadInteger( tblSPN_Fields[8] ) ); }
    bool FASTCALL PICID_IsNull() const                         { return ( IsNull( tblSPN_Fields[8] ) ); }
    void FASTCALL SetPICID( int value )                        { WriteInteger( tblSPN_Fields[8], value ); }

    ds_string FASTCALL GetPICCODE() const                      { return ( ReadString( tblSPN_Fields[9] ) ); }
    bool FASTCALL PICCODE_IsNull() const                       { return ( IsNull( tblSPN_Fields[9] ) ); }
    void FASTCALL SetPICCODE( const ds_string& value )         { WriteString( tblSPN_Fields[9], value ); }

    ds_string FASTCALL GetPICDESCRIPTION() const               { return ( ReadString( tblSPN_Fields[10] ) ); }
    bool FASTCALL PICDESCRIPTION_IsNull() const                { return ( IsNull( tblSPN_Fields[10] ) ); }
    void FASTCALL SetPICDESCRIPTION( const ds_string& value )  { WriteString( tblSPN_Fields[10], value ); }

    ds_string FASTCALL GetUNISHORTNAMEA() const                { return ( ReadString( tblSPN_Fields[11] ) ); }
    bool FASTCALL UNISHORTNAMEA_IsNull() const                 { return ( IsNull( tblSPN_Fields[11] ) ); }
    void FASTCALL SetUNISHORTNAMEA( const ds_string& value )   { WriteString( tblSPN_Fields[11], value ); }

    ds_string FASTCALL GetUNISHORTNAMEB() const                { return ( ReadString( tblSPN_Fields[12] ) ); }
    bool FASTCALL UNISHORTNAMEB_IsNull() const                 { return ( IsNull( tblSPN_Fields[12] ) ); }
    void FASTCALL SetUNISHORTNAMEB( const ds_string& value )   { WriteString( tblSPN_Fields[12], value ); }

    short FASTCALL GetSPNDFVGROUP() const                      { return ( ReadShort( tblSPN_Fields[13] ) ); }
    bool FASTCALL SPNDFVGROUP_IsNull() const                   { return ( IsNull( tblSPN_Fields[13] ) ); }
    void FASTCALL SetSPNDFVGROUP( short value )                { WriteShort( tblSPN_Fields[13], value ); }

    int FASTCALL GetSPNCOSTBEHAVIOUR() const                   { return ( ReadInteger( tblSPN_Fields[14] ) ); }
    bool FASTCALL SPNCOSTBEHAVIOUR_IsNull() const              { return ( IsNull( tblSPN_Fields[14] ) ); }
    void FASTCALL SetSPNCOSTBEHAVIOUR( int value )             { WriteInteger( tblSPN_Fields[14], value ); }

    short FASTCALL GetSPNORDERTRACKING() const                 { return ( ReadShort( tblSPN_Fields[15] ) ); }
    bool FASTCALL SPNORDERTRACKING_IsNull() const              { return ( IsNull( tblSPN_Fields[15] ) ); }
    void FASTCALL SetSPNORDERTRACKING( short value )           { WriteShort( tblSPN_Fields[15], value ); }
};

typedef ds::cuTable<tblSPN_rec>  tblSPN;
typedef ds::shared_ptr<tblSPN>   tblSPN_ptr;
//***********************************************************************
//******    tblAIP
//***********************************************************************
class tblAIP_map
{
private:
    tblAIP_map();
    tblAIP_map( const tblAIP_map& src );
    tblAIP_map& operator = ( const tblAIP_map& src );
public:
    int        MCIID_;
    STRING_FM  (DFVCODE1_,20);
    STRING_FM  (DFVCODE2_,20);
    STRING_FM  (DFVCODE3_,20);
    STRING_FM  (DFVCODE4_,20);
    STRING_FM  (DFVCODE5_,20);
    STRING_FM  (DFVCODE6_,20);
    STRING_FM  (DFVCODE7_,20);
    int        PICID_;
    STRING_FM  (PICCODE_,25);
    STRING_FM  (PICDESCRIPTION_,40);
};

class tblAIP_data
{
protected:
    static const ds::cFieldDef_   tblAIP_Fields[];
    static const ds::cFieldDefs_  tblAIP_FieldDef;
};

class tblAIP_raw : public tblAIP_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblAIP_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)             {} // empty
    tblAIP_raw * FASTCALL operator->()              { return ( this ); }
    const tblAIP_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetMCIID() const                   { return ( ReadInteger( tblAIP_Fields[0] ) ); }
    bool FASTCALL MCIID_IsNull() const              { return ( IsNull( tblAIP_Fields[0] ) ); }

    ds_string FASTCALL GetDFVCODE1() const          { return ( ReadString( tblAIP_Fields[1] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const           { return ( IsNull( tblAIP_Fields[1] ) ); }

    ds_string FASTCALL GetDFVCODE2() const          { return ( ReadString( tblAIP_Fields[2] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const           { return ( IsNull( tblAIP_Fields[2] ) ); }

    ds_string FASTCALL GetDFVCODE3() const          { return ( ReadString( tblAIP_Fields[3] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const           { return ( IsNull( tblAIP_Fields[3] ) ); }

    ds_string FASTCALL GetDFVCODE4() const          { return ( ReadString( tblAIP_Fields[4] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const           { return ( IsNull( tblAIP_Fields[4] ) ); }

    ds_string FASTCALL GetDFVCODE5() const          { return ( ReadString( tblAIP_Fields[5] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const           { return ( IsNull( tblAIP_Fields[5] ) ); }

    ds_string FASTCALL GetDFVCODE6() const          { return ( ReadString( tblAIP_Fields[6] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const           { return ( IsNull( tblAIP_Fields[6] ) ); }

    ds_string FASTCALL GetDFVCODE7() const          { return ( ReadString( tblAIP_Fields[7] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const           { return ( IsNull( tblAIP_Fields[7] ) ); }

    int FASTCALL GetPICID() const                   { return ( ReadInteger( tblAIP_Fields[8] ) ); }
    bool FASTCALL PICID_IsNull() const              { return ( IsNull( tblAIP_Fields[8] ) ); }

    ds_string FASTCALL GetPICCODE() const           { return ( ReadString( tblAIP_Fields[9] ) ); }
    bool FASTCALL PICCODE_IsNull() const            { return ( IsNull( tblAIP_Fields[9] ) ); }

    ds_string FASTCALL GetPICDESCRIPTION() const    { return ( ReadString( tblAIP_Fields[10] ) ); }
    bool FASTCALL PICDESCRIPTION_IsNull() const     { return ( IsNull( tblAIP_Fields[10] ) ); }
};

class tblAIP_rec : public tblAIP_data, public ds::cRecordPtr
{
public:
    typedef tblAIP_raw    raw;
public:
    CDFASTCALL tblAIP_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblAIP_rec * FASTCALL operator->()              { return ( this ); }
    const tblAIP_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetMCIID() const                              { return ( ReadInteger( tblAIP_Fields[0] ) ); }
    bool FASTCALL MCIID_IsNull() const                         { return ( IsNull( tblAIP_Fields[0] ) ); }
    void FASTCALL SetMCIID( int value )                        { WriteInteger( tblAIP_Fields[0], value ); }

    ds_string FASTCALL GetDFVCODE1() const                     { return ( ReadString( tblAIP_Fields[1] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                      { return ( IsNull( tblAIP_Fields[1] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )        { WriteString( tblAIP_Fields[1], value ); }

    ds_string FASTCALL GetDFVCODE2() const                     { return ( ReadString( tblAIP_Fields[2] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                      { return ( IsNull( tblAIP_Fields[2] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )        { WriteString( tblAIP_Fields[2], value ); }

    ds_string FASTCALL GetDFVCODE3() const                     { return ( ReadString( tblAIP_Fields[3] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                      { return ( IsNull( tblAIP_Fields[3] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )        { WriteString( tblAIP_Fields[3], value ); }

    ds_string FASTCALL GetDFVCODE4() const                     { return ( ReadString( tblAIP_Fields[4] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                      { return ( IsNull( tblAIP_Fields[4] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )        { WriteString( tblAIP_Fields[4], value ); }

    ds_string FASTCALL GetDFVCODE5() const                     { return ( ReadString( tblAIP_Fields[5] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                      { return ( IsNull( tblAIP_Fields[5] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )        { WriteString( tblAIP_Fields[5], value ); }

    ds_string FASTCALL GetDFVCODE6() const                     { return ( ReadString( tblAIP_Fields[6] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                      { return ( IsNull( tblAIP_Fields[6] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )        { WriteString( tblAIP_Fields[6], value ); }

    ds_string FASTCALL GetDFVCODE7() const                     { return ( ReadString( tblAIP_Fields[7] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                      { return ( IsNull( tblAIP_Fields[7] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )        { WriteString( tblAIP_Fields[7], value ); }

    int FASTCALL GetPICID() const                              { return ( ReadInteger( tblAIP_Fields[8] ) ); }
    bool FASTCALL PICID_IsNull() const                         { return ( IsNull( tblAIP_Fields[8] ) ); }
    void FASTCALL SetPICID( int value )                        { WriteInteger( tblAIP_Fields[8], value ); }

    ds_string FASTCALL GetPICCODE() const                      { return ( ReadString( tblAIP_Fields[9] ) ); }
    bool FASTCALL PICCODE_IsNull() const                       { return ( IsNull( tblAIP_Fields[9] ) ); }
    void FASTCALL SetPICCODE( const ds_string& value )         { WriteString( tblAIP_Fields[9], value ); }

    ds_string FASTCALL GetPICDESCRIPTION() const               { return ( ReadString( tblAIP_Fields[10] ) ); }
    bool FASTCALL PICDESCRIPTION_IsNull() const                { return ( IsNull( tblAIP_Fields[10] ) ); }
    void FASTCALL SetPICDESCRIPTION( const ds_string& value )  { WriteString( tblAIP_Fields[10], value ); }
};

typedef ds::cuTable<tblAIP_rec>  tblAIP;
typedef ds::shared_ptr<tblAIP>   tblAIP_ptr;
//***********************************************************************
//******    tblPIC
//***********************************************************************
class tblPIC_map
{
private:
    tblPIC_map();
    tblPIC_map( const tblPIC_map& src );
    tblPIC_map& operator = ( const tblPIC_map& src );
public:
    int        PICID_;
    STRING_FM  (PICCODE_,25);
    STRING_FM  (PICDESCRIPTION_,40);
    double     PICQTYSAFETYSTOCK_;
    int        PICLEADTIME_;
    short      PICLOTPOLICY_;
    double     PICLOTQTY_;
};

class tblPIC_data
{
protected:
    static const ds::cFieldDef_   tblPIC_Fields[];
    static const ds::cFieldDefs_  tblPIC_FieldDef;
};

class tblPIC_raw : public tblPIC_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblPIC_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)             {} // empty
    tblPIC_raw * FASTCALL operator->()              { return ( this ); }
    const tblPIC_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetPICID() const                   { return ( ReadInteger( tblPIC_Fields[0] ) ); }
    bool FASTCALL PICID_IsNull() const              { return ( IsNull( tblPIC_Fields[0] ) ); }

    ds_string FASTCALL GetPICCODE() const           { return ( ReadString( tblPIC_Fields[1] ) ); }
    bool FASTCALL PICCODE_IsNull() const            { return ( IsNull( tblPIC_Fields[1] ) ); }

    ds_string FASTCALL GetPICDESCRIPTION() const    { return ( ReadString( tblPIC_Fields[2] ) ); }
    bool FASTCALL PICDESCRIPTION_IsNull() const     { return ( IsNull( tblPIC_Fields[2] ) ); }

    double FASTCALL GetPICQTYSAFETYSTOCK() const    { return ( ReadFloat( tblPIC_Fields[3] ) ); }
    bool FASTCALL PICQTYSAFETYSTOCK_IsNull() const  { return ( IsNull( tblPIC_Fields[3] ) ); }

    int FASTCALL GetPICLEADTIME() const             { return ( ReadInteger( tblPIC_Fields[4] ) ); }
    bool FASTCALL PICLEADTIME_IsNull() const        { return ( IsNull( tblPIC_Fields[4] ) ); }

    short FASTCALL GetPICLOTPOLICY() const          { return ( ReadShort( tblPIC_Fields[5] ) ); }
    bool FASTCALL PICLOTPOLICY_IsNull() const       { return ( IsNull( tblPIC_Fields[5] ) ); }

    double FASTCALL GetPICLOTQTY() const            { return ( ReadFloat( tblPIC_Fields[6] ) ); }
    bool FASTCALL PICLOTQTY_IsNull() const          { return ( IsNull( tblPIC_Fields[6] ) ); }
};

class tblPIC_rec : public tblPIC_data, public ds::cRecordPtr
{
public:
    typedef tblPIC_raw    raw;
public:
    CDFASTCALL tblPIC_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblPIC_rec * FASTCALL operator->()              { return ( this ); }
    const tblPIC_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetPICID() const                              { return ( ReadInteger( tblPIC_Fields[0] ) ); }
    bool FASTCALL PICID_IsNull() const                         { return ( IsNull( tblPIC_Fields[0] ) ); }
    void FASTCALL SetPICID( int value )                        { WriteInteger( tblPIC_Fields[0], value ); }

    ds_string FASTCALL GetPICCODE() const                      { return ( ReadString( tblPIC_Fields[1] ) ); }
    bool FASTCALL PICCODE_IsNull() const                       { return ( IsNull( tblPIC_Fields[1] ) ); }
    void FASTCALL SetPICCODE( const ds_string& value )         { WriteString( tblPIC_Fields[1], value ); }

    ds_string FASTCALL GetPICDESCRIPTION() const               { return ( ReadString( tblPIC_Fields[2] ) ); }
    bool FASTCALL PICDESCRIPTION_IsNull() const                { return ( IsNull( tblPIC_Fields[2] ) ); }
    void FASTCALL SetPICDESCRIPTION( const ds_string& value )  { WriteString( tblPIC_Fields[2], value ); }

    double FASTCALL GetPICQTYSAFETYSTOCK() const               { return ( ReadFloat( tblPIC_Fields[3] ) ); }
    bool FASTCALL PICQTYSAFETYSTOCK_IsNull() const             { return ( IsNull( tblPIC_Fields[3] ) ); }
    void FASTCALL SetPICQTYSAFETYSTOCK( double value )         { WriteFloat( tblPIC_Fields[3], value ); }

    int FASTCALL GetPICLEADTIME() const                        { return ( ReadInteger( tblPIC_Fields[4] ) ); }
    bool FASTCALL PICLEADTIME_IsNull() const                   { return ( IsNull( tblPIC_Fields[4] ) ); }
    void FASTCALL SetPICLEADTIME( int value )                  { WriteInteger( tblPIC_Fields[4], value ); }

    short FASTCALL GetPICLOTPOLICY() const                     { return ( ReadShort( tblPIC_Fields[5] ) ); }
    bool FASTCALL PICLOTPOLICY_IsNull() const                  { return ( IsNull( tblPIC_Fields[5] ) ); }
    void FASTCALL SetPICLOTPOLICY( short value )               { WriteShort( tblPIC_Fields[5], value ); }

    double FASTCALL GetPICLOTQTY() const                       { return ( ReadFloat( tblPIC_Fields[6] ) ); }
    bool FASTCALL PICLOTQTY_IsNull() const                     { return ( IsNull( tblPIC_Fields[6] ) ); }
    void FASTCALL SetPICLOTQTY( double value )                 { WriteFloat( tblPIC_Fields[6], value ); }
};

typedef ds::cuTable<tblPIC_rec>  tblPIC;
typedef ds::shared_ptr<tblPIC>   tblPIC_ptr;
//***********************************************************************
//******    tblPRN
//***********************************************************************
class tblPRN_map
{
private:
    tblPRN_map();
    tblPRN_map( const tblPRN_map& src );
    tblPRN_map& operator = ( const tblPRN_map& src );
public:
    int            PRNID_;
    STRING_FM      (PRNCODE_,30);
    int            MCIID_;
    STRING_FM      (CODCODE_,30);
    STRING_FM      (ITMNAME_,60);
    STRING_FM      (DFVCODE1_,20);
    STRING_FM      (DFVCODE2_,20);
    STRING_FM      (DFVCODE3_,20);
    STRING_FM      (DFVCODE4_,20);
    STRING_FM      (DFVCODE5_,20);
    STRING_FM      (DFVCODE6_,20);
    STRING_FM      (DFVCODE7_,20);
    double         PRNTOTQUANTITY_;
    double         PRNTOTQUANTITYB_;
    double         PRNREMQUANTITY_;
    double         PRNREMQUANTITYB_;
    ds::cDateTime  PRNEARLDELIVDATE_;
    ds::cDateTime  PRNLATEDELIVDATE_;
    short          PRNPRIORITY_;
    int            BOMID_;
    STRING_FM      (BOMCODE_,20);
    STRING_FM      (BOMDESCRIPTION_,40);
    STRING_FM      (BTGCODE_,20);
    STRING_FM      (BTGDESCRIPTION_,40);
    int            WRHID_;
    STRING_FM      (PRNDESCRIPTION_,40);
    STRING_FM      (WRHCODE_,4);
    STRING_FM      (WRHNAME_,40);
    short          PRNSTATUS_;
    double         MRPQUANTITYA_;
    double         MRPQUANTITYB_;
    double         MPSQUANTITYA_;
    double         MPSQUANTITYB_;
    STRING_FM      (UNISHORTNAMEA_,4);
    STRING_FM      (UNISHORTNAMEB_,4);
    int            UNIIDA_;
    int            UNIIDB_;
    double         PRNSTARTWEEK_;
    double         PRNENDWEEK_;
    STRING_FM      (PRNCOMMENT_,255);
};

class tblPRN_data
{
protected:
    static const ds::cFieldDef_   tblPRN_Fields[];
    static const ds::cFieldDefs_  tblPRN_FieldDef;
};

class tblPRN_raw : public tblPRN_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblPRN_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                 {} // empty
    tblPRN_raw * FASTCALL operator->()                  { return ( this ); }
    const tblPRN_raw * FASTCALL operator->() const      { return ( this ); }

    int FASTCALL GetPRNID() const                       { return ( ReadInteger( tblPRN_Fields[0] ) ); }
    bool FASTCALL PRNID_IsNull() const                  { return ( IsNull( tblPRN_Fields[0] ) ); }

    ds_string FASTCALL GetPRNCODE() const               { return ( ReadString( tblPRN_Fields[1] ) ); }
    bool FASTCALL PRNCODE_IsNull() const                { return ( IsNull( tblPRN_Fields[1] ) ); }

    int FASTCALL GetMCIID() const                       { return ( ReadInteger( tblPRN_Fields[2] ) ); }
    bool FASTCALL MCIID_IsNull() const                  { return ( IsNull( tblPRN_Fields[2] ) ); }

    ds_string FASTCALL GetCODCODE() const               { return ( ReadString( tblPRN_Fields[3] ) ); }
    bool FASTCALL CODCODE_IsNull() const                { return ( IsNull( tblPRN_Fields[3] ) ); }

    ds_string FASTCALL GetITMNAME() const               { return ( ReadString( tblPRN_Fields[4] ) ); }
    bool FASTCALL ITMNAME_IsNull() const                { return ( IsNull( tblPRN_Fields[4] ) ); }

    ds_string FASTCALL GetDFVCODE1() const              { return ( ReadString( tblPRN_Fields[5] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const               { return ( IsNull( tblPRN_Fields[5] ) ); }

    ds_string FASTCALL GetDFVCODE2() const              { return ( ReadString( tblPRN_Fields[6] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const               { return ( IsNull( tblPRN_Fields[6] ) ); }

    ds_string FASTCALL GetDFVCODE3() const              { return ( ReadString( tblPRN_Fields[7] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const               { return ( IsNull( tblPRN_Fields[7] ) ); }

    ds_string FASTCALL GetDFVCODE4() const              { return ( ReadString( tblPRN_Fields[8] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const               { return ( IsNull( tblPRN_Fields[8] ) ); }

    ds_string FASTCALL GetDFVCODE5() const              { return ( ReadString( tblPRN_Fields[9] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const               { return ( IsNull( tblPRN_Fields[9] ) ); }

    ds_string FASTCALL GetDFVCODE6() const              { return ( ReadString( tblPRN_Fields[10] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const               { return ( IsNull( tblPRN_Fields[10] ) ); }

    ds_string FASTCALL GetDFVCODE7() const              { return ( ReadString( tblPRN_Fields[11] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const               { return ( IsNull( tblPRN_Fields[11] ) ); }

    double FASTCALL GetPRNTOTQUANTITY() const           { return ( ReadFloat( tblPRN_Fields[12] ) ); }
    bool FASTCALL PRNTOTQUANTITY_IsNull() const         { return ( IsNull( tblPRN_Fields[12] ) ); }

    double FASTCALL GetPRNTOTQUANTITYB() const          { return ( ReadFloat( tblPRN_Fields[13] ) ); }
    bool FASTCALL PRNTOTQUANTITYB_IsNull() const        { return ( IsNull( tblPRN_Fields[13] ) ); }

    double FASTCALL GetPRNREMQUANTITY() const           { return ( ReadFloat( tblPRN_Fields[14] ) ); }
    bool FASTCALL PRNREMQUANTITY_IsNull() const         { return ( IsNull( tblPRN_Fields[14] ) ); }

    double FASTCALL GetPRNREMQUANTITYB() const          { return ( ReadFloat( tblPRN_Fields[15] ) ); }
    bool FASTCALL PRNREMQUANTITYB_IsNull() const        { return ( IsNull( tblPRN_Fields[15] ) ); }

    ds::cDateTime FASTCALL GetPRNEARLDELIVDATE() const  { return ( ReadDate( tblPRN_Fields[16] ) ); }
    bool FASTCALL PRNEARLDELIVDATE_IsNull() const       { return ( IsNull( tblPRN_Fields[16] ) ); }

    ds::cDateTime FASTCALL GetPRNLATEDELIVDATE() const  { return ( ReadDate( tblPRN_Fields[17] ) ); }
    bool FASTCALL PRNLATEDELIVDATE_IsNull() const       { return ( IsNull( tblPRN_Fields[17] ) ); }

    short FASTCALL GetPRNPRIORITY() const               { return ( ReadShort( tblPRN_Fields[18] ) ); }
    bool FASTCALL PRNPRIORITY_IsNull() const            { return ( IsNull( tblPRN_Fields[18] ) ); }

    int FASTCALL GetBOMID() const                       { return ( ReadInteger( tblPRN_Fields[19] ) ); }
    bool FASTCALL BOMID_IsNull() const                  { return ( IsNull( tblPRN_Fields[19] ) ); }

    ds_string FASTCALL GetBOMCODE() const               { return ( ReadString( tblPRN_Fields[20] ) ); }
    bool FASTCALL BOMCODE_IsNull() const                { return ( IsNull( tblPRN_Fields[20] ) ); }

    ds_string FASTCALL GetBOMDESCRIPTION() const        { return ( ReadString( tblPRN_Fields[21] ) ); }
    bool FASTCALL BOMDESCRIPTION_IsNull() const         { return ( IsNull( tblPRN_Fields[21] ) ); }

    ds_string FASTCALL GetBTGCODE() const               { return ( ReadString( tblPRN_Fields[22] ) ); }
    bool FASTCALL BTGCODE_IsNull() const                { return ( IsNull( tblPRN_Fields[22] ) ); }

    ds_string FASTCALL GetBTGDESCRIPTION() const        { return ( ReadString( tblPRN_Fields[23] ) ); }
    bool FASTCALL BTGDESCRIPTION_IsNull() const         { return ( IsNull( tblPRN_Fields[23] ) ); }

    int FASTCALL GetWRHID() const                       { return ( ReadInteger( tblPRN_Fields[24] ) ); }
    bool FASTCALL WRHID_IsNull() const                  { return ( IsNull( tblPRN_Fields[24] ) ); }

    ds_string FASTCALL GetPRNDESCRIPTION() const        { return ( ReadString( tblPRN_Fields[25] ) ); }
    bool FASTCALL PRNDESCRIPTION_IsNull() const         { return ( IsNull( tblPRN_Fields[25] ) ); }

    ds_string FASTCALL GetWRHCODE() const               { return ( ReadString( tblPRN_Fields[26] ) ); }
    bool FASTCALL WRHCODE_IsNull() const                { return ( IsNull( tblPRN_Fields[26] ) ); }

    ds_string FASTCALL GetWRHNAME() const               { return ( ReadString( tblPRN_Fields[27] ) ); }
    bool FASTCALL WRHNAME_IsNull() const                { return ( IsNull( tblPRN_Fields[27] ) ); }

    short FASTCALL GetPRNSTATUS() const                 { return ( ReadShort( tblPRN_Fields[28] ) ); }
    bool FASTCALL PRNSTATUS_IsNull() const              { return ( IsNull( tblPRN_Fields[28] ) ); }

    double FASTCALL GetMRPQUANTITYA() const             { return ( ReadFloat( tblPRN_Fields[29] ) ); }
    bool FASTCALL MRPQUANTITYA_IsNull() const           { return ( IsNull( tblPRN_Fields[29] ) ); }

    double FASTCALL GetMRPQUANTITYB() const             { return ( ReadFloat( tblPRN_Fields[30] ) ); }
    bool FASTCALL MRPQUANTITYB_IsNull() const           { return ( IsNull( tblPRN_Fields[30] ) ); }

    double FASTCALL GetMPSQUANTITYA() const             { return ( ReadFloat( tblPRN_Fields[31] ) ); }
    bool FASTCALL MPSQUANTITYA_IsNull() const           { return ( IsNull( tblPRN_Fields[31] ) ); }

    double FASTCALL GetMPSQUANTITYB() const             { return ( ReadFloat( tblPRN_Fields[32] ) ); }
    bool FASTCALL MPSQUANTITYB_IsNull() const           { return ( IsNull( tblPRN_Fields[32] ) ); }

    ds_string FASTCALL GetUNISHORTNAMEA() const         { return ( ReadString( tblPRN_Fields[33] ) ); }
    bool FASTCALL UNISHORTNAMEA_IsNull() const          { return ( IsNull( tblPRN_Fields[33] ) ); }

    ds_string FASTCALL GetUNISHORTNAMEB() const         { return ( ReadString( tblPRN_Fields[34] ) ); }
    bool FASTCALL UNISHORTNAMEB_IsNull() const          { return ( IsNull( tblPRN_Fields[34] ) ); }

    int FASTCALL GetUNIIDA() const                      { return ( ReadInteger( tblPRN_Fields[35] ) ); }
    bool FASTCALL UNIIDA_IsNull() const                 { return ( IsNull( tblPRN_Fields[35] ) ); }

    int FASTCALL GetUNIIDB() const                      { return ( ReadInteger( tblPRN_Fields[36] ) ); }
    bool FASTCALL UNIIDB_IsNull() const                 { return ( IsNull( tblPRN_Fields[36] ) ); }

    double FASTCALL GetPRNSTARTWEEK() const             { return ( ReadFloat( tblPRN_Fields[37] ) ); }
    bool FASTCALL PRNSTARTWEEK_IsNull() const           { return ( IsNull( tblPRN_Fields[37] ) ); }

    double FASTCALL GetPRNENDWEEK() const               { return ( ReadFloat( tblPRN_Fields[38] ) ); }
    bool FASTCALL PRNENDWEEK_IsNull() const             { return ( IsNull( tblPRN_Fields[38] ) ); }

    ds_string FASTCALL GetPRNCOMMENT() const            { return ( ReadString( tblPRN_Fields[39] ) ); }
    bool FASTCALL PRNCOMMENT_IsNull() const             { return ( IsNull( tblPRN_Fields[39] ) ); }
};

class tblPRN_rec : public tblPRN_data, public ds::cRecordPtr
{
public:
    typedef tblPRN_raw    raw;
public:
    CDFASTCALL tblPRN_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblPRN_rec * FASTCALL operator->()              { return ( this ); }
    const tblPRN_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetPRNID() const                                    { return ( ReadInteger( tblPRN_Fields[0] ) ); }
    bool FASTCALL PRNID_IsNull() const                               { return ( IsNull( tblPRN_Fields[0] ) ); }
    void FASTCALL SetPRNID( int value )                              { WriteInteger( tblPRN_Fields[0], value ); }

    ds_string FASTCALL GetPRNCODE() const                            { return ( ReadString( tblPRN_Fields[1] ) ); }
    bool FASTCALL PRNCODE_IsNull() const                             { return ( IsNull( tblPRN_Fields[1] ) ); }
    void FASTCALL SetPRNCODE( const ds_string& value )               { WriteString( tblPRN_Fields[1], value ); }

    int FASTCALL GetMCIID() const                                    { return ( ReadInteger( tblPRN_Fields[2] ) ); }
    bool FASTCALL MCIID_IsNull() const                               { return ( IsNull( tblPRN_Fields[2] ) ); }
    void FASTCALL SetMCIID( int value )                              { WriteInteger( tblPRN_Fields[2], value ); }

    ds_string FASTCALL GetCODCODE() const                            { return ( ReadString( tblPRN_Fields[3] ) ); }
    bool FASTCALL CODCODE_IsNull() const                             { return ( IsNull( tblPRN_Fields[3] ) ); }
    void FASTCALL SetCODCODE( const ds_string& value )               { WriteString( tblPRN_Fields[3], value ); }

    ds_string FASTCALL GetITMNAME() const                            { return ( ReadString( tblPRN_Fields[4] ) ); }
    bool FASTCALL ITMNAME_IsNull() const                             { return ( IsNull( tblPRN_Fields[4] ) ); }
    void FASTCALL SetITMNAME( const ds_string& value )               { WriteString( tblPRN_Fields[4], value ); }

    ds_string FASTCALL GetDFVCODE1() const                           { return ( ReadString( tblPRN_Fields[5] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                            { return ( IsNull( tblPRN_Fields[5] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )              { WriteString( tblPRN_Fields[5], value ); }

    ds_string FASTCALL GetDFVCODE2() const                           { return ( ReadString( tblPRN_Fields[6] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                            { return ( IsNull( tblPRN_Fields[6] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )              { WriteString( tblPRN_Fields[6], value ); }

    ds_string FASTCALL GetDFVCODE3() const                           { return ( ReadString( tblPRN_Fields[7] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                            { return ( IsNull( tblPRN_Fields[7] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )              { WriteString( tblPRN_Fields[7], value ); }

    ds_string FASTCALL GetDFVCODE4() const                           { return ( ReadString( tblPRN_Fields[8] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                            { return ( IsNull( tblPRN_Fields[8] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )              { WriteString( tblPRN_Fields[8], value ); }

    ds_string FASTCALL GetDFVCODE5() const                           { return ( ReadString( tblPRN_Fields[9] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                            { return ( IsNull( tblPRN_Fields[9] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )              { WriteString( tblPRN_Fields[9], value ); }

    ds_string FASTCALL GetDFVCODE6() const                           { return ( ReadString( tblPRN_Fields[10] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                            { return ( IsNull( tblPRN_Fields[10] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )              { WriteString( tblPRN_Fields[10], value ); }

    ds_string FASTCALL GetDFVCODE7() const                           { return ( ReadString( tblPRN_Fields[11] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                            { return ( IsNull( tblPRN_Fields[11] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )              { WriteString( tblPRN_Fields[11], value ); }

    double FASTCALL GetPRNTOTQUANTITY() const                        { return ( ReadFloat( tblPRN_Fields[12] ) ); }
    bool FASTCALL PRNTOTQUANTITY_IsNull() const                      { return ( IsNull( tblPRN_Fields[12] ) ); }
    void FASTCALL SetPRNTOTQUANTITY( double value )                  { WriteFloat( tblPRN_Fields[12], value ); }

    double FASTCALL GetPRNTOTQUANTITYB() const                       { return ( ReadFloat( tblPRN_Fields[13] ) ); }
    bool FASTCALL PRNTOTQUANTITYB_IsNull() const                     { return ( IsNull( tblPRN_Fields[13] ) ); }
    void FASTCALL SetPRNTOTQUANTITYB( double value )                 { WriteFloat( tblPRN_Fields[13], value ); }

    double FASTCALL GetPRNREMQUANTITY() const                        { return ( ReadFloat( tblPRN_Fields[14] ) ); }
    bool FASTCALL PRNREMQUANTITY_IsNull() const                      { return ( IsNull( tblPRN_Fields[14] ) ); }
    void FASTCALL SetPRNREMQUANTITY( double value )                  { WriteFloat( tblPRN_Fields[14], value ); }

    double FASTCALL GetPRNREMQUANTITYB() const                       { return ( ReadFloat( tblPRN_Fields[15] ) ); }
    bool FASTCALL PRNREMQUANTITYB_IsNull() const                     { return ( IsNull( tblPRN_Fields[15] ) ); }
    void FASTCALL SetPRNREMQUANTITYB( double value )                 { WriteFloat( tblPRN_Fields[15], value ); }

    ds::cDateTime FASTCALL GetPRNEARLDELIVDATE() const               { return ( ReadDate( tblPRN_Fields[16] ) ); }
    bool FASTCALL PRNEARLDELIVDATE_IsNull() const                    { return ( IsNull( tblPRN_Fields[16] ) ); }
    void FASTCALL SetPRNEARLDELIVDATE( const ds::cDateTime& value )  { WriteDate( tblPRN_Fields[16], value ); }

    ds::cDateTime FASTCALL GetPRNLATEDELIVDATE() const               { return ( ReadDate( tblPRN_Fields[17] ) ); }
    bool FASTCALL PRNLATEDELIVDATE_IsNull() const                    { return ( IsNull( tblPRN_Fields[17] ) ); }
    void FASTCALL SetPRNLATEDELIVDATE( const ds::cDateTime& value )  { WriteDate( tblPRN_Fields[17], value ); }

    short FASTCALL GetPRNPRIORITY() const                            { return ( ReadShort( tblPRN_Fields[18] ) ); }
    bool FASTCALL PRNPRIORITY_IsNull() const                         { return ( IsNull( tblPRN_Fields[18] ) ); }
    void FASTCALL SetPRNPRIORITY( short value )                      { WriteShort( tblPRN_Fields[18], value ); }

    int FASTCALL GetBOMID() const                                    { return ( ReadInteger( tblPRN_Fields[19] ) ); }
    bool FASTCALL BOMID_IsNull() const                               { return ( IsNull( tblPRN_Fields[19] ) ); }
    void FASTCALL SetBOMID( int value )                              { WriteInteger( tblPRN_Fields[19], value ); }

    ds_string FASTCALL GetBOMCODE() const                            { return ( ReadString( tblPRN_Fields[20] ) ); }
    bool FASTCALL BOMCODE_IsNull() const                             { return ( IsNull( tblPRN_Fields[20] ) ); }
    void FASTCALL SetBOMCODE( const ds_string& value )               { WriteString( tblPRN_Fields[20], value ); }

    ds_string FASTCALL GetBOMDESCRIPTION() const                     { return ( ReadString( tblPRN_Fields[21] ) ); }
    bool FASTCALL BOMDESCRIPTION_IsNull() const                      { return ( IsNull( tblPRN_Fields[21] ) ); }
    void FASTCALL SetBOMDESCRIPTION( const ds_string& value )        { WriteString( tblPRN_Fields[21], value ); }

    ds_string FASTCALL GetBTGCODE() const                            { return ( ReadString( tblPRN_Fields[22] ) ); }
    bool FASTCALL BTGCODE_IsNull() const                             { return ( IsNull( tblPRN_Fields[22] ) ); }
    void FASTCALL SetBTGCODE( const ds_string& value )               { WriteString( tblPRN_Fields[22], value ); }

    ds_string FASTCALL GetBTGDESCRIPTION() const                     { return ( ReadString( tblPRN_Fields[23] ) ); }
    bool FASTCALL BTGDESCRIPTION_IsNull() const                      { return ( IsNull( tblPRN_Fields[23] ) ); }
    void FASTCALL SetBTGDESCRIPTION( const ds_string& value )        { WriteString( tblPRN_Fields[23], value ); }

    int FASTCALL GetWRHID() const                                    { return ( ReadInteger( tblPRN_Fields[24] ) ); }
    bool FASTCALL WRHID_IsNull() const                               { return ( IsNull( tblPRN_Fields[24] ) ); }
    void FASTCALL SetWRHID( int value )                              { WriteInteger( tblPRN_Fields[24], value ); }

    ds_string FASTCALL GetPRNDESCRIPTION() const                     { return ( ReadString( tblPRN_Fields[25] ) ); }
    bool FASTCALL PRNDESCRIPTION_IsNull() const                      { return ( IsNull( tblPRN_Fields[25] ) ); }
    void FASTCALL SetPRNDESCRIPTION( const ds_string& value )        { WriteString( tblPRN_Fields[25], value ); }

    ds_string FASTCALL GetWRHCODE() const                            { return ( ReadString( tblPRN_Fields[26] ) ); }
    bool FASTCALL WRHCODE_IsNull() const                             { return ( IsNull( tblPRN_Fields[26] ) ); }
    void FASTCALL SetWRHCODE( const ds_string& value )               { WriteString( tblPRN_Fields[26], value ); }

    ds_string FASTCALL GetWRHNAME() const                            { return ( ReadString( tblPRN_Fields[27] ) ); }
    bool FASTCALL WRHNAME_IsNull() const                             { return ( IsNull( tblPRN_Fields[27] ) ); }
    void FASTCALL SetWRHNAME( const ds_string& value )               { WriteString( tblPRN_Fields[27], value ); }

    short FASTCALL GetPRNSTATUS() const                              { return ( ReadShort( tblPRN_Fields[28] ) ); }
    bool FASTCALL PRNSTATUS_IsNull() const                           { return ( IsNull( tblPRN_Fields[28] ) ); }
    void FASTCALL SetPRNSTATUS( short value )                        { WriteShort( tblPRN_Fields[28], value ); }

    double FASTCALL GetMRPQUANTITYA() const                          { return ( ReadFloat( tblPRN_Fields[29] ) ); }
    bool FASTCALL MRPQUANTITYA_IsNull() const                        { return ( IsNull( tblPRN_Fields[29] ) ); }
    void FASTCALL SetMRPQUANTITYA( double value )                    { WriteFloat( tblPRN_Fields[29], value ); }

    double FASTCALL GetMRPQUANTITYB() const                          { return ( ReadFloat( tblPRN_Fields[30] ) ); }
    bool FASTCALL MRPQUANTITYB_IsNull() const                        { return ( IsNull( tblPRN_Fields[30] ) ); }
    void FASTCALL SetMRPQUANTITYB( double value )                    { WriteFloat( tblPRN_Fields[30], value ); }

    double FASTCALL GetMPSQUANTITYA() const                          { return ( ReadFloat( tblPRN_Fields[31] ) ); }
    bool FASTCALL MPSQUANTITYA_IsNull() const                        { return ( IsNull( tblPRN_Fields[31] ) ); }
    void FASTCALL SetMPSQUANTITYA( double value )                    { WriteFloat( tblPRN_Fields[31], value ); }

    double FASTCALL GetMPSQUANTITYB() const                          { return ( ReadFloat( tblPRN_Fields[32] ) ); }
    bool FASTCALL MPSQUANTITYB_IsNull() const                        { return ( IsNull( tblPRN_Fields[32] ) ); }
    void FASTCALL SetMPSQUANTITYB( double value )                    { WriteFloat( tblPRN_Fields[32], value ); }

    ds_string FASTCALL GetUNISHORTNAMEA() const                      { return ( ReadString( tblPRN_Fields[33] ) ); }
    bool FASTCALL UNISHORTNAMEA_IsNull() const                       { return ( IsNull( tblPRN_Fields[33] ) ); }
    void FASTCALL SetUNISHORTNAMEA( const ds_string& value )         { WriteString( tblPRN_Fields[33], value ); }

    ds_string FASTCALL GetUNISHORTNAMEB() const                      { return ( ReadString( tblPRN_Fields[34] ) ); }
    bool FASTCALL UNISHORTNAMEB_IsNull() const                       { return ( IsNull( tblPRN_Fields[34] ) ); }
    void FASTCALL SetUNISHORTNAMEB( const ds_string& value )         { WriteString( tblPRN_Fields[34], value ); }

    int FASTCALL GetUNIIDA() const                                   { return ( ReadInteger( tblPRN_Fields[35] ) ); }
    bool FASTCALL UNIIDA_IsNull() const                              { return ( IsNull( tblPRN_Fields[35] ) ); }
    void FASTCALL SetUNIIDA( int value )                             { WriteInteger( tblPRN_Fields[35], value ); }

    int FASTCALL GetUNIIDB() const                                   { return ( ReadInteger( tblPRN_Fields[36] ) ); }
    bool FASTCALL UNIIDB_IsNull() const                              { return ( IsNull( tblPRN_Fields[36] ) ); }
    void FASTCALL SetUNIIDB( int value )                             { WriteInteger( tblPRN_Fields[36], value ); }

    double FASTCALL GetPRNSTARTWEEK() const                          { return ( ReadFloat( tblPRN_Fields[37] ) ); }
    bool FASTCALL PRNSTARTWEEK_IsNull() const                        { return ( IsNull( tblPRN_Fields[37] ) ); }
    void FASTCALL SetPRNSTARTWEEK( double value )                    { WriteFloat( tblPRN_Fields[37], value ); }

    double FASTCALL GetPRNENDWEEK() const                            { return ( ReadFloat( tblPRN_Fields[38] ) ); }
    bool FASTCALL PRNENDWEEK_IsNull() const                          { return ( IsNull( tblPRN_Fields[38] ) ); }
    void FASTCALL SetPRNENDWEEK( double value )                      { WriteFloat( tblPRN_Fields[38], value ); }

    ds_string FASTCALL GetPRNCOMMENT() const                         { return ( ReadString( tblPRN_Fields[39] ) ); }
    bool FASTCALL PRNCOMMENT_IsNull() const                          { return ( IsNull( tblPRN_Fields[39] ) ); }
    void FASTCALL SetPRNCOMMENT( const ds_string& value )            { WriteString( tblPRN_Fields[39], value ); }
};

typedef ds::cuTable<tblPRN_rec>  tblPRN;
typedef ds::shared_ptr<tblPRN>   tblPRN_ptr;
//---------------------------------------------------------------------------
#endif
