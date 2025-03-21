#include <gtest/gtest.h>

#include "file.h"

TEST(TestTopic, MapPathToAbsolute) {
    EXPECT_EQ(File::getContentType(".png"), "image/png");
}