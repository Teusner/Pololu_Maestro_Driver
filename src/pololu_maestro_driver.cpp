#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <iostream>

void PololuMaestroDriver::SetPosition(uint8_t channel, unsigned short position) {
    if (position >= min_channel_value_ && position <= max_channel_value_) {
        uint8_t command[4] = {
            0x84, channel,
            static_cast<uint8_t>(4 * position & 0x7F),
            static_cast<uint8_t>(((4 * position) >> 7) & 0x7F)
        };
	std::cout << channel << " " <<  4*position << std::endl;
        serial_->write(sizeof(command), command);
    }
}

void PololuMaestroDriver::GetPosition(uint8_t channel, unsigned short &position) {
    // Requesting the position on the channel
    uint8_t command[2] = { 0x90, channel };
    serial_->write(sizeof(command), command);

    // Reading data
    unsigned int timeoutMillis = 100;
	uint8_t response[2] = { 0x00, 0x00 };
    serial_->read(sizeof(response), response, 100);
	position = response[0] + 256 * response[1];
}

void PololuMaestroDriver::SetVelocity(uint8_t channel, unsigned short speed) {
    uint8_t command[4] = {
        0x87, channel,
        static_cast<uint8_t>(speed & 0x7F),
        static_cast<uint8_t>((speed >> 7) & 0x7F)
    };
    serial_->write(sizeof(command), command);
}

void PololuMaestroDriver::SetAcceleration(uint8_t channel, unsigned short acceleration) {
    uint8_t command[4] = {
        0x89, channel,
        static_cast<uint8_t>(acceleration & 0x7F),
        static_cast<uint8_t>((acceleration >> 7) & 0x7F)
    };
    serial_->write(sizeof(command), command);
}
