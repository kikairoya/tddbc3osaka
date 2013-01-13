#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <map>
#include <set>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/operators.hpp>

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
  struct Item: boost::equality_comparable<Item, boost::less_than_comparable<Item> > {
    Item(DrinkName name): name(name) {
      switch (name) {
      case DrinkName::Coke:
        return;
      }
      throw invalid_drinkname(name);
    }
    friend bool operator ==(const Item &x, const Item &y) {
      return x.name == y.name;
    }
    friend bool operator <(const Item &x, const Item &y) {
      return x.name < y.name;
    }
    unsigned getPrice() const {
      switch (name) {
      case DrinkName::Coke:
        return 120;
      }
      throw invalid_drinkname(name);
    }
    DrinkName getName() const { return name; }
  private:
    DrinkName name;
  };

  static const std::multiset<Item> initialStock{{DrinkName::Coke}, {DrinkName::Coke}, {DrinkName::Coke}, {DrinkName::Coke}, {DrinkName::Coke}};

  class Vendor {
    unsigned int totalAmount;
    unsigned int paybackAmount;
    unsigned int saleAmount;
    std::multiset<Item> stock;

  public:
    Vendor();
    void input(const Money);
    void store(const Item&);
    void purchase();

    void refund();
    unsigned int getChangeAmount();
    void clearChange();

    const std::multiset<Item> getStockInfomation() const;
    bool getPurchasableAny() const;
    unsigned int getTotalAmount() const;
    unsigned int getSaleAmount() const;
  };
}

