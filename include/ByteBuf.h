#ifndef BYTEBUF_H
#define BYTEBUF_H

#include <vector>
#include <exception>
#include <string>
#include <stdexcept>

class ByteBuf {
    public:
        unsigned long long MaxSize;
        std::vector<char> buf;
        unsigned long long index;
        ByteBuf(const unsigned long long MaxSize);
        ByteBuf(const std::vector<char>& buf);
        //清空
        void clear();
        //扩容
        void expand(const unsigned long long size);
        /* 以下为添加 */
        void appendChar(const char value);
        void appendShortBigEndian(const short int value);
        void appendShortLittleEndian(const short int value);
        void appendIntBigEndian(const int value);
        void appendIntLittleEndian(const int value);
        void appendLongIntBigEndian(const long int value);
        void appendLongIntLittleEndian(const long int value);
        void appendVector(const std::vector<char>& buff);
        /* 以下为查询 */
        char readChar();
        short int readShortIntBigEndian();
        short int readShortIntLittleEndian();
        int readIntBigEndian();
        int readIntLittleEndian();
        long int readLongIntBigEndian();
        long int readLongIntLittleEndian();
        char* readCharArray(const unsigned int size);
    private:
        void appendMoreChar(std::initializer_list<char> more);
};


//一个统一的缓冲区异常
class ByteBufException: public std::runtime_error {
    public:
        ByteBufException(const std::string& msg) : std::runtime_error(msg) {

        }
        const char* what() const noexcept override {
            return std::runtime_error::what();
        }
};

#endif