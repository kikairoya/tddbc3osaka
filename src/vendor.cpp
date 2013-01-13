namespace std { class type_info; }
#include "vendor.h"
#include <sstream>

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
    }  }

  unsigned int Vendor::payback() {
    const unsigned int change = getTotalAmount();
    totalAmount = 0u;
    return change;
  }

  bool Vendor::getPurchasable() const {
    return stock.price <= getTotalAmount()
           && stock.number > 0u;
  }

  const std::string Vendor::getStockInfomation() const {
    std::stringstream ss;
    ss << "名前:" << stock.name << ", 在庫:" << stock.number
       << ", 価格:" << stock.price;

    return ss.str();
  }

  unsigned int Vendor::getTotalAmount() const {
    return totalAmount;
  }

  unsigned int Vendor::getSaleAmount() const {
    return saleAmount;
  }
}