#pragma once

#include <string>
#include <sstream>
#include <string.h>
#include <exception>
#include <vector>


template<typename T>
void parser(std::string value, T& t){
    throw std::runtime_error("not implemented for type");
}

template<>
void parser(std::string value, float& t){
    t = std::stof(value);
}

template<>
void parser(std::string value, int& t){
    t = std::stoi(value);
}

template<>
void parser(std::string value, double& t){
    t = std::stod(value);
}

template<>
void parser(std::string value, long& t){
    t = std::stol(value);
}

template<>
void parser(std::string value, long long& t){
    t = std::stoll(value);
}

template<>
void parser(std::string value, long double& t){
    t = std::stold(value);
}

template<>
void parser(std::string value, unsigned long& t){
    t = std::stoul(value);
}

template<>
void parser(std::string value, unsigned long long& t ){
    t = std::stoull(value);
}

template<>
void parser(std::string value, std::string& t ){
    t = value;
}


#define HB_FIELD(type, name)  type name;

#define HB_STR(type, name)    stream << #name << ":" << name << "\r\n";

#define HB_FUNC(type, name)  if (std::string(label) == #name ) {parser(std::string(content), object.name);} 


#define ObjectBuilder(header_name)                                                          \
struct header_name##Object{                                                                 \
    header_name##_TABLE_(HB_FIELD)                                                          \
    std::string serializer(){                                                               \
        std::stringstream stream;                                                           \
        header_name##_TABLE_(HB_STR)                                                        \
        stream << "\r\n";                                                                   \
        return stream.str();                                                                \
    }                                                                                       \
    std::vector<char> serializer_bytes(){                                                   \
        std::stringstream stream;                                                           \
        header_name##_TABLE_(HB_STR)                                                        \
        stream << "\r\n";                                                                   \            
        std::string st = stream.str();                                                      \
        return  std::vector<char>(st.begin(), st.end());                                    \
    }                                                                                       \
};                                                                                          \  

#define HeaderBuilder(header_name)                                                          \  
class header_name##Builder{                                                                 \
public:                                                                                     \
    header_name##Builder()                                                                  \
    {}                                                                                      \
    header_name##Object deserializer(std::string header){                                   \            
        return deserializer_(header);                                                       \
    }                                                                                       \
    header_name##Object deserializer(std::vector<char> header){                             \   
        return deserializer_(std::string(header.begin(), header.end()));                    \                                                                
    }                                                                                       \                                                                  
private:                                                                                    \
    header_name##Object deserializer_(std::string header){                                  \
        header_name##Object object;                                                         \
        char* save_pointer;                                                                 \
        char* header_st = new char[header.size() + 1];                                      \
        memcpy(header_st, header.c_str(), header.size());                                   \
        char* line = strtok_r(header_st, "\r\n", &save_pointer);                            \
        while (line != NULL){                                                               \
            char* delimeter = strchr(line, ':');                                            \
            if(delimeter != NULL){                                                          \
                delimeter[0] = '\0';                                                        \
                char* label = line;                                                         \
                char* content = delimeter + 1;                                              \
                header_name##_TABLE_(HB_FUNC)                                               \                                                   
            }                                                                               \
            line = strtok_r(NULL, "\r\n", &save_pointer);                                   \
        }                                                                                   \
        delete header_st;                                                                   \  
        return object;                                                                      \
    }                                                                                       \                   
};

