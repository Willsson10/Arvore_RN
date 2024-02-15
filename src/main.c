/*
    Este projeto, se trata da implementação de uma árvore binária rubro
    negra, na linguagem C.

    Caso queira saber mais afundo sobre a árvore rubro negra, acesso a página:
    https://www.ime.usp.br/~song/mac5710/slides/08rb.pdf

    Neste projeto, serão implementadas funções para a manipulação da árvore rubro negra.
    Como inserção, remoção e balanceamento. Além de funções auxiliares para elas. Também, 
    terão funções para escrever um arquivo, com o qual, será possível a visualização da
    árvore.

    O programa utiliza como entrada, as funções de inserção dentro do programa, 
    e gera uma saída .dot. Além de outros dois arquivos .txt, os quais mostram, em ordem
    os elementos inseridos e removidos da árvore binária rubro negra.

    Todos osa arquivos de saída, estarão dentro da pasta "Saída".

    Para visualizar a saída .dot, acesse:
    https://dreampuf.github.io/GraphvizOnline

    Para conferir a RB Tree, acesse:
    https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
*/

#include "headers.h"
#include <time.h>

int main () {

    Arvore* arvore = InicializaArvore();

    FILE* inseridos = fopen("Saída/Inseridos.txt", "w"); // Arquivo para escrever os elementos inseridos.
    FILE* removidos = fopen("Saída/Removidos.txt", "w"); // Arquivo para escrever os elementos removidos.

    srand(time(NULL));

    int valores[64];
    for (int i=0; i<64; i++) valores[i] = (-1);

    // Inserindo valores aleatórios.
    for (int i=0; i<64; i++) {
        int valor = rand() % 500;
        Insere(arvore, valor);
        valores[i] = valor;
        fprintf(inseridos, "%d\n", valor);
    }

    // Removendo valores aleatórios.
    for (int i=0; i<32; i++) {
        int valor = rand() % 64;
        if (valores[valor] != -1) {
            RemoveArvore(arvore, valores[valor]);
            fprintf(removidos, "%d\n", valores[valor]);
            valores[valor] = -1;
        }
    }

    // Escrevendo o .dot.
    InicioDot("Saída/RB.dot");
    EscreveDot("Saída/RB.dot", arvore);
    FimDot("Saída/RB.dot");

    fclose(inseridos);
    fclose(removidos);

    return 0;
}