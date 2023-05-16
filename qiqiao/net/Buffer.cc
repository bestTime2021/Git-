#include "Buffer.h"
#include <sys/uio.h>
#include <cerrno>

using namespace qiqiao;
using namespace qiqiao::net;

const size_t Buffer::kInitSize;
const size_t Buffer::kCheapPrepend;

size_t Buffer::readFd(int fd, int *saveErrno) {
	char extraBuf[65535];
	struct iovec vec[2];	
	vec[0].iov_base = begin() + writeIndex_;
	vec[0].iov_len = writableBytes();
	vec[1].iov_base = extraBuf;
	vec[1].iov_len = sizeof(extraBuf);

	size_t writable = writableBytes();
	int iovcnt = 2;
	size_t n = ::readv(fd, vec, iovcnt);
	if (n < 0) {
		*saveErrno = errno;
	} else if (n <= writable) {
		writeIndex_ += n;
	} else {
		writeIndex_ += buffer_.size();
		append(extraBuf, n - writable);
	}
	return n;
}

