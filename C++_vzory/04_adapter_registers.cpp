#include <memory>
#include <iostream>
#include <cstdint>

//Adapter example
//Also Decorator pattern
class Register {
public:
    virtual void set_value(int32_t new_value) = 0;
    virtual int32_t get_value() = 0;
};

//It simplifies any aceess to register
//But it is not Fasade
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

class LogDecorator : public Register {
    public:
    LogDecorator(Register &target) : target(target) {}
    void set_value(int32_t new_value) override {
        std::cout << "Setting value from " << target.get_value() << " to " << new_value << std::endl;
        target.set_value(new_value);
    }

    int32_t get_value() override {
        std::cout << "Getting value " << target.get_value() << std::endl;
        return target.get_value();
    }

private:
    Register &target;
};

// Configuration
// Assembly of different pieces together
/*
int DecoratorExample1() {
    FakeRegister fake_reg;
    LogDecorator log_reg(fake_reg);
    reg->set_value(0xaa);    
    std::cout << "value = " << reg->get_value() << std::endl;
    RegisterBits bits(*reg);
    std::cout << "bit = \n" << bits.get_bit(7) << std::endl;    
}*/

int adapter_decorator_example() {
    bool conf_logging = true;
    FakeRegister fake_reg;//alloc
    Register *reg = &fake_reg; 

    LogDecorator log_reg(fake_reg); // alloc
    if (conf_logging) {
        reg = &log_reg;
    }

    reg->set_value(0xaa);
    RegisterBits bits(*reg);
    std::cout << "bit = " << bits.get_bit(7) << std::endl;    
}

// Configuration

