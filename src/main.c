#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_and_union.h"
#include "trie.h"
#include "parser.h"

int main() {
  InitializeFindAndUnion();
  InitializeTrie();
  while (ParseLine() == 0);
  DestroyNode(root);
  free(set_table);
  free(energy);
  return 0;
}