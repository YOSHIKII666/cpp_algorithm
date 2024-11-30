#include <vector>
#include<mutex>
#include<thread>
#include <algorithm>
#include <iostream>

class observer {
public:
    virtual void update(double cost)=0;
    virtual ~observer()=default;
};

class subject {
public:
    std::vector<observer*> vector_;
    virtual void add(observer*)=0;
    virtual void deleted(observer*)=0;
    virtual void notifyAll()=0;
    virtual ~subject()=default;
};

class concreat:public subject {
private:
    int price;
    std::mutex mutex_;
public:
    void add(observer* ob) override {
        std::lock_guard<std::mutex> guard(mutex_);
        vector_.push_back(ob);
    }
    void deleted(observer* ob) override {
        std::lock_guard<std::mutex> guard(mutex_);
        auto it=std::find(vector_.begin(),vector_.end(),ob);
        if(it!=vector_.end()) {
            vector_.erase(it);
        }
    }
    void notifyAll() override {
        //设置一个互斥锁，防止在遍历时析构函数被触发了，导致空指针异常
        std::lock_guard<std::mutex> guard(mutex_);
        for(observer* ob:vector_) {
            ob->update(price);
        }
    }
    void set(int price) {
        this->price=price;
    }
};
class street:public observer {
private:
    double price=0;
    subject& s;
public:
    street(subject& sub):s(sub) {
            s.add(this);
    }
    void update(double cost) override {
        std::cout<<"price is:"<<cost*2<<std::endl;
    }
     ~street() {
        s.deleted(this);
    }
};

class wall:public observer {
private:
    double price=0;
    subject& s;
public:
    wall(subject& sub):s(sub) {
        s.add(this);
    }
    void update(double cost) override {
        std::cout<<"price is:"<<cost*3<<std::endl;
    }
    ~wall() {
        s.deleted(this);
    }
};

void addp(concreat& sub) {
    street st(sub);
    sub.set(200);
    sub.notifyAll();
}

int main(int argc, char *argv[]) {
    concreat sub;
        wall w(sub);
        sub.set(400);
        sub.notifyAll();
    std::thread t(addp,std::ref(sub));
    t.join();//主线程等待thread处理完
}
