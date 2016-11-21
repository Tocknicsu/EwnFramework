all:
	g++ -O3 ./framework/*.cpp ./player/*.cpp main.cpp -I./framework -I./player -o ewn
