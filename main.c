/* DO NOT REMOVE INCLUDES - Do NOT add your own */
#include "gradebook.h"

int main(void) {
  // initialize gradebook weights
  gradebook.weights[HW1] = 0.25;
  gradebook.weights[HW2] = 0.25;
  gradebook.weights[HW3] = 0.25;
  gradebook.weights[P1] = 0.125;
  gradebook.weights[P2] = 0.125;

  // Add your own test cases here to test your functions :)
  char *student_name = "John Doe";
  int gtid = 903123456;
  int year = 2025;
  char *major = "CS";

  // Add a new student
  int add_result = add_student(student_name, gtid, year, major);
  printf(
      "Adding Student - Expected Return Value: %d, Actual Return Value: %d\n",
      SUCCESS, add_result);

  // Verify the student was added by searching for them
  int search_add_result = search_student(student_name);
  printf("Searching Added Student - Expected: Index >= 0, Actual: %d\n",
         search_add_result);

  if (search_add_result == ERROR) {
    printf("Student not found after add. Exiting test.\n");
    return ERROR;
  }
  return SUCCESS;
}
