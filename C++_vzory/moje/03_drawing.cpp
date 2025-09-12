#include <iostream>
#include <string>
#include <memory>

namespace moje{

class Draw{
    public:
    virtual void draw_line(int pixels, int degress) = 0;
    virtual ~Draw() {};
    //00 .. 359
    // 0 degress = right
    // 90 degrees = up
};

class TestDraw : public Draw {
    public:
        void draw_line(int pixels, int direction) override {
        std::cout << "Drawing line of " << pixels << " pixels at " << direction << " degrees.\n";
    }
};

class Turtle {
    public:
        virtual ~Turtle() {}; // without it this could crash especially with more 
        virtual void forward(int steps)  = 0;
        virtual void left(int degrees) = 0;
        virtual void right(int degrees) = 0;   
    //Avoid following, there could be many unnecessary code.
    //protected:
    //    int direction; 
};

class TestTurtle : public Turtle {
    public:
        void forward(int steps) override {
        std::cout << "Moving forward " << steps << " steps.\n";
    }
    void left(int degrees) override {
        std::cout << "Turning left " << degrees << " degrees.\n";
    }
    void right(int degrees) override {
        std::cout << "Turning right " << degrees << " degrees.\n";
    }    
};

class DrawAsTurtle : public Turtle {
    public:
    DrawAsTurtle(std::shared_ptr<Draw> draw) : draw(draw), direction(0) {}
    
    void forward(int steps) override {
        if (steps < 0) {
            std::cout << "Error: Cannot move backward with negative steps.\n";
            return;
        }
        draw->draw_line(steps * steps_per_pixel, direction);
    }
    
    void left(int degrees) override {
        direction = (direction + degrees) % 360;
    }
    
    void right(int degrees) override {
        direction = (direction - degrees + 360) % 360;
    }    
    
    private:
        std::shared_ptr<Draw> draw;
        int direction; // Current direction in degrees
        int steps_per_pixel = 10; // Example conversion factor
};

class TurtleAsDraw : public Draw {
    public:
    TurtleAsDraw(std::shared_ptr<Turtle> turtle, int turtle_direction)
        : turtle(turtle), turtle_direction(turtle_direction) {}
    void draw_line(int pixels, int direction) override {
        int direction_change = (direction - turtle_direction + 360) % 360;
        turtle->left(direction_change);
        turtle->forward(pixels / steps_per_pixel);
        turtle_direction = direction;
    }
    private:
        std::shared_ptr<Turtle> turtle;
        int steps_per_pixel = 10; // Example conversion factor
        int turtle_direction = 0;
};


int main3() {
    
    /*draw->draw_line(30, 0); // 30 pixels right
    draw->draw_line(20, 90); // 20 pixels up*/
    //auto turtle = std::make_shared<TestTurtle>();
        
    //1st option - DrawAsTurtle
  //auto test_draw = std::make_shared<TestDraw>();
  //auto turtle = std::make_shared<DrawAsTurtle>(test_draw); //we need Adapter to implement Turtle interface  

    //2nd option - TurtleAsDraw
    auto test_turtle = std::make_shared<TestTurtle>();
    auto draw = std::make_shared<TurtleAsDraw>(test_turtle,0);
    auto turtle = std::make_shared<DrawAsTurtle>(draw);
    
//TODO does not provide same results - why?

    //Consumer
    //draw->draw_line(19, 0);
    turtle->forward(3);
    turtle->left(90);
    turtle->forward(2);
    turtle->right(45);
    turtle->forward(1);
    turtle->left(180);
    turtle->forward(1);
    turtle->left(181);
    turtle->forward(1);
    turtle->right(180);
    turtle->forward(1);

    return 0;

}
}