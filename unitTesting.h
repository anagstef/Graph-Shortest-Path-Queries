#ifndef UNITTESTING_H
#define UNITTESTING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include "list_node.h"
#include "Graph.h"
#include "JobScheduler.h"
#include "StaticQueryJob.h"
#include "DynamicQueryJob.h"
#include "Templates.h"

#include "CUnit/Basic.h"

int initSuite(void);
int cleanSuite(void);
void testQueue(void);
void testStack(void);
void testCreateP(void);
void testCreateF(void);
void testQuery1(void);
void testQuery2(void);
void testCC(void);
void testSCC(void);

#endif
