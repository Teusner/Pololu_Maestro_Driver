#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

int i=0;
uint8_t response[2] = { 0x00, 0x00 };

void g(const boost::system::error_code err, std::size_t n) {
}
void f(rtac::asio::Stream::Ptr serial_, const boost::system::error_code err, std::size_t n) {
	uint8_t command[2] = { 0x90, 0 };
    	serial_->async_write(sizeof(command), command, g);
	
        // Reading data
	serial_->async_read(sizeof(response), response, std::bind(f, serial_, std::placeholders::_1, std::placeholders::_2));
	uint16_t position = response[0] + 256 * response[1];
	
	std::cout << ++i << " Got " << position << std::endl << std::flush;
}



int main() {
    PololuMaestroDriver driver("/dev/POLOLU", 115200);
    
    uint16_t position;
    for (int i=0; i<10000; ++i) {
   for (uint8_t channel=1; channel<=3; ++channel) {
       driver.GetPosition(channel, position);
   	std::cout << i << " Channel " << channel << " position " << position << std::endl << std::flush;
   }
   std::this_thread::sleep_for(10ms);
    }
   //f(driver.serial(), boost::system::error_code(), 0);
   getchar();
   return 0;
}
