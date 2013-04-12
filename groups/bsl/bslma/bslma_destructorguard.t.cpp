// bslma_destructorguard.t.cpp                                        -*-C++-*-

#include <bslma_destructorguard.h>

#include <bslma_default.h>
#include <bslma_testallocator.h>

#include <bsls_bsltestutil.h>
#include <bsls_objectbuffer.h>

#include <vector>       // std::vector for the usage example

#include <stdio.h>
#include <stdlib.h>

using namespace BloombergLP;

//=============================================================================
//                             TEST PLAN
//-----------------------------------------------------------------------------
//                              Overview
//                              --------
// We are testing a proctor object to ensure that it destroys the proper
// sequence of contiguous objects (in unspecified order).  We achieve this goal
// by creating objects of a user-defined type that are each initialized with
// the address of a unique counter.  As each object is destroyed, its
// destructor increments the counter held by the object, indicating the number
// of times the object's destructor is called.  We create proctors to manage
// varying sequences (differing in origin and length) of such user-defined-type
// objects in an array.  After each proctor is destroyed, we verify that the
// corresponding counters of the objects managed by the proctor are modified.
//-----------------------------------------------------------------------------
// [2] bslma::DestructorGuard<TYPE>(&object)
// [2] ~bslma::DestructorGuard<TYPE>();
//-----------------------------------------------------------------------------
// [1] my_Class(&counter);
// [1] ~my_Class();
//=============================================================================

//=============================================================================
//                  STANDARD BDE ASSERT TEST MACRO
//-----------------------------------------------------------------------------
// NOTE: THIS IS A LOW-LEVEL COMPONENT AND MAY NOT USE ANY C++ LIBRARY
// FUNCTIONS, INCLUDING IOSTREAMS.
static int testStatus = 0;

static void aSsErT(bool b, const char *s, int i) {
    if (b) {
        printf("Error " __FILE__ "(%d): %s    (failed)\n", i, s);
        if (testStatus >= 0 && testStatus <= 100) ++testStatus;
    }
}

//=============================================================================
//                       STANDARD BDE TEST DRIVER MACROS
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

// ============================================================================
//                  NEGATIVE-TEST MACRO ABBREVIATIONS
// ----------------------------------------------------------------------------

#define ASSERT_SAFE_PASS(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_PASS(EXPR)
#define ASSERT_SAFE_FAIL(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_FAIL(EXPR)
#define ASSERT_PASS(EXPR)      BSLS_ASSERTTEST_ASSERT_PASS(EXPR)
#define ASSERT_FAIL(EXPR)      BSLS_ASSERTTEST_ASSERT_FAIL(EXPR)
#define ASSERT_OPT_PASS(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_PASS(EXPR)
#define ASSERT_OPT_FAIL(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_FAIL(EXPR)

//=============================================================================
//                          HELPER CLASS FOR TESTING
//-----------------------------------------------------------------------------

class my_Class {
    // This object indicates that its destructor is called by incrementing the
    // counter it *holds* (provided at construction) in the destructor.
  private:
    int *d_counter_p; // Counter to be incremented at destruction

  public:
    // CREATORS
    my_Class(int *counter) : d_counter_p(counter) {}
        // Create this object and optionally specify the address of the
        // 'counter' to be held.

    ~my_Class() { ++*d_counter_p; }
        // Destroy this object.  Also increment this object's counter if it is
        // not 'null'.
};

//=============================================================================
//                  GLOBAL TYPEDEFS, CONSTANTS AND VARIABLES
//-----------------------------------------------------------------------------

int test;
int verbose;
int veryVerbose;

//=============================================================================
//                              USAGE EXAMPLE
//-----------------------------------------------------------------------------

// Suppose we have a situation where one of the two constructors will be
// called to create an object on the stack for performance reasons.  The
// construction thus occurs within either of the branches of an 'if'
// statement, so the object itself, to survive the end of the "then" or "else"
// block, must be constructed in a 'bsls::ObjectBuffer'.  Once constructed, the
// object would not be destroyed automatically, so to make sure it will be
// destroyed, we place it under the management of a 'bslma::DestructorGuard'.
// After that, we know that however the routine exits -- either by a return
// or as a result of an exception being thrown -- the object will be destroyed.

double usageExample(double startValue)
{
    bsls::ObjectBuffer<std::vector<double> > buffer;
    std::vector<double>& myVec = buffer.object();

    if (startValue >= 0) {
        new (&myVec) std::vector<double>(100, startValue);
    }
    else {
        new (&myVec) std::vector<double>();
    }

    //***********************************************************
    // Note the use of the destructor guard on 'myVec' (below). *
    //***********************************************************

    bslma::DestructorGuard<std::vector<double> > guard(&myVec);
        // Note that regardless of how this routine terminates, 'myVec'
        // will be destroyed.

    myVec.push_back(3.0);
        // Note that 'push_back' could allocate memory and therefore may
        // throw.  However, if it does, 'myVec' will be destroyed
        // automatically along with 'guard'.

    if (myVec[0] >= 5.0) {
        return 5.0;                                               // RETURN
            // Note that 'myVec' is automatically destroyed as the
            // function returns.
    }

    return myVec[myVec.size() / 2];
        // Note that 'myVec' is destroyed after the temporary containing
        // the return value is created.
}

//=============================================================================
//                                MAIN PROGRAM
//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    test = argc > 1 ? atoi(argv[1]) : 0;
    verbose = argc > 2;
    veryVerbose = argc > 3;

    printf("TEST " __FILE__ " CASE %d\n", test);

    switch (test) { case 0:
      case 3: {
        // --------------------------------------------------------------------
        // USAGE EXAMPLE
        //
        // Concerns:
        //   That the usage example compiles and produces the expected
        //   results given different inputs.
        // --------------------------------------------------------------------

        if (verbose) printf("\nUSAGE EXAMPLE"
                            "\n=============\n");

        double result;

        result = usageExample(10.0);
        ASSERT(5.0 == result);

        result = usageExample(2.0);
        ASSERT(2.0 == result);

        result = usageExample(-1.0);
        ASSERT(3.0 == result);
      } break;
      case 2: {
        // --------------------------------------------------------------------
        // BREATHING TEST
        //
        // Concerns:
        //   Need to exercise basic functionality of 'bslma::DestructorGuard'.
        //   Note that since this class has only a c'tor and d'tor, the
        //   breathing test is a thorough test of the component.
        //
        // Plan:
        //   Have an instance of 'my_Class', a class which can be destructed
        //   multiple times and which keeps count of the number of times it has
        //   been destructed.  Use 'bslma::DestructorGuard' to destruct it
        //   several times and verify that the expected destructions occur.
        //
        // Testing:
        //   bslma::DestructorGuard()
        //   ~bslma::DestructorGuard()
        // --------------------------------------------------------------------

        if (verbose) printf("\nBREATHING TEST"
                            "\n==============\n");

        int counter = 0;
        int i;
        {
            my_Class mC(&counter);

            for (i = 0; i < 10; ++i) {
                ASSERT(i == counter);

                bslma::DestructorGuard<my_Class> mX(&mC);

                ASSERT(i == counter);
            }
            ASSERT(i == counter);
        }
        ASSERT(i + 1 == counter);
      } break;
      case 1: {
        // --------------------------------------------------------------------
        // HELPER CLASS TEST
        //
        // Concerns:
        //   That the destructor for the helper class 'my_Class' increments
        //   the object's counter appropriately, and that there are no ill
        //   effects from calling the destructor on a given instance of
        //   my_Class multiple times.
        //
        // Plan:
        //   Several times, create an instance of 'my_Class' referring to
        //   'counter', verify that 'counter' gets incremented once for every
        //   instance of 'my_Class' going out of scope.  The in another loop
        //   iterate calling the destructor for the same 'my_Class' object
        //   several times, verifying that calling the destructor on the same
        //   object multiple times has the desired effect.
        //
        // Testing:
        //   my_Class(&counter);
        //   ~my_Class();
        // --------------------------------------------------------------------

        if (verbose) printf("\nHELPER CLASS TEST"
                            "\n=================\n");

        if (verbose) printf("Testing 'my_Class'.\n");
        {
            int counter = 0;
            const int NUM_TEST = 5;
            for (int i = 0; i < NUM_TEST; ++i) {
                LOOP_ASSERT(i, counter == i);
                my_Class mX(&counter);
            }
            ASSERT(NUM_TEST == counter);
        }

        {
            int counter = 0;
            const int NUM_TEST = 5;
            {
                my_Class mX(&counter);
                for (int i = 0; i < NUM_TEST; ++i) {
                    ASSERT(i == counter);
                    mX.~my_Class();
                }
                ASSERT(NUM_TEST == counter);
            }
            ASSERT(NUM_TEST + 1 == counter);
        }
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
