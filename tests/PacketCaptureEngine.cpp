#include <pcap.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "DevicesContainer.hpp"
#include "TimeAdapter.hpp"

void printBytesOfPacket(const std::shared_ptr<Packet> packet)
{
    for (uint32_t i = 0; i < packet->byteStreamSize(); ++i)
    {
        if (i % 16 == 0)
        {
            std::cout << std::endl;
        }
        else if (i % 8 == 0)
        {
            std::cout << "  ";
        }
        std::cout << std::setfill('0') << std::setw(2) << std::hex << +(*packet)[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc,char **argv)
{ 
    Device device; 
    std::string deviceName;
    if (argc > 1)
    {
        deviceName = argv[1];
    }
    
    /* Print all devices and their addresses */
    DevicesContainer devicesContainer = DevicesContainer::instance();

    for (const auto& dev : devicesContainer)
    {
        std::cout << dev << std::endl;
    }

    /* grab a device to peak into... */
    try
    {
        if (argc > 1)
        {
            device = devicesContainer.getDeviceByName(argv[1]);
        }
        else
        {
            device = devicesContainer[0];
        }
        
        /* open device for reading */
        device.open();

        /* printing */
        std::cout << "Main device is " << device.getName() << std::endl;
        std::cout << "Description: " << device.getDescription() << std::endl;
        std::cout << "Addresses: " << device.toString() << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }    

    device.startCapture(3);

    std::shared_ptr<Packet> packet;
    while((packet = device.popPacket()) != nullptr)
    {
        /* handle packet */
        printBytesOfPacket(packet);
    }

    device.close();
    return 0;
}

