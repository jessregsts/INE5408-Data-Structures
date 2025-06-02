#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i, int &swaps) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        swaps++;
        heapify(arr, n, largest, swaps);
    }
}

void heapSort(int arr[], int n) {
    int swaps = 0;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, swaps);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        swaps++;
        heapify(arr, i, 0, swaps);
    }
    cout << "Número total de trocas: " << swaps << endl;
}

int main() {
    srand(time(NULL));
    int n = 10;
    int arr[n];

    cout << "Valores escolhidos: ";
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
        cout << arr[i] << " ";
    }
    cout << endl;

    heapSort(arr, n);

    cout << "Valores ordenados: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
