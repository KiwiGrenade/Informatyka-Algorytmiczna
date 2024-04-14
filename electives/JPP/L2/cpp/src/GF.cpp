//
// Created by jaskow on 06.04.24.
//

#include <stdexcept>
#include "GF.hpp"
#include "lib.h"
void GF::checkP(const GF& L, const GF& R) {
    if(L.p != R.p)
        throw std::invalid_argument("[GF]ERROR: not matching p!");
}

GF::GF(const uint32_t& _p, const int64_t& _val) {
    if(_p == 0) {
        throw std::invalid_argument("[GF]ERROR: p must be > 0");
    }
    p = _p;
    setVal(_val);
}

uint32_t GF::getP() const noexcept{
    return p;
}
void GF::setP(uint32_t _p) noexcept{
    p = _p;
    this->setVal(val);
}

uint32_t GF::getVal() const noexcept{
    return val;
}
void GF::setVal(int64_t _val) noexcept{
    if(_val < 0 ) {
        val = (p + _val) % p;
    }
    else {
        val = _val;
    }
}

// compare
bool GF::operator==(const GF &R) const {
    checkP(*this, R);
    return this->val == R.val;
}
bool GF::operator!=(const GF &R) const {
    return !(*this == R);
}
bool GF::operator<(const GF &R) const {
    checkP(*this, R);
    return this->val < R.val;
}
bool GF::operator>(const GF &R) const {
    return R < *this;
}
bool GF::operator<=(const GF &R) const {
    return !(*this > R);
}
bool GF::operator>=(const GF &R) const {
    return !(*this < R);
}

// arithmetic
GF GF::operator+() const noexcept {
    return *this;
}
GF GF::operator-() const noexcept{
    return GF(p, p - val);
}
GF GF::operator-(const GF &R) const {
    checkP(*this, R);
    return ((-R) + (*this));
}
GF GF::operator+(const GF &R) const {
    checkP(*this, R);
    uint32_t _val = (val + R.val) % p;
    return GF(R.p, _val);
}
GF GF::operator*(const GF &R) const {
    checkP(*this, R);
    uint32_t _val = (val * R.val) % p;
    return GF(p, _val);
}
GF GF::operator/(const GF &R) const {
    checkP(*this, R);

    uint32_t RValReverse = ILDES((uint64_t)R.val, (uint64_t)R.p, RGCD(R.val, R.p)).x;

    uint32_t _val = (val * RValReverse) % p;
    return GF(p, _val);
}

// assignment
GF& GF::operator+=(const GF &other) {
    *this = ((*this) + other);
    return *this;
}
GF& GF::operator-=(const GF &other) {
    *this = (*this - other);
    return *this;
}
GF& GF::operator*=(const GF &other) {
    *this = ((*this) * other);
    return *this;
}
GF& GF::operator/=(const GF &other) {
    *this = (*this / other);
    return *this;
}

std::ostream &operator<<(std::ostream &out, const GF &gf) {
    out << "p   = " << gf.p
        << "val = " << gf.val;
    return out;
}
