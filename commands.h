#ifndef COMMANDS_H
#define COMMANDS_H

#include "trie.h"

void declare(node *history);

void remove_history(node *history);

//returns -1 if history == NULL, 1 if valid, 0 if invalid 
int valid(node *history);

//returns 0 if unassigned energy
unsigned long long energy_check(node *history);

//assumes valid history
void energy_assign(node *history, unsigned long long new_energy);

//Asummes valid history_a and valid history_b.
//Returns 0 if energy of any history is assigned, 1 otherwise.
int equal(node *history_a, node *history_b);

#endif