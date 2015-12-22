#pragma once
// Note this should be in Storm

namespace BW
{
  template <class T>
  class CLink
  {
    T* prev;
    T* next;
  };

  static_assert(sizeof(CLink<void>) == 8, "Expected CLink to be 8 bytes.");
}
