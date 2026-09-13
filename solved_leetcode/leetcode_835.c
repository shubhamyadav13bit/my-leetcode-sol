/*
Leetcode Daily for 13 Sept, 2026
Problem: Leetcode 835. Image Overlap
Difficulty: Medium
Topics: Recursion, DFS, Memoization, Matrix

Solution:
The algorithm treats each possible translation of the two images as a state, represented by the top-left corner offset 
(tlc) of img1 relative to img2. A memoization table is used to avoid recomputing the overlap for the same translation.

The solution uses four recursive DFS functions (goNW, goNE, goSW, goSE) that traverse the translation space in four 
quadrants. Each function starts from a distinct seed offset to ensure that every translation in the range 
[-(n-1), n-1] x [-(n-1), n-1] is covered exactly once without gaps or overlaps. Before processing a translation, 
the function checks if it has already been visited (via the memo table); if not, it computes the overlap count using 
calculateOverlap and marks it visited.

calculateOverlap computes the overlapping region between img1 and img2 for a given translation tlc. It calculates the 
top-left and bottom-right corners of the intersecting rectangle, iterates over all pixels in that rectangle, and counts 
positions where both images have a 1. The result is stored in the memo table.

Finally, the maximum value in the memo table is returned as the largest possible overlap.

Time: O(n^4) - There are O(n^2) translations, and for each translation we may scan up to O(n^2) pixels in the overlap 
region, leading to O(n^4) in the worst case. The DFS traversal visits each translation at most once due to memoization.
Space: O(n^2) - The memoization table stores O(n^2) integer values, and the recursion depth is at most O(n) in each 
direction, so the space complexity is dominated by the memo table.
*/
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int r;
    int c;
} coords;

void calculateOverlap(int **img1, int **img2, int n, coords tlc, int **memo){
    if(tlc.r == n || tlc.c == n || tlc.r == -n || tlc.c == -n) return;
    if(memo[tlc.r + n - 1][tlc.c + n - 1] != -1) return;
    else memo[tlc.r + n - 1][tlc.c + n - 1] = 0;
    coords i0, i1;
    i0.r = (tlc.r >= 0) ? tlc.r : 0;
    i0.c = (tlc.c >= 0) ? tlc.c : 0;
    coords brc = (coords){tlc.r + n - 1, tlc.c + n - 1};
    i1.r = (brc.r < n) ? brc.r : n - 1;
    i1.c = (brc.c < n) ? brc.c : n - 1;
    for(int i = i0.r; i <= i1.r; i++) {
        for(int j = i0.c; j <= i1.c; j++) {
            if(img1[i - tlc.r][j - tlc.c] == 1 && img2[i][j] == 1)
                memo[tlc.r + n - 1][tlc.c + n - 1]++;
        }
    }
}

void goNW(int **img1, int **img2, int n, coords tlc, int **memo) {
    if (tlc.r == -n || tlc.c == -n) return;
    if (memo[tlc.r + n - 1][tlc.c + n - 1] != -1) return;
    calculateOverlap(img1, img2, n, tlc, memo);
    goNW(img1, img2, n, (coords){tlc.r - 1, tlc.c}, memo);
    goNW(img1, img2, n, (coords){tlc.r, tlc.c - 1}, memo);
}

void goNE(int **img1, int **img2, int n, coords tlc, int **memo) {
    if (tlc.r == -n || tlc.c == n) return;
    if (memo[tlc.r + n - 1][tlc.c + n - 1] != -1) return;
    calculateOverlap(img1, img2, n, tlc, memo);
    goNE(img1, img2, n, (coords){tlc.r - 1, tlc.c}, memo);
    goNE(img1, img2, n, (coords){tlc.r, tlc.c + 1}, memo);
}

void goSW(int **img1, int **img2, int n, coords tlc, int **memo) {
    if (tlc.r == n || tlc.c == -n) return;
    if (memo[tlc.r + n - 1][tlc.c + n - 1] != -1) return;
    calculateOverlap(img1, img2, n, tlc, memo);
    goSW(img1, img2, n, (coords){tlc.r + 1, tlc.c}, memo);
    goSW(img1, img2, n, (coords){tlc.r, tlc.c - 1}, memo);
}

void goSE(int **img1, int **img2, int n, coords tlc, int **memo) {
    if (tlc.r == n || tlc.c == n) return;
    if (memo[tlc.r + n - 1][tlc.c + n - 1] != -1) return;
    calculateOverlap(img1, img2, n, tlc, memo);
    goSE(img1, img2, n, (coords){tlc.r + 1, tlc.c}, memo);
    goSE(img1, img2, n, (coords){tlc.r, tlc.c + 1}, memo);
}

int largestOverlap(int** img1, int img1Size, int* img1ColSize, int** img2, int img2Size, int* img2ColSize) {
    int n = img1Size;

    int **memo = malloc((2 * n - 1) * sizeof(int*));
    if (!memo) return -1;
    for (int i = 0; i < 2 * n - 1; i++) memo[i] = NULL;
    for (int i = 0; i < 2 * n - 1; i++) {
        memo[i] = malloc((2 * n - 1) * sizeof(int));
        if (!memo[i]) {
            for (int j = 0; j < i; j++) free(memo[j]);
            free(memo);
            return -1;
        }
    }
    for (int i = 0; i < 2 * n - 1; i++)
        for (int j = 0; j < 2 * n - 1; j++)
            memo[i][j] = -1;

    goNW(img1, img2, n, (coords){0, 0}, memo);
    goNE(img1, img2, n, (coords){0, 1}, memo);
    goSW(img1, img2, n, (coords){1, 0}, memo);
    goSE(img1, img2, n, (coords){1, 1}, memo);

    int max = 0;
    for (int i = 0; i < 2 * n - 1; i++)
        for (int j = 0; j < 2 * n - 1; j++)
            if (memo[i][j] > max) max = memo[i][j];

    for (int i = 0; i < 2 * n - 1; i++) free(memo[i]);
    free(memo);
    return max;
}