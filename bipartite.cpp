#include<iostream> // c언어에서의 stdio.h // 입출력 함수 사용 위해
#include<vector> // vector 사용위해
#define MAX 101

using namespace std;

vector<int> vertex[MAX];
int* previous;
bool* flag;

bool dfs(int);
int main(void) {
	FILE* fp = fopen("bipartite_input.txt", "r");
	int src_size, dst_size, edge_size;
	int source, destination;

	fscanf(fp, "%d %d %d", &src_size, &dst_size, &edge_size);

	previous = (int*)malloc(sizeof(int)*(dst_size + 1));
	flag = (bool*)malloc(sizeof(bool)*(src_size + 1));

	for (int i = 0; i < dst_size + 1; i++) {
		previous[i] = 0;
	}

	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d", &source, &destination);
		printf("%d %d\n", source, destination);
		vertex[source].push_back(destination);
	}
	
	for (int i = 1; i <= src_size; i++) {
		printf("%d : ", i);
		int size = vertex[i].size();
		for (int j = 0; j < size; j++) {
			printf("%d ", vertex[i][j]);
		}
		printf("\n");
	}


	int count = 0;

	for (int i = 1; i <= src_size; i++) {
		fill(flag, flag + src_size+1, false); // fill(first, last) first부터 last '전'까지 false로 채움
		if (dfs(i)) { // 매칭 성공 시 true, 실패 시 false
			count++;
		}
	}

	cout << count << "개의 매칭이 이루어졌습니다" << endl;
	for (int i = 1; i <= dst_size; i++) {
		if(previous[i]){
			cout << previous[i] << "->" << i << endl;
		}
	}

	return 0;
}
bool dfs(int source) {
	for (int i = 0; i < vertex[source].size(); i++) {
		int dst = vertex[source][i];
		if (flag[dst]) { // 이미 처리한 노드일 경우 더 볼 필요 없음
			continue;
		}
		flag[dst] = true;
		if (previous[dst] == 0 || dfs(previous[dst])) { // 비어있거나, 다른 선택이 가능하면
			previous[dst] = source;
			return true;
		}
	}
	return false;
}