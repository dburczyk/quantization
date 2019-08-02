#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 4

typedef struct node node;
struct node {
  node *children[ALPHABET_SIZE];
  node *parent;
  int set_number;
};

node *root;

node *create_node();

void destroy_node(node *v);

node *move_down(node *v, int digit);

void initialize_trie();

#endif