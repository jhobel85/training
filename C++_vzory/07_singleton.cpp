#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>

// Advice: Don't use Singleton or globals when you don't need to.

// When do we not want to have more instances than one?

//   - One process in an operating system.
//       - Synchronization of file system access
//   - Some hardware.

// One resource that we have to manage -> singleton.

// send_message(PID, data)

// Global variable initialized before main.
// Lazy-initialized singleton.

class Singleton {
public:
    static Singleton *get();
private:
    Singleton() = default;
    // friend Singleton *get_singleton();
};

Singleton *Singleton::get() {
    static Singleton *instance = nullptr;

    if (instance == nullptr) {
        instance = new Singleton();
    }

    return instance;
}

int main() {
    Singleton *s1 = Singleton::get();
    Singleton *s2 = Singleton::get();
    std::cout << (intptr_t)s1 << std::dec << "\n";
    std::cout << (intptr_t)s2 << std::dec << "\n";    
    //Singleton s3;
}