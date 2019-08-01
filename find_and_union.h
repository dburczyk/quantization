#ifndef FIND_AND_UNION_H
#define FIND_AND_UNION_H

int *set_table;
unsigned long long *energy;

int new_set();

int find_set(int s);

void union_set(int s, int t);

void initialize_find_and_union();

#endif