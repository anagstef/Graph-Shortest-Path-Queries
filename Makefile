OBJS = main.o list_node.o Buffer.o NodeIndex.o Graph.o HashTable.o Explored.o SCC.o #Queue_.o #list.o
SOURCE = main.cpp list_node.cpp Buffer.cpp NodeIndex.cpp Graph.cpp HashTable.cpp Explored.cpp SCC.cpp #Queue_.cpp #list.cpp
HEADER = list_node.h Buffer.h NodeIndex.h Graph.h HashTable.h Explored.h SCC.h #Queue_.h #list.h
OUT = project
CC = g++ -std=c++11
#FLAGS  = -c -g -O2 -Wextra -Wall
FLAGS  = -c -g -Wextra -Wall

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o project

prof: $(OBJS)
	$(CC) -pg $(OBJS) -o prof

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

list_node.o: list_node.cpp
	$(CC) $(FLAGS) list_node.cpp

#list.o: list.cpp
#	$(CC) $(FLAGS) list.cpp

Buffer.o: Buffer.cpp
	$(CC) $(FLAGS) Buffer.cpp

NodeIndex.o: NodeIndex.cpp
	$(CC) $(FLAGS) NodeIndex.cpp

Graph.o: Graph.cpp
	$(CC) $(FLAGS) Graph.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) HashTable.cpp

Explored.o: Explored.cpp
	$(CC) $(FLAGS) Explored.cpp

SCC.o: SCC.cpp
	$(CC) $(FLAGS) SCC.cpp

#Queue_.o: Queue_.cpp
#	$(CC) $(FLAGS) Queue_.cpp

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
