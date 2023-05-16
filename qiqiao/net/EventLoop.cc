#include "EventLoop.h"
#include "Poller.h"
#include "Channel.h"

using namespace qiqiao;
using namespace qiqiao::net;

EventLoop::EventLoop()
	:poller_(new Poller(this)),
	quit_(false){
}

void EventLoop::loop() {
	while (!quit_) {
		activeChannels_.clear();
		poller_->poll(&activeChannels_);		
		auto iter = activeChannels_.begin();
		while (iter != activeChannels_.end()) {
			(*iter)->handleEvent();
			++iter;
		}
		//std::cout << "polling" << std::endl;
	}
}

void EventLoop::updateChannel(Channel *channel) {
	poller_->updateChannel(channel);
}

