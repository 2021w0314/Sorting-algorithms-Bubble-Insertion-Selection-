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

//  insertion sort: "Insert key on the proper position in the sorted part"
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

/*  selection sort: "Find the minimal element in the rest array, 
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
    double mesT_bub[FIVE], mesT_ins[FIVE], mesT_sel[FIVE];
    double mesT_bub_ord[FIVE], mesT_ins_ord[FIVE], mesT_sel_ord[FIVE];
    int cnt_bub[FIVE], cnt_ins[FIVE], cnt_sel[FIVE], cnt_res_bub[FIVE], cnt_res_ins[FIVE], cnt_res_sel[FIVE];    //  counter of switchs

    for(int i = 0; i < FIVE; i++){
        //******* Sorting randomly generated arrays of length L *******
        lth = arr_L[i];
        int arr_init[lth], arr_tmp1[lth], arr_tmp2[lth], arr_tmp3[lth];
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


        //******* Sorting reserved ordered arrays of length L *******
        int arr_tmp4[lth], arr_tmp5[lth], arr_tmp6[lth], arr_tmp7[lth];
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
    printf("\t\t\t\t     ******* Results *******\nBubble\t\tInsertion\tSelection\t|\tBubble\t\tInsertion\tSelection\n");
    printf("\t(randomly generated arrays)\t\t|\t\t(reserved ordered arrays)\n");
    for(int i = 0; i < FIVE; i++){
        printf("%f(%d)\t%f(%d)\t%f(%d)\t|\t%f(%d)\t%f(%d)\t%f(%d)\n", mesT_bub[i], cnt_bub[i], mesT_ins[i], cnt_ins[i], mesT_sel[i]
                , cnt_sel[i], mesT_bub_ord[i], cnt_res_bub[i], mesT_ins_ord[i], cnt_res_ins[i], mesT_sel_ord[i], cnt_res_sel[i]);
    }
    writeExcel(mesT_bub, mesT_ins, mesT_sel, mesT_bub_ord, mesT_ins_ord, mesT_sel_ord);
    return;
}


int main(){
    unsigned int length = 4000;
    int array[length];

    // measure_avg_time();

    // // ****************************   Test of the function    ****************************
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

    //  *** Bubble sort ascending***
    int srtArr_bub[length];     //sorte array, by using bubble sort
    memcpy(srtArr_bub, array, sizeof(int)*length);
    // printf("Initial array is: (COPIED)\n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_bub[i]);
    // }
    // printf("\n");
    start = clock();
    int buble_cnt = bubble_sort(array, length, srtArr_bub);
    end = clock();
    // printf("*** randomly ordered    ***\n");
    // printf("Bubble sorted array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", srtArr_bub[i]);
    // }
    // printf("\n");
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    elapsed_time *= 10e2;
    printf("Bubble sort function runs in %f ms\t(it makes %d times of switch).\n\n", elapsed_time, buble_cnt);

    // ***  Bubble sort with reserved ordered   ***
    int resered_initArr[length];
    printf("*** reserved ordered   ***\n");
    memcpy(resered_initArr, array, sizeof(int)*length);
    insrt_sort_descending(array, length, resered_initArr);
    // printf("Reserved ordered array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", resered_initArr[i]);
    // }
    // printf("\n");
    start = clock();
    int buble_ord_cnt = bubble_sort(array, length, resered_initArr);
    end = clock();
    // printf("Bubble sorted array is: \n");
    // for(int i = 0; i < length; i++){
    //     printf("%d\t", resered_initArr[i]);
    // }
    // printf("\n");
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    elapsed_time *= 10e2;
    printf("Bubble sort function runs in %f ms\t(it makes %d times of switch).\n\n", elapsed_time, buble_ord_cnt);


    // //  *** Insertion sort ascending***
    // int srtArr_ins[length];     //sorte array, by using insertion sort
    // memcpy(srtArr_ins, array, sizeof(int)*length);
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
    // memcpy(srtArr_sel, array, sizeof(int)*length);
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
