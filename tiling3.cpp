#include<iostream>
using namespace std;
int* result;
int Tile3(int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return 0;
	if (n == 2)
		return 3;
	if (result[n])
		return result[n];
	
	result[n] = 3 * Tile3(n - 2);
	int size = 4;
	while (size<=n) {
		result[n] += 2 * Tile3(n - size);
		size = size + 2;
	}
	return result[n];
}
int main(void) {
	int n;
	int answer;
	scanf("%d", &n);
	result = (int*)malloc(sizeof(int)*(n + 1));
	fill(result, result + n + 1, 0);

	answer = Tile3(n);
	printf("%d\n", answer);
}