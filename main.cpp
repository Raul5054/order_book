#include "OrderBook.hpp"
#include "Order.hpp"
#include "Transaction.hpp"
#include <iostream>

using namespace std;

int main()
{
    // sistema
    OrderBook book;
    cout << "Sistema criado" << endl;

    // INSERÇÃO DE OREDENS
    // compras
    book.submit(Order(100, 'B', 10.0, 1));
    book.submit(Order(200, 'B', 18.0, 2));
    book.submit(Order(300, 'B', 7.0, 3));
    book.submit(Order(400, 'B', 13.0, 4));

    // vendas (sem sucesso)
    book.submit(Order(500, 'S', 20.0, 5));
    book.submit(Order(600, 'S', 23.0, 6));
    book.submit(Order(700, 'S', 21.0, 7));

    // EXECUÇÃOS BEM SUCEDIDAS
    // exibição antes das transações
    cout << "\nAntes das transacoes" << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();

    // com compras
    book.submit(Order(800, 'B', 20.0, 8));
    book.submit(Order(900, 'B', 25.0, 9));

    // com vendas
    book.submit(Order(101, 'S', 16.0, 10));
    book.submit(Order(102, 'S', 9.0, 11));

    // exibição após as transações
    cout << "\nApos as transacoes" << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();
    cout << endl;

    // ORDENS NÃO EXECUTADAS
    // com compras agora
    book.submit(Order(103, 'B', 33.0, 12));
    book.submit(Order(104, 'B', 28.0, 13));

    // CANCELAMENTOS
    book.cancel(600);
    book.cancel(104);

    // RECUPERAÇÃO DE DADOS
    // para compras
    int b;
    Order *buys = book.getBuyOrders(&b);
    if (buys)
    {
        cout << "Numero de compras:" << endl;
        cout << "n = " << b << endl;
    }
    delete[] buys;

    // para vendas
    int s;
    Order *sells = book.getSellOrders(&s);
    if (sells)
    {
        cout << "Numero de vendas:" << endl;
        cout << "n = " << s << endl;
    }
    delete[] sells;

    // para transações
    int t;
    Transaction *trans = book.getTransactions(&t);
    if (trans)
    {
        cout << "Numero de transacoes:" << endl;
        cout << "n = " << t << endl;
    }
    delete[] trans;

    // EXIBIÇÃO
    cout << endl
         << "Exibicao final:" << endl;
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();
}