# Specify the g++ compiler using a variable named CXX. This allows you to switch
# easily to a different compiler if you wish.
CXX = g++

# Some optional compiler flags that turn all compiler warnings and turn them
# into compiler errors. Helpful for reducing possible runtime errors but
# also kind of a pain to work with.
OPTCFLAGS = -Wall -Werror

# Change this path to the fully qualified path from the root to your include directory
CFLAGS = -I/Users/jourdanrampoldi/Desktop/textAdventure/include/

# list all of the .cpp files needed to build the program and save them in a
# variable named SOURCES
SOURCES = $(shell ls lib/*.cpp main.cpp) 

# build the adventureGame target from the list of source files. This uses the
# g++ compiler to create the program (target) named adventureGame. Note the $@
# is a variable that refers to the target name. The rest expands the variable
# SOURCES to provide the compiler with a list of .cpp files.
AdAstraPerInfernum: $(SOURCES)
	$(CXX) ${CFLAGS} -o $@ $(SOURCES)

# remove the target (handy rule if you want to easily rebuild it)
.PHONY: clean
clean:
	rm -f adventureGame
