#include <stdlib.h>

int *set_table;
unsigned long long *energy;
int set_table_size = 4;
int unused_set_id = 1;

int NewSet() {
  if (unused_set_id == set_table_size) {
    set_table_size *= 2;
    set_table = realloc(set_table, set_table_size * sizeof(int));
    energy = realloc(energy, set_table_size * sizeof(unsigned long long));
    if (set_table == NULL || energy == NULL) {
      exit(1);
      return 0;
    }
  }
  set_table[unused_set_id] = 0;
  energy[unused_set_id] = 0; //energy = 0 means it is unassigned
  unused_set_id++;
  return unused_set_id - 1;
}

int FindSet(int s) {
  if (set_table[s] == 0)return s;
  set_table[s] = FindSet(set_table[s]);
  return set_table[s];
}

void UnionSet(int s, int t) {
  s = FindSet(s);
  t = FindSet(t);
  if (s != 0 && t != 0 && s != t)set_table[s] = t;
  return;
}

void InitializeFindAndUnion() {
  energy = malloc(set_table_size * sizeof(unsigned long long));
  set_table = malloc(set_table_size * sizeof(unsigned long long));
  if (set_table == NULL || energy == NULL) {
    exit(1);
    return;
  }
  set_table[0] = 0;
  energy[0] = 0;
  return;
}