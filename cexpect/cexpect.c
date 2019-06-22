#include <stdlib.h>
#include <stdio.h>


#include "cexpect.h"
#include "cexpect_dot_formatter.h"


#include "internal/list.h"
#include "internal/test.h"
#include "internal/suite.h"
#include "internal/failed_test.h"
#include "internal/matcher.h"
#include "internal/match_result.h"


static void perform_format_summary(Formatter *formatter, Suite *suite) {
	int _number_of_failed_tests = number_of_failed_tests(suite);
	FailedTest failed_tests[_number_of_failed_tests];

	int i = 0;

	for(Cexpect_ListItem *list_item = list_first(get_failed_tests(suite)); list_item; list_item = list_next(list_item)) {
		failed_tests[i] = *(FailedTest *)list_value(list_item);
		i++;
	}

	do_format_summary(
		formatter,
		number_of_tests(suite),
		number_of_passing_tests(suite),
		_number_of_failed_tests,
		number_of_pending_tests(suite),
		failed_tests);
}


Suite *create_suite(char *suite_name) {
	return make_suite(suite_name, make_dot_formatter(&printf));
}


void set_formatter(Suite *suite, Formatter *formatter) {
	set_formatter_for_suite(suite, formatter);
}


void add_test(Suite *suite, test_function_type test_function) {
	add_to_list(
		get_tests(suite), 
		make_test(suite, test_function));
}


void add_before_each(Suite *suite, void (*before_each_function)()) {
	add_before_each_to_suite(suite, before_each_function);
}


void add_after_each(Suite *suite, void (*after_each_function)()) {
	add_after_each_to_suite(suite, after_each_function);
}


int run_suite(Suite *suite) {
	Formatter *formatter = get_formatter(suite);
	do_format_start(formatter, get_suite_name(suite));

	for (Cexpect_ListItem *item = list_first(get_tests(suite)); item; item = list_next(item)) {
		Test *test = list_value(item);
		before_each(suite);
		perform_test(test);
		after_each(suite);
	}

	perform_format_summary(formatter, suite);

	return number_of_failed_tests(suite) > 0;
}


/*
 * base expectation:
 * 
 */
void make_expectation(
	Test *test, 
	void *actual_value, 
	Matcher *matcher, 
	const char *test_name, 
	int line_number, 
	char *file_name) {
	
	MatchResult *result = perform_match(matcher, actual_value);
	
	if (is_match(result)) {
		pass_test(test);
	} else {
		fail_test(test,
		          expected_message(result),
		          actual_message(result),
		          (char *)test_name,
		          line_number,
		          file_name);
	}
}


void start_cexpect(Suite *suite) {
	int status_code = run_suite(suite);

	exit(status_code);
}

