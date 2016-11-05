OBJS = main.o list_node.o list.o
SOURCE = main.cpp list_node.cpp list.cpp
HEADER = list_node.h list.h
OUT = project
CC = g++ -std=c++11
FLAGS  = -c -g -Wextra -Wall

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

list_node.o: list_node.cpp
	$(CC) $(FLAGS) list_node.cpp

list.o: list.cpp
    $(CC) $(FLAGS) list.cpp

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
