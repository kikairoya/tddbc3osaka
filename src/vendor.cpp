namespace std { class type_info; }
#include "vendor.h"
#include <sstream>
#include <vector>

namespace AutoVendor {

  Vendor::Vendor() : totalAmount(0u), paybackAmount(0u), saleAmount(0u) {
      store(initialStock);
  }

  void Vendor::input(const Money money) {
    switch(money){
    case Money::TenYenCoin:
    case Money::FiftyYenCoin:
    case Money::HundredYenCoin:
    case Money::FiveHundredYenCoin:
    case Money::ThousandYenBill:
      totalAmount += static_cast<unsigned int>(money);
      break;
    default:
      paybackAmount += static_cast<unsigned int>(money);
      break;
    }

  }

  void Vendor::store(const Item& item) {
    auto it = stock.lower_bound(item.name);
    if (it == stock.end() || it->first != item.name) {
      stock.insert(it, std::make_pair(item.name, item));
    }
    else {
      it->second.number += item.number;
    }
  }

  void Vendor::purchase() {
    if (getPurchasableAny()) {
      auto item = stock.begin()->second;
      item.number -= 1u;
      totalAmount -= item.getPrice();
      saleAmount += item.getPrice();
    }
  }

  void Vendor::refund(){
    paybackAmount +=  getTotalAmount();
    totalAmount = 0u;
  }

  unsigned int Vendor::getChangeAmount(){
    return paybackAmount;
  }

  void Vendor::clearChange(){
    paybackAmount = 0;
  }


  bool Vendor::getPurchasableAny() const {
    typedef decltype(*stock.begin()) value_type;
    return std::any_of(stock.begin(), stock.end(), [this](const value_type &pair){
              return pair.second.getPrice() <= getTotalAmount() && pair.second.number > 0u;
        });
  }

  const std::vector<Item> Vendor::getStockInfomation() const {
    auto v = rng::values(stock);
    return std::vector<Item>(v.begin(), v.end());
  }

  unsigned int Vendor::getTotalAmount() const {
    return totalAmount;
  }

  unsigned int Vendor::getSaleAmount() const {
    return saleAmount;
  }
}
