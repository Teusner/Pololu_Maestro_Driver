#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>


int main() {
    PololuMaestroDriver driver("/dev/POLOLU", 115200);
    std::this_thread::sleep_for(std::chrono::seconds(10));
    
    uint8_t channel=0;
    std::chrono::seconds delay(1);

    std::cout << "Going forward!" << std::endl;
    for (uint16_t value=1500; value<=2000; ++channel) {
        std::cout << "Setting value " << value << "us" << std::endl;
        driver.SetPosition(channel, value);
        std::this_thread::sleep_for(delay);
    }

    std::cout << "Going backward!" << std::endl;
    for (uint16_t value=1500; value>=1000; --channel) {
        std::cout << "Setting value " << value << "us" << std::endl;
        driver.SetPosition(channel, value);
        std::this_thread::sleep_for(delay);
    }
}
