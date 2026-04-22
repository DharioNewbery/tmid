#pragma once 

#include <HeaderBuilder.hpp>

#define userHeader_TABLE_(X)        \
    X(std::string, userOperation)   \
    X(uint16_t, userPin)        

ObjectBuilder(userHeader)
HeaderBuilder(userHeader)

#define globalHeader_TABLE_(X)  \
    X(size_t, packagesize)      

ObjectBuilder(globalHeader)
HeaderBuilder(globalHeader)

#define localHeader_TABLE_(X)   \
    X(std::string, relativepath)

ObjectBuilder(localHeader)
HeaderBuilder(localHeader)
