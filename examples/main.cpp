#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>


int main() {
    PololuMaestroDriver driver("/dev/POLOLU", 9600);

    for (unsigned int channel=1; channel<=3; ++channel) {
        std::vector<std::pair<unsigned short, std::string>> pairs = {
            {1000, "min"},
            {2000, "max"},
            {1500, "neutral"}
        };

        for (const auto &p: pairs) {
            std::cout << "Channel " << channel << " " << p.second << " (" << p.first << ")us" << std::endl;
            driver.SetPosition(channel, p.first);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}