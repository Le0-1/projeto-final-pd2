| Classe: `Conta`||
| :------------------------ | ----------------- |
| **Responsabilidades**     | **Colaborações**  |
| saldoInicial              | `Transação`       |
| saldoAtual                | `ContaBancaria`   |
| nome                      | `Carteira`        |

| Classe: `ContaBancaria`||
| :--------------------- | ---------------------|
| **Responsabilidades:** | **Colaborações:**    |
| cartoesCredito         | `cartao`             |

| Classe: `Carteira`||
| :--------------------- | ---------------------|
| **Responsabilidades:** | **Colaborações:**    |
|                        |                      |

| Classe: `Transacao`||
| :--------------------- | ---------------------|
| **Responsabilidades:** | **Colaborações:**    |
| data                   |                      |
| valor                  |                      |
| descricao              |                      |

| Classe: `Despesas`||
| :--------------------- | -------------------- |
| **Responsabilidades:** | **Colaborações:**    |
| origem                 | `ContaBancaria`      |
| valor                  |                      |
| totalAPagar            |                      |
| despesaCartaoCredito   |                      |
| vencimento             |                      |

| Classe: `Transferencia`||
| :--------------------- | -------------------- |
| **Responsabilidades:** | **Colaborações:**    |
| origem                 | `ContaBancaria`      |
| destino                |                      |


| Classe: `Orcamento`||
| :--------------------- | ----------------- |
| **Filha:**             | **Pai:**          |
| **Responsabilidades:** | **Colaborações:** |
| valor                  |                   |
| fluxo                  |                   |
| periodo                |                   |
