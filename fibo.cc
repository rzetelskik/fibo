#include "fibo.h"

Fibo::Fibo(const std::string& str) {
    //TODO sanity check moodle
    this->bits = boost::dynamic_bitset<>(str);
    normaliseBits();
}

void Fibo::clearLeadingZeroBits() {
    size_t i = this->length() - 1;
    while (i > 0 && !this->bits[i]) --i;

    this->bits.resize(i + 1);
}

void Fibo::clearBitsInRange(size_t begin, size_t end) {
    if (end < begin) std::swap(begin, end);
    for (size_t i = begin; i <= end; i++) {
        this->bits[i] = false;
    }
}

void Fibo::normaliseBits() {
    clearLeadingZeroBits();

    this->bits.push_back(false);
    size_t memZero = this->length() - 1, lowestSetBit = this->bits.find_first();

    for (size_t i = this->length() - 2; i > lowestSetBit; i--) {
        if (!this->bits[i] && !this->bits[i - 1]) {
            memZero = i - 1;
        } else if (this->bits[i] && this->bits[i - 1]) {
            this->bits[memZero] = true;
            clearBitsInRange(memZero - 1, i - 1);
            memZero = i - 1;
        }
    }

    clearLeadingZeroBits();
}

Fibo::Fibo(long long n) {
    //TODO sanity check moodle
    if (n < 0) throw std::invalid_argument("Negative value provided.");
    //TODO
}

Fibo& Fibo::operator=(const Fibo& other) {
    if (this != &other) {
        bits = other.bits;
    }
    return *this;
}

bool Fibo::getOrDefault(size_t i, bool value) const {
    if (this->length() > i) {
        return this->bits[i];
    }
    return value;
}

Fibo& Fibo::performBitwiseOperation(const Fibo& other, const BitFunction& f) {
    size_t min = this->length(), max = other.length();
    if (max < min) std::swap(min, max);

    for (size_t i = 0; i < min; i++) {
        this->bits[i] = f(this->bits[i], other.bits[i]);
    }

    if (this->length() < max) this->bits.resize(max, false);
    for (size_t i = min; i < max; i++) {
        this->bits[i] = f(this->bits[i], other.getOrDefault(i, false));
    }

    normaliseBits();
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

Fibo& Fibo::operator<<=(long long n) {
    if (!n) return *this;
    //TODO co robimy dla n < 0?
    if (n < 0) throw std::invalid_argument("Invalid argument provided");

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

const Fibo Fibo::operator<<(long long n) const {
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