#pragma once

#include <string>
#include <iostream>

#include <rtac_asio/Stream.h>
#include <rtac_asio/SerialStream.h>


class PololuMaestroDriver {

    public:
        /**
        * Constructor.
        * \param port device name, example "/dev/ttyUSB0" or "COM4"
        * \param baud_rate communication speed, example 9600 or 115200
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        PololuMaestroDriver(std::string port, unsigned int baud_rate) : serial_(rtac::asio::Stream::CreateSerial(port, baud_rate)) {
            serial_->flush();
        };

        /**
        * Set position on the channel
        * \param unsigned int channel: pololu maestro channel
        * \param unsigned short position: duty cycle value in range
        *  [1000; 2000] us applied on the channel
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        void SetPosition(uint8_t channel, uint_8 position);

        /**
        * Get the current position on the channel
        * \param unsigned int channel: pololu maestro channel
        * \param unsigned short &position: current duty cycle value in range
        *  [1000; 2000] us
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        void GetPosition(uint8_t channel, unsigned short &position);

        /**
        * Set velocity on the channel
        * \param unsigned int channel: pololu maestro channel
        * \param unsigned short velocity: velocity of the duty cycle
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        void SetVelocity(uint8_t channel, unsigned short velocity);

        /**
        * Set acceleration on the channel
        * \param unsigned int channel: pololu maestro channel
        * \param unsigned short acceleration: acceleration of the duty cycle
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        void SetAcceleration(uint8_t channel, unsigned short acceleration);

    private:
        // Pointer to the serial stream
        rtac::asio::Stream::Ptr serial_;

        // Minimal channel value in quarter of us
        unsigned short min_channel_value_ = 1000;

        // Maximal channel value in quarter of us
        unsigned short max_channel_value_ = 2000;
};