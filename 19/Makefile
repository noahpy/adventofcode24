LIBS = ../lib/parseutils.cpp ../lib/regexutils.cpp ../lib/listutils.cpp ../lib/printutils.cpp ../lib/vectorutils.cpp ../lib/nutils.cpp
OBJECTS = objects/parseutils.o objects/regexutils.o objects/listutils.o objects/printutils.o objects/vectorutils.o objects/nutils.o

libs: $(LIBS)
	g++ -c ../lib/parseutils.cpp ../lib/regexutils.cpp ../lib/listutils.cpp ../lib/printutils.cpp ../lib/vectorutils.cpp ../lib/nutils.cpp 
	mkdir -p objects 
	mv *.o ./objects

first: puzzle1.cpp 
	g++ -O3 puzzle1.cpp $(OBJECTS) -o ./first

second: puzzle2.cpp
	g++ -O3 puzzle2.cpp $(OBJECTS) -o ./second

frun:
	./first input.txt | tail -n 1 | wl-copy

srun:
	./second input.txt | tail -n 1 | wl-copy

clean:
	rm -f ./first
	rm -f ./second
