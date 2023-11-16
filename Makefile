
# Reset all default rules

.SUFFIXES: 

# Set logical "dummy" targets, which are not associated with any
# physical file

.PHONY: default all clean clean-dot clean-png clean-all

default: main

all: default

# Add Makefile as a prerequisite, so that all is rebuilt each time the
# Makefile file is modified

graph.o: graph.cpp graph.hpp Makefile
	g++ -std=c++11 -Wall graph.cpp -c

main.o: main.cpp graph.hpp Makefile
	g++ -std=c++11 -Wall main.cpp -c

main: graph.o main.o
	g++ -std=c++11 graph.o main.o -o main

# The "rm" command is prefixed with a "-", so that a failure in the
# command does not stop make. This command will for instance fail if
# none of the specified files exists.

clean:
	-rm -f *.o main *~ *.orig *.gch

clean-dot:
	-rm -f *.dot

clean-png:
	-rm -f *.png

clean-all: clean clean-dot clean-png
