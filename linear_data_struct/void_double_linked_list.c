// this double linked list have an function to accept data where the user request to put, like if the user want to put data in the 3 element of the list it will be possible
// also remove elements it's possible by the same way
// this is a void list so the user can use any type of data inside the list
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_linked_list_s{
    struct node_linked_list_s *above, *below;
    void *data;
}node_linked_list_t;

typedef struct linked_list_s{
    struct node_linked_list_s *begin, *end;
    int count;
    size_t data_size; // way to define a value which will be always positive
}linked_list_t;

linked_list_t *linked_list_init(size_t data_size){ // pointer here cause the initied will be a point to a location in the memory
    if(data_size <= 0){
        return NULL;
    }

    linked_list_t *L = malloc(sizeof(linked_list_t));
    if(L == NULL){
        return NULL;
    }
    L->begin = NULL;
    L->end = NULL;
    L->data_size = data_size;
    L->count = 0;
    return L;
}

int list_add(linked_list_t *L, void *value){
    if(L == NULL || value == NULL){
        return 1;
    }
    node_linked_list_t *N = malloc(sizeof(node_linked_list_t));
    if(N == NULL){
        return 1;
    }
    N->data = malloc(L->data_size); // as it's a pointer you need to allocate memory separated
    if(N->data == NULL){
        return 1;
    }
    if(L->begin == NULL && L->end == NULL){
        N->below = NULL;
        L->begin = N;
        
    }else{
        L->end->above = N;
        N->below = L->end;
    }
    N->above = NULL;
    L->end = N;
    void *dest = (char *) N->data;
    memcpy(dest, value, L->data_size);
    L->count++;
    return 0;
}

int list_remove(linked_list_t *L, void *value){
    if(L == NULL || value == NULL){
        return 1;
    }
    node_linked_list_t *N = L->begin;
    void *dest = (char *) N->data;
    memcpy(value, dest, L->data_size);
    if(N->above == NULL){
        L->begin = NULL;
        L->end = NULL;
    }else{
        L->begin = N->above;
        L->begin->below = NULL;
    }
    free(N->data);
    free(N);
    L->count--;
    return 0;
}

int list_print(linked_list_t *L){
    if(L == NULL){
        return 1;
    }
    node_linked_list_t *N = L->begin;
    printf("%d\n", *(int *)N->data);
    while(N->above != NULL){
        N = N->above;
        printf("%d\n", *(int *)N->data);
    }

    return 0;
}

int main(){
    linked_list_t *L = linked_list_init(sizeof(int));

    int a = 25, b = 42, c = 67;
    list_add(L, &a);
    list_add(L, &b);
    list_add(L, &c);

    int out = 0;
    int *p = &out;
    list_remove(L, p);

    list_print(L);

    return 0;
}