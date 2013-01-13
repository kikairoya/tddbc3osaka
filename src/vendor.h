#pragma once

#include <string>

namespace AutoVendor {

  enum class Money : unsigned int {
    ThousandYenBill = 1000u,
    FiveHundoredYenCoin = 500u,
    HundoredYenCoin = 100u,
    FiftyYenCoin = 50u,
    TenYenCoin = 10u
  };

  struct Item {
    std::string name;
    unsigned int number;
    unsigned int price;
  };

  static const Item initialStock = {"コーラ", 5u, 120u};

  class Vendor {
    unsigned int totalAmount;
    unsigned int saleAmount;
    Item stock;

  public:
    Vendor();
    void input(const Money);
    void store(const Item&);
    void purchase();
    unsigned int payback();
    const std::string getStockInfomation() const;
    bool getPurchasable() const;
    unsigned int getTotalAmount() const;
    unsigned int getSaleAmount() const;
  };
}

