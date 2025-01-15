#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        vector<vector<int>> tree(n);
        for (const auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        
        int componentCount = 0;
        dfs(0, tree, values, k, componentCount);
        return componentCount;
    }

    int dfs(int node, vector<vector<int>>& tree, vector<int>& values, int k, int& componentCount) {
        int sum = values[node];
        
        for (int child : tree[node]) {
            tree[child].erase(find(tree[child].begin(), tree[child].end(), node));  // Remove the parent from the child's list
            sum += dfs(child, tree, values, k, componentCount);
        }
        
        // If the sum of the component is divisible by k, increment the count
        if (sum % k == 0) {
            componentCount++;
            return 0;  // Cut this edge
        }
        
        return sum;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> edges = {{0, 2}, {1, 2}, {1, 3}, {2, 4}};
    vector<int> values = {1, 8, 1, 4, 4};
    cout << sol.maxDivisibleComponents(5, edges, values, 6) << endl;  // Output: 2
    return 0;
}
