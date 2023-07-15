#include <iostream>
#include <random>
void printArr(size_t arr[], size_t n) noexcept
{
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

void printArrState(size_t arr[], size_t n) noexcept
{
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int nSwap = 0;
int nComp = 0;
void merge(size_t arr[], size_t p, size_t q, size_t r) noexcept
{
    size_t lenLeft = q - p + 1;
    size_t lenRight = r - q;
    size_t left[lenLeft];
    size_t right[lenRight];

    for(int i = 0; i < lenLeft; i++)
    {
        left[i] = arr[p + i];
    }
    for(int j = 0; j < lenRight; j++)
    {
        right[j] = arr[q + j + 1];
    }

    size_t i = 0;
    size_t j = 0;
    size_t k = p;
    for(;i < lenLeft && j < lenRight; k++, nComp++, nSwap++)
    {
        if(left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
    }
    for(;i < lenLeft; k++, i++)
    {
        nSwap++;
        arr[k] = left[i];
    }
    for(;j < lenRight; k++, j++)
    {
        nSwap++;
        arr[k] = right[j];
    }
}

void mergeSort(size_t arr[], int p, int r, int n) noexcept
{
    if(p < r)
    {
        int q = std::floor((p+r)/2);
        mergeSort(arr, p, q, n);
        mergeSort(arr, q + 1, r, n);
        merge(arr, p, q, r);
        if(n < 40)
        {
            printArrState(arr, n);
        }
    }
}

int main()
{
    std::string line;
    std::cin >> line;
    size_t n = std::stoi(line);
    size_t arr[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> line;
        arr[i] = stol(line);
    }

    if(n < 40)
    {
        std::cout << "Random numbers:" << std::endl;
        printArr(arr, n);
        printArrState(arr, n);
    }

    mergeSort(arr, 0, n-1, n);

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
