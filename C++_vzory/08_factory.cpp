//#include <print>
#include <memory>
#include <iostream>
#include <cstdint>
#include <vector>
#include <functional>
#include <string>

/*
Factory - what is it good for?

  - Creation of multiple objects by one method.
  - Type based on parameter, but all of them provide the same interface.

  - Input: Description (std::string, JSON, description object)
  - Output: Behavior for that specific description

  // sqlite://...
  // pgsql://
  // { "driver": "sqlite", "filename": "..." }
*/

class Device {
public:
    Device(std::vector<std::string> compatible) : compatible(compatible) {}
    std::vector<std::string> compatible;
};

class Driver {
public:
    virtual ~Driver() {}
    virtual std::string name() = 0;
};

class ImxDriver : public Driver {
public:
    ImxDriver(Device &dev) {
        std::cout << "IMX driver constructor\n";
        for (const auto& c : dev.compatible) {
            if (c == compatible) {
                std::cout << "Yes, we are compatible!\n";
                break;
            }
        }
    }
    std::string name() override { return "IMX device Driver"; }
private:
    std::string compatible = "fsl,imx28-auart";
};

class OtherDriver : public Driver {
public:
    OtherDriver(Device &dev) {
        std::cout << "Other driver constructor\n";
        for (const auto& c : dev.compatible) {
            if (c == compatible) {
                std::cout << "Yes, we are compatible!\n";
                break;
            }
        }
    }
    std::string name() override { return "Other device Driver"; }
private:
    std::string compatible = "other,stuff";
};

class NullDriver : public Driver {
public:
    NullDriver(Device &dev) {}
    std::string name() override { return "Null driver for unknown devices"; }
};

std::unique_ptr<Driver> probe_driver(Device &dev) {
    for (const auto& c : dev.compatible) {
        if (c == "fsl,imx28-auart") 
            return std::make_unique<ImxDriver>(dev);
        else if (c == "other,stuff") {
            return std::make_unique<OtherDriver>(dev);
        }
    }
    return std::make_unique<NullDriver>(dev);
    //return nullptr; // will cause segmentation error in future.
}

int factoryMethod() {
    std::vector<Device> devices;
    devices.push_back(Device({"fsl,imx28-auart", "fsl,imx23-auart"}));
    devices.push_back(Device({"other,stuff"}));
    devices.push_back(Device({"something,unknown"}));
    devices.push_back(Device({"something,other-unknown"}));

    std::vector<std::shared_ptr<Driver>> drivers;
    for (auto &dev : devices) {
        // shared_ptr<Driver> <-- unqiue_ptr<Driver> 
        //push back does not work with unique pointer -> compile error -> we must explicitly specify it as shared_ptr
        //auto drv = probe_driver(dev);
        std::shared_ptr<Driver> drv = probe_driver(dev);
        drivers.push_back(drv);
        std::cout << "driver name: "<< drv->name() << std::endl;
    }    
}