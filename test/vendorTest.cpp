#include <gtest/gtest.h>
#include "../src/vendor.h"
#include <stdexcept>

using namespace AutoVendor;

class VendorTest : public ::testing::Test {

protected:

  Vendor vendor;

  VendorTest() {}

  virtual void SetUp() {}
  virtual void TearDown() {}
};

// Test Vendor.input
TEST_F(VendorTest, Input1000YenBill) {
  vendor.input(Money::ThousandYenBill);
  EXPECT_EQ(1000u, vendor.getTotalAmount());
}

TEST_F(VendorTest, Input500YenCoin) {
  vendor.input(Money::FiveHundoredYenCoin);
  EXPECT_EQ(500u, vendor.getTotalAmount());
}

TEST_F(VendorTest, Input100YenCoin) {
  vendor.input(Money::HundoredYenCoin);
  EXPECT_EQ(100u, vendor.getTotalAmount());
}

TEST_F(VendorTest, Input50YenCoin) {
  vendor.input(Money::FiftyYenCoin);
  EXPECT_EQ(50u, vendor.getTotalAmount());
}

TEST_F(VendorTest, Input10YenCoin) {
  vendor.input(Money::TenYenCoin);
  EXPECT_EQ(10u, vendor.getTotalAmount());
}

TEST_F(VendorTest, Input) {
  vendor.input(Money::HundoredYenCoin);
  vendor.input(Money::TenYenCoin);
  EXPECT_EQ(110u, vendor.getTotalAmount());

  vendor.input(Money::ThousandYenBill);
  EXPECT_EQ(1110u, vendor.getTotalAmount());
}

// vendor.purchase
TEST_F(VendorTest, purchase) {
  vendor.input(Money::ThousandYenBill);
  vendor.purchase();

  ASSERT_TRUE(vendor.getPurchasable());
  EXPECT_EQ(880u, vendor.getTotalAmount());
}

TEST_F(VendorTest, purchaseAndGetZeroChange) {
  vendor.input(Money::HundoredYenCoin);
  vendor.input(Money::TenYenCoin);
  vendor.input(Money::TenYenCoin);

  ASSERT_TRUE(vendor.getPurchasable());
  vendor.purchase();

  EXPECT_EQ(0u, vendor.getTotalAmount());
  EXPECT_EQ(120u, vendor.getSaleAmount());
}

TEST_F(VendorTest, notPurchase) {
  vendor.input(Money::HundoredYenCoin);

  ASSERT_FALSE(vendor.getPurchasable());
  vendor.purchase();

  EXPECT_EQ(0u, vendor.getSaleAmount());
  EXPECT_EQ(100u, vendor.getTotalAmount());
}

TEST_F(VendorTest, saleAmount) {
  vendor.input(Money::ThousandYenBill);
  EXPECT_EQ(0u, vendor.getSaleAmount());

  vendor.purchase();
  EXPECT_EQ(120u, vendor.getSaleAmount());

  vendor.purchase();
  EXPECT_EQ(240u, vendor.getSaleAmount());
}

TEST_F(VendorTest, emptyStock) {
  vendor.input(Money::ThousandYenBill);

  ASSERT_TRUE(vendor.getPurchasable());
  vendor.purchase(); vendor.purchase();
  vendor.purchase(); vendor.purchase(); vendor.purchase();

  EXPECT_EQ(400u, vendor.getTotalAmount());
  EXPECT_EQ(600u, vendor.getSaleAmount());

  ASSERT_FALSE(vendor.getPurchasable());
  vendor.purchase();
  EXPECT_EQ(400u, vendor.getTotalAmount());
  EXPECT_EQ(600u, vendor.getSaleAmount());
}

// vendor.payback
TEST_F(VendorTest, payback) {
  vendor.input(Money::ThousandYenBill);
  EXPECT_EQ(1000u, vendor.payback());
  ASSERT_EQ(0u, vendor.getTotalAmount());

  vendor.input(Money::FiveHundoredYenCoin);
  vendor.purchase();
  EXPECT_EQ(380u, vendor.payback());
  EXPECT_EQ(0u, vendor.getTotalAmount());
}

// vendor.getStockInfomation
TEST_F(VendorTest, getStockInfomation) {
  vendor.input(Money::ThousandYenBill);

  EXPECT_EQ("名前:コーラ, 在庫:5, 価格:120", vendor.getStockInfomation());

  vendor.purchase();
  EXPECT_EQ("名前:コーラ, 在庫:4, 価格:120", vendor.getStockInfomation());

  vendor.purchase();
  vendor.purchase(); vendor.purchase(); vendor.purchase();
  EXPECT_EQ("名前:コーラ, 在庫:0, 価格:120", vendor.getStockInfomation());

  vendor.purchase();
  EXPECT_EQ("名前:コーラ, 在庫:0, 価格:120", vendor.getStockInfomation());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
