//
// Created by jaskow on 06.04.24.
//

#include <stdexcept>
#include "GF.hpp"

void GF::checkP(const GF& L, const GF& R) {
    if(L.p != R.p)
        throw std::invalid_argument("[GF]ERROR: not matching p!");
}

GF::GF(const uint32_t& _p, const uint32_t& _value) noexcept{
    p = _p;
    value = _value % p;
}

uint32_t GF::getP() const noexcept{
    return p;
}
void GF::setP(uint32_t _p) {
    p = _p;
}

uint32_t GF::getVal() const noexcept{
    return value;
}
void GF::setVal(uint32_t _val) {
    value = _val;
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

GF GF::operator+(const GF &R) const {
    checkP(*this, R);
    uint32_t _val = (value + R.value) % p;
    return GF(R.p, _val);
}






