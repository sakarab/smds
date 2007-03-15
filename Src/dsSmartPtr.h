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

  Please read the "readme" file in the root directory of this
  package for more copyright and license information.
****************************************************************************/
//---------------------------------------------------------------------------
#ifndef SM_DS_SMARTPTR_H
#define SM_DS_SMARTPTR_H
//---------------------------------------------------------------------------

#include "dsConfig.h"
#include <algorithm>

#if defined ( SM_DS_USE_SMALL_SHARED_PTR )

#include "shared_in_ptr.hpp"

namespace ds
{

template <class T> class shared_ptr : public boost::shared_in_ptr<T>
{
private:
    typedef boost::shared_in_ptr<T>    inherited;
public:
    shared_ptr() : inherited()                                                  {}
    explicit shared_ptr( T *obj ) : inherited( obj )                            {}
    template<class Y> shared_ptr( const shared_ptr<Y>& r) : inherited( r )      {}
};

};

#if ! defined ( __BORLANDC__ )
namespace std
{

template<class T> inline void swap( ds::shared_ptr<T>& a, ds::shared_ptr<T>& b )
{
    a.swap( b );
}

};
#endif

#endif

//---------------------------------------------------------------------------

#if defined ( SM_DS_USE_BOOST_SMART_PTR )

#include <boost/smart_ptr.hpp>

namespace ds
{

template <class T> class shared_ptr : public boost::shared_ptr<T>
{
private:
    typedef boost::shared_ptr<T>    inherited;
public:
    shared_ptr() : inherited()                                                  {}
    explicit shared_ptr( T *obj ) : inherited( obj )                            {}
    template<class Y> shared_ptr(shared_ptr<Y> const & r) : inherited( r )      {}
};

};

#if ! defined ( __BORLANDC__ )
namespace std
{

template<class T> inline void swap( ds::shared_ptr<T>& a, ds::shared_ptr<T>& b )
{
    a.swap( b );
}

};
#endif

#endif

//---------------------------------------------------------------------------

#if defined ( SM_DS_USE_LOKI_SHARED_PTR )

#include <loki/SmartPtr.h>

namespace ds
{

template <class T> class shared_ptr : public Loki::SmartPtr< T,
                                                             Loki::RefCounted,
                                                             Loki::DisallowConversion,
                                                             Loki::NoCheck,
                                                             Loki::DefaultSPStorage
                                                            >
{
private:
    typedef Loki::SmartPtr< T, Loki::RefCounted, Loki::DisallowConversion,
                            Loki::NoCheck, Loki::DefaultSPStorage >             inherited;
public:
    shared_ptr() : inherited()                                                  {}
    explicit shared_ptr( T *obj ) : inherited( obj )                                     {}
    template<class Y> shared_ptr(shared_ptr<Y> const & r) : inherited( r )      {}
    T * get() const                                                             { return ( GetImpl( *this ) ); }
    //void reset( T *p )                                                          { inherited::Reset( inherited( p ) ) ); }
};

};

#if ! defined ( __BORLANDC__ )
namespace std
{

template<class T> inline void swap( ds::shared_ptr<T>& a, ds::shared_ptr<T>& b )
{
    a.Swap( b );
}

};
#endif

#endif

//---------------------------------------------------------------------------
#endif
