# How to execute:
After compiling, using __Makefile__, execute the following command:

>./tsp \[num_of_threads] \[initialization_graph.txt] [graph_workload.txt]

# Input Files:
The __Initialization Graph__ input file should only contain edges in the following syntax form:

>0 1

>1 2

>2 3

The __Workload__ input file should contain queries if it's a __Static__ graph, or more edges if it is __Dynamic__ (default is Dynamic):

__Static-Workload:__

>STATIC

>Q 0 1

>Q 1 2

>Q 2 3

>F

>Q 4 3

>Q 0 1

>F

__Dynamic-Workload:__

>DYNAMIC

>A 0 1

>Q 1 2

>F

>A 12 3

>Q 4 3

>Q 0 1

>F

_\*Batches are seperated with a "F"_
