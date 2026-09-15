#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    int begin,end;
    int capacity, size;
    size_t data_size;
}void_queue_t;

void_queue_t *queue_init (int capacity, size_t data_size){
    if(capacity<=0 || data_size <= 0){
        return NULL;
    }
    
    void_queue_t *Q = malloc(sizeof(void_queue_t));
    if(Q==NULL){
        return NULL;
    }

    Q->data = malloc(data_size * capacity); // o tamanho dos dados presente é o tamanho do dado passado pra função * o tamanho da lista circulas
    if(Q->data == NULL){
        free(Q);
        return NULL;
    }
    Q->begin=0;
    Q->end=0;
    Q->capacity = capacity;
    Q->size = 0;
    Q->data_size = data_size;
    return Q;
}

int enqueue_queue (void_queue_t *Q, void *D){
    if(Q==NULL || D == NULL){
        return 1;
    }
    if(Q->size == Q->capacity){ // faz com que se for enfileirado mais dados que o capacity suporta ele retorne 1 e não faça nada
        return 1;
    }
    void *dest = (char *)Q->data + Q->end * Q->data_size; // em C quando você faz um data[i+1] é o mesmo que data[1] por conta disso o que está sendo feito aqui
                                                          // é acessar o elemento Q->data[Q->end * Q->data_size]
                                                          // está conta faz com que o dest aponte para o primeiro bloco de memoria disponivel após o end
                                                          // ex se fosse um int e tivesse 2 elementos na fila seria Q->data + 2 * 4(bytes do int) = 8
    memcpy(dest, D, Q->data_size); // copia do D pro dest
    Q->size++;
    Q->end++;
    if(Q->end == Q->capacity){ // se chegou ao tamanho máximo da lista circular volta pro inicio
        Q->end = 0;
    }
    return 0;
}

int dequeue_queue (void_queue_t *Q, void *D){
    if(Q==NULL || D == NULL){
        return 1;
    }
    if(Q->size == 0){
        return 1;
    }
    void *src = (char *)Q->data + Q->begin * Q->data_size; // aqui a mesma coisa, está sendo apontado para o primeiro bloco disponivel após o begin, como é uma fila circular
                                                           // a ideia aqui é que o begin ande para o proximo bloco de memoria, desta forma o begin antigo fica como sujeira na mem e será sobreescrevido no prox enqueue
    memcpy(D, src, Q->data_size); // copia do src pro D, dessa forma após o dequeue o dado é passado pra função principal
    Q->size--;
    Q->begin++;
    if(Q->begin == Q->capacity){
        Q->begin = 0;
    }
    return 0;
}

int is_empty_queue(void_queue_t *Q){
    if(Q==NULL){
        return 0;
    }
    return Q->size==0;
}

int size_queue(void_queue_t *Q){
    if(Q==NULL){
        return 0;
    }
    return Q->size;
}

int print_queue(void_queue_t *Q){
    if(Q==NULL || is_empty_queue(Q) == 1){
        return 1;
    }
    int aux = Q->begin;
    for(int i = 0; i<Q->size; i++){
        aux = Q->begin + i;
        if(Q->begin + i > Q->capacity-1){
            aux = aux % Q->capacity; // quando o begin + i for 5 ele vai pegar o quanto sobra de 5/4, depois 6/4 que vai dar os indices baixos
        }
        void *src = (char *) Q->data + aux * Q->data_size;
        printf("%d\n", *(int *)src);
    }

    return 0;
}

void destroy_queue(void_queue_t *Q){
    if(Q==NULL){
        return;
    }
    free(Q->data);
    free(Q);
}

int main(){
    void_queue_t *Q = queue_init(4, sizeof(int));

    printf("vazia? %d (esperado: 1)\n", is_empty_queue(Q));

    int a = 10, b = 20, c = 30;
    enqueue_queue(Q, &a);
    enqueue_queue(Q, &b);
    enqueue_queue(Q, &c);

    int out;
    dequeue_queue(Q, &out);
    dequeue_queue(Q, &out);

    // teste 4: testar o wraparound circular
    // agora size=1 (só o 30 dentro), capacity=4, ainda cabem 3
    int d = 40, e = 50, f = 60, h = 70;
    enqueue_queue(Q, &d);
    enqueue_queue(Q, &e);
    enqueue_queue(Q, &f); // esse enqueue faz o 'end' dar a volta (wraparound)

    // teste 5: fila cheia deve recusar novo enqueue
    int g = 70;
    int resultado = enqueue_queue(Q, &g);
    printf("enqueue em fila cheia retornou: %d (esperado: 1, ou seja, erro)\n", resultado);

    print_queue(Q);

    //esvaziar fila
    while(!is_empty_queue(Q)){
        dequeue_queue(Q, &out);
        //printf("dequeue: %d\n", out);
    }
    printf("size final: %d (esperado: 0)\n", size_queue(Q));

    resultado = dequeue_queue(Q, &out);
    printf("dequeue em fila vazia retornou: %d (esperado: 1, ou seja, erro)\n", resultado);
    
    destroy_queue(Q);
    return 0;
}