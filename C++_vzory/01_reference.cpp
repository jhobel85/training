#include <iostream>
#include <string>
#include <memory>

class Service {
public:
    Service(std::string text) : text(text) {}
    void do_something() {std::cout << "Hello" << text; }    
private:
    std::string text;
};

class Consumer0 {
public:
    Consumer0(Service &service) : service(service) {}
    void run() {service.do_something(); }
private:
    Service &service;
};

//- Raw pointer T*
//	- stack_var
//	- New / delete (doubler, free, use after free)
//- Reference T&
//- Unique & shared pointer
//	- When non needed it will be deleted.
//Std:make_unique<T>

int reference() {
    auto service = std::make_unique<Service>("World2"); // create a service
    Consumer0 consumer(*service); // unique -> ref // pass it to consumer
    consumer.run(); //and run it.
    // What is advantage here?
    //we can configure it, we can configure some part and then change it easily
    //we can have more services
    // we can change easily code to do something else
}