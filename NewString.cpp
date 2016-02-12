#include "stdafx.h"
#include<TCHAR.H>
#include <string.h>
#include <iostream>


#ifdef _UNICODE
    #define t_cout std::wcout
#else
    #define t_cout std::cout
#endif //UNICODE


/*
 * The class NewString allows string handling (TCHAR *) and provides 
 * basic string operations.
 */

class NewString
{
protected:
    TCHAR* m_tchar;

public:
    /*
     * Constructor
     */
    NewString() : m_tchar(0)
    {
    }

    /*
     * Copy constructor
     */
    NewString(const NewString& copyNewString)
    {
        m_tchar = 0;
        asign(&m_tchar, copyNewString.m_tchar);
    }

    /*
     * Destructor
     */
    ~NewString()
    {
        if (m_tchar != 0)
        {
            delete m_tchar;
            m_tchar = 0;
        }
    }

    void asign (TCHAR** s1, const TCHAR* s2)
    {
        if (*s1 != s2)
        {
            if (*s1 != 0)
            {
                
                delete[] *s1;
            }

            if (s2 != 0)
            {
                *s1 = new TCHAR[_tcslen(s2) + 1];
                _tcscpy(*s1, s2);
            }
            else
            {
                *s1 = 0;
            }
        }
    }
    /*
     * Operator = (assign)
     */
    NewString &operator= (const NewString& assignedNewString)
    {
        asign(&m_tchar, assignedNewString.m_tchar);

        return *this;
    }

    /*
     * Operator = (assign)
     */
    NewString &operator= (const TCHAR* ptrTchar)
    {
        asign(&m_tchar, ptrTchar);

        return *this;
    }

    /*
     * Operator <<
     */
    friend std::basic_ostream<TCHAR>& operator<< (std::basic_ostream<TCHAR> &out, 
        const NewString& newString)
    {
        out << newString.m_tchar;
        return out;
    }

    /*
     * Operator == (compare)
     */
    bool operator==(const NewString& ns1/*, const NewString& ns2*/)
    {
        bool result(false);

        if ((m_tchar == 0) && (ns1.m_tchar == 0))
        {
            result = true;
        }
        else if ((m_tchar != 0) && (ns1.m_tchar != 0))
        {
            if (_tcscmp(m_tchar, ns1.m_tchar))
            {
                result = true;
            }
        }
        else
        {
            result = false;
        }
        
        return result;
    }

    /*
     * Operator + (concat NewString + NewString)
     */
    friend NewString operator+ (const NewString& lhs, const NewString& rhs)
    {
        NewString newString;
        newString.m_tchar = new TCHAR[_tcslen(lhs.m_tchar) + 
                                      _tcslen(rhs.m_tchar) + 1];

        _tcscpy(newString.m_tchar, lhs.m_tchar);
        _tcscat(newString.m_tchar, rhs.m_tchar);

        return newString;
    }

    /*
     * Operator + (concat NewString + TCHAR*)
     */
    friend NewString operator+ (const NewString& lhs, const TCHAR* rhs)
    {
        NewString newString;
        newString.m_tchar = new TCHAR[_tcslen(lhs.m_tchar) + _tcslen(rhs) + 1];

        _tcscpy(newString.m_tchar, lhs.m_tchar);
        _tcscat(newString.m_tchar, rhs);

        return newString;
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
    NewString a, b, c;
    a = _T( "This is" );
    b = _T( "a simple example " );
    c = _T( "for " );

    NewString d = a + b + c + _T( "testing the class NewString!\n" );
    t_cout << d;
}

