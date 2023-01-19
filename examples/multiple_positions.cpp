#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>


int main() {
    PololuMaestroDriver driver("/dev/POLOLU", 115200);

    std::vector<uint16_t> values = {
        1000, 2000, 1500
    };

    for (std::size_t i=0; i<3; ++i) {
        std::rotate(values.begin(), values.begin()+1, values.end());
        driver.SetMultiplePositions(3, 1, &values[0]);
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::size_t c = 0;
        for (const auto v: values) {
            std::cout << "Channel " << ++c << " " << v << std::endl;
        }
    }
}
