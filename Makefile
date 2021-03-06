#tsp
OBJS = main.o list_node.o Buffer.o NodeIndex.o SCC.o CC.o UpdateIndex.o Graph.o Explored.o GrailIndex.o JobScheduler.o worker_routine.o
SOURCE = main.cpp list_node.cpp Buffer.cpp NodeIndex.cpp SCC.cpp CC.cpp UpdateIndex.cpp Graph.cpp Explored.cpp GrailIndex.cpp JobScheduler.cpp worker_routine.cpp
HEADER = list_node.h Buffer.h NodeIndex.h SCC.h CC.h UpdateIndex.h Graph.h Explored.h GrailIndex.h Job.h JobScheduler.h QueryJob.h worker_routine.h
OUT = tsp

#unit testing
OBJS_2 = list_node.o Buffer.o NodeIndex.o SCC.o CC.o UpdateIndex.o Graph.o Explored.o GrailIndex.o JobScheduler.o worker_routine.o unitTesting.o
SOURCE_2 = list_node.cpp Buffer.cpp NodeIndex.cpp SCC.cpp CC.cpp UpdateIndex.cpp Graph.cpp Explored.cpp GrailIndex.cpp JobScheduler.cpp worker_routine.cpp unitTesting.cpp
HEADER_2 = list_node.h Buffer.h NodeIndex.h SCC.h CC.h UpdateIndex.h Graph.h Explored.h GrailIndex.h Job.h JobScheduler.h QueryJob.h worker_routine.h unitTesting.h
OUT_2 = unitTesting

CC = g++ -std=c++11
#FLAGS  = -c -g -O2 -Wextra -Wall
FLAGS  = -c -g -Wextra -Wall

all: $(OUT)

unit: $(OUT_2)

#tsp
$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o tsp -lpthread

#unit testing
$(OUT_2): $(OBJS_2)
	$(CC) -g $(OBJS_2) -o unitTesting -lpthread -lcunit

prof: $(OBJS)
	$(CC) -pg $(OBJS) -o prof

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

unitTesting.o: unitTesting.cpp
	$(CC) $(FLAGS) unitTesting.cpp

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

JobScheduler.o: JobScheduler.cpp
	$(CC) $(FLAGS) JobScheduler.cpp

worker_routine.o: worker_routine.cpp
	$(CC) $(FLAGS) worker_routine.cpp

clean:
	rm -f $(OBJS) $(OUT)
	rm -f $(OBJS_2) $(OUT_2)

count:
	wc $(SOURCE) $(HEADER)
	wc $(SOURCE_2) $(HEADER_2)
