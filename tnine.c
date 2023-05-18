// David Luo
// CSE 374 HW5

#include "trienode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to run the interactive session
void run_session(TrieNode *wordTrie) {
  TrieNode *curr = wordTrie;
  char key[MAX_WORD_SIZE];

  // Interactive session loop
  while (printf("Enter Key Sequence (or \"#\" for next word):\n> "),
         fgets(key, sizeof(key), stdin) != NULL) {
    if (strncmp(key, "exit", 4) == 0) {
      break;
    }

    // Remove trailing newline character
    key[strcspn(key, "\n")] = 0;

    if (key[0] == '#') {
      // If "#" is entered, move to the next word in the Trie
      if (curr->children[10]) {
        curr = curr->children[10];
        printf("'%s'\n", curr->word);
      } else {
        printf("There are no more T9onyms\n");
      }
    } else {
      // Search for the key sequence in the Trie
      curr = search(wordTrie, key);
    }
  }
}

int main(int argc, char **argv) {
  FILE *dictionary = NULL;
  TrieNode *wordTrie = NULL;

  if (argc < 2) {
    // Check if the dictionary file is provided as an argument
    fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    // Open the dictionary file
    dictionary = fopen(argv[1], "r");
    if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  // Build the trie
  wordTrie = createNode();
  char word[MAX_WORD_SIZE];
  while (fgets(word, sizeof(word), dictionary)) {
    // Remove trailing newline character
    word[strcspn(word, "\n")] = 0;

    // Convert the word to its T9 representation
    char *key = wordToT9(word);

    // Insert the word into the trie
    insert(wordTrie, key, word);
  }

  fclose(dictionary);

  // Run interactive session
  run_session(wordTrie);

  // Clean up the trie
  freeTrie(wordTrie);

  return (EXIT_SUCCESS);
}
