#include<iostream>
#include<vector>
#define INF 999999

using namespace std;

int main(void) {
	FILE* fp;
	int max_distance, num;
	int* distance, *previous;
	int* time;
	int* cost;
	int sum = 0;

	if (!(fp = fopen("race_input.txt", "r"))) {
		fprintf(fp, "Cannot open file\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d %d", &max_distance, &num);

	distance = (int*)malloc(sizeof(int)*(num+2));
	previous = (int*)malloc(sizeof(int)*(num+2));
	time = (int*)malloc(sizeof(int)*(num + 1));
	cost = (int*)malloc(sizeof(int)*(num + 2));


	for (int i = 1; i < num + 2; i++) {
		fscanf(fp, "%d", &distance[i]);
	}

	for (int i = 1; i < num + 1; i++) {
		fscanf(fp, "%d", &time[i]);
	}

	cost[0] = 0;
	for (int i = 1; i < num + 2; i++) {
		cost[i] = INF;
	}

	for (int i = 0; i < num + 2; i++) {
		previous[i] = -1;
	}

	for (int i = 0; i <= num; i++) {
		sum = 0;
		for (int j = i + 1; j <= num + 1; j++) {
			sum += distance[j];
			if (sum <= max_distance) {
				if (cost[j] > cost[i] + time[j]) {
					cost[j] = cost[i] + time[j];
					previous[j] = i;
				}
			}
		}
	}

	int i = previous[num+1];
	vector<int> result;
	int total_time = 0;
	int visited_num = 0;

	while (i != 0) {
		result.push_back(i);
		total_time += time[i];
		visited_num++;
		i = previous[i];
	}

	printf("%d\n%d\n", total_time, visited_num);
	while (!result.empty()) {
		printf("%d ", result.back());
		result.pop_back();
	}
	printf("\n");

}