// bslmf_forwardingtype.t.cpp                                         -*-C++-*-
#include <bslmf_forwardingtype.h>

#include <bslmf_isarray.h>
#include <bslmf_issame.h>          // for testing only

#include <bsls_bsltestutil.h>
#include <bsls_platform.h>

#include <iostream>
#include <typeinfo>

#include <stdlib.h>    // atoi()

using namespace BloombergLP;
using namespace std;

//=============================================================================
//                                TEST PLAN
//-----------------------------------------------------------------------------
//                                Overview
//                                --------
// This component provides two meta-functions.  We simply verify that they
// return the proper type for a list of suitably chosen arguments.
//-----------------------------------------------------------------------------
// [ 1] bslmf::ForwardingType
// [ 2] bslmf::ConstForwardingType
// [ 3] USAGE EXAMPLE
//=============================================================================
//                       STANDARD BDE ASSERT TEST MACRO
//-----------------------------------------------------------------------------
// NOTE: THIS IS A LOW-LEVEL COMPONENT AND MAY NOT USE ANY C++ LIBRARY
// FUNCTIONS, INCLUDING IOSTREAMS.
static int testStatus = 0;

void aSsErT(bool b, const char *s, int i)
{
    if (b) {
        printf("Error " __FILE__ "(%d): %s    (failed)\n", i, s);
        if (testStatus >= 0 && testStatus <= 100) ++testStatus;
    }
}

# define ASSERT(X) { aSsErT(!(X), #X, __LINE__); }

//=============================================================================
//                       STANDARD BDE TEST DRIVER MACROS
//-----------------------------------------------------------------------------
#define LOOP_ASSERT  BSLS_BSLTESTUTIL_LOOP_ASSERT
#define LOOP2_ASSERT BSLS_BSLTESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BSLS_BSLTESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BSLS_BSLTESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BSLS_BSLTESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BSLS_BSLTESTUTIL_LOOP6_ASSERT

#define Q   BSLS_BSLTESTUTIL_Q   // Quote identifier literally.
#define P   BSLS_BSLTESTUTIL_P   // Print identifier and value.
#define P_  BSLS_BSLTESTUTIL_P_  // P(X) without '\n'.
#define T_  BSLS_BSLTESTUTIL_T_  // Print a tab (w/o newline).
#define L_  BSLS_BSLTESTUTIL_L_  // current Line number

//=============================================================================
//                    NON-STANDARD BDE ASSERT TEST MACROS
//-----------------------------------------------------------------------------

#define ASSERT_SAME(X, Y) ASSERT(1 == (bsl::is_same<X, Y>::value))

//=============================================================================
//                  GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

enum   Enum   {};
struct Struct {};
union  Union  {};
class  Class  {};

typedef int INT;

typedef void      F ();
typedef void ( & RF)();
typedef void (*  PF)();
typedef void (*&RPF)();

typedef void    Fi  (int);
typedef void (&RFi) (int);
typedef void (*PFi) (int);
typedef void    FRi (int&);
typedef void (&RFRi)(int&);

typedef char    A [5];
typedef char (&RA)[5];

//=============================================================================
//                     GLOBAL TYPES FOR USAGE EXAMPLE
//-----------------------------------------------------------------------------

struct MyType {};
typedef MyType& MyTypeRef;

void usageExample()
{

///Usage
///-----
// For example:
//..
    typedef int                    T1;
    typedef int&                   T2;
    typedef const volatile double& T3;
    typedef const double &         T4;
    typedef const float * &        T5;
    typedef const float * const &  T6;
    typedef MyType                 T7;
    typedef const MyType&          T8;
    typedef MyType&                T9;
    typedef MyType*                T10;

    typedef int                    EXP1;
    typedef int&                   EXP2;
    typedef const volatile double& EXP3;
    typedef double                 EXP4;
    typedef const float * &        EXP5;
    typedef const float *          EXP6;
    typedef const MyType&          EXP7;
    typedef const MyType&          EXP8;
    typedef MyType&                EXP9;
    typedef MyType*                EXP10;

    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T1>::Type,
                               EXP1>::value));
    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T2>::Type,
                               EXP2>::value));
    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T3>::Type,
                               EXP3>::value));
    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T4>::Type,
                               EXP4>::value));
    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T5>::Type,
                               EXP5>::value));
    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T6>::Type,
                               EXP6>::value));
    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T7>::Type,
                               EXP7>::value));
    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T8>::Type,
                               EXP8>::value));
    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T9>::Type,
                               EXP9>::value));
    ASSERT(1 == (bsl::is_same<bslmf::ForwardingType<T10>::Type,
                               EXP10>::value));
}

//=============================================================================
//                              MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    int verbose = argc > 2;
    int veryVerbose = argc > 3;

    (void) verbose;      // eliminate unused variable warning
    (void) veryVerbose;  // eliminate unused variable warning

    cout << "TEST " << __FILE__ << " CASE " << test << endl;

    switch (test) { case 0:  // Zero is always the leading case.
      case 3: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //   Simple example illustrating use of 'bsl::remove_reference'.
        //
        // Concerns:
        //
        // Plan:
        //
        // Tactics:
        //   - Add-Hoc Data Selection Method
        //   - Brute-Force implementation technique
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) cout << endl << "USAGE EXAMPLE" << endl
                                  << "=============" << endl;

        usageExample();

      } break;
      case 2: {
        // --------------------------------------------------------------------
        // Test Plan:
        //   Instantiate 'bslmf::ConstForwardingType' with various types and
        //   verify that its 'Type' typedef is set to the expected type.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "bslmf::ConstForwardingType" << endl
                          << "==========================" << endl;

        ASSERT_SAME(bslmf::ConstForwardingType<int       >::Type, int);
        ASSERT_SAME(bslmf::ConstForwardingType<int&      >::Type, int&);
        if (verbose)
            P(bslmf::ConstForwardingType<int&>::BSLMF_FORWARDING_TYPE_ID);
        ASSERT_SAME(bslmf::ConstForwardingType<int const&>::Type, int);

        ASSERT_SAME(bslmf::ConstForwardingType<void *>::Type, void *);
        if (verbose)
            P(bslmf::ConstForwardingType<void *>::BSLMF_FORWARDING_TYPE_ID);
        ASSERT_SAME(bslmf::ConstForwardingType<void *&>::Type,
                    void *&);
        ASSERT_SAME(bslmf::ConstForwardingType<void volatile *&>::Type,
                    volatile void                            *&);

        ASSERT_SAME(bslmf::ConstForwardingType<char const *const&>::Type,
                    char const *);

        ASSERT_SAME(bslmf::ConstForwardingType<Enum    >::Type, Enum);
        ASSERT_SAME(bslmf::ConstForwardingType<Enum&   >::Type, Enum&);
        ASSERT_SAME(bslmf::ConstForwardingType<Struct  >::Type, const Struct&);
        ASSERT_SAME(bslmf::ConstForwardingType<Struct& >::Type, Struct&);
        ASSERT_SAME(bslmf::ConstForwardingType<Union   >::Type, const Union&);
        ASSERT_SAME(bslmf::ConstForwardingType<Union&  >::Type, Union&);
        ASSERT(0 == bsl::is_array<Class>::value);
        ASSERT_SAME(bslmf::ConstForwardingType<Class   >::Type,const Class&);
        if (verbose)
            P(bslmf::ConstForwardingType<Class>::BSLMF_FORWARDING_TYPE_ID);
        if (verbose) P(bslmf::ConstForwardingType<Class>::IS_BASIC_TYPE);
        ASSERT_SAME(bslmf::ConstForwardingType<const Class&>::Type,
                    const Class&);

        ASSERT_SAME(bslmf::ConstForwardingType<INT >::Type, int);
        ASSERT_SAME(bslmf::ConstForwardingType<INT&>::Type, int&);

        ASSERT_SAME(bslmf::ConstForwardingType<int Class:: *>::Type,
                    int Class::*);
        ASSERT_SAME(bslmf::ConstForwardingType<int Class::* const& >::Type,
                    int                                            Class::*);

        ASSERT_SAME(bslmf::ConstForwardingType<int Class::*&>::Type,
                    int                            Class::*&);

        ASSERT_SAME(bslmf::ConstForwardingType< PF>::Type, PF);
        ASSERT_SAME(bslmf::ConstForwardingType<RPF>::Type, PF&);

        ASSERT_SAME(bslmf::ConstForwardingType< A>::Type, const char*);
        ASSERT_SAME(bslmf::ConstForwardingType<RA>::Type, char*);
        if (verbose)
            P(bslmf::ConstForwardingType<RA>::BSLMF_FORWARDING_TYPE_ID);
      } break;
      case 1: {
        // --------------------------------------------------------------------
        // Test Plan:
        //   Instantiate 'bslmf::ForwardingType' with various types and verify
        //   that its 'Type' typedef is set to the expected type.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "bslmf::ForwardingType" << endl
                          << "======================" << endl;

        ASSERT_SAME(bslmf::ForwardingType<int       >::Type, int);
        if (verbose) P(typeid(bslmf::ForwardingType<int>::Type).name());
        ASSERT_SAME(bslmf::ForwardingType<int&      >::Type, int&);
        ASSERT_SAME(bslmf::ForwardingType<int const&>::Type, int);

        ASSERT_SAME(bslmf::ForwardingType<void *          >::Type, void *);
        ASSERT_SAME(bslmf::ForwardingType<void *&         >::Type, void *&);
        ASSERT_SAME(bslmf::ForwardingType<void volatile *&>::Type,
                    volatile void *&);

        ASSERT_SAME(bslmf::ForwardingType<char const *const&>::Type,
                    char const *);

        ASSERT_SAME(bslmf::ForwardingType<Enum        >::Type, Enum);
        ASSERT_SAME(bslmf::ForwardingType<Enum&       >::Type, Enum&);
        ASSERT_SAME(bslmf::ForwardingType<Struct      >::Type, const Struct&);
        ASSERT_SAME(bslmf::ForwardingType<Struct&     >::Type, Struct&);
        ASSERT_SAME(bslmf::ForwardingType<Union       >::Type, const Union&);
        ASSERT_SAME(bslmf::ForwardingType<Union&      >::Type, Union&);
        ASSERT(0 == bsl::is_array<Class>::value);
        ASSERT_SAME(bslmf::ForwardingType<Class       >::Type, const Class&);
        if (verbose)
            P(bslmf::ForwardingType<Class>::BSLMF_FORWARDING_TYPE_ID);
        if (verbose) P(bslmf::ForwardingType<Class>::IS_BASIC_TYPE);
        ASSERT_SAME(bslmf::ForwardingType<const Class&>::Type, const Class&);

        ASSERT_SAME(bslmf::ForwardingType<INT >::Type, int);
        ASSERT_SAME(bslmf::ForwardingType<INT&>::Type, int&);

        ASSERT_SAME(bslmf::ForwardingType<int Class::* >::Type, int Class::*);
        ASSERT_SAME(bslmf::ForwardingType<int Class::* const& >::Type,
                    int                                       Class::*);

        ASSERT_SAME(bslmf::ForwardingType<int Class::*&>::Type, int Class::*&);

#if !defined(BSLS_PLATFORM_CMP_MSVC)    \
    && (!defined(BSLS_PLATFORM_CMP_IBM) \
        || (BSLS_PLATFORM_CMP_VER_MAJOR < 0x0800))
        // xlc-8 and MSVC 2005 seem to have problems with function types.

        ASSERT_SAME(bslmf::ForwardingType<  F>::Type,  F);
#endif
        ASSERT_SAME(bslmf::ForwardingType< RF>::Type,  RF);

        ASSERT_SAME(bslmf::ForwardingType< PF>::Type, PF);
        ASSERT_SAME(bslmf::ForwardingType<RPF>::Type, PF&);

#if !defined(BSLS_PLATFORM_CMP_MSVC)    \
    && (!defined(BSLS_PLATFORM_CMP_IBM) \
        || (BSLS_PLATFORM_CMP_VER_MAJOR < 0x0800))
        // xlc-8 and MSVC 2005 seem to have problems with function types.

        ASSERT_SAME(bslmf::ForwardingType< Fi >::Type, Fi);
        ASSERT_SAME(bslmf::ForwardingType< FRi>::Type, FRi);
#endif
        ASSERT_SAME(bslmf::ForwardingType<RFi >::Type, RFi);
        ASSERT_SAME(bslmf::ForwardingType<RFRi>::Type, FRi&);

        ASSERT_SAME(bslmf::ForwardingType< A>::Type, char*);
        ASSERT_SAME(bslmf::ForwardingType<RA>::Type, char *);
      } break;
      default: {
        cerr << "WARNING: CASE `" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = "
             << testStatus << "." << endl;
    }
    return testStatus;
}

// ----------------------------------------------------------------------------
// Copyright (C) 2013 Bloomberg L.P.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------- END-OF-FILE ----------------------------------
