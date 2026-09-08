/*
Leetcode Daily for 5 Sept, 2026
Problem: Leetcode 3904. Smallest Stable index II
Difficulty: Medium
Topics: Array, Monotonic Stack

Solution:
The algorithm finds the first index i such that max(nums[0..i]) - min(nums[i..n-1]) <= k.
It first builds a monotonic stack of indices where a new suffix minimum appears when scanning from right to left.
The stack stores candidate suffix minima. Then it scans i from 0 to n-1, maintaining the maximum of the prefix.
Before computing the suffix minimum for i, it pops from the stack any index less than i, so stack[top] is the 
index of the minimum in nums[i..n-1].
The instability score is prefixMax - suffixMin; if <= k, return i.

Time: O(n) – each index is pushed and popped at most once, and prefix scan is linear.
Space: O(n) – stack may hold up to n indices in the worst case.
*/
#include <stdlib.h>
#include <limits.h>

int firstStableIndex(int* nums, int numsSize, int k) {
    if(numsSize == 1) return 0;
    int maxnum_1toI = -1, instability_score, minnum_ItoN = INT_MAX;
    
    //stack = [d, c, b, a], stack will be made such that (numsSize-1 == d > c > b > a >= 0)
    //and if c >= i > b, minnum_ItoN for i is nums[c].
    int *stack = NULL, top = -1, stack_size = (numsSize > 20) ? numsSize/4 : 5;
    stack = malloc(stack_size*sizeof(int));
    if(stack == NULL) return -1;

    //filling stack and increasing its capacity, if needed
    for(int i = numsSize-1; i >= 0; i--){
        if(minnum_ItoN > nums[i]){
            minnum_ItoN = nums[i];
            //push i on stack after checking capacity
            //checking capacity and realloc if full
            if(top == stack_size-1){
                int size_increment = (numsSize > 20) ? numsSize/8 : 3;
                int *temp = NULL; temp = realloc(stack, (stack_size + size_increment)*sizeof(int));
                if(temp == NULL){
                    free(stack); return -1; //realloc failure
                }
                stack_size += size_increment; //only runs if realloc successful
                stack = temp;
            }
            //push i on stack
            stack[++top] = i;
        }
    }

    minnum_ItoN = INT_MAX; //reseting just to be safe

    //getting instability_score by calculating maxnum_1toI on the go
    //getting minnum_ItoN from stack by ensuring that stack[top] >= i and getting minnum_ItoN == nums[stack[top]]
    //if i gets greater than stack[top], simply 'pull' and repeat
    for(int i = 0; i < numsSize; i++){
        maxnum_1toI = (maxnum_1toI > nums[i]) ? maxnum_1toI : nums[i];
        
        if(i > stack[top]) top--; //pull
        minnum_ItoN = nums[stack[top]];

        instability_score = maxnum_1toI - minnum_ItoN;
        if(instability_score <= k){
            free(stack); return i;
        }
    }

    free(stack);
    return -1;
}