#include "gtest/gtest.h"

using namespace std;

TEST (BasicTest, Section1) {
  EXPECT_EQ(18.0, 17);
  cout << "Gamer 1" << endl;
  EXPECT_EQ(25.4, 25.4);
}

TEST (BasicTest, Section2) {
  ASSERT_EQ(18.0, 17);
  cout << "Gamer 2" << endl;
  ASSERT_EQ(25.4, 25.4);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
