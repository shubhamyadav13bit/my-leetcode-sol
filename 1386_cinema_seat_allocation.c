/*
Leetcode daily for 19 Aug, 2026
Problem: 1386. Cinema Seat Allocation
Difficulty: Medium
Topics: Arrays, Sorting, Bit Manipulation, Hash Table (or Greedy)

Solution: Use a bitmask (3 bits) per row to track whether the three possible 4‑seat blocks
(columns 2‑5, 4‑7, 6‑9) are still free. Only rows with at least one reservation are stored
in a sorted array. For each reserved seat, clear the relevant bits. Start with all empty rows
giving 2 families each, then add contributions for rows with reservations based on remaining
available blocks.

Time: O(K log K) where K = reservedSeatsSize (sorting dominates), 33ms, beats 27.27%
Space: O(K) for storing distinct rows and their bitmasks, 20.32MB, beats 27.27%
*/

#include <stdio.h>
#include <stdlib.h>

#define Q1 (1 << 0) //Q1. Is 2345 avialable in row?
#define Q2 (1 << 1) //Q2. Is 4567 avialable in row?
#define Q3 (1 << 2) //Q3. Is 6789 avialable in row?
typedef struct {
    int rownum;
    int ans;
} record;
void insertion_sort(int *arr, int l, int r){
    int key, j;
    for(int i = l+1; i <= r; i++){
        key = arr[i];
        j = i-1;
        while(j >= l){
            if(key < arr[j]) arr[j+1] = arr[j];
            else break;
            j--;
        }
        arr[j+1] = key;
    }
}
void quicksort(int *arr, int l, int r){
    if(r-l+1 < 20){
        insertion_sort(arr, l, r);
        return;
    }
    int i = l-1, j = r+1, pivot = arr[(l+r)/2], temp;
    //Hoare Partition Scheme
    while(1){
        do{i++;} while(arr[i] < pivot);
        do{j--;} while(arr[j] > pivot);
        if(i >= j) break;
        else{
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    quicksort(arr, l, j);
    quicksort(arr, j+1, r);
}
int binary_search(record *arr, int l,  int r, int rownum){
    int mid;
    while(r >= l){
        mid = (l+r)/2;
        if(rownum == arr[mid].rownum) return mid;
        else if(rownum > arr[mid].rownum) l = mid+1;
        else r = mid-1;
    }
    return -1;
}
int maxNumberOfFamilies(int n, int** reservedSeats, int reservedSeatsSize, int* reservedSeatsColSize) {
    if(reservedSeatsSize == 0) return 2*n;
    int output = 0;
    int *cpyResSeat = NULL; //copy of reservedSeats[i][0]
    cpyResSeat = malloc(reservedSeatsSize*sizeof(int));
    if(!cpyResSeat) return -1;

    for(int i = 0; i < reservedSeatsSize; i++) cpyResSeat[i] = reservedSeats[i][0];

    quicksort(cpyResSeat, 0, reservedSeatsSize-1);

    int numRowWresSeat = 1; //number of rows with atlest one seat reserved
    for(int i = 1; i < reservedSeatsSize; i++) if(cpyResSeat[i] != cpyResSeat[i-1]) numRowWresSeat++;
    
    record* r = NULL;
    int r_ptr = 1;
    r = malloc((numRowWresSeat+1)*sizeof(record));
    if(!r){
        free(cpyResSeat);
        return -1;
    }

    r[1].rownum = cpyResSeat[0];
    for(int i = 1; i < reservedSeatsSize; i++){
        if(cpyResSeat[i] != cpyResSeat[i-1]){
            r[++r_ptr].rownum = cpyResSeat[i];
        }
    }

    free(cpyResSeat);
    output += 2*(n-numRowWresSeat);

    for(int i = 1; i <= numRowWresSeat; i++){
        r[i].ans = 0;
        r[i].ans |= Q1;
        r[i].ans |= Q2;
        r[i].ans |= Q3; 
    }
    
    int rownum, seatnum;
    for(int i = 0; i < reservedSeatsSize; i++){
        rownum = reservedSeats[i][0];
        r_ptr = binary_search(r, 1, numRowWresSeat, rownum);
        if(r_ptr == -1) continue;
        
        seatnum = reservedSeats[i][1];
        if(seatnum == 2 || seatnum == 3) r[r_ptr].ans &=  ~Q1;
        if(seatnum == 4 || seatnum == 5){
            r[r_ptr].ans &= ~Q1;
            r[r_ptr].ans &= ~Q2;
        }
        if(seatnum == 6 || seatnum == 7){
            r[r_ptr].ans &= ~Q2;
            r[r_ptr].ans &= ~Q3;
        }
        if(seatnum == 8 || seatnum == 9) r[r_ptr].ans &= ~Q3;
    }

    int ans1, ans2, ans3, ans;
    for(int i = 1; i <= numRowWresSeat; i++){
        ans = r[i].ans;
        ans1 = ans & Q1;
        ans2 = ans & Q2;
        ans3 = ans & Q3;
        if(ans1 && ans3) output += 2;
        else if(ans1 || ans2 || ans3) output += 1;
    }
    
    free(r);
    return output;
}
