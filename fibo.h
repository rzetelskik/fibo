#ifndef FIBO_FIBO_H
#define FIBO_FIBO_H

#include <boost/dynamic_bitset.hpp>
#include <functional>

using BitFunction = std::function<bool(bool, bool)>;

class Fibo {
private:
    boost::dynamic_bitset<> bits;
    void clearBitsInRange(size_t begin, size_t end);
    void clearLeadingZeroBits();
    void normaliseBits();
    [[nodiscard]] bool getOrDefault(size_t i, bool value) const;
    Fibo& performBitwiseOperation(const Fibo& other, const BitFunction& f);
public:
    Fibo() : bits(1, false) {};
    Fibo(const Fibo& other) = default;
    ~Fibo() = default;
    explicit Fibo(const std::string& str);
    explicit Fibo(long long n);

    Fibo& operator=(const Fibo& other);
    Fibo& operator+=(const Fibo& other);
    Fibo& operator&=(const Fibo& other);
    Fibo& operator|=(const Fibo& other);
    Fibo& operator^=(const Fibo& other);
    Fibo& operator<<=(long long n);

    const Fibo operator+(const Fibo& other) const;
    const Fibo operator&(const Fibo& other) const;
    const Fibo operator|(const Fibo& other) const;
    const Fibo operator^(const Fibo& other) const;
    const Fibo operator<<(long long n) const;

    bool operator==(const Fibo& other) const;
    bool operator<(const Fibo& other) const;
    bool operator<=(const Fibo& other) const;
    bool operator!=(const Fibo& other) const;
    bool operator>(const Fibo& other) const;
    bool operator>=(const Fibo& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Fibo& fibo);
    [[nodiscard]] unsigned long long length() const;
};

const Fibo Zero();

const Fibo One();

#endif //FIBO_FIBO_H
