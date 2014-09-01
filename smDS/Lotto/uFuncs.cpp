//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "uFuncs.h"
#include <vector>
//---------------------------------------------------------------------------

void Frequency( const StatEntry* self, spDRAWS& data, TStringGrid *grid )
{
    std::vector<int>        numbers( 50 );
    tDRAWS::iterator        it = data->GetIterator();

    while ( ! it.eof() )
    {
        ++numbers[it->getNum_1()];
        ++numbers[it->getNum_2()];
        ++numbers[it->getNum_3()];
        ++numbers[it->getNum_4()];
        ++numbers[it->getNum_5()];
        ++numbers[it->getNum_6()];
        ++it;
    }

    std::vector<double>     percent( 50 );

    for ( int n = 1 ; n < 50 ; ++n )
        percent[n] = static_cast<double>(numbers[n]) * 100.0 / 6 / static_cast<double>(data->RecordCount());

    GridPrinter     gp( grid );

    if ( gp.CurrentLine() != 0 )
        gp.NewLine();

    gp.Print( 0, self->ShortDescr );
    gp.NewLine();
    for ( int n = 1 ; n < 50 ; ++n )
        gp.Print( n-1, n );

    gp.NewLine();
    for ( int n = 1 ; n < 50 ; ++n )
        gp.Print( n-1, numbers[n] );

    gp.NewLine();
    for ( int n = 1 ; n < 50 ; ++n )
        gp.Print( n-1, percent[n] );
}

void Expectation( const StatEntry* self, spDRAWS& data, TStringGrid *grid )
{
    tDRAWS::index_ptr           idx = data->NewIndex( smds::cIndexField( "DDate" ) );

    tDRAWS::index::iterator     last = idx->GetIterator();

    if ( last.eof() )
        return;

    tDRAWS::index::iterator     next = last;

    ++next;
    if ( next.eof() )
        return;

    std::vector<int>        weight( 50 );

    while ( ! next.eof() )
    {
        ++numbers[next->getNum_1()];
        ++numbers[next->getNum_2()];
        ++numbers[next->getNum_3()];
        ++numbers[next->getNum_4()];
        ++numbers[next->getNum_5()];
        ++numbers[next->getNum_6()];
        ++it;
    }
}

