// DESENVOLVIMENTO DA ÁRVORE AVL - NÉLIO ESPÍNDULA JUNIOR CC6N
// DIÁRIO DE BORDO (15/09/2024)

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Função para criar um novo nó
Node* newNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalanceFactor(struct Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// =-=-=-=- ROTAÇÕES =-=-=-=- //
// A função recebe como parâmetro o nó que está desbalanceado:
Node *rightRotate(Node *unbalanced) {
    Node *new_root = unbalanced->left; 
    // Defino a nova raiz como sendo o filho à 
    // esquerda do nó desbalanceado.
    Node *node_subtree = new_root->right; 
    // Defino o filho à esquerda do novo nó será a 
    // subárvore da direita na minha raiz.

    new_root->right = unbalanced;
    unbalanced->left = node_subtree;

    // Atualização das alturas com base na verificação de cada uma das subárvores.
    unbalanced->height = max(height(unbalanced->left), height(unbalanced->right)) + 1;
    new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

    return new_root;
}
// A função recebe como parâmetro o nó que está desbalanceado:
Node *leftRotate(Node *unbalanced_node) {
    // Defino a nova raiz como sendo o filho à
    // direita do nó desbalanceado.
    Node *new_root = unbalanced_node->right;
    // Defino o filho à direita do novo nó será a
    // subárvore da esquerda na minha raiz. 
    Node *node_subtree = new_root->left;

    new_root->left = unbalanced_node;
    unbalanced_node->right = node_subtree;

    // Atualização das alturas com base na verificação de cada uma das subárvores.
    unbalanced_node->height = max(height(unbalanced_node->left), height(unbalanced_node->right)) + 1;
    new_root->height = max(height(new_root->left), height(new_root->right)) + 1;

    return new_root;
}
// =-=-=-=- ROTAÇÕES =-=-=-=- //

struct Node *balanceTree(struct Node *node_root, int value) {
    if (node_root == NULL) {
        return node_root;
    }
    // Atualiza a altura do nó atual
    node_root->height = 1 + max(height(node_root->left), height(node_root->right));

    int balance = getBalanceFactor(node_root);

    // Verificação para rotações a fim de balancear a arvore

     // Caso de rotação simples à direita
    if (balance > 1 && value < node_root->left->value)
        return rightRotate(node_root);

    // Caso de rotação simples à esquerda
    if (balance < -1 && value > node_root->right->value)
        return leftRotate(node_root);

    // Rotação esquerda-direita
    if (balance > 1 && value > node_root->left->value) {
        node_root->left = leftRotate(node_root->left);
        return rightRotate(node_root);
    }

    // Rotação direita-esquerda
    if (balance < -1 && value < node_root->right->value) {
        node_root->right = rightRotate(node_root->right);
        return leftRotate(node_root);
    }
    
    // Retorna a árvore já balanceada.
    return node_root;
}

struct Node *insert(struct Node *node_root, int value) {
   if (node_root == NULL)
        return newNode(value);

    if (value < node_root->value)
        node_root->left = insert(node_root->left, value);
    else if (value > node_root->value)
        node_root->right = insert(node_root->right, value);
    else
        return node_root;

    return balanceTree(node_root, value);
}

struct Node *findMinimunValue(struct Node *node) {
    struct Node *current_minimun = node;

    // Acha o nó mais à esquerda
    while (current_minimun && current_minimun->left != NULL) {
        current_minimun = current_minimun->left;
    }

    return current_minimun;
}

struct Node *findMaximumValue(struct Node *node){
    struct Node *current_maximum = node;

    if (current_maximum == NULL)
        return NULL;

    // Acha o nó mais à direita
    while (current_maximum->right != NULL) {
        current_maximum = current_maximum->right;
    }

    return current_maximum;
}

struct Node *delete(struct Node *node_root, int value) {
    if (node_root == NULL) {
        return node_root;
    }

    if (value < node_root->value) {
        node_root->left = delete(node_root->left, value);
    } else if (value > node_root->value) {
        node_root->right = delete(node_root->right, value);
    } else {
        if ((node_root->left == NULL) || (node_root->right == NULL)) {
            Node *temporary_root = node_root->left ? node_root->left : node_root->right;

            if (temporary_root == NULL) {
                temporary_root = node_root;
                node_root = NULL;
            } else {
                *node_root = *temporary_root;
            }

            free(temporary_root);
        } else {
            if (height(node_root->left) > height(node_root->right)) {
                Node *temporary_root = findMaximumValue(node_root->left);
                node_root->value = temporary_root->value;
                node_root->left = delete(node_root->left, temporary_root->value);
            } else {
                Node *temporary_root = findMinimunValue(node_root->right);
                node_root->value = temporary_root->value;
                node_root->right = delete(node_root->right, temporary_root->value);
            }
        }
    return balanceTree(node_root, value);
    }  
}

void inOrder(struct Node *node_root) {
    if (node_root != NULL) {
        inOrder(node_root->left);
        printf("%d ", node_root->value);
        inOrder(node_root->right);
    }
}

void preOrder(struct Node *node_root) {
    if (node_root != NULL) {
        printf("%d ", node_root->value);
        preOrder(node_root->left);
        preOrder(node_root->right);
    }
}

void postOrder(struct Node *node_root) {
    if (node_root != NULL) {
        postOrder(node_root->left);
        postOrder(node_root->right);
        printf("%d ", node_root->value);
    }
}

void printNode(int value, int spaces) {
    int i;
    for (i = 0; i < spaces; i++)
        printf("   ");
    printf("%i\n", value);
}

void showTree(struct Node *node_root, int spaces) {
    if (node_root != NULL) {
        showTree(node_root->right, spaces + 1);
        printNode(node_root->value, spaces);
        showTree(node_root->left, spaces + 1);
    }
}

struct Node *findNode(struct Node *node_root, int value) {
    if (node_root == NULL || node_root->value == value) {
        return node_root;
    }

    if (value < node_root->value) {
        return findNode(node_root->left, value);
    } else {
        return findNode(node_root->right, value);
    }
}

int treeHeight(struct Node *node_root) {
    if (node_root == NULL) {
        return -1;
    }
    
    int leftHeight = height(node_root->left);
    int rightHeight = height(node_root->right);

    return (max(leftHeight, rightHeight) + 1);
}

int isBinarySearchTree(struct Node *node_root, int minimun_value, int maximum_value) {
    if (node_root == NULL) {
        return 1;
    }

    if ((node_root->value <= minimun_value) || (node_root->value >= maximum_value)) {
        return 0;
    }

    return isBinarySearchTree(node_root->left, minimun_value, node_root->value) && isBinarySearchTree(node_root->right, node_root->value, maximum_value);

}

// UMA ÁRVORE AVL É VALIDA:
//      1) SE A DIFERENÇA DO FATOR DE BALANCEAMENTO DAS SUBARVORES
//      DE CADA NÓ FOR 1, -1 OU 0;
//      2) SE A ÁRVORE FOR UMA ÁRVORE DE BUSCA BINÁRIA;
int isValidAVLTree(struct Node *node_root) {
    if (node_root == NULL) {
        return 1;
    }
    
    int minimun_value = findMinimunValue(node_root->right)->value;
    int maximum_value = findMaximumValue(node_root->left)->value;

    if (!isBinarySearchTree(node_root, minimun_value, maximum_value)) {
        return 0;
    }

    int balance = getBalanceFactor(node_root);

    if (balance > 1 || balance < -1) {
        return 0;
    }

    return isValidAVLTree(node_root->left) && isValidAVLTree(node_root->right);

}

int main()
{

    struct Node *root = NULL;
    //Inserindo elementos na árvore AVL
    root = insert(root, 30);
    root = insert(root, 24);
    root = insert(root, 20);
    root = insert(root, 35);
    root = insert(root, 27);
    root = insert(root, 33);
    root = insert(root, 38);
    root = insert(root, 25);
    root = insert(root, 22);
    root = insert(root, 34);
    root = insert(root, 40);
    root = insert(root, 29);
    showTree(root, 3);
   
    printf("\nLetra A - Insere 31 ---------------------------\n");
    root = insert(root, 31);
    showTree(root, 3);
   
    printf("\nLetra B - Insere 15 ---------------------------\n");
    root = insert(root, 15);
    showTree(root, 3);
   
    printf("\nLetra C - Insere 23 ----------------------------\n");
    root = insert(root, 23);
    showTree(root, 3);
   
    printf("\nLetra D - Exclui 24 ---------------------------\n");
    root = delete(root, 24);
    showTree(root, 3);
   
    printf("\nLetra E - Exclui 35 ---------------------------\n");
    root = delete(root, 35);
    showTree(root, 3);

     printf("\nLetra F - insert 24 ---------------------------\n");
    root = insert(root, 24);
    showTree(root, 3);

     printf("\nLetra G - Exclui 27 ---------------------------\n");
    root = delete(root, 27);
    showTree(root, 3);

     printf("\nLetra H - insert 32 ---------------------------\n");
    root = insert(root, 32);
    showTree(root, 3);

     printf("\nLetra I - Exclui 30 ---------------------------\n");
    root = delete(root, 30);
    showTree(root, 3);
    
    printf("\nLetra J - insert 21 ---------------------------\n");
    root = insert(root, 21);
    showTree(root, 3);

    return 0;
}
