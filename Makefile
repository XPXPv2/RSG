
run-debug-xterm: debug.bin
	xterm -hold -e "./bin/debug.bin"

run-debug: debug.bin
	./bin/debug.bin

debug.bin: bin/main.o bin/RSG.o
	g++ -g -o bin/debug.bin bin/main.o bin/RSG.o -std=c++17 -pthread

bin/main.o: src/main.cpp include/RSG.hpp
	g++ -g -c -o bin/main.o src/main.cpp -I include -std=c++17 -pthread

bin/RSG.o: src/RSG.cpp include/RSG.hpp
	g++ -g -c -o bin/RSG.o src/RSG.cpp -I include -std=c++17 -pthread

.PHONY: clean
clean:
	rm bin/debug.bin
	rm bin/main.o
	rm bin/RSG.o
	
.PHONY: setup
setup:
	mkdir -p bin
