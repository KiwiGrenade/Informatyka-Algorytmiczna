#include <iostream>
#include <random>
#include <list>
void printArr(size_t arr[], size_t n) noexcept
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

void printArrState(size_t arr[], size_t n) noexcept
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

size_t nSwap = 0;
size_t nComp = 0;

void count(size_t arr[], long low, long high, size_t n) noexcept {
    if(low > high)
    {
        return;
    }
    long p;
    long q;

    nComp++;
    if(arr[high] < arr[low])
    {
        p = arr[high];
        q = arr[low];
    }
    else
    {
        p = arr[low];
        q = arr[high];
    }
    long i = low + 1;
    long k = high - 1;
    long j = i;
    long d = 0;
    while(j <= k)
    {
        nComp++;
        if(d >= 0)
        {
            nComp+=2;
            if(arr[j] < p)
            {
                nSwap++;
                std::swap(arr[i], arr[j]);
                i++;
                j++;
                d++;
            }
            else if(arr[j] < q)
            {
                j++;
            }
            else
            {
                nSwap++;
                std::swap(arr[j], arr[k]);
                k--;
                d--;
            }
        }
        else if(arr[k] > q)
        {
            k--;
            d--;
        }
        else
        {
            nComp++;
            if(arr[k] < p)
            {
                nSwap += 3;
                long tmp = arr[k];
                arr[k] = arr[j];
                arr[j] = arr[i];
                arr[i] = tmp;
                i++;
                d++;
            }
            else
            {
                nSwap++;
                std::swap(arr[j], arr[k]);
            }
            j++;
        }
    }
    nSwap += 4;
    arr[low] = arr[i-1];
    arr[i-1] = p;
    arr[high] = arr[k+1];
    arr[k+1] = q;
    if(n < 40)
    {
        printArrState(arr, n);
    }
    count(arr, low, i - 2, n);
    count(arr, i, k, n);
    count(arr, k + 2, high, n);
}

int main(int argc, char* argv[])
{
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);
    size_t arr[n];
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        arr[i] = stol(line);
    }
    if(n < 40)
    {
        std::cout << "Random numbers:" << std::endl;
        printArr(arr, n);
    }

    count(arr, 0, n - 1, n);

    if(n < 40)
    {
        std::cout << std::endl << "Sorted array:" << std::endl;
        printArr(arr, n);
    }
    std::cout << "Number of comparisons: " << nComp << std::endl;
    std::cout << "Number of swaps: " << nSwap << std::endl;
    std::cout << "Is array sorted: " << std::is_sorted(arr,arr+n-1) << std::endl;

    return 0;
}
