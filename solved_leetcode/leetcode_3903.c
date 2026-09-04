/*
Problem: Leetcode 3903. Smallest Stable Index I
Leetcode Daily for 4 September, 2026
Difficulty: Easy
Topics: Arrays, Prefix Maximum, Suffix Minimum

Solution: 
For each index i, we need to check if max(nums[0..i]) - min(nums[i..n-1]) <= k.
We precompute a suffix minimum array minnum_ItoN where minnum_ItoN[i] = min(nums[i..n-1]).
Then we scan from left to right, maintaining the prefix maximum maxnum_1toI.
At each i, compute instability_score = prefix_max - suffix_min[i] and return i if it's ≤ k.
If no such index, return -1. Edge cases: empty array returns -1; allocation failure returns -2.

Time: O(n) - one pass for suffix min + one pass for prefix max and check.
Space: O(n) - for the suffix minimum array; auxiliary space is O(n).
*/

#include <stdlib.h>
#include <limits.h>

int firstStableIndex(int* nums, int numsSize, int k) {
    if(numsSize <= 0) return -1; 
    int maxnum_1toI = INT_MIN;
    int instability_score;

    int *minnum_ItoN = NULL;    minnum_ItoN = malloc(numsSize*sizeof(int));
    if(minnum_ItoN == NULL) return -2; //memory allocation failure error code
    minnum_ItoN[numsSize-1] = nums[numsSize-1];
    for(int i = numsSize-2; i >= 0; i--) minnum_ItoN[i] = (minnum_ItoN[i+1] < nums[i]) ? minnum_ItoN[i+1] : nums[i];

    for(int i = 0; i < numsSize; i++){
        maxnum_1toI = (maxnum_1toI > nums[i]) ? maxnum_1toI : nums[i];
        instability_score = maxnum_1toI - minnum_ItoN[i];
        if(instability_score <= k){
            free(minnum_ItoN);
            return i;
        } 
    }
    free(minnum_ItoN);
    return -1;
}