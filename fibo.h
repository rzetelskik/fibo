#ifndef FIBO_FIBO_H
#define FIBO_FIBO_H

#include <boost/dynamic_bitset.hpp>

class Fibo {
private:
    boost::dynamic_bitset<> bits;
public:
    // Sets all bits to zeros by default.
    Fibo() : bits(1) {};
    Fibo(const Fibo& other) : bits(other.bits) {};
    ~Fibo() = default;
    explicit Fibo(const std::string& str);
    //TODO int? long long?
    explicit Fibo(unsigned long n);

    //TODO pojecia nie mam czy to jest optymalne, trzeba zerknac na czytanki
    Fibo& operator=(const Fibo &other);
    Fibo& operator+=(const Fibo &other);
    Fibo& operator&=(const Fibo &other);
    Fibo& operator|=(const Fibo &other);
    Fibo& operator^=(const Fibo &other);
    Fibo& operator<<=(unsigned long n);
    const Fibo& operator+(const Fibo &other) const;
    const Fibo& operator&(const Fibo &other) const;
    const Fibo& operator|(const Fibo &other) const;
    const Fibo& operator^(const Fibo &other) const;
    const Fibo& operator<<(unsigned long n) const;
    friend std::ostream& operator<<(std::ostream &os, const Fibo& fibo);
    unsigned long length();
};

Fibo Zero();

Fibo One();

#endif //FIBO_FIBO_H
