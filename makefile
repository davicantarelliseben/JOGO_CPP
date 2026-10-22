EXE_NAME = main.exe
INCLUDE = include
SRCS = main.cpp Character.cpp
CC = g++

all : $(SRCS) 
	$(CC) $(SRCS) -o $(EXE_NAME) -O3 -g -I$(INCLUDE)



clean :
	rm -f $(EXE_NAME)

