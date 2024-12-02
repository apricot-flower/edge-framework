#include "ByteBuf.h"
#include <cstring>
#include <algorithm>

ByteBuf::ByteBuf(const unsigned long long max) : MaxSize(max) {
    index = 0;
    buf = std::vector<char>(max);
}

ByteBuf::ByteBuf(const std::vector<char>& buff) : buf(buff) {
    index = 0;
    MaxSize = buff.size();
}


//清空
void ByteBuf::clear() {
    index = 0;
    buf.clear();
}

//扩容
void ByteBuf::expand(const unsigned long long size) {
    MaxSize += size;
}

//追加一个char
void ByteBuf::appendChar(const char value) {
    //判断容量
    if (buf.size() + sizeof(char) > MaxSize) {
        throw ByteBufException("exceeding maximum capacity!");
    }
    buf.push_back(value);
}

//追加一个short,大端序
void ByteBuf::appendShortBigEndian(const short int value) {
    //获取低位
    char low = static_cast<char>(value & 0xFF);
    //高位
    char high = static_cast<char>((value >> 8)) & 0xFF;
    appendMoreChar({high, low});
}

void ByteBuf::appendShortLittleEndian(const short int value) {
    //获取低位
    char low = static_cast<char>(value & 0xFF);
    //高位
    char high = static_cast<char>((value >> 8)) & 0xFF;
    appendMoreChar({low, high});
}


//追加一个int
void ByteBuf::appendIntBigEndian(const int value) {
    char char1 = static_cast<char>(value & 0xFF);
    char char2 = static_cast<char>((value >> 8)) & 0xFF;
    char char3 = static_cast<char>((value >> 16)) & 0xFF;
    char char4 = static_cast<char>((value >> 24)) & 0xFF;
    appendMoreChar({char1, char2, char3, char4});
}


void ByteBuf::appendIntLittleEndian(const int value) {
    char char1 = static_cast<char>(value & 0xFF);
    char char2 = static_cast<char>((value >> 8)) & 0xFF;
    char char3 = static_cast<char>((value >> 16)) & 0xFF;
    char char4 = static_cast<char>((value >> 24)) & 0xFF;
    appendMoreChar({char4, char3, char2, char1});
}

//追加一个long
void ByteBuf::appendLongIntBigEndian(const long int value) {
    char more[8];
    std::memcpy(more, &value, sizeof(long int));
    buf.insert(buf.end(), more, more + sizeof(long int));
}

void ByteBuf::appendLongIntLittleEndian(const long int value) {
    char more[8];
    std::memcpy(more, &value, sizeof(long int));
    int size_n = sizeof(more) / sizeof(more[0]);
    std::reverse(more, more + size_n);
    buf.insert(buf.end(), more, more + sizeof(long int));
}


void ByteBuf::appendVector(const std::vector<char>& buff) {
    if (buf.size() + buff.size() > MaxSize) {
        throw ByteBufException("exceeding maximum capacity!");
    }
    buf.insert(buf.end(), buff.begin(), buff.end());
}


char ByteBuf::readChar() {
    if (index > MaxSize) {
        throw ByteBufException("All data has been read out!");
    }
    char value = buf[index];
    index ++;
    return value;
}

short int ByteBuf::readShortIntBigEndian() {
    if (index > MaxSize || index + sizeof(short int) > MaxSize) {
        throw ByteBufException("All data has been read out!");
    }
    short int value;
    std::memcpy(&value, &buf[index], sizeof(short int));
    index += sizeof(short int);
    return value;
}

short int ByteBuf::readShortIntLittleEndian() {
    short int value = readShortIntBigEndian();
    value = (value >> 8) | (value << 8);
    return value;
}


int ByteBuf::readIntBigEndian() {
    if (index > MaxSize || index + sizeof(int) > MaxSize) {
        throw ByteBufException("All data has been read out!");
    }
    int value;
    std::memcpy(&value, &buf[index], sizeof(int));
    index += sizeof(int);
    return value;
}


int ByteBuf::readIntLittleEndian() {
    int value = readIntBigEndian();
     return (value >> 24) |
           ((value << 8) & 0x00FF0000) |
           ((value >> 8) & 0x0000FF00) |
           (value << 24);
}

long int ByteBuf::readLongIntBigEndian() {
    if (index > MaxSize || index + sizeof(long int) > MaxSize) {
        throw ByteBufException("All data has been read out!");
    }
    long int value;
    std::memcpy(&value, &buf[index], sizeof(long int));
    index += sizeof(long int);
    return value;
}

long int ByteBuf::readLongIntLittleEndian() {
    long int value = readLongIntBigEndian();
    return (value >> 56) |
           ((value << 40) & 0x00FF000000000000LL) |
           ((value << 24) & 0x0000FF0000000000LL) |
           ((value << 8) & 0x000000FF00000000LL) |
           ((value >> 8) & 0x00000000FF000000LL) |
           ((value >> 24) & 0x0000000000FF0000LL) |
           ((value >> 40) & 0x000000000000FF00LL) |
           (value << 56);
}


char* ByteBuf::readCharArray(const unsigned int size) {
    if (index > MaxSize || index + size > MaxSize) {
        throw ByteBufException("All data has been read out!");
    }
    char more[size];
    for (int i = 0; i < size; i++) {
        more[i] = readChar();
    }
    return more;
}

void ByteBuf::appendMoreChar(std::initializer_list<char> more) {
    if (buf.size() + more.size() > MaxSize) {
        throw ByteBufException("exceeding maximum capacity!");
    }
    buf.insert(buf.end(), more.begin(), more.end());   
}