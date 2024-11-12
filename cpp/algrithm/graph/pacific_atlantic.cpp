#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};
    vector<vector<int>> heights;
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        this->heights=heights;
        vector<vector<bool>> pacific(heights.size(),vector<bool>(heights[0].size()));
        vector<vector<bool>> atlantic(heights.size(),vector<bool>(heights[0].size()));
        for(int i=0;i<heights.size();i++) {
            dfs(i,0,pacific);
        }
        for(int i=0;i<heights[0].size();i++) {
            dfs(0,i,pacific);
        }
        for(int i=0;i<heights.size();i++) {
            dfs(i,heights[0].size()-1,atlantic);
        }
        for(int i=0;i<heights[0].size();i++) {
            dfs(heights.size()-1,i,atlantic);
        }
        vector<vector<int>> res;
        for(int i=0;i<heights.size();i++) {
            for(int j=0;j<heights[0].size();j++) {
                if(pacific[i][j]&&atlantic[i][j]) {
                    vector<int> v1;
                    v1.emplace_back(i);
                    v1.emplace_back(j);
                    res.emplace_back(v1);
                }
            }
        }
        return res;
    }
    void dfs(int i,int j,vector<vector<bool>> &matrix) {
        if(matrix[i][j]) return;
        matrix[i][j] = true;
        for(vector<int> dir:directions) {
            int new_i=i+dir[0];
            int new_j=j+dir[1];
            if(new_i>=0&&new_i<matrix.size()&&new_j>=0&&new_j<matrix[0].size()&&heights[new_i][new_j]>=heights[i][j]) {
                dfs(new_i,new_j,matrix);
            }
        }
    }
};