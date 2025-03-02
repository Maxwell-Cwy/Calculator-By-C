#include "parse.h"
#include "dfa.h"
#include <stdlib.h>
#include <stdio.h>
Token* t = token;

int expr() {
    int result_e, t1;
    t1 = term();
    result_e = expr_p(t1);
    return result_e;
}

int expr_p(int temp) {//A(+B)(+C)
    int result_ep, t1, t2;
    if (t->id == 2 && t->value[0] == '+') {
        t++;
        t1 = term();
        t2 = temp + t1;
        result_ep = expr_p(t2);
        return result_ep;
    }
    if (t->id == 2 && t->value[0] == '-') {
        t++;
        t1 = term();
        t2 = temp - t1;
        result_ep = expr_p(t2);
        return result_ep;
    }
    else {
        result_ep = temp;
        return result_ep;
    }
}

int term() {//A(*B)
    int result_t, t1;
    t1 = factor();
    result_t = term_p(t1);
    return result_t;
}

int term_p(int temp) {//A*B(*C)
    int result_tp, t1;
    if (t->id == 2 && t->value[0] == '*') {
        t++;
        t1 = temp * factor();
        result_tp = term_p(t1);
        return result_tp;
    }

    if (t->id == 2 && t->value[0] == '/') {
        t++;
        t1 = temp / factor();
        result_tp = term_p(t1);
        return result_tp;
    }

    else {
        result_tp = temp;
        return result_tp;
    }
}

int factor() {
    int result_f;
    if (t->id == 1) {
        result_f = atoi(t->value);//识别出数字字符
        t++;
        return result_f;
    }
    if (t->id == 3) {//识别出左括号字符
        t++;
        result_f = expr();//识别出表达式，指针+1;
        if (t->id == 4) //识别出右括号字符
            t++;
        return result_f;
    }
    else {
        printf("parse error!\n");
        exit(1);
    }
}