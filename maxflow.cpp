#include<iostream>
#include<vector>
#include<queue>
#define MAX 52
#define INF 999999

using namespace std;

vector<int> graph[MAX];
int c[MAX][MAX] = { 0, }; // capacity
int f[MAX][MAX] = { 0, }; // flow
int result = 0; // max flow value

// the start and the end are 'A', 'Z',
// but there can exist the way 'A'->'a'->'Z'
// so it's size must be MAX=52

int ctoi(char);
void Maxflow(char, char);
int main(void) {
	FILE* fp = fopen("maxflow_input.txt", "r");
	int edge_size;
	char v1, v2;
	int capacity;

	fscanf(fp, "%d", &edge_size);

	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, " %c %c %d", &v1, &v2, &capacity);
		v1 = ctoi(v1);
		v2 = ctoi(v2);
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
		c[v1][v2] += capacity;
		c[v2][v1] += capacity;
	}

	Maxflow('A', 'Z');
	printf("max flow is %d\n", result);
}
void Maxflow(char s, char t) {
	int start, end;
	int p[MAX];
	int src, dst;

	start = ctoi(s);
	end = ctoi(t);

	while (1) {
		queue<int> q;
		fill(p, p + MAX, -1); // initialize the path
		q.push(start);
		while (!q.empty() && p[end] == -1) {
			// the queue is not empty && there's no path yet
			src = q.front();
			q.pop();
			for (int i = 0; i < graph[src].size(); i++) {
				dst = graph[src][i];
				if (p[dst] == -1 && c[src][dst] - f[src][dst] > 0) {
					// not visited && enough capacity
					q.push(dst);
					p[dst] = src;
					if (dst == end) {
						break;
					}
				}
			}
		}

		if (p[end] == -1) { // there's no path
			break;
		}


		int i = end;
		int min_flow = INF;
		while (i!=start) {
			min_flow = min(min_flow, c[p[i]][i] - f[p[i]][i]);
			i = p[i];
		}
		// find the min left flow value

		i = end;
		while (i != start) {
			f[p[i]][i] += min_flow;
			f[i][p[i]] -= min_flow;
			i = p[i];
		}
		// update flow value

		result += min_flow;

	}
}
int ctoi(char a) {
	if (a <= 'Z') {
		return a - 'A';
	}
	return a - 'a' + 26;
}