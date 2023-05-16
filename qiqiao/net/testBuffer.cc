#include "Buffer.cc"
#include <iostream>
#include <cassert>

#include <cstring>
using namespace qiqiao::net;

int main(int argc, char **argv) {
	assert(argc >= 2);
	char *str = argv[1];
	qiqiao::net::Buffer buf;

	int saveErrno;
	buf.readFd(0, &saveErrno);
//	buf.retrieve(5);
	buf.printBuffer();
}
