#include <stdio.h>
#include <stdlib.h>

// 1. DFS
/*
struct Vertex {

	struct IncidentEdge* incidentEdges; // ���� ������
	int number; // ������ ����
	struct Vertex* next; // ���� ���� (�������� ���� ��Ÿ���� ����)
	int visited; // �湮 ���� (0 : fresh, 1 : visited) 

}typedef Vertex;

struct Edge {

	struct Vertex* origin; // ��� ����
	struct Vertex* dest; // ���� ����
	//int weight; // ������ ����ġ
	struct Edge* nextEdge; // ���� ���� ( �������� ������ ��Ÿ���� ����)
	int visited; // �湮 ���� (0 : fresh, 1 : Tree, 2 : Back) 

}typedef Edge;

struct IncidentEdge {

	struct Edge* edge; // ������ ����Ű�� ������
	struct IncidentEdge* next; // ���� ���� ����( ���� �������� ������ ��Ÿ���� ����)

}typedef IncidentEdge;

struct Graph {

	struct Vertex* vertexList; // ������ ������ ��Ÿ���� ����Ʈ
	struct Edge* edgeList; // ������ ������ ��Ÿ���� ����Ʈ
	int vertexCount; // ������ ����
	int edgeCount; // ������ ����

}typedef Graph;


Vertex* createVertex(int number) {

	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));

	// vertex�� �����Ͽ� number�� ����
	vertex->number = number;
	// ���� ������ ��Ÿ���� ����Ʈ �����Ͽ� ��� �ʱ�ȭ
	vertex->incidentEdges = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	// ���� ������ ���� ���� ������ next�� NULL ����
	vertex->incidentEdges->next = NULL;
	// ���� vertex�� ���� ������ NULL ����
	vertex->next = NULL;

	return vertex;
}

Edge* createEdge(Vertex* origin, Vertex* dest) {

	Edge* edge = (Edge*)malloc(sizeof(Edge));

	// �Է� ���� ������ ���, ���� ���� �Է�
	edge->origin = origin;
	edge->dest = dest;
	// ���� edge�� ���� ������ NULL ����
	edge->nextEdge = NULL;

	return edge;
}

IncidentEdge* createIncidentEdge(Edge* edge) {

	IncidentEdge* incidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	incidentEdge->edge = edge;
	incidentEdge->next = NULL;

	return incidentEdge;

}

void insertVertex(Graph* graph, int number) {

	Vertex* vertex = graph->vertexList;

	// ���� �׷����� vertex�� ����Ǿ� ���� ������ ����� ����
	if (vertex == NULL) {
		graph->vertexList = createVertex(number);
		return;
	}

	// �׷��� ������ ������ vertex���� �̵�
	while (vertex->next != NULL) {
		vertex = vertex->next;
	}

	vertex->next = createVertex(number);

}

Edge* findEdge(Graph* graph, int originNum, int destNum) {

	Edge* edge = graph->edgeList;

	while (edge != NULL) {

		Vertex* origin = edge->origin;
		Vertex* dest = edge->dest;

		// ���� edge�� ����Ǿ� �ִ� vertex���� number�� �Է¹��� number��� ���� ��� �ش� edge�� ��ȯ
		if (origin->number == originNum && dest->number == destNum)
			return edge;
		else if (origin->number == destNum && dest->number == originNum)
			return edge;

		edge = edge->nextEdge;
	}

	// edge�� �������� ���� ��� NULL�� ��ȯ��
	return edge;
}

// ������ ã�� �Լ�
Vertex* findVertex(Graph* graph, int number) {

	// vertex�� vertexList�� ù ��° node�� �Ҵ�
	Vertex* vertex = graph->vertexList;

	// vertex�� ����Ǿ� �ִ� number�� �Է� ���� number�� ���� ��� �ش� ������ ��ȯ
	while (vertex != NULL) {
		if (vertex->number == number)
			return vertex;
		vertex = vertex->next;
	}

	// number�� ���� ������ ���� ��� NULL�� ��ȯ
	return vertex;
}

// edge�� ����Ǿ� �ִ� fromVertex�� ���� ������ ���ϴ� �Լ�
// opposite
Vertex* adjacentVertex(Vertex* fromVertex, Edge* edge) {

	// ���� edge�� origin�� fromVertex�� ������ dest Vertex�� ��ȯ
	if (edge->origin == fromVertex)
		return edge->dest;
	else
		return edge->origin;

}

// vertex : incidentEdge�� �߰� �� vertex, newEdge : ���� ������ edge
void insertIncidentEdge(Vertex* vertex, Edge* newEdge) {

	// incidentEdge : vertex�� incidentEdges ���
	IncidentEdge* incidentEdge = vertex->incidentEdges;
	IncidentEdge* prev;
	IncidentEdge* newIncidentEdge = createIncidentEdge(newEdge);

	// ��� ��常 ���� ���
	if (incidentEdge->next == NULL) {
		// ���ο� incidentEdge ����
		incidentEdge->next = newIncidentEdge;
		return;
	}

	// �ٸ� incident edge�� ���� ���,
	// incident edge�� ����Ǿ� �ִ� edge�鿡�� ���� vertex�� ������ vertex�� 
	// ũ�⸦ ���Ͽ� ������������ �����ؾ� ��

	else {

		while (incidentEdge->next != NULL) {

			prev = incidentEdge;
			incidentEdge = incidentEdge->next;

			// ���� new Edge�� ����Ǿ� �ִ� ���� vertex�� �ƴ� �ٸ� vertex�� ���ڰ� �� ���� ���
			if (adjacentVertex(vertex, incidentEdge->edge)->number >= adjacentVertex(vertex, newEdge)->number) {
				prev->next = newIncidentEdge;
				prev->next->next = incidentEdge;
				return;
			}
		}

		// return���� ������ ������ ������ �� ���̱� ������ ������ incidentEdge���� �� ���̱� ������ �������� ����
		incidentEdge->next = newIncidentEdge;

	}

}

// edge�� ����Ǿ� �ִ� vertex�� incidentEdge�� update
void updateIncidentEdge(Edge* newEdge) {

	Vertex* originVertex = newEdge->origin;
	Vertex* destVertex = newEdge->dest;


	insertIncidentEdge(originVertex, newEdge);

	if (originVertex != destVertex) insertIncidentEdge(destVertex, newEdge);

}


void insertEdge(Graph* graph, int originNum, int destNum) {

	Edge* edge = graph->edgeList;

	// orginNum�� destNum�� �����ϴ� ������ ã�Ƽ� �Ҵ�
	Vertex* originVertex = findVertex(graph, originNum);
	Vertex* destVertex = findVertex(graph, destNum);

	// origin number�� �����ϴ� origin Vertex�� ���� �� 
	if (originVertex == NULL || destVertex == NULL) {
		if (originVertex == NULL) {
			printf("Does Not Exist Vertex including %d", originNum);
		}
		else if (destVertex == NULL) {
			printf("Does Not Exist Vertex including %d", destNum);
		}
		return;
	}

	// ���� List�� �Է� �� edge ����
	Edge* newEdge = createEdge(originVertex, destVertex);

	// edgeList�� ����� �� ù ��° edge�� ����
	if (edge == NULL) {
		graph->edgeList = newEdge;
	}
	else {

		// �׷��� ������ ������ edge���� �̵�
		while (edge->nextEdge != NULL) {
			edge = edge->nextEdge;
		}

		// �������� newEdge ����
		edge->nextEdge = newEdge;
	}

	updateIncidentEdge(newEdge);
}

// ������ ���� �������� number�� ������ ����ġ�� ���
//void printAllAdjacentVertex(Graph* graph, int number) {
//
//	Vertex* vertex = findVertex(graph, number);
//	Vertex* adjacentV;
//
//	if (vertex == NULL) printf("-1\n");
//	else {
//
//		IncidentEdge* incidentEdge = vertex->incidentEdges;
//
//		while (incidentEdge->next != NULL) {
//
//			incidentEdge = incidentEdge->next;
//
//			adjacentV = adjacentVertex(vertex, incidentEdge->edge);
//
//			printf(" %d %d", adjacentV->number, incidentEdge->edge->weight);
//		}
//
//		printf("\n");
//	}
//}

IncidentEdge* removeIncidentEdge(Vertex* vertex, Edge* edge) {

	IncidentEdge* incidentEdge = vertex->incidentEdges;
	IncidentEdge* prev = incidentEdge;
	incidentEdge = incidentEdge->next;

	while (incidentEdge != NULL) {
		if (incidentEdge->edge == edge) {
			prev->next = incidentEdge->next;
			free(incidentEdge);
			return;
		}

		prev = incidentEdge;
		incidentEdge = incidentEdge->next;
	}
}

void removeEdge(Graph* graph, Edge* edge) {

	Edge* deletingEdge = graph->edgeList;
	Edge* prevEdge = NULL;

	while (deletingEdge != NULL) {
		// ������ edge�� ������ ������ vertex�� ���� �������� ����
		if (deletingEdge == edge) {
			removeIncidentEdge(deletingEdge->origin, edge);
			removeIncidentEdge(deletingEdge->dest, edge);

			// ������ edge�� ù ��° �� ���
			if (prevEdge == NULL) {
				graph->edgeList = deletingEdge->nextEdge;
			}
			else {
				prevEdge->nextEdge = deletingEdge->nextEdge;
			}
			free(deletingEdge);
			return;
		}
		prevEdge = deletingEdge;
		deletingEdge = deletingEdge->nextEdge;
	}
}


// ������ weight�� ����
//void modifyEdge(Graph* graph, int originNum, int destNum, int weight) {
//
//	Edge* edge = findEdge(graph, originNum, destNum);
//	Vertex* origin = findVertex(graph, originNum);
//	Vertex* dest = findVertex(graph, destNum);
//
//	if (origin == NULL || dest == NULL) {
//		printf("-1\n");
//		return;
//	}
//
//	// ������ ������ ���� ����
//	if (edge == NULL) {
//		insertEdge(graph, originNum, destNum, weight);
//		return;
//	}
//
//	// ����ġ�� 0���� �ԷµǸ� edge�� ����
//	if (weight == 0) {
//		removeEdge(graph, edge);
//		return;
//	}
//
//	edge->weight = weight;
//
//}

//void createGraph(Graph* graph) {
//
//	// ���� ����
//	for (int i = 1; i <= 6; i++) {
//		insertVertex(graph, i);
//	}
//
//	// ���� ����
//	insertEdge(graph, 1, 2, 1);
//	insertEdge(graph, 1, 3, 1);
//	insertEdge(graph, 1, 4, 1);
//	insertEdge(graph, 1, 6, 2);
//	insertEdge(graph, 2, 3, 1);
//	insertEdge(graph, 3, 5, 4);
//	insertEdge(graph, 5, 5, 4);
//	insertEdge(graph, 5, 6, 3);
//
//}

Graph* initGraph(int vertexCount, int edgeCount) {

	Graph* graph = (Graph*)malloc(sizeof(Graph));
	int origin, dest;

	graph->vertexList = NULL;
	graph->edgeList = NULL;
	graph->vertexCount = vertexCount;
	graph->edgeCount = edgeCount;

	for (int i = 1; i <= vertexCount; i++) {
		insertVertex(graph, i);
	}

	for (int i = 0; i < edgeCount; i++) {
		scanf("%d%d", &origin, &dest);
		insertEdge(graph, origin, dest);
	}

	return graph;
}

void rDFS(Graph* graph, Vertex* vertex) {

	IncidentEdge* incidentEdge = vertex->incidentEdges;
	Vertex* w;

	vertex->visited = 1;
	printf("%d\n", vertex->number);

	while (incidentEdge->next != NULL) {

		incidentEdge = incidentEdge->next;

		if (incidentEdge->edge->visited == 0) {

			w = adjacentVertex(vertex, incidentEdge->edge);

			// w�� ó�� �湮�ϴ� vertex�� ��� �ش� vertex���� rDFS�� ���� 
			if (w->visited == 0) {
				incidentEdge->edge->visited = 1; // �ش� ������ Tree�� labeling
				rDFS(graph, w);
			}

			else
				incidentEdge->edge->visited = 2; 
				// ������ fresh���� vertex�� �̹� �湮�� �����̸�
				// back labeling

		}

	}
}

void DFS(Graph* graph,int start) {

	Vertex* startVertex = findVertex(graph, start);

	Vertex* vertex = graph->vertexList;
	Edge* edge = graph->edgeList;

	if (startVertex == NULL)
		return;

	while (vertex != NULL) {
		vertex->visited = 0;
		vertex = vertex->next;
	}

	while (edge != NULL) {
		edge->visited = 0;
		edge = edge->nextEdge;
	}

	rDFS(graph, startVertex);

	//vertex = graph->vertexList;

	//while (vertex != NULL) {
	//	if (vertex->visited == 0)
	//		rDFS(graph, vertex);
	//	vertex = vertex->next;
	//}
	
}
int main() {

	int n, m, s; // n : ������ ����, m : ������ ����, s : ��ȸ ���� ����

	scanf("%d%d%d", &n, &m, &s);

	Graph* graph = initGraph(n,m);
	Vertex* startVertex = findVertex(graph, s);

	if (startVertex == NULL) {
		//printf("Does not Exist Vertex %d",s);
		return;
	}

	DFS(graph,s);

	//createGraph(graph);

	//char operation;
	//int number, originNum, destNum, weight;

	//while (1) {

	//	scanf("%c", &operation);

	//	if (operation == 'a') {
	//		scanf("%d", &number);
	//		printAllAdjacentVertex(graph, number);
	//	}
	//	else if (operation == 'm') {
	//		scanf("%d%d%d", &originNum, &destNum, &weight);
	//		modifyEdge(graph, originNum, destNum, weight);
	//	}
	//	else if (operation == 'q') {
	//		break;
	//	}

	//	getchar();
	//}
}
*/

// ---------------------------------------------------------------------------
// 2. ��������� ����� BFS

#include<stdio.h>
#include<stdlib.h>

// ���� ����� ��Ÿ���� ��������
struct Edge** adjacencyMatrix[100];

struct Vertex {

	int index; // ���� ��Ŀ����� ��ġ
	int number; // ������ ����
	struct Vertex* next; // ���� ���� (�������� ���� ��Ÿ���� ����)
	int visited; // �湮���� (0 : fresh, 1 : visited )

}typedef Vertex;

struct Edge {

	struct Vertex* origin; // ��� ����
	struct Vertex* dest; // ���� ����
	struct Edge* nextEdge; // ���� ���� ( �������� ������ ��Ÿ���� ����)
	int visited; // �湮 ����( 0 : fresh, 1 : tree, 2 : cross)

}typedef Edge;


struct Graph {

	struct Vertex* vertexList; // ������ ������ ��Ÿ���� ����Ʈ
	struct Edge* edgeList; // ������ ������ ��Ÿ���� ����Ʈ
	int vertexCount; // ������ ��
	int edgeCount; // ������ ��

}typedef Graph;

void initAdjacencyMatrix(int n, int m) {

	// ���� ��� �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		adjacencyMatrix[i] = (Edge**)malloc(sizeof(Edge*) * m);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			adjacencyMatrix[i][j] = (Edge*)malloc(sizeof(Edge));
			adjacencyMatrix[i][j] = NULL;
		}
	}
}

Vertex* createVertex(int index, int number) {

	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));

	// vertex�� �����Ͽ� number�� ����
	vertex->number = number;
	// ���� ��Ŀ��� �ڽ��� ��ġ�� ��Ÿ���� index ����
	vertex->index = index;

	vertex->next = NULL;

	return vertex;
}

Edge* createEdge(Vertex* origin, Vertex* dest) {

	Edge* edge = (Edge*)malloc(sizeof(Edge));

	// �Է� ���� ������ ���, ���� ���� �Է�
	edge->origin = origin;
	edge->dest = dest;
	// ���� edge�� ���� ������ NULL ����
	edge->nextEdge = NULL;

	return edge;
}

void insertVertex(Graph* graph, int index, int number) {

	Vertex* vertex = graph->vertexList;

	// ���� �׷����� vertex�� ����Ǿ� ���� ������ ����� ����
	if (vertex == NULL) {
		graph->vertexList = createVertex(index, number);
		return;
	}

	// �׷��� ������ ������ vertex���� �̵�
	while (vertex->next != NULL) {
		vertex = vertex->next;
	}

	vertex->next = createVertex(index, number);

}

Edge* findEdge(Graph* graph, Vertex* originVertex, Vertex* destVertex) {

	int originIndex = originVertex->index;
	int destIndex = destVertex->index;


	return adjacencyMatrix[originIndex][destIndex];

}

// ������ ã�� �Լ�
Vertex* findVertex(Graph* graph, int number) {

	// vertex�� vertexList�� ù ��° node�� �Ҵ�
	Vertex* vertex = graph->vertexList;

	// vertex�� ����Ǿ� �ִ� number�� �Է� ���� number�� ���� ��� �ش� ������ ��ȯ
	while (vertex != NULL) {
		if (vertex->number == number)
			return vertex;
		vertex = vertex->next;
	}

	// number�� ���� ������ ���� ��� NULL�� ��ȯ
	return vertex;
}

// edge�� ����Ǿ� �ִ� fromVertex�� ���� ������ ���ϴ� �Լ�
Vertex* adjacentVertex(Vertex* fromVertex, Edge* edge) {

	// ���� edge�� origin�� fromVertex�� ������ dest Vertex�� ��ȯ
	if (edge->origin == fromVertex)
		return edge->dest;
	else
		return edge->origin;

}


// edge�� �����ϸ� edge�� ����� vertex�� �ش��ϴ� adjacency matrix�� update
void updateAdjacencyMatrix(Edge* newEdge) {

	Vertex* originVertex = newEdge->origin;
	Vertex* destVertex = newEdge->dest;

	int originIndex = newEdge->origin->index;
	int destIndex = newEdge->dest->index;

	adjacencyMatrix[originIndex][destIndex] = newEdge;

	if (originVertex != destVertex) adjacencyMatrix[destIndex][originIndex] = newEdge;

}


void insertEdge(Graph* graph, int originNum, int destNum) {

	Edge* edge = graph->edgeList;

	// orginNum�� destNum�� �����ϴ� ������ ã�Ƽ� �Ҵ�
	Vertex* originVertex = findVertex(graph, originNum);
	Vertex* destVertex = findVertex(graph, destNum);

	// origin number�� �����ϴ� origin Vertex�� ���� �� 
	if (originVertex == NULL || destVertex == NULL) {
		if (originVertex == NULL) {
			printf("Does Not Exist Vertex including %d", originNum);
		}
		else if (destVertex == NULL) {
			printf("Does Not Exist Vertex including %d", destNum);
		}
		return;
	}

	// ���� List�� �Է� �� edge ����
	Edge* newEdge = createEdge(originVertex, destVertex);

	// edgeList�� ����� �� ù ��° edge�� ����
	if (edge == NULL) {
		graph->edgeList = newEdge;
	}
	else {

		// �׷��� ������ ������ edge���� �̵�
		while (edge->nextEdge != NULL) {
			edge = edge->nextEdge;
		}

		// �������� newEdge ����
		edge->nextEdge = newEdge;
	}

	// ���� ����� ������Ʈ
	updateAdjacencyMatrix(newEdge);
}

// ������ ���� �������� number�� ������ ����ġ�� ���
//void printAllAdjacentVertex(Graph* graph, int number) {
//
//	Vertex* vertex = findVertex(graph, number);
//	Vertex* adjacentV;
//	Edge* edge;
//
//	// vertex�� �������� ������ -1���
//	if (vertex == NULL) printf("-1\n");
//	else {
//		// index��°�� ���� ��ȸ
//		int index = vertex->index;
//
//		for (int i = 0; i < graph->vertexCount; i++) {
//
//			edge = adjacencyMatrix[index][i];
//
//			if (edge != NULL) {
//
//				adjacentV = adjacentVertex(vertex, edge);
//
//				printf(" %d %d", adjacentV->number, edge->weight);
//			}
//		}
//
//		printf("\n");
//	}
//}
//
//// ���� ��Ŀ��� edge�� ����
//void removeAdjacencyMatrix(Edge* edge) {
//
//	int originIndex = edge->origin->index;
//	int destIndex = edge->dest->index;
//
//	adjacencyMatrix[originIndex][destIndex] = NULL;
//	adjacencyMatrix[destIndex][originIndex] = NULL;
//
//}
//
//void removeEdge(Graph* graph, Edge* edge) {
//
//	Edge* deletingEdge = graph->edgeList;
//	Edge* prevEdge = NULL;
//
//	while (deletingEdge != NULL) {
//		// ������ edge�� ������ ������ vertex�� ���� �������� ����
//		if (deletingEdge == edge) {
//
//			removeAdjacencyMatrix(edge);
//
//			// ������ edge�� ù ��° �� ���
//			if (prevEdge == NULL) {
//				graph->edgeList = deletingEdge->nextEdge;
//			}
//			else {
//				prevEdge->nextEdge = deletingEdge->nextEdge;
//			}
//			free(deletingEdge);
//			return;
//		}
//		prevEdge = deletingEdge;
//		deletingEdge = deletingEdge->nextEdge;
//	}
//}
//
//
//// ������ weight�� ����
//void modifyEdge(Graph* graph, int originNum, int destNum, int weight) {
//
//	Vertex* origin = findVertex(graph, originNum);
//	Vertex* dest = findVertex(graph, destNum);
//
//	if (origin == NULL || dest == NULL) {
//		printf("-1\n");
//		return;
//	}
//
//	/*Edge* edge = findEdge(graph, originNum, destNum);*/
//
//	Edge* edge = findEdge(graph, origin, dest);
//
//	// ������ ������ ���� ����
//	if (edge == NULL) {
//		insertEdge(graph, originNum, destNum, weight);
//		return;
//	}
//
//	// ����ġ�� 0���� �ԷµǸ� edge�� ����
//	if (weight == 0) {
//		removeEdge(graph, edge);
//		return;
//	}
//
//	edge->weight = weight;
//
//}
//
//void createGraph(Graph* graph) {
//
//	// ���� ����
//	for (int i = 0; i < graph->vertexCount; i++) {
//		insertVertex(graph, i, i + 1);
//	}
//
//	// ���� ����
//	insertEdge(graph, 1, 2, 1);
//	insertEdge(graph, 1, 3, 1);
//	insertEdge(graph, 1, 4, 1);
//	insertEdge(graph, 1, 6, 2);
//	insertEdge(graph, 2, 3, 1);
//	insertEdge(graph, 3, 5, 4);
//	insertEdge(graph, 5, 5, 4);
//	insertEdge(graph, 5, 6, 3);
//
//}

Graph* initGraph(int vertexCount, int edgeCount) {

	int origin, dest;

	Graph* graph = (Graph*)malloc(sizeof(Graph));
	initAdjacencyMatrix(vertexCount, edgeCount);
	// ����, ���� ����Ʈ�� NULL�� �ʱ�ȭ
	graph->vertexList = NULL;
	graph->edgeList = NULL;

	// vertex ���� edge ���� �Է¹��� ������ �ʱ�ȭ
	graph->vertexCount = vertexCount;
	graph->edgeCount = edgeCount;

	for (int i = 1; i <= vertexCount; i++) {
		insertVertex(graph, i-1,i);
	}

	for (int i = 0; i < edgeCount; i++) {
		scanf("%d%d", &origin, &dest);
		insertEdge(graph, origin, dest);
	}

	return graph;

}

void BFS1(Graph* graph, Vertex* startVertex) {

	Vertex** queue;
	Vertex* popVertex;
	Vertex* w;
	Edge* edge;

	int front = 0;
	int rear = -1;
	int vertexIndex;

	queue = (Vertex**)malloc(sizeof(Vertex*) * (graph->vertexCount));

	queue[++rear] = startVertex;
	startVertex->visited = 1;

	while (front <= rear) {
		
		popVertex = queue[front++];
		vertexIndex = popVertex->index;

		printf("%d\n", popVertex->number);

		for (int i = 0; i < graph->edgeCount; i++) {
			edge = adjacencyMatrix[vertexIndex][i];
			
			if (edge != NULL) {
				//printf("%d %d", edge->origin->number, edge->dest->number);
				if (edge->visited == 0) {
					w = adjacentVertex(popVertex, edge);

					if (w->visited == 0) {
						queue[++rear] = w;
						w->visited = 1;
					}
					else {
						edge->visited = 2;
					}
				}
			}
		}
	}
}

void BFS(Graph* graph, int start) {

	Vertex* startVertex = findVertex(graph, start);

	Vertex* vertex = graph->vertexList;
	Edge* edge = graph->edgeList;

	if (startVertex == NULL)
		return;

	while (vertex != NULL) {
		vertex->visited = 0;
		vertex = vertex->next;
	}

	while (edge != NULL) {
		edge->visited = 0;
		edge = edge->nextEdge;
	}

	BFS1(graph, startVertex);

}


int main() {

	int n, m, s; // n : ������ ����, m : ������ ����, s : ��ȸ ���� ����

	scanf("%d%d%d", &n, &m, &s);

	Graph* graph = initGraph(n, m);

	BFS(graph, s);

}

/*
5 7 1
1 2
1 4
5 1
3 5
4 3
3 1
2 3

*/