# Philosophers

Implementação do projeto **Philosophers** da Escola 42, desenvolvida em **C** utilizando **threads (`pthread`)** e **mutexes** para resolver o clássico problema da sincronização conhecido como **Dining Philosophers Problem**.

---

## 📖 Sobre o projeto

O problema dos filósofos jantando foi proposto por Edsger Dijkstra em 1965 e é um dos exemplos mais conhecidos de problemas de concorrência.

Cinco filósofos estão sentados ao redor de uma mesa circular. Entre cada filósofo existe um garfo. Para comer, cada filósofo precisa utilizar **dois garfos**, o da esquerda e o da direita.

Cada filósofo executa continuamente as seguintes ações:

* 🍝 Comer;
* 😴 Dormir;
* 🤔 Pensar.

Entretanto, o programa deve garantir que:

* Não ocorra **deadlock**;
* Não existam condições de corrida (*race conditions*);
* As mensagens impressas não sejam corrompidas;
* A morte de um filósofo seja detectada corretamente;
* A simulação seja encerrada quando necessário.

---

## ⚙️ Regras da simulação

O programa recebe os seguintes argumentos:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Argumentos

| Argumento                                   | Descrição                                                       |
| ------------------------------------------- | --------------------------------------------------------------- |
| `number_of_philosophers`                    | Quantidade de filósofos e de garfos                             |
| `time_to_die`                               | Tempo máximo (em ms) que um filósofo pode ficar sem comer       |
| `time_to_eat`                               | Tempo gasto para comer                                          |
| `time_to_sleep`                             | Tempo gasto dormindo                                            |
| `number_of_times_each_philosopher_must_eat` | (Opcional) Número de refeições que cada filósofo deve completar |

Todos os valores devem ser números inteiros positivos.

---

## ▶️ Compilação

Para compilar o projeto:

```bash
make
```

O executável gerado será:

```bash
./philo
```

---

## 🧹 Regras do Makefile

### Compilar

```bash
make
```

### Remover arquivos objeto

```bash
make clean
```

### Remover objetos e executável

```bash
make fclean
```

### Recompilar tudo

```bash
make re
```

---

## 🚀 Exemplos de execução

### Simulação simples

```bash
./philo 5 800 200 200
```

Saída esperada:

```text
0 1 is thinking
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
...
```

---

### Com número mínimo de refeições

```bash
./philo 5 800 200 200 7
```

A simulação será encerrada quando todos os filósofos tiverem comido pelo menos sete vezes.

---

### Caso especial: apenas um filósofo

```bash
./philo 1 800 200 200
```

Saída:

```text
0 1 has taken a fork
800 1 died
```

Como existe apenas um garfo disponível, o filósofo nunca conseguirá comer.

---

## 🏗️ Estrutura do projeto

```text
.
├── Makefile
├── philo.h
├── main.c
├── inits.c
├── monitor.c
├── philo_routine.c
├── start_simulations.c
├── parse_args.c
└── utils.c
```

---

## 📂 Descrição dos arquivos

### `main.c`

Responsável por:

* Inicializar a simulação;
* Criar as threads;
* Aguardar o término das threads;
* Liberar a memória utilizada.

---

### `inits.c`

Responsável por:

* Validar argumentos;
* Interpretar os parâmetros recebidos;
* Alocar memória;
* Inicializar mutexes;
* Inicializar os filósofos.

---

### `monitor.c`

Implementa a thread monitora responsável por:

* Verificar se algum filósofo morreu;
* Encerrar a simulação em caso de morte;
* Verificar se todos os filósofos atingiram o número mínimo de refeições.

---

### `philo_routine.c`

Contém:

* A rotina principal dos filósofos;
* Impressão protegida das mensagens;
* Verificação do estado da simulação;
* Tratamento do caso de apenas um filósofo.

---

### `start_simulations.c`

Responsável pelas ações dos filósofos:

* Pegar os garfos;
* Soltar os garfos;
* Comer;
* Dormir;
* Pensar.

---

### `utils.c`

Funções auxiliares:

* Obtenção do tempo atual;
* Sleep de maior precisão;
* Conversão de string para inteiro;
* Validação de números.

---

### `philo.h`

Contém:

* Estruturas do projeto;
* Protótipos das funções;
* Inclusão das bibliotecas necessárias.

---

## 🧵 Estratégia de sincronização

### Mutex para os garfos

Cada garfo é representado por um mutex:

```c
pthread_mutex_t *forks;
```

Um filósofo só pode comer após bloquear os dois mutexes correspondentes aos seus garfos.

---

### Prevenção de deadlock

Os garfos são sempre adquiridos na mesma ordem:

```c
if (left < right)
{
    first = left;
    second = right;
}
else
{
    first = right;
    second = left;
}
```

Essa estratégia elimina a espera circular e impede deadlocks.

---

### Impressão protegida

Todas as mensagens são protegidas por um mutex:

```c
pthread_mutex_t print;
```

Isso evita que múltiplas threads escrevam simultaneamente no terminal.

---

### Controle de morte

A variável:

```c
int dead;
```

é protegida por:

```c
pthread_mutex_t dead_mutex;
```

garantindo que todas as threads tenham uma visão consistente do estado da simulação.

---

### Controle de refeições

O número de filósofos que atingiram o objetivo é armazenado em:

```c
int finished;
```

e protegido por:

```c
pthread_mutex_t finish_mutex;
```

---

## ⏱️ Controle de tempo

O tempo é medido em milissegundos utilizando:

```c
gettimeofday()
```

através da função:

```c
long get_time(void);
```

Para evitar uso excessivo de CPU durante esperas, foi implementada:

```c
void ft_usleep(long time);
```

que realiza pequenas pausas até atingir o tempo desejado.

---

## 🔄 Fluxo da simulação

```text
Inicialização
      ↓
Criação do monitor
      ↓
Criação das threads dos filósofos
      ↓
Pensar
      ↓
Pegar os garfos
      ↓
Comer
      ↓
Soltar os garfos
      ↓
Dormir
      ↓
Voltar a pensar
      ↓
Monitor verifica mortes/finalização
      ↓
Encerramento
      ↓
Liberação de recursos
```

---

## 🧪 Testes realizados

* ✅ 1 filósofo;
* ✅ 2 filósofos;
* ✅ Número elevado de filósofos;
* ✅ Encerramento por morte;
* ✅ Encerramento por número mínimo de refeições;
* ✅ Validação de argumentos inválidos;
* ✅ Verificação de ausência de deadlocks.

---

## 🛠️ Tecnologias utilizadas

* Linguagem C;
* POSIX Threads (`pthread`);
* Mutexes;
* `gettimeofday`;
* GNU Make.

---

## 📚 Conceitos estudados

Este projeto explora diversos conceitos fundamentais de programação concorrente, incluindo:

* Criação e gerenciamento de threads;
* Exclusão mútua;
* Sincronização;
* Deadlocks;
* Race conditions;
* Compartilhamento seguro de recursos;
* Monitoramento de estados concorrentes;
* Controle preciso de tempo.

---

## 👩‍💻 Autoria

Desenvolvido como parte do currículo da **42**.

Autores:

* Cristiane Suominsky (`csuomins`)
* Cris Sky (`cris_sky`)
