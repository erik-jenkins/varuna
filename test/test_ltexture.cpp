#include "catch.hpp"
#include "ltexture.hpp"

TEST_CASE("LTexture initialization", "[LTexture]") {
    LTexture texture;

    REQUIRE(texture.getHeight() == 0);
    REQUIRE(texture.getWidth()  == 0);
}
