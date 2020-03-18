#include<iostream> // c������ stdio.h // ����� �Լ� ��� ����
#include<vector> // vector �������
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
		fill(flag, flag + src_size+1, false); // fill(first, last) first���� last '��'���� false�� ä��
		if (dfs(i)) { // ��Ī ���� �� true, ���� �� false
			count++;
		}
	}

	cout << count << "���� ��Ī�� �̷�������ϴ�" << endl;
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
		if (flag[dst]) { // �̹� ó���� ����� ��� �� �� �ʿ� ����
			continue;
		}
		flag[dst] = true;
		if (previous[dst] == 0 || dfs(previous[dst])) { // ����ְų�, �ٸ� ������ �����ϸ�
			previous[dst] = source;
			return true;
		}
	}
	return false;
}