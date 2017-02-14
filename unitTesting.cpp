#include "unitTesting.h"
#include <queue>
#include <stack>

static FILE* graph_file = NULL;
static FILE* static_file = NULL;
static FILE* dynamic_file = NULL;
static FILE* queue_file = NULL;
static FILE* stack_file = NULL;
static FILE* results_static = NULL;
static FILE* results_dynamic = NULL;

void addJob();
void queryJob();
void testQueue();
void testStack();
void testHashTable();

int initSuite(void) {
    if (NULL == (graph_file = fopen("./unitFiles/tinyGraph.txt", "r")))
        return -1;
    if (NULL == (dynamic_file = fopen("./unitFiles/dynamic.txt", "r")))
        return -1;
    if (NULL == (static_file = fopen("./unitFiles/static.txt", "r")))
        return -1;
    if (NULL == (queue_file = fopen("./unitFiles/queue.txt", "r")))
        return -1;
    if (NULL == (stack_file = fopen("./unitFiles/stack.txt", "r")))
        return -1;
    if (NULL == (results_static = fopen("./unitFiles/results_static.txt", "w")))
        return -1;
    if (NULL == (results_dynamic = fopen("./unitFiles/results_dynamic.txt", "w")))
        return -1;
    return 0;
}

int cleanSuite(void) {
    if (0 != fclose(graph_file))
        return -1;
    if (0 != fclose(dynamic_file))
        return -1;
    if (0 != fclose(static_file))
        return -1;
    if (0 != fclose(queue_file))
        return -1;
    if (0 != fclose(stack_file))
        return -1;
    if (0 != fclose(results_static))
        return -1;
    if (0 != fclose(results_dynamic))
        return -1;
    return 0;
}

void testCreate(void) {
    Graph graph(1);
    uint32_t node, neighbour;
    int result, flag = 0;
    while (fscanf(graph_file, "%u %u", &node, &neighbour) == 2) {
        result = graph.add(node, neighbour);
        if (result == 1) {
            printf("\nNode successfully added.");
        }
        else if (result == -1) {
            printf("\nFound duplicate.");
            flag = -1;
        }
    }
    printf("\n");
    if (flag == -1) {
        CU_ASSERT(0);
    }
    else {
        CU_ASSERT(1);
    }
}

void testCC(void) {
    Graph graph(1);
    uint32_t node, neighbour;
    int result;
    while (fscanf(graph_file, "%u %u", &node, &neighbour))
        graph.add(node, neighbour);
    printf("\nGraph done.\n");
    result = graph.createComponents();
    rewind(graph_file);
    if (result == 1) {
        printf("CC successfully created.\n");
    }
    else {
        printf("CC creation failed.\n");
    }
    CU_ASSERT(result);
}

void testSCC(void) {
    Graph graph(1);
    graph.graphStatic();
    uint32_t node, neighbour;
    int result;
    while (fscanf(graph_file, "%u %u", &node, &neighbour))
        graph.add(node, neighbour);
    printf("\nGraph done.\n");
    result = graph.createComponents();
    rewind(graph_file);
    if (result == 1) {
        printf("SCC successfully created.\n");
    }
    else if (result == 0) {
        printf("SCC creation failed.\n");
    }
    CU_ASSERT(result);
}

void testQuery1(void) {
    Graph graph(1);
    graph.graphStatic();
    uint32_t node, neighbour;
    char op, buffer[64];
    int result;
    while (fscanf(graph_file, "%u %u", &node, &neighbour))
        graph.add(node, neighbour);
    printf("\nGraph done.\n");
    graph.createComponents();
    rewind(graph_file);
    while (1) {
        if(fgets(buffer, 64, static_file) == NULL)
          break;
        sscanf(buffer, "%c %u  %u", &op, &node, &neighbour);
        result = graph.query(node, neighbour, 0, 0);
        fprintf(results_static, "%d\n", result);
    }
    CU_ASSERT(1);
}

void testQuery2(void) {
    Graph graph(1);
    uint32_t node, neighbour;
    char op, buffer[64];
    int result;
    while (fscanf(graph_file, "%u %u", &node, &neighbour))
        graph.add(node, neighbour);
    printf("\nGraph done.\n");
    graph.createComponents();
    rewind(graph_file);
    while (1) {
        if(fgets(buffer, 64, dynamic_file) == NULL)
          break;
        sscanf(buffer, "%c %u  %u", &op, &node, &neighbour);
        if (op == 'A') {
            graph.add(node, neighbour);
        }
        else if (op == 'Q') {
            result = graph.query(node, neighbour, 0, 0);
            fprintf(results_dynamic, "%d\n", result);
        }
    }
    CU_ASSERT(1);
}

void testQueue(void) {
    Queue <uint32_t> q1(100);
    queue <uint32_t> q2;
    uint32_t value;
    while (fscanf(queue_file, "%u", &value) == 1) {
        q1.push(value);
        q2.push(value);
    }
    int result = 1;
    while (!q1.isEmpty()) {
        if (q1.pop() == q2.front()) {
            q2.pop();
        }
        else {
            result = 0;
            break;
        }
    }
    if (result == 0)
        printf("\nQueue failed.\n");
    else
        printf("\nQueue passed.\n");
    CU_ASSERT(result);
}

void testStack(void) {
    Stack <uint32_t> s1(100);
    stack <uint32_t> s2;
    uint32_t value;
    while (fscanf(stack_file, "%u", &value) == 1) {
        s1.push(value);
        s2.push(value);
    }
    int result = 1;
    while (!s1.isEmpty()) {
        if (s1.pop() == s2.top()) {
            s2.pop();
        }
        else {
            result = 0;
            break;
        }
    }
    if (result == 0)
        printf("\nStack failed.\n");
    else
        printf("\nStack passed.\n");
    CU_ASSERT(result);
}

int main(void) {
    CU_pSuite pSuite1 = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    pSuite1 = CU_add_suite("Suite_1", initSuite, cleanSuite);
    if (NULL == pSuite1) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite1, "Test of graph creation", testCreate))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite1, "Test of CC", testCC))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite1, "Test of SCC", testSCC))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite1, "Test of Static Query", testQuery1))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite1, "Test of Dynamic Query", testQuery2))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite1, "Test of Queue", testQueue))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite1, "Test of Stack", testStack))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
