#include <sys/timerfd.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "EventLoop.h"
#include "Channel.h"

static qiqiao::net::EventLoop *g_loop;
void timeoutCallback() {
	std::cout << "timeout" << std::endl;
	g_loop->quit();
}

int main() {
	qiqiao::net::EventLoop loop;
	g_loop = &loop;

	int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
	qiqiao::net::Channel channel(&loop, timerfd);
	channel.setReadCallback(timeoutCallback);
	channel.enableReading();

	struct itimerspec howlong;
	bzero(&howlong, sizeof(howlong));
	howlong.it_value.tv_sec = 5;
	::timerfd_settime(timerfd, 0, &howlong, NULL);
	loop.loop();
}
