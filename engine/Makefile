CXX = g++
AR = ar
LD = g++
WINDRES = windres

# Flags generali
CFLAGS = -Wall -std=c++20 -fPIC -m64 -fexceptions
LDFLAGS = -m64

# Include generali
INC = 
LIBDIR = 

# Debug Settings
INC_DEBUG = -I../dependencies/freeglut/include $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g -D_DEBUG
LIBDIR_DEBUG = -L../dependencies/freeglut/lib/x64/Debug $(LIBDIR)
LIB_DEBUG = -lGL -lGLU ../dependencies/freeglut/lib/x64/Debug/freeglut_staticd.lib
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
OUT_DEBUG = bin/Debug/libengine.so

# Release Settings
INC_RELEASE = -I../dependencies/freeglut/include $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
LIBDIR_RELEASE = -L../dependencies/freeglut/lib/x64/Release $(LIBDIR)
LIB_RELEASE = -lGL -lGLU ../dependencies/freeglut/lib/x64/Release/freeglut_static.lib
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
OUT_RELEASE = bin/Release/libengine.so

# Test Settings
TESTDIR = tests
OBJDIR_TEST = obj/Test
BINDIR_TEST = bin/Test
TEST_MAIN = $(TESTDIR)/RunTests.cpp  # File con la funzione main per i test
TEST_OBJS = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR_TEST)/%.o, $(filter-out $(TEST_MAIN), $(wildcard $(TESTDIR)/*.cpp)))
TEST_BIN = $(BINDIR_TEST)/test_runner

# Target Principale
all: test debug release

clean: clean_test clean_debug clean_release

# Target per i test
before_test:
	test -d $(BINDIR_TEST) || mkdir -p $(BINDIR_TEST)
	test -d $(OBJDIR_TEST) || mkdir -p $(OBJDIR_TEST)

# Compila i file di test tranne RunTests.cpp (file principale)
$(OBJDIR_TEST)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $< -o $@

# Compila il test_runner con gli altri oggetti
$(TEST_BIN): before_test $(OBJDIR_TEST)/RunTests.o $(TEST_OBJS)
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) $^ -o $(TEST_BIN) $(LIBDIR_DEBUG) $(LDFLAGS_DEBUG) $(LIB_DEBUG)

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

.PHONY: all clean test clean_test debug clean_debug release clean_release
