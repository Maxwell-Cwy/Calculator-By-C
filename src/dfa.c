#define _CRT_SECURE_NO_WARNINGS 1

#include "dfa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char chbuf[100];
int count = 0;
int num = 0;

int Isdigit(char ch) {
    if (ch < 58 && ch>47) {
        return 1;
    }
    else {
        return 0;
    }
}

State DFA(char* input) {
    if (Isdigit(*input)) {
        chbuf[count] = *input;
        count++;
        return DIGIT;
    }
    if ((*input) == '(') {
        chbuf[count] = *input;
        count++;
        return L;
    }

    if ((*input) == ')') {
        chbuf[count] = *input;
        count++;
        return R;
    }
    if (*input == '+' || *input == '-' || *input == '*' || *input == '/' || *input == '\0') {
        chbuf[count] = *input;
        count++;
        return OP;
    }
    else {
        return ERROR;
    }

}


void analays(char* p, State current) {
    int i;
    num=0;
    for (i = 0; *p != '\0'; i++) {
        current = DFA(p);
        if (current == DIGIT && (!Isdigit(*(p + 1)))) {
            printf("digit:%s\n", chbuf);
            strcpy(token[num].value, chbuf);
            token[num].id = 1;
            num++;
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
        }
        if (current == OP) {
            printf("OP:%s\n", chbuf);
            strcpy(token[num].value, chbuf);
            token[num].id = 2;
            num++;
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
        }
        if (current == L) {
            printf("L:%s\n", chbuf);
            strcpy(token[num].value, chbuf);
            token[num].id = 3;
            num++;
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
        }
        if (current == R) {
            printf("R:%s\n", chbuf);
            strcpy(token[num].value, chbuf);
            token[num].id = 4;
            num++;
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
        }
        if (current == ERROR) {
            printf("invalid char!\n");
            memset(chbuf, 0, sizeof(chbuf));
            count = 0;
            exit(1);
            break;
        }
        p++;
    }
}