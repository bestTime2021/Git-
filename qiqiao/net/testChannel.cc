#include <iostream>
#include "Channel.h"
using namespace qiqiao::net;

void ReadableNote() {
	std::cout << "It is readable now.\n";
}
int main() {
	Channel channel(nullptr, 3);
	channel.setRevent(POLLIN);
	channel.setReadCallback(std::bind(ReadableNote));
	channel.handleEvent();
}
