#include<iostream>
//#include<algorithm>

using namespace std;

int* result;

int Tile(int n) {
	if (n == 1) {
		return 1;
	}
	if (n == 2) {
		return 2;
	}
	if (result[n] != 0) {
		return result[n];
	}
	return result[n] = (Tile(n - 1) + Tile(n - 2)) % 10007;
	// if return without %10007, the result value will be too big to save in int array
}
int main(void) {
	int n;
	int answer;

	scanf("%d", &n);

	result = (int*)malloc(sizeof(int)*(n + 1));
	fill(result, result + n + 1, 0);

	answer = Tile(n)%10007;

	printf("%d\n", answer);
}