OBJS = main.o list_node.o list.o Buffer.o NodeIndex.o Graph.o Queue.o HashTable.o
SOURCE = main.cpp list_node.cpp list.cpp Buffer.cpp NodeIndex.cpp Graph.cpp Queue.cpp HashTable.cpp
HEADER = list_node.h list.h Buffer.h NodeIndex.h Graph.h Queue.h HashTable.h
OUT = project
CC = g++ -std=c++11
FLAGS  = -c -g -Wextra -Wall

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o project

prof: $(OBJS)
	$(CC) -pg $(OBJS) -o prof

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

list_node.o: list_node.cpp
	$(CC) $(FLAGS) list_node.cpp

list.o: list.cpp
	$(CC) $(FLAGS) list.cpp

Buffer.o: Buffer.cpp
	$(CC) $(FLAGS) Buffer.cpp

NodeIndex.o: NodeIndex.cpp
	$(CC) $(FLAGS) NodeIndex.cpp

Graph.o: Graph.cpp
	$(CC) $(FLAGS) Graph.cpp

Queue.o: Queue.cpp
	$(CC) $(FLAGS) Queue.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) HashTable.cpp

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
