#include "Transaction.hpp"

Transaction::Transaction(int buy_order_id, int sell_order_id, float execution_price)
{
    this->buy_order_id = buy_order_id;
    this->sell_order_id = sell_order_id;
    this->execution_price = execution_price;
}

Transaction::Transaction() : buy_order_id(0), sell_order_id(0), execution_price(0.0) {}

Transaction::~Transaction() {}

int Transaction::getBuyOrderId() { return buy_order_id; }
int Transaction::getSellOrderId() { return sell_order_id; }
float Transaction::getExecutionPrice() { return execution_price; }