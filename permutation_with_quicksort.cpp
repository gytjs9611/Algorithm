#include<iostream>
#include<time.h>

#define MAX_STRING_SIZE 100
#define swap(a,b){int temp; temp = a; a= b; b = temp;}
using namespace std;

int cnt = 0;

void Permutation(char*, int, int);
void RandomQuickSort(char*, int, int);
int ReturnPivotIndex(char*, int, int);

int main(void) {
	char input[MAX_STRING_SIZE];
	int input_size;

	cout << "input string : ";
	cin >> input;
	cout << endl << "( Check your input string : " << input << " )" << endl;

	input_size = strlen(input);

	cout << "\nPermuation Result ..." << endl;


	RandomQuickSort(input, 0, input_size - 1);
	// sort first ( It means, "cab" is same as "abc" )

	Permutation(input, 0, input_size - 1);

	cout << "\nThe number of Result : " << cnt << endl;

}
void Permutation(char* data, int first, int last) {
	if (first >= last) { // Ȥ�� first==last
		cnt++;
		cout << data << endl;
		return;
	}

	Permutation(data, first + 1, last);
	RandomQuickSort(data, first + 1, last);

	for (int i = first + 1; i <= last; i++) {
		if (data[first] < data[i]) { // if data is bigger than first data, swap
			swap(data[first], data[i]);
			Permutation(data, first + 1, last);
			RandomQuickSort(data, first + 1, last);
		}
	}

}
void RandomQuickSort(char* data, int first, int last) {
	int pivot_index;

	if (first <= last) { // ** !! DO NOT FORGET THE EXIT CONDITION !! **
		pivot_index = ReturnPivotIndex(data, first, last);
		RandomQuickSort(data, first, pivot_index - 1);
		RandomQuickSort(data, pivot_index + 1, last);
	}
	

}
int ReturnPivotIndex(char* data, int first, int last) {
	srand(time(NULL));

	int pivot_index = first + rand() % (last - first + 1);
	int pivot_data = data[pivot_index];
	int head_of_large, i;

	swap(data[last], data[pivot_index]);
	// exchange pivot and last data
	// then the pivot is located at the end of the array

	head_of_large = first;
	// 'head_of_large' always points the head of the group whose items are larger than pivot data


	for (i = first; i < last; i++) {
		if (data[i] <= pivot_data) { // if data smaller than pivot appear, swap with head_of_large
			swap(data[i], data[head_of_large]);
			head_of_large++;
		}
	}
	
	swap(data[last], data[head_of_large]);
	
	return head_of_large; // return pivot position
}
