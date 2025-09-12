#include <memory>
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <iomanip>

class Register {
public:
    virtual void set_value(uint32_t new_value) = 0;
    virtual uint32_t get_value() = 0;
};

class FakeRegister : public Register {
public:
    void set_value(uint32_t new_value) override {
        std::cout << "set_value(0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << new_value << ")\n" << std::dec;
        value = new_value;
    }
    uint32_t get_value() override {
        std::cout << "get_value() -> 0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << value << ")\n" << std::dec;
        return value;
    }
private:
    uint32_t value = 0x00000000;
};

// Editor
// https://compiler-explorer.com/z/KfKq3Txe6

class Command {
public:
    virtual void apply(Register &reg) = 0;
};

class Editor {
public:
    Editor(Register &reg) : reg(reg) {
        initial_value = reg.get_value();
    }
    void execute(std::shared_ptr<Command> cmd) {
        cmd->apply(reg);
        history.push_back(cmd);
    }
    void undo() {
        std::cout << "-- undo start --\n";
        history.pop_back(); // !!!
        replay_history();
        std::cout << "-- undo end --\n";
    }
private:
    void replay_history() {
        reg.set_value(initial_value);
        for (auto &cmd : history) {
            cmd->apply(reg);
        }
    }
    Register &reg;
    std::vector<std::shared_ptr<Command>> history;
    uint32_t initial_value;
};

class SetValue : public Command {
public:
    SetValue(uint32_t value) : value(value) {}
    void apply(Register &reg) override{
        reg.set_value(value);
    }
private:
    uint32_t value;
};

class SetBit : public Command {
public:
    SetBit(int idx, bool value) : idx(idx), value(value) {}
    void apply(Register &reg) override {
        uint32_t previous_value = reg.get_value();
        reg.set_value((previous_value & ~(1 << idx)) | (value ? 1 << idx : 0));
    }
private:
    int idx;
    bool value;
};

// Undo

int main() {
    FakeRegister reg;
    reg.set_value(0xaaaaaaaa);
    Editor editor(reg);
    editor.execute(std::make_shared<SetValue>(0xffff0000));
    editor.execute(std::make_shared<SetBit>(1, true));
    editor.execute(std::make_shared<SetBit>(2, true));
    editor.execute(std::make_shared<SetBit>(3, true));
    editor.execute(std::make_shared<SetBit>(4, true));
    editor.undo();
    editor.undo();
    editor.undo();
    editor.undo();
    editor.undo(); // pop_back must be handled otherise undefined behavior
}