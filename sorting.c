#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FIVE 5

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

void writeExcel(double* mesT_bub, double* mesT_ins, double* mesT_sel,
                 double* mesT_bub_ord, double* mesT_ins_ord, double* mesT_sel_ord){
    FILE* f = fopen("./testGraphe.txt", "w");
    for(int i = 0; i < FIVE; i++){
        fprintf(f, "%f\t%f\t%f\t%f\t%f\t%f\n", mesT_bub[i], mesT_ins[i], mesT_sel[i], 
                    mesT_bub_ord[i], mesT_ins_ord[i], mesT_sel_ord[i]);
    }
    fclose(f);
}


//  *****************   Algo: in ascending order  *****************  

//  bubble sort: "the biggest bubble raises up first"
/*
    In array a we iteratively look for a pair 
    “left one is greater than the right one” 
    a[i] > a[i + 1] 
    and exchange the items a[i] and a[i + 1]
*/
void bubble_sort(int* array, unsigned int length, int* srtArr_bub){
    memcpy(srtArr_bub, array, sizeof(int)*length);
    int flag = 1;
    int tmp;
    while(flag){
        flag = 0;
        for(int i = 0; i < length-1; i++){
            if(srtArr_bub[i] > srtArr_bub[i+1]){
                tmp = srtArr_bub[i];
                srtArr_bub[i] = srtArr_bub[i+1];
                srtArr_bub[i+1] = tmp;
                flag = 1;
            }
        }
    }
    return;
}

//  insertion sort: "Insert key on the proper position in the sorted part"
void insertion_sort(int* array, unsigned int length, int* srtArr_ins){
    memcpy(srtArr_ins, array, sizeof(int)*length);
    int j, tmp;
    for(int i = 1; i < length; i++){
        j = i-1;
        while((j >= 0) && (srtArr_ins[j] > srtArr_ins[j+1])){
            tmp = srtArr_ins[j];
            srtArr_ins[j] = srtArr_ins[j+1];
            srtArr_ins[j+1] = tmp;
            j--;
        }
    }
    return;
}

/*  selection sort: "Find the minimal element in the rest array, 
    and insert it in the right index of the array befor"
*/
void selection_sort(int* array, unsigned int length, int* srtArr_sel){
    memcpy(srtArr_sel, array, sizeof(int)*length);
    int min, idx;
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
    }
    return;
}

//  *****************   Algo: in descending order  *****************
//  (by using Insertion sort)
void insrt_sort_descending(int* array, unsigned int length, int* srtArr_des){
    memcpy(srtArr_des, array, sizeof(int)*length);
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
    double mesT_bub[FIVE], mesT_ins[FIVE], mesT_sel[FIVE];
    double mesT_bub_ord[FIVE], mesT_ins_ord[FIVE], mesT_sel_ord[FIVE];

    //******* Sorting randomly generated arrays of length L *******
    for(int i = 0; i < FIVE; i++){
        lth = arr_L[i];
        int arr_init[lth], arr_tmp1[lth], arr_tmp2[lth], arr_tmp3[lth];
        rand_fill(arr_init, lth);
        // printf("\nInitial array is: ");
        // for(int i = 0; i < lth; i++){
        //     printf("%d\t", arr_init[i]);
        // }
        // printf("\n");

        // ***  Bubble sort  ***
        start = clock();
        bubble_sort(arr_init, lth, arr_tmp1);
        end = clock();
        mesT_bub[i] = calculate_time(start, end);

        // ***  Insertion sort  ***
        start = clock();
        insertion_sort(arr_init, lth, arr_tmp2);
        end = clock();
        mesT_ins[i] = calculate_time(start, end);

        // ***  Selection sort  ***
        start = clock();
        selection_sort(arr_init, lth, arr_tmp3);
        end = clock();
        mesT_sel[i] = calculate_time(start, end);
    }

    //******* Sorting reserved ordered arrays of length L *******
    for(int i = 0; i < FIVE; i++){
        lth = arr_L[i];
        int arr_init[lth], arr_tmp1[lth], arr_tmp2[lth], arr_tmp3[lth], arr_tmp4[lth];
        rand_fill(arr_init, lth);
        insrt_sort_descending(arr_init, lth, arr_tmp4);

        // ***  Bubble sort  ***
        start = clock();
        bubble_sort(arr_tmp4, lth, arr_tmp1);
        end = clock();
        mesT_bub_ord[i] = calculate_time(start, end);

        // ***  Insertion sort  ***
        start = clock();
        insertion_sort(arr_tmp4, lth, arr_tmp2);
        end = clock();
        mesT_ins_ord[i] = calculate_time(start, end);

        // ***  Selection sort  ***
        start = clock();
        selection_sort(arr_tmp4, lth, arr_tmp3);
        end = clock();
        mesT_sel_ord[i] = calculate_time(start, end);
    }

    //  exprime the results
    printf("\t\t\t\t     ******* Results *******\nBubble\t\tInsertion\tSelection\t|\tBubble\t\tInsertion\tSelection\n");
    printf("\t(randomly generated arrays)\t\t|\t\t(reserved ordered arrays)\n");
    for(int i = 0; i < FIVE; i++){
        printf("%f\t%f\t%f\t|\t%f\t%f\t%f\n", mesT_bub[i], mesT_ins[i], mesT_sel[i]
                , mesT_bub_ord[i], mesT_ins_ord[i], mesT_sel_ord[i]);
    }
    writeExcel(mesT_bub, mesT_ins, mesT_sel, mesT_bub_ord, mesT_ins_ord, mesT_sel_ord);
    return;
}


int main(){
    unsigned int length = 10000;
    int array[length];

    measure_avg_time();

    // ****************************   Test of the function    ****************************
    // rand_fill(array, length);
    // printf("Initial array is: ");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", array[i]);
    // }
    // printf("\n");

    // // variables to measure the initial and final time of each run of function
    // clock_t start, end;
    // //variable to store the elapsed time
    // double elapsed_time ;

    // //  *** Bubble sort ascending***
    // int srtArr_bub[length];     //sorte array, by using bubble sort
    // start = clock();
    // bubble_sort(array, length, srtArr_bub);
    // end = clock();
    // printf("Bubble sorted array is: ");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_bub[i]);
    // }
    // printf("\n");
    // elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    // elapsed_time *= 10e2;
    // printf("Bubble sort function runs in %f ms\n\n", elapsed_time);

    // //  *** Insertion sort ascending***
    // int srtArr_ins[length];     //sorte array, by using insertion sort
    // start = clock();
    // insertion_sort(array, length, srtArr_ins);
    // end = clock();
    // printf("Insertion sorted array is: ");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_ins[i]);
    // }
    // printf("\n");
    // elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    // elapsed_time *= 10e2;
    // printf("Insertion sort function runs in %f ms\n\n", elapsed_time);

    // //  *** Selection sort ascending***
    // int srtArr_sel[length];     //sorte array, by using selection sort
    // start = clock();
    // selection_sort(array, length, srtArr_sel);
    // end = clock();
    // printf("Selection sorted array is: ");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_sel[i]);
    // }
    // printf("\n");
    // elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    // elapsed_time *= 10e2;
    // printf("Selection sort function runs in %f ms\n\n", elapsed_time);

    // //  *** Insertion sort descending***
    // int srtArr_des[length];
    // start = clock();
    // insrt_sort_descending(array, length, srtArr_des);
    // end = clock();
    // printf("Insertion sorted array (descending) is: ");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_des[i]);
    // }
    // printf("\n");
    // elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    // elapsed_time *= 10e2;
    // printf("Insertion sort function (descending) runs in %f ms\n\n", elapsed_time);

    return 0;
}
