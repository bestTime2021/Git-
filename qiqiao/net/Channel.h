#ifndef QIQIAO_NET_CHANNEL_H
#define QIQIAO_NET_CHANNEL_H

#include <iostream>
#include <poll.h>
#include <functional>

namespace qiqiao {
namespace net {
	class EventLoop;
	class Channel {
		typedef std::function<void()> ReadCallback;
	public:
		Channel(EventLoop *loop, int fd);
		~Channel(){}
	public:
		int fd() {
			return fd_;
		}
		int event() {
			return events_;
		}
		int index() {
			return index_;
		}
		void setRevent(int revent) {
			revents_ = revent;
		}
		void setIndex(int idx) {
			index_ = idx;
		}
		void setReadCallback(const ReadCallback &cb) {
			readCallback_ = cb;
		}


		void handleEvent();
		void update();
		void enableReading();
	
	private:
		int fd_;
		int events_;
		int revents_;
		int index_;
		EventLoop *ownerLoop_;

		ReadCallback readCallback_;
	};
};
};

#endif
