#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/words.h"
#include "../include/game.h"

int main() {
    int word_count;
    char** words = load_words("wl-5lw.txt", &word_count);
    if (word_count == 0) {
        printf("Error: No valid words found in file.\n");
        return 1;
    }

    srand(time(NULL));
    int result = play_game(words, word_count);
    free_words(words, word_count);
    return result;
}
