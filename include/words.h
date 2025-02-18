#ifndef WORDS_H
#define WORDS_H

char** load_words(const char* filename, int* word_count);
void free_words(char** words, int word_count);
int binary_search(char* arr[], int size, char* target);

#endif
