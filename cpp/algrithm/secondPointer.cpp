#include<iostream>
int main(int argc, char const *argv[])
{
    int** b=new int*[6];
    for(int i=0;i<6;i++){
        b[i]=new int[8];
    }
    b[2][0]=2;
    //�ɴ˿ɼ�������ָ��ǰ��һλ���൱��һ��ָ�������ǰ��һ����
    std::cout<<**(b+2)<<std::endl;
    return 0;
}
