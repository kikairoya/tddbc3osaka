#pragma once

#include <string>
#include <sstream>
#include <vector>

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
    friend bool operator ==(const Item &x, const Item &y) {
      return x.name == y.name && x.number == y.number && x.price == y.price;
    }
    friend bool operator !=(const Item &x, const Item &y) {
      return !( x == y );
    }
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

    const std::vector<Item> getStockInfomation() const;
    bool getPurchasable() const;
    unsigned int getTotalAmount() const;
    unsigned int getSaleAmount() const;
  };
}

