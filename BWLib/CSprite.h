#pragma once
#pragma once
#include <cstddef>
#include "SpriteNumber.h"

namespace BW
{
  class CImage;

  class CSprite
  {
  public:
    // CLink<CSprite>
    /*0x00*/ CSprite*     prev;
    /*0x04*/ CSprite*     next;
    /*0x08*/ SpriteNumber spriteType;
    /*0x0A*/ u8           creator;      // official, player ID that created this sprite
    /*0x0B*/ u8           selectionIndex; //0 <= selectionIndex <= 11. Index in the selection area at bottom of screen.
    /*0x0C*/ u8           visibilityMask;  // Player bits indicating the visibility for a player
    /*0x0D*/ u8           elevation;
    /*0x0E*/ u8           flags;
                          /*    0x01  Draw selection circle.
                                0x02
                                0x04
                                0x08  Selected.
                                0x10
                                0x20  Hidden
                                0x40  Burrowed
                                0x80  Iscript unbreakable code section.
                          */
    /*0x0F*/ u8         selectionFlashTimer;
    /*0x10*/ u16        index;
    /*0x12*/ point<u8>  size;
    /*0x14*/ Position   position;
    /*0x18*/ CImage*    pImagePrimary;    // official
    /*0x1C*/ CImage*    pImageHead;       // official
    /*0x20*/ CImage*    pImageTail;       // official

    //void draw();
  };

  static_assert(sizeof(CSprite) == 36, "BW::CSprite is incorrect.");

  static_assert(offsetof(CSprite, prev) == 0x00, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, next) == 0x04, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, spriteType) == 0x08, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, creator) == 0x0A, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, selectionIndex) == 0x0B, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, visibilityMask) == 0x0C, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, elevation) == 0x0D, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, flags) == 0x0E, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, selectionFlashTimer) == 0x0F, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, index) == 0x10, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, size) == 0x12, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, position) == 0x14, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, pImagePrimary) == 0x18, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, pImageHead) == 0x1C, "CSprite member not at correct offset");
  static_assert(offsetof(CSprite, pImageTail) == 0x20, "CSprite member not at correct offset");
};
