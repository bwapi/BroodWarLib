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
    CSprite*     prev;
    CSprite*     next;
    SpriteNumber spriteType;
    u8           creator;      // official, player ID that created this sprite
    u8           selectionIndex; //0 <= selectionIndex <= 11. Index in the selection area at bottom of screen.
    u8           visibilityMask;  // Player bits indicating the visibility for a player
    u8           elevation;
    u8           flags;
                 /*    0x01  Draw selection circle.
                       0x02
                       0x04
                       0x08  Selected.
                       0x10
                       0x20  Hidden
                       0x40  Burrowed
                       0x80  Iscript unbreakable code section.
                 */
    u8         selectionFlashTimer;
    u16        index;
    point<u8>  size;
    Position   position;
    CImage*    pImagePrimary;    // official
    CImage*    pImageHead;       // official
    CImage*    pImageTail;       // official

    //void draw();
  };

  static_assert(sizeof(CSprite) == 36, "BW::CSprite is incorrect.");
#define OFFSET_ASSERT(offset, member) static_assert(offset == offsetof(CSprite, member), "CSprite member not at correct offset")
  OFFSET_ASSERT(0x00, prev);
  OFFSET_ASSERT(0x04, next);
  OFFSET_ASSERT(0x08, spriteType);
  OFFSET_ASSERT(0x0A, creator);
  OFFSET_ASSERT(0x0B, selectionIndex);
  OFFSET_ASSERT(0x0C, visibilityMask);
  OFFSET_ASSERT(0x0D, elevation);
  OFFSET_ASSERT(0x0E, flags);
  OFFSET_ASSERT(0x0F, selectionFlashTimer);
  OFFSET_ASSERT(0x10, index);
  OFFSET_ASSERT(0x12, size);
  OFFSET_ASSERT(0x14, position);
  OFFSET_ASSERT(0x18, pImagePrimary);
  OFFSET_ASSERT(0x1C, pImageHead);
  OFFSET_ASSERT(0x20, pImageTail);
#undef OFFSET_ASSERT
};
