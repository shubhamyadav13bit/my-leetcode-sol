/*
Problem: Leetcode 486. Predict the Winner
Difficulty: Medium
Topics: Array, Dynamic Programming, Recursion, Minimax

Solution: Top-down memoized recursion (interval DP). 
        memo[l][r] stores the maximum score difference (Player1 - Player2) 
        achievable from subarray nums[l..r] under optimal play.
Time: O(n^2)
Space: O(n^2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


int max_score_diff(int *nums, int numsSize, int l, int r, int **memo) {
    if (l > r) return 0; // base case

    if (memo[l][r] != INT_MAX) return memo[l][r]; // cache read

    int player_turn = numsSize - (r - l + 1) + 1;
    int lp = max_score_diff(nums, numsSize, l + 1, r, memo);
    int rm = max_score_diff(nums, numsSize, l, r - 1, memo);

    if (player_turn % 2 == 1) {
        // Player 1's turn - maximize the difference (P1 - P2)
        memo[l][r] = ((lp + nums[l]) >= (rm + nums[r])) ? lp + nums[l] : rm + nums[r];
        return memo[l][r];
    } else {
        // Player 2's turn - minimize the difference (P1 - P2)
        memo[l][r] = ((lp - nums[l]) <= (rm - nums[r])) ? lp - nums[l] : rm - nums[r];
        return memo[l][r];
    }
}

bool predictTheWinner(int* nums, int numsSize) {
    int **memo = NULL;
    memo = malloc(numsSize * sizeof(int*));
    if (!memo) {
        printf("Memory allocation for memo failed.");
        return false;
    }

    for (int i = 0; i < numsSize; i++) {
        memo[i] = malloc(numsSize * sizeof(int));
        if (!memo[i]) {
            printf("Memory allocation failed for memo[%d]", i);
            for (int j = 0; j < i; j++) free(memo[j]);
            free(memo);
            return false;
        }

        for (int j = 0; j < numsSize; j++) {
            memo[i][j] = INT_MAX;
        }
    }

    int output = max_score_diff(nums, numsSize, 0, numsSize - 1, memo);

    for (int i = 0; i < numsSize; i++) free(memo[i]);
    free(memo);

    return output >= 0;
}