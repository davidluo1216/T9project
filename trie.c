#include "trienode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TrieNode *createNode() {
  TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
  node->word = NULL;
  for (int i = 0; i < SIZE; i++) {
    node->children[i] = NULL;
  }
  return node;
}

char *wordToT9(char *word) {
  static char t9[27] = "22233344455566677778889999";
  static char buffer[MAX_WORD_SIZE + 1];
  int i, len = strlen(word);

  for (i = 0; i < len; i++) {
    if (word[i] >= 'a' && word[i] <= 'z') {
      buffer[i] = t9[word[i] - 'a'];
    }
  }
  buffer[i] = '\0';

  return buffer;
}

void insert(TrieNode *root, const char *key, const char *word) {
  TrieNode *curr = root;
  for (int i = 0; key[i] != '\0'; i++) {
    int index = key[i] - ASCII_NUM_START;
    if (!curr->children[index]) {
      curr->children[index] = createNode();
    }
    curr = curr->children[index];
  }

  if (curr->word) {
    TrieNode *temp = curr;
    while (temp->children[10]) {
      temp = temp->children[10];
    }
    temp->children[10] = createNode();
    temp = temp->children[10];
    temp->word = strdup(word);
  } else {
    curr->word = strdup(word);
  }
}

TrieNode *search(TrieNode *root, const char *key) {
  TrieNode *curr = root;
  for (int i = 0; key[i] != '\0'; i++) {
    if (key[i] == '#') {
      if (!curr->children[10]) {
        printf("There are no more T9onyms\n");
        return NULL;
      }
      curr = curr->children[10];
    } else {
      int index = key[i] - ASCII_NUM_START;
      if (!curr->children[index]) {
        printf("Not found in current dictionary.\n");
        return NULL;
      }
      curr = curr->children[index];
    }
  }

  if (curr->word) {
    printf("'%s'\n", curr->word);
  } else {
    printf("Not found in current dictionary.\n");
  }

  return curr;
}

void freeTrie(TrieNode *root) {
  if (!root)
    return;
  for (int i = 0; i < SIZE; i++) {
    if (root->children[i]) {
      freeTrie(root->children[i]);
    }
  }
  if (root->word) {
    free(root->word);
  }
  free(root);
}

