#include<iostream>
int main(int argc, char const *argv[])
{
    int** b=new int*[6];
    for(int i=0;i<6;i++){
        b[i]=new int[8];
    }
    b[2][0]=2;
    //由此可见，二级指针前进一位，相当于一级指针的数组前进一整行
    std::cout<<**(b+2)<<std::endl;
    return 0;
}
