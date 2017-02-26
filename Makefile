CXX = g++
OPT = -g -Wall -O3

main: eurelTour.cpp
	$(CXX) $(OPT) eurelTour.cpp -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -f main *.o *~