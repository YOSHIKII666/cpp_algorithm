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
    virtual void add(observer*);
    virtual void deleted(observer*);
    virtual void notifyAll();
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
        std::cout<<"price is:"<<cost*2<<std::endl;
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
    std::thread t(addp,std::ref(sub));

    wall w(sub);
    sub.set(400);
    sub.notifyAll();

    t.join();
}
