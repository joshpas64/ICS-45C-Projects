#include <functional>
#include <string>

#ifndef HASHFUNCTION_HPP
#define HASHFUNCTION_HPP

typedef std::function<unsigned int(const std::string &key)> HashFunction;

unsigned int simpleHash(const std::string &key);
unsigned int ELFHash(const std::string &key);
unsigned int DJBHash(const std::string &key); //overflow error -_____-
#endif