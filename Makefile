OBJS = main.o list_node.o Buffer.o NodeIndex.o SCC.o CC.o UpdateIndex.o Graph.o Explored.o GrailIndex.o
SOURCE = main.cpp list_node.cpp Buffer.cpp NodeIndex.cpp SCC.cpp CC.cpp UpdateIndex.cpp Graph.cpp Explored.cpp GrailIndex.cpp
HEADER = list_node.h Buffer.h NodeIndex.h SCC.h CC.h UpdateIndex.h Graph.h Explored.h GrailIndex.h
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

Buffer.o: Buffer.cpp
	$(CC) $(FLAGS) Buffer.cpp

NodeIndex.o: NodeIndex.cpp
	$(CC) $(FLAGS) NodeIndex.cpp

CC.o: CC.cpp
	$(CC) $(FLAGS) CC.cpp

UpdateIndex.o: UpdateIndex.cpp
	$(CC) $(FLAGS) UpdateIndex.cpp

Graph.o: Graph.cpp
	$(CC) $(FLAGS) Graph.cpp

Explored.o: Explored.cpp
	$(CC) $(FLAGS) Explored.cpp

SCC.o: SCC.cpp
	$(CC) $(FLAGS) SCC.cpp

GrailIndex.o: GrailIndex.cpp
	$(CC) $(FLAGS) GrailIndex.cpp

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
