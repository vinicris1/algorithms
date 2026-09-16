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