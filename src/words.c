#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/words.h"
#include "../include/constants.h"

char** load_words(const char* filename, int *word_count)
{
  FILE* file = fopen(filename, "r");
  if (!file)
  {
    printf("File %s not found\n", filename);
    exit(1);
  }

  char** words = malloc(MAX_WORDS * sizeof(char *));
  char buffer[100];
  *word_count = 0;

  while (fgets(buffer, 100, file) && *word_count < MAX_WORDS)
  {
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) != WORD_LENGTH) continue;

    words[*word_count] = malloc(WORD_LENGTH + 1);
    strcpy(words[*word_count], buffer);

    for (int i = 0; words[*word_count][i]; i++)
      words[*word_count][i] = tolower(words[*word_count][i]);
    (*word_count)++;
  }

  fclose(file);
  return words;
}

void free_words(char** words, int word_count)
{
  for (int i = 0; i < word_count; i++)
    free(words[i]);
  free(words);
}


int binary_search(char **arr, int size, char *target)
{
  int low = 0, high = size - 1;
  while (low <= high)
  {
    int mid = (low+high)/2;
    int cmp = strcmp(arr[mid], target);
    if (cmp == 0) return mid;
    if (cmp < 0) low = mid + 1;
    else high = mid - 1;
  }
  return -1;
}
