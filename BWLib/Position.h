#pragma once

#include "Types.h"

namespace BW
{
  struct Position
  {
    s16 x, y;
  };

  static_assert(sizeof(Position) == 4, "Position size is incorrect");
}
