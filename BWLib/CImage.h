#pragma once
#include "Types.h"
#include "IScriptAnimation.h"
#include "RLEType.h"
#include "ImageNumber.h"
#include "CList.h"

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

    CLink<CImage> link;
    ImageNumber   imageNumber;    // officially "uwNo"
    RLEType       drawType;    // officially "ubRLE"
    u8            direction;
    u16           flags;
                  /*  0x0001  - Redraw
                      0x0002  - Flipped/Mirrored
                      0x0004  - FreezeY
                      0x0008  - Has rotation frames
                      0x0010  - FullIScript
                      0x0020  - Clickable
                      0x0040  - Hidden/Invisible (don't draw)
                      0x0080  - UseParentLO
                  */
    point<s8>        offset;
    u16              iscriptHeader;
    u16              iscriptOffset;
    u16              iscriptReturnPosition;
    IScriptAnimation anim;
    u8               sleep;        // iscript sleep time
    u16              frameSet;
    u16              frameIndex;
    Position         mapPosition;
    Position         screenPosition;
    rect<s16>        grpBounds;      // Bounds for GRP frame, only different from normal when part of graphic is out of bounds.
    GraphicHeader*   GRPFile;
    void*            drawFunctionParam;
    DrawFunction*    drawFunction;    // official
    UpdateFunction*  updateFunction;  // official
    CSprite*         parent;
  };

  static_assert(sizeof(CImage) == 64, "BW::CImage is incorrect.");
#define OFFSET_ASSERT(offset, member) static_assert(offset == offsetof(CImage, member), "CImage member not at correct offset")
  OFFSET_ASSERT(0x00, link);
  OFFSET_ASSERT(0x08, imageNumber);
  OFFSET_ASSERT(0x0A, drawType);
  OFFSET_ASSERT(0x0B, direction);
  OFFSET_ASSERT(0x0C, flags);
  OFFSET_ASSERT(0x0E, offset);
  OFFSET_ASSERT(0x10, iscriptHeader);
  OFFSET_ASSERT(0x12, iscriptOffset);
  OFFSET_ASSERT(0x14, iscriptReturnPosition);
  OFFSET_ASSERT(0x16, anim);
  OFFSET_ASSERT(0x17, sleep);
  OFFSET_ASSERT(0x18, frameSet);
  OFFSET_ASSERT(0x1A, frameIndex);
  OFFSET_ASSERT(0x1C, mapPosition);
  OFFSET_ASSERT(0x20, screenPosition);
  OFFSET_ASSERT(0x24, grpBounds);
  OFFSET_ASSERT(0x2C, GRPFile);
  OFFSET_ASSERT(0x30, drawFunctionParam);
  OFFSET_ASSERT(0x34, drawFunction);
  OFFSET_ASSERT(0x38, updateFunction);
  OFFSET_ASSERT(0x3C, parent);
#undef OFFSET_ASSERT
}
