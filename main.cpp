#include <iostream>
#include <fstream>
int main()
{
    std::ifstream testVector;
    testVector.open("tests/2/g2a-1.txt", std::ios::out);
    if (testVector.is_open())
    {
        bool directed;
        size_t v, u;
        std::string line;
        getline(testVector, line);
        line == "D" ? directed = true : directed = false;
        getline(testVector, line);
        v = std::stol(line);
        getline(testVector, line);
        u = std::stol(line);
        while(getline(testVector, line))
        {
            size_t i, v1, v2;
            i = line.find(1,' ');
            v1 = std::stol(line.substr(0, i - 1));
            v2 = std::stol(line.substr(i + 1, std::string::npos));

        }
    }
    else
    {
        std::cout << "Something went wrong. Could not open the file." << std::endl;
    }
    return 0;
}
