#include<iostream>
#include<functional>
#include<vector>
#include<future>
#include<memory>
#include<stdexcept>
#include<queue>
#include<thread>

//
class ThreadPool{
public:
    ThreadPool(size_t);
    template<class F,class... Args>
    auto enqueue(F&& f,Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;
    ~ThreadPool();
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queue_mutex;
    std::condition_variable cv;
    bool stop;
};

inline ThreadPool::ThreadPool(size_t threads):stop(false){
    for(size_t i=0;i<threads;++i)
        workers.emplace_back(
            [this]{
                for(;;){//无限循环，直到stop为false或者tasks为empty
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);//上锁
                        this->cv.wait(lock,[this]{return this->stop||!this->tasks.empty();});//线程会在这里阻塞，直到this->stop=true||this->tasks不为空
                        if(this->stop&&this->tasks.empty()) return;
                        task=std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            }
        );
}

template<class F,class... Args>
auto ThreadPool::enqueue(F&& f,Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>{
    using return_type=typename std::result_of<F(Args...)>::type;
    auto task=std::make_shared<std::packaged_task<return_type()>>(//std::package_task主要用于将一个可调用的对象进行包装，使得这个可调用的对象能够以异步的方式进行调用
            std::bind(std::forward<F>(f),std::forward<Args>(args)...)//bind将函数和参数进行重新绑定
    );
    std::future<return_type> res=task->get_future();
    {
        //单独的局部作用域，可以严格控制锁的生命周期
        std::unique_lock<std::mutex> lock(queue_mutex);
        if(stop) throw std::runtime_error("enqueue on stopped ThreadPool");
        //放进缓冲队列中
        tasks.emplace([task](){(*task)();});
    }
    cv.notify_one();
    return res;
}

inline ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop=true;
    }
    cv.notify_all();
    for(std::thread & worker:workers){
        worker.join();
    }
}
const int COUNT=100;
std::mutex mtx;
std::condition_variable cv1;
int turn=0;
void printA(){
    for(int i=0;i<COUNT;i++){
        std::unique_lock<std::mutex> lock(mtx);
        while(turn!=0){
            cv1.wait(lock);
        }
        std::cout<<"a";
        turn=1;
        cv1.notify_all();
    }
}
void printB(){
    for(int i=0;i<COUNT;i++){
        std::unique_lock<std::mutex> lock(mtx);
        while(turn!=1){
            cv1.wait(lock);
        }
        std::cout<<"b";
        turn=2;
        cv1.notify_all();
    }
}
void printC(){
    for(int i=0;i<COUNT;i++){
        std::unique_lock<std::mutex> lock(mtx);
        while(turn!=2){
            cv1.wait(lock);
        }
        std::cout<<"c";
        turn=0;
        cv1.notify_all();
    }
}
int main(int argc, char const *argv[])
{
    ThreadPool pool(3);
    auto future_a=pool.enqueue(printA);
    auto future_b=pool.enqueue(printB);
    auto future_c=pool.enqueue(printC);
    future_a.get();
    future_b.get();
    future_c.get();
    return 0;
}
