#include <memory>
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>

class Register {
public:
    virtual void set_value(uint32_t new_value) = 0;
    virtual uint32_t get_value() = 0;
};

// https://compiler-explorer.com/z/oMjj46e1E

class FakeRegister : public Register {
public:
    void set_value(uint32_t new_value) override {
        std::cout << "set_value(0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << new_value << ")\n" << std::dec;
        value = new_value;
    }
    uint32_t get_value() override { return value; }
private:
    uint32_t value = 0x0000;
};

class RegisterBits {
public:
    RegisterBits(Register &reg) : reg(reg) {}
    bool get_bit(int idx) {
        return (reg.get_value() & (1 << idx)) != 0;
    }
    void set_bit(int idx, bool value) {
        reg.set_value((reg.get_value() & ~(1 << idx)) | (value ? 1 << idx : 0));
    }
private:
    Register &reg;
};

class SetBit {
public:
    SetBit(int idx, bool value) : idx(idx), value(value) {}

    void apply(Register &reg) {
        RegisterBits bits(reg);
        previous_value = bits.get_bit(idx);
        bits.set_bit(idx, value);
    }

    void unapply(Register &reg) {
        RegisterBits bits(reg);
        bits.set_bit(idx, previous_value);
    }

    bool getValue() const {
        return value;
    }

private:
    int idx;
    bool value;
    bool previous_value; 
};



int exampleUndoWithoutCommandPattern() {
    std::vector<std::shared_ptr<Command>> program;
    program.push_back(std::make_shared<SetValue>(0xffff0000));
    program.push_back(std::make_shared<SetBit>(1, true));
    program.push_back(std::make_shared<SetBit>(2, true));
    program.push_back(std::make_shared<SetBit>(3, true));
    program.push_back(std::make_shared<SetBit>(4, true));
    // Simulation
    for (auto &cmd : program) {
        cmd->apply(reg);
    }

    // Undo last command
    program.back()->unapply(reg);
    program.pop_back();    
    

}


int exampleWithoutPattern() {
    FakeRegister reg;
    RegisterBits bits(reg);
    bits.set_bit(1, true);
    bits.set_bit(0, true);
    bits.set_bit(31, true);
    bits.set_bit(1, false);
    //bits.set_bit(32, false); // automatic conversion and start from 0 again. What would be different if we use unsigned int?

}