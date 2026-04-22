#pragma once 
#include <map>
#include <string>
#include <vector>
#include <ranges>
#include <fstream>
#include <sstream>
#include <exception>

class Auth{
public:
    Auth():clientMap(std::map<uint16_t, std::string>()){}
    void saveMap(std::string dbName){
        std::ofstream dbFile(dbName);
        
        if ( !dbFile.is_open() )
            throw std::runtime_error("Fail to open the file");

        std::stringstream stream;

        for (auto const& [key, value] : clientMap){
            stream << key << " " << value << "\n";
        }

        dbFile << stream.str();
        if (dbFile.fail())
            throw std::runtime_error("Fail to save the map");

        dbFile.close();
    }

    void getMap(std::string dbName){
        std::map<uint16_t, std::string> contentMap;

        std::ifstream dbFile(dbName);
        
        if ( !dbFile.is_open() )
            throw std::runtime_error("Fail to open the file");

        dbFile.seekg(std::ios_base::end);
        std::streampos fileSize = dbFile.tellg();
        dbFile.seekg(std::ios_base::beg);

        std::string fileContent;
        fileContent.resize(fileSize);

        dbFile.read(fileContent.data(), fileSize);

        if ( dbFile.fail() )
            throw std::runtime_error("Fail to read from the file");
        
        std::stringstream stream;
        stream << fileContent;
        std::string strPair;
        
        while ( std::getline(stream, strPair, '\n') ) {
            size_t pos = strPair.find(' ');
            
            if (pos == std::string::npos) continue;

            std::pair<uint16_t, std::string> pair;
            pair.first = (uint16_t)std::stoul(strPair.substr(0, pos));
            pair.second = strPair.substr(pos + 1,  strPair.size() - (pos + 1) );        
            clientMap.insert(pair);
        }

        dbFile.close();
    }

    void popMap(uint16_t pin){
        auto search = clientMap.find(pin);
        if ( search == clientMap.end())
            throw std::runtime_error("There is no pair with the current key");
        
        clientMap.erase(search);
        
    }
    void addMap(uint16_t pin, std::string clientData){
        auto search = clientMap.find(pin);
        if ( search == clientMap.end())
            throw std::runtime_error("The curremt key already exist");
        std::pair<uint16_t, std::string> newPair(pin, clientData);
        clientMap.insert(newPair);
    }

private:
    std::map<uint16_t, std::string> clientMap; 
};