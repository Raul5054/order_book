#include "Order.hpp"

Order::Order(int id, char type, float price, int timestamp)
{
    this->id = id;
    this->type = type;
    this->price = price;
    this->timestamp = timestamp;
}

Order::Order() : id(0), type(' '), price(0.0), timestamp(0) {}

Order::~Order() {}

int Order::getId() { return id; }
char Order::getType() { return type; }
float Order::getPrice() { return price; }
int Order::getTimestamp() { return timestamp; }