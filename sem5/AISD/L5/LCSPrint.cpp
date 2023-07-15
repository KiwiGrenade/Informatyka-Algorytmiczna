#include <iostream>

void LCS(char *X, size_t m, char *Y, size_t n) {
    size_t nRow = m + 1;
    size_t nCol = n + 1;

    // 2D table
    size_t **L = new size_t *[nRow];
    for (size_t i = 0; i < nRow; i++) {
        L[i] = new size_t[nCol];
    }

    // LCS
    for (size_t i = 0; i <= m; i++) {
        for (size_t j = 0; j <= n; j++) {
            // prefix is empty
            if (i == 0 || j == 0) {
                L[i][j] = 0;
            }
                // X and Y have the same char
            else if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = std::max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    size_t index = L[m][n];
    char seq[index + 1];
    // null terminate the array
    seq[index] = 0;

    // create subsequence array from bottom up
    for (size_t i = m, j = n; index != 0;) {
        // chars are the same => go up and right
        if (X[i - 1] == Y[j - 1]) {
            seq[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
            // L_left > L_top --> go right
        else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        }
            // L_left <= L_top --> go top
        else {
            j--;
        }
    }

    // print
    if (m < 50 && n < 50) {
        std::cout << "SEQ X: " << X << std::endl
                  << "SEQ Y: " << Y << std::endl
                  << "LCS: " << seq << std::endl
                  << "size: " << L[m][n] << std::endl;
    }

    // free space
    for (size_t i = 0; i < nRow; i++) {
        delete[] L[i];
    }
    delete[] L;
}

int main(int argc, char *argv[]) {
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);

    char X[n + 1];
    char Y[n + 1];
    X[n] = 0;
    Y[n] = 0;

    // initialize array X
    for (size_t i = 0; i < n; i++) {
        std::cin >> line;
        X[i] = line[0];
    }
    // initialize array Y
    for (size_t i = 0; i < n; i++) {
        std::cin >> line;
        Y[i] = line[0];
    }

    LCS(X, n, Y, n);

    return 0;
}
