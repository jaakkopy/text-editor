#ifndef MACROS_HPP
#define MACROS_HPP

#include <cstdlib>
#include <cstdio>

#define CHECK(rv, error_code, msg) if (rv == error_code) {perror(msg); exit(1);}
#define CTRL_KEY(key) (key & 0b00011111)

#endif