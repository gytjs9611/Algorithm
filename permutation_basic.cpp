/* Permutation_ver1 : 주어진 문자열의 모든 순열을 출력하는 문제 (문자열중복없음) */
#include<iostream>
#define MAX 100
#define swap(a, b, temp) temp = a; a = b; b = temp;

using namespace std;

int cnt = 0;

void permutation(char*, const int, const int);
int main(void) {
	char input[MAX];
	int size;

	cout << "input data >> ";
	cin >> input;

	cout << "check your data : " << input << endl;

	size = strlen(input);

	permutation(input, 0, size - 1); // input array, first, last

	cout << "total : " << cnt << " permutations" << endl;

}
void permutation(char* a, const int first, const int last) {  // permutate from first to last
	int temp;

	if (first == last) { // no more things to swap, so print
		cout << a << endl;
		cnt++;
	}
	else {
		for (int i = first; i <= last; i++) {
			swap(a[first], a[i], temp); // swap first and i
			permutation(a, first + 1, last); // permutate from first+1 to last
			swap(a[first], a[i], temp); // turn back to first state for the next loop
		} // and do it again
	}


}