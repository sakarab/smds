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
