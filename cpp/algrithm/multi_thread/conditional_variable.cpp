#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<vector>

std::mutex mtx;
std::condition_variable cv;
std::vector<int> list;
const int MAX_QUEUE_SIZE=10;

void product(){
    for(int i=0;i<20;i++){
        std::unique_lock<std::mutex>lock(mtx);
        if(list.size()>=10){
            cv.wait(lock);
        }
        list.push_back(i);
        std::cout<<"生产数据："<<i<<std::endl;
        cv.notify_all();
    }
}

void consumer(int id){
    while(true){
        std::unique_lock<std::mutex>lock(mtx);
        while(list.empty()){
            cv.wait(lock);
        }
        int data=list.back();
        list.pop_back();
        std::cout<<"消费者:"<<id<<"消费数据:"<<data<<std::endl;
        cv.notify_all();
    }
}

int main(int argc, char const *argv[])
{
    std::thread prod(product);
    std::vector<std::thread> consumers;
    for(int i=0;i<3;i++){
        consumers.push_back(std::thread(consumer,i));
    }
    prod.join();
    for(auto& t:consumers){
        t.join();
    }
    return 0;
}
