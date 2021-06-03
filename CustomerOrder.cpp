// Name: Francesco Menghi
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <string>
#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder()
{
    m_cntItem = 0;
}

CustomerOrder::CustomerOrder(std::string &param)
{
    Utilities util;
    size_t next_pos = 0;
    m_cntItem = 0;
    bool more = true;
    m_name = util.extractToken(param, next_pos, more);
    m_product = util.extractToken(param, next_pos, more);

    // count number of delimiters in param and subtract 1 for the first delimiter
    int cnt = std::count(param.begin(), param.end(), util.getDelimiter()) - 1;
    m_lstItem = new Item *[cnt];
    do
    {
        m_lstItem[m_cntItem++] = new Item(util.extractToken(param, next_pos, more));
        if (CustomerOrder::m_widthField < util.getFieldWidth())
            CustomerOrder::m_widthField = util.getFieldWidth();
    } while (more);
}

CustomerOrder::CustomerOrder(const CustomerOrder &other)
{
    throw std::exception();
}

CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept
{
    *this = std::move(other);
}

CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept
{
    if (this != &other)
    {
        if (m_lstItem)
        {
            for (unsigned int i = 0; i < m_cntItem; i++)
                delete m_lstItem[i];
            delete[] m_lstItem;
        }
        m_lstItem = other.m_lstItem;
        other.m_lstItem = nullptr;

        m_name = other.m_name;
        other.m_name.clear();
        m_product = other.m_product;
        other.m_product.clear();
        m_cntItem = other.m_cntItem;
        other.m_cntItem = 0;
    }
    return *this;
}

CustomerOrder::~CustomerOrder()
{
    for (unsigned int i = 0; i < m_cntItem; i++)
        delete m_lstItem[i];
    delete[] m_lstItem;
}

bool CustomerOrder::isOrderFilled() const
{
    bool res = true;
    for (unsigned int i = 0u; i < m_cntItem; i++)
    {
        if (!m_lstItem[i]->m_isFilled)
            res = false;
    }
    return res;
}

bool CustomerOrder::isItemFilled(const std::string &itemName) const
{
    bool res = true;
    for (unsigned int i = 0u; i < m_cntItem; i++)
    {
        if (m_lstItem[i]->m_itemName == itemName)
            res = m_lstItem[i]->m_isFilled;
    }
    return res;
}

void CustomerOrder::fillItem(Station &station, std::ostream &os)
{
    for (unsigned int i = 0u; i < m_cntItem; i++)
    {
        if (m_lstItem[i]->m_itemName == station.getItemName())
        {
            if (station.getQuantity() > 0)
            {
                station.updateQuantity();
                m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
            }
            else
                os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
        }
    }
}

void CustomerOrder::display(std::ostream &os) const
{
    os << m_name << " - " << m_product << "\n";

    for (unsigned int i = 0u; i < m_cntItem; i++)
    {
        os << "[";
        os.fill('0');
        os.width(6);
        os << m_lstItem[i]->m_serialNumber << "] ";
        os.fill(' ');
        os.width(m_widthField);
        os.setf(std::ios::left);
        os << m_lstItem[i]->m_itemName << " - ";
        m_lstItem[i]->m_isFilled ? os << "FILLED\n" : os << "MISSING\n";
        os.unsetf(std::ios::left);
    }
}
