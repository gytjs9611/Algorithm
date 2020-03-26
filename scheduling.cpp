#include<iostream>
#include<vector>
#include<algorithm>

#define SIMPLE 0
#define WEIGHTED 1


typedef struct jobnode {
	int job, deadline, profit;
} tJob;

int* parent;
int* empty; // for weighted scheduling
int* schedule;
int sum = 0;

std::vector<tJob> input;

void Initialize(int);
tJob MakeJob(int, int, int);
bool Compare(tJob, tJob);

void WeightedScheduling(int);
void SimpleScheduling(int);
void Scheduling(int, int);

int CollapsingFind(int);
void WeightedUnion(int, int);
void SimpleUnion(int, int);

void PrintSchedule(int);

int main(void) {
	FILE* fp;
	int size;
	int job, deadline, profit;


	if (!(fp = fopen("scheduling_input.txt", "r"))) {
		fprintf(stderr, "Cannot Open File\n");
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%d", &size);

	parent = (int*)malloc(sizeof(int)*(size + 1));
	empty = (int*)malloc(sizeof(int)*(size + 1));
	schedule = (int*)malloc(sizeof(int)*(size + 1));

	Initialize(size);

	for (int i = 0; i < size; i++) {
		fscanf(fp, "%d %d %d", &job, &deadline, &profit);
		input.push_back(MakeJob(job, deadline, profit));
	}
	std::sort(input.begin(), input.end(), Compare); // sort in descending order

	std::cout << "Simple Scheduling ..." << std::endl;
	Scheduling(SIMPLE, size);
	PrintSchedule(size);
	printf("sum = %d\n", sum);
	printf("\n\n");

	Initialize(size);
	std::cout << "Weighted Scheduling ..." << std::endl;
	Scheduling(WEIGHTED, size);
	PrintSchedule(size);
	printf("sum = %d\n", sum);
	printf("\n");


}
void SimpleScheduling(int size) {
	int job, deadline, profit;
	int root, next_empty;

	for (int i = 0; i < size; i++) {
		job = input[i].job;
		deadline = input[i].deadline;
		profit = input[i].profit;

		root = CollapsingFind(deadline); // find the empty space
		if (root == 0) {
			continue;
		}
		schedule[root] = job; // put the job into there
		sum += profit;

		next_empty = CollapsingFind(root - 1);
		SimpleUnion(root, next_empty); // root is connected to next_empty (root->next_empty)
	}
}
int CollapsingFind(int v) { // for minmizing the height of the tree
	int ptr = v;
	int root, temp;

	while (parent[v] >= 0) {
		v = parent[v];
	}
	root = v;

	while (parent[ptr] >= 0) {
		temp = parent[ptr]; // save next destination
		parent[ptr] = root; // update parent to root value
		ptr = temp; // update pointer to next destination
	}

	return root;
}
void SimpleUnion(int v1, int v2) {
	parent[v1] = v2;
}
void WeightedScheduling(int size) {
	int job, deadline, profit;
	int root, now_empty, next_empty;
	
	for (int i = 0; i < size; i++) {
		job = input[i].job;
		deadline = input[i].deadline;
		profit = input[i].profit;

		root = CollapsingFind(deadline);
		now_empty = empty[root];

		if (now_empty == 0) { // it has no place to go
			continue;
		}

		schedule[now_empty] = job;
		sum += profit;
		
		next_empty = CollapsingFind(now_empty - 1);
		WeightedUnion(root, next_empty);
	}
}
void WeightedUnion(int v1, int v2) { // connect like v1->v2
	int temp = parent[v1] + parent[v2];
	if (parent[v1] < parent[v2]) {
		parent[v1] = temp;
		parent[v2] = v1;
		empty[v1] = empty[v2];
		// connect like v2->v1
		// so, when visit v1 and then empty[v1] to find the empty space
		// empty[v1] must be same as empty[v2]
	}
	else { // connect like v1->v2
		parent[v1] = v2;
		parent[v2] = temp;
	}
}
void Scheduling(int choice, int size) {
	switch (choice) {
	case SIMPLE:
		SimpleScheduling(size);
		break;
	case WEIGHTED:
		WeightedScheduling(size);
		break;
	default:
		fprintf(stderr, "Wrong Choice\n");
		exit(EXIT_FAILURE);
		return;
	}
}
void PrintSchedule(int size) {
	printf("Deadline : ");
	for (int i = 1; i <= size; i++) {
		printf("%2d ", i);
	}
	printf("\nJob      : ");
	for (int i = 1; i <= size; i++) {
		printf("%2d ", schedule[i]);
	}
}
tJob MakeJob(int j, int d, int p) {
	tJob temp;
	temp.job = j;
	temp.deadline = d;
	temp.profit = p;
	return temp;
}
bool Compare(tJob j1, tJob j2) {
	return j1.profit > j2.profit;
}
void Initialize(int size) {
	for (int i = 0; i <= size; i++) {
		parent[i] = -1;
		empty[i] = i;
		schedule[i] = -1;
	}
	sum = 0;
}