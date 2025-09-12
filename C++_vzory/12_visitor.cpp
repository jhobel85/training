#include <memory>
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>

// exp = const | var | (exp + exp) | (exp * exp)
// 1
// (1 + 2)
// (1 + 2) + 1
// a

// https://compiler-explorer.com/z/3foGsxKz1

class Cst;
class Sum;

class Visitor {
public:
    virtual void visit(Cst &cst) = 0;
    virtual void visit(Sum &sum) = 0;
};

class Exp {
public:
    virtual void accept(Visitor &visitor) = 0;
};

class Cst : public Exp {
public:
    Cst(int value) : value(value) {}
    void accept(Visitor &visitor) { visitor.visit(*this); /* Cst */ };
    int value;
};

class Sum : public Exp {
public:
    Sum(Exp &left, Exp &right) : left(left), right(right) {}
    void accept(Visitor &visitor) { visitor.visit(*this); /* Sum */ };
    Exp &left;
    Exp &right;
};

// Visitor Implementations

class ToString : public Visitor {
public:
    void visit(Cst &cst) override {
        std::ostringstream oss;
        oss << cst.value;
        result = oss.str();
    }
    void visit(Sum &sum) override {
        sum.left.accept(*this);
        std::string left = result;
        sum.right.accept(*this);
        std::string right = result;
        result = "(" + left + " + " + right + ")";
    }
    std::string execute(Exp &exp) {
        exp.accept(*this);
        return result;
    }
private:
    std::string result;
};
    
class Evaluate : public Visitor {
public:
    void visit(Cst &cst) override {
        result = cst.value;
    }
    void visit(Sum &sum) override {
        sum.left.accept(*this);
        int left = result;
        sum.right.accept(*this);
        int right = result;
        result = left + right;
    }
    int execute(Exp &exp) {
        exp.accept(*this);
        return result;
    }
private:
    int result;
};
    
int main() {
    Cst a(5);
    Cst b(7);
    Sum c(a, b); // a + b
    Sum d(c, c);

    std::cout << ToString().execute(d) << std::endl;
    std::cout << Evaluate().execute(d) << std::endl;
}