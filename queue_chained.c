// chained queue implementation
// ponto de atenção, os nodes da fila apontam sempre pro proximo elemento a sair, não ao primeiro elemento, exemplo:
// terceiro <- segundo <- primeiro e não terceiro -> segundo -> primeiro

#include <stdio.h>
#include <stdlib.h>

// ao usar typedef com nome, sempre referencia a struct como o nome dentro dos typedef
typedef struct node_queue_s{
    int data;
    struct node_queue_s *next; // ponteiro para o proximo node da fila
}node_queue_t;

typedef struct{
    struct node_queue_s *begin, *end; // ponteiros para os nodes da fila
    int count;
}queue_t;

queue_t *queue_init(){
    queue_t *Q = malloc(sizeof(queue_t));
    if(Q == NULL){
        return NULL;
    }
    Q->begin = NULL;
    Q->end = NULL;
    Q->count = 0;
    return Q;
}

int queue_add(queue_t *Q, int value){
    if(Q == NULL){
        return 1;
    }
    // aqui você precisa iniciar um novo node para cada add
    node_queue_t *N = malloc(sizeof(node_queue_t));
    if(N==NULL){
        return 1;
    }
    N->data = value;
    N->next = NULL; // como ao adicionar numa fila ele adiciona ao fim, ele sempre apontará para NULL
    if(Q->begin == NULL){
        Q->begin = N;
        Q->end = N;
    }else{
        Q->end->next = N; // muda o NULL do antigo fim da fila para um pointer ao novo fim da fila
        Q->end = N;
    }
    Q->count++;
    return 0;
}

int queue_remove(queue_t *Q, int *value){ // ponteiro para o inteiro que vai receber o valor qeu foi removido
    if(Q == NULL || value == NULL || Q->begin == NULL){
        return 1;
    }
    node_queue_t *N = Q->begin;
    *value = N->data;
    Q->begin = N->next; // seta o begin pra NULL se o N->next apontar pra NULL
    if(N->next == NULL){
        Q->end = NULL; // caso o n->next apontar pra NULL o Q->end passa a apontar também
    }
    free(N);
    Q->count--;
    return 0;
}

int queue_isempty (queue_t *Q){
    if(Q == NULL){
        return 0;
    }
    return Q->begin==NULL;
}

int queue_size(queue_t *Q){
    if(Q == NULL){
        return 0;
    }
    return Q->count;
}

int print_queue(queue_t *Q){
    if(Q == NULL){
        return 1;
    }
    node_queue_t *N = Q->begin;
    printf("%d\n",N->data);
    while(N != NULL){
        N = N->next;
        printf("%d\n",N->data);
    }
    return 0;
}

void queue_destroy(queue_t *Q){
    if(Q == NULL){
        return;
    }
    while(Q->begin != NULL){
        node_queue_t *current = Q->begin;
        Q->begin = Q->begin->next;
        free(current);
    }
    free(Q);
}

int main(){
    queue_t *Q = queue_init();
    queue_add(Q, 10);
    queue_add(Q, 20);
    queue_add(Q, 30);
    printf("%d\n", Q->end->data);
    printf("%d\n", Q->begin->data);

    int x = 0;
    int *p = &x;
    queue_remove(Q, p);
    printf("%d\n", Q->begin->data);

    int a = queue_size(Q);
    printf("%d\n", a);

    queue_add(Q, 40);
    queue_add(Q, 50);

    queue_remove(Q, p);

    print_queue(Q);

    queue_destroy(Q);

    return 0;
}