//---------------------------------------------------------------------------
#ifndef SM_DS_DATETIME_H
#define SM_DS_DATETIME_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <ssport.h>
#include "dsStream.h"

namespace ds
{

// Data types
#pragma pack( push, 1 )

/*
struct cDateTime
{
    unsigned int Date;
    unsigned int Time;
};
*/

class cDateTime
{
private:
    //friend double operator - ( const cDateTime& left, const cDateTime& right );
    //friend bool operator <= ( const cDateTime& left, const cDateTime& right );
    //friend bool operator < ( const cDateTime& left, const cDateTime& right );
    friend cStream& FASTCALL operator << ( cStream& st, const cDateTime a );
    friend cStream& FASTCALL operator >> ( cStream& st, cDateTime& a );
    double  mValue;
public:
    CDFASTCALL cDateTime() : mValue(0)                                  {} // empty
    CDFASTCALL cDateTime( const double& value ) : mValue(value)         {} // empty
    double FASTCALL AsDouble() const                                    { return ( mValue ); }
    double FASTCALL Date() const                                        { return ( static_cast<double>(static_cast<int>(mValue)) ); }
    cDateTime& FASTCALL operator += ( int days )
    {
        mValue += days;
        return ( *this );
    }
    cDateTime& FASTCALL operator -= ( int days )
    {
        mValue -= days;
        return ( *this );
    }
    cDateTime FASTCALL operator + ( int days )
    {
        cDateTime   tmp( *this );

        tmp += days;
        return ( tmp );
    }
    bool operator <= ( const cDateTime& right )                         { return ( mValue <= right.mValue ); }
    bool operator < ( const cDateTime& right )                          { return ( mValue < right.mValue ); }
};

//inline double operator - ( const cDateTime& left, const cDateTime& right )
//{
//    return ( left.mValue - right.mValue );
//}
//
//inline bool operator <= ( const cDateTime& left, const cDateTime& right )
//{
//    return ( left.mValue <= right.mValue );
//}
//
//inline bool operator < ( const cDateTime& left, const cDateTime& right )
//{
//    return ( left.mValue < right.mValue );
//}

cStream& FASTCALL operator << ( cStream& st, const cDateTime a );
cStream& FASTCALL operator >> ( cStream& st, cDateTime& a );

//typedef double  cDateTime;

#pragma pack( pop )

};
//---------------------------------------------------------------------------
#endif
