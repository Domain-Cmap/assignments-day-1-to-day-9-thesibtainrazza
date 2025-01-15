#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rootCount(int n, vector<vector<int>>& edges, vector<vector<int>>& guesses, int k) {
        vector<vector<int>> tree(n);
        for (const auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        
        vector<vector<bool>> isGuessed(n, vector<bool>(n, false));
        for (const auto& guess : guesses) {
            isGuessed[guess[0]][guess[1]] = true;
        }
        
        vector<int> guessCount(n, 0);
        for (int root = 0; root < n; ++root) {
            dfs(root, tree, isGuessed, guessCount, 0, k);
        }
        
        int validRoots = 0;
        for (int i = 0; i < n; ++i) {
            if (guessCount[i] >= k) validRoots++;
        }
        
        return validRoots;
    }
    
    void dfs(int node, vector<vector<int>>& tree, vector<vector<bool>>& isGuessed, vector<int>& guessCount, int currentGuess, int k) {
        if (currentGuess >= k) return;
        
        guessCount[node]++;
        
        for (int child : tree[node]) {
            dfs(child, tree, isGuessed, guessCount, currentGuess + (isGuessed[node][child] ? 1 : 0), k);
        }
    }
};

int main() {
    Solution sol;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}, {4, 2}};
    vector<vector<int>> guesses = {{1, 3}, {0, 1}, {1, 0}, {2, 4}};
    cout << sol.rootCount(5, edges, guesses, 3) << endl;  // Output: 3
    return 0;
}
