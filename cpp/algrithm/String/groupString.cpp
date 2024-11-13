#include<vector>
#include<string>
#include<unordered_map>
#include<iostream>
class solution{
    public:
        std::vector<std::vector<std::string>> groupAngrams(std::vector<std::string>& strs){
            std::unordered_map<std::string,std::vector<std::string>> map;
            for(std::string str:strs){
                std::string sorted=str;
                std::sort(sorted.begin(),sorted.end());
                if(map.find(sorted)==map.end()){
                    map[sorted]=std::vector<std::string>();
                }
                map[sorted].push_back(str);
            }
            std::vector<std::vector<std::string>> res;
            for(auto pair:map){
                res.push_back(pair.second);
            }
            return res;
        }
};