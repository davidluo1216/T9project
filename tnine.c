#include "trienode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_session(TrieNode *wordTrie) {
  TrieNode *curr = wordTrie;
  char key[MAX_WORD_SIZE];
  while (printf("Enter Key Sequence (or \"#\" for next word):\n> "),
         fgets(key, sizeof(key), stdin) != NULL) {
    if (strncmp(key, "exit", 4) == 0) {
      break;
    }

    // Remove trailing line char
    key[strcspn(key, "\n")] = 0;

    if (key[0] == '#') {
      if (curr->children[10]) {
        curr = curr->children[10];
        printf("'%s'\n", curr->word);
      } else {
        printf("There are no more T9onyms\n");
      }
    } else {
      curr = search(wordTrie, key);
    }
  }
}

int main(int argc, char **argv) {
  FILE *dictionary = NULL;
  TrieNode *wordTrie = NULL;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    dictionary = fopen(argv[1], "r");
    if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  // build the trie
  wordTrie = createNode();
  char word[MAX_WORD_SIZE];
  while (fgets(word, sizeof(word), dictionary)) {
    // remove trailing line char
    word[strcspn(word, "\n")] = 0;

    char *key = wordToT9(word);
    insert(wordTrie, key, word);
  }

  fclose(dictionary);

  // run interactive session
  run_session(wordTrie);

  // clean up
  freeTrie(wordTrie);

  return (EXIT_SUCCESS);
}

