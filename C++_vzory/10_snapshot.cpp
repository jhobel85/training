#include <memory>
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <iomanip>
// https://compiler-explorer.com/z/MeE6T7shc // Command

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

class Snapshot {
public:
    Snapshot(Register &reg) {
        value = reg.get_value();
        std::cout << "new snapshot: " << std::hex << std::uppercase << std::setw(8) << std::setfill('0') << value << std::dec << std::endl;
    }
    void restore(Register &reg) {
        reg.set_value(value);
    }
private:
    uint32_t value;
};

class Editor {
public:
    Editor(Register &reg) : reg(reg) {}
    void undo() {
        std::cout << "-- undo start --\n";
        snapshots.back().restore(reg);
        snapshots.pop_back(); // !!!
        std::cout << "-- undo end --\n";
    }
    void set_value(uint32_t value) {
        save_snapshot();
        reg.set_value(value);
    }
    void set_bit(int idx, bool value) {
        uint32_t previous_value = reg.get_value();
        save_snapshot();
        reg.set_value((previous_value & ~(1 << idx)) | (value ? 1 << idx : 0));
    }
private:
    void save_snapshot() {
        snapshots.push_back(Snapshot(reg));
    }
    Register &reg;
    std::vector<Snapshot> snapshots;
};

// https://compiler-explorer.com/z/7aWs749sv

// Undo

int main() {
    FakeRegister reg;
    reg.set_value(0xaaaaaaaa);
    Editor editor(reg);
    editor.set_value(0xffff0000);
    editor.set_bit(1, true);
    editor.set_bit(2, true);
    editor.set_bit(3, true);
    editor.set_bit(4, true);
    editor.undo();
    editor.undo();
    editor.undo();
    editor.undo();
    editor.undo();
}