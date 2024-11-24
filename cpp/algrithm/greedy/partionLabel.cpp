//
// Created by 王少泽 on 2024/11/24.
//

#include <vector>
class solution {
public:
    std::vector<int> partionLabels(std::string s) {
        std::vector<int> v1(26);
        for(int i=0;i<s.size();i++) {
            v1[s[i]-'a']=i;
        }
        int max=0;
        int left=0;
        std::vector<int> res;
        for(int i=0;i<s.size();i++) {
            max=std::max(max,v1[s[i]-'a']);
            if(i==max) {
                res.push_back(i-left+1);
                left=i+1;
            }
        }
        return res;
    }
};
