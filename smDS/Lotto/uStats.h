//---------------------------------------------------------------------------
#ifndef uStatsH
#define uStatsH
//---------------------------------------------------------------------------
#include "uTables.h"
#include <Grids.hpp>
//---------------------------------------------------------------------------

struct StatEntry;

typedef void (*TStatFunc)( const StatEntry* self, spDRAWS& data, TStringGrid *grid );

struct StatEntry
{
    const char  *ShortDescr;
    const char  *LongDescr;
    TStatFunc   StatFunc;
    void Execute( spDRAWS& data, TStringGrid *grid ) const      { StatFunc( this, data, grid ); }
};

//***********************************************************************
//******    AvailableStats
//***********************************************************************
class AvailableStats
{
private:
    static StatEntry    Statistics[];
public:
    int Count();
    const StatEntry& GetStat( int idx );
};

//***********************************************************************
//******    GridPrinter
//***********************************************************************
class GridPrinter
{
private:
    TStringGrid     *mGrid;
    int             mCurrentRow;
    // non copyable
    GridPrinter( const GridPrinter& src );
    GridPrinter& operator=( const GridPrinter& src );
public:
    GridPrinter( TStringGrid *grid );
    int Lines() const                               { return mGrid->RowCount; }
    int CurrentLine() const                         { return mCurrentRow; }
    void NewLine();
    void Print( int col, const char *text );
    void Print( int col, int text );
    void Print( int col, double text );
};

//---------------------------------------------------------------------------
#endif
