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
#if ! defined (SM_DS_CONFIG_H)
#define SM_DS_CONFIG_H

/**********************************************************************************
** Comment this to disable default shared_ptr selection ...
***********************************************************************************/
#define SM_DS_DEFAULT_SHARED_PTR

/**********************************************************************************
** ... or Uncomment one of the following to make shared_ptr selection
***********************************************************************************/
//#define SM_DS_USE_BOOST_SMART_PTR
//#define SM_DS_USE_SMALL_SHARED_PTR
//#define SM_DS_USE_LOKI_SHARED_PTR

/**********************************************************************************
** Uncomment this to make C++Builder 6 use the Rogue Wave STL
***********************************************************************************/
//#define _USE_OLD_RW_STL

/**********************************************************************************
** Uncomment this to make a debug build
***********************************************************************************/
//#define SM_DS_DEBUG

/**********************************************************************************
** Uncomment this so that the library raises an exception when field values are
** null instead of returning the default value for the field type
***********************************************************************************/
#define SM_DS_NULL_VALUE_EXCEPTION

/**********************************************************************************
** Uncomment this to make a build with debug iterators (not yet implemented)
***********************************************************************************/
//#define SM_DS_DEBUG_ITERATORS

/**********************************************************************************
** When SM_DS_STRING_AS_STRING is defined then the raw record buffer class
** (cRawBuffer) holds strings as ds_string.
** When SM_DS_STRING_AS_STRING is --NOT-- defined then the raw record buffer class
** (cRawBuffer) holds strings as char arrays
***********************************************************************************/
#define SM_DS_STRING_AS_STRING

/**********************************************************************************
** Uncomment this line to get faster (but less safe) iterator.
** The gain is not so mush at speed then is code size.
** This will take effect only if SM_DS_DEBUG is --NOT-- defined
***********************************************************************************/
// #define SM_DS_FAST_ITERATORS

/**********************************************************************************
** Defined - Enables / undefined - disables the notification mechanism
***********************************************************************************/
#define SM_DS_ENABLE_NOTIFY

/**********************************************************************************
** When SM_DS_COPYABLE_TABLES is defined all classes inherited from Tablebase
** will be copyable.
***********************************************************************************/
// #define SM_DS_COPYABLE_TABLES

/**********************************************************************************
** Defining SM_USE_COM_DELPHI_INTERFACE will make a library that uses COM compatible
** interfaces for communucation with the back-end DLLs.
** That is they will have "QueryInterface", "AddRef", and "Release" methods so that
** back-end DLL can be created with development environments thet support only
** COM interfaces (eg VB(!!!), Delphi).
** The DLLs must also be recompiled.
***********************************************************************************/
// #define SM_USE_COM_DELPHI_INTERFACE

/**********************************************************************************
** if defined date-time classes use internally a double for the representation
** else they use the corresponding ODBC structs
***********************************************************************************/
#define SM_DS_DATE_IS_DOUBLE

/**********************************************************************************
** Comment this to enable asserts in boost library
***********************************************************************************/
#define BOOST_DISABLE_ASSERTS

/**********************************************************************************
** Comment this to enable multithreading support in boost and specificaly
** in shared_ptr
***********************************************************************************/
#define BOOST_DISABLE_THREADS
#define BOOST_SP_DISABLE_THREADS

/**********************************************************************************
** I don't remember about this
***********************************************************************************/
#define BOOST_VARIANT_DETAIL_NO_SUBSTITUTE

/**********************************************************************************
** I don't remember about this
***********************************************************************************/
#if ! defined NDEBUG
#define NDEBUG
#endif

/**********************************************************************************
***********************************************************************************
***********************************************************************************
** Change the code below ONLY IF YOU KNOW WHAT YOU ARE DOING!!!!
***********************************************************************************
***********************************************************************************
***********************************************************************************/

#if ! defined(SM_DS_DEBUG)
    #if defined ( SM_DS_FAST_ITERATORS )
        #define SM_DS_FAST_ITERATORS_INTERNAL
    #endif
#endif

/**********************************************************************************
** Smart pointer selection
***********************************************************************************/

#if defined(SM_DS_DEFAULT_SHARED_PTR) && (defined(SM_DS_USE_BOOST_SMART_PTR) || defined(SM_DS_USE_SMALL_SHARED_PTR) || defined(SM_DS_USE_LOKI_SHARED_PTR))
    #error  "Error in smart pointer selection"
#endif

#ifdef SM_DS_DEFAULT_SHARED_PTR

    #ifdef _MSC_VER
        #define SM_DS_USE_LOKI_SHARED_PTR
    #endif

    #ifdef __BORLANDC__
        #define SM_DS_USE_SMALL_SHARED_PTR
    #endif

    #ifdef __GNUG__
        #define SM_DS_USE_BOOST_SMART_PTR
    #endif

#endif

#if !defined( SM_DS_USE_BOOST_SMART_PTR ) && !defined( SM_DS_USE_SMALL_SHARED_PTR ) && !defined( SM_DS_USE_LOKI_SHARED_PTR )
    #error  "No smart pointer selection"
#endif

/**********************************************************************************
** this is a part copied from <ssport.h> to remove the dependency
***********************************************************************************/
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
