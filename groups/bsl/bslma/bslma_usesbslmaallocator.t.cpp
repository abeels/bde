// bslma_usesbslmaallocator.t.cpp                                     -*-C++-*-

#include <bslma_usesbslmaallocator.h>

#include <bslma_allocator.h>

#include <bsls_bsltestutil.h>

#include <cstdio>
#include <cstdlib>

using namespace BloombergLP;
using namespace std;
using namespace bsl;

//=============================================================================
//                             TEST PLAN
//-----------------------------------------------------------------------------
//
//

//-----------------------------------------------------------------------------

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

enum { VERBOSE_ARG_NUM = 2, VERY_VERBOSE_ARG_NUM, VERY_VERY_VERBOSE_ARG_NUM };

struct SniffUsesBslmaAllocatorFromConstructor
{
    SniffUsesBslmaAllocatorFromConstructor(bslma::Allocator *);
};

struct ConstructFromAnyPointer
{
    template <typename TYPE>
    ConstructFromAnyPointer(TYPE *);
};

struct ClassUsingBslmaAllocator
{
};

struct DerivedAllocator : bslma::Allocator
{
};

struct ConvertibleToAny
    // Type that can be converted to any type.  'DetectNestedTrait' shouldn't
    // assign it any traits.  The concern is that since
    // 'BSLMF_NESTED_TRAIT_DECLARATION' defines its own conversion operator,
    // the "convert to anything" operator shouldn't interfere with the nested
    // trait logic.
{
    template <typename T>
    operator T() const { return T(); }
};

}

namespace BloombergLP {
namespace bslma {

template <>
struct UsesBslmaAllocator<ClassUsingBslmaAllocator> : bsl::true_type {};

template <>
struct UsesBslmaAllocator<ConvertibleToAny> : bsl::true_type {
    // Even though the nested trait logic is disabled by the template
    // conversion operator, the out-of-class trait specialization should still
    // work.
};

}
}

//=============================================================================
//                  CLASSES FOR TESTING USAGE EXAMPLES
//-----------------------------------------------------------------------------


//=============================================================================
//                              MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int test = argc > 1 ? atoi(argv[1]) : 0;
    bool verbose = argc > 2;
    bool veryVerbose = argc > 3;
    bool veryVeryVerbose = argc > 4;

    printf("TEST " __FILE__ " CASE %d\n", test);

    switch (test) { case 0:  // Zero is always the leading case.
      case 1: {
        // --------------------------------------------------------------------
        // BREATHING/USAGE TEST
        //
        // Concerns:
        //
        // Plan:
        //
        // Testing:
        //
        // --------------------------------------------------------------------

        if (verbose) printf("\nBREATHING TEST"
                            "\n==============\n");

        ASSERT(bslma::UsesBslmaAllocator<
                    SniffUsesBslmaAllocatorFromConstructor>::value);
        ASSERT(bslma::UsesBslmaAllocator<
                    SniffUsesBslmaAllocatorFromConstructor const>::value);
        ASSERT(bslma::UsesBslmaAllocator<
                    SniffUsesBslmaAllocatorFromConstructor volatile>::value);

        ASSERT(bslma::UsesBslmaAllocator<
                    ClassUsingBslmaAllocator>::value);
        ASSERT(bslma::UsesBslmaAllocator<
                    ClassUsingBslmaAllocator const>::value);
        ASSERT(bslma::UsesBslmaAllocator<
                    ClassUsingBslmaAllocator volatile>::value);

        ASSERT(! bslma::UsesBslmaAllocator<ConstructFromAnyPointer>::value);
        ASSERT(! bslma::UsesBslmaAllocator<bslma::Allocator *>::value);
        ASSERT(! bslma::UsesBslmaAllocator<bslma::Allocator const *>::value);
        ASSERT(! bslma::UsesBslmaAllocator<bslma::Allocator volatile *>::value);

        ASSERT(! bslma::UsesBslmaAllocator<DerivedAllocator *>::value);

        ASSERT(bslma::UsesBslmaAllocator<ConvertibleToAny>::value);
      } break;

      default: {
        fprintf(stderr, "WARNING: CASE `%d' NOT FOUND.\n", test);
        testStatus = -1;
      }
    }

    if (testStatus > 0) {
        fprintf(stderr, "Error, non-zero test status = %d.\n", testStatus);
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
