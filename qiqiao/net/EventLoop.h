#ifndef QIQIAO_NET_EVENTLOOP_H
#define QIQIAO_NET_EVENTLOOP_H

#include <iostream>

#include <vector>
#include <cassert>
#include <poll.h>
namespace qiqiao{
namespace net {
	class Poller;
	class Channel;
	class EventLoop {
	public:
		EventLoop();
		~EventLoop() {}

		void loop();
		void quit() {quit_ = true;}
		void updateChannel(Channel *channel);
	
		typedef std::vector<Channel*> ChannelPtrVec;
	private:
		Poller *poller_;
		ChannelPtrVec activeChannels_;

		bool quit_;
	};
};
};

#endif
