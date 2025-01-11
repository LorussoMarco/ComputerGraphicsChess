# output: shared library (.so) and an executable to run tests


BASE_NAME := engine
TARGET_DIR := .
# Name of shared library that will be build --> libengine.so
TARGET := lib$(BASE_NAME).so
# Set of all .cpp files in the current directory
MAIN_SRC_FILES := $(wildcard *.cpp)
# Set of all object (.o) correspondents to (.cpp) files
MAIN_OBJ_FILES := $(MAIN_SRC_FILES:.cpp=.o)
# Name of the executable file for the test runner --> engine-tests-runner
TESTS_RUNNER := $(BASE_NAME)-tests-runner
# Set of all test file in the tests directory
TEST_SRC_FILES := $(wildcard tests/*_test.cpp)
# Set of all object file (.o) for the test file
TEST_OBJ_FILES := $(TEST_SRC_FILES:.cpp=.o)
DEPENDENCIES_DIR := dependencies

# Specifies the C++ compiler to use --> g++
CXX := g++
CXX_FLAGS := -c -fPIC -std=c++20 -O2
# Flag for the linker to create a shared library
LD_FLAGS := -shared
# Libraries to link with the project (glut, GL, GLU, freeimage)
LIBS := -lglut -lGL -lGLU -lfreeimage

# Your default target (first in the makefile) run make without specifying a target (ex: make clean)
install: $(TARGET)
	@echo "all done!"

# Target for building the shared library
# check if the test runner and object files are update
$(TARGET): $(MAIN_OBJ_FILES)
	# builds the shared library
	$(CXX) $(LD_FLAGS) -o $(TARGET) $(MAIN_OBJ_FILES) $(LIBS)
	@echo "$(TARGET) build done!"

# Target Principale
all: test debug release

clean: clean_test clean_debug clean_release

# Target per i test
before_test:
	test -d $(BINDIR_TEST) || mkdir -p $(BINDIR_TEST)
	test -d $(OBJDIR_TEST) || mkdir -p $(OBJDIR_TEST)

$(OBJDIR_TEST)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $< -o $@

$(OBJDIR_TEST)/RunTest.o: $(TEST_MAIN)
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $< -o $@

$(TEST_BIN): before_test $(OBJDIR_TEST)/RunTest.o $(TEST_OBJS) $(OBJ_DEBUG)
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) $^ -o $@ $(LIBDIR_DEBUG) $(LDFLAGS_DEBUG) $(LIB_DEBUG)

test: $(TEST_BIN)
	@echo "Esecuzione dei test:"
	@./$(TEST_BIN)

clean_test:
	rm -f $(OBJDIR_TEST)/*.o $(TEST_BIN)
	rm -rf $(BINDIR_TEST) $(OBJDIR_TEST)

# Debug
before_debug:
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

debug: before_debug $(OUT_DEBUG)

$(OUT_DEBUG): $(OBJDIR_DEBUG)/engine.o
	$(LD) -shared $(LIBDIR_DEBUG) $^ -o $@ $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/engine.o: engine.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $< -o $@

clean_debug:
	rm -f $(OBJDIR_DEBUG)/*.o $(OUT_DEBUG)
	rm -rf bin/Debug $(OBJDIR_DEBUG)

# Release
before_release:
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

release: before_release $(OUT_RELEASE)

$(OUT_RELEASE): $(OBJDIR_RELEASE)/engine.o
	$(LD) -shared $(LIBDIR_RELEASE) $^ -o $@ $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/engine.o: engine.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $< -o $@

clean_release:
	rm -f $(OBJDIR_RELEASE)/*.o $(OUT_RELEASE)
	rm -rf bin/Release $(OBJDIR_RELEASE)

# Declaration that clean and install are not files
# Always execute commands associated with that target, regardless of whether a file with the same name exists
.PHONY: clean install
