#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <cstring>

using namespace std;

int main() {
    long int tamMB;
    cout << "Tamanho da memoria a ser alocada:" << endl;
    cin >> tamMB;

    //long int tamMB = tamGB * 1024;
    long int elementosPorBloco = (1024 * 1024) / sizeof(int);
    long int qtdBlocos = tamMB;

    // Aloca memória para armazenar os ponteiros dos blocos
    int** blocos = new int*[qtdBlocos];
    bool badAlloc = false;

    // Aloca memória em blocos de 1 MB
    for (long int i = 0; i < qtdBlocos; i++) {
        try {
            blocos[i] = new int[elementosPorBloco];
            memset(blocos[i], 0, elementosPorBloco * sizeof(int));
        } catch (bad_alloc& e) {
            cout << "Falha na alocação de memória no bloco " << i <<endl;
            qtdBlocos = i;
            badAlloc = true;
            break;
        }
    }

    if (badAlloc) {
        cout << "Nao foi possível alocar toda a memoria solicitada." << endl;
    } else {
        cout << "Memoria alocada com sucesso." << endl;
    }

    // Medir o tempo de acesso para diferentes padrões de acesso
    auto start = chrono::high_resolution_clock::now();

    // Acesso sequencial
    for (long int i = 0; i < qtdBlocos; i++) {
        for (long int j = 0; j < elementosPorBloco; j++) {
            blocos[i][j] += 1;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Tempo de acesso sequencial: " << duration / 1e6 << " segundos" << endl;

    start = chrono::high_resolution_clock::now();

    // Acesso aleatório
    for (long int i = 0; i < qtdBlocos; i++) {
        for (long int j = 0; j < elementosPorBloco; j++) {
            long int indiceBloco = rand() % qtdBlocos;
            long int indiceElemento = rand() % elementosPorBloco;
            blocos[indiceBloco][indiceElemento] += 1;
        }
    }

    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Tempo de acesso aleatorio: " << duration / 1e6 << " segundos" << endl;

    // Libera a memória alocada
    for (long int i = 0; i < qtdBlocos; i++) {
        delete[] blocos[i];
    }
    delete[] blocos;

    return 0;
}
