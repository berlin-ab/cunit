#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cexpect.h"

#define MAX_SUITE_SIZE 100


struct TestData {
    bool is_active;
    void (*test_function)(Test *test);
    Suite *suite;
};


typedef struct FailedTestData {
    char *expected_value;
    char *actual_value;
} FailedTest;


struct SuiteData {
    char *name;
    Test tests[MAX_SUITE_SIZE];
    FailedTest failed_tests[MAX_SUITE_SIZE];
    int size;
    int number_of_failed_tests;
    int number_of_passing_tests;
    Formatter *formatter;
};


struct FormatterData {
    void (*fail)(Test *test);
    void (*success)(Test *test);
    void (*summary)(Suite *suite);
    void (*report_start)(Suite *suite);
};


int number_of_failed_tests(Suite *suite) {
	return suite->number_of_failed_tests;
}


int number_of_passing_tests(Suite *suite) {
	return suite->number_of_passing_tests;
}

void pass_test(Test *test) {
	test->suite->number_of_passing_tests++;
	test->suite->formatter->success(test);
}


void fail_test(Test *test, char *expected_value, char *actual_value) {
    FailedTest failed_test;
    failed_test.expected_value = expected_value;
    failed_test.actual_value = actual_value;

    test->suite->failed_tests[test->suite->number_of_failed_tests] = failed_test;
    test->suite->number_of_failed_tests++;
    test->suite->formatter->fail(test);
}


void expect_equal(Test *test, int expected_value, int actual_value) {
    if (expected_value == actual_value) {
	pass_test(test);
    } else {
        char *expected_value_string = calloc(100, sizeof(char));
        char *actual_value_string = calloc(100, sizeof(char));

	sprintf(expected_value_string, "%d", expected_value);
	sprintf(actual_value_string, "%d", actual_value);

	fail_test(test, expected_value_string, actual_value_string);
    }
}


void report_failing_test_with_void(Test *test) {
}


void report_successful_test_with_void(Test *test) {
}


void report_summary_for_void(Suite *suite) {
}


void report_start_for_void(Suite *suite) {
}


void report_failing_test_with_dot(Test *test) {
    printf("F");
}


void report_successful_test_with_dot(Test *test) {
    printf(".");
}


void report_start_for_dots(Suite *suite) {
    printf("Running suite: %s\n", suite->name);
}


void report_summary_for_dots(Suite *suite) {
    printf("\n");
    printf("\n");
    printf("Summary:\n");
    printf("\nRan %d test(s).\n\n%d passed, %d failed",
	   suite->size,
	   suite->number_of_passing_tests,
	   suite->number_of_failed_tests);
    printf("\n\n");
    for(int i = 0; i < suite->number_of_failed_tests; i++) {
        FailedTest failed_test = suite->failed_tests[i];
        printf("expected %s, got %s\n",
	       failed_test.expected_value,
	       failed_test.actual_value);
    }
    printf("\n\n\n\n");
}


Formatter *make_void_formatter() {
    Formatter *formatter = calloc(1, sizeof(Formatter));
    formatter->fail = report_failing_test_with_void;
    formatter->success = report_successful_test_with_void;
    formatter->summary = report_summary_for_void;
    formatter->report_start = report_start_for_void;
    return formatter;
}


Formatter *make_dot_formatter() {
    Formatter *formatter = calloc(1, sizeof(Formatter));
    formatter->fail = report_failing_test_with_dot;
    formatter->success = report_successful_test_with_dot;
    formatter->summary = report_summary_for_dots;
    formatter->report_start = report_start_for_dots;
    return formatter;
}


void add_test(Suite *suite, void (*test_function)(Test *test)) {
    Test test;
    test.is_active = true;
    test.test_function = test_function;
    test.suite = suite;
    
    suite->tests[suite->size] = test;
    suite->size++;
}


void set_formatter(Suite *suite, Formatter *formatter) {
    suite->formatter = formatter;
}


int run_suite(Suite *suite) {
    suite->formatter->report_start(suite);

    for (Test *test = suite->tests; test->is_active == true; test = test+1) {
	test->test_function(test);
    }

    suite->formatter->summary(suite);

    return suite->number_of_failed_tests > 0;
}


Suite *make_suite(char *suite_name) {
    Suite *suite = calloc(1, sizeof(Suite));
    suite->formatter = make_dot_formatter();
    suite->name = suite_name;

    for (int i = 0; i < MAX_SUITE_SIZE; i++) {
        Test test;
	test.is_active = false;
	suite->tests[i] = test;
    }

    return suite;
}


void cexpect_start(Suite *suite) {
    exit(run_suite(suite));
}
