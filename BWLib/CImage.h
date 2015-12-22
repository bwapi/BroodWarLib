#pragma once
#include "Types.h"
#include "IScriptAnimation.h"
#include "RLEType.h"
#include "ImageNumber.h"
#include <cstddef>

namespace BW
{
  class GraphicHeader;
  class GraphicFrame;
  class CSprite;

  class CImage
  {
  public:

    using DrawFunction = void __fastcall (int screenX, int screenY, GraphicFrame* pFrame, rect<s16>* grpRect, void* param);
    using UpdateFunction = void __fastcall (CImage* img);

    //void updateGraphicData();
    //void drawImage();

    //grpFrame      *getCurrentFrame() const;
    //BW::Position  getPosition() const;

    /*0x00*/ CImage*      prev;
    /*0x04*/ CImage*      next;
    /*0x08*/ ImageNumber  imageNumber;    // officially "uwNo"
    /*0x0A*/ RLEType      drawType;    // officially "ubRLE"
    /*0x0B*/ u8           direction;
    /*0x0C*/ u16          flags;
    /*  0x0001  - Redraw
        0x0002  - Flipped/Mirrored
        0x0004  - FreezeY
        0x0008  - Has rotation frames
        0x0010  - FullIScript
        0x0020  - Clickable
        0x0040  - Hidden/Invisible (don't draw)
        0x0080  - UseParentLO
        */
    /*0x0E*/ point<s8>        offset;
    /*0x10*/ u16              iscriptHeader;
    /*0x12*/ u16              iscriptOffset;
    /*0x14*/ u16              iscriptReturnPosition;
    /*0x16*/ IScriptAnimation anim;
    /*0x17*/ u8               sleep;        // iscript sleep time
    /*0x18*/ u16              frameSet;
    /*0x1A*/ u16              frameIndex;
    /*0x1C*/ Position         mapPosition;
    /*0x20*/ Position         screenPosition;
    /*0x24*/ rect<s16>        grpBounds;      // Bounds for GRP frame, only different from normal when part of graphic is out of bounds.
    /*0x2C*/ GraphicHeader*   GRPFile;
    /*0x30*/ void*            drawFunctionParam;
    /*0x34*/ DrawFunction*    drawFunction;    // official
    /*0x38*/ UpdateFunction*  updateFunction; // official
    /*0x3C*/ CSprite*         parent;
  };

  static_assert(sizeof(CImage) == 64, "BW::CImage is incorrect.");

  static_assert(offsetof(CImage, prev) == 0x00, "CImage member not at correct offset");
  static_assert(offsetof(CImage, next) == 0x04, "CImage member not at correct offset");
  static_assert(offsetof(CImage, imageNumber) == 0x08, "CImage member not at correct offset");
  static_assert(offsetof(CImage, drawType) == 0x0A, "CImage member not at correct offset");
  static_assert(offsetof(CImage, direction) == 0x0B, "CImage member not at correct offset");
  static_assert(offsetof(CImage, flags) == 0x0C, "CImage member not at correct offset");
  static_assert(offsetof(CImage, offset) == 0x0E, "CImage member not at correct offset");
  static_assert(offsetof(CImage, iscriptHeader) == 0x10, "CImage member not at correct offset");
  static_assert(offsetof(CImage, iscriptOffset) == 0x12, "CImage member not at correct offset");
  static_assert(offsetof(CImage, iscriptReturnPosition) == 0x14, "CImage member not at correct offset");
  static_assert(offsetof(CImage, anim) == 0x16, "CImage member not at correct offset");
  static_assert(offsetof(CImage, sleep) == 0x17, "CImage member not at correct offset");
  static_assert(offsetof(CImage, frameSet) == 0x18, "CImage member not at correct offset");
  static_assert(offsetof(CImage, frameIndex) == 0x1A, "CImage member not at correct offset");
  static_assert(offsetof(CImage, mapPosition) == 0x1C, "CImage member not at correct offset");
  static_assert(offsetof(CImage, screenPosition) == 0x20, "CImage member not at correct offset");
  static_assert(offsetof(CImage, grpBounds) == 0x24, "CImage member not at correct offset");
  static_assert(offsetof(CImage, GRPFile) == 0x2C, "CImage member not at correct offset");
  static_assert(offsetof(CImage, drawFunctionParam) == 0x30, "CImage member not at correct offset");
  static_assert(offsetof(CImage, drawFunction) == 0x34, "CImage member not at correct offset");
  static_assert(offsetof(CImage, updateFunction) == 0x38, "CImage member not at correct offset");
  static_assert(offsetof(CImage, parent) == 0x3C, "CImage member not at correct offset");
}
