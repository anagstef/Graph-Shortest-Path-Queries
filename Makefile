OBJS = main.o list_node.o
SOURCE = main.cpp list_node.cpp
HEADER = list_node.h
OUT = project
CC = g++ -std=c++11
FLAGS  = -c -g -Wextra -Wall

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

list_node.o: list_node.cpp
	$(CC) $(FLAGS) list_node.cpp

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
