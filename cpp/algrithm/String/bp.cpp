#include<string>

class solution{
    public :
        int strStr(std::string haystack,std::string needle){
            int len=needle.size();
            int l=0;
            int r=len-1;
            while(r<haystack.size()){
            if(haystack.substr(l,r-l+1)==needle){//cpp�е�substr������(������꣬��ȡ����),java�е�subString��(������꣬�յ�����+1)
                return l;
            }else{
                l++;
                r++;
            }
        }
            return -1;
        }
};