#include <iostream>

std::size_t randomSelect(const size_t arr[], const std::size_t n, const std::size_t k)
{
    std::size_t
        up = n / 2,
        down = 0,
        nComp = 0;

    while( up >= down)
    {
        nComp++;
        std::size_t pivot = (down + up) / 2;
        if(k == arr[pivot])
        {
            return true;
        }
        else if (k > arr[pivot])
        {
            down = pivot + 1;
        }
        else
        {
            up = pivot - 1;
        }
    }

    std::cout << "Num. of comparisons: " << nComp << std::endl;

    return false;
}

void printArrState(std::size_t arr[], std::size_t n) noexcept
{
    for (std::size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    std::size_t v = std::stol(argv[1]);
    std::string line;
    std::cin >> line;
    std::size_t n = std::stol(line);
    std::size_t arr[n];
    std::cout << "Number we're looking for: " << v  << " " << n << std::endl;

    // initialize array
    for (std::size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        arr[i] = stol(line);
    }

    if(n < 40)
    {
        std::cout << "Array: ";
        printArrState(arr, n);
    }
    bool contains = randomSelect(arr, n, v);
    std::cout << "Does array contain "<< v << " ? " << contains << std::endl;

    return 0;
}
