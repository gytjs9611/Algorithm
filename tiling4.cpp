#include<iostream>
using namespace std;

long long int *result;
int Tile4(int n) {
	long long int sum = 0;
	result[0] = 1;
	result[1] = 2;
	result[2] = 7;

	
	for (int i = 3; i <= n; i++) {
		sum += 2 * result[i - 3];
		result[i] = (2 * result[i - 1] + 3 * result[i - 2] + sum) % 1000000007;
	}
	
	return result[n];
}
int main(void) {
	int n;
	int answer;
	scanf("%d", &n);
	result = (long long int*)malloc(sizeof(long long int)*(n + 1));
	fill(result, result + n + 1, 0);
	answer = Tile4(n);
	printf("%d\n", answer);
}