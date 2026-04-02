# Order Book (Sistema de Ordens de Compra e Venda)

## Descrição do projeto
Este projeto implementa um sistema que gerencia ordens de compra e venda de ações.
Para cada nova ordem adicionada, o sistema procura uma contraparte correspondente e compatível, se encontrar, realiza uma
transação automaticamente, se não, adiciona em espera.

**Funcionalidades:**
- Inserir uma ordem (`'B'` para compra, `'S'` para venda), cada uma com identificador e timestamp.
- Executa automaticamente transações, desde que a ordem de compra tenha preço maior ou igual a uma ordem de venda e vice-versa,
em caso de igualdade, verifica-se o menor tempstamp.
- Cancelar ordens ativas.
- Verificar quantas ordens estão ativas e quantos transações foram realizadas, gerando também cópias com arrays dinâmicos.
- Exibição das ordens de compra e venda e as transações realizadas.

## Estruturas Usadas
Neste projeto, foram utilizadas três listas encadeadas simples:
- **BuyOrder**: armazena ordens de compras ativas, cada nó contém uma ordem `Order` e um ponteiro para a próxima ordem `next`.
- **SellOrder**: análogo à BuyOrder.
- **TransactionOrder**: armazena cada transação realizada, cada nó contém uma transação `Transaction` e um ponteiro para a
- próxima transação `next`.

Quando uma ordem é inserida e o sistema não encontra uma contraparte, ela é adicionada ao fim da lista encadeada correspondente, 
o mesmo acontece quando uma transação ocorre, ou seja, para cada ordem e transação adicionada, o sistema percorre toda lista existente
e adiciona ao fim, isso foi feito para manter a ordem do timestamp (primeiros adicionados ficam no começo). Para cancelar, o sistema 
percorre toda a lista de BuyOrder e SellOrder, respectivamente, procurando pelo id correspondente,e elimina a ordem ao encontrar ou 
retorna false se não achar.

## Compilação
Para complilar, utilize o comando:
```bash
g++ main.cpp OrderBook.cpp Order.cpp Transaction.cpp -o order_book
```

## Execução
Para executar, utilize o comando:
```bash
./order_book
```

## Autores
- Raul Medici Martinelli
- Pablo Levy Fernandes Alcântara
