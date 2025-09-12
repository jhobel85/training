
//#include <print>
#include <memory>
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>

class Register;

class RegisterState {
public:
    virtual void set_value(Register &reg, int32_t value) {}
    virtual int32_t get_value(Register &reg) { return 0xffff; }
    virtual void lock(Register &reg) {}
    virtual void unlock(Register &reg) {}
};

class UnlockedState : public RegisterState {
public:
    void set_value(Register &reg, int32_t value) override;
    int32_t get_value(Register &reg) override;
    void lock(Register &reg) override;
};

// unlocked_state is a shared instance, not a strict singleton
// It allows someone from creating another UnlockedState instance elsewhere in the code, so it is not a true singleton (which would prevent multiple instances).
// it is NOT lazy (create when it is first used) initialization (like in Singleton pattern)
// but it will not create instance in constructor of Register (static initialization order fiasco)
std::shared_ptr<UnlockedState> unlocked_state = std::make_shared<UnlockedState>();
/*
make_shared = allocate space for UnlockedState
+ allocate space for the control block (reference counting)
+ (initialize control block)
+ (intitialize the UnlockedState -> call the constructor)

after static initialization is done
----------
initialization is done before the main function is called
so this is tricky because initialization does not happen immediately -> Rather to avoid it.
In C++ initialization is more complex.
-> Singleton can solve this problem.
*/

class LockedState : public RegisterState {
public:
    void unlock(Register &reg) override;
};

std::shared_ptr<LockedState> locked_state = std::make_shared<LockedState>();

class Register {
public:
    Register() : state(unlocked_state) {}
    void set_value(int32_t value) { state->set_value(*this, value); }
    int32_t get_value() { return state->get_value(*this); }
    void lock() { state->lock(*this); }
    void unlock() { state->unlock(*this); }
private:
    // Overhead of refcounting
    std::shared_ptr<RegisterState> state;
    int32_t value = 0xaaaa;
    friend UnlockedState;
    friend LockedState;
};

void UnlockedState::set_value(Register &reg, int32_t value) {
    reg.value = value;
}
int32_t UnlockedState::get_value(Register &reg) {
    return reg.value;
}
void UnlockedState::lock(Register &reg) {
    reg.state = locked_state;
};

void LockedState::unlock(Register &reg) {
    reg.state = unlocked_state;
};

int lock_unclock() {
    Register reg;
    reg.set_value(5);
    reg.lock();
    reg.set_value(7); // ???
    reg.unlock();
    //std::print("{:04x}\n", reg.get_value()); // 5
    return 0;
}