#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_and_union.h"
#include "trie.h"
#include "parser.h"

int main(){
    initialize_find_and_union();
    initialize_trie();
    while(parse_line() == 0);
    destroy_node(root);
    free(set_table);
    free(energy);
    return 0;
}