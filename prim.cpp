#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define TRUE 1
#define FALSE 0
#define INF 99999


typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	int weight;
	nodePointer link;
} tNode;

typedef struct edge {
	int src, dst, weight;
} tEdge;

nodePointer* adjList;

int* dist;
int* flag;

nodePointer createNode(int, int);
void createList(int, int, int);
void MST_Prim(int);
int main(void) {
	FILE* fp;
	int ver_size, edge_size;
	int v1, v2, w;
	
	if (!(fp = fopen("prim_input.txt", "r"))) {
		fprintf(stderr, "file not exist\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d", &ver_size, &edge_size);
	adjList = (nodePointer*)malloc(sizeof(nodePointer)*ver_size);
	dist = (int*)malloc(sizeof(int)*ver_size);
	flag = (int*)malloc(sizeof(int)*ver_size);

	for (int i = 0; i < ver_size; i++) {
		adjList[i] = NULL;
		dist[i] = INF;
		flag[i] = FALSE;
	}

	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d %d", &v1, &v2, &w);
		createList(v1, v2, w);
	}

	MST_Prim(ver_size);

}
struct compare {
	bool operator()(tEdge e1, tEdge e2) {
		return e1.weight > e2.weight; // min heap
	}
};
void MST_Prim(int ver_size) {
	tEdge temp, top_edge;
	vector<tEdge> result;
	priority_queue<tEdge, vector<tEdge>, compare> pq;
	int src, dst, w;

	dist[0] = 0;
	temp.src = 0;
	temp.dst = 0;
	temp.weight = dist[0];
	pq.push(temp);

	while (!pq.empty()) {
		top_edge = pq.top();
		pq.pop();
		src = top_edge.dst;
		if (!flag[src]) {
			nodePointer ptr = adjList[src];
			while (ptr) {
				dst = ptr->vertex;
				w = ptr->weight;
				if (!flag[dst] && dist[dst] > w) {
					dist[dst] = w;
					temp.src = src;
					temp.dst = dst;
					temp.weight = w;
					pq.push(temp);
				}
				ptr = ptr->link;
			}

			result.push_back(top_edge);
			flag[src] = TRUE;
		}
		
	}
	
	int sum = 0;

	for (int i = 1; i < result.size(); i++) {
		printf("%d %d %d\n", result[i].src, result[i].dst, result[i].weight);
		sum += result[i].weight;
	}
	printf("Cost : %d\n", sum);



	
}
void createList(int v1, int v2, int w) {
	nodePointer n1, n2, ptr;
	n1 = createNode(v1, w);
	n2 = createNode(v2, w);


	if (!adjList[v1]) {
		adjList[v1] = n2;
	}
	else {
		ptr = adjList[v1];
		while (ptr->link) {
			ptr = ptr->link;
		}
		ptr->link = n2;
	}
	
	if (!adjList[v2]) {
		adjList[v2] = n1;
	}
	else {
		ptr = adjList[v2];
		while (ptr->link) {
			ptr = ptr->link;
		}
		ptr->link = n1;
	}
}
nodePointer createNode(int v, int w) {
	nodePointer temp = (nodePointer)malloc(sizeof(tNode));
	temp->vertex = v;
	temp->weight = w;
	temp->link = NULL;
	return temp;
}