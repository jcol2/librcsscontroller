# Declaration of variables
CC = g++
OBJ_FLAGS = -fPIC -std=c++11 -g -I ../include 
EXEC_FLAGS = -shared -Wl,-soname,librcsscontroller.so.1
 
# File names
EXEC = librcsscontroller.so.1.0.0
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(EXEC_FLAGS) $(OBJECTS) -o $(EXEC)
	ln -sf librcsscontroller.so.1.0.0 librcsscontroller.so.1.0
	ln -sf librcsscontroller.so.1.0 librcsscontroller.so.1
	ln -sf librcsscontroller.so.1 librcsscontroller.so

# To obtain object files
%.o: %.cpp
	$(CC) -c $(OBJ_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
	rm librcsscontroller.so*