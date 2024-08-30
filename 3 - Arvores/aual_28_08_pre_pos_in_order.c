#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_MAX 100

// STRUCTURES


struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
};

struct Stack
{
    int top;
    struct Node* arr[STACK_MAX];
};


// STRUCTURES

void initializeStack(struct Stack *stack)
{
    stack->top = -1;
}

bool isStackEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

bool isStackFull(struct Stack *stack)
{
    return stack->top == STACK_MAX - 1;
}

void push(struct Stack *stack, struct Node* value)
{
    if (isStackFull(stack))
    {
        printf("Can't perform operation\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

struct Node* pop(struct Stack *stack)
{
    if (isStackEmpty(stack))
    {
        printf("Cant perform operation\n");
        return NULL;
    }

    struct Node* poppedElement = stack->arr[stack->top];
    stack->top--;
    return poppedElement;
}

struct Node* show(struct Stack *stack)
{
    if (isStackEmpty(stack))
    {
        printf("Stack is empty\n");
        return NULL;
    }
    return stack->arr[stack->top];
}

// NODE BLOCK SECTION

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node *insertValue(struct Node *root, int value)
{
    if (root == NULL)
    {
        root = createNode(value);
    }
    else
    {
        if (value <= root->value)
        {
            root->left = insertValue(root->left, value);
        }
        else
        {
            root->right = insertValue(root->right, value);
        }
    }
    return root;
}

void runPreOrder(struct Node root)
{

}

int main()
{
    struct Stack stack;
    initializeStack(&stack);

    return 0;
}