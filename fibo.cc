#include <functional>
#include "fibo.h"

Fibo::Fibo(const std::string& str) {
    this->bits = boost::dynamic_bitset<>(str);
    normalise();
}

void Fibo::normalise() {
    //TODO
}

Fibo::Fibo(unsigned long n) {
    //TODO
}

Fibo& Fibo::operator=(const Fibo& other) {
    if (this != &other) {
        bits = other.bits;
    }
    return *this;
}

Fibo& Fibo::performBitwiseOperation(const Fibo& other, const BitFunction& f) {
    size_t min = std::min(this->length(), other.length());
    for (size_t i = 0; i < min; i++) {
        this->bits[i] = f(this->bits[i], other.bits[i]);
    }
    for (size_t i = min; i < other.length(); i++) {
        this->bits.push_back(f(other.bits[i], false));
    }

    return *this;
}


Fibo& Fibo::operator+=(const Fibo& other) {
    //TODO
    return *this;
}

Fibo& Fibo::operator&=(const Fibo& other) {
    return performBitwiseOperation(other, std::bit_and<>());
}

Fibo& Fibo::operator|=(const Fibo& other) {
    return performBitwiseOperation(other, std::bit_or<>());
}

Fibo& Fibo::operator^=(const Fibo &other) {
    return performBitwiseOperation(other, std::bit_xor<>());
};

Fibo& Fibo::operator<<=(unsigned long n) {
    //TODO exception for n < 0?
    if (!n) {
        return *this;
    }

    this->bits.resize(this->length() + n, false);
    this->bits <<= n;
    return *this;
}

const Fibo Fibo::operator+(const Fibo& other) const {
    return Fibo(*this) += other;
}

const Fibo Fibo::operator&(const Fibo& other) const {
    return Fibo(*this) &= other;
}

const Fibo Fibo::operator|(const Fibo& other) const {
    return Fibo(*this) |= other;
}

const Fibo Fibo::operator^(const Fibo& other) const {
    return Fibo(*this) ^= other;
}

const Fibo Fibo::operator<<(unsigned long n) const {
    return Fibo(*this) <<= n;
}

unsigned long Fibo::length() const {
    return bits.size();
}

std::ostream& operator<<(std::ostream& os, const Fibo& fibo) {
    os << fibo.bits;
    return os;
}

bool Fibo::operator==(const Fibo& other) const {
    return this->bits == other.bits;
}

bool Fibo::operator<(const Fibo& other) const {
    return this->bits < other.bits;
}

bool Fibo::operator<=(const Fibo& other) const {
    return this->bits <= other.bits;
}

bool Fibo::operator!=(const Fibo& other) const {
    return this->bits != other.bits;
}

bool Fibo::operator>(const Fibo& other) const {
    return this->bits > other.bits;
}

bool Fibo::operator>=(const Fibo& other) const {
    return this->bits >= other.bits;
}

const Fibo Zero() {
    return Fibo();
}

const Fibo One() {
    return Fibo(1);
}