// DESENVOLVIMENTO DA ÁRVORE REDBLACK - NÉLIO ESPÍNDULA JUNIOR CC6N
// DIÁRIO DE BORDO (29/09/2024)

#include <stdio.h>
#include <stdlib.h>

// Definição dos possíveis valores de cor
#define VERMELHO 0
#define PRETO 1

// estrutura do nó da árvore Red-Black
typedef struct No
{
    int valor;
    int cor;
    struct No *esquerda, *direita, *pai;
} No;

// Função para criar nó
No *criar_no(int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->cor = VERMELHO;
    novoNo->esquerda = novoNo->direita = novoNo->pai = NULL;
    return novoNo;
}

// Função para fazer a rotação à esquerda
void rotacao_esquerda(No **raiz, No *x)
{
    No *y = x->direita;       // 'y' vai ser o novo pai de 'x'
    x->direita = y->esquerda; // Move o filho esquerdo de 'y' para a direita de 'x'
    if (y->esquerda != NULL)
        y->esquerda->pai = x; // Ajusta o pai se o filho esquerdo de 'y' existir
    y->pai = x->pai;          // Conecta o pai de 'x' ao novo nó 'y'
    if (x->pai == NULL)
        *raiz = y; // Se 'x' for raiz, 'y' agora é a nova raiz
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    else
        x->pai->direita = y;
    y->esquerda = x; // Ajusta a nova posição de 'x'
    x->pai = y;
}

// Função para fazer a rotação à direita
// ( mesma lógica da rotação à esquerda, porém invertida )
void rotacao_direita(No **raiz, No *x)
{
    No *y = x->esquerda;
    x->esquerda = y->direita;
    if (y->direita != NULL)
        y->direita->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        *raiz = y;
    else if (x == x->pai->direita)
        x->pai->direita = y;
    else
        x->pai->esquerda = y;
    y->direita = x;
    x->pai = y;
}

// Função para balancear a árvore após a inserção de um nó
void corrigir_violacao(No **raiz, No *no)
{
    // Continua corrigindo enquanto houver violações
    while (no != *raiz && no->pai->cor == VERMELHO)
    {
        // Caso onde o pai de 'no' é filho esquerdo do avô
        if (no->pai == no->pai->pai->esquerda)
        {
            No *x = no->pai->pai->direita; // Tio de 'no'
            if (x != NULL && x->cor == VERMELHO)
            {
                // Caso 1: Tio é vermelho - recolorir
                no->pai->cor = PRETO;
                x->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                no = no->pai->pai;
            }
            else
            {
                // Caso 2: 'no' é filho direito - rotaciona para a esquerda
                if (no == no->pai->direita)
                {
                    no = no->pai;
                    rotacao_esquerda(raiz, no);
                }
                // Caso 3: Recolorir e rotacionar à direita
                no->pai->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                rotacao_direita(raiz, no->pai->pai);
            }
        }
        else // Caso simétrico ao anterior
        {
            No *x = no->pai->pai->esquerda;
            if (x != NULL && x->cor == VERMELHO)
            {
                no->pai->cor = PRETO;
                x->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                no = no->pai->pai;
            }
            else
            {
                if (no == no->pai->esquerda)
                {
                    no = no->pai;
                    rotacao_direita(raiz, no);
                }
                no->pai->cor = PRETO;
                no->pai->pai->cor = VERMELHO;
                rotacao_esquerda(raiz, no->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO; // A raiz sempre deve ser preta
}

// Função para inserir um novo nó na árvore
void inserir(No **raiz, int valor)
{
    No *z = criar_no(valor); // Cria o novo nó
    No *y = NULL;
    No *x = *raiz;

    // Encontra a posição correta para inserir o novo nó
    while (x != NULL)
    {
        y = x;
        if (z->valor < x->valor)
            x = x->esquerda;
        else
            x = x->direita;
    }

    z->pai = y; // Define o pai do novo nó
    if (y == NULL)
        *raiz = z; // Se a árvore estava vazia, o novo nó é a raiz
    else if (z->valor < y->valor)
        y->esquerda = z;
    else
        y->direita = z;

    // Corrige violações das propriedades da Red-Black
    corrigir_violacao(raiz, z);
}

// Função para buscar um valor na árvore
No *buscar(No *raiz, int valor)
{
    while (raiz != NULL && valor != raiz->valor)
    {
        if (valor < raiz->valor)
            raiz = raiz->esquerda;
        else
            raiz = raiz->direita;
    }
    return raiz;
}

// Função para imprimir a árvore em ordem
void em_ordem(No *raiz)
{
    if (raiz != NULL)
    {
        em_ordem(raiz->esquerda);
        if (raiz->cor == VERMELHO)
            printf("%d RED\n", raiz->valor);
        else
            printf("%d BLK\n", raiz->valor);
        em_ordem(raiz->direita);
    }
}

// Função para imprimir a árvore de acordo com o formato esquerda-raiz-direita
void imprimir_arvore(No *raiz, int b)
{
    if (raiz != NULL)
    {
        imprimir_arvore(raiz->direita, b + 1);
        for (int i = 0; i < b; i++)
            printf("       ");
        if (raiz->cor == VERMELHO)
            printf("\033[31m%d\033[0m\n\n", raiz->valor);
        else
            printf("%d\n\n", raiz->valor);
        imprimir_arvore(raiz->esquerda, b + 1);
    }
}

int main()
{
    struct No *raiz = NULL;
    int opcao, valor;

    do
    {
        printf("1 - Inserir valor\n");
        printf("2 - Buscar valor\n");
        printf("3 - Exibir árvore em ordem\n");
        printf("4 - Exibir árvore Red-Black formatada\n");
        printf("5 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor a ser inserido: ");
            scanf("%d", &valor);
            inserir(&raiz, valor);
            break;
        case 2:
            printf("Digite o valor a ser buscado: ");
            scanf("%d", &valor);
            if (buscar(raiz, valor) != NULL)
                printf("Valor %d encontrado na árvore.\n", valor);
            else
                printf("Valor %d não encontrado na árvore.\n", valor);
            break;
        case 3:
            printf("Árvore em ordem:\n");
            em_ordem(raiz);
            break;
        case 4:
            printf("Árvore Red-Black formatada:\n");
            imprimir_arvore(raiz, 0);
            break;
        case 5:
            printf("FIM !! \n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
        }
        printf("\n");
    } while (opcao != 5);

    return 0;
}