//DAVID LUO
//CSE 375 HW5
#ifndef TRIENODE_H
#define TRIENODE_H

#include <stdio.h>

#define SIZE 11
#define MAX_WORD_SIZE 50
#define ASCII_NUM_START 48

// trieNode is one node in an 11-tree
typedef struct TrieNode {
  char *word;
  struct TrieNode *children[SIZE];
} TrieNode;

// Function to create a new TrieNode
TrieNode *createNode();

// Function to convert a word to its T9 representation
char *wordToT9(char *word);

// Function to insert a word into the Trie
void insert(TrieNode *root, const char *key, const char *word);

// Function to search for a word in the Trie
TrieNode *search(TrieNode *root, const char *key);

// Function to free the memory allocated for the Trie
void freeTrie(TrieNode *root);

#endif
