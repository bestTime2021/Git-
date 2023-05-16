#include "Channel.h"
#include "Poller.h"

using namespace qiqiao;
using namespace qiqiao::net;

Poller::Poller(EventLoop *loop):ownerLoop_(loop) {}

void Poller::poll(ChannelPtrVec *activeChannels) {
	assert(activeChannels != nullptr);
	int nready = ::poll(&*pollfds_.begin(), pollfds_.size(), 500);
	if (nready > 0) {
		fillActiveChannels(nready, activeChannels);
	}
}

void Poller::fillActiveChannels(int nready, ChannelPtrVec *activeChannels) {
	auto iter = pollfds_.begin();	
	while (iter != pollfds_.end() && nready > 0) {
		if (iter->revents > 0) {
			nready--;
			int fd = iter->fd;
			assert(channels_.find(fd) != channels_.end());
			Channel *channel = channels_[fd];
			channel->setRevent(iter->revents);
			activeChannels->push_back(channel);
		}
		++iter;
	}
}

void Poller::updateChannel(Channel *channel) {
	if (channel->index() < 0) {
		assert(channels_.find(channel->fd()) == channels_.end());
		struct pollfd pd;
		pd.fd = channel->fd();
		pd.events = channel->event();
		pd.revents = 0;

		channels_[pd.fd] = channel;
		pollfds_.push_back(pd);
		channel->setIndex(pollfds_.size() - 1);
	} else {
		assert(channels_.find(channel->fd()) != channels_.end());
		int idx = channel->index();
		assert(idx > -1 && idx < static_cast<int>(pollfds_.size()));
		struct pollfd &pd = pollfds_[idx];
		assert(pd.fd == channel->fd());
		pd.events = channel->event();
		pd.revents = 0;
		
	} 

	//FIXME
	for (auto item: pollfds_) {
		std::cout << item.fd << ' ';
	}
	std::cout << std::endl;
}
