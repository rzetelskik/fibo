//TODO do wyjebania
#include <iostream>
#include "fibo.h"

Fibo::Fibo(const std::string& str) {
    //TODO sanity check?
    this->bits = boost::dynamic_bitset<>(str);
    //TODO normalize
}

Fibo& Fibo::operator=(const Fibo& other) {
    if (this != &other) {
        bits = other.bits;
    }
    return *this;
}

Fibo::Fibo(unsigned long n) {
    //TODO
}

Fibo& Fibo::operator+=(const Fibo& other) {
    //TODO
    return *this;
}

Fibo& Fibo::operator&=(const Fibo& other) {
    //TODO
    return *this;
}

Fibo& Fibo::operator|=(const Fibo& other) {
    //TODO
    return *this;
}

Fibo& Fibo::operator^=(const Fibo &other) {
    //TODO
    return *this;
};

Fibo& Fibo::operator<<=(unsigned long n) {
    //TODO
    return *this;
}

const Fibo& Fibo::operator+(const Fibo& other) const {
    return Fibo(*this) += other;
}

const Fibo& Fibo::operator&(const Fibo& other) const {
    return Fibo(*this) &= other;
}

const Fibo& Fibo::operator|(const Fibo& other) const {
    return Fibo(*this) |= other;
}

const Fibo& Fibo::operator^(const Fibo& other) const {
    return Fibo(*this) ^= other;
}

const Fibo& Fibo::operator<<(unsigned long n) const {
    return Fibo(*this) <<= n;

}

unsigned long Fibo::length() {
    return bits.size();
}

std::ostream& operator<<(std::ostream& os, const Fibo& fibo) {
    os << fibo.bits;
    return os;
}
