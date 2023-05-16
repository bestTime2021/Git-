#include <iostream>
#include "Poller.cc"
int main() {
	Poller poller(nullptr);
	Channel channel(11);
	Channel channel2(12);
	poller.updateChannel(&channel);
	poller.updateChannel(&channel2);

	std::cout << poller.channels_[11] << ' ' << poller.pollfds_[0].fd << std::endl;
	std::cout << poller.channels_[12] << ' ' << poller.pollfds_[1].fd << std::endl;
}
