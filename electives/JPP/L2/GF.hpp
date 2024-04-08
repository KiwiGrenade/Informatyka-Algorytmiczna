//
// Created by jaskow on 06.04.24.
//

#ifndef JPP_L2_GF_HPP
#define JPP_L2_GF_HPP

#include <cstdint>

class GF {
private:
    uint32_t p;
    uint32_t value;
    static void checkP(const GF& L, const GF& R);

public:
    explicit GF(const uint32_t& _p, const uint32_t& _value) noexcept;
    ~GF() = default;

    [[nodiscard]] uint32_t getP() const noexcept;
    void setP(uint32_t _p);
    [[nodiscard]] uint32_t getVal() const noexcept;
    void setVal(uint32_t _val);

    // copy assignment
    GF& operator=(const GF& other) = default;

    // compare
    bool operator == (const GF &R) const;
    bool operator != (const GF &R) const;
    bool operator <  (const GF &R) const;
    bool operator >  (const GF &R) const;
    bool operator <= (const GF &R) const;
    bool operator >= (const GF &R) const;

    // arithmetic
    GF operator+(const GF &R) const;

};

#endif //JPP_L2_GF_HPP
