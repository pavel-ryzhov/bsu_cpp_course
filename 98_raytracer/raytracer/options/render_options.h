#pragma once

#include <cstdint>

enum class RenderMode : uint8_t { kDepth, kNormal, kFull };

struct RenderOptions {
    int depth{};
    RenderMode mode = RenderMode::kFull;
};
