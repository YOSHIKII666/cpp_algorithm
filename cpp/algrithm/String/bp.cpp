#include<string>

class solution{
    public :
        int strStr(std::string haystack,std::string needle){
            int len=needle.size();
            int l=0;
            int r=len-1;
            while(r<haystack.size()){
            if(haystack.substr(l,r-l+1)==needle){//cpp中的substr操作是(起点坐标，截取长度),java中的subString是(起点坐标，终点坐标+1)
                return l;
            }else{
                l++;
                r++;
            }
        }
            return -1;
        }
};