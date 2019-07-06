CXXFLAGS += -std=c++17

CXXFLAGS += -Wall -Wextra -pedantic-errors
LDLIBS := $(shell pkg-config sfml-all --libs)

SOURCES := $(wildcard *.cc)
PROGRAMS := $(patsubst %.cc,%,$(SOURCES))

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS)