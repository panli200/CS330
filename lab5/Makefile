# leads comments in a line 
# Build all: default target
all : myIO

# Separate compilation to build object files
main.o : main.cpp  
	g++ -c -ggdb main.cpp


# linking
#demo is a target which depends upon main.o and greet.o 
#"g++ main.o greet.o -o demo" is the command to produce the executable file
#You need to use a TAB before g++ 
myIO : main.o 
	g++ main.o  -o myIO

# Testing
check : all
	./myIO

# Clean up all build targets so that one may get a clean build
clean :
	rm -f *.o myIO *.txt
