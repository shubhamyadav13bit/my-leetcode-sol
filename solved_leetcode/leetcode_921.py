# Problem: Leetcode 921. Minimum Add to Make Parentheses Valid
# Leetcode Daily for 6 October, 2026
# Difficulty: Medium
# Topics: Stack, String
#
# Solution:
# The algorithm uses a stack to track unmatched opening parentheses. It iterates through
# each character in the string: when an opening parenthesis '(' is encountered, it is
# pushed onto the stack; when a closing parenthesis ')' is found, the algorithm checks
# if there is a matching '(' at the top of the stack. If so, it pops the stack (forming
# a valid pair); otherwise, the ')' is pushed onto the stack as an unmatched closing
# parenthesis. After processing all characters, the stack contains only the unmatched
# parentheses (both '(' and ')'), and the size of the stack represents the minimum
# number of parentheses that need to be added to make the string valid.
#
# Time: O(n) – each character in the string is visited exactly once
# Space: O(n) – in the worst case, the stack may store all characters (e.g., all '(' or all ')')

class Solution:
    def minAddToMakeValid(self, s: str) -> int:
        stack = []

        for ch in s:
            if ch == '(':
                stack.append(ch)
            else:
                if stack and stack[-1] == '(':
                    stack.pop()
                else:
                    stack.append(ch)
        return len(stack)