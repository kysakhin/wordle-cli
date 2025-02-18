#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "../include/game.h"
#include "../include/api.h"
#include "../include/constants.h"
#include "../include/words.h"
#include "../include/utils.h"

void print_guess_result(const char *target, const char *guess)
{
  int letter_counts[26] = {0};
  for (int i = 0; i<WORD_LENGTH; i++) letter_counts[target[i] - 'a']++;

  for (int i = 0; i < WORD_LENGTH; i++)
  {
    if (guess[i] == target[i])
    {
      printf(GREEN "%c" RESET, guess[i]);
      letter_counts[guess[i] - 'a']--;
    } else {
      printf("_");
    }
  }

  printf(" ");

  for (int i = 0; i < WORD_LENGTH; i++)
  {
    if (guess[i] == target[i]) printf(" ");
    else if (letter_counts[guess[i] - 'a'] > 0) 
    {
    printf(YELLOW "%c" RESET, guess[i]);
    letter_counts[guess[i] - 'a']--;
  } else printf("%c", guess[i]);
  }
  printf("\n");
}

int play_game(char** words, int word_count) {
  srand(time(NULL));
  char guess[WORD_LENGTH + 1];
  char buffer[100];
  int attempts = 0;

  char* target_word = fetch_word_from_api();
  if (!target_word) {
    target_word = words[rand() % word_count];
    printf("(Using random word as fallback)\n");
  }

  clear_screen();
  printf("Welcome to Wordle!\n");
  printf("You have %d attempts to guess the %d-letter word.\n", MAX_ATTEMPTS, WORD_LENGTH);

  while (attempts < MAX_ATTEMPTS) {
    printf("\nAttempt %d/%d\n", attempts + 1, MAX_ATTEMPTS);

    while (1) {
      if (fgets(buffer, sizeof(buffer), stdin)) {
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == WORD_LENGTH) {
          strcpy(guess, buffer);
          break;
        } else {
          printf("Please enter a %d-letter word\n", WORD_LENGTH);
        }
      }
    }

    for (int i = 0; guess[i]; i++) guess[i] = tolower(guess[i]);
    if (strlen(guess) != WORD_LENGTH) {
      printf("Please enter a %d-letter word\n", WORD_LENGTH);
      continue;
    }

    else if (binary_search(words, word_count, guess) == -1) {
      printf("Not a valid word.\n");
      continue;
    }

    attempts++;
    print_guess_result(target_word, guess);
    if (strcmp(guess, target_word) == 0) {
      printf("\nCongratulations! You won!\n");
      return 0;
    }
  }

  printf("\nGame Over! The word was: %s\n", target_word);
  return 1;
}
