#pragma once
#include "Types.h"

namespace BW
{
  enum class RLEType : u8
  {
    Normal = 0x0,
    NormalSpecial = 0x1,
    Cloaking = 0x2,
    Cloak = 0x3,
    Decloaking = 0x4,
    DetectedCloaking = 0x5,
    DetectedCloak = 0x6,
    DetectedDecloaking = 0x7,
    Remap = 0x9,  // effect
    Shadow = 0xa,       // RLE_SHADOW
    HpFloatDraw = 0xb,  // RLE_HPFLOATDRAW
    WarpIn = 0xc,
    SelectionCircle = 0xd,  // outline
    OverrideColor = 0xe, // Flag, RLE_PLAYER_SIDE
    Hallucination = 0x10,
    WarpFlash = 0x11  // fire?
  };
}
