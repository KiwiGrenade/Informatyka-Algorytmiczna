package org.example;

import org.jetbrains.annotations.NotNull;

public interface GFI {
    GF instantiate(long _p, long _val);
    void setP(long _p);
    long getP();
    void setVal(long _val);
    long getVal();

    boolean equals(@NotNull GF L, @NotNull GF R);
    boolean notEquals(@NotNull GF L, @NotNull GF R);
    boolean lessThan(@NotNull GF L, @NotNull GF R);
    boolean greaterThan(@NotNull GF L, @NotNull GF R);
    boolean lessThanOrEqual(@NotNull GF L, @NotNull GF R);
    boolean greaterThanOrEqual(@NotNull GF L, @NotNull GF R);

    GF plus();
    GF minus();
    GF add(@NotNull GF L, @NotNull GF R);
    GF subtract(@NotNull GF L, @NotNull GF R);
    GF multiply(@NotNull GF L, @NotNull GF R);
    GF divide(@NotNull GF L, @NotNull GF R);

    void assign(@NotNull GF other);
    void plusAssign(@NotNull GF other);
    void minusAssign(@NotNull GF other);
    void multiplyAssign(@NotNull GF other);
    void divideAssign(@NotNull GF other);
}
