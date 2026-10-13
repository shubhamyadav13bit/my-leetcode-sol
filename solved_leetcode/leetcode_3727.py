# Problem: Leetcode 3727. Maximum Alternating Sum of Squares
# Leetcode Daily for 13 Oct, 2026
# If you are reading this, then you may relate that debugging such a simple code snippet on your own is frustrating
# Difficulty: Medium
# Topics: Sorting, Greedy, Math, List Comprehension
#
# Solution:
# Square every element in the array, then sort the squared values in non-decreasing order.
# To maximize the alternating sum (which subtracts the smaller half and adds the larger half),
# pair the smallest squared values as the subtracted terms and the largest squared values as the added terms.
# The loop iterates over half the array length, subtracting the i-th smallest and adding the i-th largest.
# If the array length is odd, the median squared value is added to the result.
#
# Time: O(n log n) - dominated by the sort operation; the list comprehension and the loop are O(n).
# Space: O(n) - a new list of squared values is created and sorted.
class Solution:
    def maxAlternatingSum(self, nums: list[int]) -> int:
        numslen = len(nums)
        nums = [n**2 for n in nums]
        snums = sorted(nums)
        output = 0
        for i in range(numslen//2):
            output -= snums[i]
            output += snums[numslen-1 - i]
        if numslen % 2 != 0:
            output += snums[numslen//2]
        return output