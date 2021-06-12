#include "Packet.hpp"  
	
Packet::Packet(const struct pcap_pkthdr* packetInfo, const u_char* stream) : 
    BytesStream(packetInfo->len), 
    _timeStamp(packetInfo->ts) 
{
    std::copy(stream, stream + _size, _stream.get());
}
	
Packet::~Packet()
{
	
}