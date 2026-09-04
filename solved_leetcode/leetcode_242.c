/*
Problem: Leetcode 242. Valid Anagram
Difficulty: Easy
Topics: Hash Table, Array, Counting

Solution:
Use a fixed-size integer array to count character frequencies. For each character in s, increment the
corresponding count; for each character in t, decrement it. If the two strings are anagrams, all counts
will be zero at the end. This works because the total length is equal and every character from one string 
cancels with the corresponding character from the other.

Time: O(n) – one pass through both strings.
Space: O(1) – constant-size array of 26 integers.
*/
#include <stdbool.h>
#include <stdlib.h>

bool isAnagram(char* s, char* t) {
    int slen = strlen(s), tlen = strlen(t);
    if(slen != tlen) return false;

    int *count = NULL;  count = calloc(26, sizeof(int));
    if(count == NULL) return false; //memory callocation failure

    for(int i = 0; i < slen; i++){
        count[s[i] - 'a']++;
        count[t[i] - 'a']--;
    }

    for(int i = 0; i < 26; i++){
        if(count[i] != 0){
            free(count); return false;
        }
    }

    return true;
}