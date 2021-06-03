#if !defined(AFX_TR_H_INCLUDED_)
#define AFX_TR_H_INCLUDED_
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace TR {

	template<typename T>
	static T FromString( const CString& csStr ) {
		std::string s = csStr;
		std::istringstream iss( s );
		T t;

		if( iss >> t ) {
			return t;
		}
		else {
			CString csExc = _T("Conversion Error");
			csExc += _T(": ");
			csExc += csStr;
			throw( csExc );
		}
	}

	template<typename T>
	static CString ToString( const T& t ) {
		std::ostringstream oss;

		if( oss << t ) {
			CString csStr = _T("");
			csStr.Format( _T("%s"), oss.str().c_str() );
			return csStr;
		}
		else {
			CString csExc = _T("Conversion Error");
			throw( csExc );
		}
	}

	template<typename T>
	static void Swap( T& t1, T& t2 ) {
		T t = t1;
		t1  = t2;
		t2  = t;
	}

	template<typename T>
	static T Max( T& t1, T& t2 ) {
		return t1 > t2 ? t1 : t2;
	}

	template<typename T>
	static T Min( T& t1, T& t2 ) {
		return t1 < t2 ? t1 : t2;
	}
}

#endif // !defined(AFX_TR_H_INCLUDED_)