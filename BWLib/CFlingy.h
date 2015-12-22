#pragma once
#include <cstddef>

#include "CThingy.h"
#include "Types.h"
#include "Position.h"
#include "Target.h"
#include "OrderType.h"

namespace BW
{
  class CSprite;

  /// <summary>A particle on the game map that can have behaviours.</summary>
  /// A "Flying Thingy".
  class CFlingy : public CThingy
  {
  public:
    // One of these Position structs are just called "swLocX" and "swLocY"
    /*0x010*/ Target    moveTarget;             // The position or unit to move to. It is NOT an order target.
    /*0x018*/ Position  nextMovementWaypoint;   /**< The next way point in the path the unit is following to get to its destination.
                                                * Equal to moveToPos for air units since they don't need to navigate around buildings
                                                * or other units.
                                                */
    /*0x01C*/ Position  nextTargetWaypoint;   // The desired position
    /*0x020*/ u8        movementFlags;        // Flags specifying movement type - defined in BW#MovementFlags.
    /*0x021*/ u8        facingDirection;    // The current direction the flingy is facing
    /*0x022*/ u8        turnSpeed;
    /*0x023*/ u8        movementDirection;  /**< This usually only differs from the currentDirection field for units that can accelerate
                                            *   and travel in a different direction than they are facing. For example Mutalisks can change
                                            *   the direction they are facing faster than then can change the direction they are moving.
                                            */
    /*0x024*/ u16       flingyType;
    /*0x026*/ u8        _unknown_0x026;
    /*0x027*/ u8        flingyMovementType;
    /*0x028*/ Position  position;         // Current position of the flingy
                                          /*0x02C*/ //point         halt;             // @todo Unknown    // Either this or current_speed is officially called "xDX, xDY" (no POINT struct)
    s32 haltX, haltY;
    /*0x034*/ u32 flingyTopSpeed;
    /*0x038*/ s32 currentSpeed;
    /*0x03C*/ s32 nextSpeed;
    /*0x040*/ //point current_speed;
    s32 current_speedX, current_speedY;

    /*0x048*/ u16 acceleration;
    /*0x04A*/ u8  newDirection;
    /*0x04B*/ u8  targetDirection;   // pathing related, gets this value from Path::unk_1A?
    /*0x04C*/ u8  playerOwner;             // Specification of owner of this flingy.
    /*0x04D*/ OrderType orderType;              // Specification of type of order currently given.
    /*0x04E*/ u8  orderState;  //< Additional order info (mostly unknown, wander property investigated so far)  // officially "ubActionState"
                               /*  0x01  Moving/Following Order
                               0x02  No collide (Larva)?
                               0x04  Harvesting? Working?
                               0x08  Constructing Stationary
                               Note: I don't actually think these are flags
                               */
    /*0x04F*/ u8     orderSignal;  /*  0x01  Update building graphic/state
                                   0x02  Casting spell
                                   0x04  Reset collision? Always enabled for hallucination...
                                   0x10  Lift/Land state
                                   */
    /*0x050*/ UnitType orderFoggedUnitType;      // officially "uwFoggedTarget"

    u16 __0x52;  // Unknown. Originally presumed to be padding, but resides on a proper boundary.

    /*0x054*/ u8     mainOrderTimer;       // A timer for orders, example: time left before minerals are harvested
    /*0x055*/ u8     groundWeaponCooldown;
    /*0x056*/ u8     airWeaponCooldown;
    /*0x057*/ u8     spellCooldown;
    /*0x058*/ Target orderTarget;        // officially called ActionFocus
  };

  static_assert(sizeof(CFlingy) == 0x60, "Size of CFlingy is incorrect");

  static_assert(offsetof(CFlingy, moveTarget) == 0x10, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, nextMovementWaypoint) == 0x18, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, nextTargetWaypoint) == 0x1C, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, movementFlags) == 0x20, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, facingDirection) == 0x21, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, turnSpeed) == 0x22, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, movementDirection) == 0x23, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, flingyType) == 0x24, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, _unknown_0x026) == 0x26, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, flingyMovementType) == 0x27, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, position) == 0x28, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, haltX) == 0x2C, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, haltY) == 0x30, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, flingyTopSpeed) == 0x34, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, currentSpeed) == 0x38, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, nextSpeed) == 0x3C, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, current_speedX) == 0x40, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, current_speedY) == 0x44, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, acceleration) == 0x48, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, newDirection) == 0x4A, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, targetDirection) == 0x4B, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, playerOwner) == 0x4C, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, orderType) == 0x4D, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, orderState) == 0x4E, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, orderSignal) == 0x4F, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, orderFoggedUnitType) == 0x50, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, mainOrderTimer) == 0x54, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, groundWeaponCooldown) == 0x55, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, airWeaponCooldown) == 0x56, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, spellCooldown) == 0x57, "CFlingy member not at correct offset");
  static_assert(offsetof(CFlingy, orderTarget) == 0x58, "CFlingy member not at correct offset");
}