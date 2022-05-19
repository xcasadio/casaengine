//////////////////////////////////////////////////////////////////////
//  About class CWin32Error
//  =======================
//      - Is an incredibly small but enormously useful C++ thingie.
//      - Encapsulates the two basic Win32 APIs:
//          - ::GetLastError()  and
//          - ::FormatMessage().
//      - Employs smart copy methods to minimize the overheads of
//        mem allocation, retrieving system error strings, and copying.
//      - Has all member-functions inline. Just #include this header.
//      - Does not depend on MFC. Use freely with any C++ library.
//      - Compiles under both UNICODE and MBCS.
//      - Is very convenient and simple to use--in fact, the objects
//        of this class are *best* created on the stack, and can
//        be passed by value without undue performance hit.
//      - Provides automatic conversion to const TCHAR* type. Pass
//        objects, as they are, to MessageBox() or AfxMessageBox().
//      - Supports the MFC TRACE macro. Pass objects to TRACE as they
//        are--you don't have to call object.c_str() method or so.
//        e.g. TRACE( "%s\n", e ); and not TRACE( "%s\n", e.c_str() );
//      - Helps in taking advantage of the exception-handling features
//        of the C++ language.
//
//  Intended usages:
//  ===============
//      - As an exception class whose instances can be thrown and
//        and caught by value without undue performance hit.
//      - As a convenient encapsulation of strings with error codes.
//      - As a debugger convenience for error messages.
//
//  Example usage, technical notes, and suggestions for improvements
//        appear towards the end of this file.
//
//  Well thought out comments are welcome.
//
//  Thanks for using, and happy debugging ;)
//
//      -- Ajit Jadhav (ajit_jadhav@hotmail.com)
//
////////////////////////////////////////////////////////////////////////

#ifndef WIN32EXCEPTION_H__
#define WIN32EXCEPTION_H__

#include "CA_Export.h"

#include <tchar.h>


namespace CasaEngine
{
	class CA_EXPORT Win32Exception
	{
	public:
		//----- Construction and destruction -----------------------------------

			// The default constructor calls ::GetLastError() as well
			// as ::FormatMessage(). BUT the copy constructor and the
			// overloaded assignment ('=') operator DO NOT.
			// Thus, object-copies carry the original error code and message.
			// This avoids the possible confusion due to intermittent
			// SetLastError() called by some other Win32 API functions.
		Win32Exception();

		// Smart copy
		Win32Exception(const Win32Exception& rRHS);

		// Use this form of construction if you yourself
		// call ::GetLastError() just before instantiation.
		// Also useful for returning success status (arg = 0 ).
		Win32Exception(unsigned int dwLastError);

		// Smart copy.
		const Win32Exception& operator=(const Win32Exception& rRHS);

		// Automatically frees the internal buffer once
		// the internal reference count drops to zero.
		// TODO: Make dtor virtual, if deriving from this.
		~Win32Exception();

		//----- Returning the state without modification -----------------------

			// The Win32 error code currently held in this object.
		unsigned int ErrorCode() const;

		// The Win32 error code currently held in this object.
		operator unsigned int() const;

		// TCHAR count including the terminating nullptr TCHAR. That is not
		// necessarily equal to byte count. (Depends on UNICODE/MBCS).
		int MessageLength() const;

		// Internal buffer returned!! Do not modify, delete[] or free.
		// You can directly pass this object to any function that
		// accepts a const char* argument, e.g. to AfxMessageBox().
		// Makes available the Win32 API error string held internally.
		operator const TCHAR* () const;

		// The function form for returning the error string.
		// Internal buffer returned!! Do not modify, delete[] or free.
		const TCHAR* Description() const;

		//----- Resetting the internal state -----------------------------------

			// Note: GetLastError() is being called for the n+1 time
			// now. (The first time was in construction.) The two values
			// may differ if ::SetLastError() was called in between.
			// This can happen if either you call SetLastError yourself
			// of if you call some Win32 API (such as CreateFile() )
			// that on its own calls SetLastError()
		void ReGetLastError();

		//----- Private members ----------------------------------------------
	private:

		// struct for smart copying. Meta info is prepended to
		// the actual string, something like in BASIC strings (BSTRs).
		struct SMetaMem
		{
			SMetaMem();

			long m_nRefCnt;             // Including this
			unsigned int m_fwErrCode;   // Win32 error code
			int m_nMsgStrLen;           // i.e. _tcslen() + 1.

			TCHAR* getString();
		};

		void addRef(const Win32Exception& rOrig);

		void releaseRef();

		void doFormatMessage(unsigned int dwLastErr);

		void allocCopyData(TCHAR* pTemp, int nLen, unsigned int dwLastErr);

		void freeBuffer();

		SMetaMem* metaMem() const;

		// The error message given by ::FormatMessage()
		TCHAR* m_szErrMsg;
	};
}

//======================================================================
// class CWin32Error Interface and Implementation ends here.
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//
//  CWin32Error Example Usages:
//  ==========================
//
//  Example 1: Simplified Exception Handling For Win32 API Errors
//             This was my main purpose in writing this class.
//             --------------------------------------------------
//
//  void MyFunction( void ) throw CWin32Error // see client below
//  {
//      if( ! SomeWin32API() )
//      {
//          // ::GetLastError() and ::FormatMessage()
//          // automatically get called during construction.
//
//          // Catch by value or by ref--the code stays the same.
//
//          // Smart copying means you can rethrow the object by
//          // value as many times as you like!
//
//          throw CWin32Error();
//      }
//  }
//
//  void ClientToMyFunction( void )
//  {
//      try
//      {
//          MyFunction();
//      }
//      catch( CWin32Error e ) // catching by value is OK (smart copying)
//      {
//          // Note: Automatic conversion to const TCHAR* type.
//
//          ::OutputDebugTrace( e );
//      }
//  }
//
//
//  Example 2: "Vanilla" usage (No Exception Handling)
//             ---------------------------------------
//
//  // This function returns a CWin32Error object. Smart copy
//  // means you can return objects even during normal
//  // (non-exception-related) execution, without having to
//  // take undue performance hit.
//
//  CWin32Error MyFunction( void )
//  {
//      if( ! SomeWin32API() )
//      {
//          // Constructor gets last error and keeps the text
//          // of the error message ready.
//
//          CWin32Error e;
//
//          // Don't have to call a member function even in
//          // MFC trace macro [i.e. no e.c_str() or (const char*) e]
//
//          TRACE( "%s\n", e );
//
//          return e;
//      }
//      // In Win32 API, the '0' value corresponds to the
//      // error string: "Operation completed successfully"
//      // The error string is automatically taken from the OS
//      // in the returned CWin32Error object.
//
//      return 0; // ctor taking unsigned int called here
//  }
//
//
//  Example 3:  Simplest: Neither exception-handling nor returning
//              errors. Just a help for getting the message-strings
//              formatted from the OS.
//              --------------------------------------------------
//
//  void MyFunction( void )
//  {
//      if( ! SomeWin32API() )
//      {
//          // If you want to retrieve the error code yourself...
//
//          DWORD dwErr = ::GetLastError();
//
//          // ...perhaps for some check on the code like this...
//
//          if( dwErr is really bad and
//              user should know about it )
//          {
//              // This form of CWin32Error ctor does NOT call
//              // ::GetLastError().
//
//              CWin32Error e = dwErr;
//
//              // CWin32Error supplies const char* conversion
//
//              AfxMessageBox( e );
//          }
//          // Else, forget prompting the user.
//          // Just return from the function...
//
//          return;
//      }
//      // other code ...
//  }
//
////////////////////////////////////////////////////////////////////////
//
// Technical Notes for CWin32Error:
// ===============================
//
// On-Stack- Vs. On-Heap-Instantiation:
// -----------------------------------
// This class was designed so that error objects can be freely created
// on the stack and returned by value across exception frames/blocks.
//
// Creating objects of this class dynamically (i.e on the heap)
// offers no particular advantage. Usually, people tend to
// reuse such heap-allocated objects via pointers. Heap is not harmful
// by itself, but there are object reuse issues, as given below.
//
// Reusing the same instance (object) at runtime.
// ---------------------------------------------
// (i) You have to remember to call CWin32Error::ReGetLastError()
// (ii) You have to provide thread-protection in multi-threaded
// apps--the single global object may grab error code from place in
// another thread.
//
// Of course, if you do not *reuse* the same instance, then it's
// perfectly OK to create CWin32Error objects on the heap.
//
// Remember not to delete [] Description() return value
// ----------------------------------------------------
// - The only reason I didn't return an MFC CString or an STL string or
// wstring object is because I didn't want to create dependencies on
// other libraries right in this small utility class.
// - On the minus side of this decision is exposing the internal buffer
// (even if as a const).
// - On the plus side, you can use this class intact in almost any
// kind of Win32 development--whether in performance-critical sockets
// apps; or in ATL COM components; or in console app using STL; or
// in a database project using some third-party ODBC library, or in
// the AppWizard generated MFC MDI App.
////////////////////////////////////////////////////////////////////////
//
//  Suggestions for improvements to the class
//  =========================================
//  - Enhancements/checks for handling Value-collision of error codes:
//      - MAPI errors vs Win32
//      - Win32 vs custom MC-dll
//  - Provide support for ::FormatMessage() arguments:
//      - Formatting messages from strings.
//      - Inserts and argument arrays.
//  - Using a custom message (MC-compiled) dll for messages.
//      - Use its instance module handle to format messages.
//      - Add/Alter member functions suitably.
//      Caution:
//          - Who loads the dll? Manages its in-proc-time?
//          - Who sets the thread error number? When?
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#endif // #ifndef WIN32EXCEPTION_H__
