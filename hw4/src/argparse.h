#ifndef _ARGPARSE_H_
#define _ARGPARSE_H_

#include <string>
#include "define.h"

int parse_arguments(
    const int argc,
    const char** argv,
    std::string* goldPath,
    std::string* path,
    uint16_t* mSize,
    int16_t* mAngle,
    float* mK,
    uint16_t* gSize,
    float* gSigma,
    float* gK
);

#endif