class Solution:
    def reverseParentheses(self, s: str) -> str:
        stack = [] #stack of indices of s containing '('
        slen = len(s)
        for i in range(slen):
            while s[i] != '(' or s[i] != ')':
                i += 1
                continue

            if s[i] == '(':
                stack.append(i)

            if s[i] == ')':
                self.reverseSubString(s, stack.pop()+1, i-1)
                #I think we can reduce reversing if we see the depth of characters, if even, no net reversing, if odd, one reverse, idk how to get that depth, is it simply the number of elements in stack?, but this approach might bring errors

            i += 1
        
        output = []
        for i in range(slen):
            if s[i] == '(' or s[i] == ')':
                continue
            else:
                output.append(s[i])
        
        return ''.join(output)

    def reverseSubString(self, s, l, r):
        m = (l+r)/2
        i = l
        while i <= m:
            temp = s[i]
            s[i] = s[r-(i-l)]
            s[r-(i-l)] = temp
            i += 1
