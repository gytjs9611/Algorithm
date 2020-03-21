#include<iostream>
#include<vector>
#include<queue>

#define ROOT -1
#define INF 99999

using namespace std;

typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	int weight;
	nodePointer link;
} tNode;

nodePointer* graph;
int* cost;
int* previous;
bool* flag;

void CreateGraph(int, int, int);
nodePointer CreateNode(int, int);
void PrintGraph(int);
void Dijkstra(int);
void PrintResult(int, int);

int main(void) {
	FILE* fp = fopen("input.txt", "r");
	int vertex_size, edge_size;
	int source, destination, weight;

	fscanf(fp, "%d %d", &vertex_size, &edge_size);
	graph = (nodePointer*)malloc(sizeof(nodePointer)*vertex_size);
	cost = (int*)malloc(sizeof(int)*vertex_size);
	previous = (int*)malloc(sizeof(int)*vertex_size);
	flag = (bool*)malloc(sizeof(bool)*vertex_size);
	
	for (int i = 0; i < vertex_size; i++) {
		graph[i] = NULL;
		cost[i] = INF;
		previous[i] = ROOT;
		flag[i] = false;
	}

	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d %d", &source, &destination, &weight);
		CreateGraph(source, destination, weight);
	}

	cout << "Graph is created ..." << endl;
	PrintGraph(vertex_size);
	cout << "\nRun Dijkstra Algorithm ..." << endl;
	Dijkstra(0);
	for (int i = 1; i < vertex_size; i++) {
		PrintResult(0, i);
	}


}
void Dijkstra(int start) {
	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pair<int, int> temp;
	int src, dst, w;
	nodePointer ptr;

	cost[start] = 0;
	temp = make_pair(cost[start], start);
	pq.push(temp);

	while (!pq.empty()) {
		src = pq.top().second; // select the vertex which has the smallest cost
		pq.pop(); // remember pop has no return value

		//if (!flag[src]) { // I think is not essential cause only push unvisited vertex in queue, so flag must be always false
			ptr = graph[src];
			while (ptr) {
				dst = ptr->vertex;
				if (!flag[dst]) {
					w = ptr->weight;
					if (cost[dst] > cost[src] + w) {
						cost[dst] = cost[src] + w;
						previous[dst] = src;
						temp = make_pair(cost[dst], dst);
						pq.push(temp);
					}
				}
				ptr = ptr->link;
			}
		//}
		flag[src] = true;

	}

}
void PrintResult(int src, int dst) {
	vector<int> path;

	printf("distance[%d-%d] = %-3d :\t", src, dst, cost[dst]);
	
	while (1) {
		path.push_back(dst);
		if (dst == src) {
			break;
		}
		dst = previous[dst];
	}

	while (1) {
		printf("%d ", path.back());
		path.pop_back();
		if (path.empty()) {
			break;
		}
		printf("-> ");
	}
	printf("\n");

	/* CAUTION!
	for(int i = 0; i< path.size(); i++)
		path.pop_back(); => vector size is changed!!
	*/

}
void CreateGraph(int src, int dst, int weight) {
	nodePointer src_node, dst_node;
	nodePointer ptr;

	src_node = CreateNode(src, weight);
	dst_node = CreateNode(dst, weight);


	ptr = graph[src];
	if (!ptr) {
		graph[src] = dst_node;
	}
	else {
		while (ptr->link) {
			ptr = ptr->link;
		}
		ptr->link = dst_node;
	}

	ptr = graph[dst];
	if (!ptr) {
		graph[dst] = src_node;
	}
	else {
		while (ptr->link) {
			ptr = ptr->link;
		}
		ptr->link = src_node;
	}

}
nodePointer CreateNode(int v, int w) {
	nodePointer temp = (nodePointer)malloc(sizeof(tNode));
	temp->vertex = v;
	temp->weight = w;
	temp->link = NULL;
	return temp;
}
void PrintGraph(int v_size) {
	nodePointer ptr;

	for (int i = 0; i < v_size; i++) {
		cout << i << " : ";
		ptr = graph[i];
		while (ptr) {
			printf("(%d, %d) ", ptr->vertex, ptr->weight);
			ptr = ptr->link;
		}
		cout << endl;
	}

}