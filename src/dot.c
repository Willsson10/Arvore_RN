#include "dot.h"

void InicioDot (char* fn) {

    FILE* dot = fopen(fn, "w"); // Abre o arquivo para escrita.

    fprintf(dot, "digraph RadialTree {\n\n"); // Escre o começo do .dot.
    
    fclose(dot);    
}

void EscreveDot (char* fn, Arvore* arvore) {

    if (arvore == NULL || arvore->raiz == NULL) return;

    FILE* dot = fopen(fn, "a+");

    if (arvore->raiz != NULL) {
        if (arvore->raiz->cor == VERMELHO) fprintf (dot, "\t%d [style=filled, fillcolor = red, fontcolor = white]\n", arvore->raiz->valor);
        else fprintf (dot, "\t%d [style=filled, fillcolor = black, fontcolor = white]\n", arvore->raiz->valor);
    }
    if (arvore->raiz->esquerda != NULL) {
        if (arvore->raiz->esquerda->cor == VERMELHO) fprintf (dot, "\t%d [style=filled, fillcolor = red, fontcolor = white]\n", arvore->raiz->esquerda->valor);
        else fprintf (dot, "\t%d [style=filled, fillcolor = black, fontcolor = white]\n", arvore->raiz->esquerda->valor);
        fprintf (dot, "\t%d -> %d\n", arvore->raiz->valor, arvore->raiz->esquerda->valor);
    }
    if (arvore->raiz->direita != NULL) {
        if (arvore->raiz->direita->cor == VERMELHO) fprintf (dot, "\t%d [style=filled, fillcolor = red, fontcolor = white]\n", arvore->raiz->direita->valor);
        else fprintf (dot, "\t%d [style=filled, fillcolor = black, fontcolor = white]\n", arvore->raiz->direita->valor);
        fprintf (dot, "\t%d -> %d\n", arvore->raiz->valor, arvore->raiz->direita->valor);
    }

    Arvore arvore_aux;
    arvore_aux.quantidade = arvore->quantidade;
    
    arvore_aux.raiz = arvore->raiz->esquerda;
    EscreveDot(fn, &arvore_aux);
    arvore_aux.raiz = arvore->raiz->direita;
    EscreveDot(fn, &arvore_aux);

    fclose(dot);
}

void FimDot (char* fn) {

    FILE* dot = fopen(fn, "a+"); // Abre o arquivo para edição.

    fprintf(dot, "}"); // Fecha o .dot.

    fclose(dot);
}