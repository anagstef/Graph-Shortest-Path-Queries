#include "unitTesting.h"
#include <queue>
#include <stack>

static FILE* results_static = NULL;
static FILE* results_dynamic = NULL;

int initSuite(void) {
    if (NULL == (results_static = fopen("results_static.txt", "w")))
        return -1;
    if (NULL == (results_dynamic = fopen("results_dynamic.txt", "w")))
        return -1;
    return 0;
}

int cleanSuite(void) {
    if (0 != fclose(results_static))
        return -1;
    if (0 != fclose(results_dynamic))
        return -1;
    return 0;
}

void testCreateP(void) {
    Graph graph(1);
    int result, i;
    int results[13];
    result = graph.add(0, 1);
    results[0] = result;
    result = graph.add(1, 2);
    results[1] = result;
    result = graph.add(2, 0);
    results[2] = result;
    result = graph.add(2, 3);
    results[3] = result;
    result = graph.add(3, 4);
    results[4] = result;
    result = graph.add(4, 5);
    results[5] = result;
    result = graph.add(5, 3);
    results[6] = result;
    result = graph.add(6, 5);
    results[7] = result;
    result = graph.add(6, 7);
    results[8] = result;
    result = graph.add(7, 8);
    results[9] = result;
    result = graph.add(8, 9);
    results[10] = result;
    result = graph.add(9, 6);
    results[11] = result;
    result = graph.add(9, 10);
    results[12] = result;
    for (i = 0; i < 13; ++i) {
        if (results[i] == -1) {
            CU_ASSERT(0);
            printf("\nFound duplicate\n");
            return;
        }
    }
    printf("\n");
    CU_ASSERT(1);
}

void testCreateF(void) {
    Graph graph(1);
    int result, i;
    int results[13];
    result = graph.add(0, 1);
    results[0] = result;
    result = graph.add(1, 2);
    results[1] = result;
    result = graph.add(2, 0);
    results[2] = result;
    result = graph.add(2, 3);
    results[3] = result;
    result = graph.add(3, 4);
    results[4] = result;
    result = graph.add(4, 5);
    results[5] = result;
    result = graph.add(5, 3);
    results[6] = result;
    result = graph.add(6, 5);
    results[7] = result;
    result = graph.add(6, 7);
    results[8] = result;
    result = graph.add(7, 8);
    results[9] = result;
    result = graph.add(8, 9);
    results[10] = result;
    result = graph.add(9, 6);
    results[11] = result;
    result = graph.add(9, 6);
    results[12] = result;
    for (i = 0; i < 13; ++i) {
        if (results[i] == -1) {
            CU_ASSERT(0);
            printf("\nFound duplicate\n");
            return;
        }
    }
    CU_ASSERT(1);
}

void testCC(void) {
    Graph graph(1);
    int result;
    graph.add(0, 1);
    graph.add(1, 2);
    graph.add(2, 0);
    graph.add(2, 3);
    graph.add(3, 4);
    graph.add(4, 5);
    graph.add(5, 3);
    graph.add(6, 5);
    graph.add(6, 7);
    graph.add(7, 8);
    graph.add(8, 9);
    graph.add(9, 6);
    graph.add(9, 10);
    printf("\nGraph done.\n");
    result = graph.createComponents();
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
    int result;
    graph.graphStatic();
    graph.add(0, 1);
    graph.add(1, 2);
    graph.add(2, 0);
    graph.add(2, 3);
    graph.add(3, 4);
    graph.add(4, 5);
    graph.add(5, 3);
    graph.add(6, 5);
    graph.add(6, 7);
    graph.add(7, 8);
    graph.add(8, 9);
    graph.add(9, 6);
    graph.add(9, 10);
    printf("\nGraph done.\n");
    result = graph.createComponents();
    printf("0 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(0)+1);
    printf("1 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(1)+1);
    printf("2 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(2)+1);
    printf("3 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(3)+1);
    printf("4 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(4)+1);
    printf("5 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(5)+1);
    printf("6 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(6)+1);
    printf("7 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(7)+1);
    printf("8 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(8)+1);
    printf("9 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(9)+1);
    printf("10 belongs to SCC %d\n", graph.get_SCC()->findNodeStronglyConnectedComponentID(10)+1);
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
    int result;
    graph.graphStatic();
    graph.add(0, 1);
    graph.add(1, 2);
    graph.add(2, 0);
    graph.add(2, 3);
    graph.add(3, 4);
    graph.add(4, 5);
    graph.add(5, 3);
    graph.add(6, 5);
    graph.add(6, 7);
    graph.add(7, 8);
    graph.add(8, 9);
    graph.add(9, 6);
    graph.add(9, 10);
    printf("\nGraph done.\n");
    graph.createComponents();
    printf("SCC done\n");
    result = graph.query(0, 1, 0, 0);
    fprintf(results_static, "%d\n", result);
    printf("%d\n", result);
    result = graph.query(3, 5, 0, 0);
    fprintf(results_static, "%d\n", result);
    printf("%d\n", result);
    result = graph.query(7, 9, 0, 0);
    fprintf(results_static, "%d\n", result);
    printf("%d\n", result);
    result = graph.query(1, 9, 0, 0);
    fprintf(results_static, "%d\n", result);
    printf("%d\n", result);
    result = graph.query(10, 1, 0, 0);
    fprintf(results_static, "%d\n", result);
    printf("%d\n", result);
    CU_ASSERT(1);
}

void testQuery2(void) {
    Graph graph(1);
    int result;
    graph.add(0, 1);
    graph.add(1, 2);
    graph.add(2, 0);
    graph.add(2, 3);
    graph.add(3, 4);
    graph.add(4, 5);
    graph.add(5, 3);
    graph.add(6, 5);
    graph.add(6, 7);
    graph.add(7, 8);
    graph.add(8, 9);
    graph.add(9, 6);
    graph.add(9, 10);
    printf("\nGraph done.\n");
    graph.createComponents();
    printf("CC done\n");
    result = graph.query(0, 1, 0, 0);
    fprintf(results_static, "%d\n", result);
    printf("%d\n", result);
    result = graph.query(3, 5, 0, 0);
    fprintf(results_static, "%d\n", result);
    printf("%d\n", result);
    result = graph.query(7, 9, 0, 0);
    fprintf(results_static, "%d\n", result);
    printf("%d\n", result);
    graph.add(10, 11);
    graph.rebuildCC();
    printf("CC rebuilded\n");
    result = graph.query(10, 11, 0, 0);
    fprintf(results_static, "%d\n", result);
    printf("%d\n", result);
    CU_ASSERT(1);
}

void testQueue(void) {
    Queue <uint32_t> q1(100);
    queue <uint32_t> q2;
    uint32_t value;
    for (value = 0; value < 20; ++value){
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
    for (value = 0; value < 20; ++value) {
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

    if ((NULL == CU_add_test(pSuite1, "Test of graph creation", testCreateP))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite1, "Test of graph creation", testCreateF))) {
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
