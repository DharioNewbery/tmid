#pragma once 

#include <HeaderBuilder.hpp>


#define globalHeader_TABLE_(X)  \
    X(size_t, packagesize)      

ObjectBuilder(globalHeader)
HeaderBuilder(globalHeader)

#define localHeader_TABLE_(X)   \
    X(std::string, relativepath)

ObjectBuilder(localHeader)
HeaderBuilder(localHeader)
