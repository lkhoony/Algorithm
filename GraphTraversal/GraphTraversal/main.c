#include <stdio.h>
#include <stdlib.h>

// 1. DFS
/*
struct Vertex {

	struct IncidentEdge* incidentEdges; // 부착 간선들
	int number; // 정점의 원소
	struct Vertex* next; // 다음 정점 (정점들의 집합 나타내기 위함)
	int visited; // 방문 여부 (0 : fresh, 1 : visited) 

}typedef Vertex;

struct Edge {

	struct Vertex* origin; // 출발 정점
	struct Vertex* dest; // 도착 정점
	//int weight; // 간선의 가중치
	struct Edge* nextEdge; // 다음 간선 ( 간선들의 집합을 나타내기 위함)
	int visited; // 방문 여부 (0 : fresh, 1 : Tree, 2 : Back) 

}typedef Edge;

struct IncidentEdge {

	struct Edge* edge; // 간선을 가르키는 포인터
	struct IncidentEdge* next; // 다음 인접 간선( 인접 간선들의 집합을 나타내기 위함)

}typedef IncidentEdge;

struct Graph {

	struct Vertex* vertexList; // 정점의 집합을 나타내는 리스트
	struct Edge* edgeList; // 간선의 집합을 나타내는 리스트
	int vertexCount; // 정점의 갯수
	int edgeCount; // 간선의 갯수

}typedef Graph;


Vertex* createVertex(int number) {

	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));

	// vertex를 생성하여 number를 대입
	vertex->number = number;
	// 인접 간선을 나타내는 리스트 생성하여 헤더 초기화
	vertex->incidentEdges = (IncidentEdge*)malloc(sizeof(IncidentEdge));
	// 인접 간선이 아직 없기 때문에 next에 NULL 대입
	vertex->incidentEdges->next = NULL;
	// 다음 vertex가 없기 때문에 NULL 대입
	vertex->next = NULL;

	return vertex;
}

Edge* createEdge(Vertex* origin, Vertex* dest) {

	Edge* edge = (Edge*)malloc(sizeof(Edge));

	// 입력 받은 간선의 출발, 종료 정점 입력
	edge->origin = origin;
	edge->dest = dest;
	// 다음 edge가 없기 때문에 NULL 대입
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

	// 만약 그래프에 vertex가 저장되어 있지 않으면 헤더를 설정
	if (vertex == NULL) {
		graph->vertexList = createVertex(number);
		return;
	}

	// 그렇지 않으면 마지막 vertex까지 이동
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

		// 만약 edge에 저장되어 있는 vertex들의 number가 입력받은 number들과 같을 경우 해당 edge를 반환
		if (origin->number == originNum && dest->number == destNum)
			return edge;
		else if (origin->number == destNum && dest->number == originNum)
			return edge;

		edge = edge->nextEdge;
	}

	// edge가 존재하지 않을 경우 NULL이 반환됨
	return edge;
}

// 정점을 찾는 함수
Vertex* findVertex(Graph* graph, int number) {

	// vertex에 vertexList의 첫 번째 node를 할당
	Vertex* vertex = graph->vertexList;

	// vertex에 저장되어 있는 number가 입력 받은 number와 같을 경우 해당 정점을 반환
	while (vertex != NULL) {
		if (vertex->number == number)
			return vertex;
		vertex = vertex->next;
	}

	// number를 갖는 정점이 없을 경우 NULL을 반환
	return vertex;
}

// edge와 연결되어 있는 fromVertex의 인접 정점을 구하는 함수
// opposite
Vertex* adjacentVertex(Vertex* fromVertex, Edge* edge) {

	// 만약 edge의 origin이 fromVertex와 같으면 dest Vertex를 반환
	if (edge->origin == fromVertex)
		return edge->dest;
	else
		return edge->origin;

}

// vertex : incidentEdge가 추가 될 vertex, newEdge : 새로 생성된 edge
void insertIncidentEdge(Vertex* vertex, Edge* newEdge) {

	// incidentEdge : vertex의 incidentEdges 헤더
	IncidentEdge* incidentEdge = vertex->incidentEdges;
	IncidentEdge* prev;
	IncidentEdge* newIncidentEdge = createIncidentEdge(newEdge);

	// 헤더 노드만 있을 경우
	if (incidentEdge->next == NULL) {
		// 새로운 incidentEdge 삽입
		incidentEdge->next = newIncidentEdge;
		return;
	}

	// 다른 incident edge도 있을 경우,
	// incident edge에 저장되어 있는 edge들에서 기준 vertex와 인접한 vertex의 
	// 크기를 비교하여 오름차순으로 저장해야 함

	else {

		while (incidentEdge->next != NULL) {

			prev = incidentEdge;
			incidentEdge = incidentEdge->next;

			// 만약 new Edge에 저장되어 있는 기준 vertex가 아닌 다른 vertex의 숫자가 더 작을 경우
			if (adjacentVertex(vertex, incidentEdge->edge)->number >= adjacentVertex(vertex, newEdge)->number) {
				prev->next = newIncidentEdge;
				prev->next->next = incidentEdge;
				return;
			}
		}

		// return되지 않으면 마지막 노드까지 온 것이기 때문에 마지막 incidentEdge까지 온 것이기 때문에 마지막에 대입
		incidentEdge->next = newIncidentEdge;

	}

}

// edge에 저장되어 있는 vertex의 incidentEdge를 update
void updateIncidentEdge(Edge* newEdge) {

	Vertex* originVertex = newEdge->origin;
	Vertex* destVertex = newEdge->dest;


	insertIncidentEdge(originVertex, newEdge);

	if (originVertex != destVertex) insertIncidentEdge(destVertex, newEdge);

}


void insertEdge(Graph* graph, int originNum, int destNum) {

	Edge* edge = graph->edgeList;

	// orginNum과 destNum을 포함하는 정점을 찾아서 할당
	Vertex* originVertex = findVertex(graph, originNum);
	Vertex* destVertex = findVertex(graph, destNum);

	// origin number를 포함하는 origin Vertex가 없을 때 
	if (originVertex == NULL || destVertex == NULL) {
		if (originVertex == NULL) {
			printf("Does Not Exist Vertex including %d", originNum);
		}
		else if (destVertex == NULL) {
			printf("Does Not Exist Vertex including %d", destNum);
		}
		return;
	}

	// 새로 List에 입력 될 edge 생성
	Edge* newEdge = createEdge(originVertex, destVertex);

	// edgeList가 비었을 때 첫 번째 edge를 설정
	if (edge == NULL) {
		graph->edgeList = newEdge;
	}
	else {

		// 그렇지 않으면 마지막 edge까지 이동
		while (edge->nextEdge != NULL) {
			edge = edge->nextEdge;
		}

		// 마지막에 newEdge 삽입
		edge->nextEdge = newEdge;
	}

	updateIncidentEdge(newEdge);
}

// 정점의 인접 정점들의 number와 간선의 가중치를 출력
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
		// 삭제할 edge와 같으면 각각의 vertex의 인접 간선에서 제거
		if (deletingEdge == edge) {
			removeIncidentEdge(deletingEdge->origin, edge);
			removeIncidentEdge(deletingEdge->dest, edge);

			// 삭제할 edge가 첫 번째 일 경우
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


// 간선의 weight를 수정
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
//	// 간선이 없으면 새로 생성
//	if (edge == NULL) {
//		insertEdge(graph, originNum, destNum, weight);
//		return;
//	}
//
//	// 가중치가 0으로 입력되면 edge를 제거
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
//	// 정점 생성
//	for (int i = 1; i <= 6; i++) {
//		insertVertex(graph, i);
//	}
//
//	// 간선 생성
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

			// w가 처음 방문하는 vertex일 경우 해당 vertex에서 rDFS를 실행 
			if (w->visited == 0) {
				incidentEdge->edge->visited = 1; // 해당 간선을 Tree로 labeling
				rDFS(graph, w);
			}

			else
				incidentEdge->edge->visited = 2; 
				// 간선이 fresh지만 vertex가 이미 방문한 정점이면
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

	int n, m, s; // n : 정점의 개수, m : 간선의 개수, s : 순회 시작 정점

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
// 2. 인접행렬을 사용한 BFS

#include<stdio.h>
#include<stdlib.h>

// 인접 행렬을 나타내는 지역변수
struct Edge** adjacencyMatrix[100];

struct Vertex {

	int index; // 인접 행렬에서의 위치
	int number; // 정점의 원소
	struct Vertex* next; // 다음 정점 (정점들의 집합 나타내기 위함)
	int visited; // 방문여부 (0 : fresh, 1 : visited )

}typedef Vertex;

struct Edge {

	struct Vertex* origin; // 출발 정점
	struct Vertex* dest; // 도착 정점
	struct Edge* nextEdge; // 다음 간선 ( 간선들의 집합을 나타내기 위함)
	int visited; // 방문 여부( 0 : fresh, 1 : tree, 2 : cross)

}typedef Edge;


struct Graph {

	struct Vertex* vertexList; // 정점의 집합을 나타내는 리스트
	struct Edge* edgeList; // 간선의 집합을 나타내는 리스트
	int vertexCount; // 정점의 수
	int edgeCount; // 간선의 수

}typedef Graph;

void initAdjacencyMatrix(int n, int m) {

	// 인접 행렬 초기화
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

	// vertex를 생성하여 number를 대입
	vertex->number = number;
	// 인접 행렬에서 자신의 위치를 나타내는 index 생성
	vertex->index = index;

	vertex->next = NULL;

	return vertex;
}

Edge* createEdge(Vertex* origin, Vertex* dest) {

	Edge* edge = (Edge*)malloc(sizeof(Edge));

	// 입력 받은 간선의 출발, 종료 정점 입력
	edge->origin = origin;
	edge->dest = dest;
	// 다음 edge가 없기 때문에 NULL 대입
	edge->nextEdge = NULL;

	return edge;
}

void insertVertex(Graph* graph, int index, int number) {

	Vertex* vertex = graph->vertexList;

	// 만약 그래프에 vertex가 저장되어 있지 않으면 헤더를 설정
	if (vertex == NULL) {
		graph->vertexList = createVertex(index, number);
		return;
	}

	// 그렇지 않으면 마지막 vertex까지 이동
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

// 정점을 찾는 함수
Vertex* findVertex(Graph* graph, int number) {

	// vertex에 vertexList의 첫 번째 node를 할당
	Vertex* vertex = graph->vertexList;

	// vertex에 저장되어 있는 number가 입력 받은 number와 같을 경우 해당 정점을 반환
	while (vertex != NULL) {
		if (vertex->number == number)
			return vertex;
		vertex = vertex->next;
	}

	// number를 갖는 정점이 없을 경우 NULL을 반환
	return vertex;
}

// edge와 연결되어 있는 fromVertex의 인접 정점을 구하는 함수
Vertex* adjacentVertex(Vertex* fromVertex, Edge* edge) {

	// 만약 edge의 origin이 fromVertex와 같으면 dest Vertex를 반환
	if (edge->origin == fromVertex)
		return edge->dest;
	else
		return edge->origin;

}


// edge를 생성하면 edge와 연결된 vertex에 해당하는 adjacency matrix를 update
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

	// orginNum과 destNum을 포함하는 정점을 찾아서 할당
	Vertex* originVertex = findVertex(graph, originNum);
	Vertex* destVertex = findVertex(graph, destNum);

	// origin number를 포함하는 origin Vertex가 없을 때 
	if (originVertex == NULL || destVertex == NULL) {
		if (originVertex == NULL) {
			printf("Does Not Exist Vertex including %d", originNum);
		}
		else if (destVertex == NULL) {
			printf("Does Not Exist Vertex including %d", destNum);
		}
		return;
	}

	// 새로 List에 입력 될 edge 생성
	Edge* newEdge = createEdge(originVertex, destVertex);

	// edgeList가 비었을 때 첫 번째 edge를 설정
	if (edge == NULL) {
		graph->edgeList = newEdge;
	}
	else {

		// 그렇지 않으면 마지막 edge까지 이동
		while (edge->nextEdge != NULL) {
			edge = edge->nextEdge;
		}

		// 마지막에 newEdge 삽입
		edge->nextEdge = newEdge;
	}

	// 인접 행렬을 업데이트
	updateAdjacencyMatrix(newEdge);
}

// 정점의 인접 정점들의 number와 간선의 가중치를 출력
//void printAllAdjacentVertex(Graph* graph, int number) {
//
//	Vertex* vertex = findVertex(graph, number);
//	Vertex* adjacentV;
//	Edge* edge;
//
//	// vertex가 존재하지 않으면 -1출력
//	if (vertex == NULL) printf("-1\n");
//	else {
//		// index번째의 행을 순회
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
//// 인접 행렬에서 edge를 제거
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
//		// 삭제할 edge와 같으면 각각의 vertex의 인접 간선에서 제거
//		if (deletingEdge == edge) {
//
//			removeAdjacencyMatrix(edge);
//
//			// 삭제할 edge가 첫 번째 일 경우
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
//// 간선의 weight를 수정
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
//	// 간선이 없으면 새로 생성
//	if (edge == NULL) {
//		insertEdge(graph, originNum, destNum, weight);
//		return;
//	}
//
//	// 가중치가 0으로 입력되면 edge를 제거
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
//	// 정점 생성
//	for (int i = 0; i < graph->vertexCount; i++) {
//		insertVertex(graph, i, i + 1);
//	}
//
//	// 간선 생성
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
	// 정점, 간선 리스트를 NULL로 초기화
	graph->vertexList = NULL;
	graph->edgeList = NULL;

	// vertex 수와 edge 수를 입력받은 값으로 초기화
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

	int n, m, s; // n : 정점의 개수, m : 간선의 개수, s : 순회 시작 정점

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