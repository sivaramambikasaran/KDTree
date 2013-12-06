CC = g++
CFLAGS	= -c -Wall -O4 -ffast-math -ffinite-math-only -I ~/Dropbox/Eigen/ -I ./header/
SOURCES = ./src/KDTree.cpp ./examples/test_KDTree.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = ./exec/test_KDTree

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o ./examples/*.o ./src/*.o ./exec/*.o

tar:
	tar -zcvf KDTree.tar.gz ./makefile.mk ./exec ./src ./header ./examples