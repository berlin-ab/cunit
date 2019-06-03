# cexpect

A testing framework for C inspired by hamcrest

## Usage

```
#include "cexpect.h"
#include "cexpect_cmatchers.h"


void some_failing_test(Test *test) {
    expect(test, 1, is_int_equal_to(2));
}


void some_passing_test(Test *test) {
    expect(test, 1, is_int_equal_to(1));
}


int main(int argc, char *args[]) {
    Suite *suite = make_suite();
    add_test(suite, some_failing_test);
    add_test(suite, some_passing_test);
    cexpect_start(suite);
}
```


## Matchers

* is_int_equal_to
* is_true
* is_false


## Example output

```
make -s readme_test
Running suite: Readme suite
.F

Summary:

Ran 2 test(s).

1 passed, 1 failed



Makefile:48: recipe for target 'readme_test' failed
make: *** [readme_test] Error 1```
```

## Design goals


* xunit-like framework similar to hamcrest
* Extensible matchers
* Extensible formatting
* Code coverage reporting enabled.
* Self-tested. No additional frameworks.
* No magic. No #include of c files, or use of macros for assertions.
* Should be useable in isolated unit tests and also in integrated system tests.
* Report only one passing test per test function


## Planned improvements

* individual test failure detailed reporting in summary
* dynamic test list (currently hard coded array)
* test-anything-protocol output formatter
* lcov/gcov
* make Makefile more idiomatic
* matchers for all standard C primative data types


## Testing

```
make -s test
```