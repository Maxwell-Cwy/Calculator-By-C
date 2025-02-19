#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dfa.h"
#include "parse.h"
#include "lr0.h"

int main() {
    char expression[100];
    int result = 0;
    int back = 0;
    while (1) {
        State current = START;
        printf("**********四则计算器**********\n");
        printf("请输入一个四则运算表达式:");
        scanf("%s", expression);
        analays(expression, current);
        lr0Run();
        printf("按1返回:");
        scanf("%d", &back);
        if (back == 1) {
            system("cls\n");
        }
        memset(token, 0, sizeof(token));
        memset(expression, 0, sizeof(expression));
   }
}