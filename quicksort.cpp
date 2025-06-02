// Esse código novo calcula as trocas. Espero q esteja certo =]
#include <iostream>
#include <cstdlib>
#include <ctime>

#define tInfo int
#define quantidade 1000

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

    std::cout << "Número total de trocas para quicksort: " << total_trocas << std::endl;

    // Imprimir o array ordenado
    for (i = 0; i < quantidade; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
