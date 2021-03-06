#ifndef FIBO_FIBO_H
#define FIBO_FIBO_H

#include <boost/dynamic_bitset.hpp>
#include <boost/operators.hpp>
#include <functional>

using BitFunction = std::function<bool(bool, bool)>;

class Fibo : boost::addable<Fibo>,
             boost::bitwise<Fibo>,
             boost::left_shiftable<Fibo, size_t>,
             boost::totally_ordered<Fibo> {
  public:
    Fibo();
    Fibo(const Fibo &other) = default;
    Fibo(Fibo &&other) noexcept : bits(std::move(other.bits)) {}
    ~Fibo() = default;
    explicit Fibo(const std::string &str);
    Fibo(long long n);
    template <typename T, typename = typename std::enable_if<
                              (std::is_same<T, bool>::value ||
                               std::is_same<T, char>::value ||
                               std::is_same<T, wchar_t>::value ||
                               std::is_same<T, char16_t>::value ||
                               std::is_same<T, char32_t>::value)>::type>
    Fibo(T t) = delete;
    Fibo &operator=(const Fibo &other);
    Fibo &operator+=(const Fibo &other);
    Fibo &operator&=(const Fibo &other);
    Fibo &operator|=(const Fibo &other);
    Fibo &operator^=(const Fibo &other);
    Fibo &operator<<=(size_t n);

    friend bool operator==(const Fibo &left, const Fibo &right);
    friend bool operator<(const Fibo &left, const Fibo &right);
    friend std::ostream &operator<<(std::ostream &os, const Fibo &fibo);

    [[nodiscard]] size_t length() const;

  private:
    boost::dynamic_bitset<> bits;
    void initZero();
    void clearBitsInRange(size_t begin, size_t end);
    void clearLeadingZeroBits();
    void adjustSizeForAddition(const Fibo &other);
    void addOneBit(size_t i, bool bit, bool carry, bool *carry1, bool *carry2);
    void normaliseLocalBits(size_t i);
    void normaliseBits();
    [[nodiscard]] bool getOrDefault(size_t i, bool value) const;
    Fibo &performBitwiseOperation(const Fibo &other, const BitFunction &f);
};

const Fibo &Zero();

const Fibo &One();

#endif // FIBO_FIBO_H
