#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Grau mínimo (t) da árvore B
#define GRAU_MINIMO 3

// Estrutura para o nó da árvore B
typedef struct NoArvoreB
{
    int *chaves;               // Array de chaves
    int grau;                  // Grau mínimo
    struct NoArvoreB **filhos; // Array de ponteiros para os filhos
    int numeroChaves;          // Número atual de chaves
    bool ehFolha;              // Verdadeiro se for um nó folha
} NoArvoreB;

// Estrutura para a árvore B
typedef struct ArvoreB
{
    NoArvoreB *raiz;
    int grau; // Grau mínimo
} ArvoreB;

// Função para criar um novo nó da árvore B
NoArvoreB *criarNo(int grau, bool ehFolha)
{
    NoArvoreB *novoNo = (NoArvoreB *)malloc(sizeof(NoArvoreB));
    novoNo->grau = grau;
    novoNo->ehFolha = ehFolha;
    novoNo->chaves = (int *)malloc(sizeof(int) * (2 * grau - 1));
    novoNo->filhos = (NoArvoreB **)malloc(sizeof(NoArvoreB *) * (2 * grau));
    novoNo->numeroChaves = 0;
    return novoNo;
}

// Função para criar uma árvore B vazia
ArvoreB *criarArvoreB(int grau)
{
    ArvoreB *arvore = (ArvoreB *)malloc(sizeof(ArvoreB));
    arvore->grau = grau;
    arvore->raiz = criarNo(grau, true);
    return arvore;
}

// Função para buscar uma chave em um nó
NoArvoreB *buscar(NoArvoreB *no, int chave)
{
    int i = 0;
    while (i < no->numeroChaves && chave > no->chaves[i])
    {
        i++;
    }
    if (i < no->numeroChaves && chave == no->chaves[i])
    {
        return no;
    }
    if (no->ehFolha)
    {
        return NULL;
    }
    else
    {
        return buscar(no->filhos[i], chave);
    }
}

// Função para dividir o filho y de x no índice i
void dividirFilho(NoArvoreB *pai, int indice, NoArvoreB *filho)
{
    int grau = filho->grau;
    NoArvoreB *novoFilho = criarNo(grau, filho->ehFolha);
    novoFilho->numeroChaves = grau - 1;

    for (int j = 0; j < grau - 1; j++)
    {
        novoFilho->chaves[j] = filho->chaves[j + grau];
    }

    if (!filho->ehFolha)
    {
        for (int j = 0; j < grau; j++)
        {
            novoFilho->filhos[j] = filho->filhos[j + grau];
        }
    }

    filho->numeroChaves = grau - 1;

    for (int j = pai->numeroChaves; j >= indice + 1; j--)
    {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[indice + 1] = novoFilho;

    for (int j = pai->numeroChaves - 1; j >= indice; j--)
    {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[indice] = filho->chaves[grau - 1];
    pai->numeroChaves++;
}

// Função para inserir em um nó não cheio
void inserirEmNoNaoCheio(NoArvoreB *no, int chave)
{
    int i = no->numeroChaves - 1;

    if (no->ehFolha)
    {
        while (i >= 0 && chave < no->chaves[i])
        {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numeroChaves++;
    }
    else
    {
        while (i >= 0 && chave < no->chaves[i])
        {
            i--;
        }
        i++;
        if (no->filhos[i]->numeroChaves == 2 * no->grau - 1)
        {
            dividirFilho(no, i, no->filhos[i]);
            if (chave > no->chaves[i])
            {
                i++;
            }
        }
        inserirEmNoNaoCheio(no->filhos[i], chave);
    }
}

// Função para inserir uma nova chave na árvore B
void inserir(ArvoreB *arvore, int chave)
{
    NoArvoreB *raiz = arvore->raiz;

    if (raiz->numeroChaves == 2 * arvore->grau - 1)
    {
        NoArvoreB *novaRaiz = criarNo(arvore->grau, false);
        novaRaiz->filhos[0] = raiz;
        dividirFilho(novaRaiz, 0, raiz);

        int i = 0;
        if (novaRaiz->chaves[0] < chave)
        {
            i++;
        }
        inserirEmNoNaoCheio(novaRaiz->filhos[i], chave);

        arvore->raiz = novaRaiz;
    }
    else
    {
        inserirEmNoNaoCheio(raiz, chave);
    }
}

// Função para imprimir a árvore B
void percorrer(NoArvoreB *no)
{
    int i;
    for (i = 0; i < no->numeroChaves; i++)
    {
        if (!no->ehFolha)
        {
            percorrer(no->filhos[i]);
        }
        printf("%d ", no->chaves[i]);
    }
    if (!no->ehFolha)
    {
        percorrer(no->filhos[i]);
    }
}

int main()
{
    ArvoreB *arvore = criarArvoreB(GRAU_MINIMO);

    inserir(arvore, 10);
    inserir(arvore, 20);
    inserir(arvore, 5);
    inserir(arvore, 6);
    inserir(arvore, 12);
    inserir(arvore, 30);
    inserir(arvore, 7);
    inserir(arvore, 17);

    printf("Percorrendo a árvore B construída: ");
    percorrer(arvore->raiz);
    printf("\n");

    return 0;
}
