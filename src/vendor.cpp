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
    stock = item;
  }

  void Vendor::purchase() {
    if (getPurchasable()) {
      stock.number -= 1u;
      totalAmount -= stock.price;
      saleAmount += stock.price;
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


  bool Vendor::getPurchasable() const {
    return stock.price <= getTotalAmount()
           && stock.number > 0u;
  }

  const std::vector<Item> Vendor::getStockInfomation() const {
    return { stock };
  }

  unsigned int Vendor::getTotalAmount() const {
    return totalAmount;
  }

  unsigned int Vendor::getSaleAmount() const {
    return saleAmount;
  }
}
