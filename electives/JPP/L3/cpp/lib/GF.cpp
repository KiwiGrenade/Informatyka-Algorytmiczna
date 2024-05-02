//
// Created by jaskow on 06.04.24.
//
#include <stdexcept>
#include "GF.hpp"
#include "lib.h"

//////////////////////////////////////////////////////////////
// private
void GF::checkP(const GF& L, const GF& R) {
    if(L.p != R.p)
        throw std::invalid_argument("[GF]ERROR: not matching p! " + std::to_string(L.p) + " != " + std::to_string(R.p));
}

uint32_t GF::inverse(const uint32_t _p, const int64_t _val){
    return _p + (_val % _p);
}


//////////////////////////////////////////////////////////////
// public
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
        val = inverse(p, _val);
    }
    else {
        val = _val % p;
    }
}


// compare
bool GF::operator==(const GF &R) const {
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
    return GF(R.p, ((uint64_t) val + R.val) % p);
}
GF GF::operator*(const GF &R) const {
    checkP(*this, R);
    return GF(p, ((uint64_t) val * R.val) % p); 
}
GF GF::operator/(const GF &R) const {
    checkP(*this, R);

    uint64_t RValReverse = ILDES(R.val, R.p, RGCD(R.val, R.p)).x;

    return GF(p, val) * GF(p, RValReverse);
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
    out << "p: " << gf.p << ", "
        << "val: " << gf.val;
    return out;
}
