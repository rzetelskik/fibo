#include <vector>

#include "fibo.h"

bool Fibo::isStringValid(const std::string& str) {
    for (auto c: str) {
        if ('1' < c || c < '0') return false;
    }

    return true;
}

Fibo::Fibo(const std::string& str) {
    if (!isStringValid(str)) throw std::invalid_argument("Invalid argument provided.");
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
    if (n < 0) throw std::invalid_argument("Negative value provided.");
    if (n == 0) {
        this->bits.push_back(0);
        return;
    }
    std::vector<long long> fibs;
    int a = 1, b = 1;
    while (b <= n) {
        fibs.push_back(b);
        int tmp = b;
        b += a;  //TODO: Here is a risk of IntOverflow
        a = tmp;
    }
    this->bits.resize(fibs.size(), false);
    for (int i = fibs.size() - 1; i >= 0; i--) {
        int fib = fibs[i];
        if (fib <= n) {
            n -= fib;
            this->bits[i] = 1;
        }
    }
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
    size_t len1 = length();
    size_t len2 = other.length();
    if (len1 < len2)
        bits.resize(len2, false);
    else if (len1 == len2)
        bits.resize(len1 + 1, false);
    bits.push_back(false);

    bool rem[3] = {false, false, false};
    int j = 0;
    for (int i = len2 - 1; i >= 0; i--) {
        if (!other.bits.test(i) && !rem[j]) {}
        else if ((other.bits.test(i) && rem[j]) || bits.test(i)) {
            if (bits.test(i + 1)) {
                bits.set(i + 2, true);
                rem[(j + 1) % 3] = true;
            }
            bits.flip(i + 1);
            rem[(j + 2) % 3] = true;
            if (!other.bits.test(i) || !rem[j])
                bits.set(i, false);
        } else {
            bits.set(i, true);
        }
        if (bits.test(i) && bits.test(i + 1)) {
            bits.flip(i);
            bits.flip(i + 1);
            bits.flip(i + 2);
        }
        rem[j] = false;
        j = (j + 1) % 3;
    }
    if (rem[j] && bits.test(0)) {
        bits.flip(0);
        bits.set(1, true);
    } else if (rem[j])
        bits.set(0, true);

    normaliseBits();
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

size_t Fibo::length() const {
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