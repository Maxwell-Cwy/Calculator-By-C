#ifndef _SLR_H
#define _SLR_H


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
#define acc 39
#define R0 40
#define R1 41
#define R2 42
#define R3 43
#define R4 44
#define R5 45
#define R6 46
#define R7 47
#define R8 48
#define R9 49


#define MAX_STACK_SIZE 50

typedef struct {
    char **symbol;
    int top;
} Stack;

void slrRun();
#endif