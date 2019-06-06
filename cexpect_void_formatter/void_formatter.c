#include "cexpect_internal.h"


/* 
 * Void formatter 
 */
static void report_failing_test_with_void() {
}


static void report_successful_test_with_void() {
}


static void report_summary_for_void(
	int number_of_tests,
	int number_of_passing_tests,
	int number_of_failed_tests,
	List *failed_tests
) {
}


static void report_start_for_void(char *suite_name) {
}


Formatter *make_void_formatter() {
	return make_formatter(
		report_failing_test_with_void,
		report_successful_test_with_void,
		report_summary_for_void,
		report_start_for_void);
}