/*
    Este módulo possui funções para ser gerado um arquivo .dot,
    o qual, ao ser interpretado, consegue representar de forma visual
    a árvore binária rubro negra.

    Para visualizar o arquivo .dot, acesse:
    https://dreampuf.github.io/GraphvizOnline
*/

#ifndef _DOT_H
#define _DOT_H

#include "arvore.h"

/*
    Função a qual escreve o início de um arquivo .dot,
    de caminho/nome "fn".
*/
void InicioDot (char* fn);

/*
    Função a qual escreve o corpo do arquivo .dot. Escreve
    de uma forma, para representar a árvore binária rubro negra
    "arvore". O caminho/nome do arquivo é "fn".
*/
void EscreveDot (char* fn, Arvore* arvore);

/*
    Função a qual escreve o fim de um arquivo .dot,
    de caminho/nome "fn".
*/
void FimDot (char* fn);

#endif