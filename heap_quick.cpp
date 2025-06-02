#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#define tInfo int
#define quantidade 20

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
    cout << "Número total de trocas para Heapsort: " << swaps << endl;
}

int particione(tInfo *A, int p, int r, int &trocas) {
    int i;
    tInfo x, tmp;
    int tamanho = (r - p) + 1;
    int pos = (rand() % tamanho) + p;
    x = A[pos];
    tmp = A[pos];
    A[pos] = A[r];
    A[r] = tmp;
    i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
            trocas++;
        }
    }
    tmp = A[i + 1];
    A[i + 1] = A[r];
    A[r] = tmp;
    trocas++;
    return i + 1;
}

int quicksort(tInfo *A, int p, int r) {
    int q;
    int trocas = 0;
    if (p < r) {
        q = particione(A, p, r, trocas);
        trocas += quicksort(A, p, q - 1);
        trocas += quicksort(A, q + 1, r);
    }
    return trocas;
}

int main() {
    int i;
    int a[quantidade];

    unsigned seed = time(0);
    srand(seed);

    for (int c = 0; c < quantidade; c++) {
        int numero = rand() % 10000;
        a[c] = numero;
    }

    int total_trocas = quicksort(a, 0, quantidade - 1);

    cout << "Número total de trocas para Quicksort: " << total_trocas << endl;

    heapSort(a, quantidade);

    // Imprimir o array ordenado
    for (i = 0; i < quantidade; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
