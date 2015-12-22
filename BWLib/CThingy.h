#pragma once
#include <cstddef>
#include "Types.h"

namespace BW
{
  class CSprite;

  /// <summary>A static, unmovable, non-interactive object on the map.</summary>
  class CThingy
  {
  public:
    // CLink<CFlingy> link;
    CThingy* prev;
    CThingy* next;      /**< Pointer to next flingy in the linked list, we use
                        *   it to iterate units/bullets.
                        **/
    s32       xLife;  // Hit Points of unit, note that the displayed value in broodwar is ceil(hitPoints/256)
                      // Set to 1 to indicate existence for non-units. Official.
    CSprite*  sprite;
  };

  static_assert(sizeof(CThingy) == 0x10, "Size of CThingy is incorrect");
#define OFFSET_ASSERT(offset, member) static_assert(offset == offsetof(CThingy, member), "CThingy member not at correct offset")
  OFFSET_ASSERT(0x00, prev);
  OFFSET_ASSERT(0x04, next);
  OFFSET_ASSERT(0x08, xLife);
  OFFSET_ASSERT(0x0C, sprite);
#undef OFFSET_ASSERT
}