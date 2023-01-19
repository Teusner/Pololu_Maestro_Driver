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
            serial_->start();
            serial_->flush();
	    serial_->enable_io_dump("rx", "tx");
	};
	
	auto serial() {return serial_;}

        /**
        * Set position on the channel
        * \param uint8_t int channel: pololu maestro channel
        * \param int32_t position: duty cycle value in range
        *  [1000; 2000] us applied on the channel
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        void SetPosition(uint8_t channel, uint16_t position);

        /**
        * Set multiple positions on the channel (Mini Maestro 12, 18, and 24 only)
        * \param unsigned int n: number of channels
        * \param uint8_t first_channel: first channel number channel
        * \param int32_t* positions: position to each channel starting from first_channel
        * in range [100; 200] us applied on the consecutive channels
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        void SetMultiplePositions(uint8_t n, uint8_t first_channel, uint16_t positions[]);

        /**
        * Get the current position on the channel
        * \param unsigned int channel: pololu maestro channel
        * \param unsigned short &position: current duty cycle value in range
        *  [1000; 2000] us
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        void GetPosition(uint8_t channel, uint16_t &position);

        /**
        * Set velocity on the channel
        * \param unsigned int channel: pololu maestro channel
        * \param unsigned short velocity: velocity of the duty cycle
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        void SetVelocity(uint8_t channel, uint16_t velocity);

        /**
        * Set acceleration on the channel
        * \param unsigned int channel: pololu maestro channel
        * \param unsigned short acceleration: acceleration of the duty cycle
        * \throws boost::system::system_error if cannot open the
        * serial device
        */
        void SetAcceleration(uint8_t channel, uint16_t acceleration);

    private:
        // Pointer to the serial stream
        rtac::asio::Stream::Ptr serial_;

        // Minimal channel value in quarter of us
        unsigned short min_channel_value_ = 1000;

        // Maximal channel value in quarter of us
        unsigned short max_channel_value_ = 2000;
};
