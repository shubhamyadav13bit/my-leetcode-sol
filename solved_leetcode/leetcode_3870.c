/*
Leetcode Daily Question for 8 Sept, 2026
Problem: Leetcode 3870. Count Commas
Difficulty: Easy
Topics: Math

Solution:
The problem asks for the number of integers in [1, n] that contain a comma when written in standard comma-separated format. Numbers less than 1000 have no comma, while every integer from 1000 to n inclusive has at least one comma. Therefore, the count is simply max(0, n - 999). This formula works for all n.

Time: O(1) – only arithmetic operations.
Space: O(1) – no extra memory used.
*/
int countCommas(int n) {
    if(n < 1000) return 0;
    else return n - 999;
}