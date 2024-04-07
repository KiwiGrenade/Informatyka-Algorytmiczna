//
// Created by jaskow on 06.04.24.
//

#include <stdexcept>
#include "GF.hpp"

GF::GF(const int64_t& _p, const int64_t& _value) noexcept{
    p = _p;
    value = _value;
}

void GF::checkP(const GF& L, const GF& R) {
    if(L.p != R.p)
        throw std::invalid_argument("ERROR: not matching p!");
}

bool GF::operator==(const GF &R) const {
    checkP(*this, R);
    return this->value == R.value;
}

bool GF::operator!=(const GF &R) const {
    return !(*this == R);
}

int64_t GF::getP() const {
    return this->p;
}




