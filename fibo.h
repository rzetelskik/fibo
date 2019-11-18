#ifndef FIBO_FIBO_H
#define FIBO_FIBO_H

#include <boost/dynamic_bitset.hpp>

using BitFunction = std::function<bool(bool, bool)>;

class Fibo {
private:
    boost::dynamic_bitset<> bits;
    void normalise();
    Fibo& performBitwiseOperation(const Fibo& other, const BitFunction& f);
public:
    // Sets all bits to zeros by default.
    Fibo() : bits(1) {};
    Fibo(const Fibo& other) : bits(other.bits) {};
    ~Fibo() = default;
    explicit Fibo(const std::string& str);
    //TODO int? long long?
    explicit Fibo(unsigned long n);

    Fibo& operator=(const Fibo& other);
    Fibo& operator+=(const Fibo& other);
    Fibo& operator&=(const Fibo& other);
    Fibo& operator|=(const Fibo& other);
    Fibo& operator^=(const Fibo& other);
    Fibo& operator<<=(unsigned long n);

    const Fibo operator+(const Fibo& other) const;
    const Fibo operator&(const Fibo& other) const;
    const Fibo operator|(const Fibo& other) const;
    const Fibo operator^(const Fibo& other) const;
    const Fibo operator<<(unsigned long n) const;

    bool operator==(const Fibo& other) const;
    bool operator<(const Fibo& other) const;
    bool operator<=(const Fibo& other) const;
    bool operator!=(const Fibo& other) const;
    bool operator>(const Fibo& other) const;
    bool operator>=(const Fibo& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Fibo& fibo);
    [[nodiscard]] unsigned long length() const;
};

const Fibo Zero();

const Fibo One();

#endif //FIBO_FIBO_H
