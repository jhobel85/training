//#include <memory>
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>

class Register {
public:
    virtual void set_value(int32_t new_value) = 0;
    virtual int32_t get_value() = 0;
};

class FakeRegister : public Register {
public:
    // override of interface methods
    void set_value(int32_t new_value) override { value = new_value; }
    int32_t get_value() override { return value; }
private:
    int32_t value = 0;
};

class RegisterBits {
public:
    RegisterBits(Register &reg) : reg(reg) {}
    bool get_bit(int idx) {
        return (reg.get_value() & (1 << idx)) != 0;
    }
private:
    Register &reg;
};

// https://compiler-explorer.com/z/fojx74hsM

class LogDecorator : public Register {
public:
    LogDecorator(std::shared_ptr<Register> target) : target(target) {}
    void set_value(int32_t new_value) override {
        //std::cout << "setting value from 0x" << std::hex << std::setw(4) << std::setfill('0') << target->get_value()
                  //<< " to 0x" << std::setw(4) << std::setfill('0') << new_value << std::dec << "\n";
        target->set_value(new_value);
    }
    int32_t get_value() override {
        int32_t value = target->get_value();
        //std::cout << "getting value 0x" << std::hex << std::setw(4) << std::setfill('0') << value << std::dec << "\n";
        return value;
    }
private:
    std::shared_ptr<Register> target;
};

// Adding side effect
// Filtering decorator
// Fixing data decorator

// Configuration
// Assembly of different pieces together

// https://compiler-explorer.com/z/qfeobdvba

class CollectDecorator : public Register {
public:
    CollectDecorator(std::shared_ptr<Register> target,
            std::function<void(int32_t)> output)
        : target(target), new_values(output) {}
    void set_value(int32_t new_value) override {
        new_values(new_value);
        target->set_value(new_value);
    }
    int32_t get_value() override {
        return target->get_value();
    }
private:
    std::shared_ptr<Register> target;
    std::function<void(int32_t)> new_values;
};

int decorator() {
    bool conf_logging = true;
    std::shared_ptr<Register> reg = std::make_shared<FakeRegister>();
    if (conf_logging) { reg = std::make_shared<LogDecorator>(reg); }

    std::vector<int32_t> output;
    auto add_to_output = [&output](int32_t new_value) {
        output.push_back(new_value);
    }; // ptr to function + ptr to &output // 16 bytes
    reg = std::make_shared<CollectDecorator>(reg, add_to_output); // ref to output
    
    reg->set_value(0xaa);
    reg->set_value(0xab);
    reg->set_value(0xac);
    RegisterBits bits(*reg);
    std::cout << "bit = " << bits.get_bit(7) << "\n";

    std::cout << "values:\n";
    for (const int32_t value : output) {
        //std::cout << "  " << std::hex << std::setw(4) << std::setfill('0') << value << std::dec << "\n";
    }
}