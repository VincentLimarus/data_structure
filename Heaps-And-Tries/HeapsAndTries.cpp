#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int heap[100] = {0};
int element = 0;

//Cek apabila value yg dimasukkan lebih kecil dari parent
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void up_heap(int index){
    if(index == 1){
        return;
    }
    int parent = index / 2;

    if(heap[index] < heap[parent]){     // (< MinHeap)   (> MaxHeap)
        swap(&heap[index], &heap[parent]);
        up_heap(parent);
    }
}

void insert(int value){
    element++;
    heap[element] = value;

    up_heap(element);
}

void view_heap(){
    for(int i = 1; i <= element; i++){
        printf("%d", heap[i]);
        i == element ? printf("\n") : printf(" | ");
    }
}

void down_heap(int index){
    // to index = 1
    int to_index = index;

    int kiri = 2*index;
    int kanan = 2*index+1;

    // MIN HEAP
    if(kiri <= element && heap[to_index] > heap[kiri]){
        to_index = kiri;
    }
    if(kanan <= element && heap[to_index] > heap[kanan]){
        to_index = kanan;
    }

    // MAX HEAP
    // if(kiri <= element && heap[to_index] < heap[kiri]){
    //     to_index = kiri;
    // }
    // if(kanan <= element && heap[to_index] < heap[kanan]){
    //     to_index = kanan;
    // }

    if(to_index == index){
        return;
    }

    swap(&heap[index], &heap[to_index]);
    down_heap(to_index);
}

int extract_min(){
    // Cek heapnya kosong atau tidak
    if(element == 0){
        printf("Heap kosong!\n");
        return 0;
    }

    // Cek kalau isinya cuma root
    if(element == 1){
        element--;
        return heap[1];
    }

    // Kalau jumlah data lebih dr 1

    int return_value = heap[1];
    swap(&heap[1], &heap[element]);
    element--;

    down_heap(1);

    return return_value;
}

int main()
{
    // Test ur Code here!
    // insert(56);
    // insert(12);
    // insert(60);
    // insert(15);
    // insert(75);
    // insert(65);
    // insert(10);
    // insert(70);
    // insert(90);
    // insert(30);
    
    // view_heap();

    // printf("Extracted: %d\n", extract_min());
    // view_heap();

    // printf("Extracted: %d\n", extract_min());
    // view_heap();

    // printf("Extracted: %d\n", extract_min());
    view_heap();

    // printf("Extracted: %d\n", extract_min());
    // view_heap();

    return 0;
}