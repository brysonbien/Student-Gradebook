#ifndef GRADEBOOK
#define GRADEBOOK

/* DO NOT MODIFY FILE */

#include <stdio.h>

#define UNUSED(x) ((void)x)
#define MAX_NAME_LENGTH 20
#define MAX_ENTRIES 50

#define ERROR -1
#define SUCCESS 0
#define INVALID_GTID -1

enum Major { CS = 0, CE, EE, IE };

enum Assignment { HW1, HW2, HW3, P1, P2, NUM_ASSIGNMENTS };

struct Student {
  char name[MAX_NAME_LENGTH];
  int gtid;
  int year;
  enum Major major;
};

struct GradebookEntry {
  struct Student student;
  double grades[NUM_ASSIGNMENTS];
  double average;
};

struct Gradebook {
  struct GradebookEntry entries[MAX_ENTRIES];
  double assignment_averages[NUM_ASSIGNMENTS];
  double course_average;
  double weights[NUM_ASSIGNMENTS];
  int size;
};

// Function prototypes
// Add/Update Methods
int add_student(char *name, int gtid, int year, char *major);
int update_grade(char *name, enum Assignment assignment_type, double new_grade);
int add_student_with_grades(char *name, int gtid, int year, char *major,
                            double *grades);

// Score/Average Methods
int calculate_average(struct GradebookEntry *entry);
int calculate_course_average(void);

// Search/Withdraw Methods
int search_student(char *name);
int withdraw_student(char *name);


// Score/Average Methods
int calculate_average(struct GradebookEntry *entry);
int calculate_course_average(void);


// Sorting Methods
int top_five_gtid(int *gtids);
int sort_name(void);
int sort_averages(void);

// Printing
int print_gradebook(void);

extern struct Gradebook gradebook;

#endif
