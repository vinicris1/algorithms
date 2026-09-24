#include <stdio.h>
#include <stdlib.h>

int swap(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

int sort(int *data, int length){
    if(length <= 1){
        return 1;
    }
    for(int j = 0; j < length - 1; j++){
        for(int i = 0; i<length - j; i++){ // - j as the last element will be in the right spot in the first run
            if(data[i] > data[i+1]){
                swap(&data[i],&data[i+1]);
            }
        }
    }
    
}

void printArray(int *data, int length){
    int i;
    for (i = 0; i < length; i++)
        printf("%d ", data[i]);
}


int main(){
    int data[] = {4,3,1,2};
    int size = sizeof(data) / sizeof(data[0]);
    printf("%d\n",size);
    sort(data, size);
    printArray(data, size);
    return 0;
}