#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20
/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{                           //우선순위를 정한다. 
    lparen = 0, /* ( 왼쪽 괄호 */
    rparen = 9, /* ) 오른쪽 괄호*/
    times = 7, /* * 곱셈 */
    divide = 6, /* / 나눗셈 */
    plus = 5, /* + 덧셈 */
    minus = 4, /* - 뺄셈 */
    operand = 1 /* 피연산자 */
} precedence;                           //구조체로 만들었다.
                                                 //아래 설명 함수 나올때마다 설명 
char infixExp[MAX_EXPRESSION_SIZE];             //infix expression을 저장하는 배열 
char postfixExp[MAX_EXPRESSION_SIZE];           //postfix로 변경된 문자열을 저장하는 배열
char postfixStack[MAX_STACK_SIZE];              //postfix로 변환을 위해 필요한 스택
int evalStack[MAX_STACK_SIZE];                  //계산을 위해 필요한 스택
int postfixStackTop = -1;
int evalStackTop = -1;
int evalResult = 0;
void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();


int main()                          //메인 함수 
{
    char command;                   //시작화면 만들기 
    do{
    printf("----------------------------------------------------------------\n");
    printf(" Infix to Postfix, then Evaluation\n");
    printf("----------------------------------------------------------------\n");
    printf(" Infix=i, Postfix=p, Eval=e, Debug=d, Reset=r, Quit=q \n");
    printf("----------------------------------------------------------------\n");
    printf("Command = ");
    scanf(" %c", &command);
    switch(command) {                   
        case 'i': case 'I':                     //i를 입력하면 getInfix()함수 실행
        getInfix();
        break;
        case 'p': case 'P':                     //p를 입력하면 toPostfix()실행
        toPostfix();
        break;
        case 'e': case 'E':                     //e를 입력하면 evaluation()실행
        evaluation();
        break;
        case 'd': case 'D':                     //d를 입력하면 debug()실행
        debug();
        break;  
        case 'r': case 'R':                     //r을 입력하면 reset()실행 
        reset();
        break;
        case 'q': case 'Q':                     
        break;
    default:
    printf("\n >>>>> Concentration!! <<<<<\n");
    
    break;
    }
    }
    while(command != 'q' && command != 'Q');    //q를 입력하면 종료
    return 1;
}
    void postfixPush(char x)            //후위표기법 push 
    {
        postfixStack[++postfixStackTop] = x; //postfixstack[]의 top을 하나 증가시키고 x를 넣는다.
    }


    char postfixPop()                 //후위표기법 pop
    {
        char x;
        if(postfixStackTop == -1)       //만약 top이 -1이면 아무일도없고
        return '\0';
        else {
            x = postfixStack[postfixStackTop--];       //top이 -1이 아니면 postfixstack[]의 top을 하나 감소 시킨다.
        }
    return x;                           //x 값을 반환한다.
    }
    void evalPush(int x)            //후위 표기헙 합산 push 
    {
        evalStack[++evalStackTop] = x; //evalStakc의top 위치를 1증가시키고 x를 넣는다.
    }
    int evalPop()                   //후위 표기법 합산 pop
    {
        if(evalStackTop == -1)      //만약 stack의 top -1이면 아무런 변화가 없고 
            return -1;
        else
            return evalStack[evalStackTop--];//top -1이 아니면 evalstack의 top의 위치를 하나 감소시킨다.
    }
    /**
    * infix expression을 입력받는다.
    * infixExp에는 입력된 값을 저장한다.
    */
    void getInfix()     //중위표기법 받기
    {
        printf("Type the expression >>> ");
        scanf("%s",infixExp);           //사용자로 부터 중위 값을 받는다.
    }
    precedence getToken(char symbol)    //연산 기호,괄호를 사용하기 위한 토큰
    {
            switch(symbol) {
            case '(' : return lparen;       //'('이면 lparen으로 리턴
            case ')' : return rparen;       //')'이면 rparen으로 리턴
            case '+' : return plus;         //'+'면 plus로 리턴
            case '-' : return minus;        //'-'면 minus로 리턴
            case '/' : return divide;       //'/'면 divide로 리턴
            case '*' : return times;        //'*'면 rimes로 리턴
            default : return operand;       //default면 operand로 리턴
        }
    }

    precedence getPriority(char x)  
    {
        return getToken(x);
    }
    /**
    * 문자하나를 전달받아, postfixExp에 추가
    */
    void charCat(char* c)       //사용자로부터 문자를 받아 postfixExp로 전달 
    {
        if (postfixExp == '\0')              
            strncpy(postfixExp, c, 1);
        else                               
            strncat(postfixExp, c, 1);
    }
    /**
    * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
    * 변경된 postfix는 postFixExp에 저장된다.
    */
    void toPostfix()
    {
        /* infixExp의 문자 하나씩을 읽기위한 포인터 */
        char *exp = infixExp;
        char x; 
        /* 문자하나를 임시로 저장하기 위한 변수 */
        /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
        while(*exp != '\0')
        {
            if(getPriority(*exp) == operand)   // 피연산자인 경우
                {
                x = *exp;
                charCat(&x);                // 피연산자를 postfixExp 문자열에 추가
                }
        else if(getPriority(*exp) == lparen) {// 왼쪽 괄호인 경우

            postfixPush(*exp);// 스택에 push
        }
        else if(getPriority(*exp) == rparen) // 오른쪽 괄호인 경우
        {
            while((x = postfixPop()) != '(') {// 스택에서 왼쪽 괄호가 나올 때까지 pop하여 postfixExp 문자열에 추가
            charCat(&x);
        }
    }
    else// 연산자인 경우
    {// 스택에서 우선순위가 같거나 높은 연산자를 pop하여 postfixExp 문자열에 추가
        while(getPriority(postfixStack[postfixStackTop]) >=
            getPriority(*exp))
            {
                x = postfixPop();
                charCat(&x);
            }
            postfixPush(*exp);// 현재 연산자를 스택에 push
    }
    exp++;
    }

    // 스택에 남은 연산자들을 pop하여 postfixExp 문자열에 추가
    while(postfixStackTop != -1)
    {
        x = postfixPop();
        charCat(&x);
    }
    }

    void debug()                            //출력하는 함수 
    {
        printf("\n---DEBUG\n");
        printf("infixExp = %s\n", infixExp);        //중위표기법출력
        printf("postExp = %s\n", postfixExp);       //후위표기법 출력
        printf("eval result = %d\n", evalResult);   //결과값 출력
        printf("postfixStack : ");                  //스텍에 있는 opertator있는거 출력
        for(int i = 0; i < MAX_STACK_SIZE; i++)     
            printf("%c ", postfixStack[i]);
        printf("\n");
    }

    void reset()
    {                                                       //모든값을 초기상태로 초기화한다.
        infixExp[0] = '\0';
        postfixExp[0] = '\0';
        for(int i = 0; i < MAX_STACK_SIZE; i++)
            postfixStack[i] = '\0';

        postfixStackTop = -1;
        evalStackTop = -1;
        evalResult = 0;
    }

    void evaluation()                       //값을 연산하는 함수
    {
        int opr1, opr2, i;
        int length = strlen(postfixExp);
        char symbol;
        evalStackTop = -1;
        for(i = 0; i < length; i++)
        {
            symbol = postfixExp[i];
        if(getToken(symbol) == operand) {
            evalPush(symbol - '0');
        }
        else {
            opr2 = evalPop();
            opr1 = evalPop();
                switch(getToken(symbol)) {                  //sysbol에 따라 연산이 달라짐
                case plus: evalPush(opr1 + opr2); break;
                case minus: evalPush(opr1 - opr2); break;
                case times: evalPush(opr1 * opr2)s; break;
                case divide: evalPush(opr1 / opr2); break;
                default: break;
                }

        }
    }
    evalResult = evalPop(); //마지막에 계산을 해서 operator를 썼기 떄문에 하나 팝한다.
}