# ------------------------------------
# Version
# ------------------------------------
VERSION := 0.9.0

# ------------------------------------
# Tools and Flags
# ------------------------------------
CXX      ?= $(shell which g++)
CXXFLAGS += -std=c++17 -Wall -Wextra -Wpedantic -fexceptions -O2
CPPFLAGS += $(shell pkg-config --cflags pwxlib) -DVERSION=\"${VERSION}\"
INSTALL  := $(shell which install)
LDFLAGS  += $(shell pkg-config --libs pwxlib)
RM       := $(shell which rm) -f
SED      := $(shell which sed)
TARGET   := getrn

# Use the compiler as the linker.
LD := $(CXX)

# ------------------------------------
# Install and target directories
# ------------------------------------
PREFIX     ?= /usr
DESTDIR    ?=
BINPREFIX  ?= $(PREFIX)
BINDIR     ?= ${BINPREFIX}/bin


# ------------------------------------
# Source files and objects
# ------------------------------------
SOURCES := $(sort $(wildcard src/*.cpp))
MODULES := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
DEPENDS := $(addprefix dep/,$(notdir $(SOURCES:.cpp=.d)))


# ------------------------------------
# Rules
# ------------------------------------
.Phony: clean
.SUFFIXES: .cpp

# ------------------------------------
# Create dependencies
# ------------------------------------
dep/%.d: src/%.cpp
	@set -e; $(RM) $@; \
	$(CXX) -MM $(CPPFLAGS) $(CXXFLAGS) $< > $@.$$$$; \
	$(SED) 's,\($*\)\.o[ :]*,obj/\1.o $@ : ,g' < $@.$$$$ > $@; \
	$(RM) $@.$$$$

# ------------------------------------
# Compile modules
# ------------------------------------
obj/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

all: $(TARGET)

clean:
	@echo "Cleaning getRandomName"
	@rm -rf $(TARGET) $(MODULES)

$(TARGET): $(MODULES)
	$(CXX) -o $(TARGET) $(MODULES) $(CPPFLAGS) $(LDFLAGS) $(CXXFLAGS)

# ------------------------------------
# Include all dependency files
# ------------------------------------
ifeq (,$(findstring clean,$(MAKECMDGOALS)))
  -include $(DEPENDS)
endif
