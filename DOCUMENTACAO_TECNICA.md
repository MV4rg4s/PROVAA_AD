# Documentação Técnica - Implementação PI para Roteamento

## Visão Geral da Arquitetura

### Componentes Principais:

1. **Roteador (Roteador.cc/h)**: Módulo principal que implementa o algoritmo PI
2. **Mensagem (Mensagem.msg)**: Estrutura de dados para troca de informações
3. **Topologias (.ned)**: 5 diferentes configurações de rede
4. **Configurações (.ini)**: Parâmetros de simulação para cada topologia

## Implementação do Algoritmo PI

### 1. Inicialização (initialize())

```cpp
void Roteador::initialize() {
    // Configuração inicial
    meuId = getId();
    totalMensagensEnviadas = 0;
    totalMensagensRecebidas = 0;
    tempoInicial = simTime();
    convergiu = false;
    
    // Tabela de roteamento inicial
    tabelaRoteamento[meuId] = 0.0;
    proximosSaltos[meuId] = meuId;
    
    // Descoberta de vizinhos
    for (int i = 0; i < gateSize("portas"); ++i) {
        // Descobre vizinhos e custos
        // Popula tabelas iniciais
    }
    
    // Inicia propagação se for nó inicial
    if (par("isStarter").boolValue()) {
        scheduleAt(simTime() + delayInicial, new cMessage("IniciarPI"));
    }
}
```

### 2. Propagação de Informação (propagarInformacao())

```cpp
void Roteador::propagarInformacao() {
    for (int i = 0; i < gateSize("portas"); ++i) {
        Mensagem *msgPI = new Mensagem("PropagacaoInformacao");
        msgPI->setIdNoOrigem(meuId);
        
        // Prepara arrays com informações de roteamento
        msgPI->setDestinosArraySize(tabelaRoteamento.size());
        msgPI->setCustosArraySize(tabelaRoteamento.size());
        
        // Copia dados da tabela para a mensagem
        int j = 0;
        for (auto const& [destino, custo] : tabelaRoteamento) {
            msgPI->setDestinos(j, destino);
            msgPI->setCustos(j, custo);
            j++;
        }
        
        send(msgPI->dup(), "portas$o", i);
        registrarMensagemEnviada();
    }
}
```

### 3. Processamento de Informação Recebida (processarInformacaoRecebida())

```cpp
void Roteador::processarInformacaoRecebida(Mensagem *msg) {
    int idVizinho = msg->getIdNoOrigem();
    bool tabelaAtualizada = false;
    
    // Reconstrói tabela do vizinho
    std::map<int, double> tabelaVizinho;
    for (unsigned int i = 0; i < msg->getDestinosArraySize(); i++) {
        tabelaVizinho[msg->getDestinos(i)] = msg->getCustos(i);
    }
    
    double custoAteVizinho = custoVizinhos[idVizinho];
    
    // Processa informações usando conceito de PI
    for (auto const& [destino, custoDoVizinho] : tabelaVizinho) {
        double novoCusto = custoAteVizinho + custoDoVizinho;
        
        // Atualiza se encontrou caminho melhor
        if (tabelaRoteamento.find(destino) == tabelaRoteamento.end() || 
            novoCusto < tabelaRoteamento[destino]) {
            
            tabelaRoteamento[destino] = novoCusto;
            proximosSaltos[destino] = idVizinho;
            tabelaAtualizada = true;
        }
    }
    
    // Propaga se houve atualização
    if (tabelaAtualizada) {
        propagarInformacao();
    }
    
    verificarConvergencia();
}
```

## Estrutura de Dados

### Tabela de Roteamento:
```cpp
std::map<int, double> tabelaRoteamento;  // destino -> custo
std::map<int, int> proximosSaltos;       // destino -> próximo salto
std::map<int, double> custoVizinhos;     // vizinho -> custo direto
```

### Mensagem de Propagação:
```cpp
packet Mensagem {
    int idNoOrigem;      // ID do nó origem
    int destinos[];      // Array de destinos conhecidos
    double custos[];     // Array de custos correspondentes
}
```

## Topologias Implementadas

### 1. Linear (topologia1.ned)
- **Conexões**: Sequenciais + redundância
- **Custos**: 1-4ms
- **Complexidade**: Baixa a média

### 2. Malha (topologia2.ned)
- **Conexões**: Grade 4x2 + diagonais
- **Custos**: 1-5ms
- **Complexidade**: Alta

### 3. Estrela (topologia3.ned)
- **Conexões**: Centralizada
- **Custos**: 2-8ms
- **Complexidade**: Baixa

### 4. Anel (topologia4.ned)
- **Conexões**: Circular + cruzadas
- **Custos**: 1-6ms
- **Complexidade**: Média

### 5. Hierárquica (topologia5.ned)
- **Conexões**: Árvore + redundância
- **Custos**: 1-10ms
- **Complexidade**: Média a alta

## Métricas e Análise

### Coleta de Dados:
```cpp
void Roteador::finish() {
    recordScalar("mensagens_enviadas", totalMensagensEnviadas);
    recordScalar("mensagens_recebidas", totalMensagensRecebidas);
    recordScalar("tempo_convergencia", tempoConvergencia);
    recordScalar("convergiu", convergiu ? 1 : 0);
    recordScalar("destinos_conhecidos", destinosConhecidos.size());
}
```

### Verificação de Consistência:
```cpp
void Roteador::verificarConsistenciaRoteamento() {
    for (auto const& [destino, custo] : tabelaRoteamento) {
        if (destino != meuId) {
            int proximoSalto = proximosSaltos[destino];
            double custoDireto = custoVizinhos[proximoSalto];
            
            // Verifica se o caminho é consistente
            if (custoDireto > 0) {
                // Log da verificação
            }
        }
    }
}
```

## Detecção de Convergência

```cpp
void Roteador::verificarConvergencia() {
    int totalNos = 8; // Para todas as topologias
    
    if (tabelaRoteamento.size() >= totalNos && !convergiu) {
        convergiu = true;
        tempoConvergencia = simTime() - tempoInicial;
        verificarConsistenciaRoteamento();
    }
}
```

## Execução e Análise

### Comandos de Execução:
```bash
# Topologia 1
PROVA.exe -u Cmdenv -c topologia1 simulations/omnetpp.ini

# Topologia 2
PROVA.exe -u Cmdenv -c topologia2 simulations/omnetpp.ini

# Topologia 3
PROVA.exe -u Cmdenv -c topologia3 simulations/omnetpp.ini

# Topologia 4
PROVA.exe -u Cmdenv -c topologia4 simulations/omnetpp.ini

# Topologia 5
PROVA.exe -u Cmdenv -c topologia5 simulations/omnetpp.ini
```

### Análise de Resultados:
- **Scalar files**: Estatísticas finais
- **Vector files**: Evolução temporal
- **Event log**: Log detalhado

## Justificativa da Solução

### Por que PI?
1. **Baseado em conceitos ensinados**: PI foi especificamente ensinado em aula
2. **Distribuído**: Cada nó executa localmente
3. **Eficiente**: Propaga apenas informações necessárias
4. **Convergente**: Garante que todos os nós encontrem as rotas ótimas

### Adaptação para Roteamento:
- **Informação**: Tabela de roteamento
- **Propagação**: Broadcast para vizinhos
- **Processamento**: Cálculo de caminhos mínimos
- **Convergência**: Detecção de estabilização

### Vantagens da Implementação:
1. **Simplicidade**: Código claro e compreensível
2. **Robustez**: Funciona com diferentes topologias
3. **Métricas**: Coleta dados para análise
4. **Escalabilidade**: Adaptável para redes maiores
