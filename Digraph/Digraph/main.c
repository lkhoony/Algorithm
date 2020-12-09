#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct DiGraph* G; // ����׷��� ��������
int n, m; // n : ������ ��, m : ������ ��
int* in; // ������ �������� �迭
int* topOrder; // ������ ������� �迭
int* Q; // �������� ��⿭

struct DiGraph {

	struct Vertex** vertexList; // ���� ����Ʈ(�迭�� ����)
	struct DirectedEdge** directedEdgeList; // ���� ���� ����Ʈ(�迭�� ����)

}typedef DiGraph;

struct Vertex {
	
	int i; // ������ �ε���
	int inDegree; // ���� ����
	char vName; // ���� index�� �̸�
	struct IncidentEdge* outEdges; // ���� ���� ����Ʈ
	struct IncidentEdge* inEdges; // ���� ���� ����Ʈ

}typedef Vertex;

struct DirectedEdge {

	int i; // ������ �ε���
	int origin; // ���� ����
	int destination; // ���� ����

}typedef DirectedEdge;

struct IncidentEdge {

	int i; // ���� ���Ⱓ�� �ε���
	struct IncidentEdge* next; // ���� ���Ⱓ��

}typedef IncidentEdge;

// incidentEdgeList�� �ʱ�ȭ
IncidentEdge* initIncidentEdgeList() {

	IncidentEdge* incidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	incidentEdge->i = -1;
	incidentEdge->next = NULL;

	return incidentEdge;

}

// vName : ���� �̸�, i : ������ �ε���
DiGraph* insertVertex(char vName, int i) {

	Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
	
	newVertex->vName = vName;
	newVertex->outEdges = initIncidentEdgeList(); // ��� �Է�
	newVertex->inEdges = initIncidentEdgeList(); // ��� �Է�
	newVertex->inDegree = 0;

	(G->vertexList)[i] = newVertex;

}

// vName : ������ �̸�
int index(char vName) {

	Vertex** vertexList = G->vertexList;

	for (int i=0; i < n; i++) {
		if (vName == vertexList[i]->vName) {
			return i;
		}
	}
}

// ����, ���� �������� ����Ʈ�� �� �տ� ����
void addFirst(IncidentEdge* header, int i) {

	IncidentEdge* newEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));

	newEdge->i = i;
	newEdge->next = header->next;
	header->next = newEdge;

}

// uName : ���� ������ �̸�
// wName : ���� ������ �̸� 
// i : DirectedEdge�� �ε���
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