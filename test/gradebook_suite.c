#include "test.h"

extern struct Gradebook gradebook;
struct Gradebook test_gradebook;

/* HELPER FUNCTIONS */

/********************************************************************************/
/********************* Modify Grade Book test ****************************/
/********************************************************************************/

// int add_student(char *name, int gtid, int year, char *major);
START_TEST(TEST_add_students) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  gradebook.entries[0].average = 37.4;
  for (int i = 0; i < num_students; i++) {
    int expected = s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    int actual = add_student(names[i], gtids[i], years[i], majors[i]);

    sprintf(student_function_name, "add_student(%s, %d, %d, %s)", names[i], gtids[i], years[i], majors[i]);

    ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

    compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  }

} END_TEST

START_TEST(TEST_add_students_invalid_major) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"AB", "AC", "DD", "CCS", "CEE"};

  char student_function_name[400];

  for (int i = 0; i < num_students; i++) {
    int expected = s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    int actual = add_student(names[i], gtids[i], years[i], majors[i]);

    sprintf(student_function_name, "add_student(%s, %d, %d, %s)", names[i], gtids[i], years[i], majors[i]);

    ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

    compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  }

} END_TEST

START_TEST(TEST_add_students_gradebook_full) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = MAX_ENTRIES;

  char *names[] = {"Max0", "Max1", "Max2", "Max3", "Max4", 
  "Max5", "Max6", "Max7", "Max8", "Max9", "Max10", "Max11", 
  "Max12", "Max13", "Max14", "Max15", "Max16", "Max17", "Max18", 
  "Max19", "Max20", "Max21", "Max22", "Max23", "Max24", "Max25", 
  "Max26", "Max27", "Max28", "Max29", "Max30", "Max31", "Max32", 
  "Max33", "Max34", "Max35", "Max36", "Max37", "Max38", "Max39", 
  "Max40", "Max41", "Max42", "Max43", "Max44", "Max45", "Max46", 
  "Max47", "Max48", "Max49", "Max50", "Max51", "Max52", "Max53", 
  "Max54", "Max55", "Max56", "Max57", "Max58", "Max59", "Max60", 
  "Max61", "Max62", "Max63", "Max64", "Max65", "Max66", "Max67", 
  "Max68", "Max69", "Max70", "Max71", "Max72", "Max73", "Max74", 
  "Max75", "Max76", "Max77", "Max78", "Max79", "Max80", "Max81", 
  "Max82", "Max83", "Max84", "Max85", "Max86", "Max87", "Max88", 
  "Max89", "Max90", "Max91", "Max92", "Max93", "Max94", "Max95", 
  "Max96", "Max97", "Max98", "Max99"};

  int gtid = 903000000;
  int year = 4;
  char *major = "CS";

  char student_function_name[400];

  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtid + i, year, major);
    add_student(names[i], gtid + i, year, major);
  }

  // add extra student

  int expected = s_add_student(&test_gradebook, "Max100", gtid + num_students, year, major);
  int actual = add_student("Max100", gtid + num_students, year, major);

  sprintf(student_function_name, "add_student(%s, %d, %d, %s)", "Max100", gtid + num_students, year, major);

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

  // compare_gradebooks(&test_gradebook, &gradebook, student_function_name);

} END_TEST

START_TEST(TEST_add_students_null_pointer) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  // int num_students = 4;
  // char *names[] = {"John", "Jane", "Jack", "Jill", ""};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  // char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  int expected = s_add_student(&test_gradebook, 0, gtids[0], years[0], 0);
  int actual = add_student(0, gtids[0], years[0], 0);

  sprintf(student_function_name, "add_student(%s, %d, %d, %s)", "NULL", gtids[0], years[0], "NULL");

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

  // compare_gradebooks(&test_gradebook, &gradebook, student_function_name);

} END_TEST

START_TEST(TEST_add_students_name_too_long) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 4;
  char *names[] = {"Max", "MaxMaxMaxMaxMaxMax",  "MaxMaxMaxMaxMaxMaxM", "MaxMaxMaxMaxMaxMaxMaxMaxMaxMaxMaxMax"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  for (int i = 0; i < num_students; i++) {
    int expected = s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    int actual = add_student(names[i], gtids[i], years[i], majors[i]);

    sprintf(student_function_name, "add_student(%s, %d, %d, %s)", names[i], gtids[i], years[i], majors[i]);

    ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

    compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  }

} END_TEST

START_TEST(TEST_add_students_duplicate) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "John"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000111};
  int years[] = {1, 2, 3, 4, 1};
  char *majors[] = {"CS", "CE", "EE", "CS", "CS"};

  char student_function_name[400];

  for (int i = 0; i < num_students; i++) {
    int expected = s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    int actual = add_student(names[i], gtids[i], years[i], majors[i]);

    sprintf(student_function_name, "add_student(%s, %d, %d, %s)", names[i], gtids[i], years[i], majors[i]);

    ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

    compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  }

} END_TEST


// update grade


START_TEST(TEST_update_grade) {
  
    init_gradebook(&test_gradebook);
    init_gradebook(&gradebook);
  
    // Add students to gradebook
    int num_students = 5;
    char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
    int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
    int years[] = {1, 2, 3, 4, 5};
    char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

    char student_function_name[400];
  
    // add students
    for (int i = 0; i < num_students; i++) {
      s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
      s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
    }
  
    // Update grades
    double grades[][NUM_ASSIGNMENTS] = {
      {100.0, 100.0, 100.0, 100.0, 100.0},
      {90.0, 90.0, 90.0, 90.0, 90.0},
      {80.0, 80.0, 80.0, 80.0, 80.0},
      {70.0, 70.0, 70.0, 70.0, 70.0},
      {60.0, 60.0, 60.0, 60.0, 60.0}
    };
  
    for (int i = 0; i < num_students; i++) {
      for (int j = 0; j < NUM_ASSIGNMENTS; j++) {

        sprintf(student_function_name, "update_grade(%s, %d, %f)", names[i], j, grades[i][j]);

        int expected = s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
        int actual = update_grade(names[i], j, grades[i][j]);
  
        ck_assert_msg(expected == actual, "update_grade() - Expected return value: %d, Actual return value: %d\n", expected, actual);
  
      }
      compare_gradebooks(&test_gradebook, &gradebook, "update_grade()");
    }
  
} END_TEST

START_TEST(TEST_update_grade_student_not_found) {
  
    init_gradebook(&test_gradebook);
    init_gradebook(&gradebook);
  
    // Add students to gradebook
    int num_students = 5;
    char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
    int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
    int years[] = {1, 2, 3, 4, 5};
    char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

    char student_function_name[400];
  
    // add students
    for (int i = 0; i < num_students; i++) {
      s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
      s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
    }
  
    // Update grades
    double grades[][NUM_ASSIGNMENTS] = {
      {100.0, 100.0, 100.0, 100.0, 100.0},
      {90.0, 90.0, 90.0, 90.0, 90.0},
      {80.0, 80.0, 80.0, 80.0, 80.0},
      {70.0, 70.0, 70.0, 70.0, 70.0},
      {60.0, 60.0, 60.0, 60.0, 60.0}
    };

    char *names2[] = {"Max", "Max", "Max", "Max", "Max"};
  
    for (int i = 0; i < num_students; i++) {
      for (int j = 0; j < NUM_ASSIGNMENTS; j++) {

        sprintf(student_function_name, "update_grade(%s, %d, %f)", names2[i], j, grades[i][j]);

        int expected = s_update_grade(&test_gradebook, names2[i], j, grades[i][j]);
        int actual = update_grade(names2[i], j, grades[i][j]);
  
        ck_assert_msg(expected == actual, "update_grade() - Expected return value: %d, Actual return value: %d\n", expected, actual);
  
      }
      compare_gradebooks(&test_gradebook, &gradebook, "update_grade()");
    }
  
} END_TEST



// add student with grades



START_TEST(TEST_add_student_with_grades) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  double grades[][NUM_ASSIGNMENTS] = {
      {100.0, 100.0, 100.0, 100.0, 100.0},
      {90.0, 90.0, 90.0, 90.0, 90.0},
      {80.0, 80.0, 80.0, 80.0, 80.0},
      {70.0, 70.0, 70.0, 70.0, 70.0},
      {60.0, 60.0, 60.0, 60.0, 60.0}
    };

  char student_function_name[400];

  for (int i = 0; i < num_students; i++) {
    int expected = s_add_student_with_grades(&test_gradebook, names[i], gtids[i], years[i], majors[i], grades[i]);
    int actual = add_student_with_grades(names[i], gtids[i], years[i], majors[i], grades[i]);

    sprintf(student_function_name, "add_student_with_grades(%s, %d, %d, %s, [%f, %f, %f, %f, %f])", names[i], gtids[i], years[i], majors[i], grades[i][0], grades[i][1], grades[i][2], grades[i][3], grades[i][4]);

    ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

    compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  }

} END_TEST

START_TEST(TEST_add_student_with_grades_invalid_major) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"AB", "AC", "DD", "CCS", "CEE"};

  double grades[][NUM_ASSIGNMENTS] = {
      {100.0, 100.0, 100.0, 100.0, 100.0},
      {90.0, 90.0, 90.0, 90.0, 90.0},
      {80.0, 80.0, 80.0, 80.0, 80.0},
      {70.0, 70.0, 70.0, 70.0, 70.0},
      {60.0, 60.0, 60.0, 60.0, 60.0}
    };

  char student_function_name[400];

  for (int i = 0; i < num_students; i++) {
    int expected = s_add_student_with_grades(&test_gradebook, names[i], gtids[i], years[i], majors[i], grades[i]);
    int actual = add_student_with_grades(names[i], gtids[i], years[i], majors[i], grades[i]);

    sprintf(student_function_name, "add_student_with_grades(%s, %d, %d, %s, [%f, %f, %f, %f, %f])", names[i], gtids[i], years[i], majors[i], grades[i][0], grades[i][1], grades[i][2], grades[i][3], grades[i][4]);

    ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

    compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  }

} END_TEST

START_TEST(TEST_add_student_with_grades_gradebook_full) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = MAX_ENTRIES;

  char *names[] = {"Max0", "Max1", "Max2", "Max3", "Max4", 
  "Max5", "Max6", "Max7", "Max8", "Max9", "Max10", "Max11", 
  "Max12", "Max13", "Max14", "Max15", "Max16", "Max17", "Max18", 
  "Max19", "Max20", "Max21", "Max22", "Max23", "Max24", "Max25", 
  "Max26", "Max27", "Max28", "Max29", "Max30", "Max31", "Max32", 
  "Max33", "Max34", "Max35", "Max36", "Max37", "Max38", "Max39", 
  "Max40", "Max41", "Max42", "Max43", "Max44", "Max45", "Max46", 
  "Max47", "Max48", "Max49", "Max50", "Max51", "Max52", "Max53", 
  "Max54", "Max55", "Max56", "Max57", "Max58", "Max59", "Max60", 
  "Max61", "Max62", "Max63", "Max64", "Max65", "Max66", "Max67", 
  "Max68", "Max69", "Max70", "Max71", "Max72", "Max73", "Max74", 
  "Max75", "Max76", "Max77", "Max78", "Max79", "Max80", "Max81", 
  "Max82", "Max83", "Max84", "Max85", "Max86", "Max87", "Max88", 
  "Max89", "Max90", "Max91", "Max92", "Max93", "Max94", "Max95", 
  "Max96", "Max97", "Max98", "Max99"};

  int gtid = 903000000;
  int year = 4;
  char *major = "CS";

  double grades[][NUM_ASSIGNMENTS] = {
      {100.0, 100.0, 100.0, 100.0, 100.0},
      {90.0, 90.0, 90.0, 90.0, 90.0},
      {80.0, 80.0, 80.0, 80.0, 80.0},
      {70.0, 70.0, 70.0, 70.0, 70.0},
      {60.0, 60.0, 60.0, 60.0, 60.0}
    };

  char student_function_name[400];

  for (int i = 0; i < num_students; i++) {
    s_add_student_with_grades(&test_gradebook, names[i], gtid + i, year, major, grades[0]);
    add_student_with_grades(names[i], gtid + i, year, major, grades[0]);
  }

  // add extra student

  int expected = s_add_student_with_grades(&test_gradebook, "Max100", gtid + num_students, year, major, grades[0]);
  int actual = add_student_with_grades("Max100", gtid + num_students, year, major, grades[0]);

  sprintf(student_function_name, "add_student_with_grades(%s, %d, %d, %s, [%f, %f, %f, %f, %f])", "Max100", gtid + num_students, year, major, grades[0][0], grades[0][1], grades[0][2], grades[0][3], grades[0][4]);

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

  // compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  
} END_TEST

START_TEST(TEST_add_student_with_grades_null_pointer) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  // int num_students = 5;
  // char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  // char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  // double grades[][NUM_ASSIGNMENTS] = {
  //     {100.0, 100.0, 100.0, 100.0, 100.0},
  //     {90.0, 90.0, 90.0, 90.0, 90.0},
  //     {80.0, 80.0, 80.0, 80.0, 80.0},
  //     {70.0, 70.0, 70.0, 70.0, 70.0},
  //     {60.0, 60.0, 60.0, 60.0, 60.0}
  //   };

  char student_function_name[400];

  int expected = s_add_student_with_grades(&test_gradebook, 0, gtids[0], years[0], 0, 0);
  int actual = add_student_with_grades(0, gtids[0], years[0], 0, 0);

  sprintf(student_function_name, "add_student_with_grades(%s, %d, %d, %s, %s)", "NULL", gtids[0], years[0], "NULL", "NULL");

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

  // compare_gradebooks(&test_gradebook, &gradebook, student_function_name);

} END_TEST

START_TEST(TEST_add_student_with_grades_name_too_long) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 4;
  char *names[] = {"Max", "MaxMaxMaxMaxMaxMax", "MaxMaxMaxMaxMaxMaxM", "MaxMaxMaxMaxMaxMaxMaxMaxMaxMaxMaxMax", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  double grades[][NUM_ASSIGNMENTS] = {
      {100.0, 100.0, 100.0, 100.0, 100.0},
      {90.0, 90.0, 90.0, 90.0, 90.0},
      {80.0, 80.0, 80.0, 80.0, 80.0},
      {70.0, 70.0, 70.0, 70.0, 70.0},
      {60.0, 60.0, 60.0, 60.0, 60.0}
    };

  char student_function_name[400];

  for (int i = 0; i < num_students; i++) {
    int expected = s_add_student_with_grades(&test_gradebook, names[i], gtids[i], years[i], majors[i], grades[i]);
    int actual = add_student_with_grades(names[i], gtids[i], years[i], majors[i], grades[i]);

    sprintf(student_function_name, "add_student_with_grades(%s, %d, %d, %s, [%f, %f, %f, %f, %f])", names[i], gtids[i], years[i], majors[i], grades[i][0], grades[i][1], grades[i][2], grades[i][3], grades[i][4]);

    ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

    compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  }

} END_TEST



// int withdraw_student(char *name);



START_TEST(TEST_withdraw_student) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

  // withdraw students
  for (int i = 0; i < num_students - 1; i++) {
    int expected = s_withdraw_student(&test_gradebook, names[i]);
    int actual = withdraw_student(names[i]);

    sprintf(student_function_name, "withdraw_student(%s)", names[i]);

    ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

    compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  }

} END_TEST

START_TEST(TEST_withdraw_student_student_not_found) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

  // withdraw students
  int expected = s_withdraw_student(&test_gradebook, "MAX");
  int actual = withdraw_student("MAX");

  sprintf(student_function_name, "withdraw_student(%s)", "MAX");

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

  compare_gradebooks(&test_gradebook, &gradebook, student_function_name);

} END_TEST

START_TEST(TEST_withdraw_student_null) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

  // withdraw students
  int expected = s_withdraw_student(&test_gradebook, 0);
  int actual = withdraw_student(0);

  sprintf(student_function_name, "withdraw_student(%s)", "NULL");

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

  compare_gradebooks(&test_gradebook, &gradebook, student_function_name);

} END_TEST



// int search_student(char *name);
START_TEST(TEST_search_student) {

	init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	// search for students
	for (int i = 0; i < num_students; i++) {
		int expected = s_search_student(&test_gradebook, names[i]);
		int actual = search_student(names[i]);

		sprintf(student_function_name, "search_student(%s)", names[i]);

		ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);
	}

} END_TEST

START_TEST(TEST_search_student_student_not_found) {

	init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	// search for students
  int expected = s_search_student(&test_gradebook, "MAX");
  int actual = search_student("MAX");

  sprintf(student_function_name, "search_student(%s)", "MAX");

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

} END_TEST

START_TEST(TEST_search_student_student_null) {

	init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	// search for students
  int expected = s_search_student(&test_gradebook, 0);
  int actual = search_student(0);

  sprintf(student_function_name, "search_student(%s)", "NULL");

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

} END_TEST


/********************************************************************************/
/********************* Calculate Average Test ****************************/
/********************************************************************************/

// int calculate_average(struct GradebookEntry *entry);
START_TEST(TEST_calculate_average) {

	init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	// calculate averages

  for (int i = 0; i < num_students; i++) {

    int expected = s_calculate_average(&test_gradebook, &test_gradebook.entries[i]);
    int actual = calculate_average(&gradebook.entries[i]);

    sprintf(student_function_name, "calculate_average(%s)", "NULL");

    ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

    compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
  
  }

} END_TEST

START_TEST(TEST_calculate_average_null) {
  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	// calculate averages

  int expected = s_calculate_average(&test_gradebook, 0);
  int actual = calculate_average(0);

  sprintf(student_function_name, "calculate_average(%s)", "NULL");

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

  compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
	
} END_TEST



// double calculate_course_average();
START_TEST(TEST_calculate_course_average) {

	init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  
  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	for (int i = 0; i < num_students; i++) {
		s_calculate_average(&test_gradebook, &test_gradebook.entries[i]);
		s_calculate_average(&gradebook, &gradebook.entries[i]);
	}

	// calculate course averages

	sprintf(student_function_name, "calculate_course_average()");

	double expected = s_calculate_course_average(&test_gradebook);
	double actual = calculate_course_average();

	ck_assert_msg(expected == actual, "%s - Expected return value: %f, Actual return value: %f\n", student_function_name, expected, actual);
	compare_gradebooks(&test_gradebook, &gradebook, student_function_name);
	
} END_TEST

START_TEST(TEST_calculate_course_average_no_students) {

  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  char student_function_name[400];

	// calculate course averages

	sprintf(student_function_name, "calculate_course_average()");
  gradebook.assignment_averages[2] = 32.7;
  gradebook.assignment_averages[4] = 39.3;
  gradebook.course_average = 35.8;
	double expected = s_calculate_course_average(&test_gradebook);
	double actual = calculate_course_average();

	ck_assert_msg(expected == actual, "%s - Expected return value: %f, Actual return value: %f\n", student_function_name, expected, actual);
	
} END_TEST



// int top_five_gtid(int *gtids);
START_TEST(TEST_top_five_gtid) {

	init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	for (int i = 0; i < num_students; i++) {
		s_calculate_average(&test_gradebook, &test_gradebook.entries[i]);
		s_calculate_average(&gradebook, &gradebook.entries[i]);
	}

	// calculate course averages
	int expected_gtid[5];
	int actual_gtid[5];

	sprintf(student_function_name, "top_five_gtid()");

	int expected = s_top_five_gtid(&test_gradebook, expected_gtid);
	int actual = top_five_gtid(actual_gtid);

	ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

	for (int i = 0; i < 5; i++) {
		ck_assert_msg(expected_gtid[i] == actual_gtid[i], "%s - Expected GTID at index %d: %d, Actual GTID at index %d: %d\n", student_function_name, i, expected_gtid[i], i, actual_gtid[i]);
	}


} END_TEST


START_TEST(TEST_top_five_gtid_few_entries) {

	init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 3;
  char *names[] = {"John", "Jane", "Jack"};
  int gtids[] = {903000111, 903000222, 903000333};
  int years[] = {1, 2, 3};
  char *majors[] = {"CS", "CE", "EE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {80.0, 80.0, 80.0, 80.0, 80.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	for (int i = 0; i < num_students; i++) {
		s_calculate_average(&test_gradebook, &test_gradebook.entries[i]);
		s_calculate_average(&gradebook, &gradebook.entries[i]);
	}

	// calculate course averages
	int expected_gtid[5];
	int actual_gtid[5];

	sprintf(student_function_name, "top_five_gtid()");

	int expected = s_top_five_gtid(&test_gradebook, expected_gtid);
	int actual = top_five_gtid(actual_gtid);

	ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

	for (int i = 0; i < 5; i++) {
		ck_assert_msg(expected_gtid[i] == actual_gtid[i], "%s - Expected GTID at index %d: %d, Actual GTID at index %d: %d\n", student_function_name, i, expected_gtid[i], i, actual_gtid[i]);
	}


} END_TEST


START_TEST(TEST_top_five_gtid_gradebook_empty) {
  
  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  char student_function_name[400];

	// calculate course averages
	int expected_gtid[5];
	int actual_gtid[5];

	sprintf(student_function_name, "top_five_gtid()");

	int expected = s_top_five_gtid(&test_gradebook, expected_gtid);
	int actual = top_five_gtid(actual_gtid);

	ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

} END_TEST


/********************************************************************************/
/********************* Sorting by X Test ****************************/
/********************************************************************************/

// Sorting Methods
// void sort_name();
START_TEST(TEST_sort_name) {

	init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	for (int i = 0; i < num_students; i++) {
		s_calculate_average(&test_gradebook, &test_gradebook.entries[i]);
		s_calculate_average(&gradebook, &gradebook.entries[i]);
	}

	s_calculate_course_average(&test_gradebook);
	s_calculate_course_average(&gradebook);

	// sort by name
	sprintf(student_function_name, "sort_name()");

	int expected = s_sort_name(&test_gradebook);
	int actual = sort_name();

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

	compare_gradebooks(&test_gradebook, &gradebook, student_function_name);

} END_TEST

START_TEST(TEST_sort_name_empty) {
  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  char student_function_name[400];

	// sort by name
	sprintf(student_function_name, "sort_name()");

	int expected = s_sort_name(&test_gradebook);
	int actual = sort_name();

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

} END_TEST


// void sort_averages();
START_TEST(TEST_sort_averages) {

	init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 5;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  char student_function_name[400];

  // add students
  for (int i = 0; i < num_students; i++) {
    s_add_student(&test_gradebook, names[i], gtids[i], years[i], majors[i]);
    s_add_student(&gradebook, names[i], gtids[i], years[i], majors[i]);
  }

  // add grades
  double grades[][NUM_ASSIGNMENTS] = {
    {70.0, 70.0, 70.0, 70.0, 70.0},
    {90.0, 90.0, 90.0, 90.0, 90.0},
    {100.0, 100.0, 100.0, 100.0, 100.0},
    {80.0, 80.0, 80.0, 80.0, 80.0},
    {60.0, 60.0, 60.0, 60.0, 60.0}
  };

  for (int i = 0; i < num_students; i++) {
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      s_update_grade(&test_gradebook, names[i], j, grades[i][j]);
      s_update_grade(&gradebook, names[i], j, grades[i][j]);
    }
  }

	for (int i = 0; i < num_students; i++) {
		s_calculate_average(&test_gradebook, &test_gradebook.entries[i]);
		s_calculate_average(&gradebook, &gradebook.entries[i]);
	}

	s_calculate_course_average(&test_gradebook);
	s_calculate_course_average(&gradebook);

	// sort by name
	sprintf(student_function_name, "sort_name()");

	int expected = s_sort_averages(&test_gradebook);
	int actual = sort_averages();

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

	compare_gradebooks(&test_gradebook, &gradebook, student_function_name);

} END_TEST

START_TEST(TEST_sort_averages_empty) {
  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  char student_function_name[400];

	// sort by name
	sprintf(student_function_name, "sort_name()");

	int expected = s_sort_averages(&test_gradebook);
	int actual = sort_averages();

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

} END_TEST


/********************************************************************************/
/********************* Grade Book Print Test ****************************/
/********************************************************************************/

START_TEST(TEST_print_gradebook) {
  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  // Add students to gradebook
  int num_students = 4;
  char *names[] = {"John", "Jane", "Jack", "Jill", "James"};
  int gtids[] = {903000111, 903000222, 903000333, 903000444, 903000555};
  int years[] = {1, 2, 3, 4, 5};
  char *majors[] = {"CS", "CE", "EE", "CS", "CE"};

  double grades[][NUM_ASSIGNMENTS] = {
      {100.0, 100.0, 100.0, 100.0, 100.0},
      {90.0, 90.0, 90.0, 90.0, 90.0},
      {80.0, 80.0, 80.0, 80.0, 80.0},
      {70.0, 70.0, 70.0, 70.0, 70.0},
      {60.0, 60.0, 60.0, 60.0, 60.0}
    };

  char student_function_name[400];

  for (int i = 0; i < num_students; i++) {
    s_add_student_with_grades(&test_gradebook, names[i], gtids[i], years[i], majors[i], grades[i]);
    s_add_student_with_grades(&gradebook, names[i], gtids[i], years[i], majors[i], grades[i]);
  }

  sprintf(student_function_name, "print_gradebook()");

  // read from stdout

  FILE *original_stdout;
  char buffer[BUFSIZ];
  original_stdout = stdout;
  setbuf(stdout, buffer);
  int expected = s_print_gradebook(&test_gradebook);
  freopen(NULL, "w", original_stdout);

  char output_buffer[BUFSIZ];

  int i = 0;
  int j = 0;

  while (buffer[i]) {
    if ((buffer[i] == ' ') | (buffer[i] == '\n') | (buffer[i] == '|') | (buffer[i] == '-')) {
      i++;
      continue;
    }
    output_buffer[j] = buffer[i];
    j++;
    i++;
  }

  printf("%s\n", output_buffer);


  FILE *original_stdout_actual;
  char buffer_actual[BUFSIZ];
  original_stdout_actual = stdout;
  setbuf(stdout, buffer_actual);
  int actual = print_gradebook();
  freopen(NULL, "w", original_stdout_actual);

  char output_buffer_actual[BUFSIZ];

  i = 0;
  j = 0;

  while (buffer_actual[i]) {
    if ((buffer_actual[i] == ' ') | (buffer_actual[i] == '\n') | (buffer_actual[i] == '|') | (buffer[i] == '-')) {
      i++;
      continue;
    }
    output_buffer_actual[j] = buffer_actual[i];
    j++;
    i++;
  }

  printf("%s\n", output_buffer_actual);

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

  ck_assert_str_eq(output_buffer, output_buffer_actual);

} END_TEST

START_TEST(TEST_print_gradebook_empty) {
  init_gradebook(&test_gradebook);
  init_gradebook(&gradebook);

  char student_function_name[400];

	// sort by name
	sprintf(student_function_name, "print_gradebook()");

	int expected = s_print_gradebook(&test_gradebook);
	int actual = print_gradebook();

  ck_assert_msg(expected == actual, "%s - Expected return value: %d, Actual return value: %d\n", student_function_name, expected, actual);

} END_TEST


// Printing
// void print_gradebook();


/********************************************************************************/

Suite *gradebook_suite(void) {

  Suite *s = suite_create("part2-gradebook");
  tcase_add(s, NULL, NULL, TEST_add_students);
  tcase_add(s, NULL, NULL, TEST_add_students_invalid_major);
  tcase_add(s, NULL, NULL, TEST_add_students_gradebook_full);
  tcase_add(s, NULL, NULL, TEST_add_students_null_pointer);
  tcase_add(s, NULL, NULL, TEST_add_students_duplicate);
  tcase_add(s, NULL, NULL, TEST_add_students_name_too_long);


  tcase_add(s, NULL, NULL, TEST_update_grade);
  tcase_add(s, NULL, NULL, TEST_update_grade_student_not_found);

  tcase_add(s, NULL, NULL, TEST_add_student_with_grades);
  tcase_add(s, NULL, NULL, TEST_add_student_with_grades_invalid_major);
  tcase_add(s, NULL, NULL, TEST_add_student_with_grades_gradebook_full);
  tcase_add(s, NULL, NULL, TEST_add_student_with_grades_null_pointer);
  tcase_add(s, NULL, NULL, TEST_add_student_with_grades_name_too_long);


  tcase_add(s, NULL, NULL, TEST_withdraw_student);
  tcase_add(s, NULL, NULL, TEST_withdraw_student_student_not_found);
  tcase_add(s, NULL, NULL, TEST_withdraw_student_null);

  tcase_add(s, NULL, NULL, TEST_search_student);
  tcase_add(s, NULL, NULL, TEST_search_student_student_not_found);
  tcase_add(s, NULL, NULL, TEST_search_student_student_null);

  tcase_add(s, NULL, NULL, TEST_calculate_average);
  tcase_add(s, NULL, NULL, TEST_calculate_average_null);


  tcase_add(s, NULL, NULL, TEST_calculate_course_average);
  tcase_add(s, NULL, NULL, TEST_calculate_course_average_no_students);

  
  tcase_add(s, NULL, NULL, TEST_top_five_gtid);
  tcase_add(s, NULL, NULL, TEST_top_five_gtid_few_entries);
  tcase_add(s, NULL, NULL, TEST_top_five_gtid_gradebook_empty);

  tcase_add(s, NULL, NULL, TEST_sort_name);
  tcase_add(s, NULL, NULL, TEST_sort_name_empty);

  tcase_add(s, NULL, NULL, TEST_sort_averages);
  tcase_add(s, NULL, NULL, TEST_sort_averages_empty);

  tcase_add(s, NULL, NULL, TEST_print_gradebook);
  tcase_add(s, NULL, NULL, TEST_print_gradebook_empty);

  return s;
}