// bsls_annotation.t.cpp                                              -*-C++-*-
#include <bsls_annotation.h>

#include <bsls_bsltestutil.h>

#include <iostream>

#include <stdlib.h>  // 'calloc', 'realloc', 'atoi'
#include <string.h>  // 'strcmp'

static int testStatus = 0;

//=============================================================================
//                  SEMI-STANDARD TEST OUTPUT MACROS
//-----------------------------------------------------------------------------
#define P(X) cout << #X " = " << (X) << endl; // Print identifier and value.
#define Q(X) printf("<| " #X " |>\n");        // Quote identifier literally.
#define P_(X) cout << #X " = " << (X) << ", " << flush; // P(X) without '\n'
#define L_ __LINE__                           // current Line number
#define T_ printf("\t");                      // Print a tab (w/o newline)

// ============================================================================
//                  DECLARATION/DEFINITION OF ANNOTATED FUNCTIONS
// ----------------------------------------------------------------------------

void *test_ALLOC_SIZE(void *ptr, size_t size) BSLS_ANNOTATION_ALLOC_SIZE(2);
void *test_ALLOC_SIZE(void *ptr, size_t size)                        // { 1fo }
{
    return realloc(ptr, size);
}

void *test_ALLOC_SIZE_MUL(size_t count, size_t size)
                                          BSLS_ANNOTATION_ALLOC_SIZE_MUL(1, 2);
void *test_ALLOC_SIZE_MUL(size_t count, size_t size)                 // { 2fo }
{
    return calloc(count, size);
}

int test_ERROR() BSLS_ANNOTATION_ERROR
                               ("myExpectedError: Do not call 'test_WARNING'");
int test_ERROR()
{
    return 1;
}

int test_WARNING()
              BSLS_ANNOTATION_WARNING("myWarning: Do not call 'test_WARNING'");
int test_WARNING()
{
    return 1;
}

void test_PRINTF(const char *pattern, ...) BSLS_ANNOTATION_PRINTF(1, 2);
void test_PRINTF(const char *pattern, ...)
{
    (void)pattern;
}

void test_SCANF(const char *, ...) BSLS_ANNOTATION_SCANF(1, 2);
void test_SCANF(const char *, ...)
{
}

const char *test_FORMAT(const char *locale, const char *format)
                                                     BSLS_ANNOTATION_FORMAT(2);
const char *test_FORMAT(const char *locale, const char *format)
{
    if (0 == strcmp(locale, "FR") && 0 == strcmp(format, "Name: %s")) {
        return "Nom: %s";                                             // RETURN
    }

    return "translateFormat: bad locale or format argument - no translation";
}

char test_ARG1_NON_NULL(void *p, void *q, void *r)
                                              BSLS_ANNOTATION_ARG_NON_NULL(1);
char test_ARG1_NON_NULL(void *p, void *q, void *r)
{
    char c = *reinterpret_cast<char *>(p);
    (void)q;
    (void)r;

    return c;
}

char test_ARG2_NON_NULL(void *p, void *q, void *r)
                                              BSLS_ANNOTATION_ARG_NON_NULL(2);
char test_ARG2_NON_NULL(void *p, void *q, void *r)
{
    (void)p;
    char c = *reinterpret_cast<char *>(q);
    (void)r;

    return c;
}

void test_ARGS_NON_NULL(void *, void *) BSLS_ANNOTATION_ARGS_NON_NULL;
void test_ARGS_NON_NULL(void *, void *)
{
}

void test_NULL_TERMINATED(void *, ...) BSLS_ANNOTATION_NULL_TERMINATED;
void test_NULL_TERMINATED(void *, ...)
{
}

void test_NULL_TERMINATED_AT2(void *, ...)
                                         BSLS_ANNOTATION_NULL_TERMINATED_AT(2);
void test_NULL_TERMINATED_AT2(void *, ...)
{
}

void test_NULL_TERMINATED_AT3(void *, ...)
                                         BSLS_ANNOTATION_NULL_TERMINATED_AT(3);
void test_NULL_TERMINATED_AT3(void *, ...)
{
}

int test_WARN_UNUSED_RESULT() BSLS_ANNOTATION_WARN_UNUSED_RESULT;
int test_WARN_UNUSED_RESULT()
{
    return 1;
}

void test_DEPRECATED_function() BSLS_ANNOTATION_DEPRECATED;
void test_DEPRECATED_function()
{
}

static
void test_UNUSED_function() BSLS_ANNOTATION_UNUSED;                  // {14fwn}
void test_UNUSED_function()
{
}

// ============================================================================
//                  DEFINITION OF ANNOTATED VARIABLES
// ----------------------------------------------------------------------------

int test_DEPRECATED_variable BSLS_ANNOTATION_DEPRECATED;

static
int test_UNUSED_variable     BSLS_ANNOTATION_UNUSED;                 // {14vwn}

// ============================================================================
//                  DEFINITION OF ANNOTATED TYPES
// ----------------------------------------------------------------------------

struct Test_DEPRECATED_type {
    int d_d;
} BSLS_ANNOTATION_DEPRECATED;

struct Test_UNUSED_type {
    int d_d;
} BSLS_ANNOTATION_UNUSED;

// ============================================================================
//                  USAGE WITH NO EXPECTED COMPILER WARNINGS
// ----------------------------------------------------------------------------

void use_without_diagnostic_message_PRINTF()                         // { 5fwn}
{
    test_PRINTF("%s", "string");
    test_PRINTF("%d", 1);
    test_PRINTF("%f", 3.14159);
}

void use_without_diagnostic_message_SCANF()                          // { 6fwn}
{
    char   buffer[20];
    int    i;
    double d;

    test_SCANF("%s",  buffer);
    test_SCANF("%d",  &i);
    test_SCANF("%lf", &d);
}

void use_without_diagnostic_message_FORMAT()                         // { 7fwn}
{
    test_PRINTF(test_FORMAT("FR", "Name: %s"), "Michael Bloomberg");
}

void use_without_diagnostic_message_ARG1_NON_NULL()                  // { 8fwn}
{
    char buffer1[2];
    test_ARG1_NON_NULL(buffer1, NULL, NULL);
}

void use_without_diagnostic_message_ARG2_NON_NULL()
{
    char buffer2[2];
    test_ARG2_NON_NULL(NULL, buffer2, NULL);
}

void use_without_diagnostic_message_ARGS_NON_NULL()                  // { 9fwn}
{
    char buffer1[2];
    char buffer2[2];

    test_ARGS_NON_NULL(buffer1, buffer2);
}

void use_without_diagnostic_message_NULL_TERMINATED()                // {10fwn}
{
    char buffer1[2];
    char buffer2[2];
    char buffer3[2];
    char buffer4[2];
    test_NULL_TERMINATED(buffer1, buffer2, buffer3, buffer4, NULL);
}

void use_without_diagnostic_message_NULL_TERMINATED_AT2()            // {11fwn}
{
    char buffer1[2];
    char buffer2[2];
    char buffer4[2];
    char buffer5[2];
    test_NULL_TERMINATED_AT2(buffer1, buffer2, NULL, buffer4, buffer5);
}

void use_without_diagnostic_message_NULL_TERMINATED_AT3()
{
    char buffer1[2];
    char buffer3[2];
    char buffer4[2];
    char buffer5[2];
    test_NULL_TERMINATED_AT3(buffer1, NULL, buffer3, buffer4, buffer5);
}

int use_without_diagnostic_message_WARN_UNUSED_RESULT()              // {12fwn}
{
    return test_WARN_UNUSED_RESULT();
}

// ============================================================================
//                  USAGE WITH EXPECTED COMPILER WARNINGS
// ----------------------------------------------------------------------------

#ifdef BSLS_ANNOTATION_TRIGGER_OTHER

int use_with_warning_message_Warning = test_WARNING();               // { 4fw }

void use_with_warning_message_PRINTF()                               // { 5fwy}
{
    test_PRINTF("%s", 3.14159);
    test_PRINTF("%d", "string");
    test_PRINTF("%f", "other string");
}

void use_with_warning_message_SCANF()                                // { 6fwy}
{
    char   buffer[20];
    int    i;
    double d;

    test_SCANF("%s", &i);
    test_SCANF("%d", buffer);
    test_SCANF("%f", buffer);
}

void use_with_warning_message_FORMAT()                               // { 7fwy}
{
    test_PRINTF(test_FORMAT("FR", "Name: %s"), 3);
}

void use_with_warning_message_ARG1_NON_NULL()                        // { 8fwy}
{
    test_ARG1_NON_NULL(NULL, NULL, NULL);
}

void use_with_warning_message_ARG2_NON_NULL()
{
    test_ARG2_NON_NULL(NULL, NULL, NULL);
}

void use_with_warning_message_ARGS_NON_NULL()                        // { 9fwy}
{
    char buffer1[2];
    char buffer2[2];

    test_ARGS_NON_NULL(NULL, buffer2);
    test_ARGS_NON_NULL(buffer1, NULL);
    test_ARGS_NON_NULL(NULL, NULL);
}

void use_with_warning_message_NULL_TERMINATED()                      // {10fwy}
{
    char buffer1[2];
    char buffer2[2];
    char buffer3[2];
    char buffer4[2];
    char buffer5[2];
    test_NULL_TERMINATED(buffer1, buffer2, buffer3, buffer4, buffer5);
}

void use_with_warning_message_NULL_TERMINATED_AT2()                  // {11fwy}
{
    char buffer1[2];
    char buffer2[2];
    char buffer3[2];
    char buffer4[2];
    char buffer5[2];
    test_NULL_TERMINATED_AT2(buffer1, buffer2, buffer3, buffer4, buffer5);
}
void use_with_warning_message_NULL_TERMINATED_AT3()
{
    char buffer1[2];
    char buffer2[2];
    char buffer3[2];
    char buffer4[2];
    char buffer5[2];
    test_NULL_TERMINATED_AT3(buffer1, buffer2, buffer3, buffer4, buffer5);
}

void use_with_warning_message_WARN_UNUSED_RESULT()                   // {12fwy}
{
    test_WARN_UNUSED_RESULT();
}

void use_with_warning_message_DEPRECATED_function()                  // {13fw }
{
    test_DEPRECATED_function();
}

void use_with_warning_message_DEPRECATED_variable()                  // {13vw }
{
    test_DEPRECATED_variable;
}

int use_with_warning_message_DEPRECATED_type()                       // {13tw }
{
    Test_DEPRECATED_type instance_of_DEPRECATED_TYPE;
    instance_of_DEPRECATED_TYPE.d_d = 0;
    return instance_of_DEPRECATED_TYPE.d_d;
}


#endif

// ============================================================================
//                  USAGE WITH EXPECTED COMPILER ERRORS
// ----------------------------------------------------------------------------

#ifdef BSLS_ANNOTATION_TRIGGER_ERROR

int use_with_error_message_Error = test_ERROR();                     // { 3fe }

#endif

// ----------------------------------------------------------------------------

using namespace BloombergLP;
using namespace std;

// ============================================================================
//                            MAIN PROGRAM
// ----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    int    test = argc > 1 ? atoi(argv[1]) : 0;
    int verbose = argc > 2;

    cout << "TEST " << __FILE__ << " CASE " << test << endl;;

    switch (test) { case 0:
      case 1: {
        // --------------------------------------------------------------------
        // BREATHING TEST
        //
        // Concerns:
        //: 1 This test driver does *not* build when the
        //:   'BSLS_ANNOTATION_TRIGGER_ERROR' preprocessor variable is defined
        //:   and all expected output appears.
        //:
        //: 2 This test driver builds with all expected compiler warning
        //:   messages and no unexpected warnings when the
        //:   'BSLS_ANNOTATION_TRIGGER_OTHER' preprocessor variable is defined.
        //
        // Plan:
        //: 1 Build with 'BSLS_ANNOTATION_TRIGGER_ERROR' defined and externally
        //:   confirm that compilation of this task failed and the compiler
        //:   output shows the expected message.  (C-1)
        //:
        //: 2 Build with 'BSLS_ANNOTATION_TRIGGER_WARNINGS' defined and
        //:   externally examine compiler output for expected warnings and
        //:   the absence of warnings expected to be suppressed.  (C-2)
        //
        // Testing:
        //   BREATHING TEST
        // --------------------------------------------------------------------

        if (verbose) cout << endl
                          << "BREATHING TEST" << endl
                          << "==============" << endl;

        if (verbose) {
            cout
              << "\nThere are no run-time tests for this component."
              << "\nManually run build-time tests using a conforming compiler."
              << endl;
#ifdef BSLS_PLATFORM_CMP_GNU
            P(BSLS_PLATFORM_CMP_GNU);
#endif
#ifdef BSLS_PLATFORM_CMP_VER_MAJOR
           P(BSLS_PLATFORM_CMP_VER_MAJOR);
#endif
        }

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
