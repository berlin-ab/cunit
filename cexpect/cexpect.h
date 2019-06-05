#ifndef CEXPECT_H
#define CEXPECT_H

typedef struct FormatterData Formatter;
typedef struct SuiteData Suite;
typedef struct TestData Test;
typedef struct FailedTestData FailedTest;


// Tests
#define add_test(suite, test_function) add_test_to_suite(suite, test_function, __LINE__, __FILE__)
typedef void (*test_function_type)(Test *test);
extern void add_test_to_suite(Suite *suite, test_function_type test_function, int line_number, char *file_name);
extern void pass_test(Test *test);
extern void fail_test(Test *test, char *expected_value, char *actual_value);

// Suites
extern int run_suite(Suite *suite);
extern Suite *make_suite(char *suite_name);
extern int number_of_tests(Suite *suite);
extern int number_of_failed_tests(Suite *suite);
extern int number_of_passing_tests(Suite *suite);
extern char *get_suite_name(Suite *suite);
extern void set_formatter(Suite *suite, Formatter *formatter);


// Failed tests
extern FailedTest *get_failed_test(Suite *suite, int test_number);
extern char *get_failing_test_expected_value(FailedTest *failed_test);
extern char *get_failing_test_actual_value(FailedTest *failed_test);
extern int get_failing_test_line_number(FailedTest *failed_test);
extern char *get_failing_test_file_name(FailedTest *failed_test);


// Formatters
typedef void (*format_failure)(Formatter *formatter, Test *test);
typedef void (*format_success)(Formatter *formatter, Test *test);
typedef void (*format_summary)(Formatter *formatter, Suite *suite);
typedef void (*format_start)(Formatter *formatter, Suite *suite);

Formatter *make_formatter(
	format_failure failure,
	format_success success,
	format_summary summary,
	format_start start,
	void *extra);


void *get_formatter_extra(Formatter *formatter);
void format_failing_test(Formatter *formatter, Test *test);
void format_successful_test(Formatter *formatter, Test *test);
void format_suite_summary(Formatter *formatter, Suite *suite);
void format_suite_start(Formatter *formatter, Suite *suite);


// Int matchers
extern void expect_equal(Test *test, int expected_value, int actual_value);


// Runner
extern void start_cexpect(Suite *suite);

#endif //CEXPECT_H
