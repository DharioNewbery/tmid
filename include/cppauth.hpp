#pragma once 
#include <map>
#include <string>
#include <vector>
#include <ranges>
#include <fstream>
#include <sstream>
#include <memory>
#include <concepts>
#include <type_traits>


// Essa função também deve ser movido para algum lugar mais conveniente 
template<typename T>
std::streampos getFileSize(T& file){
    static_assert(
        std::is_same<T, std::ifstream> ||
        std::is_same<T, std::ofstream> ||
        std::is_same<T, std::fstream>,
        "The type has to be a file type"
    );

    if (!file.is_open())
        throw std::runtime_error("The current file is not open");
    
    File.seekg(std::ios_base::end);
    std::streampos fileSize = dbFile.tellg();
    File.seekg(std::ios_base::beg);

    return fileSize;
}


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

        std::streampos fileSize = getFileSize<std::ifstream>(dbFile);
        
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
        std::map<uint16_t, std::string>::iterator search = clientMap.find(pin);
        if ( search == clientMap.end())
            throw std::runtime_error("There is no pair with the current key");
        
        clientMap.erase(search);
        
    }
    void addMap(uint16_t pin, std::string clientData){
        std::map<uint16_t, std::string>::iterator search = clientMap.find(pin);
        
        if ( search == clientMap.end())
            throw std::runtime_error("The curremt key already exist");
        
            std::pair<uint16_t, std::string> newPair(pin, clientData);
        
        clientMap.insert(newPair);
    }

    bool containsClient(uint16_t pin){
        std::map<uint16_t, std::string>::iterator search = clientMap.find(pin);
        
        return search != clientMap.end();
    }

    std::string getClientContent(uint16_t pin){
        std::map<uint16_t, std::string>::iterator search = clientMap.find(pin);
        
        if (search == clientMap.end()) throw std::runtime_error("The current client is not on the map");
        
        return clientMap[pin];
    }  
private:
    std::map<uint16_t, std::string> clientMap; 
};


/*

Dhario! Penso na lógica dessa forma -> Adicionar a root do tmid a pasta data/ e então o "DB" seria o nome do group.txt 

Coloque esse parte do código em algum lugar mais conveniente !

*/




