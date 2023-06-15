#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Graph.h"
#include <chrono>
bool checkArgs(size_t argc, char *argv[])
{
    if(argc != 8) {
        std::cout << "Incorrect number of arguments!" << std::endl;
        return false;
    }
    if(strcmp(argv[1],"dijkstra") != 0 && strcmp(argv[1], "dial") != 0 && strcmp(argv[1],"radixheap") != 0)
    {
        std::cout << R"(Use "dijkstra" or "dial" or "radixheap" as first argument!)" << std::endl;
        return false;
    }
    if(strcmp(argv[2] ,"-d") != 0)
    {
        std::cout << "You forgot -d!" << std::endl;
        return false;
    }
    if(strcmp(argv[4], "-ss")  != 0 && strcmp(argv[4], "-p2p") != 0)
    {
        std::cout << "Use -ss or -p2p option!" << std::endl;
        return false;
    }
    else if((strcmp(argv[4], "-ss") == 0 && strcmp(argv[6],"-oss") != 0)
            || (strcmp(argv[4], "-p2p") == 0 && strcmp(argv[6], "-op2p") != 0))
    {
        std::cout << "Follow -ss with -oss or -p2p with -op2p option!" << std::endl;
        return false;
    }
    // TODO - check file type, aka .*
    return true;
}

bool checkFileExtension(std::string def, std::string sour, std::string res)
{
    if(def.substr(def.find_last_of('.') + 1) != "gr")
    {
        std::cout << "Invalid graph extension!" << std::endl;
        return false;
    }
    if(sour.substr(sour.find_last_of('.') + 1) != "ss"
    && sour.substr(sour.find_last_of('.') + 1) != "p2p")
    {
        std::cout << "Invalid source extension!" << std::endl;
        return false;
    }
    if(res.substr(res.find_last_of('.') + 1) != "res")
    {
        std::cout << "Invalid result extension!" << std::endl;
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if(!checkArgs(argc, argv)){
        return -1;
    }

    std::ifstream graphDefinitionFile, sourceFile;
    std::ofstream resultsFile;

    std::string definitionFileName = argv[3];
    std::string sourceFileName = argv[5];
    std::string resultsFileName = argv[7];
    if(!checkFileExtension(definitionFileName,
                           sourceFileName,
                           resultsFileName)
                           )
    {
        return -1;
    }
    graphDefinitionFile.open(definitionFileName, std::ios::out);
    sourceFile.open(sourceFileName, std::ios::out);
    resultsFile.open(resultsFileName, std::fstream::out);

    if(!graphDefinitionFile.is_open())
    {
        std::cout << "Could not find:" << definitionFileName;
    }
    if(!sourceFile.is_open())
    {
        std::cout << "Could not find:" << sourceFileName;
    }
    if(!resultsFile.is_open())
    {
        std::cout << "Could not find:" << resultsFileName;
    }

    if(graphDefinitionFile.is_open() && sourceFile.is_open() && resultsFile.is_open())
    {
        // create graph from "graphDefinitionFile" file
        Graph *graph = new Graph(graphDefinitionFile);
        // create source list from "sourceFile" file
        if(strcmp(argv[4],"-ss") == 0)
        {
            short mode = 4;
            std::list<size_t> sourceList;
            std::string line;
            std::vector<size_t> results;
            while(getline(sourceFile, line))
            {
                if(line[0] == 's')
                {
                    size_t source = std::stol(line.substr(1, std::string::npos));
                    sourceList.push_back(source);
                }
            }
            if(strcmp(argv[1], "dijkstra") == 0)
            {
                mode = 0;
            }
            else if(strcmp(argv[1], "dial") == 0)
            {
                mode = 1;
            }
            else if(strcmp(argv[1], "radixheap") == 0)
            {
                mode = 2;
            }
            auto start = std::chrono::steady_clock::now();
            size_t listSize = sourceList.size();
            for(auto s : sourceList)
            {
                std::cout << "Working on source: " << s << std::endl;
                sourceList.pop_back();
                graph->getDistance(mode, s);
            }
            auto end = std::chrono::steady_clock::now();

            double t = (double) std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() / (double)sourceList.size();
            resultsFile << "p res sp ss dijkstra\n";
            resultsFile << "f " << argv[3] << " " << argv[5] << '\n';
            resultsFile << "g " << graph->n << " " << graph->m << " " << graph->minCost << " " << graph->maxCost << "\n";
            resultsFile << "t " << t;
            std::cout << std::endl << t << std::endl;
        }
        else
        {
            short mode = 4;
            std::list<std::pair<size_t, size_t>> pairs;
            std::string line;
            while(getline(sourceFile, line))
            {
                size_t i, s, f;
                if(line[0] == 'q')
                {
                    i = line.find(' ', 2);
                    s = std::stol(line.substr(1, i));
                    f = std::stol(line.substr(i + 1, std::string::npos));
                    pairs.emplace_back(s, f);
                }
            }
            if(strcmp(argv[1], "dijkstra") == 0)
            {
                mode = 0;
            }
            else if(strcmp(argv[1], "dial") == 0)
            {
                mode = 1;
            }
            else if(strcmp(argv[1], "radixheap") == 0)
            {
                mode = 2;
            }
            resultsFile << "f " << argv[3] << " " << argv[5] << '\n';
            resultsFile << "g " << graph->n << " " << graph->m << " " << graph->minCost << " " << graph->maxCost << "\n";
            while(!pairs.empty())
            {
                std::cout << "Pairs left:" << pairs.size() << std::endl;
                size_t s = pairs.back().first;
                size_t f = pairs.back().second;
                pairs.pop_back();
                std::vector<size_t> d = graph->getDistance(mode, s);
                resultsFile << "d " << s << " " << f << " " << d[f] << '\n';
            }
        }
    }
    resultsFile.close();
    sourceFile.close();
    graphDefinitionFile.close();

    return 0;
}
