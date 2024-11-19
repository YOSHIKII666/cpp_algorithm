#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>

std::mutex mtx;
std::condition_variable cv;

int turn=0;
const int COUNT=100;

void printA(){
    for(int i=0;i<COUNT;++i){
        std::unique_lock<std::mutex> lock(mtx);
        while(turn!=0){
            cv.wait(lock);
        }
        std::cout<<"a";
        turn=1;
        cv.notify_all();
    }
}
void printB(){
    for(int i=0;i<COUNT;i++){
        std::unique_lock<std::mutex> lock(mtx);
        while(turn!=1){
            cv.wait(lock);
        }
        std::cout<<"b";
        turn=2;
        cv.notify_all();
    }
}
void printC(){
    for(int i=0;i<COUNT;i++){
        std::unique_lock<std::mutex> lock(mtx);
        if(turn!=2){
            cv.wait(lock);
        }
        std::cout<<"c";
        turn=0;
        cv.notify_all();
    }
}
int main(int argc, char const *argv[])
{
    std::thread t1(printA);    
    std::thread t2(printB);    
    std::thread t3(printC);
    t1.join();
    t2.join();
    t3.join();    
    return 0;
}
