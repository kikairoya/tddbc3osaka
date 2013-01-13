#pragma once

#include <string>
#include <sstream>

namespace AutoVendor {

  enum class Money : unsigned int {
    ThousandYenBill = 1000u,
    FiveHundredYenCoin = 500u,
    HundredYenCoin = 100u,
    FiftyYenCoin = 50u,
    TenYenCoin = 10u
  };

  struct Item {
    std::string name;
    unsigned int number;
    unsigned int price;
  };

  inline std::string to_string(const Item &item) {
    std::stringstream ss;
    ss << "名前:" << item.name << ", 在庫:" << item.number
       << ", 価格:" << item.price;
    return ss.str();
  }

  static const Item initialStock = {"コーラ", 5u, 120u};

  class Vendor {
    unsigned int totalAmount;
    unsigned int paybackAmount;
    unsigned int saleAmount;
    Item stock;

  public:
    Vendor();
    void input(const Money);
    void store(const Item&);
    void purchase();

    void refund();
    unsigned int getChangeAmount();
    void clearChange();

    const std::string getStockInfomation() const;
    bool getPurchasable() const;
    unsigned int getTotalAmount() const;
    unsigned int getSaleAmount() const;
  };
}

