#ifndef _DFA_H
#define _DFA_H

typedef enum {
    START,
    DIGIT,
    OP,
    L,
    R,
    ERROR
} State;

typedef struct {
    char value[20];
    int id;
}Token;

Token token[100];

int Isdigit(char ch);
State DFA(char* input);
void analays(char* p, State current);

#endif