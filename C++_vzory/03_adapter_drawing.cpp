#include <memory>
#include <iostream>

class Draw {
public:
    // draw line from the last position
    virtual void draw_line(int pixels, int degrees) = 0;
    virtual ~Draw() {}
    // 0 ... 359
    // 0 degrees = right
    // 90 degrees = up
};

class TestDraw : public Draw {
public:
    void draw_line(int pixels, int direction) override {
        std::cout << "Drawing line of " << pixels << " pixels at " << direction << " degrees.\n";
    }
};

// Interface + Liskov substitution principle
// 1) code (class Turtle)
// 2) documentation
//     - turtle starts oriented to the right
//     - turtle starts in the middle of the screen
// 3) assumptions
class Turtle {
public:
    virtual ~Turtle() {}
    virtual void forward(int steps) = 0;
    virtual void left(int degrees) = 0;
    virtual void right(int degrees) = 0;
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
    DrawAsTurtle(std::shared_ptr<Draw> draw) : draw(draw) {}
    void forward(int steps) override {
        draw->draw_line(steps * steps_per_pixel, direction);
    }
    void left(int degrees) override {
        direction = (direction + degrees) % 360;
    }
    void right(int degrees) override {
        direction = (direction + 360 - degrees) % 360;
    }
private:
    std::shared_ptr<Draw> draw;
    int direction = 0; // As the one for draw.
    int steps_per_pixel = 10;
};

// always remember the direction of the turtle
class TurtleAsDraw : public Draw {
public:
    TurtleAsDraw(std::shared_ptr<Turtle> turtle, int turtle_direction)
        : turtle(turtle), turtle_direction(turtle_direction) {}
    void draw_line(int pixels, int direction) override {
        // 0 ... 359
        int direction_change = (direction + 360 - turtle_direction) % 360;
        if (direction_change == 0) {
            // noop
        } else if (direction_change > 180) {
            turtle->right(360 - direction_change);
        } else {
            turtle->left(direction_change);
        }
        turtle->forward(pixels / steps_per_pixel);
        turtle_direction = direction; 
    }
private:
    std::shared_ptr<Turtle> turtle;
    int turtle_direction; // 0 ... 359
    int steps_per_pixel = 10;
};

int main3b() {
    /*draw->draw_line(30, 0); // 30 pixels right
    draw->draw_line(20, 90); // 20 pixels up*/
    //auto turtle = std::make_shared<TestTurtle>();

    //1st option - DrawAsTurtle
  //auto test_draw = std::make_shared<TestDraw>();
  //auto turtle = std::make_shared<DrawAsTurtle>(test_draw);

  //2nd option - TurtleAsDraw
    std::shared_ptr<Turtle> test_turtle = std::make_shared<TestTurtle>();
    std::shared_ptr<Draw> draw = std::make_shared<TurtleAsDraw>(test_turtle, 0);
    std::shared_ptr<Turtle> turtle = std::make_shared<DrawAsTurtle>(draw);

    // Consumer
    // draw->draw_line(19, 0);
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
}

// Configuration

