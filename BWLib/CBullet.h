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
    /*0x60*/ WeaponType weaponType;
    /*0x61*/ u8         timeRemaining;
    /*0x62*/ u8         flags;            // 0x01 = miss target; 0x02 = no damage (hallucination)
    /*0x63*/ u8         remainingBounces; // Bounce count for mutalisk weapon (official name: ubChain)
    /*0x64*/ CUnit*     sourceUnit;
    /*0x68*/ CUnit*     nextBounceUnit;   // Next unit for bounce, temporary
    /*0x6C*/ u8         spreadSeed;       // some sort of cyclic burst counter (used by valkyries, goliath air attack)
  };

  static_assert(sizeof(CBullet) == 112, "BW::CBullet is incorrect.");

  static_assert(offsetof(CBullet, weaponType) == 0x60, "CBullet member not at correct offset");
  static_assert(offsetof(CBullet, timeRemaining) == 0x61, "CBullet member not at correct offset");
  static_assert(offsetof(CBullet, flags) == 0x62, "CBullet member not at correct offset");
  static_assert(offsetof(CBullet, remainingBounces) == 0x63, "CBullet member not at correct offset");
  static_assert(offsetof(CBullet, sourceUnit) == 0x64, "CBullet member not at correct offset");
  static_assert(offsetof(CBullet, nextBounceUnit) == 0x68, "CBullet member not at correct offset");
  static_assert(offsetof(CBullet, spreadSeed) == 0x6C, "CBullet member not at correct offset");
}