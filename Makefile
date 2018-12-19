CXX       = $(shell which g++)
CXXFLAGS += -std=c++17 -Wall -Wextra -Wpedantic -fexceptions -O2
CXXFLAGS += $(shell pkg-config --cflags pwxlib)
LDFLAGS  += $(shell pkg-config --libs pwxlib)
TARGET    = getrn
SOURCES = $(wildcard *.cpp)
MODULES = $(SOURCES:.cpp=.o)

# ------------------------------------
# Rules
# ------------------------------------
.Phony: clean depend

.SUFFIXES: .cpp

%.o: %.cpp
	@echo "Compiling $@"
	$(CXX) $(CXXFLAGS) -o $@ -c $<

all: $(TARGET)

clean:
	@echo "Cleaning getRandomName"
	@rm -rf $(TARGET) $(MODULES)


$(TARGET): depend $(MODULES)
	@echo "Linking $(TARGET)"
	$(CXX) $(LDFLAGS) -o $(TARGET) $(MODULES)

# ------------------------------------
# Create dependencies
# ------------------------------------
depend: Makefile
	@echo "Checking dependencies"
	@$(CXX) -MM $(CXXFLAGS) $(SOURCES) > Makefile.dep

# ------------------------------------
# Include dependencies
# ------------------------------------
-include Makefile.dep
