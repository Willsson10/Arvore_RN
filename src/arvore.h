/*
    Este módulo possui funções de manipulação de uma árvore binária
    rubro negra. Possuindo funções de inserção, remoção, balanceamento
    e escrita.

    Também possui funções auxiliares, as quais auxiliam na manipulação da árvore.

    Aqui também são declaradas as structs que constituem as estruturas da árvore.
*/

#ifndef _ARVORE_H
#define _ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct node {
    int valor;
    int cor;
    struct node* esquerda;
    struct node* direita;
    struct node* pai;
} Node;

typedef struct arvore {
    int quantidade;
    Node* raiz;
} Arvore;

#define VERMELHO 1
#define PRETO 0

/*
    Função a qual inicializa uma nova árvore, e retorna
    o ponteiro para ela.
*/
Arvore* InicializaArvore ();

/*
    Função a qual realiza rotações e mudanças de cor,
    para balancear um node "node" da arvore binaria RB.
*/
void BalanceaInsere (Node* node);

/*
    Função onde é chamada a função de inserção na árvore binária
    RB. Atualiza a raiz da árvore e pinta-a de PRETO.
*/
void Insere (Arvore* arvore, int valor);

/*
    Função onde ocorre a inserção de um node de valor "valor"
    na árvore binária RB "arvore".
*/
Node* InsereArvore (Arvore* arvore, int valor);

/*
    Função a qual aloca memória para um novo node de valor "valor".
    E retorna o ponteiro para o node novo.
*/
Node* NovoNo (int valor);

/*
    Função a qual irá remover elemento de valor "valor"
    da árvore binária rubro negra "arvore". E irá atualizar
    a sua raiz.
*/
void RemoveArvore (Arvore* arvore, int valor);

/*
    Função a qual realiza a remoção e balanceamento do node
    "node", da árvore binária rubro negra "arvore".
*/
void BalanceaRemove (Arvore* arvore, Node* node);

/*
    Função a qual realiza a remoção no node "node",
    dando free nele.
*/
void RemoveNode (Arvore* arvore, Node* node);

/*
    Função a qual retorna o maior node da esquerda, em
    relação ao node "node".
*/
Node* GetMaiorEsquerda (Node* node);

/*
    Escreve os nodes de uma arvore binaria "arvore" no terminal.
*/
void EscreveArvore (Node* raiz);

/*
    Retorna a cor de um node "node". Vermelho ou preto.
*/
int GetColor (Node* node);

/*
    Inverte a cor de um node "node" e de seus filhos.
*/
void TrocaCor (Node* node);

/*
    Função a qual realiza uma rotação à esquerda do node "node".
*/
Node* RotacionaEsquerda (Node* node);

/*
    Função a qual realiza uma rotação à direita do node "node".
*/
Node* RotacionaDireita (Node* node);

/*
    Função a qual retora o node "irmão" do node "node".
    Caso não tenha irmão, retorna NULL.
*/
Node* GetBrother (Node* node);








void Caso_3_1_Remocao (Arvore* arvore, Node* node);

void Caso_3_2_Remocao (Arvore* arvore, Node* node);

void Caso_3_3_Remocao (Arvore* arvore, Node* node);

void Caso_3_4_Remocao (Arvore* arvore, Node* node);

void VerificaDuploNegro (Arvore* arvore, Node* node);

void RemasteredBalanceaRemove (Arvore* arvore, Node* node);

Node* RotEsq (Node* node);

Node* RotDir (Node* node);

#endif