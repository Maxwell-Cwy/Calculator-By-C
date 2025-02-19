#ifndef _LR0_H
#define _LR0_H


#define S0 22
#define S1 23
#define S2 24
#define S3 25
#define S4 26 
#define S5 27
#define S6 28
#define S7 29
#define S8 30
#define S9 31
#define S10 32
#define S11 33
#define S12 34 
#define S13 35
#define S14 36
#define S15 37
#define S16 38
#define S17 39
#define S18 40
#define S19 41
#define S20 42
#define S21 43
#define acc 44
#define R0 45
#define R1 46
#define R2 47
#define R3 48
#define R4 49
#define R5 50
#define R6 51
#define R7 52
#define R8 53
#define R9 54
#define R10 55


#define MAX_STACK_SIZE 50

typedef struct {
    char **symbol;
    int top;
} Stack;

void lr0Run();
#endif