/* Bipartite : ���� �ڿ��� ���� �������� ����ϴ� ���� */
#include<iostream>
#include<vector>
#define MAX 101

using namespace std;

vector<int> source_vertex[MAX]; // source vertex�� ���� �ִ� 100��(�ε��� 1~100, 0�� �Ⱦ�)
//source_vertex[i]�� i�� ����Ǿ��ִ� destination vertex�� ������

int* previous;
bool* flag;

bool dfs(int);
int main(void) {
	FILE* fp = fopen("input2.txt", "r");
	int src_size, dst_size, edge_size;
	int src, dst;
	int count = 0;

	fscanf(fp, "%d %d %d", &src_size, &dst_size, &edge_size);

	previous = (int*)malloc(sizeof(int)*(dst_size + 1)); // previous[i] = j; => j->i ����Ǿ�����
	flag = (bool*)malloc(sizeof(bool)*(dst_size + 1)); // dfs�� �� destination�� ���� Ȯ�� ������ ǥ��
	// �� previous�� flag�� dst ������ŭ �Ҵ��ؾ��Ѵٴ� �� ��������!!!

	for (int i = 0; i < dst_size + 1; i++) {
		previous[i] = -1;
		flag[i] = false;
	}

	for (int i = 0; i < edge_size; i++) {
		fscanf(fp, "%d %d", &src, &dst); // src->dst �� ����Ǿ�����
		source_vertex[src].push_back(dst); // c����� ���, �� src���� top�ε����� ��������
	}

	//for (int i = 1; i <= src_size; i++) {
	//	cout << i << " : ";
	//	for (int j = 0; j < source_vertex[i].size(); j++) {
	//		cout << source_vertex[i][j] <<" ";
	//	}
	//	cout << endl;
	//}


	for (int i = 1; i <= src_size; i++) {
		fill(flag, flag + dst_size + 1, false); // flag�� src vertex �� �� �������� ��ȿ�ϹǷ� �ʱ�ȭ������
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
	// ���� ��������Ʈ�� �Ѵٸ� ptr�� adjList[src]�� �ְ� ptr->link �ذ��鼭 Ȯ��, �������� �� �Ȱ��� ���� ����

	for (int i = 0; i < source_vertex[src].size(); i++) {
		dst = source_vertex[src][i]; // dst�� src�� ����� vertex�� ���ʷ� ����
		if (flag[dst]) {
			continue;
		}
		flag[dst] = true;
		// dst�� ����� ���� �ƹ��͵� ���� or dst�� ����� ��尡 �ٸ� ��� ������ �����ϴ�
		if (previous[dst] == -1 || dfs(previous[dst])) {
			previous[dst] = src;
			return true;
		}
	}
	return false;
}