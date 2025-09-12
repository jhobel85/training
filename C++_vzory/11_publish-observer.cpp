#include <memory>
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <algorithm>
#include <iomanip>

// light version of observer pattern

class Subscriber {
public:
    Subscriber(std::string name, std::function<void(std::string)> action)
        : name(name), action(action)
    {
        std::cout << "subscriber " << name << " created\n";
    }
    ~Subscriber() {
        std::cout << "subscriber " << name << " destroyed\n";
    }
    void accept_notification(std::string message) {
        action(message);
    }
private:
    std::string name;
    std::function<void(std::string)> action;
};

class Publisher {
public:
    Publisher() {}
    void register_subscriber(Subscriber &sub) {
        subscribers.push_back(sub);
    }
    void unregister_subscriber(Subscriber &sub) {
        //std::erase_if(subscribers, [&sub](auto s) { return &s.get() == &sub; });        
    }
    void send_notification(std::string message) {
        for (auto sub : subscribers) {
            sub.get().accept_notification(message);
        }
    }
private:
    std::vector<std::reference_wrapper<Subscriber>> subscribers;
};

// https://compiler-explorer.com/z/s6hqzo3Kv

// publisher -> list of subscribers -weak-> subscriber
// subscriber -weak-> publisher

// shared_ptr (strong) -> control block -> object
// weak_ptr (weak) -> control block -> NULL
int main() {
    Publisher pub;
    {
        auto s1 = std::make_shared<Subscriber>(
            "s1",
            [](std::string message) {
                std::cout << "we received " << message << "\n";
            }
        ); // 1 strong, 0 weak
        pub.register_subscriber(*s1); // refcount 1 strong, 1 weak
        pub.send_notification("Hello");
        pub.unregister_subscriber(*s1); // !!!
        // refcount 0 strong, 1 weak
    }
    pub.send_notification("Some Message");
    pub.send_notification("Goodbye");
}