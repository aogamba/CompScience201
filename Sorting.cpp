//Sorting
//Ashley Ogamba
//14444055


#include<iostream>
#include<vector>
#include<chrono>//high resolution clock
#include<algorithm>//std copy

using namespace std;

void selectionSort(int arr[], int n)
{

	//search through array, keep track with min, and swap

	//it's of O(n^2) complexity ///really bad 

	int min = 0;
	int temp = 0;
	int count = 0;

	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
		{

			if (arr[min] > arr[j])
			{
				min = j;
				count++;
			}
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
		

	}
	

}

void insertionSort(int arr[], int n)
{
	int count = 0;
	for (int i = 1; i < n; i++)
	{
		int temp = arr[i];
		int j = i - 1;

		while (j>=0 && arr[j]>temp) {
			arr[j + 1] = arr[j];
			j--;
			count++;
		}
		arr[j + 1] = temp;
	}

}



void merge(int a[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j]) {
            a[k++] = L[i++];
            //i++;
        }
        else {
            a[k++] = R[j++];
            //j++;
        }
       
    }

    while (i < n1)
    {
        a[k++] = L[i++];
       
    }

    while (j < n2)
    {
        a[k++] = R[j++];
       
    }
}

void mergesort(int a[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;
        mergesort(a, l, m);
        mergesort(a, m + 1, r);

        merge(a, l, m, r);
    }
}


int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int mid = low;
    for (int i = low; i < high; i++)
    {
        if (arr[i] < pivot)
        {
            if (mid != i) {
                int temp = arr[i];
                arr[i] = arr[mid];
                arr[mid] = temp;
            }
            mid++;
        }

    }
    arr[high] = arr[mid];
    arr[mid] = pivot;
    return mid;

}
void quickSort(int arr[], int low, int high)
{
    if (low >= high)
        return;
    int mid = partition(arr, low, high);
    quickSort(arr, low, mid - 1);
    quickSort(arr, mid + 1, high);

}
void bubbleSort(int arr[], int n)
{
    int temp;
    for (int i = 0;i <n - 1; i++)
    {
        for (int j = 0;  j <n-i-1; j++)
        {
            int temp;
            if (arr[i] > arr[j+1])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;

            }
        }
    }
}

void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = source[i];
}

// ==== TIMING FUNCTION ====
void benchmarkSort(void(*sortFunc)(int[], int), const string& name, int original[], int n) {
    int* temp = new int[n];
    copyArray(original, temp, n);

    auto start = chrono::high_resolution_clock::now();
    sortFunc(temp, n);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    cout << name << ": " << duration.count() << " seconds" << endl;

    delete[] temp;
}
void benchmarkMergeSort(int original[], int n) {
    int* temp = new int[n];
    copyArray(original, temp, n);

    auto start = chrono::high_resolution_clock::now();
    mergesort(temp, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    cout << "Merge Sort: " << duration.count() << " seconds" << endl;

    delete[] temp;
}

void benchmarkQuickSort(int original[], int n) {
    int* temp = new int[n];
    copyArray(original, temp, n);

    auto start = chrono::high_resolution_clock::now();
    quickSort(temp, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = end - start;
    cout << "Quick Sort: " << duration.count() << " seconds" << endl;

    delete[] temp;
}

// ==== MAIN ====
int main() {
    const int ARRAY_SIZE = 500;
    int original[ARRAY_SIZE];

    // Populate with random numbers
    srand(time(0));// seed
    for (int i = 0; i < ARRAY_SIZE; i++)
        original[i] = rand() % 500;//range 0-999

    cout << "Array: ";

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << original[i] <<" ";
    }

    cout << "Sorting performance for array size = " << ARRAY_SIZE << endl << endl;

    benchmarkSort(selectionSort, "Selection Sort", original, ARRAY_SIZE);
    benchmarkSort(insertionSort, "Insertion Sort", original, ARRAY_SIZE);
    benchmarkSort(bubbleSort, "Bubble Sort", original, ARRAY_SIZE);
    benchmarkMergeSort(original, ARRAY_SIZE);
    benchmarkQuickSort(original, ARRAY_SIZE);

    return 0;
}
