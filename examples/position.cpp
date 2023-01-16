#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>


int main() {
    PololuMaestroDriver driver("/dev/POLOLU", 115200);

    for (uint8_t channel=1; channel<=3; ++channel) {
        std::vector<uint16_t> values = {
            1000, 2000, 1500
        };

        for (const auto &v: values) {
            std::cout << "Channel " << int(channel) << "\t" << v << "us" << std::endl;
            driver.SetPosition(channel, v);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}
