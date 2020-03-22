#include<iostream>
#include<vector>
#include<queue>

#define EAST 0
#define SOUTH 1
#define WEST 2
#define NORTH  3

using namespace std;

bool** maze;
bool** flag;
int** cost;
vector<vector<pair<int, int>>> previous;
queue<pair<int, int>> maze_q;
vector<pair<int, int>> direction;

int cnt = 0;

void SetDirection();
void InitMaze(int, int);
void InitPrev(int, int);
int FindPath(int, int, int, int);
void PrintPath(int, int);

int main(void) {
	FILE* fp = fopen("maze_input.txt", "r");
	int row_size, col_size;
	int result;

	fscanf(fp, "%d %d", &row_size, &col_size);
	printf("%d %d\n", row_size, col_size);

	maze = (bool**)malloc(sizeof(bool*)*(row_size+2)); // CAUTION!! size+2 !!!! to block the edges of the maze
	flag = (bool**)malloc(sizeof(bool*)*(row_size + 1));
	cost = (int**)malloc(sizeof(int*)*(row_size + 1));
	for (int i = 0; i <= row_size+1; i++) {
		maze[i] = (bool*)malloc(sizeof(bool)*(col_size+2));
	}

	for (int i = 0; i <= row_size; i++) {
		flag[i] = (bool*)malloc(sizeof(bool)*(col_size + 1));
		cost[i] = (int*)malloc(sizeof(int)*(col_size + 1));
		for (int j = 0; j <= col_size; j++) {
			flag[i][j] = false;
			cost[i][j] = 1;
		}
	}
	// initialize

	InitMaze(row_size, col_size);
	InitPrev(row_size, col_size);
	SetDirection();

	for (int i = 1; i <= row_size; i++) {
		for (int j = 1; j <= col_size; j++) {
			fscanf(fp, "%1d", &maze[i][j]); // Can get just one number from the line !!!!!! ***
		}
	}

	for (int i = 0; i <= row_size+1; i++) {
		for (int j = 0; j <= col_size+1; j++) {
			printf("%d", maze[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	result = FindPath(1, 1, row_size, col_size);

	if (result) {
		printf("Path(cost:%d)\n", result);
		PrintPath(row_size, col_size);
		cout << endl;
	}
	else {
		cout << "Path doesn't exist" << endl;
	}


}
int FindPath(int start_row, int start_col, int row_size, int col_size) {
	pair<int, int> now;
	int row, col, next_row, next_col;

	now.first = start_row;
	now.second = start_col;

	maze_q.push(now);
	flag[now.first][now.second] = true;

	while (!maze_q.empty()) {
		now = maze_q.front();

		row = now.first;
		col = now.second;

		if (row == row_size && col == col_size) {
			return cost[row][col];
		}
		for (int i = 0; i <4; i++) {
			next_row = row + direction[i].first;
			next_col = col + direction[i].second;

			if (maze[next_row][next_col]) { // if it has a way to move
				if (!flag[next_row][next_col]) { // and is not visited

					maze_q.push(make_pair(next_row, next_col)); // push into the queue
					flag[next_row][next_col] = true; // and you must set the flag true right after you push into the queue !!!!!!!!!!!!!!!!!

					previous[next_row][next_col] = now; // update path
					cost[next_row][next_col] = cost[row][col] + 1;  // update distance

				}
			}
		}

		maze_q.pop();
	}
	return false;
}
void PrintPath(int dst_row, int dst_col) {
	vector<pair<int, int>> result;
	pair<int, int> temp;
	int row, col;

	row = dst_row;
	col = dst_col;

	while (row!=-1 && col!=-1) {
		temp = make_pair(row, col);
		result.push_back(temp);
		row = previous[temp.first][temp.second].first;
		col = previous[temp.first][temp.second].second;
	}

	cnt = result.size();

	while (!result.empty()) {
		printf("(%d, %d) ", result.back().first, result.back().second);
		result.pop_back();
		if (result.empty()) {
			printf("\n");
			break;
		}
		printf("-> ");
	}

}
void InitMaze(int row, int col) {
	for (int i = 0; i <= row+1; i++) {
		for (int j = 0; j <= col+1; j++) {
			maze[i][j] = false;
		}
	}
}
void InitPrev(int row, int col) {
	vector<pair<int, int>> temp;

	for (int i = 0; i <= row; i++) {
		for (int j = 0; j <= col; j++) {
			temp.push_back(make_pair(-1, -1));
		}
		previous.push_back(temp);
	}
}
void SetDirection() {
	direction.push_back(make_pair(0, 1));
	direction.push_back(make_pair(1, 0));
	direction.push_back(make_pair(0, -1));
	direction.push_back(make_pair(-1, 0));
}