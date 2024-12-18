CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall -std=c++20 -fPIC -m64 -fexceptions
RCFLAGS = 
RESINC = 
LIBDIR = 
LDFLAGS = -m64

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

TEST_SRC = $(wildcard $(TESTDIR)/*.cpp)         # Individua tutti i file di test
TEST_BIN = $(patsubst $(TESTDIR)/%.cpp, $(BINDIR_TEST)/%, $(TEST_SRC)) # Output dei binari di test

# Target Principale
all: test debug release

clean: clean_debug clean_release clean_test

# Target per i test
before_test:
	test -d $(BINDIR_TEST) || mkdir -p $(BINDIR_TEST)
	test -d $(OBJDIR_TEST) || mkdir -p $(OBJDIR_TEST)

$(BINDIR_TEST)/%: $(TESTDIR)/%.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) $< -o $@ $(LIBDIR_DEBUG) $(LDFLAGS_DEBUG) $(LIB_DEBUG)

test: before_test $(TEST_BIN)
	@echo "Esecuzione di tutti i test:"
	@for test_exec in $(TEST_BIN); do \
		echo "Running $$test_exec"; \
		./$$test_exec; \
	done

clean_test:
	rm -f $(BINDIR_TEST)/* $(OBJDIR_TEST)/*.o
	rm -rf $(BINDIR_TEST) $(OBJDIR_TEST)

# Debug
before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

debug: before_debug out_debug

out_debug: $(OBJDIR_DEBUG)/engine.o
	$(LD) -shared $(LIBDIR_DEBUG) $(OBJDIR_DEBUG)/engine.o -o $(OUT_DEBUG) $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/engine.o: engine.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c engine.cpp -o $(OBJDIR_DEBUG)/engine.o

clean_debug: 
	rm -f $(OBJDIR_DEBUG)/*.o $(OUT_DEBUG)
	rm -rf $(OBJDIR_DEBUG) bin/Debug

# Release
before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

release: before_release out_release

out_release: $(OBJDIR_RELEASE)/engine.o
	$(LD) -shared $(LIBDIR_RELEASE) $(OBJDIR_RELEASE)/engine.o -o $(OUT_RELEASE) $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/engine.o: engine.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c engine.cpp -o $(OBJDIR_RELEASE)/engine.o

clean_release: 
	rm -f $(OBJDIR_RELEASE)/*.o $(OUT_RELEASE)
	rm -rf $(OBJDIR_RELEASE) bin/Release

.PHONY: before_test test clean_test before_debug debug clean_debug before_release release clean_release
