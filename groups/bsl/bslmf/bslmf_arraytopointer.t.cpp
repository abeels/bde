// bslmf_arraytopointer.t.cpp                                         -*-C++-*-

#include <bslmf_arraytopointer.h>

#include <bslmf_issame.h>

#include <bsls_bsltestutil.h>
#include <bsls_platform.h>            // for testing only

#include <iostream>
#include <typeinfo>

#include <stdlib.h>    // atoi()

#include <cstdio>      // 'printf'

using namespace BloombergLP;
using namespace std;

//=============================================================================
//                                TEST PLAN
//-----------------------------------------------------------------------------
//                                Overview
//                                --------
// TBD
//-----------------------------------------------------------------------------
// [ 1] bslmf::ArrayToPointer
// [ 2] USAGE EXAMPLE

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
//                    NON-STANDARD BDE TEST DRIVER MACROS
//-----------------------------------------------------------------------------

#define ASSERT_SAME(X,Y) { ASSERT((1==bsl::is_same<X,Y>::value)); }

//=============================================================================
//                  GLOBAL TYPEDEFS/CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

enum Enum {};

struct Struct {
    int a[4];
};

union Union {
    int  i;
    char a[sizeof(int)];
};

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
      case 3: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //   Simple example illustrating use of 'bsl::is_array'.
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

///Usage
///-----
// For example:
//..
        ASSERT(1 == (bsl::is_same<bslmf::ArrayToPointer<int[5]>::Type
                                 , int*>::value));
        ASSERT(1 == (bsl::is_same<bslmf::ArrayToPointer<int*>::Type
                                 , int*>::value));
        ASSERT(1 == (bsl::is_same<bslmf::ArrayToPointer<int(*)[5]>::Type
                                 , int(*)[5]>::value));
        P(typeid(bslmf::ArrayToPointer<int(*)[5]>::Type).name());
      } break;
      case 2: {
        // --------------------------------------------------------------------
        // Test Plan:
        //   Instantiate 'bslmf::ArrayToConstPointer' with various types and
        //   verify that their 'Type' member aliases the correctly const-
        //   qualified decayed type.
        // --------------------------------------------------------------------
        if (verbose) cout << endl
                          << "bslmf::ArrayToConstPointer" << endl
                          << "==========================" << endl;

        ASSERT_SAME(bslmf::ArrayToPointer<char const    [1]>::Type,
                                          char const     *       );

        ASSERT_SAME(bslmf::ArrayToPointer<char       (&)[1]>::Type,
                                          char           *       );

        ASSERT_SAME(bslmf::ArrayToPointer<char             >::Type,
                                          char                   );

        ASSERT_SAME(bslmf::ArrayToPointer<char const       >::Type,
                                          char const             );

        ASSERT_SAME(bslmf::ArrayToPointer<char           * >::Type,
                                          char           *       );

        ASSERT_SAME(bslmf::ArrayToPointer<void       *   [2]>::Type,
                                          void       *    *       );
        ASSERT_SAME(bslmf::ArrayToPointer<void const *   [2]>::Type,
                                          void const *    *       );
        ASSERT_SAME(bslmf::ArrayToPointer<void       *(&)[2]>::Type,
                                          void       *    *       );
        ASSERT_SAME(bslmf::ArrayToPointer<void       *      >::Type,
                                          void       *            );
        ASSERT_SAME(bslmf::ArrayToPointer<void              >::Type,
                                          void                    );

        ASSERT_SAME(bslmf::ArrayToPointer<int                [3]>::Type,
                                          int                 *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          [3]>::Type,
                                          int const           *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       [3]>::Type,
                                          int volatile        *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile [3]>::Type,
                                          int const volatile  *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int                   >::Type,
                                          int                         );
        ASSERT_SAME(bslmf::ArrayToPointer<int const             >::Type,
                                          int const                   );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile          >::Type,
                                          int volatile                );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile    >::Type,
                                          int const volatile          );

        ASSERT_SAME(bslmf::ArrayToPointer<int                (&)[4]>::Type,
                                          int                    *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          (&)[4]>::Type,
                                          int const              *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       (&)[4]>::Type,
                                          int volatile           *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile (&)[4]>::Type,
                                          int const volatile     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int                 &    >::Type,
                                          int                 &          );
        ASSERT_SAME(bslmf::ArrayToPointer<int const           &    >::Type,
                                          int const           &          );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile        &    >::Type,
                                          int volatile        &          );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile  &    >::Type,
                                          int const volatile  &          );

        ASSERT_SAME(bslmf::ArrayToPointer<int                 * [5]>::Type,
                                          int                 *  *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const           * [5]>::Type,
                                          int const           *  *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile        * [5]>::Type,
                                          int volatile        *  *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile  * [5]>::Type,
                                          int const volatile  *  *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int                (*)[5]>::Type,
                                          int                (*)[5]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          (*)[5]>::Type,
                                          int const          (*)[5]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       (*)[5]>::Type,
                                          int volatile       (*)[5]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile (*)[5]>::Type,
                                          int const volatile (*)[5]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int                 *    >::Type,
                                          int                 *          );
        ASSERT_SAME(bslmf::ArrayToPointer<int const           *    >::Type,
                                          int const           *          );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile        *    >::Type,
                                          int volatile        *          );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile  *    >::Type,
                                          int const volatile  *          );

        ASSERT_SAME(bslmf::ArrayToPointer<int         [6][6]>::Type,
                                          int      (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int const   [6][6]>::Type,
                                          int const(*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int      (&)[6][6]>::Type,
                                          int      (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int       * [6][6]>::Type,
                                          int    * (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int      (*)[6][6]>::Type,
                                          int      (*)[6][6]      );

        ASSERT_SAME(bslmf::ArrayToPointer<int *const    [6][6]>::Type,
                                          int *const (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int *const (&)[6][6]>::Type,
                                          int *const (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int *const (*)[6][6]>::Type,
                                          int *const (*)[6][6]      );

        ASSERT_SAME(bslmf::ArrayToPointer<void *[]>::Type,
                                          void * *      );

        ASSERT_SAME(bslmf::ArrayToPointer<int                []>::Type,
                                          int                *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          []>::Type,
                                          int const          *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       []>::Type,
                                          int volatile       *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile []>::Type,
                                          int const volatile *       );

#ifndef BSLS_PLATFORM_CMP_MSVC
        ASSERT_SAME(bslmf::ArrayToPointer<int                (&)[]>::Type,
                                          int                   *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          (&)[]>::Type,
                                          int const             *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       (&)[]>::Type,
                                          int volatile          *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile (&)[]>::Type,
                                          int const volatile    *       );
#endif

        ASSERT_SAME(bslmf::ArrayToPointer<int                 * []>::Type,
                                          int                 * *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const           * []>::Type,
                                          int const           * *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile        * []>::Type,
                                          int volatile        * *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile  * []>::Type,
                                          int const volatile  * *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int                (*)[]>::Type,
                                          int                (*)[]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          (*)[]>::Type,
                                          int const          (*)[]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       (*)[]>::Type,
                                          int volatile       (*)[]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile (*)[]>::Type,
                                          int const volatile (*)[]      );

        ASSERT_SAME(bslmf::ArrayToPointer<int          [][7]>::Type,
                                          int         (*)[7]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int const    [][7]>::Type,
                                          int const   (*)[7]      );
#ifndef BSLS_PLATFORM_CMP_MSVC
        ASSERT_SAME(bslmf::ArrayToPointer<int       (&)[][7]>::Type,
                                          int       (*)  [7]      );
#endif
        ASSERT_SAME(bslmf::ArrayToPointer<int        * [][7]>::Type,
                                          int        *(*)[7]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int       (*)[][7]>::Type,
                                          int       (*)[][7]      );

        ASSERT_SAME(bslmf::ArrayToPointer<int *const    [][7]>::Type,
                                          int *const   (*)[7]      );
#ifndef BSLS_PLATFORM_CMP_MSVC
        ASSERT_SAME(bslmf::ArrayToPointer<int *const (&)[][7]>::Type,
                                          int *const (*)  [7]      );
#endif
        ASSERT_SAME(bslmf::ArrayToPointer<int *const (*)[][7]>::Type,
                                          int *const (*)[][7]      );

        ASSERT_SAME(bslmf::ArrayToPointer<Enum          [8]>::Type,
                                          Enum           *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Enum       (&)[8]>::Type,
                                          Enum           *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Enum const (&)[8]>::Type,
                                          Enum const     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Enum             >::Type,
                                          Enum                   );

        ASSERT_SAME(bslmf::ArrayToPointer<Struct    [8]>::Type,
                                          Struct     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Struct (&)[8]>::Type,
                                          Struct     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Struct       >::Type,
                                          Struct             );

        ASSERT_SAME(bslmf::ArrayToPointer<Union    [8]>::Type,
                                          Union     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Union (&)[8]>::Type,
                                          Union     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Union       >::Type,
                                          Union             );

        ASSERT_SAME(bslmf::ArrayToPointer<int  Struct::*    >::Type,
                                          int  Struct::*          );
        ASSERT_SAME(bslmf::ArrayToPointer<int (Struct::*)[9]>::Type,
                                          int (Struct::*)[9]      );
      } break;
      case 1: {
        // --------------------------------------------------------------------
        // Test Plan:
        //   Instantiate 'bslmf::ArrayToPointer' with various types and verify
        //   that their 'Type' member aliases the correctly decayed type.
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "bslmf::ArrayToPointer" << endl
                          << "====================" << endl;

        ASSERT_SAME(bslmf::ArrayToPointer<const char [6]>::Type, const char*);
        if (verbose) {
            //P(bslmf::ArrayToPointer<const char [6]>::ID);
#if !defined(BSLS_PLATFORM_CMP_CLANG)
            // Note that there is a bug in the Clang 3.1 compiler that causes
            // the front end to assert on the following 'typeid' expression:
            P(typeid(const char [6]).name());
#endif
            P(typeid(bslmf::ArrayToPointer<const char [6]>::Type).name());
        }

        ASSERT_SAME(bslmf::ArrayToPointer<char const [1]>::Type,
                    char const                      *);

        ASSERT_SAME(bslmf::ArrayToPointer<char       (&)[1]>::Type,
                    char           *       );

        ASSERT_SAME(bslmf::ArrayToPointer<char >::Type,
                    char                       );

        ASSERT_SAME(bslmf::ArrayToPointer<char const >::Type,
                    char                       const );

        ASSERT_SAME(bslmf::ArrayToPointer<char *>::Type,
                    char                       *);

        ASSERT_SAME(bslmf::ArrayToPointer<void  *[2]>::Type,
                    void                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<void const  *[2]>::Type,
                    void const                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<void       *(&)[2]>::Type,
                    void       *    *       );
        ASSERT_SAME(bslmf::ArrayToPointer<void *>::Type,
                    void                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<void >::Type,
                    void                       );

        ASSERT_SAME(bslmf::ArrayToPointer<int  [3]>::Type,
                    int                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<int const [3]>::Type,
                    int const                      *);
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile  [3]>::Type,
                    int volatile                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile  [3]>::Type,
                    int const volatile                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<int >::Type,
                    int                       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const >::Type,
                    int                       const );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile >::Type,
                    int volatile                       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile >::Type,
                    int const volatile                       );

        ASSERT_SAME(bslmf::ArrayToPointer<int                (&)[4]>::Type,
                    int                    *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          (&)[4]>::Type,
                    int const              *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       (&)[4]>::Type,
                    int volatile           *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile (&)[4]>::Type,
                    int const volatile     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int                 &    >::Type,
                    int                 &          );
        ASSERT_SAME(bslmf::ArrayToPointer<int const           &    >::Type,
                    int const           &          );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile        &    >::Type,
                    int volatile        &          );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile  &    >::Type,
                    int const volatile  &          );

        ASSERT_SAME(bslmf::ArrayToPointer<int  *[5]>::Type,
                    int                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<int const  *[5]>::Type,
                    int const                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile  *[5]>::Type,
                    int volatile                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile  *[5]>::Type,
                    int const volatile                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<int                (*)[5]>::Type,
                    int                (*)[5]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          (*)[5]>::Type,
                    int const          (*)[5]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       (*)[5]>::Type,
                    int volatile       (*)[5]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile (*)[5]>::Type,
                    int const volatile (*)[5]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int *>::Type,
                    int                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<int const *>::Type,
                    int const                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile *>::Type,
                    int volatile                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile *>::Type,
                    int const volatile                       *);

        ASSERT_SAME(bslmf::ArrayToPointer<int         [6][6]>::Type,
                    int      (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int   const [6][6]>::Type,
                    int const(*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int      (&)[6][6]>::Type,
                    int      (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int        *[6][6]>::Type,
                    int    * (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int      (*)[6][6]>::Type,
                    int      (*)[6][6]      );

        ASSERT_SAME(bslmf::ArrayToPointer<int    *const [6][6]>::Type,
                    int *const (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int *const (&)[6][6]>::Type,
                    int *const (*)[6]         );
        ASSERT_SAME(bslmf::ArrayToPointer<int *const (*)[6][6]>::Type,
                    int *const (*)[6][6]      );

        ASSERT_SAME(bslmf::ArrayToPointer<void  *[]>::Type,
                    void                       **);

        ASSERT_SAME(bslmf::ArrayToPointer<int  []>::Type,
                    int                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<int const []>::Type,
                    int const                      *);
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile  []>::Type,
                    int volatile                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile  []>::Type,
                    int const volatile                       *);

#ifndef BSLS_PLATFORM_CMP_MSVC
        ASSERT_SAME(bslmf::ArrayToPointer<int                (&)[]>::Type,
                    int                   *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          (&)[]>::Type,
                    int const             *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       (&)[]>::Type,
                    int volatile          *       );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile (&)[]>::Type,
                    int const volatile    *       );
#endif

        ASSERT_SAME(bslmf::ArrayToPointer<int  *[]>::Type,
                    int                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<int const  *[]>::Type,
                    int const                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile  *[]>::Type,
                    int volatile                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile  *[]>::Type,
                    int const volatile                       **);
        ASSERT_SAME(bslmf::ArrayToPointer<int                (*)[]>::Type,
                    int                (*)[]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int const          (*)[]>::Type,
                    int const          (*)[]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int volatile       (*)[]>::Type,
                    int volatile       (*)[]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int const volatile (*)[]>::Type,
                    int const volatile (*)[]      );

        ASSERT_SAME(bslmf::ArrayToPointer<int          [][7]>::Type,
                    int         (*)[7]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int    const [][7]>::Type,
                    int const   (*)[7]      );
#ifndef BSLS_PLATFORM_CMP_MSVC
        ASSERT_SAME(bslmf::ArrayToPointer<int       (&)[][7]>::Type,
                    int       (*)  [7]      );
#endif
        ASSERT_SAME(bslmf::ArrayToPointer<int         *[][7]>::Type,
                    int        *(*)[7]      );
        ASSERT_SAME(bslmf::ArrayToPointer<int       (*)[][7]>::Type,
                    int       (*)[][7]      );

        ASSERT_SAME(bslmf::ArrayToPointer<int    *const [][7]>::Type,
                    int *const   (*)[7]      );
#ifndef BSLS_PLATFORM_CMP_MSVC
        ASSERT_SAME(bslmf::ArrayToPointer<int *const (&)[][7]>::Type,
                    int *const (*)  [7]      );
#endif
        ASSERT_SAME(bslmf::ArrayToPointer<int *const (*)[][7]>::Type,
                    int *const (*)[][7]      );

        ASSERT_SAME(bslmf::ArrayToPointer<Enum  [8]>::Type,
                    Enum                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<Enum       (&)[8]>::Type,
                    Enum           *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Enum const (&)[8]>::Type,
                    Enum const     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Enum >::Type,
                    Enum                       );

        ASSERT_SAME(bslmf::ArrayToPointer<Struct  [8]>::Type,
                    Struct                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<Struct (&)[8]>::Type,
                    Struct     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Struct >::Type,
                    Struct                       );

        ASSERT_SAME(bslmf::ArrayToPointer<Union  [8]>::Type,
                    Union                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<Union (&)[8]>::Type,
                    Union     *       );
        ASSERT_SAME(bslmf::ArrayToPointer<Union >::Type,
                    Union                       );

        ASSERT_SAME(bslmf::ArrayToPointer<int  Struct:: *>::Type,
                    int  Struct::                       *);
        ASSERT_SAME(bslmf::ArrayToPointer<int (Struct::*)[9]>::Type,
                    int (Struct::*)[9]      );
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
