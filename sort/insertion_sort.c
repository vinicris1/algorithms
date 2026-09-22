#include <stdio.h>
#include <stdlib.h>

int swap(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

int sort (int *data, int length){
    if(length <= 1){
        return 1;
    }
    for(int i = 1; i < length; i++){
        int key = data[i]; // o i se mantem fixo com o valor não com a posição.
        int j = i - 1;

        while(j >= 0 && data[j] > key){
            swap(&data[j],&data[j+1]);
            j--;
        }
    }  

    return 0;
}

int main(){
    int data[] = {5,4,3};
    int length = 3;
    sort(data, length);

    printf("%d\n",data[0]);
    printf("%d\n",data[1]);
    printf("%d\n",data[2]);
    return 0;
}