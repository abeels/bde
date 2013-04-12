// bslmf_if.t.cpp                                                     -*-C++-*-

#include <bslmf_if.h>

#include <bslmf_nil.h>  // for testing only

#include <bsls_bsltestutil.h>

#include <iostream>

#include <stdlib.h>

using namespace BloombergLP;
using namespace std;

//=============================================================================
//                                TEST PLAN
//-----------------------------------------------------------------------------
//                                Overview
//                                --------
// The component under test contains the simple meta-function 'bslmf::If'.  The
// meta-function is tested by enumeration of all combinations of (1) 'true' and
// 'false' conditions, and (2) defaulting of zero, one, or two of the type
// arguments to 'bslmf::Nil'.
//-----------------------------------------------------------------------------
// [ 1] bslmf::If<CONDITION, IF_TRUE_TYPE, IF_FALSE_TYPE>

//=============================================================================
//                      STANDARD BDE ASSERT TEST MACRO
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

//=============================================================================
//                      STANDARD BDE TEST DRIVER MACROS
//-----------------------------------------------------------------------------

#define ASSERT       BSLS_BSLTESTUTIL_ASSERT
#define LOOP_ASSERT  BSLS_BSLTESTUTIL_LOOP_ASSERT
#define LOOP0_ASSERT BSLS_BSLTESTUTIL_LOOP0_ASSERT
#define LOOP1_ASSERT BSLS_BSLTESTUTIL_LOOP1_ASSERT
#define LOOP2_ASSERT BSLS_BSLTESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BSLS_BSLTESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BSLS_BSLTESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BSLS_BSLTESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BSLS_BSLTESTUTIL_LOOP6_ASSERT
#define ASSERTV      BSLS_BSLTESTUTIL_ASSERTV

#define Q   BSLS_BSLTESTUTIL_Q   // Quote identifier literally.
#define P   BSLS_BSLTESTUTIL_P   // Print identifier and value.
#define P_  BSLS_BSLTESTUTIL_P_  // P(X) without '\n'.
#define T_  BSLS_BSLTESTUTIL_T_  // Print a tab (w/o newline).
#define L_  BSLS_BSLTESTUTIL_L_  // current Line number

//=============================================================================
//                  GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

namespace {

    // 'SizeOf' is a meta-function that returns the non-zero size of its type
    // argument, or 0 for 'bslmf::Nil'.

    template <class T>
    struct SizeOf {
        static const size_t VALUE = sizeof(T);
    };

    template <>
    struct SizeOf<bslmf::Nil> {
        static const size_t VALUE = 0;
    };

#define SIZEOF(TYPE) SizeOf<TYPE>::VALUE

    // The compile-time evaluations depend on the following types being of
    // different sizes.

    typedef char   TrueType;   // sizeof(TrueType) == 1
    typedef double FalseType;  // sizeof(FalseType) > 1

    const size_t True  = SIZEOF(TrueType);
    const size_t False = SIZEOF(FalseType);
    const size_t Nil   = 0;

    typedef bslmf::If<true, TrueType, FalseType>::Type CT0;
    const size_t C0 = SIZEOF(CT0);                        // True

    typedef bslmf::If<false, TrueType, FalseType>::Type CT1;
    const size_t C1 = SIZEOF(CT1);                        // False

    typedef bslmf::If<true>::Type CT2;
    const size_t C2 = SIZEOF(CT2);                        // Nil

    typedef bslmf::If<false>::Type CT3;
    const size_t C3 = SIZEOF(CT3);                        // Nil

    typedef bslmf::If<true, TrueType>::Type CT4;
    const size_t C4 = SIZEOF(CT4);                        // True

    typedef bslmf::If<false, TrueType>::Type CT5;
    const size_t C5 = SIZEOF(CT5);                        // Nil

    typedef bslmf::If<true, TrueType, FalseType>::Type CT10;
    const size_t C10 = SIZEOF(CT10);                      // True

    typedef bslmf::If<false, TrueType, FalseType>::Type CT11;
    const size_t C11 = SIZEOF(CT11);                      // False

    typedef bslmf::If<true>::Type CT12;
    const size_t C12 = SIZEOF(CT12);                      // Nil

    typedef bslmf::If<false>::Type CT13;
    const size_t C13 = SIZEOF(CT13);                      // Nil

    typedef bslmf::If<true, TrueType>::Type CT14;
    const size_t C14 = SIZEOF(CT14);                      // True

    typedef bslmf::If<false, TrueType>::Type CT15;
    const size_t C15 = SIZEOF(CT15);                      // Nil

}  // close namespace 'anonymous'

//=============================================================================
//                GLOBAL TYPES AND FUNCTIONS FOR USAGE EXAMPLE
//-----------------------------------------------------------------------------

///Usage
//------
// The following snippets of code illustrate basic use of the 'bslmf::If'
// meta-function.  The examples make use of the following declarations to
// identify the type that is selected by a given constant integral expression:
//..
    enum TypeCode { T_UNKNOWN = 0, T_CHAR = 1, T_INT = 2, T_NIL = 3 };

    TypeCode whatType(char)       { return T_CHAR; }
    TypeCode whatType(int)        { return T_INT; }
    TypeCode whatType(bslmf::Nil) { return T_NIL; }
    TypeCode whatType(...)        { return T_UNKNOWN; }
//..

//=============================================================================
//                              MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    int verbose = argc > 2;
    // int veryVerbose = argc > 3;

    cout << "TEST " << __FILE__ << " CASE " << test << endl;

    switch (test) { case 0:  // Zero is always the leading case.
      case 2: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //   This case verifies that the usage example works as advertised.
        //
        // Concerns:
        //   That the usage example compiles, links, and runs as expected.
        //
        // Plan:
        //   Replicate the usage example from the component header here.
        //
        // Testing:
        //   USAGE EXAMPLE
        // --------------------------------------------------------------------

        if (verbose) cout << endl << "USAGE EXAMPLE" << endl
                                  << "=============" << endl;

// In the following example, the meta-function condition (the first argument to
// 'bslmf::If') evaluates to true (non-zero).  Thus, 'bslmf::If<...>::Type' is
// a synonym for 'int'; i.e., it "evaluates" (at compile time) to 'int':
//..
     typedef int  T1;  ASSERT(1 <  sizeof(T1));
     typedef char T2;  ASSERT(1 == sizeof(T2));

     typedef bslmf::If<(sizeof(T1) > sizeof(T2)), T1, T2>::Type LargerType;
     ASSERT(T_INT == whatType(LargerType()));
//..
// In the next example, the condition argument evaluates to false (zero).  In
// this case, 'bslmf::If<...>::Type' evaluates to 'bslmf::Nil' since the third
// template argument (the "else" type) is not explicitly specified:
//..
     typedef bslmf::If<(sizeof(T2) > 1), int>::Type Type2;
     ASSERT(T_NIL == whatType(Type2()));
//..

      } break;

      case 1: {
        // --------------------------------------------------------------------
        // TESTING BSLMF_IF
        //   Test the 'bslmf::If' meta-function.
        //
        // Concerns:
        //   - That 'true' and 'false' conditions select the first and second
        //     type arguments, respectively.
        //   - That selected types that are not explicitly specified resolve to
        //     the default 'bslmf::Nil' type.
        //
        // Plan:
        //   - Provide distinct type arguments with both 'true' and 'false'
        //     conditions and verify that the correct type is selected.
        //   - Repeat the tests such that:
        //      1. The second type parameter (only) defaults to 'bslmf::Nil'.
        //      2. Both type parameters default to 'bslmf::Nil'.
        //
        // Testing:
        //   bslmf::If<CONDITION, IF_TRUE_TYPE, IF_FALSE_TYPE>
        // --------------------------------------------------------------------

        if (verbose) cout << "bslmf::If" << endl
                          << "=========" << endl;

        ASSERT(1 == True);
        ASSERT(1 <  False);

        ASSERT(True  == C0);
        ASSERT(False == C1);
        ASSERT(Nil   == C2);
        ASSERT(Nil   == C3);
        ASSERT(True  == C4);
        ASSERT(Nil   == C5);

        ASSERT(C10   == C0);
        ASSERT(C11   == C1);
        ASSERT(C12   == C2);
        ASSERT(C13   == C3);
        ASSERT(C14   == C4);
        ASSERT(C15   == C5);

      } break;
      default: {
        cerr << "WARNING: CASE `" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = " << testStatus << "." << endl;
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
