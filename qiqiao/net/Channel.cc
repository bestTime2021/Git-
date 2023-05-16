#include "Channel.h"
#include "EventLoop.h"
using namespace qiqiao;
using namespace qiqiao::net;
Channel::Channel(EventLoop *loop, int fd)
	:ownerLoop_(loop), 
	fd_(fd), 
	events_(POLLIN), //FIXME
	revents_(0), 
	index_(-1) {
	}

void Channel::handleEvent() {
	if (revents_ & POLLIN) {
		readCallback_();
	}
}

void Channel::update() {
	ownerLoop_->updateChannel(this);
}

void Channel::enableReading() {
	events_ |= (POLLIN | POLLPRI);
	update();
}
