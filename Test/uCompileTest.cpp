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
#ifndef __GNUG__
#pragma hdrstop
#endif

#include "uCompileTest.h"
#include <dsData.h>
#include <dsIndex.h>
#include "uTables.h"
//---------------------------------------------------------------------------

/*
class A
#ifdef SM_DS_USE_SMALL_SHARED_PTR
    : public boost::shared_in_base<long>
#endif
{
public:
    int     mA;
};

typedef smds::shared_ptr<A>     spA;

class variables
{
private:
    spA     mA;
    int     mIdx;
protected:
    variables( const spA& a, int idx );
    variables( const variables& src );
    variables& operator = ( const variables& src );
    void Increment()                            { ++mIdx; }
    void Decrement()                            { --mIdx; }
    variables Add( variables& src, int num );
public:
    ~variables();
};

variables::variables( const spA& a, int idx )
    : mA(a), mIdx(idx)
{
}

variables::variables( const variables& src )
    : mA(src.mA), mIdx(src.mIdx)
{
}

variables& variables::operator = ( const variables& src )
{
    if ( this != &src )
    {
        mA = src.mA;
        mIdx = src.mIdx;
    }
    return *this;
}

variables::~variables()
{
}

variables variables::Add( variables& src, int num )
{
    variables   tmp( src );

    src.mIdx += num;
    return tmp;
}

template <class T> class varbase : public variables
{
protected:
    varbase( const spA& a, int idx )
        : variables(a,idx)                      {} // empty
    varbase( const variables& var )
        : variables(var)                        {} // empty
    T& Increment( T& ret )
    {
        variables::Increment();
        return ret;
    }
    T& Decrement( T& ret )
    {
        variables::Decrement();
        return ret;
    }
    T Add( variables& src, int num )
    {
        return T( variables::Add( src, num ) );
    }
};

class FIter : private varbase<FIter>
{
public:
    FIter( const spA& a, int idx )
        : varbase<FIter>(a,idx)                 {} // empty
    FIter( const variables& var )
        : varbase<FIter>(var)                   {} // empty
    FIter& operator++()                         { return varbase<FIter>::Increment( *this ); }
    FIter operator+( int num )                  { return varbase<FIter>::Add( *this, num ); }
};

template <class T> class variables
{
private:
    spA     mA;
    int     mIdx;
protected:
    variables( const spA& a, int idx )
        : mA(a), mIdx(idx)                  {} // empty
    T& Increment( T& ret )
    {
        ++mIdx;
        return ret;
    }
    T& Decrement( T& ret )
    {
        --mIdx;
        return ret;
    }
    T Add( variables& src, int num )
    {
        variables   tmp( src );

        src.mIdx += num;
        return T( tmp );
    }
};

class FIter : private variables<FIter>
{
public:
    FIter( const spA& a, int idx )
        : variables<FIter>(a,idx)               {} // empty
    FIter( const variables<FIter>& var )
        : variables<FIter>(var)                 {} // empty
    FIter& operator++()                         { return variables<FIter>::Increment( *this ); }
    FIter operator+( int num )                  { return variables<FIter>::Add( *this, num ); }
};

void dummy_main()
{
    spA     a( new A );
    FIter   it( a, 5 );

    ++it;
    it + 1;
    FIter   itb = ++it;

    itb = it + 1;
}
*/

using namespace smds;

void ConvertTypedData( tblFiles::index_ptr& idx )
{
    // tblFiles_ptr    ds = *idx;
}

void Tutorial()
{
    // Select engine
    DbEngine        engine = SelectDbEngine( "ADO" );

    // connect to database
    Database        database = engine.NewConnection( "" );

    // Create and open the dataset
    tblFiles_ptr    ds( new tblFiles() );

    ds->Open( database, 0 );

    // serially locate a record with PathID == 27
    tblFiles::iterator      iter = ds->GetIterator();

    while ( ! iter.eof() )
    {
        if ( ! iter->PathID_IsNull() && iter->GetPathID() == 27 )
            break;
        ++iter;
    }
    if ( ! iter.eof() )
    {
        //  found. do something with it
    }
    else
    {
        // report the error
    }

    // Create an index on "PathID" and "fSize" fields
    tblFiles::index_ptr     idx = ds->NewIndex( OpenIndexFields( cIndexField( "PathID" ), cIndexField( "fSize" ) ) );

    // find - binary search - a record with PathID == 27 and fSize == 45000
    tblFiles::index::iterator   idx_it = idx->Find( OpenValues( 27, 45000 ) );

    if ( ! idx_it.eof() )
    {
        //  found. do something with it
    }
    else
    {
        // report the error
    }

    // change all

}
//---------------------------------------------------------------------------

