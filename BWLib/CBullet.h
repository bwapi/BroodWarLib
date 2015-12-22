#pragma once
#include <cstddef>

#include "CFlingy.h"
#include "Types.h"
#include "CUnit.h"
#include "WeaponType.h"

namespace BW
{
  class CBullet : public CFlingy
  {
  public:
    WeaponType weaponType;
    u8         timeRemaining;
    u8         flags;            // 0x01 = miss target; 0x02 = no damage (hallucination)
    u8         remainingBounces; // Bounce count for mutalisk weapon (official name: ubChain)
    CUnit*     sourceUnit;
    CUnit*     nextBounceUnit;   // Next unit for bounce, temporary
    u8         spreadSeed;       // some sort of cyclic burst counter (used by valkyries, goliath air attack)
  };

  static_assert(sizeof(CBullet) == 112, "BW::CBullet is incorrect.");
#define OFFSET_ASSERT(offset, member) static_assert(offset == offsetof(CBullet, member), "CBullet member not at correct offset")
  OFFSET_ASSERT(0x60, weaponType);
  OFFSET_ASSERT(0x61, timeRemaining);
  OFFSET_ASSERT(0x62, flags);
  OFFSET_ASSERT(0x63, remainingBounces);
  OFFSET_ASSERT(0x64, sourceUnit);
  OFFSET_ASSERT(0x68, nextBounceUnit);
  OFFSET_ASSERT(0x6C, spreadSeed);
#undef OFFSET_ASSERT
}