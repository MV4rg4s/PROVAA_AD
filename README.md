# Roteamento com Menor Custo de Tempo em Sistemas Distribuídos

## Introdução ao Problema

Este trabalho implementa um sistema distribuído de roteamento que utiliza o algoritmo **PI (Propagação de Informação)** para calcular as rotas com menor tempo de transmissão entre todos os nós da rede. Cada nó conhece apenas seus vizinhos diretos e os tempos de transmissão associados, e através da propagação de informações, constrói uma tabela de roteamento completa.

## Descrição da Solução em Alto Nível

### Pseudocódigo do Algoritmo PI para Roteamento:

```
Para cada nó i:
1. Inicializar tabela de roteamento com informação local
   - Custo para si mesmo = 0
   - Custo para vizinhos diretos = custo do enlace
   
2. Enquanto não convergiu:
   a) Propagar tabela de roteamento atual para todos os vizinhos
   b) Receber tabelas de roteamento dos vizinhos
   c) Para cada destino j:
      - Calcular novo custo = custo até vizinho + custo do vizinho até j
      - Se novo custo < custo atual, atualizar tabela
   d) Se tabela foi atualizada, continuar propagação
   e) Senão, convergiu

3. Verificar consistência das rotas calculadas
```

### Conceitos Utilizados:

- **PI (Propagação de Informação)**: Cada nó propaga suas informações de roteamento para os vizinhos
- **Algoritmo Distribuído**: Cada nó executa localmente sem conhecimento global da rede
- **Convergência**: O algoritmo para quando nenhuma atualização é necessária

## Implementação da Solução

### Estrutura de Mensagens:
```cpp
packet Mensagem {
    int idNoOrigem;      // ID do nó que enviou a mensagem
    int destinos[];      // Array de destinos conhecidos
    double custos[];     // Array de custos correspondentes
}
```

### Funcionalidades Implementadas:

1. **Descoberta de Vizinhos**: Cada nó descobre automaticamente seus vizinhos diretos
2. **Propagação de Informação**: Tabelas de roteamento são propagadas entre vizinhos
3. **Cálculo de Rotas**: Caminhos de menor custo são calculados iterativamente
4. **Detecção de Convergência**: O algoritmo detecta quando todas as rotas foram encontradas
5. **Coleta de Métricas**: Mensagens trocadas, tempo de convergência, consistência

## Cenários de Uso: Topologias Implementadas

### 1. Topologia Linear (topologia1.ned)
- **Estrutura**: 8 nós em sequência com conexões adicionais
- **Complexidade**: Baixa a média
- **Custos**: 1-4ms
- **Características**: Simula rede backbone com redundância

### 2. Topologia Malha (topologia2.ned)
- **Estrutura**: 8 nós em grade 4x2 com conexões diagonais
- **Complexidade**: Alta
- **Custos**: 1-5ms
- **Características**: Alta redundância, múltiplos caminhos

### 3. Topologia Estrela (topologia3.ned)
- **Estrutura**: Nó central conectado a todos os outros
- **Complexidade**: Baixa
- **Custos**: 2-8ms
- **Características**: Centralizada, ponto único de falha

### 4. Topologia Anel (topologia4.ned)
- **Estrutura**: 8 nós em formato circular com conexões cruzadas
- **Complexidade**: Média
- **Custos**: 1-6ms
- **Características**: Redundância circular, caminhos alternativos

### 5. Topologia Hierárquica (topologia5.ned)
- **Estrutura**: Árvore com 3 níveis e conexões redundantes
- **Complexidade**: Média a alta
- **Custos**: 1-10ms
- **Características**: Estrutura organizacional, hierarquia clara

## Análise dos Resultados

### Métricas Coletadas:

1. **Número de Mensagens**:
   - Mensagens enviadas por nó
   - Mensagens recebidas por nó
   - Total de mensagens na rede

2. **Tempo de Convergência**:
   - Tempo até todos os nós convergirem
   - Comparação entre topologias

3. **Consistência de Roteamento**:
   - Verificação se caminhos são ótimos
   - Validação de tabelas de roteamento

### Como Executar as Simulações no OMNeT++:

1. **Abrir o projeto no OMNeT++ IDE**
2. **Compilar o projeto** (Build Project)
3. **Executar as simulações**:
   - Abrir o arquivo `simulations/omnetpp.ini`
   - Selecionar a configuração desejada no menu "Run Configuration":
     - `topologia1` - Topologia Linear
     - `topologia2` - Topologia Malha
     - `topologia3` - Topologia Estrela
     - `topologia4` - Topologia Anel
     - `topologia5` - Topologia Hierárquica
   - Clicar em "Run" para executar a simulação

**Ou via linha de comando:**
```bash
# Executar cada topologia
PROVA.exe -u Cmdenv -c topologia1 simulations/omnetpp.ini
PROVA.exe -u Cmdenv -c topologia2 simulations/omnetpp.ini
PROVA.exe -u Cmdenv -c topologia3 simulations/omnetpp.ini
PROVA.exe -u Cmdenv -c topologia4 simulations/omnetpp.ini
PROVA.exe -u Cmdenv -c topologia5 simulations/omnetpp.ini
```

### Análise dos Resultados:

Os resultados são salvos em `simulations/results/` e podem ser analisados usando:
- **Scalar files**: Estatísticas finais (mensagens, tempo de convergência)
- **Vector files**: Evolução temporal das métricas
- **Event log**: Log detalhado de eventos da simulação

## Conclusão e Sugestões de Melhoria

### Conclusões:

1. **Eficácia do PI**: O algoritmo PI é eficaz para roteamento distribuído
2. **Convergência**: Todas as topologias convergem corretamente
3. **Escalabilidade**: O algoritmo funciona bem com diferentes complexidades de rede
4. **Robustez**: A solução é robusta e detecta convergência adequadamente

### Sugestões de Melhoria:

1. **Otimização de Mensagens**: Implementar agregação de mensagens para reduzir overhead
2. **Detecção de Falhas**: Adicionar mecanismos para detectar nós/links falhos
3. **Métricas Avançadas**: Implementar análise de latência e throughput
4. **Topologias Dinâmicas**: Suportar mudanças na topologia durante execução
5. **Comparação com Outros Algoritmos**: Implementar PIF e Conectividade para comparação

### Justificativa da Solução:

Esta implementação utiliza exclusivamente os conceitos de **PI (Propagação de Informação)** ensinados em aula, adaptando-os para o contexto de roteamento. A solução é distribuída, eficiente e atende a todos os requisitos especificados no enunciado do trabalho.
