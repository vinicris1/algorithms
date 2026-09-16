#include <stdlib.h>
#include <stdio.h>

typedef struct node_deque_s{
    int data;
    struct node_deque_s *front,*back;
}node_deque_t;
    
typedef struct deque_double_s{
    struct node_deque_s *begin, *end;
    int count;
}deque_double_t;

deque_double_t *deque_init(){
    deque_double_t *D = malloc(sizeof(deque_double_t));
    if(D==NULL){
        return NULL;
    }
    D->begin = NULL;
    D->end = NULL;
    D->count = 0;
    return D;
}

int push_begin_deque(deque_double_t *D, int value){
    if(D == NULL){
        return 1;
    }
    node_deque_t *N = malloc(sizeof(node_deque_t));
    if(N==NULL){
        return 1;
    }
    if(D->begin == NULL){
        N->back=NULL;
        D->end = N;
    }else{
        N->back = D->begin;
        D->begin->front = N; //do the old begin to point to the new begin
    }
    N->data = value;
    N->front = NULL;
    D->begin = N;
    D->count++;
    return 0;
}

int push_end_deque(deque_double_t *D, int value){
    if(D == NULL){
        return 1;
    }
    node_deque_t *N = malloc(sizeof(node_deque_t));
    if(N==NULL){
        return 1;
    }
    if(D->end == NULL){
        N->front=NULL;
    }else{
        N->front = D->end;
        D->end->back = N; //do the old end to point to the new end
    }
    N->data = value;
    N->back = NULL;
    D->end = N;
    D->count++;
    return 0;
}

int print_deque(deque_double_t *D){
    if(D == NULL){
        return 1;
    }
    node_deque_t *N = D->end;
    printf("%d\n", N->data);

    while(N->front != NULL){
        N = N->front;
        printf("%d\n",N->data);
    }
    return 0;
}

int main(){
    deque_double_t *D = deque_init();
    push_begin_deque(D, 25);
    push_end_deque(D, 42);
    push_begin_deque(D, 50);

    print_deque(D);

    return 0;
}