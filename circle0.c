/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //큐의 최대 크기를 상수로 정의

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];  //MAX_QUEUE_SIZE 만큼 크기를 가지는 queue배열
	int front, rear;
}QueueType;		//구조체 


QueueType *createQueue();		//아래에서 설명  
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)					//초기 화면 유튜브 보면 그거 알수 있는데 ...
{
	QueueType *cQ = createQueue();
	element data;

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':					//i누르면 
			data = getElement();			//getElement()함수가 리턴한 값을 데이터에 넣는다.
			enQueue(cQ, data);				//enQueue 함수를 실행한다.
			break;
		case 'd': case 'D':					//D를르면 
			deQueue(cQ,&data);				//deQueue(cQ,&data)가 실행된다.
			break;
		case 'p': case 'P':					//p를 누르면
			printQ(cQ);						//printQ(cQ)가 실행된다.
			break;
		case 'b': case 'B':					//b를 누르면 
			debugQ(cQ);						//debugQ(cQ)가 실행된다.
			break;
		case 'q': case 'Q':					//q를 누르면 종료 
			break;							
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()		//빈큐를 생성하는 함수 
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));//QueueType 구조체를 동적으로 할당 
	cQ->front = 0;					//front와 rear값을 0으로 초기화 
	cQ->rear = 0;
	return cQ;					//구조체의 포인터를 반환
}

int freeQueue(QueueType *cQ)	//큐를 해제하는 함수 
{
    if(cQ == NULL) return 1;	//QueueType 구조체를 해제한다
    free(cQ);
    return 1;
}

element getElement()			//사용자로부터 삽입할 데이터를 입력받는 함수
{
	element item;
	printf("Input element = ");	//입력한 데이터를 element타입으로 반환
	scanf(" %c", &item);
	return item;
}


int isEmpty(QueueType *cQ) //큐가 비어있는지 확인하는 함수 
{
	if (cQ->front == cQ->rear){		//front와 rear값이 같으면 
		printf("Circular Queue is empty!"); //비어있따고 알려준다.
		return 1;//1을 반환 
	}
	else return 0;//아니면 0을 반환 
}

int isFull(QueueType *cQ)		//쿠ㅠ가 가득 찾는지 확인하는함수 
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {//큐가 가득차면 메세지를 알려준다.
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)//큐에 데이터를 삽입하는 함수 
{
	if(isFull(cQ)) return;	//큐가 가득차면 삽입하지않고 종료
	else {					//아니면 front 값을 업테이트하고 삭제한 데이터를 item포인터를 통해 반환한다.
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
	}
}

void deQueue(QueueType *cQ, element *item)//큐에서 데이터를 삽입하는 함수 
{
	if(isEmpty(cQ)) return;//큐가 비어있으면 그냥 리턴
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; //front값을 업데이트하고 
		*item = cQ->queue[cQ->front];				//삭제한 데이터를 item포인터를통해 반환
		return;
	}
}


void printQ(QueueType *cQ)		//큐에있는 데이터를 출력하는 함수 
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;					//큐가 비어있으면 함수 종료 
	while(i != last){		
		printf("%3c", cQ->queue[i]);	//front부터 rear까지의 데이터를 순서데로 출력
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)		//큐에대한 디버그 정보를 출력하는 함수
{

	printf("\n---DEBUG\n");				//queue 배열의 모든값을 순서대로 출력한다.
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {	//i가 front와 같을때
			printf("  [%d] = front\n", i);		//front임을 나타내는 문자열과 함꼐 출력
			continue;	
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);//큐의 요소 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front와 rear 값을 출력
}

