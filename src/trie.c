#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 4

typedef struct Node Node;
struct Node {
  Node *children_[ALPHABET_SIZE];
  Node *parent_;
  int set_number_;
  //int declaration;
};

Node *root;

Node *CreateNode() {
  Node *v = malloc(sizeof(Node));
  if (v == NULL) {
    exit(1);
    return v;
  }
  memset(v, 0, sizeof(Node));
  return v;
}

void DestroyNode(Node *v) {
  if (v == NULL)return;
  for (int i = 0; i < ALPHABET_SIZE; i++)DestroyNode(v->children_[i]);
  free(v);
  return;
}

Node *MoveDown(Node *v, int digit) {
  if (v == NULL)return NULL;
  if (v->children_[digit] == NULL) {
    v->children_[digit] = CreateNode();
    v->children_[digit]->parent_ = v;
    //printf("%d %d %d\n",(int)root, (int)v, (int)(v->parent));
  }
  //push_down(v);
  Node *child = v->children_[digit];
  if (v->set_number_ == 0)child->set_number_ = 0;
  return child;
}

void InitializeTrie() {
  root = CreateNode();
  return;
}