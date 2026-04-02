#include "OrderBook.hpp"
#include <iostream>

using namespace std;

OrderBook::OrderBook()
{
    this->BuyOrder = nullptr;
    this->SellOrder = nullptr;
    this->TranOrder = nullptr;
}

OrderBook::~OrderBook()
{
    OrderNode *atualBuy = BuyOrder;
    while (atualBuy != nullptr)
    {
        OrderNode *proximoBuy = atualBuy->next;
        delete atualBuy;
        atualBuy = proximoBuy;
    }

    OrderNode *atualSell = SellOrder;
    while (atualSell != nullptr)
    {
        OrderNode *proximoSell = atualSell->next;
        delete atualSell;
        atualSell = proximoSell;
    }

    TransactionNode *atualTran = TranOrder;
    while (atualTran != nullptr)
    {
        TransactionNode *proximoTran = atualTran->next;
        delete atualTran;
        atualTran = proximoTran;
    }
}

bool OrderBook::submit(Order order)
{
    // caso seja uma compra
    if (order.getType() == 'B')
    {
        OrderNode *melhor = nullptr;
        OrderNode *antMelhor = nullptr;
        OrderNode *atual = SellOrder;
        OrderNode *anterior = nullptr;
        while (atual != nullptr)
        {
            if (order.getPrice() >= atual->order.getPrice()) // válido
            {
                if (melhor == nullptr ||                                    // se não tem um melhor ainda
                    melhor->order.getPrice() > atual->order.getPrice() ||   // se o preço do atual é menor
                    (melhor->order.getPrice() == atual->order.getPrice() && // se o preço é igual mas o tempo do atual é menor
                     melhor->order.getTimestamp() > atual->order.getTimestamp()))
                {
                    melhor = atual;
                    antMelhor = anterior;
                }
            }
            anterior = atual;
            atual = atual->next;
        }

        // Se não achou uma contraparte
        if (melhor == nullptr)
        {
            // adiciona no final
            OrderNode *novoNo = new OrderNode(order);
            if (BuyOrder == nullptr)
            { // se a lista é vazia
                BuyOrder = novoNo;
            }
            else
            { // se já tem elementos, vai até o fim
                OrderNode *tempB = BuyOrder;
                while (tempB->next != nullptr)
                {
                    tempB = tempB->next;
                }
                // adiciona no fim
                tempB->next = novoNo;
            }

            return false;
        }
        // achou uma contraparte
        else
        {
            // cria uma transação
            Transaction tran(
                order.getId(),
                melhor->order.getId(),
                melhor->order.getPrice());

            TransactionNode *novaTran = new TransactionNode(tran);
            // adiciona no fim
            if (TranOrder == nullptr)
            { // se é vazia
                TranOrder = novaTran;
            }
            else
            { // se já tem elementos
                TransactionNode *tempT = TranOrder;
                while (tempT->next != nullptr)
                {
                    tempT = tempT->next;
                }
                tempT->next = novaTran;
            }

            // remove o nó 'melhor'
            if (antMelhor == nullptr)
            { // Se era o primerio da lista
                SellOrder = melhor->next;
            }
            else
            { // Se era do meio ou fim
                antMelhor->next = melhor->next;
            }
            delete melhor; // limpa a memória

            return true;
        }
    }

    // caso seja uma venda
    else if (order.getType() == 'S')
    {
        OrderNode *melhor = nullptr;
        OrderNode *antMelhor = nullptr;
        OrderNode *atual = BuyOrder;
        OrderNode *anterior = nullptr;
        while (atual != nullptr)
        {
            if (order.getPrice() <= atual->order.getPrice()) // válido
            {
                if (melhor == nullptr ||                                    // se não tem um melhor ainda
                    melhor->order.getPrice() < atual->order.getPrice() ||   // se o preço do atual é maior
                    (melhor->order.getPrice() == atual->order.getPrice() && // se o preço é igual mas o tempo do atual é menor
                     melhor->order.getTimestamp() > atual->order.getTimestamp()))
                {
                    melhor = atual;
                    antMelhor = anterior;
                }
            }
            anterior = atual;
            atual = atual->next;
        }

        // Se não achou uma contraparte
        if (melhor == nullptr)
        {
            // adiciona no final
            OrderNode *novoNo = new OrderNode(order);
            if (SellOrder == nullptr)
            { // se a lista é vazia
                SellOrder = novoNo;
            }
            else
            { // se já tem elementos, vai até o fim
                OrderNode *tempS = SellOrder;
                while (tempS->next != nullptr)
                {
                    tempS = tempS->next;
                }
                // adiciona no fim
                tempS->next = novoNo;
            }

            return false;
        }
        // achou uma contraparte
        else
        {
            // cria uma transação
            Transaction tran(
                melhor->order.getId(),
                order.getId(),
                melhor->order.getPrice());

            TransactionNode *novaTran = new TransactionNode(tran);
            // adiciona no fim
            if (TranOrder == nullptr)
            { // se é vazia
                TranOrder = novaTran;
            }
            else
            { // se já tem elementos
                TransactionNode *tempT = TranOrder;
                while (tempT->next != nullptr)
                {
                    tempT = tempT->next;
                }
                tempT->next = novaTran;
            }

            // remove o nó 'melhor'
            if (antMelhor == nullptr)
            { // Se era o primerio da lista
                BuyOrder = melhor->next;
            }
            else
            { // Se era do meio ou fim
                antMelhor->next = melhor->next;
            }
            delete melhor; // limpa a memória

            return true;
        }
    }
    return false;
}

bool OrderBook::cancel(int id)
{
    // Primeiro procura nas compras
    OrderNode *atualB = BuyOrder;
    OrderNode *anteriorB = nullptr;
    while (atualB != nullptr)
    {
        // se achou, deleta
        if (id == atualB->order.getId())
        {
            // se for o primeiro
            if (anteriorB == nullptr)
            {
                BuyOrder = atualB->next;
                delete atualB;
                return true;
            }
            else
            { // se era do meio ou do fim
                anteriorB->next = atualB->next;
                delete atualB;
                return true;
            }
        }
        anteriorB = atualB;
        atualB = atualB->next;
    }

    // Procura nas vendas agora
    OrderNode *atualS = SellOrder;
    OrderNode *anteriorS = nullptr;
    while (atualS != nullptr)
    {
        // se achou, deleta
        if (id == atualS->order.getId())
        {
            // se for o primeiro
            if (anteriorS == nullptr)
            {
                SellOrder = atualS->next;
                delete atualS;
                return true;
            }
            else
            { // se era do meio ou do fim
                anteriorS->next = atualS->next;
                delete atualS;
                return true;
            }
        }
        anteriorS = atualS;
        atualS = atualS->next;
    }

    // Se não achou, retorna false
    return false;
}

Order *OrderBook::getBuyOrders(int *n)
{
    // conta os elementos
    int quant = 0;
    OrderNode *atual = BuyOrder;
    while (atual != nullptr)
    {
        quant++;
        atual = atual->next;
    }

    *n = quant;
    if (quant == 0)
        return nullptr; // se não tem elementos

    Order *array = new Order[quant];
    atual = BuyOrder;

    for (int i = 0; i < quant; i++)
    {
        array[i] = atual->order;
        atual = atual->next;
    }

    return array;
}

Order *OrderBook::getSellOrders(int *n)
{
    // conta os elementos
    int quant = 0;
    OrderNode *atual = SellOrder;
    while (atual != nullptr)
    {
        quant++;
        atual = atual->next;
    }

    *n = quant;
    if (quant == 0)
        return nullptr; // se não tem elementos

    Order *array = new Order[quant];
    atual = SellOrder;

    for (int i = 0; i < quant; i++)
    {
        array[i] = atual->order;
        atual = atual->next;
    }

    return array;
}

Transaction *OrderBook::getTransactions(int *n)
{
    // conta os elementos
    int quant = 0;
    TransactionNode *atual = TranOrder;
    while (atual != nullptr)
    {
        quant++;
        atual = atual->next;
    }

    *n = quant;
    if (quant == 0)
        return nullptr; // se não tem elementos

    Transaction *array = new Transaction[quant];
    atual = TranOrder;

    for (int i = 0; i < quant; i++)
    {
        array[i] = atual->tran;
        atual = atual->next;
    }

    return array;
}

void OrderBook::printBuyOrders()
{
    cout << endl;
    cout << "Buy Orders:" << endl; // Cabeçalho

    // Se a lista é vazia
    if (BuyOrder == nullptr)
    {
        cout << "(empty)" << endl;
        return;
    }

    // Se tem elementos
    OrderNode *atual = BuyOrder;
    while (atual != nullptr)
    {
        cout << '['
             << atual->order.getId()
             << " | " << atual->order.getPrice()
             << " | "
             << atual->order.getTimestamp()
             << ']'
             << endl;

        atual = atual->next;
    }
}

void OrderBook::printSellOrders()
{
    cout << endl;
    cout << "Sell Orders:" << endl; // Cabeçalho

    // Se a lista é vazia
    if (SellOrder == nullptr)
    {
        cout << "(empty)" << endl;
        return;
    }

    // Se tem elementos
    OrderNode *atual = SellOrder;
    while (atual != nullptr)
    {
        cout << '['
             << atual->order.getId()
             << " | " << atual->order.getPrice()
             << " | "
             << atual->order.getTimestamp()
             << ']'
             << endl;

        atual = atual->next;
    }
}

void OrderBook::printTransactions()
{
    cout << endl;
    cout << "Transactions:" << endl; // Cabeçalho

    // Se a lista é vazia
    if (TranOrder == nullptr)
    {
        cout << "(empty)" << endl;
        return;
    }

    // Se tem elementos
    TransactionNode *atual = TranOrder;
    while (atual != nullptr)
    {
        cout << '['
             << atual->tran.getBuyOrderId()
             << " , " << atual->tran.getSellOrderId()
             << " , "
             << atual->tran.getExecutionPrice()
             << ']'
             << endl;

        atual = atual->next;
    }
}