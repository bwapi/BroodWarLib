#pragma once

#include "Position.h"

namespace BW
{
  class CUnit;

  /** The BW::Target structure is a position followed by a unit pointer. This structure is common
  *  and seen in CUnit, CBullet, COrder, CAIControl, AI Captain, and others.
  */
  struct Target
  {
    Position  pt;       // official name
    CUnit*    pUnit;
  };

  static_assert(sizeof(Target) == 8, "Target size is incorrect");
}
