#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura para um nó na Treap
typedef struct NoTreap
{
    int chave;           // Chave do nó
    int prioridade;      // Prioridade do nó
    struct NoTreap *esq; // Ponteiro para o filho esquerdo
    struct NoTreap *dir; // Ponteiro para o filho direito
} NoTreap;

// Função para criar um novo nó na Treap
NoTreap *criarNoTreap(int chave)
{
    NoTreap *novoNo = (NoTreap *)malloc(sizeof(NoTreap));
    novoNo->chave = chave;
    novoNo->prioridade = rand() % 100; // Prioridade aleatória
    novoNo->esq = novoNo->dir = NULL;
    return novoNo;
}

// Função para rotação à direita
NoTreap *rotacaoDireita(NoTreap *y)
{
    NoTreap *x = y->esq;
    NoTreap *T2 = x->dir;

    // Rotação
    x->dir = y;
    y->esq = T2;

    return x;
}

// Função para rotação à esquerda
NoTreap *rotacaoEsquerda(NoTreap *x)
{
    NoTreap *y = x->dir;
    NoTreap *T2 = y->esq;

    // Rotação
    y->esq = x;
    x->dir = T2;

    return y;
}

// Função para inserir uma nova chave na Treap
NoTreap *inserir(NoTreap *raiz, int chave)
{
    // Passo 1: Inserir a chave como em uma árvore binária de busca normal
    if (!raiz)
        return criarNoTreap(chave);

    if (chave < raiz->chave)
    {
        raiz->esq = inserir(raiz->esq, chave);

        // Passo 2: Verificar propriedade de heap
        if (raiz->esq->prioridade > raiz->prioridade)
        {
            raiz = rotacaoDireita(raiz);
        }
    }
    else
    {
        raiz->dir = inserir(raiz->dir, chave);

        // Passo 2: Verificar propriedade de heap
        if (raiz->dir->prioridade > raiz->prioridade)
        {
            raiz = rotacaoEsquerda(raiz);
        }
    }

    return raiz;
}

// Função para buscar uma chave na Treap
NoTreap *buscar(NoTreap *raiz, int chave)
{
    if (!raiz || raiz->chave == chave)
    {
        return raiz;
    }

    if (chave < raiz->chave)
    {
        return buscar(raiz->esq, chave);
    }
    else
    {
        return buscar(raiz->dir, chave);
    }
}

// Função para deletar uma chave na Treap
NoTreap *deletar(NoTreap *raiz, int chave)
{
    if (!raiz)
        return raiz;

    if (chave < raiz->chave)
    {
        raiz->esq = deletar(raiz->esq, chave);
    }
    else if (chave > raiz->chave)
    {
        raiz->dir = deletar(raiz->dir, chave);
    }
    else
    {
        // Nó encontrado
        if (!raiz->esq)
        {
            NoTreap *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if (!raiz->dir)
        {
            NoTreap *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Nó com dois filhos
        if (raiz->esq->prioridade < raiz->dir->prioridade)
        {
            raiz = rotacaoEsquerda(raiz);
            raiz->esq = deletar(raiz->esq, chave);
        }
        else
        {
            raiz = rotacaoDireita(raiz);
            raiz->dir = deletar(raiz->dir, chave);
        }
    }

    return raiz;
}

// Função para percorrer a Treap em ordem
void percorrerInOrdem(NoTreap *raiz)
{
    if (raiz)
    {
        percorrerInOrdem(raiz->esq);
        printf("Chave: %d | Prioridade: %d\n", raiz->chave, raiz->prioridade);
        percorrerInOrdem(raiz->dir);
    }
}

int main()
{
    srand(time(0)); // Inicializa a geração de números aleatórios

    NoTreap *raiz = NULL;

    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    printf("Percorrendo a Treap em ordem:\n");
    percorrerInOrdem(raiz);

    printf("\nDeletando a chave 20\n");
    raiz = deletar(raiz, 20);
    printf("Percorrendo a Treap após deletar 20:\n");
    percorrerInOrdem(raiz);

    return 0;
}
