#ifndef CEXPECT_H
#define CEXPECT_H


#include "cexpect_formatter.h"
#include "cexpect_matchers.h"
#include "cexpect_suite_types.h"


/*
 * for example:
 * 
 *   expect(test, true, is_true()); # passes
 *   expect(test, false, is_false()); # passes
 *   expect(test, true, is_false()); # fails
 *   
 */
extern void expect(Test *test, void *actual_value, Matcher *matcher);


/*
 * create a new suite instance:
 * 
 */
extern Suite *create_suite(char *suite_name);


/*
 * Add tests to a suite:
 * 
 */
#define add_test(suite, test_function) add_test_to_suite(suite, test_function, __LINE__, __FILE__)

extern void add_test_to_suite(Suite *suite, test_function_type test_function, int line_number, char *file_name);



/*
 * Add a function to run before each test:
 * 
 */
extern void add_before_each(Suite *suite, void (*before_each_function)());


/*
 * Add a function to run before each test:
 * 
 */
extern void add_after_each(Suite *suite, void (*after_each_function)());


/*
 * change formatter the suite uses:
 * 
 *   default = dot_formatter
 *   
 */
extern void set_formatter(Suite *suite, Formatter *formatter);


/*
 * run suite without exiting:
 * 
 */
extern int run_suite(Suite *suite);


/*
 * run suite and exit with appropriate status code:
 * 
 */
extern void start_cexpect(Suite *suite);


/* 
 * exposed for tests 
 */
extern int number_of_tests(Suite *suite);
extern int number_of_failed_tests(Suite *suite);
extern int number_of_passing_tests(Suite *suite);


#endif // CEXPECT_H