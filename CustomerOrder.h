// Name: Francesco Menghi
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <algorithm>
#include <string>
#include "Utilities.h"
#include "Station.h"

struct Item
{
    std::string m_itemName;
    unsigned int m_serialNumber = 0;
    bool m_isFilled = false;

    Item(const std::string &src) : m_itemName(src){};
};

class CustomerOrder
{
    std::string m_name;
    std::string m_product;
    unsigned int m_cntItem;
    Item **m_lstItem = nullptr;
    static size_t m_widthField;

public:
    CustomerOrder();
    CustomerOrder(std::string &param);
    CustomerOrder(const CustomerOrder &other);
    CustomerOrder &operator=(const CustomerOrder &other) = delete;
    CustomerOrder(CustomerOrder &&other) noexcept;
    CustomerOrder &operator=(CustomerOrder &&other) noexcept;
    ~CustomerOrder();
    bool isOrderFilled() const;
    bool isItemFilled(const std::string &itemName) const;
    void fillItem(Station &station, std::ostream &os);
    void display(std::ostream &os) const;
};

#endif