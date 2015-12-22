#pragma once
#include <cstddef>
#include "Types.h"

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

    u32      shields;      // BW shows this value/256, possibly not u32?
    UnitType unitType;        // Specifies the type of unit.

    // CLink<CUnit> player_link;
    CUnit*  previousPlayerUnit;
    CUnit*  nextPlayerUnit;

    CUnit*  subUnit;

    // CLink<COrder> orderQueue_link;
    COrder* orderQueueHead;
    COrder* orderQueueTail;

    CUnit*  autoTargetUnit;       // The auto-acquired target (Note: This field is actually used for different targets internally, especially by the AI)
    CUnit*  connectedUnit;        // Addon is connected to building (addon has conntected building, but not in other direction  (officially "pAttached")
    u8      orderQueueCount;      // @todo Verify   // officially "ubQueuedOrders"
    u8      orderQueueTimer;      // counts/cycles down from from 8 to 0 (inclusive). See also 0x122.
    u8      _unknown_0x086;       // pathing related?
    u8      attackNotifyTimer;    // Prevent "Your forces are under attack." on every attack
    UnitType previousUnitType;    // Stores the type of the unit prior to being morphed/constructed
    u8      lastEventTimer;       // countdown that stops being recent when it hits 0 
    u8      lastEventColor;       // 17 = was completed (train, morph), 174 = was attacked
    u16     _unused_0x08C;        // might have originally been RGB from lastEventColor
    u8      rankIncrease;         // Adds this value to the unit's base rank
    u8      killCount;            // Killcount
    u8      lastAttackingPlayer;  // the player that last attacked this unit
    u8      secondaryOrderTimer;
    u8      AIActionFlag;         // Internal use by AI only
    u8      userActionFlags;      // some flags that change when the user interacts with the unit
                                  // 2 = issued an order, 3 = interrupted an order, 4 = self destructing

    u16         currentButtonSet;       // The u16 is a guess, used to be u8
    bool        isCloaked;
    UnitMovementState movementState;          // A value based on conditions related to pathing, see Path.h for info
    UnitType    buildQueue[5];          //< Queue of units to build. Note that it doesn't begin with index 0, but with #buildQueueSlot index. 
    u16         energy;                 //< Energy Position   // officially "xwMagic"
    u8          buildQueueSlot;         //< Index of active unit in #buildQueue. 
    u8          uniquenessIdentifier;   //< A byte used to determine uniqueness of the unit
    OrderType   secondaryOrderType;       //< (Build addon verified) @todo verify (Cloak, Build, ExpandCreep suggested by EUDDB) 
    u8          buildingOverlayState;   // 0 means the building has the largest amount of fire/blood
    u16         hpGain;                 //< hp gained on construction or repair
    u16         shieldGain;             //< Shield gain on construction
    u16         remainingBuildTime;     //< Remaining bulding time; This is also the timer for powerups (flags) to return to their original location.
    u16         previousHP;             // The HP of the unit before it changed (example Drone->Hatchery, the Drone's HP will be stored here)
    u16         loadedUnitIndex[8];     // officially called "uwTransport[8]"
    
    union
    {
      struct
      {
        u8 spiderMineCount; // 0
      } vulture;

      struct
      {
        CUnit*  pInHanger;          // first child inside the hanger    // official
        CUnit*  pOutHanger;         // first child outside the hanger
        u8      inHangerCount;      // number inside the hanger
        u8      outHangerCount;     // number outside the hanger
      } carrier; // also applies to reaver (Carrier is official)

      struct
      {
        CUnit*  parent;
        // CLink<CUnit> hanger_link;
        CUnit*  prev;
        CUnit*  next;
        bool    inHanger;   // (is this wrong?)
      } fighter;  // also applies to scarab

      struct
      {
        u32 _unknown_00;
        u32 _unknown_04;
        u32 flagSpawnFrame; // flag beacons, the frame that the flag will spawn
      } beacon;

      struct
      {
        CUnit*      addon;
        UnitType    addonBuildType;
        u16         upgradeResearchTime;
        TechType    techType;
        UpgradeType upgradeType;
        u8          larvaTimer;
        u8          landingTimer;
        u8          creepTimer;
        u8          upgradeLevel;
      } building;

      struct
      {
        CUnit*    pPowerup;
        Target    targetResource;
        u16       repairResourceLossTimer;
        bool      isCarryingSomething;  // There is a "ubIsHarvesting" somewhere
        u8        resourceCarryCount;
      } worker;   // Official name, but there is also a "CUnit::WorkerList::pHarvestBldg" somewhere
    };

    union
    {
      struct
      {
        u16     resourceCount;  // amount of resources
        u8      resourceIscript;
        u8      gatherQueueCount;
        CUnit*  nextGatherer;     // pointer to the next worker unit waiting in line to gather
        u8      resourceGroup;
        u8      resourceBelongsToAI;
      } resource;  // When the unit is resource container
      struct { CUnit*   exit; } nydus; // connected nydius canal
      struct { CSprite* nukeDot; } ghost;
      struct { CSprite* pPowerTemplate; } pylon;
      struct
      {
        CUnit* pNuke;   // attached nuke    // official name
        bool bReady;    // official name
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
        CUnit* harvestTarget;
        // CLINK<CUnit> harvest_link;
        CUnit* prevHarvestUnit;       // When there is a gather conflict
        CUnit* nextHarvestUnit;
      } gatherer; //there is also a "CUnit::WorkerList::pHarvestBldg" somewhere
    };
    u32           statusFlags;
    ResourceType  resourceType;         // Resource being held by worker: 1 = gas, 2 = ore
    u8            wireframeSeed;
    u8            secondaryOrderState;
    u8            recentOrderTimer;     // Counts down from 15 to 0 when most orders are given,
                                        // or when the unit moves after reaching a patrol location
    s32       visibilityStatus;         // Flags specifying which players can detect this unit (cloaked/burrowed)
    Target    secondaryOrderTarget;     // Position part is unused
    // CLink<CUnit> burrow_link;
    CUnit*    previousBurrowedUnit;
    CUnit*    nextBurrowedUnit;
    union
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
    void*     unitPath;
    u8        pathingCollisionInterval; // unknown
    u8        pathingFlags;             // 0x01 = uses pathing; 0x02 = ?; 0x04 = ?
    u8        _unused_0x106;
    bool      isBeingHealed;    // 1 if a medic is currently healing this unit
    rect<s16> contourBounds;    // a rect that specifies the closest contour (collision) Position
    struct
    {
      u16     removeTimer;      //  does not apply to scanner sweep
      u16     defenseMatrixDamage;
      u8      defenseMatrixTimer;
      u8      stimTimer;
      u8      ensnareTimer;
      u8      lockdownTimer;
      u8      irradiateTimer;
      u8      stasisTimer;
      u8      plagueTimer;
      u8      stormTimer;
      CUnit*  irradiatedBy;
      u8      irradiatePlayerID;
      u8      parasiteFlags;    // bitmask identifying which players have parasited this unit
      u8      cycleCounter;     // counts/cycles up from 0 to 7 (inclusive). See also 0x85.
      bool    isBlind;
      u8      maelstromTimer;
      u8      _unused_0x125;    // ?? Might be afterburner timer or ultralisk roar timer
      u8      acidSporeCount;
      u8      acidSporeTime[9];
    } status;
    u16   bulletSpreadSeed;   // Counts up for the number of bullets shot by a unit using
                              // this weapon behaviour and resets after it reaches 12

    void* pAI;                // pointer to AI class  // official name
    u16   airStrength;
    u16   groundStrength;

    u32 posSortXL, posSortXR, posSortYT, posSortYB; // official // Ordering for unit boundries in unit finder for binary search
    
    u8        _repulseUnknown;    // @todo Unknown
    u8        repulseAngle;       // updated only when air unit is being pushed
    point<u8> repulseVelocity;    // Guess. Official names are bRepMtxX and bRepMtxY.
                                  // (mapsize/1.5 max) < don't remember what this means?
  };

  static_assert(sizeof(CUnit) == 336, "CUnit is incorrect.");
#define OFFSET_ASSERT(offset, member) static_assert(offset == offsetof(CUnit, member), "CUnit member not at correct offset")
  OFFSET_ASSERT(0x60, shields);
  OFFSET_ASSERT(0x64, unitType);
  OFFSET_ASSERT(0x68, previousPlayerUnit);
  OFFSET_ASSERT(0x6C, nextPlayerUnit);
  OFFSET_ASSERT(0x70, subUnit);
  OFFSET_ASSERT(0x74, orderQueueHead);
  OFFSET_ASSERT(0x78, orderQueueTail);
  OFFSET_ASSERT(0x7C, autoTargetUnit);
  OFFSET_ASSERT(0x80, connectedUnit);
  OFFSET_ASSERT(0x84, orderQueueCount);
  OFFSET_ASSERT(0x85, orderQueueTimer);
  OFFSET_ASSERT(0x86, _unknown_0x086);
  OFFSET_ASSERT(0x87, attackNotifyTimer);
  OFFSET_ASSERT(0x88, previousUnitType);
  OFFSET_ASSERT(0x8A, lastEventTimer);
  OFFSET_ASSERT(0x8B, lastEventColor);
  OFFSET_ASSERT(0x8C, _unused_0x08C);
  OFFSET_ASSERT(0x8E, rankIncrease);
  OFFSET_ASSERT(0x8F, killCount);
  OFFSET_ASSERT(0x90, lastAttackingPlayer);
  OFFSET_ASSERT(0x91, secondaryOrderTimer);
  OFFSET_ASSERT(0x92, AIActionFlag);
  OFFSET_ASSERT(0x93, userActionFlags);
  OFFSET_ASSERT(0x94, currentButtonSet);
  OFFSET_ASSERT(0x96, isCloaked);
  OFFSET_ASSERT(0x97, movementState);
  OFFSET_ASSERT(0x98, buildQueue);
  OFFSET_ASSERT(0xA2, energy);
  OFFSET_ASSERT(0xA4, buildQueueSlot);
  OFFSET_ASSERT(0xA5, uniquenessIdentifier);
  OFFSET_ASSERT(0xA6, secondaryOrderType);
  OFFSET_ASSERT(0xA7, buildingOverlayState);
  OFFSET_ASSERT(0xA8, hpGain);
  OFFSET_ASSERT(0xAA, shieldGain);
  OFFSET_ASSERT(0xAC, remainingBuildTime);
  OFFSET_ASSERT(0xAE, previousHP);
  OFFSET_ASSERT(0xB0, loadedUnitIndex);
  OFFSET_ASSERT(0xC0, vulture);
  OFFSET_ASSERT(0xC0, vulture.spiderMineCount);
  OFFSET_ASSERT(0xC0, carrier);
  OFFSET_ASSERT(0xC0, carrier.pInHanger);
  OFFSET_ASSERT(0xC4, carrier.pOutHanger);
  OFFSET_ASSERT(0xC8, carrier.inHangerCount);
  OFFSET_ASSERT(0xC9, carrier.outHangerCount);
  OFFSET_ASSERT(0xC0, fighter);
  OFFSET_ASSERT(0xC0, fighter.parent);
  OFFSET_ASSERT(0xC4, fighter.prev);
  OFFSET_ASSERT(0xC8, fighter.next);
  OFFSET_ASSERT(0xCC, fighter.inHanger);
  OFFSET_ASSERT(0xC0, beacon);
  OFFSET_ASSERT(0xC0, beacon._unknown_00);
  OFFSET_ASSERT(0xC4, beacon._unknown_04);
  OFFSET_ASSERT(0xC8, beacon.flagSpawnFrame);
  OFFSET_ASSERT(0xC0, building);
  OFFSET_ASSERT(0xC0, building.addon);
  OFFSET_ASSERT(0xC4, building.addonBuildType);
  OFFSET_ASSERT(0xC6, building.upgradeResearchTime);
  OFFSET_ASSERT(0xC8, building.techType);
  OFFSET_ASSERT(0xC9, building.upgradeType);
  OFFSET_ASSERT(0xCA, building.larvaTimer);
  OFFSET_ASSERT(0xCB, building.landingTimer);
  OFFSET_ASSERT(0xCC, building.creepTimer);
  OFFSET_ASSERT(0xCD, building.upgradeLevel);
  OFFSET_ASSERT(0xC0, worker);
  OFFSET_ASSERT(0xC0, worker.pPowerup);
  OFFSET_ASSERT(0xC4, worker.targetResource);
  OFFSET_ASSERT(0xCC, worker.repairResourceLossTimer);
  OFFSET_ASSERT(0xCE, worker.isCarryingSomething);
  OFFSET_ASSERT(0xCF, worker.resourceCarryCount);
  OFFSET_ASSERT(0xD0, resource);
  OFFSET_ASSERT(0xD0, resource.resourceCount);
  OFFSET_ASSERT(0xD2, resource.resourceIscript);
  OFFSET_ASSERT(0xD3, resource.gatherQueueCount);
  OFFSET_ASSERT(0xD4, resource.nextGatherer);
  OFFSET_ASSERT(0xD8, resource.resourceGroup);
  OFFSET_ASSERT(0xD9, resource.resourceBelongsToAI);
  OFFSET_ASSERT(0xD0, nydus);
  OFFSET_ASSERT(0xD0, nydus.exit);
  OFFSET_ASSERT(0xD0, ghost);
  OFFSET_ASSERT(0xD0, ghost.nukeDot);
  OFFSET_ASSERT(0xD0, pylon);
  OFFSET_ASSERT(0xD0, pylon.pPowerTemplate);
  OFFSET_ASSERT(0xD0, silo);
  OFFSET_ASSERT(0xD0, silo.pNuke);
  OFFSET_ASSERT(0xD4, silo.bReady);
  OFFSET_ASSERT(0xD0, hatchery);
  OFFSET_ASSERT(0xD0, hatchery.larvaSpawnInfluence);
  OFFSET_ASSERT(0xD0, powerup);
  OFFSET_ASSERT(0xD0, powerup.spawnTarget);
  OFFSET_ASSERT(0xD0, gatherer);
  OFFSET_ASSERT(0xD0, gatherer.harvestTarget);
  OFFSET_ASSERT(0xD4, gatherer.prevHarvestUnit);
  OFFSET_ASSERT(0xD8, gatherer.nextHarvestUnit);
  OFFSET_ASSERT(0xDC, statusFlags);
  OFFSET_ASSERT(0xE0, resourceType);
  OFFSET_ASSERT(0xE1, wireframeSeed);
  OFFSET_ASSERT(0xE2, secondaryOrderState);
  OFFSET_ASSERT(0xE3, recentOrderTimer);
  OFFSET_ASSERT(0xE4, visibilityStatus);
  OFFSET_ASSERT(0xE8, secondaryOrderTarget);
  OFFSET_ASSERT(0xF0, previousBurrowedUnit);
  OFFSET_ASSERT(0xF4, nextBurrowedUnit);
  OFFSET_ASSERT(0xF8, rally);
  OFFSET_ASSERT(0xF8, rally.target);
  OFFSET_ASSERT(0xF8, psiProvider);
  OFFSET_ASSERT(0xF8, psiProvider.prevPsiProvider);
  OFFSET_ASSERT(0xFC, psiProvider.nextPsiProvider);
  OFFSET_ASSERT(0x100, unitPath);
  OFFSET_ASSERT(0x104, pathingCollisionInterval);
  OFFSET_ASSERT(0x105, pathingFlags);
  OFFSET_ASSERT(0x107, isBeingHealed);
  OFFSET_ASSERT(0x108, contourBounds);
  OFFSET_ASSERT(0x110, status);
  OFFSET_ASSERT(0x110, status.removeTimer);
  OFFSET_ASSERT(0x112, status.defenseMatrixDamage);
  OFFSET_ASSERT(0x114, status.defenseMatrixTimer);
  OFFSET_ASSERT(0x115, status.stimTimer);
  OFFSET_ASSERT(0x116, status.ensnareTimer);
  OFFSET_ASSERT(0x117, status.lockdownTimer);
  OFFSET_ASSERT(0x118, status.irradiateTimer);
  OFFSET_ASSERT(0x119, status.stasisTimer);
  OFFSET_ASSERT(0x11A, status.plagueTimer);
  OFFSET_ASSERT(0x11B, status.stormTimer);
  OFFSET_ASSERT(0x11C, status.irradiatedBy);
  OFFSET_ASSERT(0x120, status.irradiatePlayerID);
  OFFSET_ASSERT(0x121, status.parasiteFlags);
  OFFSET_ASSERT(0x122, status.cycleCounter);
  OFFSET_ASSERT(0x123, status.isBlind);
  OFFSET_ASSERT(0x124, status.maelstromTimer);
  OFFSET_ASSERT(0x126, status.acidSporeCount);
  OFFSET_ASSERT(0x127, status.acidSporeTime);
  OFFSET_ASSERT(0x130, bulletSpreadSeed);
  OFFSET_ASSERT(0x134, pAI);
  OFFSET_ASSERT(0x138, airStrength);
  OFFSET_ASSERT(0x13A, groundStrength);
  OFFSET_ASSERT(0x13C, posSortXL);
  OFFSET_ASSERT(0x140, posSortXR);
  OFFSET_ASSERT(0x144, posSortYT);
  OFFSET_ASSERT(0x148, posSortYB);
  OFFSET_ASSERT(0x14C, _repulseUnknown);
  OFFSET_ASSERT(0x14D, repulseAngle);
  OFFSET_ASSERT(0x14E, repulseVelocity);
#undef OFFSET_ASSERT
};

