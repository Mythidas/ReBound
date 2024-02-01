#include "Import.h"
#include <RBEngine/Reflection/ComponentFactory.h>

extern "C"
{
  void RB::Internal::ImportComponents(RB::Domain* domain)
  {
    auto test_component = RB::ComponentFactory<TestComponent>(domain)
      .Data<&TestComponent::Negative>("Negative", offsetof(TestComponent, Negative))
      .Register();
  }
}