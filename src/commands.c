#include <stdlib.h>
#include <stdio.h> //
#include "trie.h"
#include "find_and_union.h"

void Declare(Node *history) {
  if (history == NULL)return;
  while (history != NULL) {
    if (history->set_number_ == 0)history->set_number_ = NewSet();
    //printf("%d %d %d\n",(int)root,(int)history,(int)(history->parent));
    history = history->parent_;
    //printf("%d %d\n",(int)history,(int)root);
  }
  return;
}

void RemoveHistory(Node *history) {
  if (history == NULL)return;
  history->set_number_ = 0;
  return;
}
//returns -1 if history == NULL, 1 if valid, 0 if invalid 
int Valid(Node *history) {
  if (history == NULL)return -1;
  if (history->set_number_ != 0)return 1;
  else return 0;
}

//returns 0 if unassigned energy
unsigned long long EnergyCheck(Node *history) {
  if (history == NULL)return 0;
  history->set_number_ = FindSet(history->set_number_);
  return energy[history->set_number_];
}

//assumes valid history
void EnergyAssign(Node *history, unsigned long long new_energy) {
  history->set_number_ = FindSet(history->set_number_);
  //if(history->set_number == 0)return;
  energy[history->set_number_] = new_energy;
  return;
}

//Asummes valid history_a and valid history_b.
//Returns 0 if energy of any history is assigned, 1 otherwise.
int Equal(Node *history_a, Node *history_b) {
  history_a->set_number_ = FindSet(history_a->set_number_);
  history_b->set_number_ = FindSet(history_b->set_number_);
  //if(history_a->set_number == 0 || history_b->set_number == 0)return -1;
  unsigned long long *energy_a = &(energy[history_a->set_number_]);
  unsigned long long *energy_b = &(energy[history_b->set_number_]);
  if (*energy_a == 0 && *energy_b == 0) {
    if (history_a == history_b)return 0;
    else return 1;
  } else if (*energy_a != 0 && *energy_b == 0) {
    *energy_b = *energy_a;
    UnionSet(history_a->set_number_, history_b->set_number_);
    return 0;
  } else if (*energy_a == 0 && *energy_b != 0) {
    *energy_a = *energy_b;
    UnionSet(history_a->set_number_, history_b->set_number_);
    return 0;
  } else {
    unsigned long long new_energy;
    //condition bellow checks overflow
    if (*energy_a + *energy_b < *energy_a)new_energy = ((*energy_a + *energy_b) >> 1) + (1ULL << 63);
    else new_energy = (*energy_a + *energy_b) >> 1;
    *energy_a = new_energy;
    *energy_b = new_energy;
    UnionSet(history_a->set_number_, history_b->set_number_);
    return 0;
  }
}
