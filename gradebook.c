#include "gradebook.h"
#include <string.h>

/*
 * Name: Bryson Bien
 */

struct Gradebook gradebook;

/**
 * Adds a new student to the gradebook and sets all the student's grades to 0.
 *
 * Updates assignment_averages and course_average based on the new grades.
 *
 * @param name The name of the student.
 * @param gtid The GTID of the student.
 * @param year The year of the student.
 * @param major The major of the student.
 * @return SUCCESS if the student is added, otherwise ERROR if the student can't
 * be added (duplicate name / GTID, no space in gradebook, invalid major).
 */
int add_student(char *name, int gtid, int year, char *major) {
  if (name == NULL || gradebook.size >= MAX_ENTRIES || strlen(name) >= MAX_NAME_LENGTH) {
    return ERROR;
  }
  for (int i = 0; i < gradebook.size; i++) {
    if (strcmp(gradebook.entries[i].student.name, name) == 0 || 
      gradebook.entries[i].student.gtid == gtid) {
        return ERROR;
    }
  }
  enum Major major_enum;
  if (strcmp(major, "CS") == 0) {
    major_enum = CS;
  } else if (strcmp(major, "CE") == 0) {
    major_enum = CE;
  } else if (strcmp(major, "EE") == 0) {
    major_enum = EE;
  } else if (strcmp(major, "IE") == 0) {
    major_enum = IE;
  } else {
    return ERROR;
  }
  struct GradebookEntry new_entry;
  strcpy(new_entry.student.name, name);
  new_entry.student.gtid = gtid;
  new_entry.student.year = year;
  new_entry.student.major = major_enum;
  for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
      new_entry.grades[i] = 0.0;
  }
  calculate_average(&new_entry);
  gradebook.entries[gradebook.size] = new_entry;
  gradebook.size++;
  calculate_course_average();
  return SUCCESS;
}

/**
 * Updates the grade of a specific assignment for a student and updates that
 * student's average grade.
 * 
 * Ensure that the overall course averages are still up-to-date after these grade updates.
 *
 * @param name The name of the student.
 * @param assignmentType The type of assignment.
 * @param newGrade The new grade.
 * @return SUCCESS if the grade is updated, otherwise ERROR if the grade isn't (student not found).
 */
int update_grade(char *name, enum Assignment assignment_type, double new_grade) {
  if (name == NULL || assignment_type >= NUM_ASSIGNMENTS || new_grade < 0) {
    return ERROR;
  }
  int found = 0;
  for (int i = 0; i < gradebook.size; i++) {
    if (strcmp(gradebook.entries[i].student.name, name) == 0) {
      gradebook.entries[i].grades[assignment_type] = new_grade;
      calculate_average(&gradebook.entries[i]);
      found = 1;
      break;
    }
  }
  if (!found) {
    return ERROR;
  }
  calculate_course_average();
  return SUCCESS;
}

/**
 * Adds a new student to the gradebook and initializes each of the student's
 * grades with the grades passed in.
 *
 * Additionally, will update the overall assignment_averages and course_average
 * based on the new added student. 
 *
 * @param name The name of the student.
 * @param gtid The GTID of the student.
 * @param year The year of the student.
 * @param major The major of the student.
 * @param grades An array of grades for the student.
 * @return SUCCESS if the student is added and the averages updated, otherwise ERROR if the student can't
 * be added (duplicate name / GTID, no space in gradebook, invalid major).
 */
int add_student_with_grades(char *name, int gtid, int year, char *major, double *grades) {
  int result = add_student(name, gtid, year, major);
  if (result == ERROR) {
    return ERROR;
  }
  for (int i = 0; i < gradebook.size; i++) {
    if (strcmp(gradebook.entries[i].student.name, name) == 0) {
      for(int j = 0; j < NUM_ASSIGNMENTS; j++) {
        gradebook.entries[i].grades[j] = grades[j];
      }
      calculate_average(&gradebook.entries[i]);
      break;
    }
  }
  calculate_course_average();
  return SUCCESS;
}

/**
 * Calculates the average grade for a specific gradebook entry and updates the
 * struct as appropriate.
 *
 * @param entry The gradebook entry for which to recalculate the average.
 * @return SUCCESS if the average is updated, ERROR if pointer is NULL
 */
int calculate_average(struct GradebookEntry *entry) {
  if (entry == NULL) {
    return ERROR;
  }
  double weight = 0, total = 0;
  for (int i = 0; i < NUM_ASSIGNMENTS; i++ ) {
    weight += (*entry).grades[i] * gradebook.weights[i];
    total += gradebook.weights[i];
  }
  if (total == 0) {
    return ERROR;
  }
  (*entry).average = weight / total;
  return SUCCESS;
}

/**
 * Calculates and update the overall course average and assignment averages. 
 * The average should be calculated by taking the averages of the student's 
 * averages, NOT the assignment averages.
 *
 * If the gradebook is empty, set the course and assignment averages to 0
 * and return ERROR.
 * 
 * @return SUCCESS if the averages are calculated properly, ERROR if gradebook
 * is empty
 */
int calculate_course_average(void) {
  if (gradebook.size == 0) {
    for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
      gradebook.assignment_averages[i] = 0;
    }
    gradebook.course_average = 0;
    return ERROR;
  }
  double students = 0, assignments[NUM_ASSIGNMENTS] = {0};
  for (int i = 0; i < gradebook.size; i++) {
    students += gradebook.entries[i].average;
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      assignments[j] += gradebook.entries[i].grades[j];
    }
  }
  gradebook.course_average = students / gradebook.size;
  for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
    double sum = 0;
    for (int j = 0; j < gradebook.size; j++) {
      sum += gradebook.entries[j].grades[i];
    }
    gradebook.assignment_averages[i] = sum / gradebook.size;
  }
  return SUCCESS;
}

/**
 * Searches for a student in the gradebook by name.
 *
 * @param name The name of the student.
 * @return The index of the student in the gradebook, or ERROR if not found.
 */
int search_student(char *name) {
  if (name == NULL) {
    return ERROR;
  }
  for (int i = 0; i < gradebook.size; i++) {
    if (strcmp(gradebook.entries[i].student.name, name) == 0) {
      return i;
    }
  }
  return ERROR;
}

/**
 * Remove a student from the gradebook while maintaining the ordering of the gradebook.
 *
 * Additionally, update the overall assignment_averages and course_average
 * based on the removed student and decrement the size of gradebook.
 *
 * If the gradebook is empty afterwards, SUCCESS should still be returned and
 * averages should be set to 0.
 *
 * @param name The name of the student to be withdrawn.
 * @return SUCCESS if the student is successfully removed, otherwise ERROR if
 * the student isn't found.
 */
int withdraw_student(char *name) {
  if (name == NULL || gradebook.size == 0) {
    return ERROR;
  }
  int found = -1;
  for (int i = 0; i < gradebook.size; i++) {
    if (strcmp(gradebook.entries[i].student.name, name) == 0) {
      found = i;
      break;
    }
  }
  if (found == -1) {
    return ERROR;
  }
  for (int i = found; i < gradebook.size - 1; i++) {
    gradebook.entries[i] = gradebook.entries[i + 1];
  }
  gradebook.size--;
  if (gradebook.size == 0) {
    for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
      gradebook.assignment_averages[i] = 0;
    }
    gradebook.course_average = 0;
  } else {
    calculate_course_average();
  }
  return SUCCESS;
}

int compare(const void *a, const void *b) {
  const struct GradebookEntry entryA = *(const struct GradebookEntry *)a;
  const struct GradebookEntry entryB = *(const struct GradebookEntry *)b;
  if (entryA.average > entryB.average) return -1;
  if (entryA.average < entryB.average) return 1;
  return 0;
}

/**
 * Populate the provided array with the GTIDs of the 5 students with the highest
 * grades. The GTIDs should be placed in descending order of averages. 
 * 
 * If unable to populate the full array (less than 5 students in gradebook), 
 * fill in the remaining values with INVALID_GTID.
 *
 * @param gtids An array to store the top five gtids.
 * @return SUCCESS if gtids are found, otherwise ERROR if gradebook is empty
 */
int top_five_gtid(int *gtids) {
  if (gtids == NULL || gradebook.size == 0) {
    return ERROR;
  }
  struct GradebookEntry temp_entries[MAX_ENTRIES];
  memcpy(temp_entries, gradebook.entries, gradebook.size * sizeof(struct GradebookEntry));
  for (int i = 0; i < gradebook.size - 1; i++) {
    for (int j = 0; j < gradebook.size - i - 1; j++) {
      if (temp_entries[j].average < temp_entries[j + 1].average) {
        struct GradebookEntry temp = temp_entries[j];
        temp_entries[j] = temp_entries[j + 1];
        temp_entries[j + 1] = temp;
      }
    }
  }
  for (int i = 0; i < 5; i++) {
    if (i < gradebook.size) {
      gtids[i] = temp_entries[i].student.gtid;
    } else {
      gtids[i] = INVALID_GTID;
    }
  }
  return SUCCESS;
}

/**
 * Sorts the gradebook entries by name in alphabetical order (First, Last).
 *
 * @return SUCCESS if names are sorted, ERROR is gradebook is empty.
 */
int sort_name(void) {
  if (gradebook.size == 0) {
    return ERROR;
  }
  int i, j;
  struct GradebookEntry temp;
  for (i = 0; i < gradebook.size - 1; i++) {
    for (j = 0; j < gradebook.size - i - 1; j++) {
      if (strcmp(gradebook.entries[j].student.name, gradebook.entries[j + 1].student.name) > 0) {
        temp = gradebook.entries[j];
        gradebook.entries[j] = gradebook.entries[j + 1];
        gradebook.entries[j + 1] = temp;
      }
    }
  }
  return SUCCESS;
}

/**
 * Sorts the gradebook entries by average grades in descending order.
 *
 * @return SUCCESS if entries are sorted, ERROR if gradebook is empty.
 */
int sort_averages(void) {
  if (gradebook.size == 0) {
    return ERROR;
  }
  int i, j;
  struct GradebookEntry temp;
  for (i = 0; i < gradebook.size - 1; i++) {
    for (j = 0; j < gradebook.size - i - 1; j++) {
      if (gradebook.entries[j].average < gradebook.entries[j + 1].average) {
        temp = gradebook.entries[j];
        gradebook.entries[j] = gradebook.entries[j + 1];
        gradebook.entries[j + 1] = temp;
      }
    }
  }
  return SUCCESS;
}

/**
 * Prints the entire gradebook in the format
 * student_name,major,grade1,grade2,...,student_average\n
 * 
 * Overall Averages:
 * grade1_average,grade2_average,...,course_average\n
 * 
 * Note 1: The '\n' shouldn’t print, just represents the newline for this example.
 * Note 2: There is an empty line above the “Overall Averages:” line.
 * 
 * All of the floats that you print must be manually rounded to 2 decimal places.
 *
 * @return SUCCESS if gradebook is printed, ERROR if gradebook is empty.
 */
int print_gradebook(void) {
  if (gradebook.size == 0) {
    return ERROR;
  }
  for (int i = 0; i < gradebook.size; i++) {
    printf("%s,", gradebook.entries[i].student.name);
      switch (gradebook.entries[i].student.major) {
        case CS: printf("CS,"); break;
        case CE: printf("CE,"); break;
        case EE: printf("EE,"); break;
        case IE: printf("IE,"); break;
        default: printf("Unknown,");
      }
    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
      printf("%.2f,", (int)(gradebook.entries[i].grades[j] * 100 + 0.5) / 100.0);
    }
    printf("%.2f\n", (int)(gradebook.entries[i].average * 100 + 0.5) / 100.0);
  }
  printf("\nOverall Averages:\n");
  for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
    printf("%.2f,", (int)(gradebook.assignment_averages[i] * 100 + 0.5) / 100.0);
  }
  printf("%.2f\n", (int)(gradebook.course_average * 100 + 0.5) / 100.0);
  return SUCCESS;
}
