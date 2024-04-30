/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	// 새로운 노드 동적 할당 및 변수 선언
	listNode* pTemp = (listNode*)malloc(sizeof(listNode));
	pTemp->key = key;
	pTemp->link = NULL;
	listNode* node = h->first;
	listNode* prev = NULL;

	// 리스트가 비어있을 경우
	if (node==NULL){
		h->first = pTemp;
		return 0;
	}

	// 리스트 검색
	while(node != NULL && node->key <=key){
		prev = node;
		node = node->link; // 다음 연결 리스트
	}

	// 맨 앞 노드에 삽입을 할 때
	if (prev==NULL){ 
		pTemp->link = h->first; // node로 변경해도 된다.
		h->first = pTemp; // node로 변경하면 안된다. -> node 함수 내의 변수이기 때문에
		return 0;
	}

	// 그 외 삽입
	pTemp->link = prev->link;
	prev->link = pTemp;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* pTemp = (listNode*)malloc(sizeof(listNode));
	pTemp->key = key;
	pTemp->link = NULL;
	listNode* node = h->first;

	// 리스트가 비어있을 경우
	if (node==NULL){
		h->first = pTemp;
		return 0;
	}
	// 리스트 마지막 위치까지 도달
	while(node->link !=NULL){
		node = node->link;
	}
	node->link = pTemp; // 마지막 리스트 위치에 값 저장
	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* node = h->first;

	// 노드가 비어있을 경우
	if (node == NULL) {
		free(node);
		printf("Nothing to delete....\n");
		return 0;
	}
	// head를 다음 노드로 연결해주기
	h->first = node->link;
	// node 해제
	free(node);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* node = h->first;
	listNode* prev = NULL;

	// 노드가 비어있을 경우
	if (node==NULL){
		printf("Node is Empty!\n");
		return 0;
	}

	while(node != NULL && node->key!=key){
		prev = node;
		node = node -> link;
	}
	// key를 찾지 못하였을 경우
	if (node==NULL){
		printf("Nothing Node in linkedlist\n");
		return 0;
	}
	// 첫번째 노드를 삭제하는 경우
	if (prev==NULL){
		h->first = node->link;
		free(node);
		return 0;
	}
	prev->link = node->link;
	free(node);
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* node = h->first;
	listNode* prev = NULL;
	// 노드가 비어있을 경우
	if (node==NULL){
		printf("Node is Empty!\n");
		return 0;
	}
	// 바로 다음 리스트가 비어있을 경우
	if (node->link == NULL) {
		free(node);
		h->first = NULL;
		return 0;
	}
	// 마지막 리스트까지 순회
	while(node->link != NULL){
		prev = node;
		node = node->link;
	}
	// prev의 link를 null로 변경
	prev->link = NULL;
	// 마지막 노드 삭제
	free(node);
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode * trail = NULL;
	listNode * middle = NULL;
	listNode * lead = h->first;
	// 리스트 역순으로 재배치
	while(lead!=NULL){
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	h->first = middle; // head node 변경해주기
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

