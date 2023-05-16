#include <iostream>

#ifndef QIQIAO_NET_BUFFER_H
#define QIQIAO_NET_BUFFER_H
#include <vector>
#include <algorithm>
#include <cassert>

namespace qiqiao {

namespace net {
	class Buffer {
	public:
		static const size_t kInitSize = 1024;
		static const size_t kCheapPrepend = 8;

	public:
		Buffer(const size_t initSize = kInitSize)
			:buffer_(initSize)
			,readIndex_(kCheapPrepend)
			,writeIndex_(kCheapPrepend)
		{}

		/*HOW TO ADD DATA INTO buffer_*/
		void append(char *data, size_t len) {
			ensureWritableBytes(len);
			std::copy(data, data+len, buffer_.begin()+readIndex_);
			writeIndex_ += len;
		}
	
		void ensureWritableBytes(size_t len) {
			if (writableBytes() < len) {
				makeSpace(len);
			}
		}

		size_t readableBytes() {
			return writeIndex_ - readIndex_;
		}

		size_t writableBytes() {
			return buffer_.size() - writeIndex_;
		}

		size_t prependableBytes() {
			return readIndex_;
		}

		void makeSpace(size_t len) {
			if (writableBytes() + prependableBytes() < len + kCheapPrepend) {
				buffer_.resize(writeIndex_ + len);
			} else {
				assert(kCheapPrepend <= readIndex_);
				size_t readable = writeIndex_ - readIndex_;
				std::copy(buffer_.begin() + readIndex_,
						  buffer_.begin() + writeIndex_,
						  buffer_.begin() + kCheapPrepend);
				readIndex_ = kCheapPrepend;
				writeIndex_ = readIndex_ + readable;
			}
		}

		/*HOW TO RETRIEVE*/
		void retrieve(size_t len) {
			assert(len <= readableBytes());
			if (len < readableBytes()) {
				readIndex_ += len;
			} else {
				retrieveAll();
			}
		}
		
		void retrieveAll() {
			readIndex_ = kCheapPrepend;
			writeIndex_ = kCheapPrepend;
		}

		size_t readFd(int fd, int *saveErrno);
	private:
		char *begin() {
			return &*buffer_.begin();
		}

		std::vector<char> buffer_;
		int readIndex_;
		int writeIndex_;

	public:
		void printBuffer() {
			auto rIter = buffer_.begin() + readIndex_;
			auto wIter = buffer_.begin() + writeIndex_;
			while (rIter != wIter) {
				std::cout << *rIter;
				++rIter;
			}
			std::cout << std::endl;
		}
	};

};
};
#endif
