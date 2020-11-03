#include "../dsp/PushPullAmp.h"

#include "catch.hpp"

TEST_CASE("scale buffer scales a buffer")
{
  std::vector<FAUSTFLOAT*> bufferCh = {nullptr};
  std::vector<FAUSTFLOAT> bufferMem = {1.0f, 1.1f, 1.2f, 1.3f};
  bufferCh[0] = &(bufferMem[0]);

  scaleBuffer((int)bufferMem.size(), &bufferCh[0], 2.0f);

  REQUIRE(bufferMem[0] == Approx(2.0f));
  REQUIRE(bufferMem[3] == Approx(2.6f));
}
