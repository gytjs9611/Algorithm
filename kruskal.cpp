#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct edge {
	int ver1, ver2, weight;
} tEdge;

vector<tEdge> graph;
vector<tEdge> result;
int* parent;

void InitParent(int);
tEdge MakeEdge(int, int, int);
bool Compare(tEdge, tEdge);

int Kruskal(int, int);
int CollapsingFind(int);
void WeightedUnion(int, int);

int main(void) {
	FILE* fin;
	int vertex_size, edge_size;
	int ver1, ver2, weight;
	int cost;

	if (!(fin = fopen("kruskal_input.txt", "r"))) {
		fprintf(stderr, "Cannot Open the File\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fin, "%d %d", &vertex_size, &edge_size);

	parent = (int*)malloc(sizeof(int)*vertex_size);
	InitParent(vertex_size);

	for (int i = 0; i < edge_size; i++) {
		fscanf(fin, "%d %d %d", &ver1, &ver2, &weight);
		graph.push_back(MakeEdge(ver1, ver2, weight));
	}

	sort(graph.begin(), graph.end(), Compare); // sort in ascending order with STL sort ( quick sort,  O(n log n) )
	
	cout << "Input Edges ..." << endl;
	for (int i = 0; i < graph.size(); i++) {
		printf("%d %d %d\n", graph[i].ver1, graph[i].ver2, graph[i].weight);
	}

	cost = Kruskal(vertex_size, edge_size);

	if (cost == -1) {
		fprintf(stderr, "Failed\n");
		exit(EXIT_FAILURE);
	}
	else {
		printf("\nSelcted Edges are ...\n");
		for (int i = 0; i < result.size(); i++) {
			printf("%d %d %d\n", result[i].ver1, result[i].ver2, result[i].weight);
		}
		printf("Cost : %d\n", cost);
	}
}
int Kruskal(int v_size, int e_size) {
	int cnt = 0;
	int cost = 0;
	int root1, root2;

	while (cnt < v_size - 1) { // MST has (n-1) edges (n:vertex size)

		for (int i = 0; i < e_size; i++) {

			printf("(%d %d %d) : ", graph[i].ver1, graph[i].ver2, graph[i].weight);
			root1 = CollapsingFind(graph[i].ver1);
			root2 = CollapsingFind(graph[i].ver2);

			if (root1 != root2) { // if root is same, it makes cycle when you choose the edge
				WeightedUnion(root1, root2);
				cnt++;
				cost += graph[i].weight;
				result.push_back(graph[i]);
			}
		
			for (int i = 0; i < v_size; i++) {
				printf("%d ", parent[i]);
			}
			puts("");
		}

	}

	if (cnt < v_size - 1) {
		return -1;
	}
	else {
		return cost;
	}
	
}
int CollapsingFind(int ver) {
	int root;
	int ptr = ver;
	int temp;

	while (parent[ver] >=0) {
		ver = parent[ver];
	}
	root = ver;

	while (parent[ptr] >= 0) { // update a parent of the vertex after you find the root
		temp = parent[ptr];
		parent[ptr] = root;
		ptr = temp;
	}

	return root;
}
void WeightedUnion(int v1, int v2) { // set the vertex parent of the other if the vertex has more children
	int temp = parent[v1] + parent[v2];

	if (parent[v1] < parent[v2]) {
		parent[v1] = temp;
		parent[v2] = v1;
	}
	else {
		parent[v2] = temp;
		parent[v1] = v2;
	}
}
bool Compare(tEdge e1, tEdge e2) {
	return e1.weight < e2.weight;
}
tEdge MakeEdge(int v1, int v2, int w) {
	tEdge temp;
	temp.ver1 = v1;
	temp.ver2 = v2;
	temp.weight = w;
	return temp;
}
void InitParent(int size) {
	for (int i = 0; i < size; i++) {
		parent[i] = -1;
	}
}