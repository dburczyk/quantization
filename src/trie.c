#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 4

typedef struct node node;
struct node {
  node *children[ALPHABET_SIZE];
  node *parent;
  int set_number;
  //int declaration;
};

node *root;

node *create_node() {
  node *v = malloc(sizeof(node));
  if (v == NULL) {
    exit(1);
    return v;
  }
  memset(v, 0, sizeof(node));
  return v;
}

void destroy_node(node *v) {
  if (v == NULL)return;
  for (int i = 0; i < ALPHABET_SIZE; i++)destroy_node(v->children[i]);
  free(v);
  return;
}

node *move_down(node *v, int digit) {
  if (v == NULL)return NULL;
  if (v->children[digit] == NULL) {
    v->children[digit] = create_node();
    v->children[digit]->parent = v;
    //printf("%d %d %d\n",(int)root, (int)v, (int)(v->parent));
  }
  //push_down(v);
  node *child = v->children[digit];
  if (v->set_number == 0)child->set_number = 0;
  return child;
}

void initialize_trie() {
  root = create_node();
  return;
}