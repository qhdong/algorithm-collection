#ifndef SPLIT_H_
#define SPLIT_H_

typedef struct {
    char* s;
    const char* delimiters;
    char* current;
    char* next;
    int is_ignore_empties;
} tokenizer_t;

enum { TOKENIZER_EMPTIES_OK, TOKENIZER_NO_EMPTIES };

tokenizer_t tokenizer(const char* s, const char* delimiters, int empties);
const char* free_tokenizer(tokenizer_t* tokenizer);
const char* tokenize(tokenizer_t* tokenizer);

#endif
