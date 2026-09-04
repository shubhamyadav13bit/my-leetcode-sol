/*
Problem: Leetcode 28. Find the Index of the First Occurrence in a String
Difficulty: Easy
Topics: KMP, String Matching

Solution:
This solution uses the Knuth-Morris-Pratt (KMP) algorithm to efficiently search for the `needle` 
substring within the `haystack`. First, it computes the longest proper prefix-suffix (LPS) array for
`needle`, which stores for each position the length of the longest proper prefix that is also a suffix.
During the scan of `haystack`, we maintain a window starting at index `i` and compare characters of `needle` 
with `haystack[i+j]`. When a mismatch occurs, the LPS array is used to skip redundant comparisons: instead 
of moving `i` by only one, we shift `i` forward by `j - lps[j-1]`, effectively reusing the matched prefix 
information. This avoids rechecking characters that are already known to match, leading to linear-time 
performance. When all characters of `needle` match, the starting index `i` is returned; if the end of 
`haystack` is reached without a full match, -1 is returned.

Time: O(n + m) – The LPS array is built in O(m) time, and the scanning phase processes each character of 
`haystack` at most once due to the skipping mechanism.
Space: O(m) – The LPS array uses O(m) extra space.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Using KMP for searching, new concept, got help
void computeLPS(char* arr, int* lps){
    int arrlen = strlen(arr);
    if(arrlen == 0) return;

    int i = 1, len = 0;
    lps[0] = 0;
    while(i < arrlen){
        if(arr[i] == arr[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len != 0){
                len = lps[len-1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

int strStr(char* haystack, char* needle) {
    int needle_len = strlen(needle), haystack_len = strlen(haystack);
    int i = 0, j;
    
    int *lps = NULL;    lps = malloc(needle_len*sizeof(int));
    if(lps == NULL) return -2; //error code for memory mallocation failure
    computeLPS(needle, lps);

    while(i <= (haystack_len - needle_len)){
        j = 0;
        while(j < needle_len && needle[j] == haystack[i+j]) j++;
        if(j == needle_len){
            free(lps);
            return i; //needle found in haystack
        }
        else{
            if(j == 0) i++;
            else i = i + j - lps[j-1]; 
        }
    }

    free(lps);
    return -1;
}

/*
0123456789
      eieidjsl
djskkaoiieisls 14
eieidjsl        8
14 - 8 = 6
*/