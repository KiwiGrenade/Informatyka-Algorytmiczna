//
// Created by jaskow on 06.04.24.
//

#ifndef JPP_L2_GF_HPP
#define JPP_L2_GF_HPP

#include <cstdint>

class GF {
private:
    int64_t p;
    int64_t value;
    static void checkP(const GF& L, const GF& R);

public:
    explicit GF(const int64_t& _p, const int64_t& _value) noexcept;
    ~GF() = default;

    [[nodiscard]] int64_t getP() const;
    // TODO: !Check if p in GF class should be unsigned!
    void setP(int64_t _p);

    // compare
    bool operator == (const GF &R) const;
    bool operator != (const GF &R) const;
    bool operator <  (const GF &R) const;
    bool operator >  (const GF &R) const;
    bool operator <= (const GF &R) const;
    bool operator >= (const GF &R) const;
};

#endif //JPP_L2_GF_HPP
