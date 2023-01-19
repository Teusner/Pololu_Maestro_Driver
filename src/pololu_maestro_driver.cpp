#include "pololu_maestro_driver/pololu_maestro_driver.hpp"

#include <iostream>
#include <memory>

PololuMaestroDriver::PololuMaestroDriver(std::string port, unsigned int baud_rate) : serial_(LibSerial::SerialPort(port)) {
        serial_.SetBaudRate(LibSerial::BaudRate::BAUD_115200);
    };

PololuMaestroDriver::~PololuMaestroDriver() {
    serial_.Close();
}

void PololuMaestroDriver::SetPosition(uint8_t channel, uint16_t position) {
    if (position >= min_channel_value_ && position <= max_channel_value_) {
        int32_t quarter_us = 4 * position;
        std::vector<uint8_t> command = {
            0x84, static_cast<uint8_t>(channel),
            static_cast<uint8_t>(quarter_us & 0x7F),
            static_cast<uint8_t>((quarter_us >> 7) & 0x7F)
        };
        serial_.Write(command);
    }
}

void PololuMaestroDriver::SetMultiplePositions(uint8_t n, uint8_t first_channel, uint16_t positions[]) {
    std::vector<uint8_t> command = { 0x9F, n, first_channel };
    for (uint8_t i=0; i<n; ++i) {
        int32_t quarter_us = 4 * positions[i];
        command.push_back(static_cast<uint8_t>(quarter_us & 0x7F));
        command.push_back(static_cast<uint8_t>((quarter_us >> 7) & 0x7F));
    }
    serial_.Write(command);
}

void PololuMaestroDriver::GetPosition(uint8_t channel, uint16_t &position) {
    // Requesting the position on the channel
    std::vector<uint8_t> command = { 0x90, channel };
    serial_.Write(command);

    // Reading data
    std::vector<uint8_t> response = { 0x00, 0x00 };
    serial_.Read(response, 2);
	position = response[0] + 256 * response[1];
}

void PololuMaestroDriver::SetVelocity(uint8_t channel, uint16_t speed) {
    std::vector<uint8_t> command = {
        0x87, channel,
        static_cast<uint8_t>(speed & 0x7F),
        static_cast<uint8_t>((speed >> 7) & 0x7F)
    };
    serial_.Write(command);
}

void PololuMaestroDriver::SetAcceleration(uint8_t channel, uint16_t acceleration) {
    std::vector<uint8_t> command = {
        0x89, channel,
        static_cast<uint8_t>(acceleration & 0x7F),
        static_cast<uint8_t>((acceleration >> 7) & 0x7F)
    };
    serial_.Write(command);
}
