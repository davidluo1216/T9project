// CSE 374 
// DAVID LUO
// HW5
#include "trienode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new TrieNode
TrieNode *createNode() {
  // Allocate memory for a new TrieNode
  TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
  
  // Initialize node properties
  node->word = NULL;
  for (int i = 0; i < SIZE; i++) {
    node->children[i] = NULL;
  }
  
  return node;
}

// Function to convert a word to its T9 representation
char *wordToT9(char *word) {
  // T9 representation mapping
  static char t9[27] = "22233344455566677778889999";
  static char buffer[MAX_WORD_SIZE + 1];
  int i, len = strlen(word);

  for (i = 0; i < len; i++) {
    if (word[i] >= 'a' && word[i] <= 'z') {
      // Convert lowercase letters to T9 representation
      buffer[i] = t9[word[i] - 'a'];
    }
  }
  buffer[i] = '\0';

  return buffer;
}

// Function to insert a word into the Trie
void insert(TrieNode *root, const char *key, const char *word) {
  TrieNode *curr = root;
  for (int i = 0; key[i] != '\0'; i++) {
    int index = key[i] - ASCII_NUM_START;
    if (!curr->children[index]) {
      // If the child node does not exist, create a new node
      curr->children[index] = createNode();
    }
    curr = curr->children[index];
  }

  if (curr->word) {
    // If a word already exists, find the last '#' node and insert the new word there
    TrieNode *temp = curr;
    while (temp->children[10]) {
      temp = temp->children[10];
    }
    temp->children[10] = createNode();
    temp = temp->children[10];
    temp->word = strdup(word);
  } else {
    // Insert the word into the current node
    curr->word = strdup(word);
  }
}

// Function to search for a word in the Trie
TrieNode *search(TrieNode *root, const char *key) {
  TrieNode *curr = root;
  for (int i = 0; key[i] != '\0'; i++) {
    if (key[i] == '#') {
      // Move to the next word in the Trie
      if (!curr->children[10]) {
        printf("There are no more T9onyms\n");
        return NULL;
      }
      curr = curr->children[10];
    } else {
      int index = key[i] - ASCII_NUM_START;
      if (!curr->children[index]) {
        // Key sequence not found in the current dictionary
        printf("Not found in current dictionary.\n");
        return NULL;
      }
      curr = curr->children[index];
    }
  }

  if (curr->word) {
    // Word found in the Trie
    printf("'%s'\n", curr->word);
  } else {
    // Word not found in the Trie
    printf("Not found in current dictionary.\n");
  }

  return curr;
}

// Function to free the memory allocated for the Trie
void freeTrie(TrieNode *root) {
  if (!root)
    return;
  for (int i = 0; i < SIZE; i++) {
    if (root->children[i]) {
      // Recursively free the memory of child nodes
      freeTrie(root->children[i]);
    }
  }
  if (root->word) {
    // Free the memory of the word stored in the node
    free(root->word);
  }
  free(root);
}
