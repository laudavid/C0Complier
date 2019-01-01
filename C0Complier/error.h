#ifndef _ERROR_H_
#define _ERROR_H_
#include <iostream>
#include <cstdio>
#include <string>
#include <set>
#include "table.h"

using namespace std;

extern bool noerror;

void error(int n);
void skip(set<symbol> s);
void skip2(set<symbol> s1, set<symbol> s2);

#endif // !_ERROR_H_
