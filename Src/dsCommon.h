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
#ifndef SM_DS_COMMON_H
#define SM_DS_COMMON_H
//---------------------------------------------------------------------------
#include "dsConfig.h"
#include <string>
//---------------------------------------------------------------------------

namespace smds
{

inline int FASTCALL StringCompare( const char *str1, const char *str2 );

#if defined ( __BORLANDC__ )
inline int FASTCALL StringCompare( const char *str1, const char *str2 )     { return stricmp( str1, str2 ); }
#endif

#if defined ( _MSC_VER )
inline int FASTCALL StringCompare( const char *str1, const char *str2 )     { return _stricmp( str1, str2 ); }
#endif

#if defined ( __GNUG__ )
    #if defined (__WIN32__)
inline int FASTCALL StringCompare( const char *str1, const char *str2 )     { return stricmp( str1, str2 ); }
    #endif
    #if defined (__linux__)
inline int FASTCALL StringCompare( const char *str1, const char *str2 )     { return strcasecmp( str1, str2 ); }
    #endif
#endif

}; // namespace smds
//---------------------------------------------------------------------------
#endif
