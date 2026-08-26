/*
Problem: Leetcode 2904. Shortest and Lexicographically smallest Beautiful string
Leetcode Daily for 26 August, 2026
Difficulty: Medium
Topics: String, Sliding Window, Two Pointers, Substring, Lexicographical Order

Solution: 
The shortest beautiful substring must start and end with '1', so we iterate over
each '1' as a potential starting index. For a fixed start `i`, we extend a
pointer `j` forward until we have collected exactly `k` ones. When a valid
substring s[i..j] is found, we compare its length and (if equal) its
lexicographic order against the current best, updating accordingly.
To avoid redundant work, we reuse the previous `j` position when moving to the
next starting '1', and we only scan forward - both `i` and `j` move
monotonically, giving linear time.

Time: O(n) - each character is visited at most once by `i` and `j`.
Space: O(n) - for the output string returned; auxiliary space is O(1).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shortestBeautifulSubstring(char* s, int k) {
    //strlen(s) <= 100, so int, size_t overkill
    int slen = strlen(s);
    if(k == 1){
        for(int i = 0; i < slen; i++) if(s[i] == '1') return "1";
        return "";
    }

    int i, j, count, len;
    int imin = -1, jmin, minlen = -1;
    int jprev;
    i = 0;
    while(i < slen){
        if(s[i] == '0'){i++; continue;} //output string will start and end with 1 to be shortest

        //initialize count and j
        if(imin == -1){count = 0; j = i;} //runs only on first iteration, ie when s[i] = 1 for first time
        else{
            j = jprev;
            count = k-1; //i incremented till s[i] jumped from one '1' to another '1'
        }

        //get next j for which count == k
        while(j < slen && count < k){
            if(s[j] == '1') count++;
            j++;
        }

        //get imin, jmin, minlen, len
        if(count == k){
            if(imin == -1) goto curr_string_shortest; //runs on first iteration, ie when s[i] = 1 for first time
            else{
                //check for length
                len = (j-1) - i + 1;
                if(len < minlen){goto curr_string_shortest;}
                else if(len == minlen){
                    //lexico check
                    for(int k = 0; k < minlen; k++){
                        if(s[imin+k] == s[i+k]) continue;
                        else if(s[imin+k] > s[i+k]) goto curr_string_shortest;
                        else break;
                    }
                }
            }
        }
        else{
            break;
            /*This means that above loop exit was because of j and no furthur string is beautiful*/
        }
        
        set_variables_for_next_iteration:
        i++;
        jprev = j;
        continue;

        curr_string_shortest:
        imin = i; 
        jmin = j-1; 
        minlen = jmin - imin + 1;
        goto set_variables_for_next_iteration;
    }

    if(minlen == -1) return "";
    char *output = NULL; output = malloc((minlen+1)*sizeof(char));
    //i know that sizeof(char) = 1 and is redundant
    if(!output) return "-1";

    output[minlen] = '\0';
    for(int k = 0; k < minlen; k++) output[k] = s[imin+k];

    return output;
}