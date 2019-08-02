#include <stdlib.h>
#include <stdio.h> //
#include "trie.h"
#include "find_and_union.h"

void declare(node *history){
    if(history == NULL)return;
    while(history != NULL){
        if(history->set_number == 0)history->set_number = new_set();
        //printf("%d %d %d\n",(int)root,(int)history,(int)(history->parent));
        history = history->parent;
        //printf("%d %d\n",(int)history,(int)root);
    }
    return;
}

void remove_history(node *history){
    if(history == NULL)return;
    history->set_number = 0;
    return;
}
//returns -1 if history == NULL, 1 if valid, 0 if invalid 
int valid(node *history){
    if(history == NULL)return -1;
    if(history->set_number != 0)return 1;
    else return 0;
}

//returns 0 if unassigned energy
unsigned long long energy_check(node *history){
    if(history == NULL)return 0;
    history->set_number = find_set(history->set_number);
    return energy[history->set_number];
}

//assumes valid history
void energy_assign(node *history, unsigned long long new_energy){
    history->set_number = find_set(history->set_number);
    //if(history->set_number == 0)return;
    energy[history->set_number] = new_energy;
    return;
}

//Asummes valid history_a and valid history_b.
//Returns 0 if energy of any history is assigned, 1 otherwise.
int equal(node *history_a, node *history_b){
    history_a->set_number = find_set(history_a->set_number);
    history_b->set_number = find_set(history_b->set_number);
    //if(history_a->set_number == 0 || history_b->set_number == 0)return -1;
    unsigned long long *energy_a = &(energy[history_a->set_number]);
    unsigned long long *energy_b = &(energy[history_b->set_number]);
    if(*energy_a == 0 && *energy_b == 0){
        if(history_a == history_b)return 0;
        else return 1;
    }
    else if(*energy_a != 0 && *energy_b == 0){
        *energy_b = *energy_a;
        union_set(history_a->set_number, history_b->set_number);
        return 0;
    }
    else if(*energy_a == 0 && *energy_b != 0){
        *energy_a = *energy_b;
        union_set(history_a->set_number, history_b->set_number);
        return 0;
    }
    else{
        unsigned long long new_energy;
        //condition bellow checks overflow
        if(*energy_a + *energy_b < *energy_a)new_energy = ((*energy_a + *energy_b)>>1) + (1ULL << 63);
        else new_energy = (*energy_a + *energy_b)>>1;
        *energy_a = new_energy;
        *energy_b = new_energy;
        union_set(history_a->set_number, history_b->set_number);
        return 0;
    }
}
