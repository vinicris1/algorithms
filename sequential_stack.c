// sequential stack 
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int capacity;
    size_t top;
}sequential_stack_t;

sequential_stack_t *stack_init(int capacity){ //como você cria o stack aqui, ele recebe a struct como tipo da função, dessa forma ele sobrevive após a execução
    if (capacity <= 0){ // O(1)
        return NULL;
    }
    sequential_stack_t *S = malloc (sizeof(sequential_stack_t));
    if(S == NULL){
        return NULL;
    }
    S->data = malloc(capacity * sizeof(int)); //como vai ser um stack de inteiros, o tamanho não pode ser maior que a quantidade de inteiros * seu peso
    if(S->data == NULL){
        free(S);
        return NULL;
    }
    S->top = 0;
    S->capacity = capacity;
    return S;
}

int stack_push(sequential_stack_t *S, int value){ //adicionar elemento ao stack, recebe o struct e o elemento que quer ser adicionado
    if(S==NULL){ //O(1)
        return 1;
    }
    if(S->top == S->capacity){ //como todo push adiciona 1 no top, quando capacity e top forem iguais não tem mais espaço no heap
        return 1;
    }
    S->data[S->top] = value; //como top é vazio/lixo adiciona o valor desejado lá
    S->top++; //top agora aponta pro prox vazio/lixo
    return 0;
}

int stack_pop(sequential_stack_t *S, int *value){ //int value aqui não é essencial, mas é adicionado para que o pop retorne o valor que foi removido para a chamada
    if(S==NULL || S->top == 0){//O(1)
        return 1;
    }
    if(value == NULL){
        return 1;
    }
    S->top--;
    *value = S->data[S->top];
    return 0;
}

int stack_is_empty(sequential_stack_t *S){
    if (S == NULL){//O(1)
        return 0;
    }
    return S->top == 0; //compara, se o top for 0 retorna 0 se o top for diferente disso retorna 1, basicamente um bool para dizer se esta vazio ou n
}

int stack_size(sequential_stack_t *S){
    if(S==NULL){//O(1)
        return 0;
    }
    return S->top;
}
void stack_destroy(sequential_stack_t *S){
    if(S == NULL){//O(1)
        return;
    }
    free(S->data);
    free(S);
}

int main (){
    sequential_stack_t *stack = stack_init(10); //você precisa iniciar o "tipo" sequential_stack_t já que ele é sua struct, não pode iniciar um int já que isso é uma struct completa
    stack_push(stack, 15);
    stack_push(stack, 42);
    for(int i = 0; i<stack->top; i++){
        printf("%d\n", stack->data[i]);
    }
    printf("valor do top apos o push %d\n", stack->top);
    int x = 0;
    int *poped = &x;
    stack_pop(stack, poped);
    printf("valor poped %d\n",x);
    printf("top apos pop %d\n", stack->top);
    
    int size = stack_size(stack);
    printf("size do stack %d\n",size);

    stack_destroy(stack);
    
    return 0;
}