#pragma once

#include "TestComponent.h"

extern "C"
{
  namespace RB::Internal
  {
    RB_API void ImportComponents(RB::Domain* domain);
  }
}