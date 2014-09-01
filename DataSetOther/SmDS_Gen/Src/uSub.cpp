//---------------------------------------------------------------------------
#pragma hdrstop
#include "uSub.h"
#include <string>
//---------------------------------------------------------------------------
// ftUnknown, ftString, ftSmallint, ftInteger, ftWord, ftBoolean, ftFloat, ftCurrency, ftBCD, ftDate,
// ftTime, ftDateTime, ftBytes, ftVarBytes, ftAutoInc, ftBlob, ftMemo, ftGraphic, ftFmtMemo, ftParadoxOle,
// ftDBaseOle, ftTypedBinary, ftCursor, ftFixedChar, ftWideString, ftLargeint, ftADT, ftArray, ftReference,
// ftDataSet, ftOraBlob, ftOraClob, ftVariant, ftInterface, ftIDispatch, ftGuid, ftTimeStamp, ftFMTBcd

namespace sub
{

const char * SelectDataType( TField *fld )
{
    switch ( fld->DataType )
    {
        case ftString   : return "ds_string";
        case ftSmallint : return "short";
        case ftInteger  : return "int";
        case ftBoolean  : return "bool";
        case ftFloat    : return "double";
        case ftDate     :
        case ftTime     :
        case ftDateTime : return "smds::cDateTime";
        default : throw Exception( AnsiString( "unsupported field DataType " ) + AnsiString( fld->DataType ) );
    }
}

const char * SelectFieldType( TField *fld )
{
    switch ( fld->DataType )
    {
        case ftString   : return "ftString";
        case ftSmallint : return "ftShort";
        case ftInteger  : return "ftInteger";
        case ftBoolean  : return "ftBool";
        case ftFloat    : return "ftDouble";
        case ftDate     :
        case ftTime     :
        case ftDateTime : return "ftDateTime";
        default : throw Exception( AnsiString( "unsupported field DataType " ) + AnsiString( fld->DataType ) );
    }
}

const char * SelectRW( TField *fld )
{
    switch ( fld->DataType )
    {
        case ftString   : return "String";
        case ftSmallint : return "Short";
        case ftInteger  : return "Integer";
        case ftBoolean  : return "Bool";
        case ftFloat    : return "Float";
        case ftDate     :
        case ftTime     :
        case ftDateTime : return "Date";
        default : throw Exception( AnsiString( "unsupported field DataType " ) + AnsiString( fld->DataType ) );
    }
}

inline const AnsiString Sormat( const AnsiString& arg )
{
    return ( arg );
}

typedef std::vector<AnsiString>::iterator   hiter;
typedef std::vector<std::string>            Line;

Line GetLine( const AnsiString& sstr )
{
    std::string             str( sstr.c_str() );
    Line                    result;
    std::string::size_type  pos = 0;
    std::string::size_type  new_pos;

    while ( (new_pos = str.find( '\t', pos )) != std::string::npos )
    {
        std::string     new_str = str.substr( pos, new_pos - pos );

        result.push_back( new_str );
        str.erase( new_pos, 1 );
        pos = new_pos;
    }
    result.push_back( str.substr( pos, str.size() ) );
    return ( result );
}

std::vector<Line>::size_type GetMaxColumns( std::vector<Line>& lines )
{
    std::vector<Line>::iterator     first = lines.begin(),
                                    last = lines.end();
    std::vector<Line>::size_type    result = 0;

    while ( first != last )
    {
        if ( first->size() > result )
            result = first->size();
        ++first;
    }
    return ( result );
}

std::vector<Line>::size_type GetMaxColWidth( std::vector<Line>& lines, std::vector<Line>::size_type col )
{
    std::vector<Line>::iterator     first = lines.begin(),
                                    last = lines.end();
    std::vector<Line>::size_type    result = 0;

    while ( first != last )
    {
        if ( col < first->size() )
        {
            if ( (*first)[col].size() > result )
                result = (*first)[col].size();
        }
        ++first;
    }
    return ( result + 2 );
}

void ExpandLines( std::vector<Line>& lines, std::vector<Line>::size_type col_width, std::vector<Line>::size_type col )
{
    std::vector<Line>::iterator     first = lines.begin(),
                                    last = lines.end();

    while ( first != last )
    {
        if ( col < first->size() - 1 )
        {
            std::string::size_type  size = (*first)[col].size();

            if ( size < col_width )
                (*first)[col].insert( size, col_width - size, ' ' );
        }
        ++first;
    }
}

void __fastcall ProccessRange( hiter first, hiter last )
{
    if ( first == last )
        return;

    hiter               first_copy = first;
    std::vector<Line>   lines;

    while ( first != last )
    {
        lines.push_back( GetLine( *first ) );
        ++first;
    }

    std::vector<Line>::size_type                max_cols = GetMaxColumns( lines );
    std::vector< std::vector<Line>::size_type > col_widths;

    for ( std::vector<Line>::size_type n = 0 ; n < max_cols ; ++n )
        col_widths.push_back( GetMaxColWidth( lines, n ) );
    for ( std::vector<Line>::size_type n = 0 ; n < max_cols ; ++n )
        ExpandLines( lines, col_widths[n], n );

    std::vector<Line>::iterator     line = lines.begin();

    first = first_copy;
    while ( first != last )
    {
        std::string line_str;

        for ( std::vector<std::string>::iterator    n = line->begin(), eend = line->end() ; n != eend ; ++n )
            line_str += *n;
        *first = AnsiString( line_str.c_str() );
        ++line;
        ++first;
    }
}

hiter __fastcall GetFirst( hiter first, hiter last )
{
    while ( first != last )
    {
        if ( first->Length() > 0 && (*first)[1] == '\t' )
        {
            *first = first->SubString( 2, first->Length() );
            ++first;
            break;
        }
        ++first;
    }
    return ( first );
}

hiter __fastcall GetNext( hiter first, hiter last )
{
    while ( first != last )
    {
        if ( first->Length() > 0 && (*first)[1] == '\t' )
        {
            *first = first->SubString( 2, first->Length() );
            break;
        }
        ++first;
    }
    return ( first );
}

void __fastcall ProccessH( std::vector<AnsiString>& h )
{
    hiter   first = GetFirst( h.begin(), h.end() );

    do
    {
        hiter   last = GetNext( first, h.end() );

        ProccessRange( first, last );
        first = last;
        ++first;
    }
    while ( first != h.end() );
}

void __fastcall Run( TFields *fields, const AnsiString& prefix, const AnsiString& table_name,
                     std::vector<AnsiString>& h )
{
    AnsiString              long_prefix = prefix + table_name;

    // class <name>_map
    h.push_back( Format( "class %s_map", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Sormat( "{" ) );
    h.push_back( Sormat( "private:" ) );
    h.push_back( Format( "    %s_map();", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Format( "    %s_map( const %s_map& src );", ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Format( "    %s_map& operator = ( const %s_map& src );", ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Sormat( "\tpublic:" ) );
    for ( int n = 0, eend = fields->Count ; n < eend ; ++n )
    {
        TField      *fld = fields->Fields[n];

        if ( fld->DataType == ftString )
            h.push_back( Format( "    STRING_FM\t(%s_,%d);", ARRAYOFCONST(( fld->FieldName, fld->Size )) ) );
        else
            h.push_back( Format( "    %s\t%s_;", ARRAYOFCONST(( SelectDataType( fld ), fld->FieldName )) ) );
    }
    h.push_back( Sormat( "};" ) );
    h.push_back( Sormat( "\t" ) );

    // class <name>_data
    h.push_back( Format( "class %s_data", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Sormat( "{" ) );
    h.push_back( Sormat( "\tprotected:" ) );
    h.push_back( Format( "    static const smds::cFieldDef_\t%s_Fields[];", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Format( "    static const smds::cFieldDefs_\t%s_FieldDef;", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Sormat( "};" ) );
    h.push_back( Sormat( "\t" ) );

    // class <name>_raw
    h.push_back( Format( "class %s_raw : public %s_data, public smds::cRawRecordPtr", ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Sormat( "{" ) );
    h.push_back( Sormat( "public:" ) );
    h.push_back( Format( "\t    CDFASTCALL %s_raw( smds::cRawBuffer& raw_buffer )", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Sormat( "        : smds::cRawRecordPtr(raw_buffer)\t{} // empty" ) );
    h.push_back( Format( "    %s_raw * FASTCALL operator->()\t{ return ( this ); }", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Format( "    const %s_raw * FASTCALL operator->() const\t{ return ( this ); }", ARRAYOFCONST(( long_prefix )) ) );
    for ( int n = 0, eend = fields->Count ; n < eend ; ++n )
    {
        TField      *fld = fields->Fields[n];

        h.push_back( Sormat( "" ) );
        h.push_back( Format( "    %s FASTCALL Get%s() const\t{ return ( Read%s( %s_Fields[%d] ) ); }",
                             ARRAYOFCONST(( SelectDataType( fld ), fld->FieldName, SelectRW( fld ), long_prefix, n )) ) );
        h.push_back( Format( "    bool FASTCALL %s_IsNull() const\t{ return ( IsNull( %s_Fields[%d] ) ); }",
                             ARRAYOFCONST(( fld->FieldName, long_prefix, n )) ) );
    }
    h.push_back( Sormat( "};" ) );
    h.push_back( Sormat( "\t" ) );

    // class <name>_rec
    h.push_back( Format( "class %s_rec : public %s_data, public smds::cRecordPtr", ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Sormat( "{" ) );
    h.push_back( Sormat( "\tpublic:" ) );
    h.push_back( Format( "    typedef %s_raw    raw;", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Sormat( "public:" ) );
    h.push_back( Format( "\t    CDFASTCALL %s_rec( smds::cDoubleBuffer& double_buffer )", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Sormat( "        : smds::cRecordPtr(double_buffer)\t{} // empty" ) );
    h.push_back( Format( "    %s_rec * FASTCALL operator->()\t{ return ( this ); }", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Format( "    const %s_rec * FASTCALL operator->() const\t{ return ( this ); }", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Sormat( "\t    static const smds::cFieldDefs_& FASTCALL GetFieldDefs();" ) );
    for ( int n = 0, eend = fields->Count ; n < eend ; ++n )
    {
        TField      *fld = fields->Fields[n];

        h.push_back( Sormat( "" ) );
        h.push_back( Format( "    %s FASTCALL Get%s() const\t{ return ( Read%s( %s_Fields[%d] ) ); }",
                             ARRAYOFCONST(( SelectDataType( fld ), fld->FieldName, SelectRW( fld ), long_prefix, n )) ) );
        h.push_back( Format( "    bool FASTCALL %s_IsNull() const\t{ return ( IsNull( %s_Fields[%d] ) ); }",
                             ARRAYOFCONST(( fld->FieldName, long_prefix, n )) ) );
        if ( fld->DataType == ftString )
        {
            h.push_back( Format( "    void FASTCALL Set%s( const %s& value )\t{ Write%s( %s_Fields[%d], value ); }",
                                 ARRAYOFCONST(( fld->FieldName, SelectDataType( fld ), SelectRW( fld ), long_prefix, n )) ) );
        }
        else if ( fld->DataType == ftDateTime )
        {
            h.push_back( Format( "    void FASTCALL Set%s( const %s& value )\t{ Write%s( %s_Fields[%d], value ); }",
                                 ARRAYOFCONST(( fld->FieldName, SelectDataType( fld ), SelectRW( fld ), long_prefix, n )) ) );
        }
        else
            h.push_back( Format( "    void FASTCALL Set%s( %s value )\t{ Write%s( %s_Fields[%d], value ); }",
                                 ARRAYOFCONST(( fld->FieldName, SelectDataType( fld ), SelectRW( fld ), long_prefix, n )) ) );
    }
    h.push_back( Sormat( "};" ) );
    h.push_back( Sormat( "\t" ) );

    // typedefs
    h.push_back( Format( "typedef smds::cuTable<%s_rec>\t%s;", ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Format( "typedef smds::shared_ptr<%s>\t%s_ptr;", ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Sormat( "\t-----------------------------------------------------------------------------------------------------" ) );

    // fields
    h.push_back( Format( "const smds::cFieldDef_\t%s_data::%s_Fields[] =", ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Sormat( "\t{" ) );
    for ( int n = 0, eend = fields->Count ; n < eend ; ++n )
    {
        TField      *fld = fields->Fields[n];

        if ( fld->DataType == ftString )
            h.push_back( Format( "    { %3d,\toffsetof(%s_map,%s_),\t\"%s\",\tsmds::fkData,\tsmds::%s,\t%4d },",
                                        ARRAYOFCONST(( n, long_prefix, fld->FieldName, fld->FieldName, SelectFieldType( fld ), fld->DataSize - 1 )) ) );
        else
            h.push_back( Format( "    { %3d,\toffsetof(%s_map,%s_),\t\"%s\",\tsmds::fkData,\tsmds::%s,\t%4d },",
                                        ARRAYOFCONST(( n, long_prefix, fld->FieldName, fld->FieldName, SelectFieldType( fld ), fld->DataSize )) ) );
    }
    h.push_back( Sormat( "};" ) );
    h.push_back( Sormat( "\t" ) );

    // field defs
    h.push_back( Format( "const smds::cFieldDefs_\t%s_data::%s_FieldDef =", ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Sormat( "\t{" ) );
    h.push_back( Format( "    sizeof(%s_map),", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Format( "    sizeof(%s_Fields)/sizeof(%s_Fields[0]),", ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Sormat( "    \"SELECT FileID, PathID, LongFileName, fSize, fDate, Description, zipID FROM %s %s\"," ) );
    h.push_back( Format( "    \"%s\",", ARRAYOFCONST(( table_name )) ) );
    h.push_back( Format( "    %s_Fields", ARRAYOFCONST(( long_prefix )) ) );
    h.push_back( Sormat( "};" ) );
    h.push_back( Sormat( "\t" ) );
    h.push_back( Format( "const smds::cFieldDefs_& FASTCALL %s_rec::GetFieldDefs()\t{ return ( %s_FieldDef ); }",
                         ARRAYOFCONST(( long_prefix, long_prefix )) ) );
    h.push_back( Sormat( "\t" ) );

    ProccessH( h );
}

void __fastcall RunQuery( TQuery *query, const AnsiString& prefix, const AnsiString& table_name,
                          const AnsiString& query_str, std::vector<AnsiString>& h )
{
    AnsiString      qstr;

    if ( ! query_str.IsEmpty() )
        qstr = query_str + AnsiString( " WHERE 0=1" );
    else
        qstr = Format( "SELECT * FROM %s WHERE 0=1", ARRAYOFCONST(( table_name )) );

    query->SQL->Text = qstr;

    OpenGuard<TQuery>       q( query );
    Run( query->Fields, prefix, table_name, h );
}

}; // namespace sub
//---------------------------------------------------------------------------


