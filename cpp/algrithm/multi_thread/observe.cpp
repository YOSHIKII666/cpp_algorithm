#include <iostream>
#include <vector>
#include <algorithm>

// ����۲��߽ӿ�
class Observer {
public:
    virtual void update(int newState) = 0;
};

// ����������
class Subject {
private:
    std::vector<Observer*> observers;
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it!= observers.end()) {
            observers.erase(it);
        }
    }

    void notify(int newState) {
        for (Observer* observer : observers) {
            observer->update(newState);
        }
    }
};

// ����۲�����1
class ConcreteObserver1 : public Observer {
public:
    void update(int newState) override {
        std::cout << "ConcreteObserver1 received update. New state: " << newState << std::endl;
    }
};

// ����۲�����2
class ConcreteObserver2 : public Observer {
public:
    void update(int newState) override {
        std::cout << "ConcreteObserver2 received update. New state: " << newState << std::endl;
    }
};

//����۲���3
class ConcreateObservation3:public Observer{
    public:
        void update(int state) override{
            std::cout<<"calculate new result"<<state*2<<std::endl;
        }
};

// ����������
class ConcreteSubject : public Subject {
private:
    int state;
public:
    void setState(int newState) {
        state = newState;
        notify(newState);
    }
};

int main() {
    ConcreteSubject subject;
    ConcreteObserver1 observer1;
    ConcreteObserver2 observer2;
    ConcreateObservation3 observer3;

    subject.attach(&observer1);
    subject.attach(&observer2);
    subject.attach(&observer3);

    subject.setState(10);

    subject.detach(&observer1);

    subject.setState(20);

    return 0;
}