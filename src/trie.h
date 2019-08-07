#ifndef TRIE_H_
#define TRIE_H_

#define ALPHABET_SIZE 4

typedef struct Node Node;
struct Node {
  Node *children_[ALPHABET_SIZE];
  Node *parent_;
  int set_number_;
};

Node *root;

Node *CreateNode();

void DestroyNode(Node *v);

Node *MoveDown(Node *v, int digit);

void InitializeTrie();

#endif