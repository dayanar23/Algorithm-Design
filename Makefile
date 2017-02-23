CXX = g++
OPT = -g -Wall -O3

output: eulerTour.cpp
	$(CXX) $(OPT) eulerTour.cpp -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -f output *.o *~