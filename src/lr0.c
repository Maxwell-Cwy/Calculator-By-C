#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfa.h"
#include "lr0.h"

Token* t = token;


int lr0Table[22][13]={
    0  ,0  ,0  ,0  ,S4 ,0  ,S5 ,0  ,1  ,2  ,3  ,0  ,0  ,
    0  ,0  ,0  ,0  ,0  ,0  ,0  ,acc,0  ,0  ,0  ,0  ,0  ,
    S6 ,S7 ,0  ,0  ,0  ,0  ,0  ,R4 ,0  ,0  ,0  ,8  ,0  ,
    0  ,0  ,S9 ,S10,0  ,0  ,0  ,R8 ,0  ,0  ,0  ,0  ,11 ,
    0  ,0  ,0  ,0  ,S4 ,0  ,S5 ,0  ,12 ,2  ,3  ,0  ,0  ,
    R10,R10,R10,R10,R10,R10,0  ,R10,0  ,0  ,0  ,0  ,0  ,
    0  ,0  ,0  ,0  ,S4 ,0  ,S5 ,0  ,0  ,13 ,3  ,0  ,0  ,
    0  ,0  ,0  ,0  ,S4 ,0  ,S5 ,0  ,0  ,14 ,3  ,0  ,0  ,
    R1 ,R1 ,R1 ,R1 ,R1 ,R1 ,0  ,R1 ,0  ,0  ,0  ,0  ,0  ,
    0  ,0  ,0  ,0  ,S4 ,0  ,S5 ,0  ,0  ,0  ,15 ,0  ,0  ,
    0  ,0  ,0  ,0  ,S4 ,0  ,S5 ,0  ,0  ,0  ,16 ,0  ,0  ,
    R5 ,R5 ,R5 ,R5 ,R5 ,R5 ,0  ,R5 ,0  ,0  ,0  ,0  ,0  ,
    0  ,0  ,0  ,0  ,0  ,S21,0  ,0  ,0  ,0  ,0  ,0  ,0  ,
    S6 ,S7 ,0  ,0  ,0  ,0  ,0  ,R4 ,0  ,0  ,0  ,17 ,0  ,
    S6 ,S7 ,0  ,0  ,0  ,0  ,0  ,R4 ,0  ,0  ,0  ,18 ,0  ,
    0  ,0  ,S9 ,S10,0  ,0  ,0  ,R8 ,0  ,0  ,0  ,0  ,19 ,
    0  ,0  ,S10,S10,0  ,0  ,0  ,R8 ,0  ,0  ,0  ,0  ,20 ,
    R2 ,R2 ,R2 ,R2 ,R2 ,R2 ,0  ,R2 ,0  ,0  ,0  ,0  ,0  ,
    R3 ,R3 ,R3 ,R3 ,R3 ,R3 ,0  ,R3 ,0  ,0  ,0  ,0  ,0  ,
    R6 ,R6 ,R6 ,R6 ,R6 ,R6 ,0  ,R6 ,0  ,0  ,0  ,0  ,0  ,
    R7 ,R7 ,R7 ,R7 ,R7 ,R7 ,0  ,R7 ,0  ,0  ,0  ,0  ,0  ,
    R9 ,R9 ,R9 ,R9 ,R9 ,R9 ,0  ,R9 ,0  ,0  ,0  ,0  ,0  ,
    };

void stackInit(Stack *stack) {
    stack->symbol = (char **)malloc(sizeof(char *) * MAX_STACK_SIZE);
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        stack->symbol[i] = (char *)malloc(sizeof(char) * 10);  // 为每个符号分配内存
    }
    stack->top = -1;
}

void stackPush(Stack *stack, char *val) {
    stack->top=stack->top+1;
    strcpy(stack->symbol[stack->top], val);
}

char* stackPop(Stack *stack) {
    char* retVal;
    retVal=(char*)malloc(sizeof(char)*5);
    strcpy(retVal,stack->symbol[stack->top]);
    stack->top = stack->top-1;
    return retVal;
}

int stackIsEmpty(Stack *stack) {
    return stack->top == -1;
}


char* stackPeek(Stack *stack) {
    return stack->symbol[stack->top];
}



/*
S' -> E         { print(E.val); }
E -> T E'       { E.val = E'.val; }
E' -> + T E1'   { E'.val = E.val + T.val; }
E' -> - T E1'   { E'.val = E.val - T.val; }
E' -> ε         { E'.val = E.val; }
T -> F T'       { T.val = T'.val; }
T' -> * F T1'   { T'.val = T.val * F.val; }
T' -> / F T1'   { T'.val = T.val / F.val; }
T' -> ε         { T'.val = T.val; }
F -> ( E )      { F.val = E.val; }
F -> num        { F.val = num.val; }
*/

void lr0Run(){
    char str[5];
    int i=0;
    Stack stateStack,symbolStack;
    char *currentState=NULL;
    char *currentSymbol=NULL;
    char *currentToken=NULL;
    int stateIndex = 0;
    int symbolIndex = 0;
    int ruleNum=0;
    char chBuf[5];
    float fVal,eVal,ePVal,tVal,tPVal;

    sprintf(str, "%d", 0);
    stackInit(&stateStack);
    stackInit(&symbolStack);
    stackPush(&stateStack,str);
    stackPush(&symbolStack,"$");
    
    t=token;

    for(i=0;t->id==1||t->id==2||t->id==3||t->id==4;i++){
        t++;
    }    
    t->id=5;
    strcpy(t->value,"$");
    
    t=token;

    currentState = stackPeek(&stateStack);
    currentSymbol = stackPeek(&symbolStack);
    currentToken = t->value;

    while(!(strcmp(currentState, "22") == 0)){
        currentState = stackPeek(&stateStack);
        currentSymbol = stackPeek(&symbolStack);
        currentToken = t->value;

        if(stateStack.top==symbolStack.top){//两个栈高度相同
            stateIndex=atoi(currentState);
            if (strcmp(currentToken, "+") == 0) symbolIndex = 0;
            else if (strcmp(currentToken, "-") == 0) symbolIndex = 1;
            else if (strcmp(currentToken, "*") == 0) symbolIndex = 2;
            else if (strcmp(currentToken, "/") == 0) symbolIndex = 3;
            else if (strcmp(currentToken, "(") == 0) symbolIndex = 4;
            else if (strcmp(currentToken, ")") == 0) symbolIndex = 5;        
            else if (strcmp(currentToken, "$") == 0) symbolIndex = 7; 
            else {symbolIndex=6;}

            if((lr0Table[stateIndex][symbolIndex]<=acc)&&(lr0Table[stateIndex][symbolIndex]>=S0)){//移入转移
                sprintf(str, "%d", lr0Table[stateIndex][symbolIndex]-S0);
                stackPush(&stateStack,str);
                stackPush(&symbolStack,t->value);
                printf("stateStackTop:%s\n",stateStack.symbol[stateStack.top]);
                printf("symbolStackTop:%s\n",symbolStack.symbol[symbolStack.top]);
                t=t+1;
            }
            else{//规约
                if((lr0Table[stateIndex][symbolIndex]<=R10)&&(lr0Table[stateIndex][symbolIndex]>=R0)){
                    ruleNum=lr0Table[stateIndex][symbolIndex]-R0;
                    switch(ruleNum){
                        case 0://S'->E
                            stackPop(&stateStack);
                            stackPop(&symbolStack);       
                            stackPush(&symbolStack,"S'");   
                            break;
                        case 1://E->TE'
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"E");

                            //printf("result:%f\n",eVal);
                            break;
                        case 2://E'->+TE'
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"E'");
                      
                            break;
                        case 3://E'->-TE'
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"E'");
                     
                            break;
                        case 4://E'->
                            stackPush(&symbolStack,"E'");
                            printf("stateStackTop:%s\n",stateStack.symbol[stateStack.top]);
                            printf("symbolStackTop:%s\n",symbolStack.symbol[symbolStack.top]);  
                            break;
                        case 5://T->FT'
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"T");
                   
                            break;
                        case 6://T'->*FT'
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"T'");
                            break;
                        case 7://T'->/FT'
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"T'");
                            break;
                        case 8://T'->
                            stackPush(&symbolStack,"T'");
                            break;
                        case 9://F->(E)
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"F");
                        
                            break;
                        case 10://F->num
                            stackPop(&stateStack);
                            strcpy(chBuf,stackPop(&symbolStack));
                            stackPush(&symbolStack,"F");
                            break;
                    }
                    printf("stateStackTop:%s\n",stateStack.symbol[stateStack.top]);
                    printf("symbolStackTop:%s\n",symbolStack.symbol[symbolStack.top]);  
                }
                else{
                    if(strcmp(currentSymbol, "F") == 0){
                        stackPush(&symbolStack,"T'");
                    }
                    else{
                        if(strcmp(currentSymbol, "T") == 0){
                            stackPush(&symbolStack,"E'");
                        }
                        else{
                            if(!(strcmp(currentState, "22") == 0)){
                                printf("analyze erro!\n");
                            }
                        }
                    }
                }
            }   

        }    
        else{//转移//两个栈高度不同
            stateIndex=atoi(currentState);
            if (strcmp(currentSymbol, "E") == 0) symbolIndex = 8;   
            else if (strcmp(currentSymbol, "T") == 0) symbolIndex = 9;   
            else if (strcmp(currentSymbol, "F") == 0) symbolIndex = 10;   
            else if (strcmp(currentSymbol, "E'") == 0) symbolIndex = 11;   
            else if (strcmp(currentSymbol, "T'") == 0) symbolIndex = 12;   
            sprintf(str, "%d", lr0Table[stateIndex][symbolIndex]);

            stackPush(&stateStack,str);
            printf("stateStackTop:%s\n",stateStack.symbol[stateStack.top]);
            printf("symbolStackTop:%s\n",symbolStack.symbol[symbolStack.top]); 
        }

    }
    printf("result:%f\n",eVal);
    printf("success\n");

}