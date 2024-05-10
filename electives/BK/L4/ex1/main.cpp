#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>

struct key_pair {
    int64_t n;
    int64_t e;
    int64_t d;
};

int64_t static gcd_extended(int64_t a, int64_t b, int64_t *x, int64_t *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int64_t x1, y1;
    int64_t d = gcd_extended(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return d;
}

int64_t static gcd(int64_t a, int64_t b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int64_t static random_number(int64_t min, int64_t max) {
    return rand() % (max - min + 1) + min;
}

struct key_pair static generate_rsa_keys(int64_t p, int64_t q) {
    int64_t n = p * q;
    int64_t phi_n = (p - 1) * (q - 1);
    int64_t e;

    do {
        e = random_number(2, phi_n - 1);
    } while (gcd(e, phi_n) != 1);

    int64_t d;
    for (d = 1; d < phi_n; d++) {
        if ((e * d) % phi_n == 1) {
            break;
        }
    }

    struct key_pair result = {n, e, d};
    return result;
}

int main(int argc, char **argv) {
    assert (argc > 2);
    srand((unsigned) time(NULL));

    char *endptr;
    const int64_t p = strtoll(argv[1], &endptr, 10);
    const int64_t q = strtoll(argv[2], &endptr, 10);
    const int64_t phi_n = (p - 1) * (q - 1);
    struct key_pair res = generate_rsa_keys(p, q);
    struct key_pair res2 = generate_rsa_keys(p, q);
    printf("%ld;%ld;%ld\n", res.n, res.e, res.d);
    printf("%ld;%ld;%ld\n", res2.n, res2.e, res2.d);

    int64_t x, y;
    int64_t g = gcd_extended(res2.e, phi_n, &x, &y);
    assert (g == 1);
    int64_t d2;
    d2 = (x % phi_n + phi_n ) % phi_n;
    printf("Wartość d2: %ld\n", d2);
    printf("Wartość y: %ld\n", y);
    return EXIT_SUCCESS;
}
