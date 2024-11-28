#include<vector>
#include<iostream>
#include<condition_variable>
#include<thread>
#include<mutex>
#include<string>
#include<algorithm>

class observe{
public:
    virtual void update(std::string name,double price);
};

class subject{
    protected:
        std::vector<observe*> observes;
        std::mutex mutex_;
        std::condition_variable cv;
        bool price_change;
    public:
        subject():price_change(false){};

        //添加观察者
        void attach(observe* ob){
            std::lock_guard<std::mutex> guard(mutex_);
            observes.push_back(ob);
        }
        //删除
        void detach(observe* ob){
            std::lock_guard<std::mutex> guard(mutex_);
            auto it=std::find(observes.begin(),observes.end(),ob);
            if(it!=observes.end()){
                observes.erase(it);
            }
        }

        virtual void notify_all(std::string stockname,double price);
        virtual void set_price(std::string stockname,double price);
};

class concreate:public subject{
    public:
        void notify_all (std::string stockname,double price) override{
            std::unique_lock<std::mutex> lock(mutex_);
            cv.wait(lock,[this]{return price_change;});
            for(observe* observer:observes){
                observer->update(stockname,price);
            }
            price_change=false;
        }
        void set_price(std::string stockname,double price) override{
            {
                std::unique_lock<std::mutex> guard(mutex_);
                price_change=true;
            }
            cv.notify_all();
        }
};

//观察者，股票用户
class ob1:public observe{
    private:
        std::string name;
    public:
        ob1(std::string name):name(name){};
        void update(std::string stockname,double price) override{
            std::cout<<name<<"received update:"<<stockname<<"price is now:"<<price<<std::endl;
        }
};

//模拟价格变换的函数
void update_price(subject* sub,std::string name){
    double price=100.0;
    while(true){
        price+=(rand()%10-5)/10.0;
        sub->set_price(name,price);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(int argc, char const *argv[])
{
    std::cout<<"xxxx"<<std::endl;
    concreate c1;
    ob1 a("mike");
    ob1 b("jack");
    ob1 c("lee");

    c1.attach(&a);
    c1.attach(&b);
    c1.attach(&c);

    std::string stockname="crop";

    std::thread change(update_price,&c1,stockname);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    c1.detach(&b);
    
    std::this_thread::sleep_for(std::chrono::seconds(10));
    change.join();
    return 0;
}

