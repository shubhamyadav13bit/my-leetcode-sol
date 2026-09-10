/*
Leetcode Daily for 10 Sept, 2026
Problem: Leetcode 2265. Count Nodes Equal to Average of Subtree
Difficulty: Medium
Topics: DFS, Recursion, Binary Tree, Post-order Traversal

Solution:
Recursively process each subtree in post-order. For every node, compute the sum 
and count of nodes in its subtree by combining the node value with the left 
and right subtree results. For a leaf, the subtree sum is the node value and 
count is 1. Increment the answer when the integer average (floor of sum / count) 
equals the node value. Returning both sum and count lets each parent compute its 
own subtree average without traversing the subtree again.

Time: O(n) – each node is visited once.
Space: O(h) – recursion stack depth is the tree height, worst-case O(n) for a skewed tree.
*/

#include <stddef.h> //only for NULL

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct Info {
    int sum;
    int count;
} info;

info dfs(struct TreeNode *root, int *ans) {
    info output;
    if(root == NULL) {
        output.sum = 0;
        output.count = 0;
        return output; 
    }
    if(root->left == NULL && root->right == NULL) {
        output.sum = root->val;
        output.count = 1;
        (*ans)++;
        return output;
    }

    info left = dfs(root->left, ans);
    info right = dfs(root->right, ans);
    int totalsum = root->val + left.sum + right.sum;
    int totalcount = 1 + left.count + right.count;

    output.sum = totalsum;
    output.count = totalcount;
    
    int avg = totalsum / totalcount; //this does truncation towards 0, which works for non negative numbers
    if(avg == root->val) (*ans)++;

    return output;
}

int averageOfSubtree(struct TreeNode* root) {
    int ans = 0;
    dfs(root, &ans);
    return ans;
}