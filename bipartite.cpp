/* Bipartite : 공통 자원에 대해 최적으로 배분하는 문제 */
#include<iostream>
#include<vector>
#define MAX 101

using namespace std;

vector<int> source_vertex[MAX]; // source vertex의 개수 최대 100개(인덱스 1~100, 0번 안씀)
//source_vertex[i]에 i와 연결되어있는 destination vertex를 저장함

int* previous;
bool* flag;

bool dfs(int);
int main(void) {
	FILE* fp = fopen("input2.txt", "r");
	int src_size, dst_size, edge_size;
	int src, dst;
	int count = 0;

	fscanf(fp, "%d %d %d", &src_size, &dst_size, &edge_size);

	previous = (int*)malloc(sizeof(int)*(dst_size + 1)); // previous[i] = j; => j->i 연결되어있음
	flag = (bool*)malloc(sizeof(bool)*(dst_size + 1)); // dfs할 때 destination과 연결 확인 중임을 표시
	// ★ previous와 flag는 dst 개수만큼 할당해야한다는 것 잊지말기!!!

	for (int i = 0; i < dst_size + 1; i++) {
		previous[i] = -1;
		flag[i] = false;
	}

	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d", &src, &dst); // src->dst 로 연결되어있음
		source_vertex[src].push_back(dst); // c언어일 경우, 각 src마다 top인덱스를 가져야함
	}

	//for (int i = 1; i <= src_size; i++) {
	//	cout << i << " : ";
	//	for (int j = 0; j < source_vertex[i].size(); j++) {
	//		cout << source_vertex[i][j] <<" ";
	//	}
	//	cout << endl;
	//}


	for (int i = 1; i <= src_size; i++) {
		fill(flag, flag + dst_size + 1, false); // flag는 src vertex 한 개 내에서만 유효하므로 초기화시켜줌
		if (dfs(i)) {
			count++;
		}
	}

	cout << "matching complete : " << count << endl;

	for (int i = 1; i <= dst_size; i++) {
		if (previous[i] != -1) {
			cout << previous[i] << " -> " << i << endl;
		}
	}

}
bool dfs(int src) {
	int dst;
	// 만약 인접리스트로 한다면 ptr에 adjList[src]를 넣고 ptr->link 해가면서 확인, 나머지는 다 똑같이 구현 가능

	for (int i = 0; i < source_vertex[src].size(); i++) {
		dst = source_vertex[src][i]; // dst에 src와 연결된 vertex들 차례로 넣음
		if (flag[dst]) {
			continue;
		}
		flag[dst] = true;
		// dst에 연결된 것이 아무것도 없다 or dst에 연결된 노드가 다른 노드 선택이 가능하다
		if (previous[dst] == -1 || dfs(previous[dst])) {
			previous[dst] = src;
			return true;
		}
	}
	return false;
}