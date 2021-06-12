#ifndef PACKET_H
#define PACKET_H

#include "Types/BytesStream.hpp"
#include <pcap.h>
	
class Packet : public BytesStream
{
private:
	struct timeval _timeStamp;    	/* time stamp */
public:

	Packet(const struct pcap_pkthdr* packetInfo, const u_char* stream);
	~Packet();

};
#endif