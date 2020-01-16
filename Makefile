
run-debug: debug.bin
	xterm -hold -e "./bin/debug.bin"

debug.bin: bin/main.o bin/RSG.o
	g++-8 -g -o bin/debug.bin bin/main.o bin/RSG.o -std=c++11 -pthread

bin/main.o: src/main.cpp include/RSG.hpp
	g++-8 -g -c -o bin/main.o src/main.cpp -I include -std=c++11 -pthread

bin/RSG.o: src/RSG.cpp include/RSG.hpp
	g++-8 -g -c -o bin/RSG.o src/RSG.cpp -I include -std=c++11 -pthread

clean:
	rm bin/debug.bin
	rm bin/main.o
	rm bin/RSG.o
