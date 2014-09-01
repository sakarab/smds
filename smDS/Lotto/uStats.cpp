//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "uStats.h"
#include "uFuncs.h"
#include <vector>
//---------------------------------------------------------------------------

StatEntry   AvailableStats::Statistics[] =
{
    {   "Συχνότητα εμφάνισης",
        "Σύνολο εμφάνισης αριθμών και % (επί τοις εκατό)",
        Frequency
    },
};

//***********************************************************************
//******    AvailableStats
//***********************************************************************
int AvailableStats::Count()
{
    return ( sizeof(Statistics) / sizeof(Statistics[0]) );
}

const StatEntry& AvailableStats::GetStat( int idx )
{
    if ( idx >= 0 && idx < Count() )
        return Statistics[idx];
    throw Exception( "Out of index" );
}

//***********************************************************************
//******    GridPrinter
//***********************************************************************
GridPrinter::GridPrinter( TStringGrid *grid )
    : mGrid(grid), mCurrentRow(grid->RowCount - 1)
{
}

void GridPrinter::NewLine()
{
    int     count = mGrid->RowCount;

    mGrid->RowCount = count + 1;
    mCurrentRow = count;
}

void GridPrinter::Print( int col, const char *text )
{
    mGrid->Cells[col][mCurrentRow] = text;
}

void GridPrinter::Print( int col, int text )
{
    mGrid->Cells[col][mCurrentRow] = IntToStr( text );
}

void GridPrinter::Print( int col, double text )
{
    mGrid->Cells[col][mCurrentRow] = AnsiString().sprintf( "%2.2f", text );
}

//---------------------------------------------------------------------------

