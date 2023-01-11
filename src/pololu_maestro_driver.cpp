#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <iostream>

void PololuMaestroDriver::SetPosition(unsigned int channel, unsigned short position) {
    if (position >= min_channel_value_ && position <= max_channel_value_) {
        unsigned char command[4] = {
            0x84, static_cast<unsigned char>(channel),
            static_cast<unsigned char>(4 * position & 0x7F),
            static_cast<unsigned char>(((4 * position) >> 7) & 0x7F)
        };
	std::cout << channel << " " <<  4*position << std::endl;
        serial_->write(sizeof(command), command);
    }
}

void PololuMaestroDriver::GetPosition(unsigned int channel, unsigned short &position) {
    // Requesting the position on the channel
    unsigned char command[2] = { 0x90, static_cast<unsigned char>(channel) };
    serial_->write(sizeof(command), command);

    // Reading data
    unsigned int timeoutMillis = 100;
	unsigned char response[2] = { 0x00, 0x00 };
    serial_->read(sizeof(response), response, 100);
	position = response[0] + 256*response[1];
}

void PololuMaestroDriver::SetVelocity(unsigned int channel, unsigned short speed) {
    unsigned char command[4] = {
        0x87, static_cast<unsigned char>(channel),
        static_cast<unsigned char>(speed & 0x7F),
        static_cast<unsigned char>((speed >> 7) & 0x7F)
    };
    serial_->write(sizeof(command), command);
}

void PololuMaestroDriver::SetAcceleration(unsigned int channel, unsigned short acceleration) {
    unsigned char command[4] = {
        0x89, static_cast<unsigned char>(channel),
        static_cast<unsigned char>(acceleration & 0x7F),
        static_cast<unsigned char>((acceleration >> 7) & 0x7F)
    };
    serial_->write(sizeof(command), command);
}
