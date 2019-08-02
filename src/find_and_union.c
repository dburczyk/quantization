#include <stdlib.h>

int *set_table;
unsigned long long *energy;
int set_table_size = 4;
int unuset_set_id = 1;

int new_set() {
  if (unuset_set_id == set_table_size) {
    set_table_size *= 2;
    set_table = realloc(set_table, set_table_size * sizeof(int));
    energy = realloc(energy, set_table_size * sizeof(unsigned long long));
    if (set_table == NULL || energy == NULL) {
      exit(1);
      return 0;
    }
  }
  set_table[unuset_set_id] = 0;
  energy[unuset_set_id] = 0; //energy = 0 means it is unassigned
  unuset_set_id++;
  return unuset_set_id - 1;
}

int find_set(int s) {
  if (set_table[s] == 0)return s;
  set_table[s] = find_set(set_table[s]);
  return set_table[s];
}

void union_set(int s, int t) {
  s = find_set(s);
  t = find_set(t);
  if (s != 0 && t != 0 && s != t)set_table[s] = t;
  return;
}

void initialize_find_and_union() {
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