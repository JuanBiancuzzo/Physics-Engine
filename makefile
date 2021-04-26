CPP=g++
NAME=gofmp
FILES= src/*.cpp src/physicsEngine/*.cpp 
HEADERS= src/headers/*.h src/physicsEngine/headers/*.h
CPPFLAGS=-g -std=c++14
CPPLINKS=

build: 
	$(CPP) $(FILES) $(CPPFLAGS) $(CPPLINKS) -o $(NAME)

execute:
	./$(NAME)

clear:
	clear

exe: build clear execute
