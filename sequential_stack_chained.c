// sequential stack chained
#include <stdio.h>
#include <stdlib.h>

typedef struct node_stack_s{
    int data;
    struct node_stack_s *next; //o next vai ser um outro node
}node_stack_t;

typedef struct{
    node_stack_t *top;
    int count;
}stack_t;

stack_t *stack_init(){ //o malloc vai vir por adição, então não precisa saber previamente quantos objetos vão ter aqui
    stack_t *S = malloc(sizeof(stack_t));
    if(S == NULL){
        return NULL;
    }
    S->top = NULL;
    S->count = 0;
    return S;
}

int stack_push(stack_t *S, int value){ //adicionar elemento ao stack, recebe o struct e o elemento que quer ser adicionado
    if(S==NULL){
        return 1;
    }
    node_stack_t *N = malloc(sizeof(node_stack_t));
    if(N==NULL){
        return 1;
    }
    N->data = value;
    if(S->top == NULL){
        N->next = NULL;
    }else{
        N->next = S->top;
    }
    
    S->top = N;
    S->count++;

    return 0;
}

int stack_pop(stack_t *S, int *value){
    if(S==NULL || S->top == NULL){
        return 1;
    }
    if(value == NULL){
        return 1;
    }

    node_stack_t *N = S->top;
    *value = S->top->data;
    
    S->top = S->top->next;
    S->count--;
    free(N);
    return 0;
}

int stack_is_empty(stack_t *S){
    if (S == NULL){
        return 0;
    }
    return S->top == NULL; //compara, se o top for NULL retorna 0 se o top for diferente disso retorna 1, basicamente um bool para dizer se esta vazio ou n
}

int stack_size(stack_t *S){
    if(S==NULL){
        return 0;
    }
    return S->count;
}

void stack_destroy(stack_t *S){
    if(S == NULL){//O(1)
        return;
    }
    while(S->top != NULL){
        node_stack_t *current = S->top;
        S->top = S->top->next;
        free(current);
    }
    free(S);
}

int main(){
    stack_t *stack = stack_init();
    stack_push(stack, 10);
    stack_push(stack, 20);
    printf("%d\n", stack->top->data);

    int x = 0;
    int *poped = &x;
    stack_pop(stack, poped);
    printf("valor poped %d\n",x);
    printf("top apos pop %d\n", stack->top->data);

    stack_pop(stack, poped);
    int size = stack_size(stack);
    printf("size do stack %d\n",size);

    int isempty = stack_is_empty(stack);
    printf("%d\n", isempty);
    
    if(isempty == 0){
        printf("lista contem conteudo");
    }else{
        printf("lista vazia");
    }

    stack_destroy(stack);
    return 0;
}