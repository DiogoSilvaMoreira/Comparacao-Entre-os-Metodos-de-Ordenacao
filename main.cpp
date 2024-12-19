/* Nome: Diogo da Silva Moreira         RA: 2023.1.08.003
 * Nome: Caio Henrique Costa de Matos   RA: 2023.1.08.002
 * 
 * Data: 07/07/2023
 *
 * Objetivo: Entender as distinções entre os métodos de ordenação e adquirir
 *conhecimento sobre uma abordagem de comparação de
 *algoritmos e aprender a elaborar relatórios dos experimentos realizados.
 * 
 */

#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

void print_array(int vetor[], int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        cout << " " << vetor[i];
    }
}

void ordenar_vetor(int vetor[], int qtd_elem_vetor) {
    for (int step = 1; step < qtd_elem_vetor; step++) {
        int key = vetor[step];
        int j = step - 1;
        while (key < vetor[j] && j >= 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = key;
    }
}

void desordenar_vetor(int vetor[], int qtd_elem_vetor) {
    for (int step = 1; step < qtd_elem_vetor; step++) {
        int key = vetor[step];
        int j = step - 1;
        while (key > vetor[j] && j >= 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = key;
    }
}
//Implementação do Selection Sort.

int selectionSort(int vetor[], int qtd_elem_vetor) {
    int array[qtd_elem_vetor] = {}, cont = 0;
    for (int i = 0; i < qtd_elem_vetor; i++) {
        array[i] = vetor[i];
    }

    for (int step = 0; step < qtd_elem_vetor - 1; step++) {
        int min_idx = step;
        for (int i = step + 1; i < qtd_elem_vetor; i++) {
            cont += 2;
            if (array[i] < array[min_idx]) {
                min_idx = i;
            }
            int temp = array[min_idx];
            array[min_idx] = array[step];
            array[step] = temp;
            cont += 4;
        }
    }
    return cont;
}

//Implementação do Insertion Sort

int insertionSort(int vetor[], int qtd_elem_vetor) {
    int array[qtd_elem_vetor] = {}, cont = 0;
    for (int i = 0; i < qtd_elem_vetor; i++) {
        array[i] = vetor[i];
    }

    for (int step = 1; step < qtd_elem_vetor; step++) {
        int key = array[step];
        cont++;
        int j = step - 1;

        cont++;
        while (key < array[j] && j >= 0) {
            array[j + 1] = array[j];
            cont += 2;
            j--;
        }
        array[j + 1] = key;
        cont++;
    }
    return cont;
}
//Implementação do Bubble Sort

int bubbleSort(int vetor[], int qtd_elem_vetor) {
    int array[qtd_elem_vetor] = {}, cont = 0;
    for (int i = 0; i < qtd_elem_vetor; i++) {
        array[i] = vetor[i];
    }

    for (int i = 0; i < qtd_elem_vetor - 1; i++) {
        for (int j = 0; j < qtd_elem_vetor - i; j++) {
            cont += 2;
            if (array[j] > array[j + 1]) {
                int aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
                cont += 4;
            }
        }
    }
    return cont;
}

int main(int argc, char** argv) {

    //Declaração das variáveis.
    int qtd_valores = 0, valor_maximo = 0, intervalo = 0;
    int contador_bubble = 0, contador_insertion = 0, contador_selection = 0;

    //Solicitando dados para o usuário.
    cout << "Insira a quantidade de valores não-repetidos do vetor: ";
    cin >> qtd_valores;
    while (qtd_valores <= 1 || qtd_valores >= 100000) {
        cout << "Insira um valor maior que 1 e menor que 100.000! ";
        cin >> qtd_valores;
    }

    cout << "Insira o valor máximo a ser gerado: ";
    cin >> valor_maximo;
    while (valor_maximo <= qtd_valores) {
        cout << "Insira um valor maior que " << qtd_valores << "! ";
        cin >> valor_maximo;
    }
    cout << "Insira o intervalo entre os vetores: ";
    cin >> intervalo;
    while (intervalo <= 0 || intervalo > qtd_valores) {
        cout << "Insira um valor menor que " << qtd_valores << "! ";
        cin >> intervalo;
    }

    // Criando arquivo de valores aleatórios.
    ofstream valores_aleatorios("ValoresAleatorios.txt"); //Abrindo como escrita.
    if (!valores_aleatorios.is_open()) {
        cerr << "Não foi possível abrir o arquivo para escrita! Saindo...";
        return 1;
    }
    //Adicionando o número de elementos na primeira linha do arquivo.
    valores_aleatorios << qtd_valores << endl;

    // Gerando valores aleatórios para o arquivo.
    int VETOR_ALEATORIO[qtd_valores] = {}, aux = 0, valor = 0;
    srand((unsigned) time(NULL)); // Alimentando a seed de valores aleatórios.
    for (int i = 0; i < qtd_valores; i++) {
        valor = rand() % valor_maximo;
        int j = 0;
        while (j < qtd_valores) {
            if (valor == VETOR_ALEATORIO[j]) {
                valor = rand() % valor_maximo;
                j = 0;
            } else {
                j++;
            }
        }

        aux = valor;
        VETOR_ALEATORIO[i] = aux;
        valores_aleatorios << aux << endl;
    }
    valores_aleatorios.close();

    // Abrindo o arquivo de valores aleatórios para leitura.
    ifstream valores_random("ValoresAleatorios.txt");
    if (!valores_random.is_open()) {
        cerr << "Não foi possível abrir o arquivo para leitura! Saindo...";
        return 1;
    }
    // Abrindo arquivo de contadores em vetor aleatório.
    ofstream aleatorio("aleatorio.csv");
    if (!aleatorio.is_open()) {
        cerr << "Não foi possível abrir o arquivo para escrita! Saindo...";
        return 1;
    }

    //Impressão dos resultados com ordenção aleatória.
    cout << "Vetor aleatório:" << endl;
    cout << "N° Elem. \tBubble \t\tInsertion \tSelection" << endl;

    for (int i = intervalo; i <= qtd_valores; i += intervalo) {
        int VETOR[i] = {};
        valores_random.seekg(0);
        valores_random >> VETOR[0];
        for (int j = 0; j < i; j++) {
            valores_random >> VETOR[j];
        }

        contador_bubble = bubbleSort(VETOR, i);
        contador_insertion = insertionSort(VETOR, i);
        contador_selection = selectionSort(VETOR, i);

        cout << i << "\t\t" << contador_bubble << "\t\t" << contador_insertion
                << "\t\t" << contador_selection << endl;
        aleatorio << i << "," << contador_bubble << "," << contador_insertion
                << "," << contador_selection << endl;
    }
    aleatorio.close();


    //Abrindo arquivo de contadores em vetor crescente
    ofstream crescente("crescente.csv");
    if (!crescente.is_open()) {
        cerr << "Não foi possível abrir o arquivo para escrita! Saindo...";
        return 1;
    }

    //Impressão dos resultados com ordenção crescente.    
    cout << "\n\nVetor crescente:" << endl;
    cout << "N° Elem. \tBubble \t\tInsertion \tSelection" << endl;

    for (int i = intervalo; i <= qtd_valores; i += intervalo) {
        int VETOR[i] = {};
        valores_random.seekg(0);
        valores_random >> VETOR[0];
        for (int j = 0; j < i; j++) {
            valores_random >> VETOR[j];
        }
        ordenar_vetor(VETOR, i);
        contador_bubble = bubbleSort(VETOR, i);
        contador_insertion = insertionSort(VETOR, i);
        contador_selection = selectionSort(VETOR, i);

        cout << i << "\t\t" << contador_bubble << "\t\t" << contador_insertion
                << "\t\t" << contador_selection << endl;
        crescente << i << "," << contador_bubble << "," << contador_insertion
                << "," << contador_selection << endl;
    }
    crescente.close();


    //Abrindo arquivo de contadores em vetor decrescente.
    ofstream decrescente("decrescente.csv");
    if (!decrescente.is_open()) {
        cerr << "Não foi possível abrir o arquivo para escrita! Saindo...";
        return 1;
    }

    //Impressão dos resultados com ordenção decrescente.    
    cout << "\n\nVetor decrescente:" << endl;
    cout << "N° Elem. \tBubble \t\tInsertion \tSelection" << endl;

    for (int i = intervalo; i <= qtd_valores; i += intervalo) {
        int VETOR[i] = {};
        valores_random.seekg(0);
        valores_random >> VETOR[0];
        for (int j = 0; j < i; j++) {
            valores_random >> VETOR[j];
        }
        desordenar_vetor(VETOR, i);
        contador_bubble = bubbleSort(VETOR, i);
        contador_insertion = insertionSort(VETOR, i);
        contador_selection = selectionSort(VETOR, i);

        cout << i << "\t\t" << contador_bubble << "\t\t" << contador_insertion
                << "\t\t" << contador_selection << endl;
        decrescente << i << "," << contador_bubble << "," << contador_insertion
                << "," << contador_selection << endl;
    }
    decrescente.close();

    //Fechando o arquivo de valores aleatórios.
    valores_random.close();

    cout << "Vetor aleatório:" << endl;
    cout << "N° Elem. \tBubble \t\tInsertion \tSelection" << endl;

    for (int i = intervalo; i <= qtd_valores; i += intervalo) {
        // Seu código para obter os contadores dos algoritmos

        printf("%8d \t%8d \t%8d \t%8d\n", i, contador_bubble, contador_insertion, contador_selection);
    }

    // Seu código existente...

    return 0;
}

    
   