#include "arvore.h"

Arvore* InicializaArvore () {

    Arvore* arvore = malloc(sizeof(Arvore));

    arvore->quantidade = 0;
    arvore->raiz = NULL;

    return arvore;
}

void BalanceaInsere (Node* node) {

    if (GetColor(node) == PRETO) return; // Caso o node seja preto, nenhuma ação é realizada.
    else {
        Node* pai = node->pai; // Declaro node pai.

        if (GetColor(node->pai) == VERMELHO) { // Confiro se o pai é vermelho.
            Node* tio = GetBrother(pai); // Declaro node tio.

            if (GetColor(tio) == PRETO) { // Caso o node não tenha tio.
                if (pai->pai->direita == pai) { // Confiro o pai à direita.
                    if (pai->direita == node) RotacionaEsquerda(pai->pai); // Confiro o filho à direita.
                    else { // Confiro o filho à esquerda.
                        Node* avo = pai->pai;
                        RotacionaDireita(pai);
                        RotacionaEsquerda(avo);
                    }
                }
                else { // Confiro o pai à esquerda.
                    if (pai->esquerda == node) RotacionaDireita(pai->pai); // Confiro o filho à esquerda.
                    else { // Confiro o filho à direita.
                        Node* avo = pai->pai;
                        RotacionaEsquerda(pai);
                        RotacionaDireita(avo);
                    }
                }
            }
            else TrocaCor(pai->pai);
        }
        else return;
    }

}

void Insere (Arvore* arvore, int valor) {

    if (arvore == NULL) return; // Caso a árvore não exista.
    
    InsereArvore(arvore, valor);
    while (arvore->raiz->pai != NULL) arvore->raiz = arvore->raiz->pai; // Atualizando raiz da árvore.
    arvore->raiz->cor = PRETO; // Pintando a raiz de preto.
}

Node* InsereArvore (Arvore* arvore, int valor) {

    if (arvore == NULL) return NULL; // Caso a arvore seja não exista.

    arvore->quantidade++; // Incrementa a quantidade de elementos na árvore em 1.
    if (arvore->raiz == NULL) {
        Node* novo = NovoNo(valor); // Cria um novo node.
        arvore->raiz = novo; // Insere na árvore.
        return novo;
    }
    else {
        Arvore arvore_aux;
        arvore_aux.quantidade = arvore->quantidade;

        if (valor > arvore->raiz->valor) { // Percorrendo a árvore pela direita.
            arvore_aux.raiz = arvore->raiz->direita;
            Node* novo = InsereArvore(&arvore_aux, valor);
            if (GetColor(novo) == VERMELHO && novo->pai == NULL) {
                arvore->raiz->direita = novo;
                novo->pai = arvore->raiz;
            }
            BalanceaInsere(arvore->raiz->direita);
        }
        else if (valor < arvore->raiz->valor){ // Percorrendo a árvore pela esquerda.
            arvore_aux.raiz = arvore->raiz->esquerda;
            Node* novo = InsereArvore(&arvore_aux, valor);
            if (GetColor(novo) == VERMELHO && novo->pai == NULL) {
                arvore->raiz->esquerda = novo;
                novo->pai = arvore->raiz;
            }
            BalanceaInsere(arvore->raiz->esquerda);
        }
        else return NULL;
    }

    return arvore->raiz;
}

Node* NovoNo (int valor) {

    Node* novo = malloc(sizeof(Node)); // Alocando memória para o novo node.

    // Atribuindo características do node.
    novo->valor = valor;
    novo->cor = VERMELHO;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = NULL;

    return novo;
}

void RemoveArvore (Arvore* arvore, int valor) {

    if (arvore == NULL || arvore->raiz == NULL) return; // Caso a arvore não exista ou não tenha elementos.

    Node* aux = arvore->raiz;

    while (aux->valor != valor && aux != NULL) { // Procura o node a ser removido.
        if (valor > aux->valor) aux = aux->direita;
        else aux = aux->esquerda;
        if (aux == NULL) return;    
    }

    RemasteredBalanceaRemove(arvore, aux);
    // BalanceaRemove(arvore, aux); // Remove e balancea a árvore.
    while (arvore->raiz->pai != NULL) arvore->raiz = arvore->raiz->pai; // Atualiza a raiz da árvore.
    arvore->raiz->cor = PRETO; // Pintando a raiz de preto.

}

void Caso_3_1_Remocao (Arvore* arvore, Node* node) {

    Node* irmao = GetBrother(node);

    node->pai->cor = VERMELHO;
    irmao->cor = PRETO;
    RotEsq(node->pai);

    VerificaDuploNegro(arvore, node);
}

void Caso_3_2_Remocao (Arvore* arvore, Node* node) {

    Node* irmao = GetBrother(node);
    Node* aux = node->pai;

    if (GetColor(aux) == VERMELHO) TrocaCor(aux);
    else VerificaDuploNegro(arvore, aux);
}

void Caso_3_3_Remocao (Arvore* arvore, Node* node) {

    Node* irmao = GetBrother(node);

    if (irmao->esquerda != NULL) irmao->esquerda->cor = PRETO;
    irmao->cor = VERMELHO;
    RotDir(irmao);

    Caso_3_4_Remocao(arvore, node);
}

void Caso_3_4_Remocao (Arvore* arvore, Node* node) {

    Node* irmao = GetBrother(node);

    irmao->cor = node->pai->cor;
    node->pai->cor = PRETO;
    if (irmao->direita != NULL) irmao->direita->cor = PRETO;
    RotEsq(node->pai);
    if (GetColor(irmao) == VERMELHO) TrocaCor(irmao);
}

void VerificaDuploNegro (Arvore* arvore, Node* node) {

    Node* irmao = GetBrother(node);

    if (irmao == NULL) return;
    else {
        if (GetColor(irmao) == VERMELHO) Caso_3_1_Remocao(arvore, node);
        else if (GetColor(irmao) == PRETO && GetColor(irmao->direita) == PRETO && GetColor(irmao->esquerda) == PRETO) Caso_3_2_Remocao(arvore, node);
        else if (GetColor(irmao) == PRETO && GetColor(irmao->direita) == PRETO && irmao->esquerda != NULL) Caso_3_3_Remocao(arvore, node);
        else if (GetColor(irmao) == PRETO && GetColor(irmao->direita) == VERMELHO) Caso_3_4_Remocao(arvore, node);
    }

}

void RemasteredBalanceaRemove (Arvore* arvore, Node* node) {

    if (node->esquerda == NULL && node->direita == NULL) { // Caso o node seja uma folha.
        if (GetColor(node) == VERMELHO) RemoveNode(arvore, node); // Se o node for vermelho, apenas remove.
        else {
            if (GetBrother(node) == NULL) RemoveNode(arvore, node); // Caso não tenha irmão.
            else {
                VerificaDuploNegro(arvore, node);
                RemoveNode(arvore, node);
            }
        }
    }
    else if (node->esquerda == NULL || node->direita == NULL) { // Caso o node tenha apenas um filho.
        if (node->esquerda != NULL) node->esquerda->cor = PRETO;
        else node->direita->cor = PRETO;
        RemoveNode(arvore, node);
    }
    else { // Caso o node tenha 2 filhos.
        Node* aux = GetMaiorEsquerda(node);
        node->valor = aux->valor;
        RemasteredBalanceaRemove(arvore, aux);
    }
}

void BalanceaRemove (Arvore* arvore, Node* node) {

    if (node->esquerda == NULL && node->direita == NULL) { // Caso o node seja uma folha.
        if (GetColor(node) == VERMELHO) RemoveNode(arvore, node); // Se o node for vermelho, apenas remove.
        else {
            Node* irmao = GetBrother(node); // Node que aponta a o irmão do node.

            if (irmao == NULL) RemoveNode(arvore, node);
            else if (GetColor(irmao) == PRETO) { // Caso o irmão seja preto
                if (GetColor(irmao->direita) == PRETO && GetColor(irmao->esquerda) == PRETO) { // Caso tenha sobrinhos pretos.
                    RemoveNode(arvore, node);

                    // Conferindo se é necessário um ajuste de cor do avô, ou alguma rotação deste.
                    Node* tio = GetBrother(irmao->pai);
                    if (tio != NULL) {  
                        if (GetColor(tio) == PRETO && GetColor(tio->esquerda) == PRETO && GetColor(tio->direita) == PRETO) {
                            if (GetColor(irmao->pai) == VERMELHO) TrocaCor(irmao->pai);
                            else TrocaCor(irmao);
                        }
                        else if (GetColor(irmao->pai) == PRETO && irmao->pai == tio->pai->esquerda && GetColor(tio) == PRETO && GetColor(tio->direita) == VERMELHO) {
                            RotacionaEsquerda(tio->pai);
                            TrocaCor(tio);
                        }
                        else if (GetColor(irmao->pai) == PRETO && irmao->pai == tio->pai->direita && GetColor(tio) == PRETO && GetColor(tio->esquerda) == VERMELHO) {
                            RotacionaDireita(tio->pai);
                            TrocaCor(tio);
                        }
                    }

                    // Ajustando a cor dos nodes
                    if (!(GetColor(tio) == PRETO && GetColor(tio->esquerda) == PRETO && GetColor(tio->direita) == PRETO)) {
                        if (GetColor(irmao->pai) == VERMELHO) TrocaCor(irmao->pai);
                        else TrocaCor(irmao);
                    }
                }
                else { // Caso tenha algum sobrinho vermelho.
                    if (node == node->pai->esquerda) { // Caso o node seja o filho da esquerda.
                        if (irmao->direita != NULL) { // Caso node tenha subrinho á direita.
                            Node* pai = node->pai;
                            RemoveNode(arvore, node);
                            TrocaCor(pai);
                            RotacionaEsquerda(pai);
                            TrocaCor(irmao);
                        }
                        else { // Caso node tenha subrinho à esquerda.
                            Node* pai = node->pai;
                            RemoveNode(arvore, node);
                            RotacionaDireita(irmao);
                            RotacionaEsquerda(pai);
                            if (GetColor(pai) == VERMELHO) TrocaCor(pai);
                            if (GetColor(irmao) == VERMELHO) TrocaCor(irmao);
                        }
                    }
                    else { // Caso o node seja o filho da direita.
                        if (irmao->esquerda != NULL) { // Caso o node tenha subrinho à esquerda.
                            Node* pai = node->pai;
                            RemoveNode(arvore, node);
                            TrocaCor(pai);
                            RotacionaDireita(pai);
                            TrocaCor(irmao);
                        }
                        else { // Caso o node tenha subrinho à direita.
                            Node* pai = node->pai;
                            RemoveNode(arvore, node);
                            RotacionaEsquerda(irmao);
                            RotacionaDireita(pai);
                            if (GetColor(pai) == VERMELHO) TrocaCor(pai);
                            if (GetColor(irmao) == VERMELHO) TrocaCor(irmao);
                        }
                    }
                }

            }
            else { // Caso o irmão seja vermelho.
                if (node == node->pai->direita) { // Caso o node seja o filho da direita.
                    Node* pai = node->pai;
                    RemoveNode(arvore, node);
                    RotacionaDireita(pai);
                    if (pai->esquerda != NULL && pai->esquerda->esquerda != NULL) {
                        Node* filho = pai->esquerda;
                        if (GetColor(pai) == VERMELHO) TrocaCor(pai);
                        RotacionaDireita(pai);
                        if (GetColor(filho) == PRETO) TrocaCor(filho);
                    } 
                    else if (pai->esquerda != NULL && pai->esquerda->esquerda == NULL && pai->esquerda->direita != NULL) {
                        Node* filho = pai->esquerda;
                        RotacionaEsquerda(filho);
                        RotacionaDireita(pai);
                        if (GetColor(pai) == VERMELHO) TrocaCor(pai);
                        if (GetColor(filho) == VERMELHO) TrocaCor(filho);
                    }
                    else TrocaCor(pai);
                }
                else { // Caso o node seja o filho da esquerda.
                    Node* pai = node->pai;
                    RemoveNode(arvore, node);
                    RotacionaEsquerda(pai);
                    if (pai->direita != NULL && pai->direita->direita != NULL) {
                        Node* filho = pai->direita;
                        if (GetColor(pai) == VERMELHO) TrocaCor(pai);
                        RotacionaEsquerda(pai);
                        if (GetColor(filho) == PRETO) TrocaCor(filho);
                    }
                    else if (pai->direita != NULL && pai->direita->direita == NULL && pai->direita->esquerda != NULL) {
                        Node* filho = pai->direita;
                        RotacionaDireita(filho);
                        RotacionaEsquerda(pai);
                        if (GetColor(pai) == VERMELHO) TrocaCor(pai);
                        if (GetColor(filho) == VERMELHO) TrocaCor(filho);
                    }
                    else TrocaCor(pai);
                }
            }
        }
    }
    else if (node->esquerda == NULL || node->direita == NULL) { // Caso o node tenha apenas um filho.
        if (node->esquerda != NULL) node->esquerda->cor = PRETO;
        else node->direita->cor = PRETO;
        RemoveNode(arvore, node);
    }
    else { // Caso o node tenha 2 filhos.
        Node* aux = GetMaiorEsquerda(node);
        node->valor = aux->valor;
        BalanceaRemove(arvore, aux);
    }
}

void RemoveNode (Arvore* arvore, Node* node) {

    if (node->esquerda == NULL && node->direita == NULL) { // Caso o node seja uma folha.
        if (node == node->pai->direita) node->pai->direita = NULL;
        else node->pai->esquerda = NULL;
        free(node);
    }
    else if (node->esquerda == NULL || node->direita == NULL) { // Caso o node tenha apenas 1 filho.
        if (node->esquerda != NULL) { // Caso o filhos seja na esquerda.
            node->esquerda->pai = node->pai;
            if (node->pai == NULL) arvore->raiz = node->esquerda;
            else {
                if (node->pai->direita == node) node->pai->direita = node->esquerda;
                else node->pai->esquerda = node->esquerda;
            }
            free(node);
        }
        else { // Caso o filho seja na direita.
            node->direita->pai = node->pai;
            if (node->pai == NULL) arvore->raiz = node->direita;
            else {
                if (node->pai->direita == node) node->pai->direita = node->direita;
                else node->pai->esquerda = node->direita;
            }
            free(node);
        }
    }
    else { // Caso o node tenha 2 filhos.
        Node* aux = GetMaiorEsquerda(node);
        node->valor = aux->valor;
        RemoveNode(arvore, aux);
    }
}

Node* GetMaiorEsquerda (Node* node) {

    Node* aux = node->esquerda;

    while (aux->direita != NULL) aux = aux->direita; // Procura o node.

    return aux;
}

void EscreveArvore (Node* raiz) {

    if (raiz == NULL) return; // Caso a raiz seja NULL.
    
    EscreveArvore(raiz->esquerda);
    EscreveArvore(raiz->direita);
}

int GetColor (Node* node) {

    if (node == NULL) return PRETO; // Se o node for NULL, é considerado preto.
    else return node->cor;
}

void TrocaCor (Node* node) {

    node->cor = !node->cor; // Troca a cor do node.

    // Troca a cor dos filhos do node.
    if (node->esquerda != NULL) node->esquerda->cor = !node->esquerda->cor;
    if (node->direita != NULL) node->direita->cor = !node->direita->cor;
}

Node* RotacionaEsquerda (Node* node) {
    
    Node* aux = node->direita; // Variável auxiliar.

    // Manipulação de ponteiros.
    node->direita = aux->esquerda;
    if (aux->esquerda != NULL) aux->esquerda->pai = node;
    aux->esquerda = node;

    aux->pai = node->pai;
    node->pai = aux;

    if (aux->pai != NULL) {
        if (aux->valor > aux->pai->valor) aux->pai->direita = aux;
        else aux->pai->esquerda = aux;
    }

    aux->cor = node->cor;
    node->cor = VERMELHO;
}

Node* RotacionaDireita (Node* node) {
    
    Node* aux = node->esquerda; // Variável auxiliar.

    // Manipulação de ponteiros.
    node->esquerda = aux->direita;
    if (aux->direita != NULL) aux->direita->pai = node;
    aux->direita = node;

    aux->pai = node->pai;
    node->pai = aux;

    if (aux->pai != NULL) {
        if (aux->valor > aux->pai->valor) aux->pai->direita = aux;
        else aux->pai->esquerda = aux;
    }

    aux->cor = node->cor;
    node->cor = VERMELHO;
}

Node* GetBrother (Node* node) {

    if (node == NULL || node->pai == NULL) return NULL; // Caso o node seja NULL, ou não tenha pai.
    
    if (node->pai->esquerda == node) return node->pai->direita;
    else return node->pai->esquerda;
}

Node* RotEsq (Node* node) {

    Node* aux = node->direita; // Variável auxiliar.

    // Manipulação de ponteiros.
    node->direita = aux->esquerda;
    if (aux->esquerda != NULL) aux->esquerda->pai = node;
    aux->esquerda = node;

    aux->pai = node->pai;
    node->pai = aux;

    if (aux->pai != NULL) {
        if (aux->valor > aux->pai->valor) aux->pai->direita = aux;
        else aux->pai->esquerda = aux;
    }
}

Node* RotDir (Node* node) {

    Node* aux = node->esquerda; // Variável auxiliar.

    // Manipulação de ponteiros.
    node->esquerda = aux->direita;
    if (aux->direita != NULL) aux->direita->pai = node;
    aux->direita = node;

    aux->pai = node->pai;
    node->pai = aux;

    if (aux->pai != NULL) {
        if (aux->valor > aux->pai->valor) aux->pai->direita = aux;
        else aux->pai->esquerda = aux;
    }
}