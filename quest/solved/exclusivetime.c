//leetcode quest dsa, stack, q3
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_fid(char* arr){
    return atoi(arr);
}
int isStart(char* arr, int arrlen){
    int colon_count = 0, i;
    for(i = 0; colon_count == 0 && i < arrlen; i++) if(arr[i] == ':') colon_count++;
    return arr[i] == 's';
}
int getTime(char * arr, int arrlen){
    int i, timestamp = 0, multiplier = 1;
    for(i = arrlen-1; i>= 0 && arr[i] != ':'; i--){
        timestamp += (arr[i] - '0')*multiplier;
        multiplier *= 10;
    }
    if(i < 5) return -1; //if function reached here before crashing with i < 6, then somethings wrong.
    // "1digitnum:end:.." gives imin = 5.
    return timestamp; 
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* exclusiveTime(int n, char** logs, int logsSize, int* returnSize) {
    int call_stack[logsSize/2 + 1], top = -1; 
    //max size is logsSize/2 + 1
    //+1 to avoid off by one error
    
    int *total_time = NULL;
    total_time = calloc(n, sizeof(int));
    if(!total_time) return NULL;

    int i, logslen;
    int curr_logslen, curr_fid, curr_timestamp, curr_isStart;
    int prev_logslen, prev_fid, prev_timestamp, prev_isStart;
    for(i = 0; i < logsSize; i++){
        curr_logslen = strlen(logs[i]);
        curr_fid = get_fid(logs[i]);
        curr_timestamp = getTime(logs[i], curr_logslen);
        curr_isStart = isStart(logs[i], curr_logslen);
        if(top >= 0) prev_fid = call_stack[top];
        
        /*
        see eg1 carefully
        if start start, totaltime normal
        if start end, totaltime + 1
        if end start, totaltime - 1
        if end end, totaltime normal
        */

        if(curr_isStart){
            call_stack[++top] = curr_fid; //push
            if(top == 0 || i == 0) goto skip_total_time_calculation;
            if(!prev_isStart) total_time[prev_fid]--;
        }
        else{
            top--; //pop
            if(prev_isStart) total_time[prev_fid]++;
        }

        total_time[prev_fid] += curr_timestamp - prev_timestamp;

        skip_total_time_calculation:
        prev_logslen = curr_logslen;
        prev_fid = curr_fid;
        prev_timestamp = curr_timestamp;
        prev_isStart = curr_isStart;

    }
    
    *returnSize = n;
    return total_time;
}


/*
n=2
["0:start:0","0:start:2","0:end:5","1:start:6","1:end:6","0:end:7"]
expected [7, 1]
output [7,0]

n =1
["0:start:0","0:start:2","0:end:5","0:start:6","0:end:6","0:end:7"]
ouput [7]
expected [8]

n = 2
["0:start:0","1:start:2","1:end:5","0:end:6"]
output [3,3]
expected [3,4]
*/