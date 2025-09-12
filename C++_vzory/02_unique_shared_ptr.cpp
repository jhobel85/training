#include <iostream>
#include <string>
#include <memory>

class Draw{
    public:
    virtual void draw_line(int pixels, int degress) = 0;
    //00 .. 359
    // 0 degress = right
    // 90 degrees = up
};

class TestDraw : public Draw {
    public:
        void draw_line(int pixels, int direction) override {
        std::cout << "Drawing line of " << pixels << " pixels at " << direction << " degrees.\n";
    }
};


class TestService {
public:
    TestService(std::string text) : text(text) {}
    void do_something() {std::cout << "Hello" << text << std::endl; }        
private:
    std::string text;
};

//mark something 
class Consumer {
public:
    Consumer(std::unique_ptr<TestService> service) 
    : service(std::move(service)) {}
    void run() {service->do_something(); }
private:
    std::unique_ptr<TestService> service;
};

class Consumer2 {
public:
    Consumer2(std::shared_ptr<TestService> service) 
    : service(service) {}
    void run() {service->do_something(); }
private:
    std::shared_ptr<TestService> service;
};

int main2() {
    auto service = std::make_unique<TestService>("Unique_PTR"); // create a service
    Consumer consumer(std::move(service)); // unique -> ref // pass it to consumer // DO NOT  
    
    auto service2 = std::make_shared<TestService>("Shared_PTR"); // create a service
    Consumer2 consumer2(service2);
    //service = nullptr; //free
    
    consumer.run();
    consumer2.run(); 
    std::cin.get();
    std::cerr << "Hi\n"; // in case of error developer can see it.
}