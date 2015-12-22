#pragma once
#include "Types.h"

namespace BW
{
  /// <summary>Image frame in a GRP file.</summary>
  struct GraphicFrame
  {
    s8  x, y;
    s8  wid, hgt;
    u32 dataOffset;
  };

  /// <summary>Header of a GRP file.</summary>
  struct GraphicHeader
  {
    u16           wFrames;  // official
    s16           width, height;
    GraphicFrame  frames[1];
  };

}
