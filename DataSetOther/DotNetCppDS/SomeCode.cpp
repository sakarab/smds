#include "stdafx.h"
#include <vector>

void DoCppJob( std::vector<int>& vec )
{
    for ( int n = 0 ; n < 100 ; ++n )
        vec.push_back( n );
}
