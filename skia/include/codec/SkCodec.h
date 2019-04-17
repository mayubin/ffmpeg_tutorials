//
// Created by wangrl on 19-4-17.
//

#pragma once

#include "private/SkNoncopyable.h"

class SkColorSpace;
class SkData;
class SkFrameHolder;
class SkPngChunkReader;
class SkSampler;

namespace DM {
    class CodecSrc;
    class ColorCodecSrc;
}

/**
 * Abstraction layer directly on top of an image codec.
 */

