#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include "Order.hpp"
#include "Transaction.hpp"

struct OrderNode
{
    Order order;
    OrderNode *next;

    OrderNode(Order order) : order(order), next(nullptr) {}
};

struct TransactionNode
{
    Transaction tran;
    TransactionNode *next;

    TransactionNode(Transaction tran) : tran(tran), next(nullptr) {}
};

class OrderBook
{

private:
    // Estruturas internas escolhidas pelos alunos
    // para armazenar ordens de compra, venda e transações
    OrderNode *BuyOrder;
    OrderNode *SellOrder;
    TransactionNode *TranOrder;

public:
    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order *getBuyOrders(int *n);
    Order *getSellOrders(int *n);
    Transaction *getTransactions(int *n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();

    // Outros métodos auxiliares, se necessário
};

#endif