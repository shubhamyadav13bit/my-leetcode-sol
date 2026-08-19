#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int *answer = NULL;
    answer = calloc(temperaturesSize, sizeof(int));
    if(!answer) return NULL;
    *returnSize = temperaturesSize;
    
    int j;
    for(int i = temperaturesSize-2; i >= 0; i--){
        j = i+1;
        if(temperatures[i] == temperatures[i+1]){
            answer[i] = answer[i+1] + 1;
            continue;
        }
        else if(temperatures[i] > temperatures[i+1]){
            if(temperatures[i+1 + answer[i+1]] > temperatures[i] ){
                answer[i] = answer[i+1]+1;
                continue;
            }
            else{
                j = i + answer[i+1] + 1;
            }
        }
        while(j < temperaturesSize && temperatures[j] <= temperatures[i]){
            j++;
        }
        if(j != temperaturesSize) answer[i] = j-i;
    }
    
    return answer;
}

//[1,1,4,2,1,1,0,0]--------------------------------------------

int main(){
    int temperatures[] = {73,74,75,71,69,72,76,73};
    int temperaturesSize = 8;
    int returnSize;
    int* answer = dailyTemperatures(temperatures, temperaturesSize, &returnSize);
    for(int i = 0; i < returnSize; i++){
        printf("%d ", answer[i]);
    }
    free(answer);
    return 0;
}