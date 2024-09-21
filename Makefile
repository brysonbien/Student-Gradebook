# Project4 (Intro to C) - CS2110: Fall 2020
# GCC flags from the syllabus (each flag described for the curious minds!)
# Flag info credit: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

# Flags code is expected to compile with
CFLAGS =
CFLAGS += -std=c99 # Using the C99 standard
CFLAGS += -Wall # This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros
CFLAGS += -pedantic # Issue all the warnings demanded by strict ISO C and ISO C++; reject all programs that use forbidden extensions, and some other programs that do not follow ISO C and ISO C++
CFLAGS += -Wextra # This enables some extra warning flags that are not enabled by -Wall
CFLAGS += -Werror # Make all warnings into errors
CFLAGS += -O0 # Reduce compilation time and make debugging produce the expected results. This is the default.
CFLAGS += -Wstrict-prototypes # Warn if a function is declared or defined without specifying the argument types
CFLAGS += -Wold-style-definition # Warn if an old-style function definition is used. A warning is given even if there is a previous prototype
CFLAGS += -g # Generate debugging information
CFLAGS += -Werror=vla # Generate an error if variable-length arrays (bad practice in C!) are used
CFLAGS += -fcf-protection=none # Workaround for a bug that can make debugging annoying: https://stackoverflow.com/questions/64697087/gdb-shows-incorrect-arguments-of-functions-for-stack-frames

# Name of Test Executable
TEST_OBJNAME = tests
ARCH = $(shell uname -m)
STUDENT_OBJNAME = student

.PHONY: clean tests run-case run-gdb student

STUDENT_C_FILES = \
	gradebook.c \

TEST_OFILES = \
	test/$(ARCH)/main.o \
	test/$(ARCH)/gradebook_helper.o \

TEST_CFILES = \
	test/gradebook_suite.c

# Libraries needed for Check
CHECK_LIBS = $(shell pkg-config --cflags --libs check)

run_tests: tests clean
	./$(TEST_OBJNAME)

student: clean
	@ gcc -fno-asm -static $(CFLAGS) $(STUDENT_C_FILES) main.c -o $(STUDENT_OBJNAME)
	@ ./$(STUDENT_OBJNAME)

########################################################
################# Autograding Below #######################
########################################################

# Testing with check library
tests: clean
	@ gcc -fno-asm -static $(CFLAGS) $(STUDENT_C_FILES) $(TEST_OFILES) $(TEST_CFILES) $(CHECK_LIBS) -o $(TEST_OBJNAME)

# To run a specific test case (or all similar to tests)
run-case: tests
	@ ./$(TEST_OBJNAME) $(TEST)

# To run gdb on testcase(s)
run-gdb: tests
	@ CK_FORK=no gdb --args ./$(TEST_OBJNAME) $(TEST)

# Clean Project
clean:
	@rm -f $(TEST_OBJNAME) *.o *.out
