# Problem: Leetcode 2897. Apply Operations on Array to Maximize Sum of Squares
# Leetcode Daily for 12 Oct, 2026
# Difficulty: Hard
# Topics: Bit Manipulation, Greedy, Math
#
# Solution:
# The operation replaces nums[i], nums[j] with (nums[i] & nums[j], nums[i] | nums[j]).
# Per bit position, this operation never changes the total count of set bits across
# the whole array: it only moves a 1 from one number to another at each bit. Therefore
# the multiset of "how many 1s exist at bit b" is invariant under any number of operations.
#
# Since we only need to maximize the sum of squares of k chosen numbers, and f(x) = x^2
# is convex, concentrating bits into as few numbers as possible yields the largest sum
# of squares. So we greedily rebuild k numbers: for each bit b from high to low, we
# assign that bit to the first min(k, count[b]) result numbers. Processing bits from
# high to low is the natural greedy order; it ensures higher-value bits are placed
# first, and since final values are just sums of assigned bit values, the result is
# optimal regardless of order.
#
# Time: O(31 * n + 31 * k) – one pass over nums to count bits (31 bits per number),
#       then one pass over bit positions to distribute across k results.
# Space: O(31 + k) – a fixed 31-length bit-count array plus the k result numbers.

class Solution:
    def maxSum(self, nums: List[int], k: int) -> int:
        bits = [0] * 31
        MOD = 10**9 + 7

        for num in nums:
            for b in range(31):
                if num & (1 << b):
                    bits[b] += 1
        
        res = [0] * k

        for b in range(30, -1, -1):
            for i in range(min(k, bits[b])):
                res[i] += (1 << b)
        
        return sum(x**2 for x in res) % MOD




            


                


        

        
