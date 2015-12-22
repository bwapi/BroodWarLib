#pragma once
#include <cstddef>
#include "Types.h"

#include "Position.h"
#include "Target.h"
#include "UnitMovementState.h"
#include "UnitType.h"
#include "OrderType.h"
#include "ResourceType.h"
#include "CFlingy.h"
#include "UpgradeType.h"
#include "TechType.h"

namespace BW
{
  // Forwards
  class CSprite;
  class COrder;

  /// <summary>Game unit.</summary>
  ///
  /// Additional notes: possibly missing a "Cloaked" link, has a static member "nSorted"
  class CUnit : public CFlingy
  {
  public:
    //const CUnit* getDamageDealer() const;

    //bool isAttacking() const;
    //int getGroundWeaponCooldown() const;
    //int getAirWeaponCooldown() const;

    /*0x060*/ u32      shields;      // BW shows this value/256, possibly not u32?
    /*0x064*/ UnitType unitType;        // Specifies the type of unit.

    // CLink<CUnit> player_link;
    /*0x068*/ CUnit*  previousPlayerUnit;
    /*0x06C*/ CUnit*  nextPlayerUnit;

    /*0x070*/ CUnit*  subUnit;

    // CLink<COrder> orderQueue_link;
    /*0x074*/ COrder* orderQueueHead;
    /*0x078*/ COrder* orderQueueTail;

    /*0x07C*/ CUnit*  autoTargetUnit;      // The auto-acquired target (Note: This field is actually used for different targets internally, especially by the AI)
    /*0x080*/ CUnit*  connectedUnit;       // Addon is connected to building (addon has conntected building, but not in other direction  (officially "pAttached")
    /*0x084*/ u8      orderQueueCount;      // @todo Verify   // officially "ubQueuedOrders"
    /*0x085*/ u8      orderQueueTimer;      // counts/cycles down from from 8 to 0 (inclusive). See also 0x122.
    /*0x086*/ u8      _unknown_0x086;       // pathing related?
    /*0x087*/ u8      attackNotifyTimer;    // Prevent "Your forces are under attack." on every attack
    /*0x088*/ UnitType previousUnitType;     // Stores the type of the unit prior to being morphed/constructed
    /*0x08A*/ u8      lastEventTimer;       // countdown that stops being recent when it hits 0 
    /*0x08B*/ u8      lastEventColor;       // 17 = was completed (train, morph), 174 = was attacked
    /*0x08C*/ u16     _unused_0x08C;        // might have originally been RGB from lastEventColor
    /*0x08E*/ u8      rankIncrease;         // Adds this value to the unit's base rank
    /*0x08F*/ u8      killCount;            // Killcount
    /*0x090*/ u8      lastAttackingPlayer;  // the player that last attacked this unit
    /*0x091*/ u8      secondaryOrderTimer;
    /*0x092*/ u8      AIActionFlag;           // Internal use by AI only
    /*0x093*/ u8      userActionFlags;        // some flags that change when the user interacts with the unit
                                              // 2 = issued an order, 3 = interrupted an order, 4 = self destructing

    /*0x094*/ u16         currentButtonSet;       // The u16 is a guess, used to be u8
    /*0x096*/ bool        isCloaked;
    /*0x097*/ UnitMovementState movementState;          // A value based on conditions related to pathing, see Path.h for info
    /*0x098*/ UnitType    buildQueue[5];          //< Queue of units to build. Note that it doesn't begin with index 0, but with #buildQueueSlot index. 
    /*0x0A2*/ u16         energy;                 //< Energy Position   // officially "xwMagic"
    /*0x0A4*/ u8          buildQueueSlot;         //< Index of active unit in #buildQueue. 
    /*0x0A5*/ u8          uniquenessIdentifier;   //< A byte used to determine uniqueness of the unit
    /*0x0A6*/ OrderType   secondaryOrderType;       //< (Build addon verified) @todo verify (Cloak, Build, ExpandCreep suggested by EUDDB) 
    /*0x0A7*/ u8          buildingOverlayState;   // 0 means the building has the largest amount of fire/blood
    /*0x0A8*/ u16         hpGain;                 //< hp gained on construction or repair
    /*0x0AA*/ u16         shieldGain;             //< Shield gain on construction
    /*0x0AC*/ u16         remainingBuildTime;     //< Remaining bulding time; This is also the timer for powerups (flags) to return to their original location.
    /*0x0AE*/ u16         previousHP;             // The HP of the unit before it changed (example Drone->Hatchery, the Drone's HP will be stored here)
    /*0x0B0*/ u16         loadedUnitIndex[8];     // officially called "uwTransport[8]"
    ///////////////
    /*0x0C0*/ union
    {
      struct
      {
        u8 spiderMineCount; // 0
      } vulture;

      struct
      {
        CUnit*  pInHanger;     // 0   first child inside the hanger    // official
        CUnit*  pOutHanger;    // 4   first child outside the hanger
        u8      inHangerCount;      // 8   number inside the hanger
        u8      outHangerCount;     // 9   number outside the hanger
      } carrier; // also applies to reaver (Carrier is official)

      struct
      {
        CUnit*  parent;    // 0
        // CLink<CUnit> hanger_link;
        CUnit*  prev;      // 4
        CUnit*  next;      // 8
        bool    inHanger;   // C (is this wrong?)
      } fighter;  // also applies to scarab

      struct
      {
        u32 _unknown_00;
        u32 _unknown_04;
        u32 flagSpawnFrame; // flag beacons, the frame that the flag will spawn
      } beacon;

      struct
      {
        CUnit*      addon;               // 0
        UnitType    addonBuildType;       // 4
        u16         upgradeResearchTime;  // 6
        TechType    techType;             // 8
        UpgradeType upgradeType;          // 9
        u8          larvaTimer;           // A
        u8          landingTimer;         // B
        u8          creepTimer;           // C
        u8          upgradeLevel;         // D
      } building;

      struct
      {
        CUnit*    pPowerup;                // 0    // official
        Target    targetResource;
        u16       repairResourceLossTimer;  // C
        bool      isCarryingSomething;      // E    // There is a "ubIsHarvesting" somewhere
        u8        resourceCarryCount;       // F
      } worker;   // Official name, but there is also a "CUnit::WorkerList::pHarvestBldg" somewhere
    };
    ///////////////
    /*0x0D0*/ union
    {
      struct
      {
        u16     resourceCount;  // amount of resources
        u8      resourceIscript;
        u8      gatherQueueCount;
        CUnit*  nextGatherer;    // 4  // pointer to the next workerunit waiting in line to gather
        u8      resourceGroup;    // 8
        u8      resourceBelongsToAI;
      } resource;  // When the unit is resource container
      struct { CUnit*   exit; } nydus; // connected nydius canal
      struct { CSprite* nukeDot; } ghost;
      struct { CSprite* pPowerTemplate; } pylon;
      struct
      {
        CUnit* pNuke;   // attached nuke    // official name
        bool bReady;      // 4   // official name
      } silo;   // Should be "CUnit::Silo::"
      struct
      {
        rect<s16> larvaSpawnInfluence; // Influenced based on resource return location
      } hatchery;
      struct
      {
        Target spawnTarget;
      } powerup;
      struct
      {
        CUnit* harvestTarget;           // 0
        // CLINK<CUnit> harvest_link;
        CUnit* prevHarvestUnit;         // 4   // When there is a gather conflict
        CUnit* nextHarvestUnit;         // 8
      } gatherer; //there is also a "CUnit::WorkerList::pHarvestBldg" somewhere
    };
    /*0x0DC*/ u32       statusFlags;
    /*0x0E0*/ ResourceType resourceType;         // Resource being held by worker: 1 = gas, 2 = ore
    /*0x0E1*/ u8        wireframeSeed;
    /*0x0E2*/ u8        secondaryOrderState;
    /*0x0E3*/ u8        recentOrderTimer;     // Counts down from 15 to 0 when most orders are given,
    // or when the unit moves after reaching a patrol location
    /*0x0E4*/ s32       visibilityStatus;     // Flags specifying which players can detect this unit (cloaked/burrowed)
    /*0x0E8*/ Target    secondaryOrderTarget;       // Position part is unused
    // CLink<CUnit> burrow_link;
    /*0x0F0*/ CUnit*    previousBurrowedUnit;
    /*0x0F4*/ CUnit*    nextBurrowedUnit;
    /*0x0F8*/ union
    {
      struct
      {
        Target target;
      } rally;  // If the unit is rally type

      struct
      { // CLink<CUnit> power_link;
        CUnit*  prevPsiProvider;
        CUnit*  nextPsiProvider;
      } psiProvider;  // If the unit is psi provider
    };
    /*0x100*/ void*     unitPath;
    /*0x104*/ u8        pathingCollisionInterval; // unknown
    /*0x105*/ u8        pathingFlags;             // 0x01 = uses pathing; 0x02 = ?; 0x04 = ?
    /*0x106*/ u8        _unused_0x106;
    /*0x107*/ bool      isBeingHealed;    // 1 if a medic is currently healing this unit
    /*0x108*/ rect<s16> contourBounds;    // a rect that specifies the closest contour (collision) Position
    struct
    {
      /*0x110*/ u16     removeTimer;      //  does not apply to scanner sweep
      /*0x112*/ u16     defenseMatrixDamage;
      /*0x114*/ u8      defenseMatrixTimer;
      /*0x115*/ u8      stimTimer;
      /*0x116*/ u8      ensnareTimer;
      /*0x117*/ u8      lockdownTimer;
      /*0x118*/ u8      irradiateTimer;
      /*0x119*/ u8      stasisTimer;
      /*0x11A*/ u8      plagueTimer;
      /*0x11B*/ u8      stormTimer;
      /*0x11C*/ CUnit*  irradiatedBy;
      /*0x120*/ u8      irradiatePlayerID;
      /*0x121*/ u8      parasiteFlags;    // bitmask identifying which players have parasited this unit
      /*0x122*/ u8      cycleCounter;     // counts/cycles up from 0 to 7 (inclusive). See also 0x85.
      /*0x123*/ bool    isBlind;
      /*0x124*/ u8      maelstromTimer;
      /*0x125*/ u8      _unused_0x125;    // ?? Might be afterburner timer or ultralisk roar timer
      /*0x126*/ u8      acidSporeCount;
      /*0x127*/ u8      acidSporeTime[9];
    } status;
    /*0x130*/ u16   bulletSpreadSeed;  // Counts up for the number of bullets shot by a unit using
    // this weapon behaviour and resets after it reaches 12

    /*0x134*/ void* pAI;            // pointer to AI class, we're not using this though  // official name
    /*0x138*/ u16   airStrength;
    /*0x13A*/ u16   groundStrength;
    rect<u32> finder; // Official names are "posSortXL, posSortXR, posSortYT, posSortYB"
                      // Ordering for unit boundries in unit finder for binary search
    /*0x14C*/ u8    _repulseUnknown;        // @todo Unknown
    /*0x14D*/ u8    repulseAngle;           // updated only when air unit is being pushed
    /*0x14E*/ u8    bRepMtxX;              //  (mapsizex/1.5 max)   // repulse matrix X/Y
    /*0x14F*/ u8    bRepMtxY;              //  (mapsizex/1.5 max)
  };

  static_assert(sizeof(CUnit) == 336, "CUnit is incorrect.");

  static_assert(offsetof(CUnit, shields) == 0x60, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, unitType) == 0x64, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, previousPlayerUnit) == 0x68, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, nextPlayerUnit) == 0x6C, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, subUnit) == 0x70, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, orderQueueHead) == 0x74, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, orderQueueTail) == 0x78, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, autoTargetUnit) == 0x7C, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, connectedUnit) == 0x80, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, orderQueueCount) == 0x84, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, orderQueueTimer) == 0x85, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, _unknown_0x086) == 0x86, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, attackNotifyTimer) == 0x87, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, previousUnitType) == 0x88, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, lastEventTimer) == 0x8A, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, lastEventColor) == 0x8B, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, _unused_0x08C) == 0x8C, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, rankIncrease) == 0x8E, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, killCount) == 0x8F, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, lastAttackingPlayer) == 0x90, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, secondaryOrderTimer) == 0x91, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, AIActionFlag) == 0x92, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, userActionFlags) == 0x93, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, currentButtonSet) == 0x94, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, isCloaked) == 0x96, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, movementState) == 0x97, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, buildQueue) == 0x98, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, energy) == 0xA2, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, buildQueueSlot) == 0xA4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, uniquenessIdentifier) == 0xA5, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, secondaryOrderType) == 0xA6, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, buildingOverlayState) == 0xA7, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, hpGain) == 0xA8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, shieldGain) == 0xAA, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, remainingBuildTime) == 0xAC, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, previousHP) == 0xAE, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, loadedUnitIndex) == 0xB0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, vulture) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, vulture.spiderMineCount) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, carrier) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, carrier.pInHanger) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, carrier.pOutHanger) == 0xC4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, carrier.inHangerCount) == 0xC8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, carrier.outHangerCount) == 0xC9, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, fighter) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, fighter.parent) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, fighter.prev) == 0xC4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, fighter.next) == 0xC8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, fighter.inHanger) == 0xCC, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, beacon) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, beacon._unknown_00) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, beacon._unknown_04) == 0xC4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, beacon.flagSpawnFrame) == 0xC8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building.addon) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building.addonBuildType) == 0xC4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building.upgradeResearchTime) == 0xC6, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building.techType) == 0xC8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building.upgradeType) == 0xC9, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building.larvaTimer) == 0xCA, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building.landingTimer) == 0xCB, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building.creepTimer) == 0xCC, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, building.upgradeLevel) == 0xCD, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, worker) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, worker.pPowerup) == 0xC0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, worker.targetResource) == 0xC4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, worker.repairResourceLossTimer) == 0xCC, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, worker.isCarryingSomething) == 0xCE, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, worker.resourceCarryCount) == 0xCF, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, resource) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, resource.resourceCount) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, resource.resourceIscript) == 0xD2, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, resource.gatherQueueCount) == 0xD3, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, resource.nextGatherer) == 0xD4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, resource.resourceGroup) == 0xD8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, resource.resourceBelongsToAI) == 0xD9, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, nydus) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, nydus.exit) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, ghost) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, ghost.nukeDot) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, pylon) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, pylon.pPowerTemplate) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, silo) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, silo.pNuke) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, silo.bReady) == 0xD4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, hatchery) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, hatchery.larvaSpawnInfluence) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, powerup) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, powerup.spawnTarget) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, gatherer) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, gatherer.harvestTarget) == 0xD0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, gatherer.prevHarvestUnit) == 0xD4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, gatherer.nextHarvestUnit) == 0xD8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, statusFlags) == 0xDC, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, resourceType) == 0xE0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, wireframeSeed) == 0xE1, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, secondaryOrderState) == 0xE2, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, recentOrderTimer) == 0xE3, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, visibilityStatus) == 0xE4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, secondaryOrderTarget) == 0xE8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, previousBurrowedUnit) == 0xF0, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, nextBurrowedUnit) == 0xF4, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, rally) == 0xF8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, rally.target) == 0xF8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, psiProvider) == 0xF8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, psiProvider.prevPsiProvider) == 0xF8, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, psiProvider.nextPsiProvider) == 0xFC, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, unitPath) == 0x100, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, pathingCollisionInterval) == 0x104, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, pathingFlags) == 0x105, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, isBeingHealed) == 0x107, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, contourBounds) == 0x108, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status) == 0x110, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.removeTimer) == 0x110, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.defenseMatrixDamage) == 0x112, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.defenseMatrixTimer) == 0x114, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.stimTimer) == 0x115, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.ensnareTimer) == 0x116, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.lockdownTimer) == 0x117, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.irradiateTimer) == 0x118, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.stasisTimer) == 0x119, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.plagueTimer) == 0x11A, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.stormTimer) == 0x11B, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.irradiatedBy) == 0x11C, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.irradiatePlayerID) == 0x120, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.parasiteFlags) == 0x121, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.cycleCounter) == 0x122, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.isBlind) == 0x123, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.maelstromTimer) == 0x124, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.acidSporeCount) == 0x126, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, status.acidSporeTime) == 0x127, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, bulletSpreadSeed) == 0x130, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, pAI) == 0x134, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, airStrength) == 0x138, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, groundStrength) == 0x13A, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, finder) == 0x13C, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, _repulseUnknown) == 0x14C, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, repulseAngle) == 0x14D, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, bRepMtxX) == 0x14E, "CUnit member not at correct offset");
  static_assert(offsetof(CUnit, bRepMtxY) == 0x14F, "CUnit member not at correct offset");
};

