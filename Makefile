
run-debug: debug.bin
	xterm -hold -e "./bin/debug.bin"

debug.bin: bin/main.o bin/RSG.o
	g++-8 -g -o bin/debug.bin bin/main.o bin/RSG.o

bin/main.o: src/main.cpp include/RSG.hpp
	g++-8 -g -c -o bin/main.o src/main.cpp -I include

bin/RSG.o: src/RSG.cpp include/RSG.hpp
	g++-8 -g -c -o bin/RSG.o src/RSG.cpp -I include
