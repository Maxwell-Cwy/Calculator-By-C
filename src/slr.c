#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfa.h"
#include "slr.h"

Token* t = token;

int controlPrint=0;


int lr0Table[17][12]={
    S4 ,0  ,0  ,0  ,0  ,S5 ,0  ,0  ,16 ,1  ,2  ,3  ,
    0  ,S6 ,S7 ,0  ,0  ,0  ,0  ,R1 ,0  ,0  ,0  ,0  ,
    0  ,R4 ,R4 ,S10,S11,0  ,R4 ,R4 ,0  ,0  ,0  ,0  ,
    0  ,R7 ,R7 ,R7 ,R7 ,0  ,R7 ,R7 ,0  ,0  ,0  ,0  ,
    0  ,R8 ,R8 ,R8 ,R8 ,0  ,R8 ,R8 ,0  ,0  ,0  ,0  ,
    S4 ,0  ,0  ,0  ,0  ,S5 ,0  ,0  ,0  ,14 ,2  ,3  ,
    S4 ,0  ,0  ,0  ,0  ,S5 ,0  ,0  ,0  ,0  ,8  ,3  ,
    S4 ,0  ,0  ,0  ,0  ,S5 ,0  ,0  ,0  ,0  ,9  ,3  ,
    0  ,R2 ,R2 ,S10,S11,0  ,R2 ,R2 ,0  ,0  ,0  ,0  ,
    0  ,R3 ,R3 ,S10,S11,0  ,R3 ,R3 ,0  ,0  ,0  ,0  ,
    S4 ,0  ,0  ,0  ,0  ,S5 ,0  ,0  ,0  ,0  ,0  ,12 ,
    S4 ,0  ,0  ,0  ,0  ,S5 ,0  ,0  ,0  ,0  ,0  ,13 ,
    0  ,R5 ,R5 ,R5 ,R5 ,0  ,R5 ,R5 ,0  ,0  ,0  ,0  ,
    0  ,R6 ,R6 ,R6 ,R6 ,0  ,R6 ,R6 ,0  ,0  ,0  ,0  ,
    0  ,S6 ,S7 ,0  ,0  ,0  ,S15,0  ,0  ,0  ,0  ,0  ,
    0  ,R9 ,R9 ,R9 ,R9 ,0  ,R9 ,R9 ,0  ,0  ,0  ,0  ,
    0  ,0  ,0  ,0  ,0  ,0  ,0  ,acc,0  ,0  ,0  ,0  ,
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
S -> E        
E -> E + T       
E -> E - T 
E -> T         
T -> T * F      
T -> T / F
T ->  F    
F -> num   
F -> ( E )        
*/

void slrRun(){
    char str[5];
    int i=0;
    Stack stateStack,symbolStack,valueStack;
    char *currentState=NULL;
    char *currentSymbol=NULL;
    char *currentToken=NULL;
    int stateIndex = 0;
    int symbolIndex = 0;
    int ruleNum=0;
    float result=0;
    char chBuf[5],chBuf2[5],chBuf3[5];
    float buf1,buf2,buf3;
    sprintf(str, "%d", 0);
    stackInit(&stateStack);
    stackInit(&symbolStack);
    stackInit(&valueStack);
    stackPush(&stateStack,str);
    stackPush(&symbolStack,"$");
    stackPush(&valueStack,"$");
    
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

    while(!(strcmp(currentState, "17") == 0)){
        currentState = stackPeek(&stateStack);
        currentSymbol = stackPeek(&symbolStack);
        currentToken = t->value;

        if(stateStack.top==symbolStack.top){//两个栈高度相同
            stateIndex=atoi(currentState);
            if (strcmp(currentToken, "+") == 0) symbolIndex = 1;
            else if (strcmp(currentToken, "-") == 0) symbolIndex = 2;
            else if (strcmp(currentToken, "*") == 0) symbolIndex = 3;
            else if (strcmp(currentToken, "/") == 0) symbolIndex = 4;
            else if (strcmp(currentToken, "(") == 0) symbolIndex = 5;
            else if (strcmp(currentToken, ")") == 0) symbolIndex = 6;        
            else if (strcmp(currentToken, "$") == 0) symbolIndex = 7; 
            else {symbolIndex=0;}

            if((lr0Table[stateIndex][symbolIndex]<=acc)&&(lr0Table[stateIndex][symbolIndex]>=S0)){//移入转移
                sprintf(str, "%d", lr0Table[stateIndex][symbolIndex]-S0);
                stackPush(&stateStack,str);
                stackPush(&symbolStack,t->value);
                
                if( (strcmp(currentToken, "+") != 0)&&(strcmp(currentToken, "-") != 0)&&
                    (strcmp(currentToken, "*") != 0)&&(strcmp(currentToken, "/") != 0)&&
                    (strcmp(currentToken, "(") != 0)&&(strcmp(currentToken, ")") != 0)&&
                    (strcmp(currentToken, "$") != 0)  ){ 
                    stackPush(&valueStack,t->value);
                }
                else{
                    stackPush(&valueStack,"$");
                }
                if(controlPrint==1){
                    printf("stateStackTop:%s\n",stateStack.symbol[stateStack.top]);
                    printf("symbolStackTop:%s\n",symbolStack.symbol[symbolStack.top]);  
                }
                t=t+1;
            }
            else{//规约
                if((lr0Table[stateIndex][symbolIndex]<=R9)&&(lr0Table[stateIndex][symbolIndex]>=R0)){
                    ruleNum=lr0Table[stateIndex][symbolIndex]-R0;
                    switch(ruleNum){
                        case 1://S -> E
                            stackPop(&stateStack);
                            stackPop(&symbolStack);       
                            stackPush(&symbolStack,"S");   
                            result=atof(valueStack.symbol[valueStack.top]);
                            break;
                        case 2://E -> E + T 
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"E");

                            buf1=atof(valueStack.symbol[valueStack.top]);
                            buf3=atof(valueStack.symbol[valueStack.top-2]);
                            buf3=buf1+buf3;
                            sprintf(valueStack.symbol[valueStack.top-2], "%f", buf3);
                            valueStack.top=valueStack.top-2;

                            break;
                        case 3://E -> E - T
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"E");

                            buf1=atof(valueStack.symbol[valueStack.top]);
                            buf3=atof(valueStack.symbol[valueStack.top-2]);
                            buf3=buf1-buf3;
                            sprintf(valueStack.symbol[valueStack.top-2], "%f", buf3);
                            valueStack.top=valueStack.top-2;

                            break;
                        case 4://E -> T
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"E");
                            break;
                        case 5://T->T*F
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"T");

                            buf1=atof(valueStack.symbol[valueStack.top]);
                            buf3=atof(valueStack.symbol[valueStack.top-2]);
                            buf3=buf1*buf3;
                            sprintf(valueStack.symbol[valueStack.top-2], "%f", buf3);
                            valueStack.top=valueStack.top-2;

                            break;
                        case 6://T->/F/T
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"T");

                            buf1=atof(valueStack.symbol[valueStack.top]);
                            buf3=atof(valueStack.symbol[valueStack.top-2]);
                            buf3=buf3/buf1;
                            sprintf(valueStack.symbol[valueStack.top-2], "%f", buf3);
                            valueStack.top=valueStack.top-2;

                            break;
                        case 7://T->F
                            stackPop(&stateStack);
                            stackPop(&symbolStack);       
                            stackPush(&symbolStack,"T");   
                            break;
                        case 8://F->num
                            stackPop(&stateStack); 
                            strcpy(chBuf,stackPop(&symbolStack));
                            stackPush(&symbolStack,"F");

                            break;
                        case 9://F->(E)
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&stateStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPop(&symbolStack);
                            stackPush(&symbolStack,"F");

                            buf2=atof(valueStack.symbol[valueStack.top-1]);
                            buf3=atof(valueStack.symbol[valueStack.top-2]);
                            buf3=buf2;
                            sprintf(valueStack.symbol[valueStack.top-2], "%f", buf3);
                            valueStack.top=valueStack.top-2;

                            break;
                    }
                    if(controlPrint==1){
                        printf("stateStackTop:%s\n",stateStack.symbol[stateStack.top]);
                        printf("symbolStackTop:%s\n",symbolStack.symbol[symbolStack.top]);  
                    }
                }
                else{
                    if(!(strcmp(currentState, "17") == 0)){
                        printf("analyze erro!\n");
                        exit(1);
                    }
                }
            }   

        }    
        else{//转移//两个栈高度不同
            stateIndex=atoi(currentState);
            if (strcmp(currentSymbol, "S") == 0) symbolIndex = 8;   
            else if (strcmp(currentSymbol, "E") == 0) symbolIndex = 9;   
            else if (strcmp(currentSymbol, "T") == 0) symbolIndex = 10;   
            else if (strcmp(currentSymbol, "F") == 0) symbolIndex = 11;     
            sprintf(str, "%d", lr0Table[stateIndex][symbolIndex]);
            stackPush(&stateStack,str);
            if(controlPrint==1){
                printf("stateStackTop:%s\n",stateStack.symbol[stateStack.top]);
                printf("symbolStackTop:%s\n",symbolStack.symbol[symbolStack.top]);  
            }
        }
    }
    printf("success!\n");
    printf("result:%f\n",result);

}