#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct DiGraph* G; // 방향그래프 전역변수
int n, m; // n : 정점의 수, m : 간선의 수
int* in; // 정점의 진입차수 배열
int* topOrder; // 정점의 위상순서 배열
int* Q; // 정점들의 대기열

struct DiGraph {

	struct Vertex** vertexList; // 정점 리스트(배열로 구현)
	struct DirectedEdge** directedEdgeList; // 방향 간선 리스트(배열로 구현)

}typedef DiGraph;

struct Vertex {
	
	int i; // 정점의 인덱스
	int inDegree; // 진입 차수
	char vName; // 정점 index의 이름
	struct IncidentEdge* outEdges; // 진출 간선 리스트
	struct IncidentEdge* inEdges; // 진입 간선 리스트

}typedef Vertex;

struct DirectedEdge {

	int i; // 간선의 인덱스
	int origin; // 시점 정점
	int destination; // 종점 정점

}typedef DirectedEdge;

struct IncidentEdge {

	int i; // 부착 방향간선 인덱스
	struct IncidentEdge* next; // 다음 방향간선

}typedef IncidentEdge;

// incidentEdgeList를 초기화
IncidentEdge* initIncidentEdgeList() {

	IncidentEdge* incidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	incidentEdge->i = -1;
	incidentEdge->next = NULL;

	return incidentEdge;

}

// vName : 정점 이름, i : 정점의 인덱스
DiGraph* insertVertex(char vName, int i) {

	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
	
	newVertex->vName = vName;
	newVertex->outEdges = initIncidentEdgeList(); // 헤더 입력
	newVertex->inEdges = initIncidentEdgeList(); // 헤더 입력
	newVertex->inDegree = 0;

	(G->vertexList)[i] = newVertex;

}

// vName : 정점의 이름
int index(char vName) {

	Vertex** vertexList = G->vertexList;

	for (int i=0; i < n; i++) {
		if (vName == vertexList[i]->vName) {
			return i;
		}
	}
}

// 진입, 진출 부착간선 리스트의 맨 앞에 삽입
void addFirst(IncidentEdge* header, int i) {

	IncidentEdge* newEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	newEdge->i = i;
	newEdge->next = header->next;
	header->next = newEdge;

}

// uName : 시점 정점의 이름
// wName : 종점 정점의 이름 
// i : DirectedEdge의 인덱스
DiGraph* insertDirectedEdge(char uName, char wName, int i) {

	int u = index(uName);
	int w = index(wName);

	DirectedEdge* directedEdge = (DirectedEdge*)malloc(sizeof(DirectedEdge));

	directedEdge->origin = u;
	directedEdge->destination = w;

	addFirst((G->vertexList)[u]->outEdges, i);
	addFirst((G->vertexList)[w]->inEdges, i);

	((G->vertexList)[w]->inDegree)++;

	G->directedEdgeList[i] = directedEdge;
}

DiGraph* initGraph() {

	G = (DiGraph*)malloc(sizeof(DiGraph));
	G->vertexList = (Vertex**)malloc(sizeof(Vertex*) * 99);
	G->directedEdgeList = (DirectedEdge**)malloc(sizeof(DirectedEdge*) * 999);
	
}

DiGraph* buildGraph() {

	char vName;
	char edge[4];

	initGraph();

	scanf("%d", &n);

	getchar();

	for (int i = 0; i < n; i++) {
		
		scanf("%c", &vName);
		insertVertex(vName, i);
		getchar();

	}

	scanf("%d", &m);

	getchar();

	for (int i = 0; i < m; i++) {
		gets(edge);
		insertDirectedEdge(edge[0], edge[2], i);
	}

	in = (int*)malloc(sizeof(int) * n);
	topOrder = (int*)malloc(sizeof(int) * (n + 1));

}

void topologicalSort() {

	Q = (int *)malloc(sizeof(int)*n);

	int front = 0;
	int rear = -1;
	int u,w;

	for (int i = 0; i < n; i++) {
		in[i] = (G->vertexList)[i]->inDegree;
		if (in[i] == 0) Q[++rear] = i;
	}

	int t = 1;

	while (front <= rear) {
		
		u = Q[front++];
		topOrder[t] = u;
		t++;

		IncidentEdge* outEdge = (G->vertexList)[u]->outEdges;
		while (outEdge->next != NULL) {
			outEdge = outEdge->next;

			w = (G->directedEdgeList)[outEdge->i]->destination;
			in[w] = in[w] - 1;
			if (in[w] == 0) Q[++rear] = w;
		}

		if (t <= n) topOrder[0] = 0;
		else topOrder[0] = 1;
	}

}
int main() {

	buildGraph();

	topologicalSort();

	if (topOrder[0] == 0)
		printf("0\n");
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", G->vertexList[topOrder[i]]->vName);
		}
	}
}

/*
3
A B C
3
A B
C A
C B
*/