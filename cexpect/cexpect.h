typedef struct FormatterData Formatter;
typedef struct SuiteData Suite;
typedef struct TestData Test;

// Tests
#define add_test(suite, test_function) add_test_to_suite(suite, test_function, __LINE__, __FILE__)
extern void add_test_to_suite(Suite *suite, void (*test_function)(Test *test), int line_number, char *file_name);
extern void pass_test(Test *test);
extern void fail_test(Test *test, char *expected_value, char *actual_value);

// Suites
extern int run_suite(Suite *suite);
extern Suite *make_suite(char *suite_name);
extern int number_of_failed_tests(Suite *suite);
extern int number_of_passing_tests(Suite *suite);
extern void set_formatter(Suite *suite, Formatter *formatter);


// Formatters
extern Formatter *make_void_formatter();
extern Formatter *make_dot_formatter();


// Int matchers
extern void expect_equal(Test *test, int expected_value, int actual_value);


// Runner
extern void start_cexpect(Suite *suite);
