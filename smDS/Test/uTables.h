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
#include <dsTypedData.h>
#include "dsODBCtypes.h"
//---------------------------------------------------------------------------

//***********************************************************************
//******    tblLocation
//***********************************************************************
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
    tblLocation_raw * FASTCALL operator->()                         { return this; }
    const tblLocation_raw * FASTCALL operator->() const             { return this; }

    int FASTCALL GetLocationID() const                              { return ReadInteger( tblLocation_Fields[0] ); }
    short FASTCALL GetLocTypeID() const                             { return ReadShort( tblLocation_Fields[1] ); }
    short FASTCALL GetIsUser() const                                { return ReadShort( tblLocation_Fields[2] ); }
    int FASTCALL GetSerialNo() const                                { return ReadInteger( tblLocation_Fields[3] ); }
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
    tblLocation_rec * FASTCALL operator->()                         { return this; }
    const tblLocation_rec * FASTCALL operator->() const             { return this; }
    static const smds::detail::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetLocationID() const                              { return ReadInteger( tblLocation_Fields[0] ); }
    short FASTCALL GetLocTypeID() const                             { return ReadShort( tblLocation_Fields[1] ); }
    short FASTCALL GetIsUser() const                                { return ReadShort( tblLocation_Fields[2] ); }
    int FASTCALL GetSerialNo() const                                { return ReadInteger( tblLocation_Fields[3] ); }
};

typedef smds::cuTable<tblLocation_rec>      tblLocation;
typedef smds::shared_ptr<tblLocation>       tblLocation_ptr;
//---------------------------------------------------------------------------

//***********************************************************************
//******    tblFiles
//***********************************************************************
class tblFiles_data
{
protected:
    static const smds::detail::cFieldDef_   tblFiles_Fields[];
    static const smds::detail::cFieldDefs_  tblFiles_FieldDef;
public:
};

class tblFiles_raw : public tblFiles_data, public smds::detail::cRawRecordPtr
{
public:
    CDFASTCALL tblFiles_raw( smds::detail::cRawBuffer& raw_buffer )
        : smds::detail::cRawRecordPtr(raw_buffer)
    {
    }
    tblFiles_raw * FASTCALL operator->()                         { return this; }
    const tblFiles_raw * FASTCALL operator->() const             { return this; }

    int FASTCALL GetFileID() const                          { return ReadInteger( tblFiles_Fields[0] ); }
    bool FASTCALL FileID_IsNull() const                     { return IsNull( tblFiles_Fields[0] ); }

    int FASTCALL GetPathID() const                          { return ReadInteger( tblFiles_Fields[1] ); }
    bool FASTCALL PathID_IsNull() const                     { return IsNull( tblFiles_Fields[1] ); }

    ds_string FASTCALL GetLongFileName() const              { return ReadString( tblFiles_Fields[2] ); }
    bool FASTCALL LongFileName_IsNull() const               { return IsNull( tblFiles_Fields[2] ); }

    int  FASTCALL GetfSize() const                          { return ReadInteger( tblFiles_Fields[3] ); }
    bool FASTCALL fSize_IsNull() const                      { return IsNull( tblFiles_Fields[3] ); }

    const smds::dbDateTime FASTCALL GetfDate() const        { return ReadDateTime( tblFiles_Fields[4] ); }
    bool FASTCALL fDate_IsNull() const                      { return IsNull( tblFiles_Fields[4] ); }

    ds_string FASTCALL GetDescription() const               { return ReadString( tblFiles_Fields[5] ); }
    bool FASTCALL Description_IsNull() const                { return IsNull( tblFiles_Fields[5] ); }

    int  FASTCALL GetzipID() const                          { return ReadInteger( tblFiles_Fields[6] ); }
    bool FASTCALL zipID_IsNull() const                      { return IsNull( tblFiles_Fields[6] ); }
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
    tblFiles_rec * FASTCALL operator->()                            { return this; }
    const tblFiles_rec * FASTCALL operator->() const                { return this; }
    static const smds::detail::cFieldDefs_& FASTCALL GetFieldDefs();

    int FASTCALL GetFileID() const                                  { return ReadInteger( tblFiles_Fields[0] ); }
    void FASTCALL SetFileID( int value )                            { WriteInteger( tblFiles_Fields[0], value ); }
    bool FASTCALL FileID_IsNull() const                             { return IsNull( tblFiles_Fields[0] ); }

    int FASTCALL GetPathID() const                                  { return ReadInteger( tblFiles_Fields[1] ); }
    void FASTCALL SetPathID( int value )                            { WriteInteger( tblFiles_Fields[1], value ); }
    bool FASTCALL PathID_IsNull() const                             { return IsNull( tblFiles_Fields[1] ); }

    ds_string FASTCALL GetLongFileName() const                      { return ReadString( tblFiles_Fields[2] ); }
    void FASTCALL SetLongFileName( const ds_string& value )         { WriteString( tblFiles_Fields[2], value ); }
    void FASTCALL SetLongFileName( const char *value )              { WriteString( tblFiles_Fields[2], value ); }
    bool FASTCALL LongFileName_IsNull() const                       { return IsNull( tblFiles_Fields[2] ); }

    int  FASTCALL GetfSize() const                                  { return ReadInteger( tblFiles_Fields[3] ); }
    void FASTCALL SetfSize( int value )                             { WriteInteger( tblFiles_Fields[3], value ); }
    bool FASTCALL fSize_IsNull() const                              { return IsNull( tblFiles_Fields[3] ); }

    smds::dbDateTime FASTCALL GetfDate() const                      { return ReadDateTime( tblFiles_Fields[4] ); }
    void FASTCALL SetfDate( const smds::dbDateTime& value )         { WriteDateTime( tblFiles_Fields[4], value ); }
    bool FASTCALL fDate_IsNull() const                              { return IsNull( tblFiles_Fields[4] ); }

    ds_string FASTCALL GetDescription() const                       { return ReadString( tblFiles_Fields[5] ); }
    void FASTCALL SetDescription( const ds_string& value )          { WriteString( tblFiles_Fields[5], value ); }
    void FASTCALL SetDescription( const char *value )               { WriteString( tblFiles_Fields[5], value ); }
    bool FASTCALL Description_IsNull() const                        { return IsNull( tblFiles_Fields[5] ); }

    int  FASTCALL GetzipID() const                                  { return ReadInteger( tblFiles_Fields[6] ); }
    void FASTCALL SetzipID( int value )                             { WriteInteger( tblFiles_Fields[6], value ); }
    bool FASTCALL zipID_IsNull() const                              { return IsNull( tblFiles_Fields[6] ); }
};

typedef smds::cuTable<tblFiles_rec>                 tblFiles;
typedef smds::shared_ptr<tblFiles>                  tblFiles_ptr;

//***********************************************************************
//******    tblSLD
//***********************************************************************
//class tblSLD_map
//{
//private:
//    tblSLD_map();
//    tblSLD_map( const tblSLD_map& src );
//    tblSLD_map& operator = ( const tblSLD_map& src );
//public:
//    int              DOCID_;
//    int              DOTID_;
//    int              FIYID_;
//    int              PERID_;
//    int              DOSID_;
//    STRING_FM        (DOSCODE_,4);
//    int              DOCNUMBER_;
//    int              DOCJRNAA_;
//    smds::cDateTime  DOCKATAHORISISDATE_;
//    smds::cDateTime  DOCENIMEROSISDATE_;
//    smds::cDateTime  DOCEKDOSISDATE_;
//    STRING_FM        (DOCREASON_,100);
//    STRING_FM        (DOCCOMMENT_,255);
//    short            DOCCANENIM_;
//    short            DOCCANCANCEL_;
//    STRING_FM        (DOCCANCELSTATUS_,1);
//    int              DOCIDAKIROMENO_;
//    int              DOCIDAKIROTIKO_;
//    int              DMIID_;
//    short            TDOGROSSRETAIL_;
//    STRING_FM        (TDOOTHERNUMBER_,20);
//    smds::cDateTime  TDOOTHERDATE_;
//    smds::cDateTime  TDOEKTELESISDATE_;
//    STRING_FM        (DSTDESCR_,50);
//    STRING_FM        (PPSDESCR_,50);
//    STRING_FM        (ORGDESCR_,50);
//    int              TPMID_;
//    int              TPTID_;
//    int              SHVID_;
//    int              WRHID_;
//    int              TRAID_;
//    STRING_FM        (TXOCODE_,4);
//    STRING_FM        (TDOTRANSPORTREMARKS_,255);
//    int              ADRIDLOGISTIRIOU_;
//    int              ADRIDPROORISMOU_;
//    smds::cDateTime  TDOSENDTIME_;
//    STRING_FM        (TDOVATSTATUS_,9);
//    STRING_FM        (TDOLEEAFM_,12);
//    STRING_FM        (TDOLEEADT_,20);
//    STRING_FM        (TDOLEEADTKIND_,2);
//    STRING_FM        (TDOADDRESS_,100);
//    int              CURID_;
//    STRING_FM        (TDOEQVTYPE_,1);
//    double           TDOEQUIVALENCE_;
//    int              TDODUEDAYS_;
//    int              TDOGRACEDAYS_;
//    int              SLMID_;
//    double           TDOTRADERDISCPCNT_;
//    double           TDOQTYA_;
//    double           TDOQTYB_;
//    double           TDOTRANSFQTYA_;
//    double           TDOTRANSFQTYB_;
//    double           TDOQTYDISCA_;
//    double           TDOQTYDISCB_;
//    double           TDOTRADERDISC_;
//    double           TDOTRADERDISCBC_;
//    double           TDOPAYMENTDISC_;
//    double           TDOPAYMENTDISCBC_;
//    double           TDOSTOCKDISC_;
//    double           TDOSTOCKDISCBC_;
//    double           TDOPRICELISTDISC_;
//    double           TDOPRICELISTDISCBC_;
//    double           TDOEXTRADISC_;
//    double           TDOEXTRADISCBC_;
//    double           TDONETSTOCK_;
//    double           TDONETSTOCKBC_;
//    double           TDONETGIFT_;
//    double           TDONETGIFTBC_;
//    double           TDONETSURCHARGE_;
//    double           TDONETSURCHARGEBC_;
//    double           TDONETOTHER_;
//    double           TDONETOTHERBC_;
//    double           TDONETTAX_;
//    double           TDONETTAXBC_;
//    double           TDOGROSSVALUE_;
//    double           TDOGROSSVALUEBC_;
//    double           TDOVATSTOCK_;
//    double           TDOVATSTOCKBC_;
//    double           TDOVATGIFT_;
//    double           TDOVATGIFTBC_;
//    double           TDOVATSURCHARGE_;
//    double           TDOVATSURCHARGEBC_;
//    double           TDOVATOTHER_;
//    double           TDOVATOTHERBC_;
//    double           TDOVATTAX_;
//    double           TDOVATTAXBC_;
//    int              PTPIDPAYMENT_;
//    int              PMTIDPAYMENT_;
//    int              DOCIDPAYMENT_;
//    double           TDOPAYMENT_;
//    double           TDOPAYMENTBC_;
//    double           TDONETKRATISI_;
//    double           TDONETKRATISIBC_;
//    double           TDOTRADERBALANCEBEFORE_;
//    double           TDOTRADERBALANCEAFTER_;
//    short            TDOCANTRANSF_;
//    double           TDOADVANCE_;
//    double           TDOADVANCEBC_;
//    double           TDOADVANCEUSAGE_;
//    double           TDOADVANCEUSAGEBC_;
//    int              CDZID_;
//    int              PTPIDDOCTYPE_;
//    int              LEEIDRECEIVER_;
//    int              ADRIDRECEIVER_;
//    int              PMTIDADVANCE_;
//    int              DOCIDADVANCE_;
//    double           TDOPAYMENTDISCPCNT_;
//    int              TTYIDTRADER_;
//    int              TTYIDSALESMAN_;
//    int              TTYIDSTOCKITEM_;
//    short            TDOVATINCLUDED_;
//    int              PTPIDTRADER_;
//    int              SYS_USRID_;
//    smds::cDateTime  SYS_LUPD_;
//    smds::cDateTime  SYS_INS_;
//    STRING_FM        (TDOKEEPPRICESTRANSF_,4);
//    double           TDOTRADERBALANCEBEFOREBC_;
//    double           TDOTRADERBALANCEAFTERBC_;
//    int              SLMIDCOLLECTOR_;
//    int              DOCIDPREDICTION_;
//    short            TDOISPREDICTION_;
//    int              TTYIDASSETITEM_;
//    double           TDOAUDITEQUIVALENCE_;
//    short            TDOAUDITEQVONEBASED_;
//    double           TDODASMEQUIVALENCE_;
//    int              SLDCASHIER_;
//    int              VERID_;
//    double           SLDDISCOUNTPOLICY_;
//    double           SLDDISCOUNTPOLICYBC_;
//    double           TDODETAILTRMTOTAL_;
//    double           TDODETAILTRMTOTALBC_;
//    int              CONID_;
//    int              DOCIDTRIANGLE_;
//    short            TRIANGLESUBSYSID_;
//    int              DOCIDTRIANGLEFROM_;
//    short            TRIANGLESUBSYSIDFROM_;
//    int              TRAIDPRINCIPAL_;
//    int              PRTID_;
//    int              ADRIDDELIVERY_;
//    smds::cDateTime  SLDPROCESSDATE_;
//    int              TDOCOLONNUMBER_;
//    double           TDOQTYAGUARANTEE_;
//    double           TDOQTYBGUARANTEE_;
//    double           TDOGUARANTEERECEIVEDVALUE_;
//    double           TDOGUARANTEERECEIVEDVALUEBC_;
//    double           TDOGUARANTEERETURNEDVALUE_;
//    double           TDOGUARANTEERETURNEDVALUEBC_;
//    int              TTYIDTRADERGUARANTEE_;
//    int              TTYIDSTOCKITEMGUARANTEE_;
//    int              ADRIDBRANCH_;
//    short            TDOTRANSFORMEDCANCELED_;
//    short            TDOTRADERTRANSSIGN_;
//    short            TDOGUARANTEETRADERTRANSSIGN_;
//    double           TDOPOLICYDISCOUNT_;
//    double           TDOPOLICYDISCOUNTBC_;
//    double           TDOTRANSDISCOUNT_;
//    double           TDOTRANSDISCOUNTBC_;
//    int              DIPIDTRANSACTION_;
//    int              BRAID_;
//    int              TRMID_;
//    short            TDOCOPYTRMID_;
//    smds::cDateTime  TDOPAYMENTSTARTDATE_;
//    int              TDOACCEPTDAYS_;
//    int              TDODRIVECURID_;
//    int              TDOTRADERCURID_;
//    double           TDOTRADEREQUIVALENCE_;
//    STRING_FM        (TDOTRADEREQVTYPE_,1);
//    double           TDOTRADERAUDITEQUIVALENCE_;
//    short            TDOTRAAUDITEQVONEBASED_;
//    STRING_FM        (SLDDELIVERYPLACE_,255);
//};
//
//class tblSLD_data
//{
//protected:
//    static const smds::detail::cFieldDef_   tblSLD_Fields[];
//    static const smds::detail::cFieldDefs_  tblSLD_FieldDef;
//};
//
//class tblSLD_raw : public tblSLD_data, public smds::detail::cRawRecordPtr
//{
//public:
//    CDFASTCALL tblSLD_raw( smds::detail::cRawBuffer& raw_buffer )
//        : smds::detail::cRawRecordPtr(raw_buffer)             {} // empty
//    tblSLD_raw * FASTCALL operator->()                        { return ( this ); }
//    const tblSLD_raw * FASTCALL operator->() const            { return ( this ); }
//
//    int FASTCALL GetDOCID() const                             { return ( ReadInteger( tblSLD_Fields[0] ) ); }
//    bool FASTCALL DOCID_IsNull() const                        { return ( IsNull( tblSLD_Fields[0] ) ); }
//
//    int FASTCALL GetDOTID() const                             { return ( ReadInteger( tblSLD_Fields[1] ) ); }
//    bool FASTCALL DOTID_IsNull() const                        { return ( IsNull( tblSLD_Fields[1] ) ); }
//
//    int FASTCALL GetFIYID() const                             { return ( ReadInteger( tblSLD_Fields[2] ) ); }
//    bool FASTCALL FIYID_IsNull() const                        { return ( IsNull( tblSLD_Fields[2] ) ); }
//
//    int FASTCALL GetPERID() const                             { return ( ReadInteger( tblSLD_Fields[3] ) ); }
//    bool FASTCALL PERID_IsNull() const                        { return ( IsNull( tblSLD_Fields[3] ) ); }
//
//    int FASTCALL GetDOSID() const                             { return ( ReadInteger( tblSLD_Fields[4] ) ); }
//    bool FASTCALL DOSID_IsNull() const                        { return ( IsNull( tblSLD_Fields[4] ) ); }
//
//    ds_string FASTCALL GetDOSCODE() const                     { return ( ReadString( tblSLD_Fields[5] ) ); }
//    bool FASTCALL DOSCODE_IsNull() const                      { return ( IsNull( tblSLD_Fields[5] ) ); }
//
//    int FASTCALL GetDOCNUMBER() const                         { return ( ReadInteger( tblSLD_Fields[6] ) ); }
//    bool FASTCALL DOCNUMBER_IsNull() const                    { return ( IsNull( tblSLD_Fields[6] ) ); }
//
//    int FASTCALL GetDOCJRNAA() const                          { return ( ReadInteger( tblSLD_Fields[7] ) ); }
//    bool FASTCALL DOCJRNAA_IsNull() const                     { return ( IsNull( tblSLD_Fields[7] ) ); }
//
//    smds::cDateTime FASTCALL GetDOCKATAHORISISDATE() const    { return ( ReadDate( tblSLD_Fields[8] ) ); }
//    bool FASTCALL DOCKATAHORISISDATE_IsNull() const           { return ( IsNull( tblSLD_Fields[8] ) ); }
//
//    smds::cDateTime FASTCALL GetDOCENIMEROSISDATE() const     { return ( ReadDate( tblSLD_Fields[9] ) ); }
//    bool FASTCALL DOCENIMEROSISDATE_IsNull() const            { return ( IsNull( tblSLD_Fields[9] ) ); }
//
//    smds::cDateTime FASTCALL GetDOCEKDOSISDATE() const        { return ( ReadDate( tblSLD_Fields[10] ) ); }
//    bool FASTCALL DOCEKDOSISDATE_IsNull() const               { return ( IsNull( tblSLD_Fields[10] ) ); }
//
//    ds_string FASTCALL GetDOCREASON() const                   { return ( ReadString( tblSLD_Fields[11] ) ); }
//    bool FASTCALL DOCREASON_IsNull() const                    { return ( IsNull( tblSLD_Fields[11] ) ); }
//
//    ds_string FASTCALL GetDOCCOMMENT() const                  { return ( ReadString( tblSLD_Fields[12] ) ); }
//    bool FASTCALL DOCCOMMENT_IsNull() const                   { return ( IsNull( tblSLD_Fields[12] ) ); }
//
//    short FASTCALL GetDOCCANENIM() const                      { return ( ReadShort( tblSLD_Fields[13] ) ); }
//    bool FASTCALL DOCCANENIM_IsNull() const                   { return ( IsNull( tblSLD_Fields[13] ) ); }
//
//    short FASTCALL GetDOCCANCANCEL() const                    { return ( ReadShort( tblSLD_Fields[14] ) ); }
//    bool FASTCALL DOCCANCANCEL_IsNull() const                 { return ( IsNull( tblSLD_Fields[14] ) ); }
//
//    ds_string FASTCALL GetDOCCANCELSTATUS() const             { return ( ReadString( tblSLD_Fields[15] ) ); }
//    bool FASTCALL DOCCANCELSTATUS_IsNull() const              { return ( IsNull( tblSLD_Fields[15] ) ); }
//
//    int FASTCALL GetDOCIDAKIROMENO() const                    { return ( ReadInteger( tblSLD_Fields[16] ) ); }
//    bool FASTCALL DOCIDAKIROMENO_IsNull() const               { return ( IsNull( tblSLD_Fields[16] ) ); }
//
//    int FASTCALL GetDOCIDAKIROTIKO() const                    { return ( ReadInteger( tblSLD_Fields[17] ) ); }
//    bool FASTCALL DOCIDAKIROTIKO_IsNull() const               { return ( IsNull( tblSLD_Fields[17] ) ); }
//
//    int FASTCALL GetDMIID() const                             { return ( ReadInteger( tblSLD_Fields[18] ) ); }
//    bool FASTCALL DMIID_IsNull() const                        { return ( IsNull( tblSLD_Fields[18] ) ); }
//
//    short FASTCALL GetTDOGROSSRETAIL() const                  { return ( ReadShort( tblSLD_Fields[19] ) ); }
//    bool FASTCALL TDOGROSSRETAIL_IsNull() const               { return ( IsNull( tblSLD_Fields[19] ) ); }
//
//    ds_string FASTCALL GetTDOOTHERNUMBER() const              { return ( ReadString( tblSLD_Fields[20] ) ); }
//    bool FASTCALL TDOOTHERNUMBER_IsNull() const               { return ( IsNull( tblSLD_Fields[20] ) ); }
//
//    smds::cDateTime FASTCALL GetTDOOTHERDATE() const          { return ( ReadDate( tblSLD_Fields[21] ) ); }
//    bool FASTCALL TDOOTHERDATE_IsNull() const                 { return ( IsNull( tblSLD_Fields[21] ) ); }
//
//    smds::cDateTime FASTCALL GetTDOEKTELESISDATE() const      { return ( ReadDate( tblSLD_Fields[22] ) ); }
//    bool FASTCALL TDOEKTELESISDATE_IsNull() const             { return ( IsNull( tblSLD_Fields[22] ) ); }
//
//    ds_string FASTCALL GetDSTDESCR() const                    { return ( ReadString( tblSLD_Fields[23] ) ); }
//    bool FASTCALL DSTDESCR_IsNull() const                     { return ( IsNull( tblSLD_Fields[23] ) ); }
//
//    ds_string FASTCALL GetPPSDESCR() const                    { return ( ReadString( tblSLD_Fields[24] ) ); }
//    bool FASTCALL PPSDESCR_IsNull() const                     { return ( IsNull( tblSLD_Fields[24] ) ); }
//
//    ds_string FASTCALL GetORGDESCR() const                    { return ( ReadString( tblSLD_Fields[25] ) ); }
//    bool FASTCALL ORGDESCR_IsNull() const                     { return ( IsNull( tblSLD_Fields[25] ) ); }
//
//    int FASTCALL GetTPMID() const                             { return ( ReadInteger( tblSLD_Fields[26] ) ); }
//    bool FASTCALL TPMID_IsNull() const                        { return ( IsNull( tblSLD_Fields[26] ) ); }
//
//    int FASTCALL GetTPTID() const                             { return ( ReadInteger( tblSLD_Fields[27] ) ); }
//    bool FASTCALL TPTID_IsNull() const                        { return ( IsNull( tblSLD_Fields[27] ) ); }
//
//    int FASTCALL GetSHVID() const                             { return ( ReadInteger( tblSLD_Fields[28] ) ); }
//    bool FASTCALL SHVID_IsNull() const                        { return ( IsNull( tblSLD_Fields[28] ) ); }
//
//    int FASTCALL GetWRHID() const                             { return ( ReadInteger( tblSLD_Fields[29] ) ); }
//    bool FASTCALL WRHID_IsNull() const                        { return ( IsNull( tblSLD_Fields[29] ) ); }
//
//    int FASTCALL GetTRAID() const                             { return ( ReadInteger( tblSLD_Fields[30] ) ); }
//    bool FASTCALL TRAID_IsNull() const                        { return ( IsNull( tblSLD_Fields[30] ) ); }
//
//    ds_string FASTCALL GetTXOCODE() const                     { return ( ReadString( tblSLD_Fields[31] ) ); }
//    bool FASTCALL TXOCODE_IsNull() const                      { return ( IsNull( tblSLD_Fields[31] ) ); }
//
//    ds_string FASTCALL GetTDOTRANSPORTREMARKS() const         { return ( ReadString( tblSLD_Fields[32] ) ); }
//    bool FASTCALL TDOTRANSPORTREMARKS_IsNull() const          { return ( IsNull( tblSLD_Fields[32] ) ); }
//
//    int FASTCALL GetADRIDLOGISTIRIOU() const                  { return ( ReadInteger( tblSLD_Fields[33] ) ); }
//    bool FASTCALL ADRIDLOGISTIRIOU_IsNull() const             { return ( IsNull( tblSLD_Fields[33] ) ); }
//
//    int FASTCALL GetADRIDPROORISMOU() const                   { return ( ReadInteger( tblSLD_Fields[34] ) ); }
//    bool FASTCALL ADRIDPROORISMOU_IsNull() const              { return ( IsNull( tblSLD_Fields[34] ) ); }
//
//    smds::cDateTime FASTCALL GetTDOSENDTIME() const           { return ( ReadDate( tblSLD_Fields[35] ) ); }
//    bool FASTCALL TDOSENDTIME_IsNull() const                  { return ( IsNull( tblSLD_Fields[35] ) ); }
//
//    ds_string FASTCALL GetTDOVATSTATUS() const                { return ( ReadString( tblSLD_Fields[36] ) ); }
//    bool FASTCALL TDOVATSTATUS_IsNull() const                 { return ( IsNull( tblSLD_Fields[36] ) ); }
//
//    ds_string FASTCALL GetTDOLEEAFM() const                   { return ( ReadString( tblSLD_Fields[37] ) ); }
//    bool FASTCALL TDOLEEAFM_IsNull() const                    { return ( IsNull( tblSLD_Fields[37] ) ); }
//
//    ds_string FASTCALL GetTDOLEEADT() const                   { return ( ReadString( tblSLD_Fields[38] ) ); }
//    bool FASTCALL TDOLEEADT_IsNull() const                    { return ( IsNull( tblSLD_Fields[38] ) ); }
//
//    ds_string FASTCALL GetTDOLEEADTKIND() const               { return ( ReadString( tblSLD_Fields[39] ) ); }
//    bool FASTCALL TDOLEEADTKIND_IsNull() const                { return ( IsNull( tblSLD_Fields[39] ) ); }
//
//    ds_string FASTCALL GetTDOADDRESS() const                  { return ( ReadString( tblSLD_Fields[40] ) ); }
//    bool FASTCALL TDOADDRESS_IsNull() const                   { return ( IsNull( tblSLD_Fields[40] ) ); }
//
//    int FASTCALL GetCURID() const                             { return ( ReadInteger( tblSLD_Fields[41] ) ); }
//    bool FASTCALL CURID_IsNull() const                        { return ( IsNull( tblSLD_Fields[41] ) ); }
//
//    ds_string FASTCALL GetTDOEQVTYPE() const                  { return ( ReadString( tblSLD_Fields[42] ) ); }
//    bool FASTCALL TDOEQVTYPE_IsNull() const                   { return ( IsNull( tblSLD_Fields[42] ) ); }
//
//    double FASTCALL GetTDOEQUIVALENCE() const                 { return ( ReadFloat( tblSLD_Fields[43] ) ); }
//    bool FASTCALL TDOEQUIVALENCE_IsNull() const               { return ( IsNull( tblSLD_Fields[43] ) ); }
//
//    int FASTCALL GetTDODUEDAYS() const                        { return ( ReadInteger( tblSLD_Fields[44] ) ); }
//    bool FASTCALL TDODUEDAYS_IsNull() const                   { return ( IsNull( tblSLD_Fields[44] ) ); }
//
//    int FASTCALL GetTDOGRACEDAYS() const                      { return ( ReadInteger( tblSLD_Fields[45] ) ); }
//    bool FASTCALL TDOGRACEDAYS_IsNull() const                 { return ( IsNull( tblSLD_Fields[45] ) ); }
//
//    int FASTCALL GetSLMID() const                             { return ( ReadInteger( tblSLD_Fields[46] ) ); }
//    bool FASTCALL SLMID_IsNull() const                        { return ( IsNull( tblSLD_Fields[46] ) ); }
//
//    double FASTCALL GetTDOTRADERDISCPCNT() const              { return ( ReadFloat( tblSLD_Fields[47] ) ); }
//    bool FASTCALL TDOTRADERDISCPCNT_IsNull() const            { return ( IsNull( tblSLD_Fields[47] ) ); }
//
//    double FASTCALL GetTDOQTYA() const                        { return ( ReadFloat( tblSLD_Fields[48] ) ); }
//    bool FASTCALL TDOQTYA_IsNull() const                      { return ( IsNull( tblSLD_Fields[48] ) ); }
//
//    double FASTCALL GetTDOQTYB() const                        { return ( ReadFloat( tblSLD_Fields[49] ) ); }
//    bool FASTCALL TDOQTYB_IsNull() const                      { return ( IsNull( tblSLD_Fields[49] ) ); }
//
//    double FASTCALL GetTDOTRANSFQTYA() const                  { return ( ReadFloat( tblSLD_Fields[50] ) ); }
//    bool FASTCALL TDOTRANSFQTYA_IsNull() const                { return ( IsNull( tblSLD_Fields[50] ) ); }
//
//    double FASTCALL GetTDOTRANSFQTYB() const                  { return ( ReadFloat( tblSLD_Fields[51] ) ); }
//    bool FASTCALL TDOTRANSFQTYB_IsNull() const                { return ( IsNull( tblSLD_Fields[51] ) ); }
//
//    double FASTCALL GetTDOQTYDISCA() const                    { return ( ReadFloat( tblSLD_Fields[52] ) ); }
//    bool FASTCALL TDOQTYDISCA_IsNull() const                  { return ( IsNull( tblSLD_Fields[52] ) ); }
//
//    double FASTCALL GetTDOQTYDISCB() const                    { return ( ReadFloat( tblSLD_Fields[53] ) ); }
//    bool FASTCALL TDOQTYDISCB_IsNull() const                  { return ( IsNull( tblSLD_Fields[53] ) ); }
//
//    double FASTCALL GetTDOTRADERDISC() const                  { return ( ReadFloat( tblSLD_Fields[54] ) ); }
//    bool FASTCALL TDOTRADERDISC_IsNull() const                { return ( IsNull( tblSLD_Fields[54] ) ); }
//
//    double FASTCALL GetTDOTRADERDISCBC() const                { return ( ReadFloat( tblSLD_Fields[55] ) ); }
//    bool FASTCALL TDOTRADERDISCBC_IsNull() const              { return ( IsNull( tblSLD_Fields[55] ) ); }
//
//    double FASTCALL GetTDOPAYMENTDISC() const                 { return ( ReadFloat( tblSLD_Fields[56] ) ); }
//    bool FASTCALL TDOPAYMENTDISC_IsNull() const               { return ( IsNull( tblSLD_Fields[56] ) ); }
//
//    double FASTCALL GetTDOPAYMENTDISCBC() const               { return ( ReadFloat( tblSLD_Fields[57] ) ); }
//    bool FASTCALL TDOPAYMENTDISCBC_IsNull() const             { return ( IsNull( tblSLD_Fields[57] ) ); }
//
//    double FASTCALL GetTDOSTOCKDISC() const                   { return ( ReadFloat( tblSLD_Fields[58] ) ); }
//    bool FASTCALL TDOSTOCKDISC_IsNull() const                 { return ( IsNull( tblSLD_Fields[58] ) ); }
//
//    double FASTCALL GetTDOSTOCKDISCBC() const                 { return ( ReadFloat( tblSLD_Fields[59] ) ); }
//    bool FASTCALL TDOSTOCKDISCBC_IsNull() const               { return ( IsNull( tblSLD_Fields[59] ) ); }
//
//    double FASTCALL GetTDOPRICELISTDISC() const               { return ( ReadFloat( tblSLD_Fields[60] ) ); }
//    bool FASTCALL TDOPRICELISTDISC_IsNull() const             { return ( IsNull( tblSLD_Fields[60] ) ); }
//
//    double FASTCALL GetTDOPRICELISTDISCBC() const             { return ( ReadFloat( tblSLD_Fields[61] ) ); }
//    bool FASTCALL TDOPRICELISTDISCBC_IsNull() const           { return ( IsNull( tblSLD_Fields[61] ) ); }
//
//    double FASTCALL GetTDOEXTRADISC() const                   { return ( ReadFloat( tblSLD_Fields[62] ) ); }
//    bool FASTCALL TDOEXTRADISC_IsNull() const                 { return ( IsNull( tblSLD_Fields[62] ) ); }
//
//    double FASTCALL GetTDOEXTRADISCBC() const                 { return ( ReadFloat( tblSLD_Fields[63] ) ); }
//    bool FASTCALL TDOEXTRADISCBC_IsNull() const               { return ( IsNull( tblSLD_Fields[63] ) ); }
//
//    double FASTCALL GetTDONETSTOCK() const                    { return ( ReadFloat( tblSLD_Fields[64] ) ); }
//    bool FASTCALL TDONETSTOCK_IsNull() const                  { return ( IsNull( tblSLD_Fields[64] ) ); }
//
//    double FASTCALL GetTDONETSTOCKBC() const                  { return ( ReadFloat( tblSLD_Fields[65] ) ); }
//    bool FASTCALL TDONETSTOCKBC_IsNull() const                { return ( IsNull( tblSLD_Fields[65] ) ); }
//
//    double FASTCALL GetTDONETGIFT() const                     { return ( ReadFloat( tblSLD_Fields[66] ) ); }
//    bool FASTCALL TDONETGIFT_IsNull() const                   { return ( IsNull( tblSLD_Fields[66] ) ); }
//
//    double FASTCALL GetTDONETGIFTBC() const                   { return ( ReadFloat( tblSLD_Fields[67] ) ); }
//    bool FASTCALL TDONETGIFTBC_IsNull() const                 { return ( IsNull( tblSLD_Fields[67] ) ); }
//
//    double FASTCALL GetTDONETSURCHARGE() const                { return ( ReadFloat( tblSLD_Fields[68] ) ); }
//    bool FASTCALL TDONETSURCHARGE_IsNull() const              { return ( IsNull( tblSLD_Fields[68] ) ); }
//
//    double FASTCALL GetTDONETSURCHARGEBC() const              { return ( ReadFloat( tblSLD_Fields[69] ) ); }
//    bool FASTCALL TDONETSURCHARGEBC_IsNull() const            { return ( IsNull( tblSLD_Fields[69] ) ); }
//
//    double FASTCALL GetTDONETOTHER() const                    { return ( ReadFloat( tblSLD_Fields[70] ) ); }
//    bool FASTCALL TDONETOTHER_IsNull() const                  { return ( IsNull( tblSLD_Fields[70] ) ); }
//
//    double FASTCALL GetTDONETOTHERBC() const                  { return ( ReadFloat( tblSLD_Fields[71] ) ); }
//    bool FASTCALL TDONETOTHERBC_IsNull() const                { return ( IsNull( tblSLD_Fields[71] ) ); }
//
//    double FASTCALL GetTDONETTAX() const                      { return ( ReadFloat( tblSLD_Fields[72] ) ); }
//    bool FASTCALL TDONETTAX_IsNull() const                    { return ( IsNull( tblSLD_Fields[72] ) ); }
//
//    double FASTCALL GetTDONETTAXBC() const                    { return ( ReadFloat( tblSLD_Fields[73] ) ); }
//    bool FASTCALL TDONETTAXBC_IsNull() const                  { return ( IsNull( tblSLD_Fields[73] ) ); }
//
//    double FASTCALL GetTDOGROSSVALUE() const                  { return ( ReadFloat( tblSLD_Fields[74] ) ); }
//    bool FASTCALL TDOGROSSVALUE_IsNull() const                { return ( IsNull( tblSLD_Fields[74] ) ); }
//
//    double FASTCALL GetTDOGROSSVALUEBC() const                { return ( ReadFloat( tblSLD_Fields[75] ) ); }
//    bool FASTCALL TDOGROSSVALUEBC_IsNull() const              { return ( IsNull( tblSLD_Fields[75] ) ); }
//
//    double FASTCALL GetTDOVATSTOCK() const                    { return ( ReadFloat( tblSLD_Fields[76] ) ); }
//    bool FASTCALL TDOVATSTOCK_IsNull() const                  { return ( IsNull( tblSLD_Fields[76] ) ); }
//
//    double FASTCALL GetTDOVATSTOCKBC() const                  { return ( ReadFloat( tblSLD_Fields[77] ) ); }
//    bool FASTCALL TDOVATSTOCKBC_IsNull() const                { return ( IsNull( tblSLD_Fields[77] ) ); }
//
//    double FASTCALL GetTDOVATGIFT() const                     { return ( ReadFloat( tblSLD_Fields[78] ) ); }
//    bool FASTCALL TDOVATGIFT_IsNull() const                   { return ( IsNull( tblSLD_Fields[78] ) ); }
//
//    double FASTCALL GetTDOVATGIFTBC() const                   { return ( ReadFloat( tblSLD_Fields[79] ) ); }
//    bool FASTCALL TDOVATGIFTBC_IsNull() const                 { return ( IsNull( tblSLD_Fields[79] ) ); }
//
//    double FASTCALL GetTDOVATSURCHARGE() const                { return ( ReadFloat( tblSLD_Fields[80] ) ); }
//    bool FASTCALL TDOVATSURCHARGE_IsNull() const              { return ( IsNull( tblSLD_Fields[80] ) ); }
//
//    double FASTCALL GetTDOVATSURCHARGEBC() const              { return ( ReadFloat( tblSLD_Fields[81] ) ); }
//    bool FASTCALL TDOVATSURCHARGEBC_IsNull() const            { return ( IsNull( tblSLD_Fields[81] ) ); }
//
//    double FASTCALL GetTDOVATOTHER() const                    { return ( ReadFloat( tblSLD_Fields[82] ) ); }
//    bool FASTCALL TDOVATOTHER_IsNull() const                  { return ( IsNull( tblSLD_Fields[82] ) ); }
//
//    double FASTCALL GetTDOVATOTHERBC() const                  { return ( ReadFloat( tblSLD_Fields[83] ) ); }
//    bool FASTCALL TDOVATOTHERBC_IsNull() const                { return ( IsNull( tblSLD_Fields[83] ) ); }
//
//    double FASTCALL GetTDOVATTAX() const                      { return ( ReadFloat( tblSLD_Fields[84] ) ); }
//    bool FASTCALL TDOVATTAX_IsNull() const                    { return ( IsNull( tblSLD_Fields[84] ) ); }
//
//    double FASTCALL GetTDOVATTAXBC() const                    { return ( ReadFloat( tblSLD_Fields[85] ) ); }
//    bool FASTCALL TDOVATTAXBC_IsNull() const                  { return ( IsNull( tblSLD_Fields[85] ) ); }
//
//    int FASTCALL GetPTPIDPAYMENT() const                      { return ( ReadInteger( tblSLD_Fields[86] ) ); }
//    bool FASTCALL PTPIDPAYMENT_IsNull() const                 { return ( IsNull( tblSLD_Fields[86] ) ); }
//
//    int FASTCALL GetPMTIDPAYMENT() const                      { return ( ReadInteger( tblSLD_Fields[87] ) ); }
//    bool FASTCALL PMTIDPAYMENT_IsNull() const                 { return ( IsNull( tblSLD_Fields[87] ) ); }
//
//    int FASTCALL GetDOCIDPAYMENT() const                      { return ( ReadInteger( tblSLD_Fields[88] ) ); }
//    bool FASTCALL DOCIDPAYMENT_IsNull() const                 { return ( IsNull( tblSLD_Fields[88] ) ); }
//
//    double FASTCALL GetTDOPAYMENT() const                     { return ( ReadFloat( tblSLD_Fields[89] ) ); }
//    bool FASTCALL TDOPAYMENT_IsNull() const                   { return ( IsNull( tblSLD_Fields[89] ) ); }
//
//    double FASTCALL GetTDOPAYMENTBC() const                   { return ( ReadFloat( tblSLD_Fields[90] ) ); }
//    bool FASTCALL TDOPAYMENTBC_IsNull() const                 { return ( IsNull( tblSLD_Fields[90] ) ); }
//
//    double FASTCALL GetTDONETKRATISI() const                  { return ( ReadFloat( tblSLD_Fields[91] ) ); }
//    bool FASTCALL TDONETKRATISI_IsNull() const                { return ( IsNull( tblSLD_Fields[91] ) ); }
//
//    double FASTCALL GetTDONETKRATISIBC() const                { return ( ReadFloat( tblSLD_Fields[92] ) ); }
//    bool FASTCALL TDONETKRATISIBC_IsNull() const              { return ( IsNull( tblSLD_Fields[92] ) ); }
//
//    double FASTCALL GetTDOTRADERBALANCEBEFORE() const         { return ( ReadFloat( tblSLD_Fields[93] ) ); }
//    bool FASTCALL TDOTRADERBALANCEBEFORE_IsNull() const       { return ( IsNull( tblSLD_Fields[93] ) ); }
//
//    double FASTCALL GetTDOTRADERBALANCEAFTER() const          { return ( ReadFloat( tblSLD_Fields[94] ) ); }
//    bool FASTCALL TDOTRADERBALANCEAFTER_IsNull() const        { return ( IsNull( tblSLD_Fields[94] ) ); }
//
//    short FASTCALL GetTDOCANTRANSF() const                    { return ( ReadShort( tblSLD_Fields[95] ) ); }
//    bool FASTCALL TDOCANTRANSF_IsNull() const                 { return ( IsNull( tblSLD_Fields[95] ) ); }
//
//    double FASTCALL GetTDOADVANCE() const                     { return ( ReadFloat( tblSLD_Fields[96] ) ); }
//    bool FASTCALL TDOADVANCE_IsNull() const                   { return ( IsNull( tblSLD_Fields[96] ) ); }
//
//    double FASTCALL GetTDOADVANCEBC() const                   { return ( ReadFloat( tblSLD_Fields[97] ) ); }
//    bool FASTCALL TDOADVANCEBC_IsNull() const                 { return ( IsNull( tblSLD_Fields[97] ) ); }
//
//    double FASTCALL GetTDOADVANCEUSAGE() const                { return ( ReadFloat( tblSLD_Fields[98] ) ); }
//    bool FASTCALL TDOADVANCEUSAGE_IsNull() const              { return ( IsNull( tblSLD_Fields[98] ) ); }
//
//    double FASTCALL GetTDOADVANCEUSAGEBC() const              { return ( ReadFloat( tblSLD_Fields[99] ) ); }
//    bool FASTCALL TDOADVANCEUSAGEBC_IsNull() const            { return ( IsNull( tblSLD_Fields[99] ) ); }
//
//    int FASTCALL GetCDZID() const                             { return ( ReadInteger( tblSLD_Fields[100] ) ); }
//    bool FASTCALL CDZID_IsNull() const                        { return ( IsNull( tblSLD_Fields[100] ) ); }
//
//    int FASTCALL GetPTPIDDOCTYPE() const                      { return ( ReadInteger( tblSLD_Fields[101] ) ); }
//    bool FASTCALL PTPIDDOCTYPE_IsNull() const                 { return ( IsNull( tblSLD_Fields[101] ) ); }
//
//    int FASTCALL GetLEEIDRECEIVER() const                     { return ( ReadInteger( tblSLD_Fields[102] ) ); }
//    bool FASTCALL LEEIDRECEIVER_IsNull() const                { return ( IsNull( tblSLD_Fields[102] ) ); }
//
//    int FASTCALL GetADRIDRECEIVER() const                     { return ( ReadInteger( tblSLD_Fields[103] ) ); }
//    bool FASTCALL ADRIDRECEIVER_IsNull() const                { return ( IsNull( tblSLD_Fields[103] ) ); }
//
//    int FASTCALL GetPMTIDADVANCE() const                      { return ( ReadInteger( tblSLD_Fields[104] ) ); }
//    bool FASTCALL PMTIDADVANCE_IsNull() const                 { return ( IsNull( tblSLD_Fields[104] ) ); }
//
//    int FASTCALL GetDOCIDADVANCE() const                      { return ( ReadInteger( tblSLD_Fields[105] ) ); }
//    bool FASTCALL DOCIDADVANCE_IsNull() const                 { return ( IsNull( tblSLD_Fields[105] ) ); }
//
//    double FASTCALL GetTDOPAYMENTDISCPCNT() const             { return ( ReadFloat( tblSLD_Fields[106] ) ); }
//    bool FASTCALL TDOPAYMENTDISCPCNT_IsNull() const           { return ( IsNull( tblSLD_Fields[106] ) ); }
//
//    int FASTCALL GetTTYIDTRADER() const                       { return ( ReadInteger( tblSLD_Fields[107] ) ); }
//    bool FASTCALL TTYIDTRADER_IsNull() const                  { return ( IsNull( tblSLD_Fields[107] ) ); }
//
//    int FASTCALL GetTTYIDSALESMAN() const                     { return ( ReadInteger( tblSLD_Fields[108] ) ); }
//    bool FASTCALL TTYIDSALESMAN_IsNull() const                { return ( IsNull( tblSLD_Fields[108] ) ); }
//
//    int FASTCALL GetTTYIDSTOCKITEM() const                    { return ( ReadInteger( tblSLD_Fields[109] ) ); }
//    bool FASTCALL TTYIDSTOCKITEM_IsNull() const               { return ( IsNull( tblSLD_Fields[109] ) ); }
//
//    short FASTCALL GetTDOVATINCLUDED() const                  { return ( ReadShort( tblSLD_Fields[110] ) ); }
//    bool FASTCALL TDOVATINCLUDED_IsNull() const               { return ( IsNull( tblSLD_Fields[110] ) ); }
//
//    int FASTCALL GetPTPIDTRADER() const                       { return ( ReadInteger( tblSLD_Fields[111] ) ); }
//    bool FASTCALL PTPIDTRADER_IsNull() const                  { return ( IsNull( tblSLD_Fields[111] ) ); }
//
//    int FASTCALL GetSYS_USRID() const                         { return ( ReadInteger( tblSLD_Fields[112] ) ); }
//    bool FASTCALL SYS_USRID_IsNull() const                    { return ( IsNull( tblSLD_Fields[112] ) ); }
//
//    smds::cDateTime FASTCALL GetSYS_LUPD() const              { return ( ReadDate( tblSLD_Fields[113] ) ); }
//    bool FASTCALL SYS_LUPD_IsNull() const                     { return ( IsNull( tblSLD_Fields[113] ) ); }
//
//    smds::cDateTime FASTCALL GetSYS_INS() const               { return ( ReadDate( tblSLD_Fields[114] ) ); }
//    bool FASTCALL SYS_INS_IsNull() const                      { return ( IsNull( tblSLD_Fields[114] ) ); }
//
//    ds_string FASTCALL GetTDOKEEPPRICESTRANSF() const         { return ( ReadString( tblSLD_Fields[115] ) ); }
//    bool FASTCALL TDOKEEPPRICESTRANSF_IsNull() const          { return ( IsNull( tblSLD_Fields[115] ) ); }
//
//    double FASTCALL GetTDOTRADERBALANCEBEFOREBC() const       { return ( ReadFloat( tblSLD_Fields[116] ) ); }
//    bool FASTCALL TDOTRADERBALANCEBEFOREBC_IsNull() const     { return ( IsNull( tblSLD_Fields[116] ) ); }
//
//    double FASTCALL GetTDOTRADERBALANCEAFTERBC() const        { return ( ReadFloat( tblSLD_Fields[117] ) ); }
//    bool FASTCALL TDOTRADERBALANCEAFTERBC_IsNull() const      { return ( IsNull( tblSLD_Fields[117] ) ); }
//
//    int FASTCALL GetSLMIDCOLLECTOR() const                    { return ( ReadInteger( tblSLD_Fields[118] ) ); }
//    bool FASTCALL SLMIDCOLLECTOR_IsNull() const               { return ( IsNull( tblSLD_Fields[118] ) ); }
//
//    int FASTCALL GetDOCIDPREDICTION() const                   { return ( ReadInteger( tblSLD_Fields[119] ) ); }
//    bool FASTCALL DOCIDPREDICTION_IsNull() const              { return ( IsNull( tblSLD_Fields[119] ) ); }
//
//    short FASTCALL GetTDOISPREDICTION() const                 { return ( ReadShort( tblSLD_Fields[120] ) ); }
//    bool FASTCALL TDOISPREDICTION_IsNull() const              { return ( IsNull( tblSLD_Fields[120] ) ); }
//
//    int FASTCALL GetTTYIDASSETITEM() const                    { return ( ReadInteger( tblSLD_Fields[121] ) ); }
//    bool FASTCALL TTYIDASSETITEM_IsNull() const               { return ( IsNull( tblSLD_Fields[121] ) ); }
//
//    double FASTCALL GetTDOAUDITEQUIVALENCE() const            { return ( ReadFloat( tblSLD_Fields[122] ) ); }
//    bool FASTCALL TDOAUDITEQUIVALENCE_IsNull() const          { return ( IsNull( tblSLD_Fields[122] ) ); }
//
//    short FASTCALL GetTDOAUDITEQVONEBASED() const             { return ( ReadShort( tblSLD_Fields[123] ) ); }
//    bool FASTCALL TDOAUDITEQVONEBASED_IsNull() const          { return ( IsNull( tblSLD_Fields[123] ) ); }
//
//    double FASTCALL GetTDODASMEQUIVALENCE() const             { return ( ReadFloat( tblSLD_Fields[124] ) ); }
//    bool FASTCALL TDODASMEQUIVALENCE_IsNull() const           { return ( IsNull( tblSLD_Fields[124] ) ); }
//
//    int FASTCALL GetSLDCASHIER() const                        { return ( ReadInteger( tblSLD_Fields[125] ) ); }
//    bool FASTCALL SLDCASHIER_IsNull() const                   { return ( IsNull( tblSLD_Fields[125] ) ); }
//
//    int FASTCALL GetVERID() const                             { return ( ReadInteger( tblSLD_Fields[126] ) ); }
//    bool FASTCALL VERID_IsNull() const                        { return ( IsNull( tblSLD_Fields[126] ) ); }
//
//    double FASTCALL GetSLDDISCOUNTPOLICY() const              { return ( ReadFloat( tblSLD_Fields[127] ) ); }
//    bool FASTCALL SLDDISCOUNTPOLICY_IsNull() const            { return ( IsNull( tblSLD_Fields[127] ) ); }
//
//    double FASTCALL GetSLDDISCOUNTPOLICYBC() const            { return ( ReadFloat( tblSLD_Fields[128] ) ); }
//    bool FASTCALL SLDDISCOUNTPOLICYBC_IsNull() const          { return ( IsNull( tblSLD_Fields[128] ) ); }
//
//    double FASTCALL GetTDODETAILTRMTOTAL() const              { return ( ReadFloat( tblSLD_Fields[129] ) ); }
//    bool FASTCALL TDODETAILTRMTOTAL_IsNull() const            { return ( IsNull( tblSLD_Fields[129] ) ); }
//
//    double FASTCALL GetTDODETAILTRMTOTALBC() const            { return ( ReadFloat( tblSLD_Fields[130] ) ); }
//    bool FASTCALL TDODETAILTRMTOTALBC_IsNull() const          { return ( IsNull( tblSLD_Fields[130] ) ); }
//
//    int FASTCALL GetCONID() const                             { return ( ReadInteger( tblSLD_Fields[131] ) ); }
//    bool FASTCALL CONID_IsNull() const                        { return ( IsNull( tblSLD_Fields[131] ) ); }
//
//    int FASTCALL GetDOCIDTRIANGLE() const                     { return ( ReadInteger( tblSLD_Fields[132] ) ); }
//    bool FASTCALL DOCIDTRIANGLE_IsNull() const                { return ( IsNull( tblSLD_Fields[132] ) ); }
//
//    short FASTCALL GetTRIANGLESUBSYSID() const                { return ( ReadShort( tblSLD_Fields[133] ) ); }
//    bool FASTCALL TRIANGLESUBSYSID_IsNull() const             { return ( IsNull( tblSLD_Fields[133] ) ); }
//
//    int FASTCALL GetDOCIDTRIANGLEFROM() const                 { return ( ReadInteger( tblSLD_Fields[134] ) ); }
//    bool FASTCALL DOCIDTRIANGLEFROM_IsNull() const            { return ( IsNull( tblSLD_Fields[134] ) ); }
//
//    short FASTCALL GetTRIANGLESUBSYSIDFROM() const            { return ( ReadShort( tblSLD_Fields[135] ) ); }
//    bool FASTCALL TRIANGLESUBSYSIDFROM_IsNull() const         { return ( IsNull( tblSLD_Fields[135] ) ); }
//
//    int FASTCALL GetTRAIDPRINCIPAL() const                    { return ( ReadInteger( tblSLD_Fields[136] ) ); }
//    bool FASTCALL TRAIDPRINCIPAL_IsNull() const               { return ( IsNull( tblSLD_Fields[136] ) ); }
//
//    int FASTCALL GetPRTID() const                             { return ( ReadInteger( tblSLD_Fields[137] ) ); }
//    bool FASTCALL PRTID_IsNull() const                        { return ( IsNull( tblSLD_Fields[137] ) ); }
//
//    int FASTCALL GetADRIDDELIVERY() const                     { return ( ReadInteger( tblSLD_Fields[138] ) ); }
//    bool FASTCALL ADRIDDELIVERY_IsNull() const                { return ( IsNull( tblSLD_Fields[138] ) ); }
//
//    smds::cDateTime FASTCALL GetSLDPROCESSDATE() const        { return ( ReadDate( tblSLD_Fields[139] ) ); }
//    bool FASTCALL SLDPROCESSDATE_IsNull() const               { return ( IsNull( tblSLD_Fields[139] ) ); }
//
//    int FASTCALL GetTDOCOLONNUMBER() const                    { return ( ReadInteger( tblSLD_Fields[140] ) ); }
//    bool FASTCALL TDOCOLONNUMBER_IsNull() const               { return ( IsNull( tblSLD_Fields[140] ) ); }
//
//    double FASTCALL GetTDOQTYAGUARANTEE() const               { return ( ReadFloat( tblSLD_Fields[141] ) ); }
//    bool FASTCALL TDOQTYAGUARANTEE_IsNull() const             { return ( IsNull( tblSLD_Fields[141] ) ); }
//
//    double FASTCALL GetTDOQTYBGUARANTEE() const               { return ( ReadFloat( tblSLD_Fields[142] ) ); }
//    bool FASTCALL TDOQTYBGUARANTEE_IsNull() const             { return ( IsNull( tblSLD_Fields[142] ) ); }
//
//    double FASTCALL GetTDOGUARANTEERECEIVEDVALUE() const      { return ( ReadFloat( tblSLD_Fields[143] ) ); }
//    bool FASTCALL TDOGUARANTEERECEIVEDVALUE_IsNull() const    { return ( IsNull( tblSLD_Fields[143] ) ); }
//
//    double FASTCALL GetTDOGUARANTEERECEIVEDVALUEBC() const    { return ( ReadFloat( tblSLD_Fields[144] ) ); }
//    bool FASTCALL TDOGUARANTEERECEIVEDVALUEBC_IsNull() const  { return ( IsNull( tblSLD_Fields[144] ) ); }
//
//    double FASTCALL GetTDOGUARANTEERETURNEDVALUE() const      { return ( ReadFloat( tblSLD_Fields[145] ) ); }
//    bool FASTCALL TDOGUARANTEERETURNEDVALUE_IsNull() const    { return ( IsNull( tblSLD_Fields[145] ) ); }
//
//    double FASTCALL GetTDOGUARANTEERETURNEDVALUEBC() const    { return ( ReadFloat( tblSLD_Fields[146] ) ); }
//    bool FASTCALL TDOGUARANTEERETURNEDVALUEBC_IsNull() const  { return ( IsNull( tblSLD_Fields[146] ) ); }
//
//    int FASTCALL GetTTYIDTRADERGUARANTEE() const              { return ( ReadInteger( tblSLD_Fields[147] ) ); }
//    bool FASTCALL TTYIDTRADERGUARANTEE_IsNull() const         { return ( IsNull( tblSLD_Fields[147] ) ); }
//
//    int FASTCALL GetTTYIDSTOCKITEMGUARANTEE() const           { return ( ReadInteger( tblSLD_Fields[148] ) ); }
//    bool FASTCALL TTYIDSTOCKITEMGUARANTEE_IsNull() const      { return ( IsNull( tblSLD_Fields[148] ) ); }
//
//    int FASTCALL GetADRIDBRANCH() const                       { return ( ReadInteger( tblSLD_Fields[149] ) ); }
//    bool FASTCALL ADRIDBRANCH_IsNull() const                  { return ( IsNull( tblSLD_Fields[149] ) ); }
//
//    short FASTCALL GetTDOTRANSFORMEDCANCELED() const          { return ( ReadShort( tblSLD_Fields[150] ) ); }
//    bool FASTCALL TDOTRANSFORMEDCANCELED_IsNull() const       { return ( IsNull( tblSLD_Fields[150] ) ); }
//
//    short FASTCALL GetTDOTRADERTRANSSIGN() const              { return ( ReadShort( tblSLD_Fields[151] ) ); }
//    bool FASTCALL TDOTRADERTRANSSIGN_IsNull() const           { return ( IsNull( tblSLD_Fields[151] ) ); }
//
//    short FASTCALL GetTDOGUARANTEETRADERTRANSSIGN() const     { return ( ReadShort( tblSLD_Fields[152] ) ); }
//    bool FASTCALL TDOGUARANTEETRADERTRANSSIGN_IsNull() const  { return ( IsNull( tblSLD_Fields[152] ) ); }
//
//    double FASTCALL GetTDOPOLICYDISCOUNT() const              { return ( ReadFloat( tblSLD_Fields[153] ) ); }
//    bool FASTCALL TDOPOLICYDISCOUNT_IsNull() const            { return ( IsNull( tblSLD_Fields[153] ) ); }
//
//    double FASTCALL GetTDOPOLICYDISCOUNTBC() const            { return ( ReadFloat( tblSLD_Fields[154] ) ); }
//    bool FASTCALL TDOPOLICYDISCOUNTBC_IsNull() const          { return ( IsNull( tblSLD_Fields[154] ) ); }
//
//    double FASTCALL GetTDOTRANSDISCOUNT() const               { return ( ReadFloat( tblSLD_Fields[155] ) ); }
//    bool FASTCALL TDOTRANSDISCOUNT_IsNull() const             { return ( IsNull( tblSLD_Fields[155] ) ); }
//
//    double FASTCALL GetTDOTRANSDISCOUNTBC() const             { return ( ReadFloat( tblSLD_Fields[156] ) ); }
//    bool FASTCALL TDOTRANSDISCOUNTBC_IsNull() const           { return ( IsNull( tblSLD_Fields[156] ) ); }
//
//    int FASTCALL GetDIPIDTRANSACTION() const                  { return ( ReadInteger( tblSLD_Fields[157] ) ); }
//    bool FASTCALL DIPIDTRANSACTION_IsNull() const             { return ( IsNull( tblSLD_Fields[157] ) ); }
//
//    int FASTCALL GetBRAID() const                             { return ( ReadInteger( tblSLD_Fields[158] ) ); }
//    bool FASTCALL BRAID_IsNull() const                        { return ( IsNull( tblSLD_Fields[158] ) ); }
//
//    int FASTCALL GetTRMID() const                             { return ( ReadInteger( tblSLD_Fields[159] ) ); }
//    bool FASTCALL TRMID_IsNull() const                        { return ( IsNull( tblSLD_Fields[159] ) ); }
//
//    short FASTCALL GetTDOCOPYTRMID() const                    { return ( ReadShort( tblSLD_Fields[160] ) ); }
//    bool FASTCALL TDOCOPYTRMID_IsNull() const                 { return ( IsNull( tblSLD_Fields[160] ) ); }
//
//    smds::cDateTime FASTCALL GetTDOPAYMENTSTARTDATE() const   { return ( ReadDate( tblSLD_Fields[161] ) ); }
//    bool FASTCALL TDOPAYMENTSTARTDATE_IsNull() const          { return ( IsNull( tblSLD_Fields[161] ) ); }
//
//    int FASTCALL GetTDOACCEPTDAYS() const                     { return ( ReadInteger( tblSLD_Fields[162] ) ); }
//    bool FASTCALL TDOACCEPTDAYS_IsNull() const                { return ( IsNull( tblSLD_Fields[162] ) ); }
//
//    int FASTCALL GetTDODRIVECURID() const                     { return ( ReadInteger( tblSLD_Fields[163] ) ); }
//    bool FASTCALL TDODRIVECURID_IsNull() const                { return ( IsNull( tblSLD_Fields[163] ) ); }
//
//    int FASTCALL GetTDOTRADERCURID() const                    { return ( ReadInteger( tblSLD_Fields[164] ) ); }
//    bool FASTCALL TDOTRADERCURID_IsNull() const               { return ( IsNull( tblSLD_Fields[164] ) ); }
//
//    double FASTCALL GetTDOTRADEREQUIVALENCE() const           { return ( ReadFloat( tblSLD_Fields[165] ) ); }
//    bool FASTCALL TDOTRADEREQUIVALENCE_IsNull() const         { return ( IsNull( tblSLD_Fields[165] ) ); }
//
//    ds_string FASTCALL GetTDOTRADEREQVTYPE() const            { return ( ReadString( tblSLD_Fields[166] ) ); }
//    bool FASTCALL TDOTRADEREQVTYPE_IsNull() const             { return ( IsNull( tblSLD_Fields[166] ) ); }
//
//    double FASTCALL GetTDOTRADERAUDITEQUIVALENCE() const      { return ( ReadFloat( tblSLD_Fields[167] ) ); }
//    bool FASTCALL TDOTRADERAUDITEQUIVALENCE_IsNull() const    { return ( IsNull( tblSLD_Fields[167] ) ); }
//
//    short FASTCALL GetTDOTRAAUDITEQVONEBASED() const          { return ( ReadShort( tblSLD_Fields[168] ) ); }
//    bool FASTCALL TDOTRAAUDITEQVONEBASED_IsNull() const       { return ( IsNull( tblSLD_Fields[168] ) ); }
//
//    ds_string FASTCALL GetSLDDELIVERYPLACE() const            { return ( ReadString( tblSLD_Fields[169] ) ); }
//    bool FASTCALL SLDDELIVERYPLACE_IsNull() const             { return ( IsNull( tblSLD_Fields[169] ) ); }
//};
//
//class tblSLD_rec : public tblSLD_data, public smds::detail::cRecordPtr
//{
//public:
//    typedef tblSLD_raw    raw;
//public:
//    CDFASTCALL tblSLD_rec( smds::detail::DoubleBuffer& double_buffer )
//        : smds::detail::cRecordPtr(double_buffer)   {} // empty
//    tblSLD_rec * FASTCALL operator->()              { return ( this ); }
//    const tblSLD_rec * FASTCALL operator->() const  { return ( this ); }
//    static const smds::detail::cFieldDefs_& FASTCALL GetFieldDefs();
//
//    int FASTCALL GetDOCID() const                                         { return ( ReadInteger( tblSLD_Fields[0] ) ); }
//    bool FASTCALL DOCID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[0] ) ); }
//    void FASTCALL SetDOCID( int value )                                   { WriteInteger( tblSLD_Fields[0], value ); }
//
//    int FASTCALL GetDOTID() const                                         { return ( ReadInteger( tblSLD_Fields[1] ) ); }
//    bool FASTCALL DOTID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[1] ) ); }
//    void FASTCALL SetDOTID( int value )                                   { WriteInteger( tblSLD_Fields[1], value ); }
//
//    int FASTCALL GetFIYID() const                                         { return ( ReadInteger( tblSLD_Fields[2] ) ); }
//    bool FASTCALL FIYID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[2] ) ); }
//    void FASTCALL SetFIYID( int value )                                   { WriteInteger( tblSLD_Fields[2], value ); }
//
//    int FASTCALL GetPERID() const                                         { return ( ReadInteger( tblSLD_Fields[3] ) ); }
//    bool FASTCALL PERID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[3] ) ); }
//    void FASTCALL SetPERID( int value )                                   { WriteInteger( tblSLD_Fields[3], value ); }
//
//    int FASTCALL GetDOSID() const                                         { return ( ReadInteger( tblSLD_Fields[4] ) ); }
//    bool FASTCALL DOSID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[4] ) ); }
//    void FASTCALL SetDOSID( int value )                                   { WriteInteger( tblSLD_Fields[4], value ); }
//
//    ds_string FASTCALL GetDOSCODE() const                                 { return ( ReadString( tblSLD_Fields[5] ) ); }
//    bool FASTCALL DOSCODE_IsNull() const                                  { return ( IsNull( tblSLD_Fields[5] ) ); }
//    void FASTCALL SetDOSCODE( const ds_string& value )                    { WriteString( tblSLD_Fields[5], value ); }
//
//    int FASTCALL GetDOCNUMBER() const                                     { return ( ReadInteger( tblSLD_Fields[6] ) ); }
//    bool FASTCALL DOCNUMBER_IsNull() const                                { return ( IsNull( tblSLD_Fields[6] ) ); }
//    void FASTCALL SetDOCNUMBER( int value )                               { WriteInteger( tblSLD_Fields[6], value ); }
//
//    int FASTCALL GetDOCJRNAA() const                                      { return ( ReadInteger( tblSLD_Fields[7] ) ); }
//    bool FASTCALL DOCJRNAA_IsNull() const                                 { return ( IsNull( tblSLD_Fields[7] ) ); }
//    void FASTCALL SetDOCJRNAA( int value )                                { WriteInteger( tblSLD_Fields[7], value ); }
//
//    smds::cDateTime FASTCALL GetDOCKATAHORISISDATE() const                { return ( ReadDate( tblSLD_Fields[8] ) ); }
//    bool FASTCALL DOCKATAHORISISDATE_IsNull() const                       { return ( IsNull( tblSLD_Fields[8] ) ); }
//    void FASTCALL SetDOCKATAHORISISDATE( const smds::cDateTime& value )   { WriteDate( tblSLD_Fields[8], value ); }
//
//    smds::cDateTime FASTCALL GetDOCENIMEROSISDATE() const                 { return ( ReadDate( tblSLD_Fields[9] ) ); }
//    bool FASTCALL DOCENIMEROSISDATE_IsNull() const                        { return ( IsNull( tblSLD_Fields[9] ) ); }
//    void FASTCALL SetDOCENIMEROSISDATE( const smds::cDateTime& value )    { WriteDate( tblSLD_Fields[9], value ); }
//
//    smds::cDateTime FASTCALL GetDOCEKDOSISDATE() const                    { return ( ReadDate( tblSLD_Fields[10] ) ); }
//    bool FASTCALL DOCEKDOSISDATE_IsNull() const                           { return ( IsNull( tblSLD_Fields[10] ) ); }
//    void FASTCALL SetDOCEKDOSISDATE( const smds::cDateTime& value )       { WriteDate( tblSLD_Fields[10], value ); }
//
//    ds_string FASTCALL GetDOCREASON() const                               { return ( ReadString( tblSLD_Fields[11] ) ); }
//    bool FASTCALL DOCREASON_IsNull() const                                { return ( IsNull( tblSLD_Fields[11] ) ); }
//    void FASTCALL SetDOCREASON( const ds_string& value )                  { WriteString( tblSLD_Fields[11], value ); }
//
//    ds_string FASTCALL GetDOCCOMMENT() const                              { return ( ReadString( tblSLD_Fields[12] ) ); }
//    bool FASTCALL DOCCOMMENT_IsNull() const                               { return ( IsNull( tblSLD_Fields[12] ) ); }
//    void FASTCALL SetDOCCOMMENT( const ds_string& value )                 { WriteString( tblSLD_Fields[12], value ); }
//
//    short FASTCALL GetDOCCANENIM() const                                  { return ( ReadShort( tblSLD_Fields[13] ) ); }
//    bool FASTCALL DOCCANENIM_IsNull() const                               { return ( IsNull( tblSLD_Fields[13] ) ); }
//    void FASTCALL SetDOCCANENIM( short value )                            { WriteShort( tblSLD_Fields[13], value ); }
//
//    short FASTCALL GetDOCCANCANCEL() const                                { return ( ReadShort( tblSLD_Fields[14] ) ); }
//    bool FASTCALL DOCCANCANCEL_IsNull() const                             { return ( IsNull( tblSLD_Fields[14] ) ); }
//    void FASTCALL SetDOCCANCANCEL( short value )                          { WriteShort( tblSLD_Fields[14], value ); }
//
//    ds_string FASTCALL GetDOCCANCELSTATUS() const                         { return ( ReadString( tblSLD_Fields[15] ) ); }
//    bool FASTCALL DOCCANCELSTATUS_IsNull() const                          { return ( IsNull( tblSLD_Fields[15] ) ); }
//    void FASTCALL SetDOCCANCELSTATUS( const ds_string& value )            { WriteString( tblSLD_Fields[15], value ); }
//
//    int FASTCALL GetDOCIDAKIROMENO() const                                { return ( ReadInteger( tblSLD_Fields[16] ) ); }
//    bool FASTCALL DOCIDAKIROMENO_IsNull() const                           { return ( IsNull( tblSLD_Fields[16] ) ); }
//    void FASTCALL SetDOCIDAKIROMENO( int value )                          { WriteInteger( tblSLD_Fields[16], value ); }
//
//    int FASTCALL GetDOCIDAKIROTIKO() const                                { return ( ReadInteger( tblSLD_Fields[17] ) ); }
//    bool FASTCALL DOCIDAKIROTIKO_IsNull() const                           { return ( IsNull( tblSLD_Fields[17] ) ); }
//    void FASTCALL SetDOCIDAKIROTIKO( int value )                          { WriteInteger( tblSLD_Fields[17], value ); }
//
//    int FASTCALL GetDMIID() const                                         { return ( ReadInteger( tblSLD_Fields[18] ) ); }
//    bool FASTCALL DMIID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[18] ) ); }
//    void FASTCALL SetDMIID( int value )                                   { WriteInteger( tblSLD_Fields[18], value ); }
//
//    short FASTCALL GetTDOGROSSRETAIL() const                              { return ( ReadShort( tblSLD_Fields[19] ) ); }
//    bool FASTCALL TDOGROSSRETAIL_IsNull() const                           { return ( IsNull( tblSLD_Fields[19] ) ); }
//    void FASTCALL SetTDOGROSSRETAIL( short value )                        { WriteShort( tblSLD_Fields[19], value ); }
//
//    ds_string FASTCALL GetTDOOTHERNUMBER() const                          { return ( ReadString( tblSLD_Fields[20] ) ); }
//    bool FASTCALL TDOOTHERNUMBER_IsNull() const                           { return ( IsNull( tblSLD_Fields[20] ) ); }
//    void FASTCALL SetTDOOTHERNUMBER( const ds_string& value )             { WriteString( tblSLD_Fields[20], value ); }
//
//    smds::cDateTime FASTCALL GetTDOOTHERDATE() const                      { return ( ReadDate( tblSLD_Fields[21] ) ); }
//    bool FASTCALL TDOOTHERDATE_IsNull() const                             { return ( IsNull( tblSLD_Fields[21] ) ); }
//    void FASTCALL SetTDOOTHERDATE( const smds::cDateTime& value )         { WriteDate( tblSLD_Fields[21], value ); }
//
//    smds::cDateTime FASTCALL GetTDOEKTELESISDATE() const                  { return ( ReadDate( tblSLD_Fields[22] ) ); }
//    bool FASTCALL TDOEKTELESISDATE_IsNull() const                         { return ( IsNull( tblSLD_Fields[22] ) ); }
//    void FASTCALL SetTDOEKTELESISDATE( const smds::cDateTime& value )     { WriteDate( tblSLD_Fields[22], value ); }
//
//    ds_string FASTCALL GetDSTDESCR() const                                { return ( ReadString( tblSLD_Fields[23] ) ); }
//    bool FASTCALL DSTDESCR_IsNull() const                                 { return ( IsNull( tblSLD_Fields[23] ) ); }
//    void FASTCALL SetDSTDESCR( const ds_string& value )                   { WriteString( tblSLD_Fields[23], value ); }
//
//    ds_string FASTCALL GetPPSDESCR() const                                { return ( ReadString( tblSLD_Fields[24] ) ); }
//    bool FASTCALL PPSDESCR_IsNull() const                                 { return ( IsNull( tblSLD_Fields[24] ) ); }
//    void FASTCALL SetPPSDESCR( const ds_string& value )                   { WriteString( tblSLD_Fields[24], value ); }
//
//    ds_string FASTCALL GetORGDESCR() const                                { return ( ReadString( tblSLD_Fields[25] ) ); }
//    bool FASTCALL ORGDESCR_IsNull() const                                 { return ( IsNull( tblSLD_Fields[25] ) ); }
//    void FASTCALL SetORGDESCR( const ds_string& value )                   { WriteString( tblSLD_Fields[25], value ); }
//
//    int FASTCALL GetTPMID() const                                         { return ( ReadInteger( tblSLD_Fields[26] ) ); }
//    bool FASTCALL TPMID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[26] ) ); }
//    void FASTCALL SetTPMID( int value )                                   { WriteInteger( tblSLD_Fields[26], value ); }
//
//    int FASTCALL GetTPTID() const                                         { return ( ReadInteger( tblSLD_Fields[27] ) ); }
//    bool FASTCALL TPTID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[27] ) ); }
//    void FASTCALL SetTPTID( int value )                                   { WriteInteger( tblSLD_Fields[27], value ); }
//
//    int FASTCALL GetSHVID() const                                         { return ( ReadInteger( tblSLD_Fields[28] ) ); }
//    bool FASTCALL SHVID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[28] ) ); }
//    void FASTCALL SetSHVID( int value )                                   { WriteInteger( tblSLD_Fields[28], value ); }
//
//    int FASTCALL GetWRHID() const                                         { return ( ReadInteger( tblSLD_Fields[29] ) ); }
//    bool FASTCALL WRHID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[29] ) ); }
//    void FASTCALL SetWRHID( int value )                                   { WriteInteger( tblSLD_Fields[29], value ); }
//
//    int FASTCALL GetTRAID() const                                         { return ( ReadInteger( tblSLD_Fields[30] ) ); }
//    bool FASTCALL TRAID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[30] ) ); }
//    void FASTCALL SetTRAID( int value )                                   { WriteInteger( tblSLD_Fields[30], value ); }
//
//    ds_string FASTCALL GetTXOCODE() const                                 { return ( ReadString( tblSLD_Fields[31] ) ); }
//    bool FASTCALL TXOCODE_IsNull() const                                  { return ( IsNull( tblSLD_Fields[31] ) ); }
//    void FASTCALL SetTXOCODE( const ds_string& value )                    { WriteString( tblSLD_Fields[31], value ); }
//
//    ds_string FASTCALL GetTDOTRANSPORTREMARKS() const                     { return ( ReadString( tblSLD_Fields[32] ) ); }
//    bool FASTCALL TDOTRANSPORTREMARKS_IsNull() const                      { return ( IsNull( tblSLD_Fields[32] ) ); }
//    void FASTCALL SetTDOTRANSPORTREMARKS( const ds_string& value )        { WriteString( tblSLD_Fields[32], value ); }
//
//    int FASTCALL GetADRIDLOGISTIRIOU() const                              { return ( ReadInteger( tblSLD_Fields[33] ) ); }
//    bool FASTCALL ADRIDLOGISTIRIOU_IsNull() const                         { return ( IsNull( tblSLD_Fields[33] ) ); }
//    void FASTCALL SetADRIDLOGISTIRIOU( int value )                        { WriteInteger( tblSLD_Fields[33], value ); }
//
//    int FASTCALL GetADRIDPROORISMOU() const                               { return ( ReadInteger( tblSLD_Fields[34] ) ); }
//    bool FASTCALL ADRIDPROORISMOU_IsNull() const                          { return ( IsNull( tblSLD_Fields[34] ) ); }
//    void FASTCALL SetADRIDPROORISMOU( int value )                         { WriteInteger( tblSLD_Fields[34], value ); }
//
//    smds::cDateTime FASTCALL GetTDOSENDTIME() const                       { return ( ReadDate( tblSLD_Fields[35] ) ); }
//    bool FASTCALL TDOSENDTIME_IsNull() const                              { return ( IsNull( tblSLD_Fields[35] ) ); }
//    void FASTCALL SetTDOSENDTIME( const smds::cDateTime& value )          { WriteDate( tblSLD_Fields[35], value ); }
//
//    ds_string FASTCALL GetTDOVATSTATUS() const                            { return ( ReadString( tblSLD_Fields[36] ) ); }
//    bool FASTCALL TDOVATSTATUS_IsNull() const                             { return ( IsNull( tblSLD_Fields[36] ) ); }
//    void FASTCALL SetTDOVATSTATUS( const ds_string& value )               { WriteString( tblSLD_Fields[36], value ); }
//
//    ds_string FASTCALL GetTDOLEEAFM() const                               { return ( ReadString( tblSLD_Fields[37] ) ); }
//    bool FASTCALL TDOLEEAFM_IsNull() const                                { return ( IsNull( tblSLD_Fields[37] ) ); }
//    void FASTCALL SetTDOLEEAFM( const ds_string& value )                  { WriteString( tblSLD_Fields[37], value ); }
//
//    ds_string FASTCALL GetTDOLEEADT() const                               { return ( ReadString( tblSLD_Fields[38] ) ); }
//    bool FASTCALL TDOLEEADT_IsNull() const                                { return ( IsNull( tblSLD_Fields[38] ) ); }
//    void FASTCALL SetTDOLEEADT( const ds_string& value )                  { WriteString( tblSLD_Fields[38], value ); }
//
//    ds_string FASTCALL GetTDOLEEADTKIND() const                           { return ( ReadString( tblSLD_Fields[39] ) ); }
//    bool FASTCALL TDOLEEADTKIND_IsNull() const                            { return ( IsNull( tblSLD_Fields[39] ) ); }
//    void FASTCALL SetTDOLEEADTKIND( const ds_string& value )              { WriteString( tblSLD_Fields[39], value ); }
//
//    ds_string FASTCALL GetTDOADDRESS() const                              { return ( ReadString( tblSLD_Fields[40] ) ); }
//    bool FASTCALL TDOADDRESS_IsNull() const                               { return ( IsNull( tblSLD_Fields[40] ) ); }
//    void FASTCALL SetTDOADDRESS( const ds_string& value )                 { WriteString( tblSLD_Fields[40], value ); }
//
//    int FASTCALL GetCURID() const                                         { return ( ReadInteger( tblSLD_Fields[41] ) ); }
//    bool FASTCALL CURID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[41] ) ); }
//    void FASTCALL SetCURID( int value )                                   { WriteInteger( tblSLD_Fields[41], value ); }
//
//    ds_string FASTCALL GetTDOEQVTYPE() const                              { return ( ReadString( tblSLD_Fields[42] ) ); }
//    bool FASTCALL TDOEQVTYPE_IsNull() const                               { return ( IsNull( tblSLD_Fields[42] ) ); }
//    void FASTCALL SetTDOEQVTYPE( const ds_string& value )                 { WriteString( tblSLD_Fields[42], value ); }
//
//    double FASTCALL GetTDOEQUIVALENCE() const                             { return ( ReadFloat( tblSLD_Fields[43] ) ); }
//    bool FASTCALL TDOEQUIVALENCE_IsNull() const                           { return ( IsNull( tblSLD_Fields[43] ) ); }
//    void FASTCALL SetTDOEQUIVALENCE( double value )                       { WriteFloat( tblSLD_Fields[43], value ); }
//
//    int FASTCALL GetTDODUEDAYS() const                                    { return ( ReadInteger( tblSLD_Fields[44] ) ); }
//    bool FASTCALL TDODUEDAYS_IsNull() const                               { return ( IsNull( tblSLD_Fields[44] ) ); }
//    void FASTCALL SetTDODUEDAYS( int value )                              { WriteInteger( tblSLD_Fields[44], value ); }
//
//    int FASTCALL GetTDOGRACEDAYS() const                                  { return ( ReadInteger( tblSLD_Fields[45] ) ); }
//    bool FASTCALL TDOGRACEDAYS_IsNull() const                             { return ( IsNull( tblSLD_Fields[45] ) ); }
//    void FASTCALL SetTDOGRACEDAYS( int value )                            { WriteInteger( tblSLD_Fields[45], value ); }
//
//    int FASTCALL GetSLMID() const                                         { return ( ReadInteger( tblSLD_Fields[46] ) ); }
//    bool FASTCALL SLMID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[46] ) ); }
//    void FASTCALL SetSLMID( int value )                                   { WriteInteger( tblSLD_Fields[46], value ); }
//
//    double FASTCALL GetTDOTRADERDISCPCNT() const                          { return ( ReadFloat( tblSLD_Fields[47] ) ); }
//    bool FASTCALL TDOTRADERDISCPCNT_IsNull() const                        { return ( IsNull( tblSLD_Fields[47] ) ); }
//    void FASTCALL SetTDOTRADERDISCPCNT( double value )                    { WriteFloat( tblSLD_Fields[47], value ); }
//
//    double FASTCALL GetTDOQTYA() const                                    { return ( ReadFloat( tblSLD_Fields[48] ) ); }
//    bool FASTCALL TDOQTYA_IsNull() const                                  { return ( IsNull( tblSLD_Fields[48] ) ); }
//    void FASTCALL SetTDOQTYA( double value )                              { WriteFloat( tblSLD_Fields[48], value ); }
//
//    double FASTCALL GetTDOQTYB() const                                    { return ( ReadFloat( tblSLD_Fields[49] ) ); }
//    bool FASTCALL TDOQTYB_IsNull() const                                  { return ( IsNull( tblSLD_Fields[49] ) ); }
//    void FASTCALL SetTDOQTYB( double value )                              { WriteFloat( tblSLD_Fields[49], value ); }
//
//    double FASTCALL GetTDOTRANSFQTYA() const                              { return ( ReadFloat( tblSLD_Fields[50] ) ); }
//    bool FASTCALL TDOTRANSFQTYA_IsNull() const                            { return ( IsNull( tblSLD_Fields[50] ) ); }
//    void FASTCALL SetTDOTRANSFQTYA( double value )                        { WriteFloat( tblSLD_Fields[50], value ); }
//
//    double FASTCALL GetTDOTRANSFQTYB() const                              { return ( ReadFloat( tblSLD_Fields[51] ) ); }
//    bool FASTCALL TDOTRANSFQTYB_IsNull() const                            { return ( IsNull( tblSLD_Fields[51] ) ); }
//    void FASTCALL SetTDOTRANSFQTYB( double value )                        { WriteFloat( tblSLD_Fields[51], value ); }
//
//    double FASTCALL GetTDOQTYDISCA() const                                { return ( ReadFloat( tblSLD_Fields[52] ) ); }
//    bool FASTCALL TDOQTYDISCA_IsNull() const                              { return ( IsNull( tblSLD_Fields[52] ) ); }
//    void FASTCALL SetTDOQTYDISCA( double value )                          { WriteFloat( tblSLD_Fields[52], value ); }
//
//    double FASTCALL GetTDOQTYDISCB() const                                { return ( ReadFloat( tblSLD_Fields[53] ) ); }
//    bool FASTCALL TDOQTYDISCB_IsNull() const                              { return ( IsNull( tblSLD_Fields[53] ) ); }
//    void FASTCALL SetTDOQTYDISCB( double value )                          { WriteFloat( tblSLD_Fields[53], value ); }
//
//    double FASTCALL GetTDOTRADERDISC() const                              { return ( ReadFloat( tblSLD_Fields[54] ) ); }
//    bool FASTCALL TDOTRADERDISC_IsNull() const                            { return ( IsNull( tblSLD_Fields[54] ) ); }
//    void FASTCALL SetTDOTRADERDISC( double value )                        { WriteFloat( tblSLD_Fields[54], value ); }
//
//    double FASTCALL GetTDOTRADERDISCBC() const                            { return ( ReadFloat( tblSLD_Fields[55] ) ); }
//    bool FASTCALL TDOTRADERDISCBC_IsNull() const                          { return ( IsNull( tblSLD_Fields[55] ) ); }
//    void FASTCALL SetTDOTRADERDISCBC( double value )                      { WriteFloat( tblSLD_Fields[55], value ); }
//
//    double FASTCALL GetTDOPAYMENTDISC() const                             { return ( ReadFloat( tblSLD_Fields[56] ) ); }
//    bool FASTCALL TDOPAYMENTDISC_IsNull() const                           { return ( IsNull( tblSLD_Fields[56] ) ); }
//    void FASTCALL SetTDOPAYMENTDISC( double value )                       { WriteFloat( tblSLD_Fields[56], value ); }
//
//    double FASTCALL GetTDOPAYMENTDISCBC() const                           { return ( ReadFloat( tblSLD_Fields[57] ) ); }
//    bool FASTCALL TDOPAYMENTDISCBC_IsNull() const                         { return ( IsNull( tblSLD_Fields[57] ) ); }
//    void FASTCALL SetTDOPAYMENTDISCBC( double value )                     { WriteFloat( tblSLD_Fields[57], value ); }
//
//    double FASTCALL GetTDOSTOCKDISC() const                               { return ( ReadFloat( tblSLD_Fields[58] ) ); }
//    bool FASTCALL TDOSTOCKDISC_IsNull() const                             { return ( IsNull( tblSLD_Fields[58] ) ); }
//    void FASTCALL SetTDOSTOCKDISC( double value )                         { WriteFloat( tblSLD_Fields[58], value ); }
//
//    double FASTCALL GetTDOSTOCKDISCBC() const                             { return ( ReadFloat( tblSLD_Fields[59] ) ); }
//    bool FASTCALL TDOSTOCKDISCBC_IsNull() const                           { return ( IsNull( tblSLD_Fields[59] ) ); }
//    void FASTCALL SetTDOSTOCKDISCBC( double value )                       { WriteFloat( tblSLD_Fields[59], value ); }
//
//    double FASTCALL GetTDOPRICELISTDISC() const                           { return ( ReadFloat( tblSLD_Fields[60] ) ); }
//    bool FASTCALL TDOPRICELISTDISC_IsNull() const                         { return ( IsNull( tblSLD_Fields[60] ) ); }
//    void FASTCALL SetTDOPRICELISTDISC( double value )                     { WriteFloat( tblSLD_Fields[60], value ); }
//
//    double FASTCALL GetTDOPRICELISTDISCBC() const                         { return ( ReadFloat( tblSLD_Fields[61] ) ); }
//    bool FASTCALL TDOPRICELISTDISCBC_IsNull() const                       { return ( IsNull( tblSLD_Fields[61] ) ); }
//    void FASTCALL SetTDOPRICELISTDISCBC( double value )                   { WriteFloat( tblSLD_Fields[61], value ); }
//
//    double FASTCALL GetTDOEXTRADISC() const                               { return ( ReadFloat( tblSLD_Fields[62] ) ); }
//    bool FASTCALL TDOEXTRADISC_IsNull() const                             { return ( IsNull( tblSLD_Fields[62] ) ); }
//    void FASTCALL SetTDOEXTRADISC( double value )                         { WriteFloat( tblSLD_Fields[62], value ); }
//
//    double FASTCALL GetTDOEXTRADISCBC() const                             { return ( ReadFloat( tblSLD_Fields[63] ) ); }
//    bool FASTCALL TDOEXTRADISCBC_IsNull() const                           { return ( IsNull( tblSLD_Fields[63] ) ); }
//    void FASTCALL SetTDOEXTRADISCBC( double value )                       { WriteFloat( tblSLD_Fields[63], value ); }
//
//    double FASTCALL GetTDONETSTOCK() const                                { return ( ReadFloat( tblSLD_Fields[64] ) ); }
//    bool FASTCALL TDONETSTOCK_IsNull() const                              { return ( IsNull( tblSLD_Fields[64] ) ); }
//    void FASTCALL SetTDONETSTOCK( double value )                          { WriteFloat( tblSLD_Fields[64], value ); }
//
//    double FASTCALL GetTDONETSTOCKBC() const                              { return ( ReadFloat( tblSLD_Fields[65] ) ); }
//    bool FASTCALL TDONETSTOCKBC_IsNull() const                            { return ( IsNull( tblSLD_Fields[65] ) ); }
//    void FASTCALL SetTDONETSTOCKBC( double value )                        { WriteFloat( tblSLD_Fields[65], value ); }
//
//    double FASTCALL GetTDONETGIFT() const                                 { return ( ReadFloat( tblSLD_Fields[66] ) ); }
//    bool FASTCALL TDONETGIFT_IsNull() const                               { return ( IsNull( tblSLD_Fields[66] ) ); }
//    void FASTCALL SetTDONETGIFT( double value )                           { WriteFloat( tblSLD_Fields[66], value ); }
//
//    double FASTCALL GetTDONETGIFTBC() const                               { return ( ReadFloat( tblSLD_Fields[67] ) ); }
//    bool FASTCALL TDONETGIFTBC_IsNull() const                             { return ( IsNull( tblSLD_Fields[67] ) ); }
//    void FASTCALL SetTDONETGIFTBC( double value )                         { WriteFloat( tblSLD_Fields[67], value ); }
//
//    double FASTCALL GetTDONETSURCHARGE() const                            { return ( ReadFloat( tblSLD_Fields[68] ) ); }
//    bool FASTCALL TDONETSURCHARGE_IsNull() const                          { return ( IsNull( tblSLD_Fields[68] ) ); }
//    void FASTCALL SetTDONETSURCHARGE( double value )                      { WriteFloat( tblSLD_Fields[68], value ); }
//
//    double FASTCALL GetTDONETSURCHARGEBC() const                          { return ( ReadFloat( tblSLD_Fields[69] ) ); }
//    bool FASTCALL TDONETSURCHARGEBC_IsNull() const                        { return ( IsNull( tblSLD_Fields[69] ) ); }
//    void FASTCALL SetTDONETSURCHARGEBC( double value )                    { WriteFloat( tblSLD_Fields[69], value ); }
//
//    double FASTCALL GetTDONETOTHER() const                                { return ( ReadFloat( tblSLD_Fields[70] ) ); }
//    bool FASTCALL TDONETOTHER_IsNull() const                              { return ( IsNull( tblSLD_Fields[70] ) ); }
//    void FASTCALL SetTDONETOTHER( double value )                          { WriteFloat( tblSLD_Fields[70], value ); }
//
//    double FASTCALL GetTDONETOTHERBC() const                              { return ( ReadFloat( tblSLD_Fields[71] ) ); }
//    bool FASTCALL TDONETOTHERBC_IsNull() const                            { return ( IsNull( tblSLD_Fields[71] ) ); }
//    void FASTCALL SetTDONETOTHERBC( double value )                        { WriteFloat( tblSLD_Fields[71], value ); }
//
//    double FASTCALL GetTDONETTAX() const                                  { return ( ReadFloat( tblSLD_Fields[72] ) ); }
//    bool FASTCALL TDONETTAX_IsNull() const                                { return ( IsNull( tblSLD_Fields[72] ) ); }
//    void FASTCALL SetTDONETTAX( double value )                            { WriteFloat( tblSLD_Fields[72], value ); }
//
//    double FASTCALL GetTDONETTAXBC() const                                { return ( ReadFloat( tblSLD_Fields[73] ) ); }
//    bool FASTCALL TDONETTAXBC_IsNull() const                              { return ( IsNull( tblSLD_Fields[73] ) ); }
//    void FASTCALL SetTDONETTAXBC( double value )                          { WriteFloat( tblSLD_Fields[73], value ); }
//
//    double FASTCALL GetTDOGROSSVALUE() const                              { return ( ReadFloat( tblSLD_Fields[74] ) ); }
//    bool FASTCALL TDOGROSSVALUE_IsNull() const                            { return ( IsNull( tblSLD_Fields[74] ) ); }
//    void FASTCALL SetTDOGROSSVALUE( double value )                        { WriteFloat( tblSLD_Fields[74], value ); }
//
//    double FASTCALL GetTDOGROSSVALUEBC() const                            { return ( ReadFloat( tblSLD_Fields[75] ) ); }
//    bool FASTCALL TDOGROSSVALUEBC_IsNull() const                          { return ( IsNull( tblSLD_Fields[75] ) ); }
//    void FASTCALL SetTDOGROSSVALUEBC( double value )                      { WriteFloat( tblSLD_Fields[75], value ); }
//
//    double FASTCALL GetTDOVATSTOCK() const                                { return ( ReadFloat( tblSLD_Fields[76] ) ); }
//    bool FASTCALL TDOVATSTOCK_IsNull() const                              { return ( IsNull( tblSLD_Fields[76] ) ); }
//    void FASTCALL SetTDOVATSTOCK( double value )                          { WriteFloat( tblSLD_Fields[76], value ); }
//
//    double FASTCALL GetTDOVATSTOCKBC() const                              { return ( ReadFloat( tblSLD_Fields[77] ) ); }
//    bool FASTCALL TDOVATSTOCKBC_IsNull() const                            { return ( IsNull( tblSLD_Fields[77] ) ); }
//    void FASTCALL SetTDOVATSTOCKBC( double value )                        { WriteFloat( tblSLD_Fields[77], value ); }
//
//    double FASTCALL GetTDOVATGIFT() const                                 { return ( ReadFloat( tblSLD_Fields[78] ) ); }
//    bool FASTCALL TDOVATGIFT_IsNull() const                               { return ( IsNull( tblSLD_Fields[78] ) ); }
//    void FASTCALL SetTDOVATGIFT( double value )                           { WriteFloat( tblSLD_Fields[78], value ); }
//
//    double FASTCALL GetTDOVATGIFTBC() const                               { return ( ReadFloat( tblSLD_Fields[79] ) ); }
//    bool FASTCALL TDOVATGIFTBC_IsNull() const                             { return ( IsNull( tblSLD_Fields[79] ) ); }
//    void FASTCALL SetTDOVATGIFTBC( double value )                         { WriteFloat( tblSLD_Fields[79], value ); }
//
//    double FASTCALL GetTDOVATSURCHARGE() const                            { return ( ReadFloat( tblSLD_Fields[80] ) ); }
//    bool FASTCALL TDOVATSURCHARGE_IsNull() const                          { return ( IsNull( tblSLD_Fields[80] ) ); }
//    void FASTCALL SetTDOVATSURCHARGE( double value )                      { WriteFloat( tblSLD_Fields[80], value ); }
//
//    double FASTCALL GetTDOVATSURCHARGEBC() const                          { return ( ReadFloat( tblSLD_Fields[81] ) ); }
//    bool FASTCALL TDOVATSURCHARGEBC_IsNull() const                        { return ( IsNull( tblSLD_Fields[81] ) ); }
//    void FASTCALL SetTDOVATSURCHARGEBC( double value )                    { WriteFloat( tblSLD_Fields[81], value ); }
//
//    double FASTCALL GetTDOVATOTHER() const                                { return ( ReadFloat( tblSLD_Fields[82] ) ); }
//    bool FASTCALL TDOVATOTHER_IsNull() const                              { return ( IsNull( tblSLD_Fields[82] ) ); }
//    void FASTCALL SetTDOVATOTHER( double value )                          { WriteFloat( tblSLD_Fields[82], value ); }
//
//    double FASTCALL GetTDOVATOTHERBC() const                              { return ( ReadFloat( tblSLD_Fields[83] ) ); }
//    bool FASTCALL TDOVATOTHERBC_IsNull() const                            { return ( IsNull( tblSLD_Fields[83] ) ); }
//    void FASTCALL SetTDOVATOTHERBC( double value )                        { WriteFloat( tblSLD_Fields[83], value ); }
//
//    double FASTCALL GetTDOVATTAX() const                                  { return ( ReadFloat( tblSLD_Fields[84] ) ); }
//    bool FASTCALL TDOVATTAX_IsNull() const                                { return ( IsNull( tblSLD_Fields[84] ) ); }
//    void FASTCALL SetTDOVATTAX( double value )                            { WriteFloat( tblSLD_Fields[84], value ); }
//
//    double FASTCALL GetTDOVATTAXBC() const                                { return ( ReadFloat( tblSLD_Fields[85] ) ); }
//    bool FASTCALL TDOVATTAXBC_IsNull() const                              { return ( IsNull( tblSLD_Fields[85] ) ); }
//    void FASTCALL SetTDOVATTAXBC( double value )                          { WriteFloat( tblSLD_Fields[85], value ); }
//
//    int FASTCALL GetPTPIDPAYMENT() const                                  { return ( ReadInteger( tblSLD_Fields[86] ) ); }
//    bool FASTCALL PTPIDPAYMENT_IsNull() const                             { return ( IsNull( tblSLD_Fields[86] ) ); }
//    void FASTCALL SetPTPIDPAYMENT( int value )                            { WriteInteger( tblSLD_Fields[86], value ); }
//
//    int FASTCALL GetPMTIDPAYMENT() const                                  { return ( ReadInteger( tblSLD_Fields[87] ) ); }
//    bool FASTCALL PMTIDPAYMENT_IsNull() const                             { return ( IsNull( tblSLD_Fields[87] ) ); }
//    void FASTCALL SetPMTIDPAYMENT( int value )                            { WriteInteger( tblSLD_Fields[87], value ); }
//
//    int FASTCALL GetDOCIDPAYMENT() const                                  { return ( ReadInteger( tblSLD_Fields[88] ) ); }
//    bool FASTCALL DOCIDPAYMENT_IsNull() const                             { return ( IsNull( tblSLD_Fields[88] ) ); }
//    void FASTCALL SetDOCIDPAYMENT( int value )                            { WriteInteger( tblSLD_Fields[88], value ); }
//
//    double FASTCALL GetTDOPAYMENT() const                                 { return ( ReadFloat( tblSLD_Fields[89] ) ); }
//    bool FASTCALL TDOPAYMENT_IsNull() const                               { return ( IsNull( tblSLD_Fields[89] ) ); }
//    void FASTCALL SetTDOPAYMENT( double value )                           { WriteFloat( tblSLD_Fields[89], value ); }
//
//    double FASTCALL GetTDOPAYMENTBC() const                               { return ( ReadFloat( tblSLD_Fields[90] ) ); }
//    bool FASTCALL TDOPAYMENTBC_IsNull() const                             { return ( IsNull( tblSLD_Fields[90] ) ); }
//    void FASTCALL SetTDOPAYMENTBC( double value )                         { WriteFloat( tblSLD_Fields[90], value ); }
//
//    double FASTCALL GetTDONETKRATISI() const                              { return ( ReadFloat( tblSLD_Fields[91] ) ); }
//    bool FASTCALL TDONETKRATISI_IsNull() const                            { return ( IsNull( tblSLD_Fields[91] ) ); }
//    void FASTCALL SetTDONETKRATISI( double value )                        { WriteFloat( tblSLD_Fields[91], value ); }
//
//    double FASTCALL GetTDONETKRATISIBC() const                            { return ( ReadFloat( tblSLD_Fields[92] ) ); }
//    bool FASTCALL TDONETKRATISIBC_IsNull() const                          { return ( IsNull( tblSLD_Fields[92] ) ); }
//    void FASTCALL SetTDONETKRATISIBC( double value )                      { WriteFloat( tblSLD_Fields[92], value ); }
//
//    double FASTCALL GetTDOTRADERBALANCEBEFORE() const                     { return ( ReadFloat( tblSLD_Fields[93] ) ); }
//    bool FASTCALL TDOTRADERBALANCEBEFORE_IsNull() const                   { return ( IsNull( tblSLD_Fields[93] ) ); }
//    void FASTCALL SetTDOTRADERBALANCEBEFORE( double value )               { WriteFloat( tblSLD_Fields[93], value ); }
//
//    double FASTCALL GetTDOTRADERBALANCEAFTER() const                      { return ( ReadFloat( tblSLD_Fields[94] ) ); }
//    bool FASTCALL TDOTRADERBALANCEAFTER_IsNull() const                    { return ( IsNull( tblSLD_Fields[94] ) ); }
//    void FASTCALL SetTDOTRADERBALANCEAFTER( double value )                { WriteFloat( tblSLD_Fields[94], value ); }
//
//    short FASTCALL GetTDOCANTRANSF() const                                { return ( ReadShort( tblSLD_Fields[95] ) ); }
//    bool FASTCALL TDOCANTRANSF_IsNull() const                             { return ( IsNull( tblSLD_Fields[95] ) ); }
//    void FASTCALL SetTDOCANTRANSF( short value )                          { WriteShort( tblSLD_Fields[95], value ); }
//
//    double FASTCALL GetTDOADVANCE() const                                 { return ( ReadFloat( tblSLD_Fields[96] ) ); }
//    bool FASTCALL TDOADVANCE_IsNull() const                               { return ( IsNull( tblSLD_Fields[96] ) ); }
//    void FASTCALL SetTDOADVANCE( double value )                           { WriteFloat( tblSLD_Fields[96], value ); }
//
//    double FASTCALL GetTDOADVANCEBC() const                               { return ( ReadFloat( tblSLD_Fields[97] ) ); }
//    bool FASTCALL TDOADVANCEBC_IsNull() const                             { return ( IsNull( tblSLD_Fields[97] ) ); }
//    void FASTCALL SetTDOADVANCEBC( double value )                         { WriteFloat( tblSLD_Fields[97], value ); }
//
//    double FASTCALL GetTDOADVANCEUSAGE() const                            { return ( ReadFloat( tblSLD_Fields[98] ) ); }
//    bool FASTCALL TDOADVANCEUSAGE_IsNull() const                          { return ( IsNull( tblSLD_Fields[98] ) ); }
//    void FASTCALL SetTDOADVANCEUSAGE( double value )                      { WriteFloat( tblSLD_Fields[98], value ); }
//
//    double FASTCALL GetTDOADVANCEUSAGEBC() const                          { return ( ReadFloat( tblSLD_Fields[99] ) ); }
//    bool FASTCALL TDOADVANCEUSAGEBC_IsNull() const                        { return ( IsNull( tblSLD_Fields[99] ) ); }
//    void FASTCALL SetTDOADVANCEUSAGEBC( double value )                    { WriteFloat( tblSLD_Fields[99], value ); }
//
//    int FASTCALL GetCDZID() const                                         { return ( ReadInteger( tblSLD_Fields[100] ) ); }
//    bool FASTCALL CDZID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[100] ) ); }
//    void FASTCALL SetCDZID( int value )                                   { WriteInteger( tblSLD_Fields[100], value ); }
//
//    int FASTCALL GetPTPIDDOCTYPE() const                                  { return ( ReadInteger( tblSLD_Fields[101] ) ); }
//    bool FASTCALL PTPIDDOCTYPE_IsNull() const                             { return ( IsNull( tblSLD_Fields[101] ) ); }
//    void FASTCALL SetPTPIDDOCTYPE( int value )                            { WriteInteger( tblSLD_Fields[101], value ); }
//
//    int FASTCALL GetLEEIDRECEIVER() const                                 { return ( ReadInteger( tblSLD_Fields[102] ) ); }
//    bool FASTCALL LEEIDRECEIVER_IsNull() const                            { return ( IsNull( tblSLD_Fields[102] ) ); }
//    void FASTCALL SetLEEIDRECEIVER( int value )                           { WriteInteger( tblSLD_Fields[102], value ); }
//
//    int FASTCALL GetADRIDRECEIVER() const                                 { return ( ReadInteger( tblSLD_Fields[103] ) ); }
//    bool FASTCALL ADRIDRECEIVER_IsNull() const                            { return ( IsNull( tblSLD_Fields[103] ) ); }
//    void FASTCALL SetADRIDRECEIVER( int value )                           { WriteInteger( tblSLD_Fields[103], value ); }
//
//    int FASTCALL GetPMTIDADVANCE() const                                  { return ( ReadInteger( tblSLD_Fields[104] ) ); }
//    bool FASTCALL PMTIDADVANCE_IsNull() const                             { return ( IsNull( tblSLD_Fields[104] ) ); }
//    void FASTCALL SetPMTIDADVANCE( int value )                            { WriteInteger( tblSLD_Fields[104], value ); }
//
//    int FASTCALL GetDOCIDADVANCE() const                                  { return ( ReadInteger( tblSLD_Fields[105] ) ); }
//    bool FASTCALL DOCIDADVANCE_IsNull() const                             { return ( IsNull( tblSLD_Fields[105] ) ); }
//    void FASTCALL SetDOCIDADVANCE( int value )                            { WriteInteger( tblSLD_Fields[105], value ); }
//
//    double FASTCALL GetTDOPAYMENTDISCPCNT() const                         { return ( ReadFloat( tblSLD_Fields[106] ) ); }
//    bool FASTCALL TDOPAYMENTDISCPCNT_IsNull() const                       { return ( IsNull( tblSLD_Fields[106] ) ); }
//    void FASTCALL SetTDOPAYMENTDISCPCNT( double value )                   { WriteFloat( tblSLD_Fields[106], value ); }
//
//    int FASTCALL GetTTYIDTRADER() const                                   { return ( ReadInteger( tblSLD_Fields[107] ) ); }
//    bool FASTCALL TTYIDTRADER_IsNull() const                              { return ( IsNull( tblSLD_Fields[107] ) ); }
//    void FASTCALL SetTTYIDTRADER( int value )                             { WriteInteger( tblSLD_Fields[107], value ); }
//
//    int FASTCALL GetTTYIDSALESMAN() const                                 { return ( ReadInteger( tblSLD_Fields[108] ) ); }
//    bool FASTCALL TTYIDSALESMAN_IsNull() const                            { return ( IsNull( tblSLD_Fields[108] ) ); }
//    void FASTCALL SetTTYIDSALESMAN( int value )                           { WriteInteger( tblSLD_Fields[108], value ); }
//
//    int FASTCALL GetTTYIDSTOCKITEM() const                                { return ( ReadInteger( tblSLD_Fields[109] ) ); }
//    bool FASTCALL TTYIDSTOCKITEM_IsNull() const                           { return ( IsNull( tblSLD_Fields[109] ) ); }
//    void FASTCALL SetTTYIDSTOCKITEM( int value )                          { WriteInteger( tblSLD_Fields[109], value ); }
//
//    short FASTCALL GetTDOVATINCLUDED() const                              { return ( ReadShort( tblSLD_Fields[110] ) ); }
//    bool FASTCALL TDOVATINCLUDED_IsNull() const                           { return ( IsNull( tblSLD_Fields[110] ) ); }
//    void FASTCALL SetTDOVATINCLUDED( short value )                        { WriteShort( tblSLD_Fields[110], value ); }
//
//    int FASTCALL GetPTPIDTRADER() const                                   { return ( ReadInteger( tblSLD_Fields[111] ) ); }
//    bool FASTCALL PTPIDTRADER_IsNull() const                              { return ( IsNull( tblSLD_Fields[111] ) ); }
//    void FASTCALL SetPTPIDTRADER( int value )                             { WriteInteger( tblSLD_Fields[111], value ); }
//
//    int FASTCALL GetSYS_USRID() const                                     { return ( ReadInteger( tblSLD_Fields[112] ) ); }
//    bool FASTCALL SYS_USRID_IsNull() const                                { return ( IsNull( tblSLD_Fields[112] ) ); }
//    void FASTCALL SetSYS_USRID( int value )                               { WriteInteger( tblSLD_Fields[112], value ); }
//
//    smds::cDateTime FASTCALL GetSYS_LUPD() const                          { return ( ReadDate( tblSLD_Fields[113] ) ); }
//    bool FASTCALL SYS_LUPD_IsNull() const                                 { return ( IsNull( tblSLD_Fields[113] ) ); }
//    void FASTCALL SetSYS_LUPD( const smds::cDateTime& value )             { WriteDate( tblSLD_Fields[113], value ); }
//
//    smds::cDateTime FASTCALL GetSYS_INS() const                           { return ( ReadDate( tblSLD_Fields[114] ) ); }
//    bool FASTCALL SYS_INS_IsNull() const                                  { return ( IsNull( tblSLD_Fields[114] ) ); }
//    void FASTCALL SetSYS_INS( const smds::cDateTime& value )              { WriteDate( tblSLD_Fields[114], value ); }
//
//    ds_string FASTCALL GetTDOKEEPPRICESTRANSF() const                     { return ( ReadString( tblSLD_Fields[115] ) ); }
//    bool FASTCALL TDOKEEPPRICESTRANSF_IsNull() const                      { return ( IsNull( tblSLD_Fields[115] ) ); }
//    void FASTCALL SetTDOKEEPPRICESTRANSF( const ds_string& value )        { WriteString( tblSLD_Fields[115], value ); }
//
//    double FASTCALL GetTDOTRADERBALANCEBEFOREBC() const                   { return ( ReadFloat( tblSLD_Fields[116] ) ); }
//    bool FASTCALL TDOTRADERBALANCEBEFOREBC_IsNull() const                 { return ( IsNull( tblSLD_Fields[116] ) ); }
//    void FASTCALL SetTDOTRADERBALANCEBEFOREBC( double value )             { WriteFloat( tblSLD_Fields[116], value ); }
//
//    double FASTCALL GetTDOTRADERBALANCEAFTERBC() const                    { return ( ReadFloat( tblSLD_Fields[117] ) ); }
//    bool FASTCALL TDOTRADERBALANCEAFTERBC_IsNull() const                  { return ( IsNull( tblSLD_Fields[117] ) ); }
//    void FASTCALL SetTDOTRADERBALANCEAFTERBC( double value )              { WriteFloat( tblSLD_Fields[117], value ); }
//
//    int FASTCALL GetSLMIDCOLLECTOR() const                                { return ( ReadInteger( tblSLD_Fields[118] ) ); }
//    bool FASTCALL SLMIDCOLLECTOR_IsNull() const                           { return ( IsNull( tblSLD_Fields[118] ) ); }
//    void FASTCALL SetSLMIDCOLLECTOR( int value )                          { WriteInteger( tblSLD_Fields[118], value ); }
//
//    int FASTCALL GetDOCIDPREDICTION() const                               { return ( ReadInteger( tblSLD_Fields[119] ) ); }
//    bool FASTCALL DOCIDPREDICTION_IsNull() const                          { return ( IsNull( tblSLD_Fields[119] ) ); }
//    void FASTCALL SetDOCIDPREDICTION( int value )                         { WriteInteger( tblSLD_Fields[119], value ); }
//
//    short FASTCALL GetTDOISPREDICTION() const                             { return ( ReadShort( tblSLD_Fields[120] ) ); }
//    bool FASTCALL TDOISPREDICTION_IsNull() const                          { return ( IsNull( tblSLD_Fields[120] ) ); }
//    void FASTCALL SetTDOISPREDICTION( short value )                       { WriteShort( tblSLD_Fields[120], value ); }
//
//    int FASTCALL GetTTYIDASSETITEM() const                                { return ( ReadInteger( tblSLD_Fields[121] ) ); }
//    bool FASTCALL TTYIDASSETITEM_IsNull() const                           { return ( IsNull( tblSLD_Fields[121] ) ); }
//    void FASTCALL SetTTYIDASSETITEM( int value )                          { WriteInteger( tblSLD_Fields[121], value ); }
//
//    double FASTCALL GetTDOAUDITEQUIVALENCE() const                        { return ( ReadFloat( tblSLD_Fields[122] ) ); }
//    bool FASTCALL TDOAUDITEQUIVALENCE_IsNull() const                      { return ( IsNull( tblSLD_Fields[122] ) ); }
//    void FASTCALL SetTDOAUDITEQUIVALENCE( double value )                  { WriteFloat( tblSLD_Fields[122], value ); }
//
//    short FASTCALL GetTDOAUDITEQVONEBASED() const                         { return ( ReadShort( tblSLD_Fields[123] ) ); }
//    bool FASTCALL TDOAUDITEQVONEBASED_IsNull() const                      { return ( IsNull( tblSLD_Fields[123] ) ); }
//    void FASTCALL SetTDOAUDITEQVONEBASED( short value )                   { WriteShort( tblSLD_Fields[123], value ); }
//
//    double FASTCALL GetTDODASMEQUIVALENCE() const                         { return ( ReadFloat( tblSLD_Fields[124] ) ); }
//    bool FASTCALL TDODASMEQUIVALENCE_IsNull() const                       { return ( IsNull( tblSLD_Fields[124] ) ); }
//    void FASTCALL SetTDODASMEQUIVALENCE( double value )                   { WriteFloat( tblSLD_Fields[124], value ); }
//
//    int FASTCALL GetSLDCASHIER() const                                    { return ( ReadInteger( tblSLD_Fields[125] ) ); }
//    bool FASTCALL SLDCASHIER_IsNull() const                               { return ( IsNull( tblSLD_Fields[125] ) ); }
//    void FASTCALL SetSLDCASHIER( int value )                              { WriteInteger( tblSLD_Fields[125], value ); }
//
//    int FASTCALL GetVERID() const                                         { return ( ReadInteger( tblSLD_Fields[126] ) ); }
//    bool FASTCALL VERID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[126] ) ); }
//    void FASTCALL SetVERID( int value )                                   { WriteInteger( tblSLD_Fields[126], value ); }
//
//    double FASTCALL GetSLDDISCOUNTPOLICY() const                          { return ( ReadFloat( tblSLD_Fields[127] ) ); }
//    bool FASTCALL SLDDISCOUNTPOLICY_IsNull() const                        { return ( IsNull( tblSLD_Fields[127] ) ); }
//    void FASTCALL SetSLDDISCOUNTPOLICY( double value )                    { WriteFloat( tblSLD_Fields[127], value ); }
//
//    double FASTCALL GetSLDDISCOUNTPOLICYBC() const                        { return ( ReadFloat( tblSLD_Fields[128] ) ); }
//    bool FASTCALL SLDDISCOUNTPOLICYBC_IsNull() const                      { return ( IsNull( tblSLD_Fields[128] ) ); }
//    void FASTCALL SetSLDDISCOUNTPOLICYBC( double value )                  { WriteFloat( tblSLD_Fields[128], value ); }
//
//    double FASTCALL GetTDODETAILTRMTOTAL() const                          { return ( ReadFloat( tblSLD_Fields[129] ) ); }
//    bool FASTCALL TDODETAILTRMTOTAL_IsNull() const                        { return ( IsNull( tblSLD_Fields[129] ) ); }
//    void FASTCALL SetTDODETAILTRMTOTAL( double value )                    { WriteFloat( tblSLD_Fields[129], value ); }
//
//    double FASTCALL GetTDODETAILTRMTOTALBC() const                        { return ( ReadFloat( tblSLD_Fields[130] ) ); }
//    bool FASTCALL TDODETAILTRMTOTALBC_IsNull() const                      { return ( IsNull( tblSLD_Fields[130] ) ); }
//    void FASTCALL SetTDODETAILTRMTOTALBC( double value )                  { WriteFloat( tblSLD_Fields[130], value ); }
//
//    int FASTCALL GetCONID() const                                         { return ( ReadInteger( tblSLD_Fields[131] ) ); }
//    bool FASTCALL CONID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[131] ) ); }
//    void FASTCALL SetCONID( int value )                                   { WriteInteger( tblSLD_Fields[131], value ); }
//
//    int FASTCALL GetDOCIDTRIANGLE() const                                 { return ( ReadInteger( tblSLD_Fields[132] ) ); }
//    bool FASTCALL DOCIDTRIANGLE_IsNull() const                            { return ( IsNull( tblSLD_Fields[132] ) ); }
//    void FASTCALL SetDOCIDTRIANGLE( int value )                           { WriteInteger( tblSLD_Fields[132], value ); }
//
//    short FASTCALL GetTRIANGLESUBSYSID() const                            { return ( ReadShort( tblSLD_Fields[133] ) ); }
//    bool FASTCALL TRIANGLESUBSYSID_IsNull() const                         { return ( IsNull( tblSLD_Fields[133] ) ); }
//    void FASTCALL SetTRIANGLESUBSYSID( short value )                      { WriteShort( tblSLD_Fields[133], value ); }
//
//    int FASTCALL GetDOCIDTRIANGLEFROM() const                             { return ( ReadInteger( tblSLD_Fields[134] ) ); }
//    bool FASTCALL DOCIDTRIANGLEFROM_IsNull() const                        { return ( IsNull( tblSLD_Fields[134] ) ); }
//    void FASTCALL SetDOCIDTRIANGLEFROM( int value )                       { WriteInteger( tblSLD_Fields[134], value ); }
//
//    short FASTCALL GetTRIANGLESUBSYSIDFROM() const                        { return ( ReadShort( tblSLD_Fields[135] ) ); }
//    bool FASTCALL TRIANGLESUBSYSIDFROM_IsNull() const                     { return ( IsNull( tblSLD_Fields[135] ) ); }
//    void FASTCALL SetTRIANGLESUBSYSIDFROM( short value )                  { WriteShort( tblSLD_Fields[135], value ); }
//
//    int FASTCALL GetTRAIDPRINCIPAL() const                                { return ( ReadInteger( tblSLD_Fields[136] ) ); }
//    bool FASTCALL TRAIDPRINCIPAL_IsNull() const                           { return ( IsNull( tblSLD_Fields[136] ) ); }
//    void FASTCALL SetTRAIDPRINCIPAL( int value )                          { WriteInteger( tblSLD_Fields[136], value ); }
//
//    int FASTCALL GetPRTID() const                                         { return ( ReadInteger( tblSLD_Fields[137] ) ); }
//    bool FASTCALL PRTID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[137] ) ); }
//    void FASTCALL SetPRTID( int value )                                   { WriteInteger( tblSLD_Fields[137], value ); }
//
//    int FASTCALL GetADRIDDELIVERY() const                                 { return ( ReadInteger( tblSLD_Fields[138] ) ); }
//    bool FASTCALL ADRIDDELIVERY_IsNull() const                            { return ( IsNull( tblSLD_Fields[138] ) ); }
//    void FASTCALL SetADRIDDELIVERY( int value )                           { WriteInteger( tblSLD_Fields[138], value ); }
//
//    smds::cDateTime FASTCALL GetSLDPROCESSDATE() const                    { return ( ReadDate( tblSLD_Fields[139] ) ); }
//    bool FASTCALL SLDPROCESSDATE_IsNull() const                           { return ( IsNull( tblSLD_Fields[139] ) ); }
//    void FASTCALL SetSLDPROCESSDATE( const smds::cDateTime& value )       { WriteDate( tblSLD_Fields[139], value ); }
//
//    int FASTCALL GetTDOCOLONNUMBER() const                                { return ( ReadInteger( tblSLD_Fields[140] ) ); }
//    bool FASTCALL TDOCOLONNUMBER_IsNull() const                           { return ( IsNull( tblSLD_Fields[140] ) ); }
//    void FASTCALL SetTDOCOLONNUMBER( int value )                          { WriteInteger( tblSLD_Fields[140], value ); }
//
//    double FASTCALL GetTDOQTYAGUARANTEE() const                           { return ( ReadFloat( tblSLD_Fields[141] ) ); }
//    bool FASTCALL TDOQTYAGUARANTEE_IsNull() const                         { return ( IsNull( tblSLD_Fields[141] ) ); }
//    void FASTCALL SetTDOQTYAGUARANTEE( double value )                     { WriteFloat( tblSLD_Fields[141], value ); }
//
//    double FASTCALL GetTDOQTYBGUARANTEE() const                           { return ( ReadFloat( tblSLD_Fields[142] ) ); }
//    bool FASTCALL TDOQTYBGUARANTEE_IsNull() const                         { return ( IsNull( tblSLD_Fields[142] ) ); }
//    void FASTCALL SetTDOQTYBGUARANTEE( double value )                     { WriteFloat( tblSLD_Fields[142], value ); }
//
//    double FASTCALL GetTDOGUARANTEERECEIVEDVALUE() const                  { return ( ReadFloat( tblSLD_Fields[143] ) ); }
//    bool FASTCALL TDOGUARANTEERECEIVEDVALUE_IsNull() const                { return ( IsNull( tblSLD_Fields[143] ) ); }
//    void FASTCALL SetTDOGUARANTEERECEIVEDVALUE( double value )            { WriteFloat( tblSLD_Fields[143], value ); }
//
//    double FASTCALL GetTDOGUARANTEERECEIVEDVALUEBC() const                { return ( ReadFloat( tblSLD_Fields[144] ) ); }
//    bool FASTCALL TDOGUARANTEERECEIVEDVALUEBC_IsNull() const              { return ( IsNull( tblSLD_Fields[144] ) ); }
//    void FASTCALL SetTDOGUARANTEERECEIVEDVALUEBC( double value )          { WriteFloat( tblSLD_Fields[144], value ); }
//
//    double FASTCALL GetTDOGUARANTEERETURNEDVALUE() const                  { return ( ReadFloat( tblSLD_Fields[145] ) ); }
//    bool FASTCALL TDOGUARANTEERETURNEDVALUE_IsNull() const                { return ( IsNull( tblSLD_Fields[145] ) ); }
//    void FASTCALL SetTDOGUARANTEERETURNEDVALUE( double value )            { WriteFloat( tblSLD_Fields[145], value ); }
//
//    double FASTCALL GetTDOGUARANTEERETURNEDVALUEBC() const                { return ( ReadFloat( tblSLD_Fields[146] ) ); }
//    bool FASTCALL TDOGUARANTEERETURNEDVALUEBC_IsNull() const              { return ( IsNull( tblSLD_Fields[146] ) ); }
//    void FASTCALL SetTDOGUARANTEERETURNEDVALUEBC( double value )          { WriteFloat( tblSLD_Fields[146], value ); }
//
//    int FASTCALL GetTTYIDTRADERGUARANTEE() const                          { return ( ReadInteger( tblSLD_Fields[147] ) ); }
//    bool FASTCALL TTYIDTRADERGUARANTEE_IsNull() const                     { return ( IsNull( tblSLD_Fields[147] ) ); }
//    void FASTCALL SetTTYIDTRADERGUARANTEE( int value )                    { WriteInteger( tblSLD_Fields[147], value ); }
//
//    int FASTCALL GetTTYIDSTOCKITEMGUARANTEE() const                       { return ( ReadInteger( tblSLD_Fields[148] ) ); }
//    bool FASTCALL TTYIDSTOCKITEMGUARANTEE_IsNull() const                  { return ( IsNull( tblSLD_Fields[148] ) ); }
//    void FASTCALL SetTTYIDSTOCKITEMGUARANTEE( int value )                 { WriteInteger( tblSLD_Fields[148], value ); }
//
//    int FASTCALL GetADRIDBRANCH() const                                   { return ( ReadInteger( tblSLD_Fields[149] ) ); }
//    bool FASTCALL ADRIDBRANCH_IsNull() const                              { return ( IsNull( tblSLD_Fields[149] ) ); }
//    void FASTCALL SetADRIDBRANCH( int value )                             { WriteInteger( tblSLD_Fields[149], value ); }
//
//    short FASTCALL GetTDOTRANSFORMEDCANCELED() const                      { return ( ReadShort( tblSLD_Fields[150] ) ); }
//    bool FASTCALL TDOTRANSFORMEDCANCELED_IsNull() const                   { return ( IsNull( tblSLD_Fields[150] ) ); }
//    void FASTCALL SetTDOTRANSFORMEDCANCELED( short value )                { WriteShort( tblSLD_Fields[150], value ); }
//
//    short FASTCALL GetTDOTRADERTRANSSIGN() const                          { return ( ReadShort( tblSLD_Fields[151] ) ); }
//    bool FASTCALL TDOTRADERTRANSSIGN_IsNull() const                       { return ( IsNull( tblSLD_Fields[151] ) ); }
//    void FASTCALL SetTDOTRADERTRANSSIGN( short value )                    { WriteShort( tblSLD_Fields[151], value ); }
//
//    short FASTCALL GetTDOGUARANTEETRADERTRANSSIGN() const                 { return ( ReadShort( tblSLD_Fields[152] ) ); }
//    bool FASTCALL TDOGUARANTEETRADERTRANSSIGN_IsNull() const              { return ( IsNull( tblSLD_Fields[152] ) ); }
//    void FASTCALL SetTDOGUARANTEETRADERTRANSSIGN( short value )           { WriteShort( tblSLD_Fields[152], value ); }
//
//    double FASTCALL GetTDOPOLICYDISCOUNT() const                          { return ( ReadFloat( tblSLD_Fields[153] ) ); }
//    bool FASTCALL TDOPOLICYDISCOUNT_IsNull() const                        { return ( IsNull( tblSLD_Fields[153] ) ); }
//    void FASTCALL SetTDOPOLICYDISCOUNT( double value )                    { WriteFloat( tblSLD_Fields[153], value ); }
//
//    double FASTCALL GetTDOPOLICYDISCOUNTBC() const                        { return ( ReadFloat( tblSLD_Fields[154] ) ); }
//    bool FASTCALL TDOPOLICYDISCOUNTBC_IsNull() const                      { return ( IsNull( tblSLD_Fields[154] ) ); }
//    void FASTCALL SetTDOPOLICYDISCOUNTBC( double value )                  { WriteFloat( tblSLD_Fields[154], value ); }
//
//    double FASTCALL GetTDOTRANSDISCOUNT() const                           { return ( ReadFloat( tblSLD_Fields[155] ) ); }
//    bool FASTCALL TDOTRANSDISCOUNT_IsNull() const                         { return ( IsNull( tblSLD_Fields[155] ) ); }
//    void FASTCALL SetTDOTRANSDISCOUNT( double value )                     { WriteFloat( tblSLD_Fields[155], value ); }
//
//    double FASTCALL GetTDOTRANSDISCOUNTBC() const                         { return ( ReadFloat( tblSLD_Fields[156] ) ); }
//    bool FASTCALL TDOTRANSDISCOUNTBC_IsNull() const                       { return ( IsNull( tblSLD_Fields[156] ) ); }
//    void FASTCALL SetTDOTRANSDISCOUNTBC( double value )                   { WriteFloat( tblSLD_Fields[156], value ); }
//
//    int FASTCALL GetDIPIDTRANSACTION() const                              { return ( ReadInteger( tblSLD_Fields[157] ) ); }
//    bool FASTCALL DIPIDTRANSACTION_IsNull() const                         { return ( IsNull( tblSLD_Fields[157] ) ); }
//    void FASTCALL SetDIPIDTRANSACTION( int value )                        { WriteInteger( tblSLD_Fields[157], value ); }
//
//    int FASTCALL GetBRAID() const                                         { return ( ReadInteger( tblSLD_Fields[158] ) ); }
//    bool FASTCALL BRAID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[158] ) ); }
//    void FASTCALL SetBRAID( int value )                                   { WriteInteger( tblSLD_Fields[158], value ); }
//
//    int FASTCALL GetTRMID() const                                         { return ( ReadInteger( tblSLD_Fields[159] ) ); }
//    bool FASTCALL TRMID_IsNull() const                                    { return ( IsNull( tblSLD_Fields[159] ) ); }
//    void FASTCALL SetTRMID( int value )                                   { WriteInteger( tblSLD_Fields[159], value ); }
//
//    short FASTCALL GetTDOCOPYTRMID() const                                { return ( ReadShort( tblSLD_Fields[160] ) ); }
//    bool FASTCALL TDOCOPYTRMID_IsNull() const                             { return ( IsNull( tblSLD_Fields[160] ) ); }
//    void FASTCALL SetTDOCOPYTRMID( short value )                          { WriteShort( tblSLD_Fields[160], value ); }
//
//    smds::cDateTime FASTCALL GetTDOPAYMENTSTARTDATE() const               { return ( ReadDate( tblSLD_Fields[161] ) ); }
//    bool FASTCALL TDOPAYMENTSTARTDATE_IsNull() const                      { return ( IsNull( tblSLD_Fields[161] ) ); }
//    void FASTCALL SetTDOPAYMENTSTARTDATE( const smds::cDateTime& value )  { WriteDate( tblSLD_Fields[161], value ); }
//
//    int FASTCALL GetTDOACCEPTDAYS() const                                 { return ( ReadInteger( tblSLD_Fields[162] ) ); }
//    bool FASTCALL TDOACCEPTDAYS_IsNull() const                            { return ( IsNull( tblSLD_Fields[162] ) ); }
//    void FASTCALL SetTDOACCEPTDAYS( int value )                           { WriteInteger( tblSLD_Fields[162], value ); }
//
//    int FASTCALL GetTDODRIVECURID() const                                 { return ( ReadInteger( tblSLD_Fields[163] ) ); }
//    bool FASTCALL TDODRIVECURID_IsNull() const                            { return ( IsNull( tblSLD_Fields[163] ) ); }
//    void FASTCALL SetTDODRIVECURID( int value )                           { WriteInteger( tblSLD_Fields[163], value ); }
//
//    int FASTCALL GetTDOTRADERCURID() const                                { return ( ReadInteger( tblSLD_Fields[164] ) ); }
//    bool FASTCALL TDOTRADERCURID_IsNull() const                           { return ( IsNull( tblSLD_Fields[164] ) ); }
//    void FASTCALL SetTDOTRADERCURID( int value )                          { WriteInteger( tblSLD_Fields[164], value ); }
//
//    double FASTCALL GetTDOTRADEREQUIVALENCE() const                       { return ( ReadFloat( tblSLD_Fields[165] ) ); }
//    bool FASTCALL TDOTRADEREQUIVALENCE_IsNull() const                     { return ( IsNull( tblSLD_Fields[165] ) ); }
//    void FASTCALL SetTDOTRADEREQUIVALENCE( double value )                 { WriteFloat( tblSLD_Fields[165], value ); }
//
//    ds_string FASTCALL GetTDOTRADEREQVTYPE() const                        { return ( ReadString( tblSLD_Fields[166] ) ); }
//    bool FASTCALL TDOTRADEREQVTYPE_IsNull() const                         { return ( IsNull( tblSLD_Fields[166] ) ); }
//    void FASTCALL SetTDOTRADEREQVTYPE( const ds_string& value )           { WriteString( tblSLD_Fields[166], value ); }
//
//    double FASTCALL GetTDOTRADERAUDITEQUIVALENCE() const                  { return ( ReadFloat( tblSLD_Fields[167] ) ); }
//    bool FASTCALL TDOTRADERAUDITEQUIVALENCE_IsNull() const                { return ( IsNull( tblSLD_Fields[167] ) ); }
//    void FASTCALL SetTDOTRADERAUDITEQUIVALENCE( double value )            { WriteFloat( tblSLD_Fields[167], value ); }
//
//    short FASTCALL GetTDOTRAAUDITEQVONEBASED() const                      { return ( ReadShort( tblSLD_Fields[168] ) ); }
//    bool FASTCALL TDOTRAAUDITEQVONEBASED_IsNull() const                   { return ( IsNull( tblSLD_Fields[168] ) ); }
//    void FASTCALL SetTDOTRAAUDITEQVONEBASED( short value )                { WriteShort( tblSLD_Fields[168], value ); }
//
//    ds_string FASTCALL GetSLDDELIVERYPLACE() const                        { return ( ReadString( tblSLD_Fields[169] ) ); }
//    bool FASTCALL SLDDELIVERYPLACE_IsNull() const                         { return ( IsNull( tblSLD_Fields[169] ) ); }
//    void FASTCALL SetSLDDELIVERYPLACE( const ds_string& value )           { WriteString( tblSLD_Fields[169], value ); }
//};
//
//typedef smds::cuTable<tblSLD_rec>  tblSLD;
//typedef smds::shared_ptr<tblSLD>   tblSLD_ptr;
//---------------------------------------------------------------------------
#endif
