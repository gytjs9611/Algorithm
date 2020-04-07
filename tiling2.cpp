#include<iostream>
using namespace std;
int* result;

int Tile2(int n) {
	if (n == 1)
		return 1;
	if (n == 2)
		return 3;
	if (result[n])
		return result[n];
	return result[n] = (Tile2(n - 1) + 2 * Tile2(n - 2)) % 10007;
}
int main(void) {
	int n;
	int answer;
	scanf("%d", &n);
	result = (int*)malloc(sizeof(int)*(n + 1));
	fill(result, result + n + 1, 0);
	answer = Tile2(n);
	printf("%d", answer);
}