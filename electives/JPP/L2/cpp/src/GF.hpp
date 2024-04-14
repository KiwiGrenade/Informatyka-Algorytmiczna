//
// Created by jaskow on 06.04.24.
//

#ifndef JPP_L2_GF_HPP
#define JPP_L2_GF_HPP

#include <cstdint>
#include <iostream>

class GF {
private:
    uint32_t p;
    uint32_t val;
    static void checkP(const GF& L, const GF& R);

public:
    explicit GF(const uint32_t& _p, const int64_t& _val);
    ~GF() = default;

    [[nodiscard]] uint32_t getP() const noexcept;
    void setP(uint32_t _p) noexcept;
    [[nodiscard]] uint32_t getVal() const noexcept;
    void setVal(int64_t _val) noexcept;

    // assignments
    GF& operator= (const GF &other) = default;
    GF& operator+=(const GF &other);
    GF& operator-=(const GF &other);
    GF& operator*=(const GF &other);
    GF& operator/=(const GF &other);

    // compare
    bool operator == (const GF &R) const;
    bool operator != (const GF &R) const;
    bool operator <  (const GF &R) const;
    bool operator >  (const GF &R) const;
    bool operator <= (const GF &R) const;
    bool operator >= (const GF &R) const;

    // arithmetic
    GF operator-() const noexcept;
    GF operator+() const noexcept;
    GF operator+(const GF &R) const;
    GF operator-(const GF &R) const;
    GF operator*(const GF &R) const;
    GF operator/(const GF &R) const;

    // stream
    friend std::ostream& operator<<(std::ostream& out, const GF& gf);

};

#endif //JPP_L2_GF_HPP
