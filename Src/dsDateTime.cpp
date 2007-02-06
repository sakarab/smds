//---------------------------------------------------------------------------
#pragma hdrstop

#include "dsDateTime.h"
//---------------------------------------------------------------------------

namespace ds
{

cStream& FASTCALL operator << ( cStream& st, const cDateTime a )
{
    return ( st.WriteBuffer( &a.mValue, sizeof(a.mValue) ) );
}

cStream& FASTCALL operator >> ( cStream& st, cDateTime& a )
{
	return ( st.ReadBuffer( &a.mValue, sizeof(a.mValue) ) );
}

};
//---------------------------------------------------------------------------

