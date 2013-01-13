#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <map>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

namespace AutoVendor {

  namespace rng {
    using namespace boost::range;
    using namespace boost::adaptors;
  }

  enum class Money : unsigned int {
    ThousandYenBill = 1000u,
    FiveHundredYenCoin = 500u,
    HundredYenCoin = 100u,
    FiftyYenCoin = 50u,
    TenYenCoin = 10u
  };

  enum class DrinkName {
    Coke
  };
  struct invalid_drinkname: std::exception {
    invalid_drinkname(DrinkName d): msg("invalid drink name : " + std::to_string(static_cast<unsigned>(d))) { }
    virtual ~invalid_drinkname() noexcept { }
    std::string msg;
    virtual const char *what() const noexcept {
      return msg.c_str();
    }
  };
  inline std::string to_string(DrinkName d) {
    switch (d) {
    case DrinkName::Coke:
      return "Coke";
    }
    throw invalid_drinkname(d);
  }
  struct Item {
    DrinkName name;
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
    ss << "名前:" << to_string(item.name) << ", 在庫:" << item.number
       << ", 価格:" << item.price;
    return ss.str();
  }

  static const Item initialStock = {DrinkName::Coke, 5u, 120u};

  class Vendor {
    unsigned int totalAmount;
    unsigned int paybackAmount;
    unsigned int saleAmount;
    std::map<DrinkName, Item> stock;

  public:
    Vendor();
    void input(const Money);
    void store(const Item&);
    void purchase();

    void refund();
    unsigned int getChangeAmount();
    void clearChange();

    const std::vector<Item> getStockInfomation() const;
    bool getPurchasableAny() const;
    unsigned int getTotalAmount() const;
    unsigned int getSaleAmount() const;
  };
}

