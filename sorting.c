#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

# define FIVE 5

void rand_fill(int* array, unsigned int length){
    time_t time_seed;
    srand((unsigned) time(&time_seed));
    for(int i = 0; i < length; i++){
        array[i] = rand()%100;
    }
}

//  method to calculate the elapsed time
double calculate_time(clock_t start, clock_t end){
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    elapsed_time *= 10e2;
    return elapsed_time;
}

void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void writeExcel(double* mesT_bub, double* mesT_ins, double* mesT_sel, double* mesT_qck, double* mesT_heap,
                 double* mesT_bub_ord, double* mesT_ins_ord, double* mesT_sel_ord, double* mesT_qck_ord, double* mesT_heap_ord){
    FILE* f = fopen("./testGraphe.txt", "w");
    for(int i = 0; i < FIVE; i++){
        fprintf(f, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", 
                    mesT_bub[i], mesT_ins[i], mesT_sel[i], mesT_qck[i], mesT_heap[i],
                    mesT_bub_ord[i], mesT_ins_ord[i], mesT_sel_ord[i], mesT_qck_ord[i], mesT_heap_ord[i]);
    }
    fclose(f);
}


//  *****************   Algo: in ascending order  *****************  

//  Bubble Sort: "the biggest bubble raises up first"
/*
    In array a we iteratively look for a pair 
    “left one is greater than the right one” 
    a[i] > a[i + 1] 
    and exchange the items a[i] and a[i + 1]
*/
int bubble_sort(int* array, unsigned int length, int* srtArr_bub){
    // memcpy(srtArr_bub, array, sizeof(int)*length);
    int flag = 1;
    int tmp;
    int count = 0;
    while(flag){
        flag = 0;
        for(int i = 0; i < length-1; i++){
            if(srtArr_bub[i] > srtArr_bub[i+1]){
                tmp = srtArr_bub[i];
                srtArr_bub[i] = srtArr_bub[i+1];
                srtArr_bub[i+1] = tmp;
                flag = 1;
                count++;
            }
        }
    }
    return count;
}

/*  Insertion Sort: 
      "Insert key on the proper position in the sorted part"
*/
int insertion_sort(int* array, unsigned int length, int* srtArr_ins){
    // memcpy(srtArr_ins, array, sizeof(int)*length);
    int j, tmp;
    int count = 0;
    for(int i = 1; i < length; i++){
        j = i-1;
        while((j >= 0) && (srtArr_ins[j] > srtArr_ins[j+1])){
            tmp = srtArr_ins[j];
            srtArr_ins[j] = srtArr_ins[j+1];
            srtArr_ins[j+1] = tmp;
            j--;
            count++;
        }
    }
    return count;
}

/*  Selection Sort: 
        "Find the minimal element in the rest array, 
        and insert it in the right index of the array befor"
*/
int selection_sort(int* array, unsigned int length, int* srtArr_sel){
    // memcpy(srtArr_sel, array, sizeof(int)*length);
    int min, idx;
    int count = 0;
    for(int i = 0; i < length - 1; i++){
        min = srtArr_sel[i];
        idx = i;
        for(int j = i+1; j < length; j++){
            if(srtArr_sel[j] < min){
                min = srtArr_sel[j];
                idx = j;
            }
        }
        srtArr_sel[idx] = srtArr_sel[i];
        srtArr_sel[i] = min;
        count++;
    }
    return count;
}

//  QuickSort: (recursive function)
/*  1) Choose a pivot,
    2) All the elements less than pivot, go to the left
    3) All the elements more than pivot, go to the right
 */
int quickSort(int* srtArr_quick, int low, int high, int count){
    // memcpy(srtArr_quick, array, sizeof(int)*length);
    if(low >= high) return count;
    int i = low, j = high, base = srtArr_quick[low];
    while(i < j){
        while((base <= srtArr_quick[j]) && (i < j)) j--;
        while((base >= srtArr_quick[i]) && (i < j)) i++;
        if(i != j){
            swap(&srtArr_quick[i], &srtArr_quick[j]);
            count++;
        }
    }
    swap(&srtArr_quick[low], &srtArr_quick[j]);
    count++;
    count = quickSort(srtArr_quick, low, j-1, count);
    count = quickSort(srtArr_quick, j+1, high, count);
    return count;
}

//  HeapSort: （improvement of Selection Sort)
/*  1) Building a heap
    2) Sorting
*/
int siftDown(int* srtArr_heap, int dad, int lth, int count){
    int son = 2*dad + 1;
    while(son < lth){
        son = 2*dad + 1;
        if(son >= lth)  return count;
        if((srtArr_heap[son] < srtArr_heap[son+1]) && ((son+1) < lth))  son++;
        if(srtArr_heap[dad] >= srtArr_heap[son])    return count;
        swap(&srtArr_heap[son], &srtArr_heap[dad]);
        count++;
        dad = son;
    }
    return count;
}
int heapSort(int* srtArr_heap, int lth, int count){
    // memcpy(srtArr_heap, array, sizeof(int)*length);
    // 1) Building a heap
    for(int i = lth/2-1; i >= 0; count = siftDown(srtArr_heap, i--, lth, count));
    // 2) Sorting
    while(lth > 1){
        swap(&srtArr_heap[0], &srtArr_heap[lth-1]);
        count++;
        lth--;
        count = siftDown(srtArr_heap, 0, lth, count);
    }
    return count;
}


//  *****************   Algo: in descending order  *****************
//  (by using Insertion sort)
void insrt_sort_descending(int* array, unsigned int length, int* srtArr_des){
    // memcpy(srtArr_des, array, sizeof(int)*length);
    int j, tmp;
    for(int i = length-2; i >= 0; i--){
        j = i+1;
        while((j <= length-1) && (srtArr_des[j] > srtArr_des[j-1])){
            tmp = srtArr_des[j-1];
            srtArr_des[j-1] = srtArr_des[j];
            srtArr_des[j] = tmp;
            j++;
        }
    }
    return;
}


//  *****************   Measure the average time    *****************
/*  measure the average time(of FIVE samples) each of the sorting algorithms takes to process:
    1)  sorting a randomly generated array of length L
    2)  sorting a reversed ordered array of length L
    L is in the range{10, 100, 1000, 10000, 100000}
*/
void measure_avg_time(){
    int arr_L[] = {10, 100, 1000, 10000, 20000};
    // int arr_L[] = {1000, 2000, 3000, 4000, 5000};
    int lth;    // length L
    clock_t start, end;     // initial and final time of each run of functions
    // arrays to store the measure of time 
    double mesT_bub[FIVE], mesT_ins[FIVE], mesT_sel[FIVE], mesT_qck[FIVE], mesT_heap[FIVE];
    double mesT_bub_ord[FIVE], mesT_ins_ord[FIVE], mesT_sel_ord[FIVE], mesT_qck_ord[FIVE], mesT_heap_ord[FIVE];
    int cnt_bub[FIVE], cnt_ins[FIVE], cnt_sel[FIVE], cnt_qck[FIVE], cnt_heap[FIVE], cnt_res_bub[FIVE], cnt_res_ins[FIVE], cnt_res_sel[FIVE], cnt_res_qck[FIVE], cnt_res_heap[FIVE];    //  counter of switchs

    for(int i = 0; i < FIVE; i++){
        //******* Sorting randomly generated arrays of length L *******
        lth = arr_L[i];
        //  arr_tmp1 <-> bubble_sort;   arr_tmp2 <-> insertion;     arr_tmp3 <-> selection;     arr_tmpA <-> quick;     arr_tmpB <-> heap
        int arr_init[lth], arr_tmp1[lth], arr_tmp2[lth], arr_tmp3[lth], arr_tmpA[lth], arr_tmpB[lth];
        rand_fill(arr_init, lth);
        // printf("\nInitial array is: ");
        // for(int i = 0; i < lth; i++){
        //     printf("%d\t", arr_init[i]);
        // }
        // printf("\n");

        // ***  Bubble sort  ***
        memcpy(arr_tmp1, arr_init, sizeof(int)*lth);
        start = clock();
        cnt_bub[i] = bubble_sort(arr_init, lth, arr_tmp1);
        end = clock();
        mesT_bub[i] = calculate_time(start, end);

        // ***  Insertion sort  ***
        memcpy(arr_tmp2, arr_init, sizeof(int)*lth);
        start = clock();
        cnt_ins[i] = insertion_sort(arr_init, lth, arr_tmp2);
        end = clock();
        mesT_ins[i] = calculate_time(start, end);

        // ***  Selection sort  ***
        memcpy(arr_tmp3, arr_init, sizeof(int)*lth);
        start = clock();
        cnt_sel[i] = selection_sort(arr_init, lth, arr_tmp3);
        end = clock();
        mesT_sel[i] = calculate_time(start, end);

        // ***  Quick sort  ***
        memcpy(arr_tmpA, arr_init, sizeof(int)*lth);
        start = clock();
        cnt_qck[i] = quickSort(arr_tmpA, 0, lth, 0);
        end = clock();
        mesT_qck[i] = calculate_time(start, end);

        // ***  Heap sort  ***
        memcpy(arr_tmpB, arr_init, sizeof(int)*lth);
        start = clock();
        cnt_heap[i] = heapSort(arr_tmpB, lth, 0);
        end = clock();
        mesT_heap[i] = calculate_time(start, end);


        //******* Sorting reserved ordered arrays of length L *******
        //  arr_tmp4 <-> buble_res;     arr_tmp5 <-> insert_res;    arr_tmp6 <-> select_res;    arr_tmpC <-> quick_res;     arr_tmpD <-> heap_res
        //  arr_tmp7 <-> arr_init_res
        int arr_tmp4[lth], arr_tmp5[lth], arr_tmp6[lth], arr_tmp7[lth], arr_tmpC[lth], arr_tmpD[lth];
        memcpy(arr_tmp7, arr_init, sizeof(int)*lth);
        insrt_sort_descending(arr_init, lth, arr_tmp7);

        // ***  Bubble sort  ***
        memcpy(arr_tmp4, arr_tmp7, sizeof(int)*lth);
        start = clock();
        cnt_res_bub[i] = bubble_sort(arr_tmp7, lth, arr_tmp4);
        end = clock();
        mesT_bub_ord[i] = calculate_time(start, end);

        // ***  Insertion sort  ***
        memcpy(arr_tmp5, arr_tmp7, sizeof(int)*lth);
        start = clock();
        cnt_res_ins[i] = insertion_sort(arr_tmp7, lth, arr_tmp5);
        end = clock();
        mesT_ins_ord[i] = calculate_time(start, end);

        // ***  Selection sort  ***
        memcpy(arr_tmp6, arr_tmp7, sizeof(int)*lth);
        start = clock();
        cnt_res_sel[i] = selection_sort(arr_tmp7, lth, arr_tmp6);
        end = clock();
        mesT_sel_ord[i] = calculate_time(start, end);

        // ***  Quick sort  ***
        memcpy(arr_tmpC, arr_init, sizeof(int)*lth);
        start = clock();
        cnt_res_heap[i] = quickSort(arr_tmpC, 0, lth, 0);
        end = clock();
        mesT_qck_ord[i] = calculate_time(start, end);

        // ***  Heap sort  ***
        memcpy(arr_tmpD, arr_init, sizeof(int)*lth);
        start = clock();
        cnt_res_heap[i] = heapSort(arr_tmpD, lth, 0);
        end = clock();
        mesT_heap_ord[i] = calculate_time(start, end);
    }

    // //******* Sorting reserved ordered arrays of length L *******
    // for(int i = 0; i < FIVE; i++){
    //     lth = arr_L[i];
    //     int arr_init[lth], arr_tmp4[lth], arr_tmp5[lth], arr_tmp6[lth], arr_tmp7[lth];
    //     rand_fill(arr_init, lth);
    //     insrt_sort_descending(arr_init, lth, arr_tmp7);

    //     // ***  Bubble sort  ***
    //     memcpy(arr_tmp4, arr_tmp7, sizeof(int)*lth);
    //     start = clock();
    //     cnt_res_bub[i] = bubble_sort(arr_tmp7, lth, arr_tmp4);
    //     end = clock();
    //     mesT_bub_ord[i] = calculate_time(start, end);

    //     // ***  Insertion sort  ***
    //     memcpy(arr_tmp5, arr_tmp7, sizeof(int)*lth);
    //     start = clock();
    //     cnt_res_ins[i] = insertion_sort(arr_tmp7, lth, arr_tmp5);
    //     end = clock();
    //     mesT_ins_ord[i] = calculate_time(start, end);

    //     // ***  Selection sort  ***
    //     memcpy(arr_tmp6, arr_tmp7, sizeof(int)*lth);
    //     start = clock();
    //     cnt_res_sel[i] = selection_sort(arr_tmp7, lth, arr_tmp6);
    //     end = clock();
    //     mesT_sel_ord[i] = calculate_time(start, end);
    // }

    //  exprime the results
    printf("\t\t\t\t     ******* Results *******\nBubble\t\tInsertion\tSelection\tQuicksort\tHeapsort\t|\tBubble\t\tInsertion\tSelection\tQuicksort\tHeapsort\n");
    printf("\t\t\t(randomly generated arrays)\t\t\t\t|\t\t\t(reserved ordered arrays)\n");
    for(int i = 0; i < FIVE; i++){
        printf("%f(%d)\t%f(%d)\t%f(%d)\t%f(%d)\t%f(%d)\t|\t%f(%d)\t%f(%d)\t%f(%d)\t%f(%d)\t%f(%d)\n"
                , mesT_bub[i], cnt_bub[i], mesT_ins[i], cnt_ins[i], mesT_sel[i], cnt_sel[i]
                , mesT_qck[i], cnt_qck[i], mesT_heap[i], cnt_heap[i]
                , mesT_bub_ord[i], cnt_res_bub[i], mesT_ins_ord[i], cnt_res_ins[i], mesT_sel_ord[i], cnt_res_sel[i]
                , mesT_qck_ord[i], cnt_res_qck[i], mesT_heap_ord[i], cnt_res_heap[i]);
    }
    writeExcel(mesT_bub, mesT_ins, mesT_sel, mesT_qck, mesT_heap, 
                mesT_bub_ord, mesT_ins_ord, mesT_sel_ord, mesT_qck_ord, mesT_heap_ord);
    return;
}

int main(){

    // measure_avg_time();

    // ****************************   Test of the function    ****************************
    unsigned int length = 20000;
    int array[length];
    rand_fill(array, length);
    // printf("Initial array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", array[i]);
    // }
    // printf("\n");

    // variables to measure the initial and final time of each run of function
    clock_t start, end;
    //variable to store the elapsed time
    double elapsed_time ;

    //  *** Quick sort ascending***
    int srtArr_quick[length];     //sorte array, by using Quick Sort
    memcpy(srtArr_quick, array, sizeof(int)*length);
    // printf("Initial array is: (COPIED)\n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_quick[i]);
    // }
    // printf("\n");
    start = clock();
    int quickSort_cnt = quickSort(srtArr_quick, 0, length, 0);
    end = clock();
    printf("***     randomly ordered    ***\n");
    // printf("Quick sorted array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_quick[i]);
    // }
    // printf("\n");
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    elapsed_time *= 10e2;
    printf("Quick sort function runs in %f ms\t(it makes %d times of switch).\n\n", elapsed_time, quickSort_cnt);

    //  *** Heap sort ascending***
    int srtArr_heap[length];     //sorte array, by using Quick Sort
    memcpy(srtArr_heap, array, sizeof(int)*length);
    // printf("Initial array is: (COPIED)\n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_quick[i]);
    // }
    // printf("\n");
    start = clock();
    int heapSort_cnt = heapSort(srtArr_heap, length, 0);
    end = clock();
    // printf("Heap sorted array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_heap[i]);
    // }
    // printf("\n");
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    elapsed_time *= 10e2;
    printf("Heap sort function runs in %f ms\t(it makes %d times of switch).\n\n", elapsed_time, heapSort_cnt);


    //  *** Insertion sort ascending***
    int srtArr_ins[length];     //sorte array, by using Quick Sort
    memcpy(srtArr_ins, array, sizeof(int)*length);
    // printf("Initial array is: (COPIED)\n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_quick[i]);
    // }
    // printf("\n");
    start = clock();
    int insert_cnt = insertion_sort(array, length, srtArr_ins);
    end = clock();
    // printf("Heap sorted array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_heap[i]);
    // }
    // printf("\n");
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    elapsed_time *= 10e2;
    printf("Insertion sort function runs in %f ms\t(it makes %d times of switch).\n\n", elapsed_time, insert_cnt);

    // // ***  with reserved ordered   ***
    // int resered_initArr[length];
    // printf("*** reserved ordered   ***\n");
    // memcpy(resered_initArr, array, sizeof(int)*length);
    // insrt_sort_descending(array, length, resered_initArr);
    // printf("Reserved ordered array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", resered_initArr[i]);
    // }
    // printf("\n\n");

    // //  *** Quick sort ascending***
    // int srtArr_quick[length];     //sorte array, by using Quick Sort
    // memcpy(srtArr_quick, resered_initArr, sizeof(int)*length);
    // // printf("Initial array is: (COPIED)\n");
    // // for(int i = 0; i < length; i++){
    // //     printf("%d\t", srtArr_quick[i]);
    // // }
    // // printf("\n");
    // start = clock();
    // int quickSort_cnt = quickSort(srtArr_quick, 0, length, 0);
    // end = clock();
    // printf("Quick sorted array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_quick[i]);
    // }
    // printf("\n");
    // elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    // elapsed_time *= 10e2;
    // printf("Quick sort function runs in %f ms\t(it makes %d times of switch).\n\n", elapsed_time, quickSort_cnt);

    // //  *** Heap sort ascending***
    // int srtArr_heap[length];     //sorte array, by using Quick Sort
    // memcpy(srtArr_heap, resered_initArr, sizeof(int)*length);
    // // printf("Initial array is: (COPIED)\n");
    // // for(int i = 0; i < length; i++){
    // //     printf("%d\t", srtArr_quick[i]);
    // // }
    // // printf("\n");
    // start = clock();
    // int heapSort_cnt = heapSort(srtArr_heap, length, 0);
    // end = clock();
    // printf("Heap sorted array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_heap[i]);
    // }
    // printf("\n");
    // elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    // elapsed_time *= 10e2;
    // printf("Heap sort function runs in %f ms\t(it makes %d times of switch).\n\n", elapsed_time, heapSort_cnt);

    return 0;
}