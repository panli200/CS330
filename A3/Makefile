# leads comments in a line 
# Build all: default target
all : myThread

# Separate compilation to build object files
myThread.o : myThread.cpp  
	g++ -c -ggdb myThread.cpp -lpthread


# linking
#myThread is a target which depends upon myThread.o 
#"g++ myThread.o -o myThread lpthread" is the command to produce the executable file
#You need to use a TAB before g++ 
myThread : myThread.o 
	g++ myThread.o -o myThread -lpthread

# Testing
check : all
	./myThread

# Clean up all build targets so that one may get a clean build
clean :
	rm -f *.o myThread 
