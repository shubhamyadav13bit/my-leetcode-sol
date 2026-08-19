/*
 * Problem: Length of Longest Subarray With at Most K Frequency
 * Difficulty: Medium
 * Topics: Staff, Array, Hash table, Sliding Window
 * 
 * Solution: [Brief description]
 * Time: O(?)
 * Space: O(?)
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int maxSubarrayLength(int* nums, int numsSize, int k) {
    int output = 0;
    int max = 0, min = INT_MAX;
    for(int i = 0; i < numsSize; i++){
        max = (max > nums[i]) ? max : nums[i];
        min = (min < nums[i]) ? min : nums[i];
    }
    int *freq = NULL;
    freq = calloc((max - min + 1), sizeof(int));
    if(freq == NULL) return 0;

    int j = 0;
    for(int i = 0; i < numsSize; i++){
        if(j == numsSize){
            output = (output > j-i) ? output : j-i;
            break;
        }

        if(i > 0 && nums[i-1] != nums[j]){
            do{
                freq[nums[i] - min]--;
                i++;
            }
            while(i < numsSize-1 && nums[i] != nums[j]);
        }
        
        while(j < numsSize){
            freq[nums[j] - min]++;
            if(freq[nums[j] - min] == k+1){
                break;
            }
            j++;
        }

        output = (output > j-i) ? output : j-i;
        freq[nums[i] - min]--;
    }

    return output;
}

void main(){
    int nums[1] = {1};
    int j = maxSubarrayLength(&nums[0], 1, 1);
}