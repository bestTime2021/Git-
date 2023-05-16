#ifndef QIQIAO_NET_POLLER_H
#define QIQIAO_NET_POLLER_H

#include <vector>
#include <cassert>
#include <poll.h>
#include <map>

namespace qiqiao {
namespace net {
	class Channel;
	class EventLoop;

	class Poller {
	public:
		Poller(EventLoop* loop);
		~Poller(){}
		
		typedef std::vector<Channel*> ChannelPtrVec;
	public:
		void poll(ChannelPtrVec *activeChannels);
		void fillActiveChannels(int nready, ChannelPtrVec *activeChannels);

		void updateChannel(Channel* channel);
	
		typedef std::map<int, Channel*> ChannelMap;
		typedef std::vector<struct pollfd> PollfdVec;
	//private:
		ChannelMap channels_;
		PollfdVec pollfds_;
		EventLoop *ownerLoop_;
	};
};
};

#endif
