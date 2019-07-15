#include <math.h>
#include <iostream>
#include <stdbool.h>
#include<stdlib.h>
using namespace std;

typedef struct sdsvertex{
	int index;
	bool visited;
	sdsvertex *next;
} SDSVertex;

int a[10000][10000];
SDSVertex v_sds[10000];
int pNum = 0, edgeNum = 0;

typedef struct queue {
	SDSVertex *front;
	SDSVertex *rear;
} Queue;

Queue *createQueue(){
Queue *queue = (Queue *)malloc(sizeof(Queue));
queue->front = NULL;
queue->rear = NULL;
return queue;
}
void addToQueue(Queue *queue, SDSVertex *node)
{
	if (!(queue->rear)) {
		queue->rear = node;
	}
	else {
		queue->rear->next = node;
		queue->rear = node;
	}
	if (!(queue->front)) {
		queue->front = node;
	}
}
SDSVertex *deleteQueue(Queue *queue)
{
	SDSVertex *temp = queue->front;
	if (temp) {
		queue->front = queue->front->next;
		return temp;
	}
	else {
		return NULL;
	}
}
int isEmptyQueue(Queue *queue)
{
	if (queue->front == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
int BFS_SDS(int i)
{
	SDSVertex *v = &v_sds[i];
	v->visited = true;
	int level = 0, count = 1;
	SDSVertex *last = v, *tail = NULL;
	Queue *queue = createQueue();
	addToQueue(queue, v);
	while (!isEmptyQueue(queue)) {
		SDSVertex *vertex = deleteQueue(queue);
		for (int j = 1; j <= pNum; j++) {
			int hasEdge = a[vertex->index][j];
			if (hasEdge && !v_sds[j].visited) {
				v_sds[j].visited = true;
				addToQueue(queue, &v_sds[j]); count++;
				tail = &v_sds[j];
			}
		}
		if (vertex == last) {
			level++; last = tail;
		}
		if (level == 6) {
			break;
		}
	}
	for (int i = 1; i <= pNum; i++) {
		v_sds[i].visited = false;
		v_sds[i].next = NULL;
	}
	return count;
}
int main()
{
	cin >> pNum >> edgeNum;
	for (int i = 1; i <= edgeNum; i++) {
		int f = 0, to = 0;
		cin >> f >> to;
		a[f][to] = 1;
		a[to][f] = 1;
	}
	for (int i = 1; i <= pNum; i++) {
		v_sds[i].visited = false;
		v_sds[i].index = i;
		v_sds[i].next = NULL;
	}
	int count = -1;
	for (int i = 1; i <= pNum; i++) {
		count = BFS_SDS(i);
		printf("%d: %.2f%%\n", i, count * 100.0 / pNum);
	}
}