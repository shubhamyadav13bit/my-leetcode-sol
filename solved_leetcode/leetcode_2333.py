# Problem: Leetcode 2333. Minimum Sum of Squared Difference
# Difficulty: Medium
# Topics: Heap, Greedy, Math, Simulation
#
# Solution:
# Compute absolute differences between nums1[i] and nums2[i], then greedily
# reduce the largest differences using at most k1 + k2 operations. A max-heap
# tracks the current maximum difference and how many indices share it. At each
# step, the algorithm either lowers the current maximum group by the uniform
# amount q = k // num_maxeq, or consumes the gap to the next distinct maximum
# and merges that group. This process repeats until k is exhausted or the
# maximum difference reaches zero. Finally, the remaining heap elements and
# the current maximum group are squared and summed.
#
# Time: O(n log n) - heapify takes O(n), and each distinct value is pushed/popped at most once.
# Space: O(n) - the heap stores up to n elements.
import heapq

class Solution:
    def minSumSquareDiff(self, nums1: list[int], nums2: list[int], k1: int, k2: int) -> int:
        n = len(nums1) # = len(nums2)

        absdiff = [0] * n # array of absolute diff (ie |nums1[i] - nums2[i]| )
        for i in range(n):
            absdiff[i] = abs(nums1[i] - nums2[i])
        return self.reduce(k1+k2, absdiff)

    def reduce(self, k: int, arr: list[int]) -> int:
        if not arr:
            return 0
        
        heap = [-x for x in arr]
        heapq.heapify(heap)
        
        neg_maxeq = heapq.heappop(heap)
        maxeq = -1 * neg_maxeq
        num_maxeq = 1

        sum_sq = 0
        while k > 0:
            q = k // num_maxeq
            if not heap: #reduce maxeq till maxeq = 0 or k = 0
                if k > num_maxeq * maxeq:
                    return 0
                else:
                    maxeq -= q
                    k -= q * num_maxeq
                    #k of maxequals (currently k < num_maxeq) will be further reduced by 1, reducing k to 0
                    sum_sq += k*((maxeq-1)**2) + (num_maxeq-k)*(maxeq**2)
                    return sum_sq

            heapmax = -heap[0]
            gap = maxeq - heapmax
                
            if gap > q:
                maxeq -= q
                k -= q * num_maxeq
                #k of maxequals (currently k < num_maxeq) will be further reduced by 1, reducing k to 0
                sum_sq += k*((maxeq-1)**2) + (num_maxeq-k)*(maxeq**2)
                num_maxeq = 0
                break # make the exit obvious
            else:        
                maxeq -= gap
                k -= gap * num_maxeq
                heapq.heappop(heap) # pop heapmax
                num_maxeq += 1 # make heapmax a part of maxeq

        sum_sq += num_maxeq * maxeq ** 2 # When loop exits not by obvious 'break' above and maxeq's arent added to sum_sq

        for x in heap:
            sum_sq += x**2 # negative signs will cancel out

        return sum_sq