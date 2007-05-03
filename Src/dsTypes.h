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
#if ! defined (SM_DS_TYPES_H)
#define SM_DS_TYPES_H

#include "dsConfig.h"
#include "dsSmartPtr.h"

/*
#if defined (__BORLANDC__) && ! defined (_NO_VCL)
    #include    <System.hpp>

    typedef AnsiString      ds_string;
#else
    #include    <string>

    typedef std::string     ds_string;
#endif
*/

#include "dsString.h"

typedef smds::string_tag    ds_sstring;
typedef smds::wstring_tag   ds_wstring;

#if defined ( SM_UNICODE )
    typedef ds_wstring      ds_string;
#else
    typedef ds_sstring      ds_string;
#endif

// foward declaration of types

namespace smds
{

//class cDoubleBuffer;
//typedef shared_ptr< cDoubleBuffer >     cDoubleBuffer_ptr;
//typedef cDoubleBuffer_ptr               cData_value_type;

namespace detail
{

class SortControler;

}; // namespace detail

}; // namespace smds

#endif


