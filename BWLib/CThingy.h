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
    /*0x000*/ CThingy* prev;
    /*0x004*/ CThingy* next;      /**< Pointer to next flingy in the linked list, we use
                                  *   it to iterate units/bullets.
                                  **/
    /*0x008*/ s32       hitPoints;  // Hit Points of unit (or bullet existence), note that the displayed value in broodwar is ceil(hitPoints/256)
                                    // Officially called "xLife"
    /*0x00C*/ CSprite*  sprite;
  };

  static_assert(sizeof(CThingy) == 0x10, "Size of CThingy is incorrect");

  static_assert(offsetof(CThingy, prev) == 0x00, "CThingy member not at correct offset");
  static_assert(offsetof(CThingy, next) == 0x04, "CThingy member not at correct offset");
  static_assert(offsetof(CThingy, hitPoints) == 0x08, "CThingy member not at correct offset");
  static_assert(offsetof(CThingy, sprite) == 0x0C, "CThingy member not at correct offset");
}