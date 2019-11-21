#include "fibo.h"
#include <iostream>
#include <vector>

namespace {
std::vector<long long> &fibonacciVector() {
  static size_t maxFit = 91;
  static std::vector<long long> fibonacciVector(maxFit, 0);
  return fibonacciVector;
}

void fibonacciComputeIfAbsent(size_t pos) {
  if (fibonacciVector().size() <= pos) {
    fibonacciVector().resize(pos, 0);
  }
  if (fibonacciVector()[pos]) {
    return;
  }

  fibonacciVector()[pos] = ((pos > 0) ? fibonacciVector()[pos - 1] : 0) +
                           ((pos > 1) ? fibonacciVector()[pos - 2] : 1);
}

size_t fibonacciGetBestFit(long long n) {
  size_t pos = 0;
  fibonacciComputeIfAbsent(pos);

  do {
    fibonacciComputeIfAbsent(pos);
  } while (fibonacciVector()[pos++] <= n);

  return --pos;
}

bool isStringValid(const std::string &str) {
  if (str.size() > 1 && str.at(0) == '0') {
    return false;
  }
  for (auto c : str) {
    if ('1' < c || c < '0')
      return false;
  }

  return true;
}
} // namespace

Fibo::Fibo(const std::string &str) {
  if (!isStringValid(str)) {
    throw std::invalid_argument("Invalid string format.");
  }
  bits = boost::dynamic_bitset<>(str);
  normaliseBits();
}

Fibo::Fibo(long long n) {
  if (n < 0) {
    throw std::invalid_argument("Negative value provided.");
  }
  if (n == 0) {
    *this = Fibo();
    return;
  }

  size_t maxPos = fibonacciGetBestFit(n);
  bits.resize(maxPos, false);

  long long fib = n;
  for (size_t i = maxPos; i <= maxPos && fib > 0; i--) {
    fib = fibonacciVector()[i];

    if (fib <= n) {
      n -= fib;
      bits.set(i, true);
    }
  }
}

void Fibo::clearLeadingZeroBits() {
  size_t i = this->length() - 1;
  while (i > 0 && !bits.test(i)) {
    i--;
  }

  bits.resize(i + 1);
}

void Fibo::clearBitsInRange(size_t begin, size_t end) {
  if (end < begin) {
    std::swap(begin, end);
  }
  for (size_t i = begin; i <= end; i++) {
    bits.set(i, false);
  }
}

void Fibo::normaliseBits() {
  clearLeadingZeroBits();

  bits.push_back(false);
  size_t memZero = length() - 1, lowestSetBit = bits.find_first();

  for (size_t i = length() - 2; i > lowestSetBit; i--) {
    if (!bits.test(i) && !bits.test(i - 1)) {
      memZero = i - 1;
    } else if (bits.test(i) && bits.test(i - 1)) {
      bits.set(memZero, true);
      clearBitsInRange(memZero - 1, i - 1);
      memZero = i - 1;
    }
  }

  clearLeadingZeroBits();
}

Fibo &Fibo::operator=(const Fibo &other) {
  if (this != &other) {
    bits = other.bits;
  }
  return *this;
}

bool Fibo::getOrDefault(size_t i, bool value) const {
  if (length() > i) {
    return bits.test(i);
  }

  return value;
}

Fibo &Fibo::performBitwiseOperation(const Fibo &other, const BitFunction &f) {
  size_t min = length(), max = other.length();
  if (max < min)
    std::swap(min, max);

  for (size_t i = 0; i < min; i++) {
    bits.set(i, f(bits.test(i), other.bits.test(i)));
  }

  if (length() < max) {
    bits.resize(max, false);
  }
  for (size_t i = min; i < max; i++) {
    bits.set(i, f(bits.test(i), other.getOrDefault(i, false)));
  }

  normaliseBits();
  return *this;
}

Fibo &Fibo::operator+=(const Fibo &other) {
  size_t len1 = length();
  size_t len2 = other.length();
  if (len1 < len2) {
    bits.resize(len2, false);
  } else if (len1 == len2) {
    bits.resize(len1 + 1, false);
  }
  bits.push_back(false);

  bool rem[3] = {false, false, false};
  int j = 0;
  for (size_t i = len2; i-- > 0;) {
    if (!other.bits.test(i) && !rem[j]) {
    } else if ((other.bits.test(i) && rem[j]) || bits.test(i)) {
      if (bits.test(i + 1)) {
        bits.set(i + 2, true);
        rem[(j + 1) % 3] = true;
      }
      bits.flip(i + 1);
      rem[(j + 2) % 3] = true;
      if (!other.bits.test(i) || !rem[j]) {
        bits.set(i, false);
      }
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
  } else if (rem[j]) {
    bits.set(0, true);
  }

  normaliseBits();
  return *this;
}

Fibo &Fibo::operator&=(const Fibo &other) {
  return performBitwiseOperation(other, std::bit_and<>());
}

Fibo &Fibo::operator|=(const Fibo &other) {
  return performBitwiseOperation(other, std::bit_or<>());
}

Fibo &Fibo::operator^=(const Fibo &other) {
  return performBitwiseOperation(other, std::bit_xor<>());
};

Fibo &Fibo::operator<<=(size_t n) {
  if (!n) {
    return *this;
  }

  bits.resize(length() + n, false);
  bits <<= n;
  return *this;
}

bool operator==(const Fibo &left, const Fibo &right) {
  return left.bits == right.bits;
}

bool operator<(const Fibo &left, const Fibo &right) {
  if (left.length() == right.length()) {
    return left.bits < right.bits;
  }

  return left.length() < right.length();
}

std::ostream &operator<<(std::ostream &os, const Fibo &fibo) {
  os << fibo.bits;
  return os;
}

const Fibo Zero() { return Fibo(); }

const Fibo One() { return Fibo(1); }

size_t Fibo::length() const { return bits.size(); }