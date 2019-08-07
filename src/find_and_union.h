#ifndef FIND_AND_UNION_H_
#define FIND_AND_UNION_H_

int *set_table;
unsigned long long *energy;

int NewSet();

int FindSet(int s);

void UnionSet(int s, int t);

void InitializeFindAndUnion();

#endif