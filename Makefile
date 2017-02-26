CXX = g++
OPT = -g -Wall -O3

main: max_benefit.cpp
	$(CXX) $(OPT) max_benefit.cpp -c -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -f main *.o *~