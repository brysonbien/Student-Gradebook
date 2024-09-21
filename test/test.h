#ifndef TEST_H
#define TEST_H


// Include all the headers needed for unit tests
//   * #define needed for getline function
//   * signal.h to catch SIGSEGV
//   * check.h is the unit testing library
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <check.h>

#include <sys/types.h>
#include <unistd.h>

#include "../gradebook.h"

// Useful macro to convert a bare word to a string
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// Useful macro of taking the size of an array
#define ARR_SIZE(xs) (sizeof(xs) / sizeof((xs)[0]))
#define ERR_BOUND(num1, num2) ((num1) - (num2) < 0.05 && (num1) - (num2) > -0.05)

// Test case strings
// Return the input and the output
#define TEST_MSG(in, exp) "Input: " #in ", Expected Result: " #exp
#define TEST_CMP(in, exp, act) "Input: " #in ", Expected: " #exp ", Actual: " #act


void init_gradebook_entries(struct GradebookEntry *entries);
void init_gradebook(struct Gradebook *gradebook);
void compare_gradebook_entires(struct GradebookEntry solution, struct GradebookEntry student, char *student_function_name, int i);
void compare_gradebooks(struct Gradebook *solution, struct Gradebook *student, char *student_function_name);
int s_add_student(struct Gradebook *g, char *name, int gtid, int year, char *major);
int s_calculate_course_average(struct Gradebook *g);
int s_calculate_average(struct Gradebook *g, struct GradebookEntry *entry);
int s_top_five_gtid(struct Gradebook *g, int *gtids);
int s_search_student(struct Gradebook *g, char *name);
int s_sort_name(struct Gradebook *g);
int s_sort_averages(struct Gradebook *g);
int s_update_grade(struct Gradebook *g, char *name, enum Assignment assignment_type, double new_grade);
int s_add_student_with_grades(struct Gradebook *g, char *name, int gtid, int year, char *major, double *grades);
int s_withdraw_student(struct Gradebook *g, char *name);
int s_print_gradebook(struct Gradebook *g);

/**
 * @brief Create test case and add it to suite
 *
 * @note setup/teardown fixture functions are run before and after each unit
 * test inside the address space of the test
 * @note `TCase *tc = tcase_create("func")`: Creates test case to be added to
 * the suite
 *
 * @param suite Create suite variable in some function and pass it in here
 * @param setup_fixture Setup function
 * @param teardown_fixture Teardown function : NULL if none
 * @param func Name of test being added to the test case
 */
#define tcase_add(suite, setup_fixture, teardown_fixture, func) { \
    TCase *tc = tcase_create(STRINGIFY(func)); \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func); \
    suite_add_tcase(suite, tc); \
}


/* TEST SUITES */
extern Suite *gradebook_suite(void);

#endif