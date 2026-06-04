#ifndef MINUNIT_H
#define MINUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define RED             "\033[1;31m"
#define GREEN           "\033[1;32m"
#define YELLOW          "\033[1;33m"
#define CYAN            "\033[1;36m"
#define RESET           "\033[0m"

int g_tests_run = 0;
int g_tests_passed = 0;
int g_tests_failed = 0;
FILE *g_trace_file = NULL;

void minunit_init(const char *trace_path)
{
    if (trace_path)
        g_trace_file = fopen(trace_path, "a");
}

void minunit_close(void)
{
    if (g_trace_file)
    {
        fclose(g_trace_file);
        g_trace_file = NULL;
    }
}

void minunit_log(const char *fmt, ...)
{
    va_list args;

    if (g_trace_file)
    {
        va_start(args, fmt);
        vfprintf(g_trace_file, fmt, args);
        va_end(args);
        fflush(g_trace_file);
    }
}

#define ASSERT_EQ(actual, expected) \
    do { \
        g_tests_run++; \
        if ((actual) == (expected)) { \
            g_tests_passed++; \
            printf(GREEN "✓" RESET); \
            fflush(stdout); \
            minunit_log("[PASS] %s == %s\n", #actual, #expected); \
        } else { \
            g_tests_failed++; \
            printf(RED "✗" RESET); \
            fflush(stdout); \
            minunit_log("[FAIL] %s (%ld) != %s (%ld) at %s:%d\n", \
                #actual, (long)(actual), #expected, (long)(expected), __FILE__, __LINE__); \
        } \
    } while (0)

#define ASSERT_NE(actual, expected) \
    do { \
        g_tests_run++; \
        if ((actual) != (expected)) { \
            g_tests_passed++; \
            printf(GREEN "✓" RESET); \
            fflush(stdout); \
            minunit_log("[PASS] %s != %s\n", #actual, #expected); \
        } else { \
            g_tests_failed++; \
            printf(RED "✗" RESET); \
            fflush(stdout); \
            minunit_log("[FAIL] %s should not equal %s at %s:%d\n", \
                #actual, #expected, __FILE__, __LINE__); \
        } \
    } while (0)

#define ASSERT_TRUE(cond) \
    do { \
        g_tests_run++; \
        if ((cond)) { \
            g_tests_passed++; \
            printf(GREEN "✓" RESET); \
            fflush(stdout); \
            minunit_log("[PASS] %s is true\n", #cond); \
        } else { \
            g_tests_failed++; \
            printf(RED "✗" RESET); \
            fflush(stdout); \
            minunit_log("[FAIL] %s is false at %s:%d\n", #cond, __FILE__, __LINE__); \
        } \
    } while (0)

#define ASSERT_FALSE(cond) \
    do { \
        g_tests_run++; \
        if (!(cond)) { \
            g_tests_passed++; \
            printf(GREEN "✓" RESET); \
            fflush(stdout); \
            minunit_log("[PASS] %s is false\n", #cond); \
        } else { \
            g_tests_failed++; \
            printf(RED "✗" RESET); \
            fflush(stdout); \
            minunit_log("[FAIL] %s is true at %s:%d\n", #cond, __FILE__, __LINE__); \
        } \
    } while (0)

#define ASSERT_NULL(ptr) \
    do { \
        g_tests_run++; \
        if ((ptr) == NULL) { \
            g_tests_passed++; \
            printf(GREEN "✓" RESET); \
            fflush(stdout); \
            minunit_log("[PASS] %s is NULL\n", #ptr); \
        } else { \
            g_tests_failed++; \
            printf(RED "✗" RESET); \
            fflush(stdout); \
            minunit_log("[FAIL] %s is not NULL at %s:%d\n", #ptr, __FILE__, __LINE__); \
        } \
    } while (0)

#define ASSERT_NOT_NULL(ptr) \
    do { \
        g_tests_run++; \
        if ((ptr) != NULL) { \
            g_tests_passed++; \
            printf(GREEN "✓" RESET); \
            fflush(stdout); \
            minunit_log("[PASS] %s is not NULL\n", #ptr); \
        } else { \
            g_tests_failed++; \
            printf(RED "✗" RESET); \
            fflush(stdout); \
            minunit_log("[FAIL] %s is NULL at %s:%d\n", #ptr, __FILE__, __LINE__); \
        } \
    } while (0)

#define TEST_SUITE(name) \
    printf(CYAN "\n=== %s ===" RESET "\n", name); \
    minunit_log("\n=== %s ===\n", name);

#define TEST_RESULT() \
    do { \
        printf("\n"); \
        if (g_tests_failed == 0) { \
            printf(GREEN "✓ All %d tests passed\n" RESET, g_tests_passed); \
            minunit_log("✓ All %d tests passed\n", g_tests_passed); \
        } else { \
            printf(RED "✗ %d/%d tests failed\n" RESET, g_tests_failed, g_tests_run); \
            minunit_log("✗ %d/%d tests failed\n", g_tests_failed, g_tests_run); \
        } \
    } while (0)

#endif
