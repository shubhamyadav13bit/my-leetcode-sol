# Problem: Leetcode 1807. Evaluate the Bracket Pairs of a String
# LeetCode Daily for 26 Sept, 2026
# Difficulty: Medium
# Topics: Hash Map, String, Simulation
#
# Solution:
# Build a dictionary that maps each key to its value so bracket lookups are O(1)
# instead of scanning the knowledge list every time. Then scan the input string
# character by character: when a '(' is hit, advance past it and collect every
# character into keyholder until the closing ')'. The collected characters are
# joined into a key string, looked up in the dictionary (falling back to "?" if
# the key is unknown), and the resulting value is appended to the output. All
# other characters are appended verbatim. The inner loop stops *on* the ')', so
# the outer i += 1 is what skips past it, keeping the scan in sync.
#
# Time: O(n + m) – one pass over the input string (n) plus one pass to build the
#       dictionary from the knowledge list (m)
# Space: O(n + m) – the output list holds one entry per input character (n) and
#       the dictionary holds one entry per knowledge pair (m)

class Solution:
    def evaluate(self, s: str, knowledge: list[list[str]]) -> str:
        lookup = {} #like a hash table in c for O(1) lookup times intead of O(n)
        for j in range(len(knowledge)):
            lookup[knowledge[j][0]] = knowledge[j][1]

        slen = len(s)
        output = []
        
        i = 0
        keyholder = []
        while i < slen:
            if s[i] == '(':
                keyholder.clear()
                
                i += 1
                while i < slen and s[i] != ')':
                    keyholder.append(s[i])
                    i += 1

                key = ''.join(keyholder)

                output.append(lookup.get(key, "?"))

            else:
                output.append(s[i])

            i += 1

        return ''.join(output)
