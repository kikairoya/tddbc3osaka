namespace std { class type_info; }
#include "vendor.h"
#include <sstream>
#include <vector>

namespace AutoVendor {

  Vendor::Vendor() : totalAmount(0u), paybackAmount(0u), saleAmount(0u), stock(initialStock) {
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
    stock.insert(item);
  }

  void Vendor::purchase() {
    auto ite = rng::find_if(stock, [this](const Item &item) { return item.getPrice() <= getTotalAmount(); });
    if (ite != stock.end()) {
      auto i = *ite;
      stock.erase(ite);
      totalAmount -= i.getPrice();
      saleAmount += i.getPrice();
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
    return std::any_of(stock.begin(), stock.end(), [this](const Item &item){
      return item.getPrice() <= getTotalAmount();
    });
  }

  const std::multiset<Item> Vendor::getStockInfomation() const {
    return stock;
  }

  unsigned int Vendor::getTotalAmount() const {
    return totalAmount;
  }

  unsigned int Vendor::getSaleAmount() const {
    return saleAmount;
  }
}
