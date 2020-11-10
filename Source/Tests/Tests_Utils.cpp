#include "../Utils.cpp"

#include "catch.hpp"

TEST_CASE("version numbers are initialized")
{
  REQUIRE(VersionNumber(1, 2, 3).major == 1);
  REQUIRE(VersionNumber(1, 2, 3).minor == 2);
  REQUIRE(VersionNumber(1, 2, 3).patch == 3);

  REQUIRE(VersionNumber().major == -1);
  REQUIRE(VersionNumber().minor == -1);
  REQUIRE(VersionNumber().patch == -1);
}

TEST_CASE("version numbers are compared")
{
  REQUIRE(VersionNumber(1, 2, 3) == VersionNumber(1, 2, 3));

  REQUIRE(VersionNumber(1, 2, 3) != VersionNumber(0, 2, 3));
  REQUIRE(VersionNumber(1, 2, 3) != VersionNumber(1, 0, 3));
  REQUIRE(VersionNumber(1, 2, 3) != VersionNumber(1, 2, 0));

  REQUIRE(VersionNumber(1, 2, 3) < VersionNumber(2, 2, 3));
  REQUIRE(VersionNumber(1, 2, 3) < VersionNumber(1, 3, 3));
  REQUIRE(VersionNumber(1, 2, 3) < VersionNumber(1, 2, 4));

  REQUIRE(VersionNumber(1, 2, 3) > VersionNumber(0, 2, 3));
  REQUIRE(VersionNumber(1, 2, 3) > VersionNumber(1, 1, 3));
  REQUIRE(VersionNumber(1, 2, 3) > VersionNumber(1, 2, 2));
}

TEST_CASE("version numbers are parsed")
{
  REQUIRE(parseVersionString("1.2.3") == VersionNumber(1, 2, 3));
  REQUIRE(parseVersionString("1.2.3.4") == VersionNumber(1, 2, 3));
  REQUIRE(parseVersionString("1.2.03") == VersionNumber(1, 2, 3));
}

TEST_CASE("values are remapped to sided ranges")
{
  REQUIRE(remapSided(0.0f, -2.0f, +10.0f) == Approx(0.0f));
  REQUIRE(remapSided(1.0f, -2.0f, +10.0f) == Approx(10.0f));
  REQUIRE(remapSided(-1.0f, -2.0f, +10.0f) == Approx(-2.0f));
  REQUIRE(remapSided(-0.5f, -2.0f, +10.0f) == Approx(-1.0f));
}

TEST_CASE("values are remapped to a single range")
{
  REQUIRE(remapRange(0.0f, -2.0f, +10.0f) == Approx(4.0f));
  REQUIRE(remapRange(1.0f, -2.0f, +10.0f) == Approx(10.0f));
  REQUIRE(remapRange(-1.0f, -2.0f, +10.0f) == Approx(-2.0f));
  REQUIRE(remapRange(-0.5f, -2.0f, +10.0f) == Approx(1.0f));
}

TEST_CASE("values are remapped from one range to another")
{
  REQUIRE(remapXY(-3.0f, -3.0f, +1.0f, -2.0f, 10.0f) == Approx(-2.0f));
  REQUIRE(remapXY(-4.0f, -3.0f, +1.0f, -2.0f, 10.0f) == Approx(-2.0f));
  REQUIRE(remapXY(+1.0f, -3.0f, +1.0f, -2.0f, 10.0f) == Approx(10.0f));
  REQUIRE(remapXY(+2.0f, -3.0f, +1.0f, -2.0f, 10.0f) == Approx(10.0f));
  REQUIRE(remapXY(0.0f, -3.0f, +1.0f, -2.0f, 10.0f) == Approx(7.0f));
}

TEST_CASE("state parameters are mapped to thier values")
{
  XmlElement state = XmlElement("state");
  XmlElement* param = nullptr;

  param = new XmlElement("PARAM");
  param->setAttribute("id", "param1");
  param->setAttribute("value", 0.0);
  state.addChildElement(param);

  param = new XmlElement("PARAM");
  param->setAttribute("id", "param2");
  param->setAttribute("value", 1.0);
  state.addChildElement(param);

  const auto map = mapParameterValues(std::make_unique<XmlElement>(state));

  REQUIRE(map.size() == 2);
  REQUIRE(map.find("param1") != map.end());
  REQUIRE(map.find("param2") != map.end());
  REQUIRE(map.at("param1") == Approx(0.0f));
  REQUIRE(map.at("param2") == Approx(1.0f));
}

TEST_CASE("remap sinh has correct behaviour")
{
  SECTION("y=-1 at x=-1")
  {
    REQUIRE(remapSinh(-1.0f, 0.0f, 1.0f) == Approx(-1.0f));
    REQUIRE(remapSinh(-1.0f, 0.0f, 5.0f) == Approx(-1.0f));
    REQUIRE(remapSinh(-1.0f, -1.0f, 5.0f) == Approx(-1.0f));
    REQUIRE(remapSinh(-1.0f, 1.0f, 5.0f) == Approx(-1.0f));
  }

  SECTION("y=1 at x=1")
  {
    REQUIRE(remapSinh(1.0f, 0.5f, 1.0f) == Approx(1.0f));
    REQUIRE(remapSinh(1.0f, 0.5f, 5.0f) == Approx(1.0f));
    REQUIRE(remapSinh(1.0f, 0.0f, 5.0f) == Approx(1.0f));
    REQUIRE(remapSinh(1.0f, 1.0f, 5.0f) == Approx(1.0f));
  }

  SECTION("y follows x0 correctly")
  {
    // when centered x0, then x=y at x=0.0
    REQUIRE(remapSinh(0.0f, 0.0f, 5.0f) == Approx(0.0f));
    // for larger x0, y initially moves faster and is larger at 0
    REQUIRE(remapSinh(0.0f, 0.1f, 5.0f) > 0.0f);
    // for smaller x0, y initially moves slower and is smaller at 0
    REQUIRE(remapSinh(0.0f, -0.1f, 5.0f) < 0.0f);
  }
}

TEST_CASE("invert remap sinh matches forward operation")
{
  REQUIRE(
      invertRemapSinh(remapSinh(-0.25, 0.5f, 2.0f), 0.5f, 2.0f)
      == Approx(-0.25f));
}
