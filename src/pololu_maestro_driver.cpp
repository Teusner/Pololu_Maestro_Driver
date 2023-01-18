#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <iostream>
#include <memory>

void PololuMaestroDriver::SetPosition(uint8_t channel, uint16_t position) {
    if (position >= min_channel_value_ && position <= max_channel_value_) {
        int32_t quarter_us = 4 * position;
        uint8_t command[4] = {
            0x84, static_cast<uint8_t>(channel),
            static_cast<uint8_t>(quarter_us & 0x7F),
            static_cast<uint8_t>((quarter_us >> 7) & 0x7F)
        };
        serial_->write(sizeof(command), command);
    }
}

void PololuMaestroDriver::SetMultiplePositions(uint8_t n, uint8_t first_channel, uint16_t positions[]) {
    auto command = std::make_unique<uint8_t[]>(2*n+3);
    command[0] = 0x9F;
    command[1] = n;
    command[2] = first_channel;
    for (uint8_t i=0; i<n; ++i) {
        int32_t quarter_us = 4 * positions[i];
        command[3+2*i] = static_cast<uint8_t>(quarter_us & 0x7F);
        command[4+2*i] = static_cast<uint8_t>((quarter_us >> 7) & 0x7F);
    }
    serial_->write(sizeof(command), command.get());
}

void PololuMaestroDriver::GetPosition(uint8_t channel, uint16_t &position) {
    // Requesting the position on the channel
    uint8_t command[2] = { 0x90, channel };
    serial_->write(sizeof(command), command);

    // Reading data
	uint8_t response[2] = { 0x00, 0x00 };
    serial_->read(sizeof(response), response);
	position = response[0] + 256 * response[1];
}

void PololuMaestroDriver::SetVelocity(uint8_t channel, uint16_t speed) {
    uint8_t command[4] = {
        0x87, channel,
        static_cast<uint8_t>(speed & 0x7F),
        static_cast<uint8_t>((speed >> 7) & 0x7F)
    };
    serial_->write(sizeof(command), command);
}

void PololuMaestroDriver::SetAcceleration(uint8_t channel, uint16_t acceleration) {
    uint8_t command[4] = {
        0x89, channel,
        static_cast<uint8_t>(acceleration & 0x7F),
        static_cast<uint8_t>((acceleration >> 7) & 0x7F)
    };
    serial_->write(sizeof(command), command);
}
