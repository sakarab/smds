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
#if ! defined (SM_DS_CONFIG_H)
#define SM_DS_CONFIG_H

/**********************************************************************************
/* Comment this to disable default shared_ptr selection ...
/**********************************************************************************/
#define SM_DS_DEFAULT_SHARED_PTR

/**********************************************************************************
/* ... or Uncomment one of the following to make shared_ptr selection
/**********************************************************************************/
//#define SM_DS_USE_BOOST_SMART_PTR
//#define SM_DS_USE_SMALL_SHARED_PTR
//#define SM_DS_USE_LOKI_SHARED_PTR

/**********************************************************************************
/* Uncomment this to make C++Builder 6 use the Rogue Wave STL
/**********************************************************************************/
//#define _USE_OLD_RW_STL

/**********************************************************************************
/* Uncomment this to make a debug build
/**********************************************************************************/
//#define SM_DS_DEBUG

/**********************************************************************************
/* Uncomment this to make a build with debug iterators (not yet implemented)
/**********************************************************************************/
//#define SM_DS_DEBUG_ITERATORS

/**********************************************************************************
/* Uncomment this so that the library raises an exception when field values are
/* null instead of returning the default value for the field type
/**********************************************************************************/
//#define SM_DS_NULL_VALUE_EXCEPTION

/**********************************************************************************
/* Uncomment this so that the raw record buffer class (cRawBuffer) holds strings
/* as ds_string and not char arrays
/**********************************************************************************/
#define SM_DS_STRING_AS_STRING

/**********************************************************************************
/* Uncomment this line will make a library that uses COM compatible interfaces for
/* communucation with the driver DLLs
/**********************************************************************************/
#define SM_USE_COM_DELPHI_INTERFACE

/**********************************************************************************
/* Uncomment this to enable asserts in boost library
/**********************************************************************************/
#define BOOST_DISABLE_ASSERTS

/**********************************************************************************
/* Uncomment this to enable multithreading support in boost library
/**********************************************************************************/
// #define BOOST_DISABLE_THREADS
#define BOOST_SP_DISABLE_THREADS

/**********************************************************************************
/* I don't remember about this
/**********************************************************************************/
#define BOOST_VARIANT_DETAIL_NO_SUBSTITUTE

/**********************************************************************************
/* I don't remember about this
/**********************************************************************************/
#if ! defined NDEBUG
#define NDEBUG
#endif

/**********************************************************************************
/* Don't touch below this
/* Don't touch below this
/* Don't touch below this
/* Don't touch below this
/* Don't touch below this
/**********************************************************************************/

#ifdef SM_DS_DEFAULT_SHARED_PTR

    #ifdef _MSC_VER
        #define SM_DS_USE_LOKI_SHARED_PTR
    #endif

    #ifdef __BORLANDC__
        #define SM_DS_USE_SMALL_SHARED_PTR
    #endif

#endif

#if !defined( SM_DS_USE_BOOST_SMART_PTR ) && !defined( SM_DS_USE_SMALL_SHARED_PTR ) && !defined( SM_DS_USE_LOKI_SHARED_PTR )
    #error  "No smart pointer selection"
#endif

/**********************************************************************************
/* this is a part copied from <ssport.h> to remove the dependency 
/**********************************************************************************/
// check if already defined (for example <ssport.h> is included)
#if ! defined( FASTCALL )
    #ifdef	NO_FASTCALL
        #define	FASTCALL
    #else
        #define	FASTCALL		__fastcall
    #endif
#endif

#if ! defined( CDFASTCALL )
    #ifdef	NO_CDFASTCALL
        #define	CDFASTCALL
    #else
        #define	CDFASTCALL		__fastcall
    #endif
#endif

#endif

