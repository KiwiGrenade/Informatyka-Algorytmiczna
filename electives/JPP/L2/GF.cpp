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

GF::GF(const uint32_t& _p, const uint32_t& _value) {
    if(_p == 0) {
        throw std::invalid_argument("[GF]ERROR: p cannot equal 0");
    }
    p = _p;
    value = _value % p;
}

uint32_t GF::getP() const noexcept{
    return p;
}
void GF::setP(uint32_t _p) noexcept{
    p = _p;
}

uint32_t GF::getVal() const noexcept{
    return value;
}
void GF::setVal(uint32_t _val) noexcept{
    value = (_val) % p;
}

// compare
bool GF::operator==(const GF &R) const {
    checkP(*this, R);
    return this->value == R.value;
}
bool GF::operator!=(const GF &R) const {
    return !(*this == R);
}
bool GF::operator<(const GF &R) const {
    checkP(*this, R);
    return this->value < R.value;
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
    return GF(p, p-value);
}
GF GF::operator-(const GF &R) const {
    checkP(*this, R);
    return ((-R) + (*this));
}
GF GF::operator+(const GF &R) const {
    checkP(*this, R);
    uint32_t _val = (value + R.value) % p;
    return GF(R.p, _val);
}
GF GF::operator*(const GF &R) const {
    checkP(*this, R);
    uint32_t _val = (value * R.value) % p;
    return GF(p, _val);
}
GF GF::operator/(const GF &R) const {
    checkP(*this, R);

    uint32_t RValReverse = ILDES((uint64_t)R.value, (uint64_t)R.p, RGCD(R.value, R.p)).x;

    uint32_t _val = (value * RValReverse) % p;
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
