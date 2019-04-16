//
// Created by wangrl on 19-4-17.
//


#include <cstdlib>
#include "codec/SkCodec.h"

struct DecoderProc {
    bool (*IsFormat)(const void*, size_t);
};

