//---------------------------------------------------------------------------
#ifndef PRN_CUSTOM_TABLES_H
#define PRN_CUSTOM_TABLES_H
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
//******    tblFirstScanDataset
//***********************************************************************
class tblFirstScanDataset_map
{
private:
    tblFirstScanDataset_map();
    tblFirstScanDataset_map( const tblFirstScanDataset_map& src );
    tblFirstScanDataset_map& operator = ( const tblFirstScanDataset_map& src );
public:
    int        MCIID_;
    STRING_FM  (DFVCODE1_,20);
    STRING_FM  (DFVCODE2_,20);
    STRING_FM  (DFVCODE3_,20);
    STRING_FM  (DFVCODE4_,20);
    STRING_FM  (DFVCODE5_,20);
    STRING_FM  (DFVCODE6_,20);
    STRING_FM  (DFVCODE7_,20);
    double     LLC_;
    double     LOTSIZE_;
    double     LEADTIME_;
    double     SAFETYSTOCK_;
    double     LOTPOLICY_;
};

class tblFirstScanDataset_data
{
protected:
    static const ds::cFieldDef_   tblFirstScanDataset_Fields[];
    static const ds::cFieldDefs_  tblFirstScanDataset_FieldDef;
};

class tblFirstScanDataset_raw : public tblFirstScanDataset_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblFirstScanDataset_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                          {} // empty
    tblFirstScanDataset_raw * FASTCALL operator->()              { return ( this ); }
    const tblFirstScanDataset_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetMCIID() const                                { return ( ReadInteger( tblFirstScanDataset_Fields[0] ) ); }
    bool FASTCALL MCIID_IsNull() const                           { return ( IsNull( tblFirstScanDataset_Fields[0] ) ); }

    ds_string FASTCALL GetDFVCODE1() const                       { return ( ReadString( tblFirstScanDataset_Fields[1] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                        { return ( IsNull( tblFirstScanDataset_Fields[1] ) ); }

    ds_string FASTCALL GetDFVCODE2() const                       { return ( ReadString( tblFirstScanDataset_Fields[2] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                        { return ( IsNull( tblFirstScanDataset_Fields[2] ) ); }

    ds_string FASTCALL GetDFVCODE3() const                       { return ( ReadString( tblFirstScanDataset_Fields[3] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                        { return ( IsNull( tblFirstScanDataset_Fields[3] ) ); }

    ds_string FASTCALL GetDFVCODE4() const                       { return ( ReadString( tblFirstScanDataset_Fields[4] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                        { return ( IsNull( tblFirstScanDataset_Fields[4] ) ); }

    ds_string FASTCALL GetDFVCODE5() const                       { return ( ReadString( tblFirstScanDataset_Fields[5] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                        { return ( IsNull( tblFirstScanDataset_Fields[5] ) ); }

    ds_string FASTCALL GetDFVCODE6() const                       { return ( ReadString( tblFirstScanDataset_Fields[6] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                        { return ( IsNull( tblFirstScanDataset_Fields[6] ) ); }

    ds_string FASTCALL GetDFVCODE7() const                       { return ( ReadString( tblFirstScanDataset_Fields[7] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                        { return ( IsNull( tblFirstScanDataset_Fields[7] ) ); }

    double FASTCALL GetLLC() const                               { return ( ReadFloat( tblFirstScanDataset_Fields[8] ) ); }
    bool FASTCALL LLC_IsNull() const                             { return ( IsNull( tblFirstScanDataset_Fields[8] ) ); }

    double FASTCALL GetLOTSIZE() const                           { return ( ReadFloat( tblFirstScanDataset_Fields[9] ) ); }
    bool FASTCALL LOTSIZE_IsNull() const                         { return ( IsNull( tblFirstScanDataset_Fields[9] ) ); }

    double FASTCALL GetLEADTIME() const                          { return ( ReadFloat( tblFirstScanDataset_Fields[10] ) ); }
    bool FASTCALL LEADTIME_IsNull() const                        { return ( IsNull( tblFirstScanDataset_Fields[10] ) ); }

    double FASTCALL GetSAFETYSTOCK() const                       { return ( ReadFloat( tblFirstScanDataset_Fields[11] ) ); }
    bool FASTCALL SAFETYSTOCK_IsNull() const                     { return ( IsNull( tblFirstScanDataset_Fields[11] ) ); }

    double FASTCALL GetLOTPOLICY() const                         { return ( ReadFloat( tblFirstScanDataset_Fields[12] ) ); }
    bool FASTCALL LOTPOLICY_IsNull() const                       { return ( IsNull( tblFirstScanDataset_Fields[12] ) ); }
};

class tblFirstScanDataset_rec : public tblFirstScanDataset_data, public ds::cRecordPtr
{
public:
    typedef tblFirstScanDataset_raw    raw;
public:
    CDFASTCALL tblFirstScanDataset_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                          {} // empty
    tblFirstScanDataset_rec * FASTCALL operator->()              { return ( this ); }
    const tblFirstScanDataset_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetMCIID() const                        { return ( ReadInteger( tblFirstScanDataset_Fields[0] ) ); }
    bool FASTCALL MCIID_IsNull() const                   { return ( IsNull( tblFirstScanDataset_Fields[0] ) ); }
    void FASTCALL SetMCIID( int value )                  { WriteInteger( tblFirstScanDataset_Fields[0], value ); }

    ds_string FASTCALL GetDFVCODE1() const               { return ( ReadString( tblFirstScanDataset_Fields[1] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                { return ( IsNull( tblFirstScanDataset_Fields[1] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )  { WriteString( tblFirstScanDataset_Fields[1], value ); }

    ds_string FASTCALL GetDFVCODE2() const               { return ( ReadString( tblFirstScanDataset_Fields[2] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                { return ( IsNull( tblFirstScanDataset_Fields[2] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )  { WriteString( tblFirstScanDataset_Fields[2], value ); }

    ds_string FASTCALL GetDFVCODE3() const               { return ( ReadString( tblFirstScanDataset_Fields[3] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                { return ( IsNull( tblFirstScanDataset_Fields[3] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )  { WriteString( tblFirstScanDataset_Fields[3], value ); }

    ds_string FASTCALL GetDFVCODE4() const               { return ( ReadString( tblFirstScanDataset_Fields[4] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                { return ( IsNull( tblFirstScanDataset_Fields[4] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )  { WriteString( tblFirstScanDataset_Fields[4], value ); }

    ds_string FASTCALL GetDFVCODE5() const               { return ( ReadString( tblFirstScanDataset_Fields[5] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                { return ( IsNull( tblFirstScanDataset_Fields[5] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )  { WriteString( tblFirstScanDataset_Fields[5], value ); }

    ds_string FASTCALL GetDFVCODE6() const               { return ( ReadString( tblFirstScanDataset_Fields[6] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                { return ( IsNull( tblFirstScanDataset_Fields[6] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )  { WriteString( tblFirstScanDataset_Fields[6], value ); }

    ds_string FASTCALL GetDFVCODE7() const               { return ( ReadString( tblFirstScanDataset_Fields[7] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                { return ( IsNull( tblFirstScanDataset_Fields[7] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )  { WriteString( tblFirstScanDataset_Fields[7], value ); }

    double FASTCALL GetLLC() const                       { return ( ReadFloat( tblFirstScanDataset_Fields[8] ) ); }
    bool FASTCALL LLC_IsNull() const                     { return ( IsNull( tblFirstScanDataset_Fields[8] ) ); }
    void FASTCALL SetLLC( double value )                 { WriteFloat( tblFirstScanDataset_Fields[8], value ); }

    double FASTCALL GetLOTSIZE() const                   { return ( ReadFloat( tblFirstScanDataset_Fields[9] ) ); }
    bool FASTCALL LOTSIZE_IsNull() const                 { return ( IsNull( tblFirstScanDataset_Fields[9] ) ); }
    void FASTCALL SetLOTSIZE( double value )             { WriteFloat( tblFirstScanDataset_Fields[9], value ); }

    double FASTCALL GetLEADTIME() const                  { return ( ReadFloat( tblFirstScanDataset_Fields[10] ) ); }
    bool FASTCALL LEADTIME_IsNull() const                { return ( IsNull( tblFirstScanDataset_Fields[10] ) ); }
    void FASTCALL SetLEADTIME( double value )            { WriteFloat( tblFirstScanDataset_Fields[10], value ); }

    double FASTCALL GetSAFETYSTOCK() const               { return ( ReadFloat( tblFirstScanDataset_Fields[11] ) ); }
    bool FASTCALL SAFETYSTOCK_IsNull() const             { return ( IsNull( tblFirstScanDataset_Fields[11] ) ); }
    void FASTCALL SetSAFETYSTOCK( double value )         { WriteFloat( tblFirstScanDataset_Fields[11], value ); }

    double FASTCALL GetLOTPOLICY() const                 { return ( ReadFloat( tblFirstScanDataset_Fields[12] ) ); }
    bool FASTCALL LOTPOLICY_IsNull() const               { return ( IsNull( tblFirstScanDataset_Fields[12] ) ); }
    void FASTCALL SetLOTPOLICY( double value )           { WriteFloat( tblFirstScanDataset_Fields[12], value ); }
};

typedef ds::cuTable<tblFirstScanDataset_rec>  tblFirstScanDataset;
typedef ds::shared_ptr<tblFirstScanDataset>   tblFirstScanDataset_ptr;
//***********************************************************************
//******    tblHelpDataset
//***********************************************************************
class tblHelpDataset_map
{
private:
    tblHelpDataset_map();
    tblHelpDataset_map( const tblHelpDataset_map& src );
    tblHelpDataset_map& operator = ( const tblHelpDataset_map& src );
public:
    int            ID_;
    int            MCIID_;
    STRING_FM      (DFVCODE1_,20);
    STRING_FM      (DFVCODE2_,20);
    STRING_FM      (DFVCODE3_,20);
    STRING_FM      (DFVCODE4_,20);
    STRING_FM      (DFVCODE5_,20);
    STRING_FM      (DFVCODE6_,20);
    STRING_FM      (DFVCODE7_,20);
    int            WEEK_;
    int            YEAR_;
    double         GROSSREQ_;
    double         SCHEDREQ_;
    double         PROJONHAND_;
    double         NETREQ_;
    double         REQPO_;
    double         RELPO_;
    double         PROJAVBAL_;
    double         EXPECTED_;
    double         TIED_;
    int            DAYS_;
    ds::cDateTime  DATE_;
};

class tblHelpDataset_data
{
protected:
    static const ds::cFieldDef_   tblHelpDataset_Fields[];
    static const ds::cFieldDefs_  tblHelpDataset_FieldDef;
};

class tblHelpDataset_raw : public tblHelpDataset_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblHelpDataset_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                     {} // empty
    tblHelpDataset_raw * FASTCALL operator->()              { return ( this ); }
    const tblHelpDataset_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetID() const                              { return ( ReadInteger( tblHelpDataset_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                         { return ( IsNull( tblHelpDataset_Fields[0] ) ); }

    int FASTCALL GetMCIID() const                           { return ( ReadInteger( tblHelpDataset_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                      { return ( IsNull( tblHelpDataset_Fields[1] ) ); }

    ds_string FASTCALL GetDFVCODE1() const                  { return ( ReadString( tblHelpDataset_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[2] ) ); }

    ds_string FASTCALL GetDFVCODE2() const                  { return ( ReadString( tblHelpDataset_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[3] ) ); }

    ds_string FASTCALL GetDFVCODE3() const                  { return ( ReadString( tblHelpDataset_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[4] ) ); }

    ds_string FASTCALL GetDFVCODE4() const                  { return ( ReadString( tblHelpDataset_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[5] ) ); }

    ds_string FASTCALL GetDFVCODE5() const                  { return ( ReadString( tblHelpDataset_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[6] ) ); }

    ds_string FASTCALL GetDFVCODE6() const                  { return ( ReadString( tblHelpDataset_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[7] ) ); }

    ds_string FASTCALL GetDFVCODE7() const                  { return ( ReadString( tblHelpDataset_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[8] ) ); }

    int FASTCALL GetWEEK() const                            { return ( ReadInteger( tblHelpDataset_Fields[9] ) ); }
    bool FASTCALL WEEK_IsNull() const                       { return ( IsNull( tblHelpDataset_Fields[9] ) ); }

    int FASTCALL GetYEAR() const                            { return ( ReadInteger( tblHelpDataset_Fields[10] ) ); }
    bool FASTCALL YEAR_IsNull() const                       { return ( IsNull( tblHelpDataset_Fields[10] ) ); }

    double FASTCALL GetGROSSREQ() const                     { return ( ReadFloat( tblHelpDataset_Fields[11] ) ); }
    bool FASTCALL GROSSREQ_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[11] ) ); }

    double FASTCALL GetSCHEDREQ() const                     { return ( ReadFloat( tblHelpDataset_Fields[12] ) ); }
    bool FASTCALL SCHEDREQ_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[12] ) ); }

    double FASTCALL GetPROJONHAND() const                   { return ( ReadFloat( tblHelpDataset_Fields[13] ) ); }
    bool FASTCALL PROJONHAND_IsNull() const                 { return ( IsNull( tblHelpDataset_Fields[13] ) ); }

    double FASTCALL GetNETREQ() const                       { return ( ReadFloat( tblHelpDataset_Fields[14] ) ); }
    bool FASTCALL NETREQ_IsNull() const                     { return ( IsNull( tblHelpDataset_Fields[14] ) ); }

    double FASTCALL GetREQPO() const                        { return ( ReadFloat( tblHelpDataset_Fields[15] ) ); }
    bool FASTCALL REQPO_IsNull() const                      { return ( IsNull( tblHelpDataset_Fields[15] ) ); }

    double FASTCALL GetRELPO() const                        { return ( ReadFloat( tblHelpDataset_Fields[16] ) ); }
    bool FASTCALL RELPO_IsNull() const                      { return ( IsNull( tblHelpDataset_Fields[16] ) ); }

    double FASTCALL GetPROJAVBAL() const                    { return ( ReadFloat( tblHelpDataset_Fields[17] ) ); }
    bool FASTCALL PROJAVBAL_IsNull() const                  { return ( IsNull( tblHelpDataset_Fields[17] ) ); }

    double FASTCALL GetEXPECTED() const                     { return ( ReadFloat( tblHelpDataset_Fields[18] ) ); }
    bool FASTCALL EXPECTED_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[18] ) ); }

    double FASTCALL GetTIED() const                         { return ( ReadFloat( tblHelpDataset_Fields[19] ) ); }
    bool FASTCALL TIED_IsNull() const                       { return ( IsNull( tblHelpDataset_Fields[19] ) ); }

    int FASTCALL GetDAYS() const                            { return ( ReadInteger( tblHelpDataset_Fields[20] ) ); }
    bool FASTCALL DAYS_IsNull() const                       { return ( IsNull( tblHelpDataset_Fields[20] ) ); }

    ds::cDateTime FASTCALL GetDATE() const                  { return ( ReadDate( tblHelpDataset_Fields[21] ) ); }
    bool FASTCALL DATE_IsNull() const                       { return ( IsNull( tblHelpDataset_Fields[21] ) ); }
};

class tblHelpDataset_rec : public tblHelpDataset_data, public ds::cRecordPtr
{
public:
    typedef tblHelpDataset_raw    raw;
public:
    CDFASTCALL tblHelpDataset_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                     {} // empty
    tblHelpDataset_rec * FASTCALL operator->()              { return ( this ); }
    const tblHelpDataset_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetID() const                           { return ( ReadInteger( tblHelpDataset_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                      { return ( IsNull( tblHelpDataset_Fields[0] ) ); }
    void FASTCALL SetID( int value )                     { WriteInteger( tblHelpDataset_Fields[0], value ); }

    int FASTCALL GetMCIID() const                        { return ( ReadInteger( tblHelpDataset_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[1] ) ); }
    void FASTCALL SetMCIID( int value )                  { WriteInteger( tblHelpDataset_Fields[1], value ); }

    ds_string FASTCALL GetDFVCODE1() const               { return ( ReadString( tblHelpDataset_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[2] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )  { WriteString( tblHelpDataset_Fields[2], value ); }

    ds_string FASTCALL GetDFVCODE2() const               { return ( ReadString( tblHelpDataset_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[3] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )  { WriteString( tblHelpDataset_Fields[3], value ); }

    ds_string FASTCALL GetDFVCODE3() const               { return ( ReadString( tblHelpDataset_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[4] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )  { WriteString( tblHelpDataset_Fields[4], value ); }

    ds_string FASTCALL GetDFVCODE4() const               { return ( ReadString( tblHelpDataset_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[5] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )  { WriteString( tblHelpDataset_Fields[5], value ); }

    ds_string FASTCALL GetDFVCODE5() const               { return ( ReadString( tblHelpDataset_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[6] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )  { WriteString( tblHelpDataset_Fields[6], value ); }

    ds_string FASTCALL GetDFVCODE6() const               { return ( ReadString( tblHelpDataset_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[7] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )  { WriteString( tblHelpDataset_Fields[7], value ); }

    ds_string FASTCALL GetDFVCODE7() const               { return ( ReadString( tblHelpDataset_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[8] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )  { WriteString( tblHelpDataset_Fields[8], value ); }

    int FASTCALL GetWEEK() const                         { return ( ReadInteger( tblHelpDataset_Fields[9] ) ); }
    bool FASTCALL WEEK_IsNull() const                    { return ( IsNull( tblHelpDataset_Fields[9] ) ); }
    void FASTCALL SetWEEK( int value )                   { WriteInteger( tblHelpDataset_Fields[9], value ); }

    int FASTCALL GetYEAR() const                         { return ( ReadInteger( tblHelpDataset_Fields[10] ) ); }
    bool FASTCALL YEAR_IsNull() const                    { return ( IsNull( tblHelpDataset_Fields[10] ) ); }
    void FASTCALL SetYEAR( int value )                   { WriteInteger( tblHelpDataset_Fields[10], value ); }

    double FASTCALL GetGROSSREQ() const                  { return ( ReadFloat( tblHelpDataset_Fields[11] ) ); }
    bool FASTCALL GROSSREQ_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[11] ) ); }
    void FASTCALL SetGROSSREQ( double value )            { WriteFloat( tblHelpDataset_Fields[11], value ); }

    double FASTCALL GetSCHEDREQ() const                  { return ( ReadFloat( tblHelpDataset_Fields[12] ) ); }
    bool FASTCALL SCHEDREQ_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[12] ) ); }
    void FASTCALL SetSCHEDREQ( double value )            { WriteFloat( tblHelpDataset_Fields[12], value ); }

    double FASTCALL GetPROJONHAND() const                { return ( ReadFloat( tblHelpDataset_Fields[13] ) ); }
    bool FASTCALL PROJONHAND_IsNull() const              { return ( IsNull( tblHelpDataset_Fields[13] ) ); }
    void FASTCALL SetPROJONHAND( double value )          { WriteFloat( tblHelpDataset_Fields[13], value ); }

    double FASTCALL GetNETREQ() const                    { return ( ReadFloat( tblHelpDataset_Fields[14] ) ); }
    bool FASTCALL NETREQ_IsNull() const                  { return ( IsNull( tblHelpDataset_Fields[14] ) ); }
    void FASTCALL SetNETREQ( double value )              { WriteFloat( tblHelpDataset_Fields[14], value ); }

    double FASTCALL GetREQPO() const                     { return ( ReadFloat( tblHelpDataset_Fields[15] ) ); }
    bool FASTCALL REQPO_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[15] ) ); }
    void FASTCALL SetREQPO( double value )               { WriteFloat( tblHelpDataset_Fields[15], value ); }

    double FASTCALL GetRELPO() const                     { return ( ReadFloat( tblHelpDataset_Fields[16] ) ); }
    bool FASTCALL RELPO_IsNull() const                   { return ( IsNull( tblHelpDataset_Fields[16] ) ); }
    void FASTCALL SetRELPO( double value )               { WriteFloat( tblHelpDataset_Fields[16], value ); }

    double FASTCALL GetPROJAVBAL() const                 { return ( ReadFloat( tblHelpDataset_Fields[17] ) ); }
    bool FASTCALL PROJAVBAL_IsNull() const               { return ( IsNull( tblHelpDataset_Fields[17] ) ); }
    void FASTCALL SetPROJAVBAL( double value )           { WriteFloat( tblHelpDataset_Fields[17], value ); }

    double FASTCALL GetEXPECTED() const                  { return ( ReadFloat( tblHelpDataset_Fields[18] ) ); }
    bool FASTCALL EXPECTED_IsNull() const                { return ( IsNull( tblHelpDataset_Fields[18] ) ); }
    void FASTCALL SetEXPECTED( double value )            { WriteFloat( tblHelpDataset_Fields[18], value ); }

    double FASTCALL GetTIED() const                      { return ( ReadFloat( tblHelpDataset_Fields[19] ) ); }
    bool FASTCALL TIED_IsNull() const                    { return ( IsNull( tblHelpDataset_Fields[19] ) ); }
    void FASTCALL SetTIED( double value )                { WriteFloat( tblHelpDataset_Fields[19], value ); }

    int FASTCALL GetDAYS() const                         { return ( ReadInteger( tblHelpDataset_Fields[20] ) ); }
    bool FASTCALL DAYS_IsNull() const                    { return ( IsNull( tblHelpDataset_Fields[20] ) ); }
    void FASTCALL SetDAYS( int value )                   { WriteInteger( tblHelpDataset_Fields[20], value ); }

    ds::cDateTime FASTCALL GetDATE() const               { return ( ReadDate( tblHelpDataset_Fields[21] ) ); }
    bool FASTCALL DATE_IsNull() const                    { return ( IsNull( tblHelpDataset_Fields[21] ) ); }
    void FASTCALL SetDATE( const ds::cDateTime& value )  { WriteDate( tblHelpDataset_Fields[21], value ); }
};

typedef ds::cuTable<tblHelpDataset_rec>  tblHelpDataset;
typedef ds::shared_ptr<tblHelpDataset>   tblHelpDataset_ptr;
//***********************************************************************
//******    tblHelpDatasetDetail
//***********************************************************************
class tblHelpDatasetDetail_map
{
private:
    tblHelpDatasetDetail_map();
    tblHelpDatasetDetail_map( const tblHelpDatasetDetail_map& src );
    tblHelpDatasetDetail_map& operator = ( const tblHelpDatasetDetail_map& src );
public:
    int     ID_;
    int     DOCID_;
    int     LINENO_;
    double  INITQTY_;
};

class tblHelpDatasetDetail_data
{
protected:
    static const ds::cFieldDef_   tblHelpDatasetDetail_Fields[];
    static const ds::cFieldDefs_  tblHelpDatasetDetail_FieldDef;
};

class tblHelpDatasetDetail_raw : public tblHelpDatasetDetail_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblHelpDatasetDetail_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                           {} // empty
    tblHelpDatasetDetail_raw * FASTCALL operator->()              { return ( this ); }
    const tblHelpDatasetDetail_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetID() const                                    { return ( ReadInteger( tblHelpDatasetDetail_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                               { return ( IsNull( tblHelpDatasetDetail_Fields[0] ) ); }

    int FASTCALL GetDOCID() const                                 { return ( ReadInteger( tblHelpDatasetDetail_Fields[1] ) ); }
    bool FASTCALL DOCID_IsNull() const                            { return ( IsNull( tblHelpDatasetDetail_Fields[1] ) ); }

    int FASTCALL GetLINENO() const                                { return ( ReadInteger( tblHelpDatasetDetail_Fields[2] ) ); }
    bool FASTCALL LINENO_IsNull() const                           { return ( IsNull( tblHelpDatasetDetail_Fields[2] ) ); }

    double FASTCALL GetINITQTY() const                            { return ( ReadFloat( tblHelpDatasetDetail_Fields[3] ) ); }
    bool FASTCALL INITQTY_IsNull() const                          { return ( IsNull( tblHelpDatasetDetail_Fields[3] ) ); }
};

class tblHelpDatasetDetail_rec : public tblHelpDatasetDetail_data, public ds::cRecordPtr
{
public:
    typedef tblHelpDatasetDetail_raw    raw;
public:
    CDFASTCALL tblHelpDatasetDetail_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                           {} // empty
    tblHelpDatasetDetail_rec * FASTCALL operator->()              { return ( this ); }
    const tblHelpDatasetDetail_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetID() const                { return ( ReadInteger( tblHelpDatasetDetail_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const           { return ( IsNull( tblHelpDatasetDetail_Fields[0] ) ); }
    void FASTCALL SetID( int value )          { WriteInteger( tblHelpDatasetDetail_Fields[0], value ); }

    int FASTCALL GetDOCID() const             { return ( ReadInteger( tblHelpDatasetDetail_Fields[1] ) ); }
    bool FASTCALL DOCID_IsNull() const        { return ( IsNull( tblHelpDatasetDetail_Fields[1] ) ); }
    void FASTCALL SetDOCID( int value )       { WriteInteger( tblHelpDatasetDetail_Fields[1], value ); }

    int FASTCALL GetLINENO() const            { return ( ReadInteger( tblHelpDatasetDetail_Fields[2] ) ); }
    bool FASTCALL LINENO_IsNull() const       { return ( IsNull( tblHelpDatasetDetail_Fields[2] ) ); }
    void FASTCALL SetLINENO( int value )      { WriteInteger( tblHelpDatasetDetail_Fields[2], value ); }

    double FASTCALL GetINITQTY() const        { return ( ReadFloat( tblHelpDatasetDetail_Fields[3] ) ); }
    bool FASTCALL INITQTY_IsNull() const      { return ( IsNull( tblHelpDatasetDetail_Fields[3] ) ); }
    void FASTCALL SetINITQTY( double value )  { WriteFloat( tblHelpDatasetDetail_Fields[3], value ); }
};

typedef ds::cuTable<tblHelpDatasetDetail_rec>  tblHelpDatasetDetail;
typedef ds::shared_ptr<tblHelpDatasetDetail>   tblHelpDatasetDetail_ptr;
//***********************************************************************
//******    tblHelpDatasetDetailRELPO
//***********************************************************************
class tblHelpDatasetDetailRELPO_map
{
private:
    tblHelpDatasetDetailRELPO_map();
    tblHelpDatasetDetailRELPO_map( const tblHelpDatasetDetailRELPO_map& src );
    tblHelpDatasetDetailRELPO_map& operator = ( const tblHelpDatasetDetailRELPO_map& src );
public:
    int  ID_;
    int  DOCID_;
    int  LINENO_;
};

class tblHelpDatasetDetailRELPO_data
{
protected:
    static const ds::cFieldDef_   tblHelpDatasetDetailRELPO_Fields[];
    static const ds::cFieldDefs_  tblHelpDatasetDetailRELPO_FieldDef;
};

class tblHelpDatasetDetailRELPO_raw : public tblHelpDatasetDetailRELPO_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblHelpDatasetDetailRELPO_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                                {} // empty
    tblHelpDatasetDetailRELPO_raw * FASTCALL operator->()              { return ( this ); }
    const tblHelpDatasetDetailRELPO_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetID() const                                         { return ( ReadInteger( tblHelpDatasetDetailRELPO_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                                    { return ( IsNull( tblHelpDatasetDetailRELPO_Fields[0] ) ); }

    int FASTCALL GetDOCID() const                                      { return ( ReadInteger( tblHelpDatasetDetailRELPO_Fields[1] ) ); }
    bool FASTCALL DOCID_IsNull() const                                 { return ( IsNull( tblHelpDatasetDetailRELPO_Fields[1] ) ); }

    int FASTCALL GetLINENO() const                                     { return ( ReadInteger( tblHelpDatasetDetailRELPO_Fields[2] ) ); }
    bool FASTCALL LINENO_IsNull() const                                { return ( IsNull( tblHelpDatasetDetailRELPO_Fields[2] ) ); }
};

class tblHelpDatasetDetailRELPO_rec : public tblHelpDatasetDetailRELPO_data, public ds::cRecordPtr
{
public:
    typedef tblHelpDatasetDetailRELPO_raw    raw;
public:
    CDFASTCALL tblHelpDatasetDetailRELPO_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                                {} // empty
    tblHelpDatasetDetailRELPO_rec * FASTCALL operator->()              { return ( this ); }
    const tblHelpDatasetDetailRELPO_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetID() const            { return ( ReadInteger( tblHelpDatasetDetailRELPO_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const       { return ( IsNull( tblHelpDatasetDetailRELPO_Fields[0] ) ); }
    void FASTCALL SetID( int value )      { WriteInteger( tblHelpDatasetDetailRELPO_Fields[0], value ); }

    int FASTCALL GetDOCID() const         { return ( ReadInteger( tblHelpDatasetDetailRELPO_Fields[1] ) ); }
    bool FASTCALL DOCID_IsNull() const    { return ( IsNull( tblHelpDatasetDetailRELPO_Fields[1] ) ); }
    void FASTCALL SetDOCID( int value )   { WriteInteger( tblHelpDatasetDetailRELPO_Fields[1], value ); }

    int FASTCALL GetLINENO() const        { return ( ReadInteger( tblHelpDatasetDetailRELPO_Fields[2] ) ); }
    bool FASTCALL LINENO_IsNull() const   { return ( IsNull( tblHelpDatasetDetailRELPO_Fields[2] ) ); }
    void FASTCALL SetLINENO( int value )  { WriteInteger( tblHelpDatasetDetailRELPO_Fields[2], value ); }
};

typedef ds::cuTable<tblHelpDatasetDetailRELPO_rec>  tblHelpDatasetDetailRELPO;
typedef ds::shared_ptr<tblHelpDatasetDetailRELPO>   tblHelpDatasetDetailRELPO_ptr;
//***********************************************************************
//******    tblPEGGING
//***********************************************************************
class tblPEGGING_map
{
private:
    tblPEGGING_map();
    tblPEGGING_map( const tblPEGGING_map& src );
    tblPEGGING_map& operator = ( const tblPEGGING_map& src );
public:
    int            PEGID_;
    int            MCIID_;
    STRING_FM      (DFVCODE1_,20);
    STRING_FM      (DFVCODE2_,20);
    STRING_FM      (DFVCODE3_,20);
    STRING_FM      (DFVCODE4_,20);
    STRING_FM      (DFVCODE5_,20);
    STRING_FM      (DFVCODE6_,20);
    STRING_FM      (DFVCODE7_,20);
    int            SRCMCIID_;
    STRING_FM      (SRCDFVCODE1_,20);
    STRING_FM      (SRCDFVCODE2_,20);
    STRING_FM      (SRCDFVCODE3_,20);
    STRING_FM      (SRCDFVCODE4_,20);
    STRING_FM      (SRCDFVCODE5_,20);
    STRING_FM      (SRCDFVCODE6_,20);
    STRING_FM      (SRCDFVCODE7_,20);
    int            PRNID_;
    int            WEEK_;
    int            YEAR_;
    double         REQQTY_;
    ds::cDateTime  DATE_;
};

class tblPEGGING_data
{
protected:
    static const ds::cFieldDef_   tblPEGGING_Fields[];
    static const ds::cFieldDefs_  tblPEGGING_FieldDef;
};

class tblPEGGING_raw : public tblPEGGING_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblPEGGING_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                 {} // empty
    tblPEGGING_raw * FASTCALL operator->()              { return ( this ); }
    const tblPEGGING_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetPEGID() const                       { return ( ReadInteger( tblPEGGING_Fields[0] ) ); }
    bool FASTCALL PEGID_IsNull() const                  { return ( IsNull( tblPEGGING_Fields[0] ) ); }

    int FASTCALL GetMCIID() const                       { return ( ReadInteger( tblPEGGING_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                  { return ( IsNull( tblPEGGING_Fields[1] ) ); }

    ds_string FASTCALL GetDFVCODE1() const              { return ( ReadString( tblPEGGING_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const               { return ( IsNull( tblPEGGING_Fields[2] ) ); }

    ds_string FASTCALL GetDFVCODE2() const              { return ( ReadString( tblPEGGING_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const               { return ( IsNull( tblPEGGING_Fields[3] ) ); }

    ds_string FASTCALL GetDFVCODE3() const              { return ( ReadString( tblPEGGING_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const               { return ( IsNull( tblPEGGING_Fields[4] ) ); }

    ds_string FASTCALL GetDFVCODE4() const              { return ( ReadString( tblPEGGING_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const               { return ( IsNull( tblPEGGING_Fields[5] ) ); }

    ds_string FASTCALL GetDFVCODE5() const              { return ( ReadString( tblPEGGING_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const               { return ( IsNull( tblPEGGING_Fields[6] ) ); }

    ds_string FASTCALL GetDFVCODE6() const              { return ( ReadString( tblPEGGING_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const               { return ( IsNull( tblPEGGING_Fields[7] ) ); }

    ds_string FASTCALL GetDFVCODE7() const              { return ( ReadString( tblPEGGING_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const               { return ( IsNull( tblPEGGING_Fields[8] ) ); }

    int FASTCALL GetSRCMCIID() const                    { return ( ReadInteger( tblPEGGING_Fields[9] ) ); }
    bool FASTCALL SRCMCIID_IsNull() const               { return ( IsNull( tblPEGGING_Fields[9] ) ); }

    ds_string FASTCALL GetSRCDFVCODE1() const           { return ( ReadString( tblPEGGING_Fields[10] ) ); }
    bool FASTCALL SRCDFVCODE1_IsNull() const            { return ( IsNull( tblPEGGING_Fields[10] ) ); }

    ds_string FASTCALL GetSRCDFVCODE2() const           { return ( ReadString( tblPEGGING_Fields[11] ) ); }
    bool FASTCALL SRCDFVCODE2_IsNull() const            { return ( IsNull( tblPEGGING_Fields[11] ) ); }

    ds_string FASTCALL GetSRCDFVCODE3() const           { return ( ReadString( tblPEGGING_Fields[12] ) ); }
    bool FASTCALL SRCDFVCODE3_IsNull() const            { return ( IsNull( tblPEGGING_Fields[12] ) ); }

    ds_string FASTCALL GetSRCDFVCODE4() const           { return ( ReadString( tblPEGGING_Fields[13] ) ); }
    bool FASTCALL SRCDFVCODE4_IsNull() const            { return ( IsNull( tblPEGGING_Fields[13] ) ); }

    ds_string FASTCALL GetSRCDFVCODE5() const           { return ( ReadString( tblPEGGING_Fields[14] ) ); }
    bool FASTCALL SRCDFVCODE5_IsNull() const            { return ( IsNull( tblPEGGING_Fields[14] ) ); }

    ds_string FASTCALL GetSRCDFVCODE6() const           { return ( ReadString( tblPEGGING_Fields[15] ) ); }
    bool FASTCALL SRCDFVCODE6_IsNull() const            { return ( IsNull( tblPEGGING_Fields[15] ) ); }

    ds_string FASTCALL GetSRCDFVCODE7() const           { return ( ReadString( tblPEGGING_Fields[16] ) ); }
    bool FASTCALL SRCDFVCODE7_IsNull() const            { return ( IsNull( tblPEGGING_Fields[16] ) ); }

    int FASTCALL GetPRNID() const                       { return ( ReadInteger( tblPEGGING_Fields[17] ) ); }
    bool FASTCALL PRNID_IsNull() const                  { return ( IsNull( tblPEGGING_Fields[17] ) ); }

    int FASTCALL GetWEEK() const                        { return ( ReadInteger( tblPEGGING_Fields[18] ) ); }
    bool FASTCALL WEEK_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[18] ) ); }

    int FASTCALL GetYEAR() const                        { return ( ReadInteger( tblPEGGING_Fields[19] ) ); }
    bool FASTCALL YEAR_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[19] ) ); }

    double FASTCALL GetREQQTY() const                   { return ( ReadFloat( tblPEGGING_Fields[20] ) ); }
    bool FASTCALL REQQTY_IsNull() const                 { return ( IsNull( tblPEGGING_Fields[20] ) ); }

    ds::cDateTime FASTCALL GetDATE() const              { return ( ReadDate( tblPEGGING_Fields[21] ) ); }
    bool FASTCALL DATE_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[21] ) ); }
};

class tblPEGGING_rec : public tblPEGGING_data, public ds::cRecordPtr
{
public:
    typedef tblPEGGING_raw    raw;
public:
    CDFASTCALL tblPEGGING_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                 {} // empty
    tblPEGGING_rec * FASTCALL operator->()              { return ( this ); }
    const tblPEGGING_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetPEGID() const                           { return ( ReadInteger( tblPEGGING_Fields[0] ) ); }
    bool FASTCALL PEGID_IsNull() const                      { return ( IsNull( tblPEGGING_Fields[0] ) ); }
    void FASTCALL SetPEGID( int value )                     { WriteInteger( tblPEGGING_Fields[0], value ); }

    int FASTCALL GetMCIID() const                           { return ( ReadInteger( tblPEGGING_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                      { return ( IsNull( tblPEGGING_Fields[1] ) ); }
    void FASTCALL SetMCIID( int value )                     { WriteInteger( tblPEGGING_Fields[1], value ); }

    ds_string FASTCALL GetDFVCODE1() const                  { return ( ReadString( tblPEGGING_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[2] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )     { WriteString( tblPEGGING_Fields[2], value ); }

    ds_string FASTCALL GetDFVCODE2() const                  { return ( ReadString( tblPEGGING_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[3] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )     { WriteString( tblPEGGING_Fields[3], value ); }

    ds_string FASTCALL GetDFVCODE3() const                  { return ( ReadString( tblPEGGING_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[4] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )     { WriteString( tblPEGGING_Fields[4], value ); }

    ds_string FASTCALL GetDFVCODE4() const                  { return ( ReadString( tblPEGGING_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[5] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )     { WriteString( tblPEGGING_Fields[5], value ); }

    ds_string FASTCALL GetDFVCODE5() const                  { return ( ReadString( tblPEGGING_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[6] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )     { WriteString( tblPEGGING_Fields[6], value ); }

    ds_string FASTCALL GetDFVCODE6() const                  { return ( ReadString( tblPEGGING_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[7] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )     { WriteString( tblPEGGING_Fields[7], value ); }

    ds_string FASTCALL GetDFVCODE7() const                  { return ( ReadString( tblPEGGING_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[8] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )     { WriteString( tblPEGGING_Fields[8], value ); }

    int FASTCALL GetSRCMCIID() const                        { return ( ReadInteger( tblPEGGING_Fields[9] ) ); }
    bool FASTCALL SRCMCIID_IsNull() const                   { return ( IsNull( tblPEGGING_Fields[9] ) ); }
    void FASTCALL SetSRCMCIID( int value )                  { WriteInteger( tblPEGGING_Fields[9], value ); }

    ds_string FASTCALL GetSRCDFVCODE1() const               { return ( ReadString( tblPEGGING_Fields[10] ) ); }
    bool FASTCALL SRCDFVCODE1_IsNull() const                { return ( IsNull( tblPEGGING_Fields[10] ) ); }
    void FASTCALL SetSRCDFVCODE1( const ds_string& value )  { WriteString( tblPEGGING_Fields[10], value ); }

    ds_string FASTCALL GetSRCDFVCODE2() const               { return ( ReadString( tblPEGGING_Fields[11] ) ); }
    bool FASTCALL SRCDFVCODE2_IsNull() const                { return ( IsNull( tblPEGGING_Fields[11] ) ); }
    void FASTCALL SetSRCDFVCODE2( const ds_string& value )  { WriteString( tblPEGGING_Fields[11], value ); }

    ds_string FASTCALL GetSRCDFVCODE3() const               { return ( ReadString( tblPEGGING_Fields[12] ) ); }
    bool FASTCALL SRCDFVCODE3_IsNull() const                { return ( IsNull( tblPEGGING_Fields[12] ) ); }
    void FASTCALL SetSRCDFVCODE3( const ds_string& value )  { WriteString( tblPEGGING_Fields[12], value ); }

    ds_string FASTCALL GetSRCDFVCODE4() const               { return ( ReadString( tblPEGGING_Fields[13] ) ); }
    bool FASTCALL SRCDFVCODE4_IsNull() const                { return ( IsNull( tblPEGGING_Fields[13] ) ); }
    void FASTCALL SetSRCDFVCODE4( const ds_string& value )  { WriteString( tblPEGGING_Fields[13], value ); }

    ds_string FASTCALL GetSRCDFVCODE5() const               { return ( ReadString( tblPEGGING_Fields[14] ) ); }
    bool FASTCALL SRCDFVCODE5_IsNull() const                { return ( IsNull( tblPEGGING_Fields[14] ) ); }
    void FASTCALL SetSRCDFVCODE5( const ds_string& value )  { WriteString( tblPEGGING_Fields[14], value ); }

    ds_string FASTCALL GetSRCDFVCODE6() const               { return ( ReadString( tblPEGGING_Fields[15] ) ); }
    bool FASTCALL SRCDFVCODE6_IsNull() const                { return ( IsNull( tblPEGGING_Fields[15] ) ); }
    void FASTCALL SetSRCDFVCODE6( const ds_string& value )  { WriteString( tblPEGGING_Fields[15], value ); }

    ds_string FASTCALL GetSRCDFVCODE7() const               { return ( ReadString( tblPEGGING_Fields[16] ) ); }
    bool FASTCALL SRCDFVCODE7_IsNull() const                { return ( IsNull( tblPEGGING_Fields[16] ) ); }
    void FASTCALL SetSRCDFVCODE7( const ds_string& value )  { WriteString( tblPEGGING_Fields[16], value ); }

    int FASTCALL GetPRNID() const                           { return ( ReadInteger( tblPEGGING_Fields[17] ) ); }
    bool FASTCALL PRNID_IsNull() const                      { return ( IsNull( tblPEGGING_Fields[17] ) ); }
    void FASTCALL SetPRNID( int value )                     { WriteInteger( tblPEGGING_Fields[17], value ); }

    int FASTCALL GetWEEK() const                            { return ( ReadInteger( tblPEGGING_Fields[18] ) ); }
    bool FASTCALL WEEK_IsNull() const                       { return ( IsNull( tblPEGGING_Fields[18] ) ); }
    void FASTCALL SetWEEK( int value )                      { WriteInteger( tblPEGGING_Fields[18], value ); }

    int FASTCALL GetYEAR() const                            { return ( ReadInteger( tblPEGGING_Fields[19] ) ); }
    bool FASTCALL YEAR_IsNull() const                       { return ( IsNull( tblPEGGING_Fields[19] ) ); }
    void FASTCALL SetYEAR( int value )                      { WriteInteger( tblPEGGING_Fields[19], value ); }

    double FASTCALL GetREQQTY() const                       { return ( ReadFloat( tblPEGGING_Fields[20] ) ); }
    bool FASTCALL REQQTY_IsNull() const                     { return ( IsNull( tblPEGGING_Fields[20] ) ); }
    void FASTCALL SetREQQTY( double value )                 { WriteFloat( tblPEGGING_Fields[20], value ); }

    ds::cDateTime FASTCALL GetDATE() const                  { return ( ReadDate( tblPEGGING_Fields[21] ) ); }
    bool FASTCALL DATE_IsNull() const                       { return ( IsNull( tblPEGGING_Fields[21] ) ); }
    void FASTCALL SetDATE( const ds::cDateTime& value )     { WriteDate( tblPEGGING_Fields[21], value ); }
};

typedef ds::cuTable<tblPEGGING_rec>  tblPEGGING;
typedef ds::shared_ptr<tblPEGGING>   tblPEGGING_ptr;
//***********************************************************************
//******    tblFromPriorLevel
//***********************************************************************
class tblFromPriorLevel_map
{
private:
    tblFromPriorLevel_map();
    tblFromPriorLevel_map( const tblFromPriorLevel_map& src );
    tblFromPriorLevel_map& operator = ( const tblFromPriorLevel_map& src );
public:
    int            ID_;
    int            MCIID_;
    STRING_FM      (DFVCODE1_,20);
    STRING_FM      (DFVCODE2_,20);
    STRING_FM      (DFVCODE3_,20);
    STRING_FM      (DFVCODE4_,20);
    STRING_FM      (DFVCODE5_,20);
    STRING_FM      (DFVCODE6_,20);
    STRING_FM      (DFVCODE7_,20);
    int            WEEK_;
    int            YEAR_;
    double         QTY_;
    int            DAYS_;
    ds::cDateTime  DATE_;
};

class tblFromPriorLevel_data
{
protected:
    static const ds::cFieldDef_   tblFromPriorLevel_Fields[];
    static const ds::cFieldDefs_  tblFromPriorLevel_FieldDef;
};

class tblFromPriorLevel_raw : public tblFromPriorLevel_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblFromPriorLevel_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                        {} // empty
    tblFromPriorLevel_raw * FASTCALL operator->()              { return ( this ); }
    const tblFromPriorLevel_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetID() const                                 { return ( ReadInteger( tblFromPriorLevel_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                            { return ( IsNull( tblFromPriorLevel_Fields[0] ) ); }

    int FASTCALL GetMCIID() const                              { return ( ReadInteger( tblFromPriorLevel_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                         { return ( IsNull( tblFromPriorLevel_Fields[1] ) ); }

    ds_string FASTCALL GetDFVCODE1() const                     { return ( ReadString( tblFromPriorLevel_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                      { return ( IsNull( tblFromPriorLevel_Fields[2] ) ); }

    ds_string FASTCALL GetDFVCODE2() const                     { return ( ReadString( tblFromPriorLevel_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                      { return ( IsNull( tblFromPriorLevel_Fields[3] ) ); }

    ds_string FASTCALL GetDFVCODE3() const                     { return ( ReadString( tblFromPriorLevel_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                      { return ( IsNull( tblFromPriorLevel_Fields[4] ) ); }

    ds_string FASTCALL GetDFVCODE4() const                     { return ( ReadString( tblFromPriorLevel_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                      { return ( IsNull( tblFromPriorLevel_Fields[5] ) ); }

    ds_string FASTCALL GetDFVCODE5() const                     { return ( ReadString( tblFromPriorLevel_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                      { return ( IsNull( tblFromPriorLevel_Fields[6] ) ); }

    ds_string FASTCALL GetDFVCODE6() const                     { return ( ReadString( tblFromPriorLevel_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                      { return ( IsNull( tblFromPriorLevel_Fields[7] ) ); }

    ds_string FASTCALL GetDFVCODE7() const                     { return ( ReadString( tblFromPriorLevel_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                      { return ( IsNull( tblFromPriorLevel_Fields[8] ) ); }

    int FASTCALL GetWEEK() const                               { return ( ReadInteger( tblFromPriorLevel_Fields[9] ) ); }
    bool FASTCALL WEEK_IsNull() const                          { return ( IsNull( tblFromPriorLevel_Fields[9] ) ); }

    int FASTCALL GetYEAR() const                               { return ( ReadInteger( tblFromPriorLevel_Fields[10] ) ); }
    bool FASTCALL YEAR_IsNull() const                          { return ( IsNull( tblFromPriorLevel_Fields[10] ) ); }

    double FASTCALL GetQTY() const                             { return ( ReadFloat( tblFromPriorLevel_Fields[11] ) ); }
    bool FASTCALL QTY_IsNull() const                           { return ( IsNull( tblFromPriorLevel_Fields[11] ) ); }

    int FASTCALL GetDAYS() const                               { return ( ReadInteger( tblFromPriorLevel_Fields[12] ) ); }
    bool FASTCALL DAYS_IsNull() const                          { return ( IsNull( tblFromPriorLevel_Fields[12] ) ); }

    ds::cDateTime FASTCALL GetDATE() const                     { return ( ReadDate( tblFromPriorLevel_Fields[13] ) ); }
    bool FASTCALL DATE_IsNull() const                          { return ( IsNull( tblFromPriorLevel_Fields[13] ) ); }
};

class tblFromPriorLevel_rec : public tblFromPriorLevel_data, public ds::cRecordPtr
{
public:
    typedef tblFromPriorLevel_raw    raw;
public:
    CDFASTCALL tblFromPriorLevel_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                        {} // empty
    tblFromPriorLevel_rec * FASTCALL operator->()              { return ( this ); }
    const tblFromPriorLevel_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetID() const                           { return ( ReadInteger( tblFromPriorLevel_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                      { return ( IsNull( tblFromPriorLevel_Fields[0] ) ); }
    void FASTCALL SetID( int value )                     { WriteInteger( tblFromPriorLevel_Fields[0], value ); }

    int FASTCALL GetMCIID() const                        { return ( ReadInteger( tblFromPriorLevel_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                   { return ( IsNull( tblFromPriorLevel_Fields[1] ) ); }
    void FASTCALL SetMCIID( int value )                  { WriteInteger( tblFromPriorLevel_Fields[1], value ); }

    ds_string FASTCALL GetDFVCODE1() const               { return ( ReadString( tblFromPriorLevel_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                { return ( IsNull( tblFromPriorLevel_Fields[2] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )  { WriteString( tblFromPriorLevel_Fields[2], value ); }

    ds_string FASTCALL GetDFVCODE2() const               { return ( ReadString( tblFromPriorLevel_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                { return ( IsNull( tblFromPriorLevel_Fields[3] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )  { WriteString( tblFromPriorLevel_Fields[3], value ); }

    ds_string FASTCALL GetDFVCODE3() const               { return ( ReadString( tblFromPriorLevel_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                { return ( IsNull( tblFromPriorLevel_Fields[4] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )  { WriteString( tblFromPriorLevel_Fields[4], value ); }

    ds_string FASTCALL GetDFVCODE4() const               { return ( ReadString( tblFromPriorLevel_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                { return ( IsNull( tblFromPriorLevel_Fields[5] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )  { WriteString( tblFromPriorLevel_Fields[5], value ); }

    ds_string FASTCALL GetDFVCODE5() const               { return ( ReadString( tblFromPriorLevel_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                { return ( IsNull( tblFromPriorLevel_Fields[6] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )  { WriteString( tblFromPriorLevel_Fields[6], value ); }

    ds_string FASTCALL GetDFVCODE6() const               { return ( ReadString( tblFromPriorLevel_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                { return ( IsNull( tblFromPriorLevel_Fields[7] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )  { WriteString( tblFromPriorLevel_Fields[7], value ); }

    ds_string FASTCALL GetDFVCODE7() const               { return ( ReadString( tblFromPriorLevel_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                { return ( IsNull( tblFromPriorLevel_Fields[8] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )  { WriteString( tblFromPriorLevel_Fields[8], value ); }

    int FASTCALL GetWEEK() const                         { return ( ReadInteger( tblFromPriorLevel_Fields[9] ) ); }
    bool FASTCALL WEEK_IsNull() const                    { return ( IsNull( tblFromPriorLevel_Fields[9] ) ); }
    void FASTCALL SetWEEK( int value )                   { WriteInteger( tblFromPriorLevel_Fields[9], value ); }

    int FASTCALL GetYEAR() const                         { return ( ReadInteger( tblFromPriorLevel_Fields[10] ) ); }
    bool FASTCALL YEAR_IsNull() const                    { return ( IsNull( tblFromPriorLevel_Fields[10] ) ); }
    void FASTCALL SetYEAR( int value )                   { WriteInteger( tblFromPriorLevel_Fields[10], value ); }

    double FASTCALL GetQTY() const                       { return ( ReadFloat( tblFromPriorLevel_Fields[11] ) ); }
    bool FASTCALL QTY_IsNull() const                     { return ( IsNull( tblFromPriorLevel_Fields[11] ) ); }
    void FASTCALL SetQTY( double value )                 { WriteFloat( tblFromPriorLevel_Fields[11], value ); }

    int FASTCALL GetDAYS() const                         { return ( ReadInteger( tblFromPriorLevel_Fields[12] ) ); }
    bool FASTCALL DAYS_IsNull() const                    { return ( IsNull( tblFromPriorLevel_Fields[12] ) ); }
    void FASTCALL SetDAYS( int value )                   { WriteInteger( tblFromPriorLevel_Fields[12], value ); }

    ds::cDateTime FASTCALL GetDATE() const               { return ( ReadDate( tblFromPriorLevel_Fields[13] ) ); }
    bool FASTCALL DATE_IsNull() const                    { return ( IsNull( tblFromPriorLevel_Fields[13] ) ); }
    void FASTCALL SetDATE( const ds::cDateTime& value )  { WriteDate( tblFromPriorLevel_Fields[13], value ); }
};

typedef ds::cuTable<tblFromPriorLevel_rec>  tblFromPriorLevel;
typedef ds::shared_ptr<tblFromPriorLevel>   tblFromPriorLevel_ptr;
//***********************************************************************
//******    tblFromPriorLevelDetail
//***********************************************************************
class tblFromPriorLevelDetail_map
{
private:
    tblFromPriorLevelDetail_map();
    tblFromPriorLevelDetail_map( const tblFromPriorLevelDetail_map& src );
    tblFromPriorLevelDetail_map& operator = ( const tblFromPriorLevelDetail_map& src );
public:
    int  ID_;
    int  DOCID_;
    int  LINENO_;
};

class tblFromPriorLevelDetail_data
{
protected:
    static const ds::cFieldDef_   tblFromPriorLevelDetail_Fields[];
    static const ds::cFieldDefs_  tblFromPriorLevelDetail_FieldDef;
};

class tblFromPriorLevelDetail_raw : public tblFromPriorLevelDetail_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblFromPriorLevelDetail_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                              {} // empty
    tblFromPriorLevelDetail_raw * FASTCALL operator->()              { return ( this ); }
    const tblFromPriorLevelDetail_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetID() const                                       { return ( ReadInteger( tblFromPriorLevelDetail_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                                  { return ( IsNull( tblFromPriorLevelDetail_Fields[0] ) ); }

    int FASTCALL GetDOCID() const                                    { return ( ReadInteger( tblFromPriorLevelDetail_Fields[1] ) ); }
    bool FASTCALL DOCID_IsNull() const                               { return ( IsNull( tblFromPriorLevelDetail_Fields[1] ) ); }

    int FASTCALL GetLINENO() const                                   { return ( ReadInteger( tblFromPriorLevelDetail_Fields[2] ) ); }
    bool FASTCALL LINENO_IsNull() const                              { return ( IsNull( tblFromPriorLevelDetail_Fields[2] ) ); }
};

class tblFromPriorLevelDetail_rec : public tblFromPriorLevelDetail_data, public ds::cRecordPtr
{
public:
    typedef tblFromPriorLevelDetail_raw    raw;
public:
    CDFASTCALL tblFromPriorLevelDetail_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                              {} // empty
    tblFromPriorLevelDetail_rec * FASTCALL operator->()              { return ( this ); }
    const tblFromPriorLevelDetail_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetID() const            { return ( ReadInteger( tblFromPriorLevelDetail_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const       { return ( IsNull( tblFromPriorLevelDetail_Fields[0] ) ); }
    void FASTCALL SetID( int value )      { WriteInteger( tblFromPriorLevelDetail_Fields[0], value ); }

    int FASTCALL GetDOCID() const         { return ( ReadInteger( tblFromPriorLevelDetail_Fields[1] ) ); }
    bool FASTCALL DOCID_IsNull() const    { return ( IsNull( tblFromPriorLevelDetail_Fields[1] ) ); }
    void FASTCALL SetDOCID( int value )   { WriteInteger( tblFromPriorLevelDetail_Fields[1], value ); }

    int FASTCALL GetLINENO() const        { return ( ReadInteger( tblFromPriorLevelDetail_Fields[2] ) ); }
    bool FASTCALL LINENO_IsNull() const   { return ( IsNull( tblFromPriorLevelDetail_Fields[2] ) ); }
    void FASTCALL SetLINENO( int value )  { WriteInteger( tblFromPriorLevelDetail_Fields[2], value ); }
};

typedef ds::cuTable<tblFromPriorLevelDetail_rec>  tblFromPriorLevelDetail;
typedef ds::shared_ptr<tblFromPriorLevelDetail>   tblFromPriorLevelDetail_ptr;
//***********************************************************************
//******    tblFromCurrentLevel
//***********************************************************************
class tblFromCurrentLevel_map
{
private:
    tblFromCurrentLevel_map();
    tblFromCurrentLevel_map( const tblFromCurrentLevel_map& src );
    tblFromCurrentLevel_map& operator = ( const tblFromCurrentLevel_map& src );
public:
    int            ID_;
    int            MCIID_;
    STRING_FM      (DFVCODE1_,20);
    STRING_FM      (DFVCODE2_,20);
    STRING_FM      (DFVCODE3_,20);
    STRING_FM      (DFVCODE4_,20);
    STRING_FM      (DFVCODE5_,20);
    STRING_FM      (DFVCODE6_,20);
    STRING_FM      (DFVCODE7_,20);
    int            WEEK_;
    int            YEAR_;
    double         QTY_;
    int            DAYS_;
    ds::cDateTime  DATE_;
};

class tblFromCurrentLevel_data
{
protected:
    static const ds::cFieldDef_   tblFromCurrentLevel_Fields[];
    static const ds::cFieldDefs_  tblFromCurrentLevel_FieldDef;
};

class tblFromCurrentLevel_raw : public tblFromCurrentLevel_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblFromCurrentLevel_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                          {} // empty
    tblFromCurrentLevel_raw * FASTCALL operator->()              { return ( this ); }
    const tblFromCurrentLevel_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetID() const                                   { return ( ReadInteger( tblFromCurrentLevel_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                              { return ( IsNull( tblFromCurrentLevel_Fields[0] ) ); }

    int FASTCALL GetMCIID() const                                { return ( ReadInteger( tblFromCurrentLevel_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                           { return ( IsNull( tblFromCurrentLevel_Fields[1] ) ); }

    ds_string FASTCALL GetDFVCODE1() const                       { return ( ReadString( tblFromCurrentLevel_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                        { return ( IsNull( tblFromCurrentLevel_Fields[2] ) ); }

    ds_string FASTCALL GetDFVCODE2() const                       { return ( ReadString( tblFromCurrentLevel_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                        { return ( IsNull( tblFromCurrentLevel_Fields[3] ) ); }

    ds_string FASTCALL GetDFVCODE3() const                       { return ( ReadString( tblFromCurrentLevel_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                        { return ( IsNull( tblFromCurrentLevel_Fields[4] ) ); }

    ds_string FASTCALL GetDFVCODE4() const                       { return ( ReadString( tblFromCurrentLevel_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                        { return ( IsNull( tblFromCurrentLevel_Fields[5] ) ); }

    ds_string FASTCALL GetDFVCODE5() const                       { return ( ReadString( tblFromCurrentLevel_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                        { return ( IsNull( tblFromCurrentLevel_Fields[6] ) ); }

    ds_string FASTCALL GetDFVCODE6() const                       { return ( ReadString( tblFromCurrentLevel_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                        { return ( IsNull( tblFromCurrentLevel_Fields[7] ) ); }

    ds_string FASTCALL GetDFVCODE7() const                       { return ( ReadString( tblFromCurrentLevel_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                        { return ( IsNull( tblFromCurrentLevel_Fields[8] ) ); }

    int FASTCALL GetWEEK() const                                 { return ( ReadInteger( tblFromCurrentLevel_Fields[9] ) ); }
    bool FASTCALL WEEK_IsNull() const                            { return ( IsNull( tblFromCurrentLevel_Fields[9] ) ); }

    int FASTCALL GetYEAR() const                                 { return ( ReadInteger( tblFromCurrentLevel_Fields[10] ) ); }
    bool FASTCALL YEAR_IsNull() const                            { return ( IsNull( tblFromCurrentLevel_Fields[10] ) ); }

    double FASTCALL GetQTY() const                               { return ( ReadFloat( tblFromCurrentLevel_Fields[11] ) ); }
    bool FASTCALL QTY_IsNull() const                             { return ( IsNull( tblFromCurrentLevel_Fields[11] ) ); }

    int FASTCALL GetDAYS() const                                 { return ( ReadInteger( tblFromCurrentLevel_Fields[12] ) ); }
    bool FASTCALL DAYS_IsNull() const                            { return ( IsNull( tblFromCurrentLevel_Fields[12] ) ); }

    ds::cDateTime FASTCALL GetDATE() const                       { return ( ReadDate( tblFromCurrentLevel_Fields[13] ) ); }
    bool FASTCALL DATE_IsNull() const                            { return ( IsNull( tblFromCurrentLevel_Fields[13] ) ); }
};

class tblFromCurrentLevel_rec : public tblFromCurrentLevel_data, public ds::cRecordPtr
{
public:
    typedef tblFromCurrentLevel_raw    raw;
public:
    CDFASTCALL tblFromCurrentLevel_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                          {} // empty
    tblFromCurrentLevel_rec * FASTCALL operator->()              { return ( this ); }
    const tblFromCurrentLevel_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetID() const                           { return ( ReadInteger( tblFromCurrentLevel_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                      { return ( IsNull( tblFromCurrentLevel_Fields[0] ) ); }
    void FASTCALL SetID( int value )                     { WriteInteger( tblFromCurrentLevel_Fields[0], value ); }

    int FASTCALL GetMCIID() const                        { return ( ReadInteger( tblFromCurrentLevel_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                   { return ( IsNull( tblFromCurrentLevel_Fields[1] ) ); }
    void FASTCALL SetMCIID( int value )                  { WriteInteger( tblFromCurrentLevel_Fields[1], value ); }

    ds_string FASTCALL GetDFVCODE1() const               { return ( ReadString( tblFromCurrentLevel_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                { return ( IsNull( tblFromCurrentLevel_Fields[2] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )  { WriteString( tblFromCurrentLevel_Fields[2], value ); }

    ds_string FASTCALL GetDFVCODE2() const               { return ( ReadString( tblFromCurrentLevel_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                { return ( IsNull( tblFromCurrentLevel_Fields[3] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )  { WriteString( tblFromCurrentLevel_Fields[3], value ); }

    ds_string FASTCALL GetDFVCODE3() const               { return ( ReadString( tblFromCurrentLevel_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                { return ( IsNull( tblFromCurrentLevel_Fields[4] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )  { WriteString( tblFromCurrentLevel_Fields[4], value ); }

    ds_string FASTCALL GetDFVCODE4() const               { return ( ReadString( tblFromCurrentLevel_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                { return ( IsNull( tblFromCurrentLevel_Fields[5] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )  { WriteString( tblFromCurrentLevel_Fields[5], value ); }

    ds_string FASTCALL GetDFVCODE5() const               { return ( ReadString( tblFromCurrentLevel_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                { return ( IsNull( tblFromCurrentLevel_Fields[6] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )  { WriteString( tblFromCurrentLevel_Fields[6], value ); }

    ds_string FASTCALL GetDFVCODE6() const               { return ( ReadString( tblFromCurrentLevel_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                { return ( IsNull( tblFromCurrentLevel_Fields[7] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )  { WriteString( tblFromCurrentLevel_Fields[7], value ); }

    ds_string FASTCALL GetDFVCODE7() const               { return ( ReadString( tblFromCurrentLevel_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                { return ( IsNull( tblFromCurrentLevel_Fields[8] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )  { WriteString( tblFromCurrentLevel_Fields[8], value ); }

    int FASTCALL GetWEEK() const                         { return ( ReadInteger( tblFromCurrentLevel_Fields[9] ) ); }
    bool FASTCALL WEEK_IsNull() const                    { return ( IsNull( tblFromCurrentLevel_Fields[9] ) ); }
    void FASTCALL SetWEEK( int value )                   { WriteInteger( tblFromCurrentLevel_Fields[9], value ); }

    int FASTCALL GetYEAR() const                         { return ( ReadInteger( tblFromCurrentLevel_Fields[10] ) ); }
    bool FASTCALL YEAR_IsNull() const                    { return ( IsNull( tblFromCurrentLevel_Fields[10] ) ); }
    void FASTCALL SetYEAR( int value )                   { WriteInteger( tblFromCurrentLevel_Fields[10], value ); }

    double FASTCALL GetQTY() const                       { return ( ReadFloat( tblFromCurrentLevel_Fields[11] ) ); }
    bool FASTCALL QTY_IsNull() const                     { return ( IsNull( tblFromCurrentLevel_Fields[11] ) ); }
    void FASTCALL SetQTY( double value )                 { WriteFloat( tblFromCurrentLevel_Fields[11], value ); }

    int FASTCALL GetDAYS() const                         { return ( ReadInteger( tblFromCurrentLevel_Fields[12] ) ); }
    bool FASTCALL DAYS_IsNull() const                    { return ( IsNull( tblFromCurrentLevel_Fields[12] ) ); }
    void FASTCALL SetDAYS( int value )                   { WriteInteger( tblFromCurrentLevel_Fields[12], value ); }

    ds::cDateTime FASTCALL GetDATE() const               { return ( ReadDate( tblFromCurrentLevel_Fields[13] ) ); }
    bool FASTCALL DATE_IsNull() const                    { return ( IsNull( tblFromCurrentLevel_Fields[13] ) ); }
    void FASTCALL SetDATE( const ds::cDateTime& value )  { WriteDate( tblFromCurrentLevel_Fields[13], value ); }
};

typedef ds::cuTable<tblFromCurrentLevel_rec>  tblFromCurrentLevel;
typedef ds::shared_ptr<tblFromCurrentLevel>   tblFromCurrentLevel_ptr;
//***********************************************************************
//******    tblFromPrnLevel
//***********************************************************************
class tblFromPrnLevel_map
{
private:
    tblFromPrnLevel_map();
    tblFromPrnLevel_map( const tblFromPrnLevel_map& src );
    tblFromPrnLevel_map& operator = ( const tblFromPrnLevel_map& src );
public:
    int            ID_;
    int            MCIID_;
    STRING_FM      (DFVCODE1_,20);
    STRING_FM      (DFVCODE2_,20);
    STRING_FM      (DFVCODE3_,20);
    STRING_FM      (DFVCODE4_,20);
    STRING_FM      (DFVCODE5_,20);
    STRING_FM      (DFVCODE6_,20);
    STRING_FM      (DFVCODE7_,20);
    int            WEEK_;
    int            YEAR_;
    double         QTY_;
    int            DAYS_;
    ds::cDateTime  DATE_;
};

class tblFromPrnLevel_data
{
protected:
    static const ds::cFieldDef_   tblFromPrnLevel_Fields[];
    static const ds::cFieldDefs_  tblFromPrnLevel_FieldDef;
};

class tblFromPrnLevel_raw : public tblFromPrnLevel_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblFromPrnLevel_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                      {} // empty
    tblFromPrnLevel_raw * FASTCALL operator->()              { return ( this ); }
    const tblFromPrnLevel_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetID() const                               { return ( ReadInteger( tblFromPrnLevel_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                          { return ( IsNull( tblFromPrnLevel_Fields[0] ) ); }

    int FASTCALL GetMCIID() const                            { return ( ReadInteger( tblFromPrnLevel_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                       { return ( IsNull( tblFromPrnLevel_Fields[1] ) ); }

    ds_string FASTCALL GetDFVCODE1() const                   { return ( ReadString( tblFromPrnLevel_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[2] ) ); }

    ds_string FASTCALL GetDFVCODE2() const                   { return ( ReadString( tblFromPrnLevel_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[3] ) ); }

    ds_string FASTCALL GetDFVCODE3() const                   { return ( ReadString( tblFromPrnLevel_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[4] ) ); }

    ds_string FASTCALL GetDFVCODE4() const                   { return ( ReadString( tblFromPrnLevel_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[5] ) ); }

    ds_string FASTCALL GetDFVCODE5() const                   { return ( ReadString( tblFromPrnLevel_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[6] ) ); }

    ds_string FASTCALL GetDFVCODE6() const                   { return ( ReadString( tblFromPrnLevel_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[7] ) ); }

    ds_string FASTCALL GetDFVCODE7() const                   { return ( ReadString( tblFromPrnLevel_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[8] ) ); }

    int FASTCALL GetWEEK() const                             { return ( ReadInteger( tblFromPrnLevel_Fields[9] ) ); }
    bool FASTCALL WEEK_IsNull() const                        { return ( IsNull( tblFromPrnLevel_Fields[9] ) ); }

    int FASTCALL GetYEAR() const                             { return ( ReadInteger( tblFromPrnLevel_Fields[10] ) ); }
    bool FASTCALL YEAR_IsNull() const                        { return ( IsNull( tblFromPrnLevel_Fields[10] ) ); }

    double FASTCALL GetQTY() const                           { return ( ReadFloat( tblFromPrnLevel_Fields[11] ) ); }
    bool FASTCALL QTY_IsNull() const                         { return ( IsNull( tblFromPrnLevel_Fields[11] ) ); }

    int FASTCALL GetDAYS() const                             { return ( ReadInteger( tblFromPrnLevel_Fields[12] ) ); }
    bool FASTCALL DAYS_IsNull() const                        { return ( IsNull( tblFromPrnLevel_Fields[12] ) ); }

    ds::cDateTime FASTCALL GetDATE() const                   { return ( ReadDate( tblFromPrnLevel_Fields[13] ) ); }
    bool FASTCALL DATE_IsNull() const                        { return ( IsNull( tblFromPrnLevel_Fields[13] ) ); }
};

class tblFromPrnLevel_rec : public tblFromPrnLevel_data, public ds::cRecordPtr
{
public:
    typedef tblFromPrnLevel_raw    raw;
public:
    CDFASTCALL tblFromPrnLevel_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                      {} // empty
    tblFromPrnLevel_rec * FASTCALL operator->()              { return ( this ); }
    const tblFromPrnLevel_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetID() const                           { return ( ReadInteger( tblFromPrnLevel_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                      { return ( IsNull( tblFromPrnLevel_Fields[0] ) ); }
    void FASTCALL SetID( int value )                     { WriteInteger( tblFromPrnLevel_Fields[0], value ); }

    int FASTCALL GetMCIID() const                        { return ( ReadInteger( tblFromPrnLevel_Fields[1] ) ); }
    bool FASTCALL MCIID_IsNull() const                   { return ( IsNull( tblFromPrnLevel_Fields[1] ) ); }
    void FASTCALL SetMCIID( int value )                  { WriteInteger( tblFromPrnLevel_Fields[1], value ); }

    ds_string FASTCALL GetDFVCODE1() const               { return ( ReadString( tblFromPrnLevel_Fields[2] ) ); }
    bool FASTCALL DFVCODE1_IsNull() const                { return ( IsNull( tblFromPrnLevel_Fields[2] ) ); }
    void FASTCALL SetDFVCODE1( const ds_string& value )  { WriteString( tblFromPrnLevel_Fields[2], value ); }

    ds_string FASTCALL GetDFVCODE2() const               { return ( ReadString( tblFromPrnLevel_Fields[3] ) ); }
    bool FASTCALL DFVCODE2_IsNull() const                { return ( IsNull( tblFromPrnLevel_Fields[3] ) ); }
    void FASTCALL SetDFVCODE2( const ds_string& value )  { WriteString( tblFromPrnLevel_Fields[3], value ); }

    ds_string FASTCALL GetDFVCODE3() const               { return ( ReadString( tblFromPrnLevel_Fields[4] ) ); }
    bool FASTCALL DFVCODE3_IsNull() const                { return ( IsNull( tblFromPrnLevel_Fields[4] ) ); }
    void FASTCALL SetDFVCODE3( const ds_string& value )  { WriteString( tblFromPrnLevel_Fields[4], value ); }

    ds_string FASTCALL GetDFVCODE4() const               { return ( ReadString( tblFromPrnLevel_Fields[5] ) ); }
    bool FASTCALL DFVCODE4_IsNull() const                { return ( IsNull( tblFromPrnLevel_Fields[5] ) ); }
    void FASTCALL SetDFVCODE4( const ds_string& value )  { WriteString( tblFromPrnLevel_Fields[5], value ); }

    ds_string FASTCALL GetDFVCODE5() const               { return ( ReadString( tblFromPrnLevel_Fields[6] ) ); }
    bool FASTCALL DFVCODE5_IsNull() const                { return ( IsNull( tblFromPrnLevel_Fields[6] ) ); }
    void FASTCALL SetDFVCODE5( const ds_string& value )  { WriteString( tblFromPrnLevel_Fields[6], value ); }

    ds_string FASTCALL GetDFVCODE6() const               { return ( ReadString( tblFromPrnLevel_Fields[7] ) ); }
    bool FASTCALL DFVCODE6_IsNull() const                { return ( IsNull( tblFromPrnLevel_Fields[7] ) ); }
    void FASTCALL SetDFVCODE6( const ds_string& value )  { WriteString( tblFromPrnLevel_Fields[7], value ); }

    ds_string FASTCALL GetDFVCODE7() const               { return ( ReadString( tblFromPrnLevel_Fields[8] ) ); }
    bool FASTCALL DFVCODE7_IsNull() const                { return ( IsNull( tblFromPrnLevel_Fields[8] ) ); }
    void FASTCALL SetDFVCODE7( const ds_string& value )  { WriteString( tblFromPrnLevel_Fields[8], value ); }

    int FASTCALL GetWEEK() const                         { return ( ReadInteger( tblFromPrnLevel_Fields[9] ) ); }
    bool FASTCALL WEEK_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[9] ) ); }
    void FASTCALL SetWEEK( int value )                   { WriteInteger( tblFromPrnLevel_Fields[9], value ); }

    int FASTCALL GetYEAR() const                         { return ( ReadInteger( tblFromPrnLevel_Fields[10] ) ); }
    bool FASTCALL YEAR_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[10] ) ); }
    void FASTCALL SetYEAR( int value )                   { WriteInteger( tblFromPrnLevel_Fields[10], value ); }

    double FASTCALL GetQTY() const                       { return ( ReadFloat( tblFromPrnLevel_Fields[11] ) ); }
    bool FASTCALL QTY_IsNull() const                     { return ( IsNull( tblFromPrnLevel_Fields[11] ) ); }
    void FASTCALL SetQTY( double value )                 { WriteFloat( tblFromPrnLevel_Fields[11], value ); }

    int FASTCALL GetDAYS() const                         { return ( ReadInteger( tblFromPrnLevel_Fields[12] ) ); }
    bool FASTCALL DAYS_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[12] ) ); }
    void FASTCALL SetDAYS( int value )                   { WriteInteger( tblFromPrnLevel_Fields[12], value ); }

    ds::cDateTime FASTCALL GetDATE() const               { return ( ReadDate( tblFromPrnLevel_Fields[13] ) ); }
    bool FASTCALL DATE_IsNull() const                    { return ( IsNull( tblFromPrnLevel_Fields[13] ) ); }
    void FASTCALL SetDATE( const ds::cDateTime& value )  { WriteDate( tblFromPrnLevel_Fields[13], value ); }
};

typedef ds::cuTable<tblFromPrnLevel_rec>  tblFromPrnLevel;
typedef ds::shared_ptr<tblFromPrnLevel>   tblFromPrnLevel_ptr;
//***********************************************************************
//******    tblFromPrnLevelDetail
//***********************************************************************
class tblFromPrnLevelDetail_map
{
private:
    tblFromPrnLevelDetail_map();
    tblFromPrnLevelDetail_map( const tblFromPrnLevelDetail_map& src );
    tblFromPrnLevelDetail_map& operator = ( const tblFromPrnLevelDetail_map& src );
public:
    int  ID_;
    int  DOCID_;
    int  LINENO_;
};

class tblFromPrnLevelDetail_data
{
protected:
    static const ds::cFieldDef_   tblFromPrnLevelDetail_Fields[];
    static const ds::cFieldDefs_  tblFromPrnLevelDetail_FieldDef;
};

class tblFromPrnLevelDetail_raw : public tblFromPrnLevelDetail_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblFromPrnLevelDetail_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)                            {} // empty
    tblFromPrnLevelDetail_raw * FASTCALL operator->()              { return ( this ); }
    const tblFromPrnLevelDetail_raw * FASTCALL operator->() const  { return ( this ); }

    int FASTCALL GetID() const                                     { return ( ReadInteger( tblFromPrnLevelDetail_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const                                { return ( IsNull( tblFromPrnLevelDetail_Fields[0] ) ); }

    int FASTCALL GetDOCID() const                                  { return ( ReadInteger( tblFromPrnLevelDetail_Fields[1] ) ); }
    bool FASTCALL DOCID_IsNull() const                             { return ( IsNull( tblFromPrnLevelDetail_Fields[1] ) ); }

    int FASTCALL GetLINENO() const                                 { return ( ReadInteger( tblFromPrnLevelDetail_Fields[2] ) ); }
    bool FASTCALL LINENO_IsNull() const                            { return ( IsNull( tblFromPrnLevelDetail_Fields[2] ) ); }
};

class tblFromPrnLevelDetail_rec : public tblFromPrnLevelDetail_data, public ds::cRecordPtr
{
public:
    typedef tblFromPrnLevelDetail_raw    raw;
public:
    CDFASTCALL tblFromPrnLevelDetail_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)                            {} // empty
    tblFromPrnLevelDetail_rec * FASTCALL operator->()              { return ( this ); }
    const tblFromPrnLevelDetail_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetID() const            { return ( ReadInteger( tblFromPrnLevelDetail_Fields[0] ) ); }
    bool FASTCALL ID_IsNull() const       { return ( IsNull( tblFromPrnLevelDetail_Fields[0] ) ); }
    void FASTCALL SetID( int value )      { WriteInteger( tblFromPrnLevelDetail_Fields[0], value ); }

    int FASTCALL GetDOCID() const         { return ( ReadInteger( tblFromPrnLevelDetail_Fields[1] ) ); }
    bool FASTCALL DOCID_IsNull() const    { return ( IsNull( tblFromPrnLevelDetail_Fields[1] ) ); }
    void FASTCALL SetDOCID( int value )   { WriteInteger( tblFromPrnLevelDetail_Fields[1], value ); }

    int FASTCALL GetLINENO() const        { return ( ReadInteger( tblFromPrnLevelDetail_Fields[2] ) ); }
    bool FASTCALL LINENO_IsNull() const   { return ( IsNull( tblFromPrnLevelDetail_Fields[2] ) ); }
    void FASTCALL SetLINENO( int value )  { WriteInteger( tblFromPrnLevelDetail_Fields[2], value ); }
};

typedef ds::cuTable<tblFromPrnLevelDetail_rec>  tblFromPrnLevelDetail;
typedef ds::shared_ptr<tblFromPrnLevelDetail>   tblFromPrnLevelDetail_ptr;
//***********************************************************************
//******    tblCAL
//***********************************************************************
class tblCAL_map
{
private:
    tblCAL_map();
    tblCAL_map( const tblCAL_map& src );
    tblCAL_map& operator = ( const tblCAL_map& src );
public:
    ds::cDateTime  CALDATE_;
};

class tblCAL_data
{
protected:
    static const ds::cFieldDef_   tblCAL_Fields[];
    static const ds::cFieldDefs_  tblCAL_FieldDef;
};

class tblCAL_raw : public tblCAL_data, public ds::cRawRecordPtr
{
public:
    CDFASTCALL tblCAL_raw( ds::cRawBuffer& raw_buffer )
        : ds::cRawRecordPtr(raw_buffer)             {} // empty
    tblCAL_raw * FASTCALL operator->()              { return ( this ); }
    const tblCAL_raw * FASTCALL operator->() const  { return ( this ); }

    ds::cDateTime FASTCALL GetCALDATE() const       { return ( ReadDate( tblCAL_Fields[0] ) ); }
    bool FASTCALL CALDATE_IsNull() const            { return ( IsNull( tblCAL_Fields[0] ) ); }
};

class tblCAL_rec : public tblCAL_data, public ds::cRecordPtr
{
public:
    typedef tblCAL_raw    raw;
public:
    CDFASTCALL tblCAL_rec( ds::cDoubleBuffer& double_buffer )
        : ds::cRecordPtr(double_buffer)             {} // empty
    tblCAL_rec * FASTCALL operator->()              { return ( this ); }
    const tblCAL_rec * FASTCALL operator->() const  { return ( this ); }
    static const ds::cFieldDefs_& FASTCALL GetFieldDefs();

    ds::cDateTime FASTCALL GetCALDATE() const               { return ( ReadDate( tblCAL_Fields[0] ) ); }
    bool FASTCALL CALDATE_IsNull() const                    { return ( IsNull( tblCAL_Fields[0] ) ); }
    void FASTCALL SetCALDATE( const ds::cDateTime& value )  { WriteDate( tblCAL_Fields[0], value ); }
};

typedef ds::cuTable<tblCAL_rec>  tblCAL;
typedef ds::shared_ptr<tblCAL>   tblCAL_ptr;
//---------------------------------------------------------------------------
#endif
