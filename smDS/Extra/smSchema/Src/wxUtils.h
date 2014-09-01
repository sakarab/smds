#ifndef WXUTILS_H
#define WXUTILS_H

#include <exception>
#include <boost/smart_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "wx/wxchar.h"

class wxWindow;

namespace wx
{

//inline wxString Utf8ToCurrentCodePage( const char *str )
//{
//    return wxString( "" ); // wxString( str );
//}

//********************************************************
//******    ExceptionBase
//********************************************************
class ExceptionBase : public std::exception
{
public:
    virtual wxChar *wwhat() const = 0;
};

//********************************************************
//******    LogException
//********************************************************
class LogException : public ExceptionBase
{
private:
    boost::shared_array<wxChar>         mMessage;
public:
    explicit LogException( const wxChar *message );

    virtual wxChar *wwhat() const       { return mMessage.get(); }
};

//********************************************************
//******    LogExceptioner
//********************************************************
class LogExceptioner : public wxLog
{
private:
    wxLog   *mOldLog;

    LogExceptioner( const LogExceptioner& );
    LogExceptioner& operator = ( const LogExceptioner& );
protected:
    virtual void DoLog( wxLogLevel level, const wxChar *szString, time_t t );
    virtual void DoLogString( const wxChar *szString, time_t t );
public:
    LogExceptioner()
    {
        mOldLog = wxLog::SetActiveTarget( this );
    }
    ~LogExceptioner()
    {
        wxLog::SetActiveTarget( mOldLog );
    }
};

//********************************************************
//******    CreateForm<T>
//********************************************************
template <class T> inline T *CreateForm( wxWindow *parent )
{
    LogExceptioner      log;

    return new T( parent );
}

//********************************************************
//******    DestroyForm<T>
//********************************************************
template <class T> inline void DestroyForm( T*& win )
{
    if ( win != 0 )
    {
        win->Destroy();
        win = 0;
    }
}

//********************************************************
//******    CreateAttachedPanel<T>
//********************************************************
template <class T> inline T *CreateAttachedPanel( wxWindow *parent )
{
    T           *result = CreateForm<T>( parent );
    wxSizer     *sizer = parent->GetSizer();

    sizer->Add( result, 1, wxGROW | wxALL, 0 );
    sizer->RecalcSizes();
    return result;
}

}; // namespace wx

#endif
