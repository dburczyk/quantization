#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "trie.h"

void Declare(Node *history);

void RemoveHistory(Node *history);

//returns -1 if history == NULL, 1 if valid, 0 if invalid 
int Valid(Node *history);

//returns 0 if unassigned energy
unsigned long long EnergyCheck(Node *history);

//assumes valid history
void EnergyAssign(Node *history, unsigned long long new_energy);

//Asummes valid history_a and valid history_b.
//Returns 0 if energy of any history is assigned, 1 otherwise.
int Equal(Node *history_a, Node *history_b);

#endif