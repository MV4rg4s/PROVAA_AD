// Implementação baseada em PI (Propagação de Informação) para Roteamento com Menor Custo
// Algoritmo distribuído onde cada nó propaga suas informações de roteamento para os vizinhos

#include "Roteador.h"

Define_Module(Roteador);

int Roteador::extrairNumeroNo(const std::string& nomeNo) {
    // Tenta diferentes estratégias para extrair o número
    
    // Estratégia 1: Procura por "no" seguido de número
    size_t pos = nomeNo.find("no");
    if (pos != std::string::npos && pos + 2 < nomeNo.length()) {
        std::string numeroStr = nomeNo.substr(pos + 2);
        // Remove caracteres não numéricos
        std::string numeroLimpo;
        for (char c : numeroStr) {
            if (c >= '0' && c <= '9') {
                numeroLimpo += c;
            }
        }
        if (!numeroLimpo.empty()) {
            return std::stoi(numeroLimpo);
        }
    }
    
    // Estratégia 2: Procura por "." seguido de "no" e número
    pos = nomeNo.find_last_of('.');
    if (pos != std::string::npos && pos + 1 < nomeNo.length()) {
        std::string nomeModulo = nomeNo.substr(pos + 1);
        if (nomeModulo.substr(0, 2) == "no" && nomeModulo.length() > 2) {
            std::string numeroStr = nomeModulo.substr(2);
            return std::stoi(numeroStr);
        }
    }
    
    return -1;
}

void Roteador::initialize() {
    meuId = getId();
    WATCH(meuId);
    
    // Inicialização das métricas
    totalMensagensEnviadas = 0;
    totalMensagensRecebidas = 0;
    tempoInicial = simTime();
    convergiu = false;
    
    // Inicialização do relógio global
    relogioGlobal = 0;
    faseAtual = 0;
    aguardandoSincronizacao = false;
    
    // Obtém o nome do nó (no0, no1, no2, etc.)
    std::string nomeNo = getFullName();
    int numeroNo = extrairNumeroNo(nomeNo);
    
    // Verifica se a extração funcionou
    if (numeroNo == -1) {
        EV << "ERRO CRÍTICO: Não foi possível extrair número do nó!" << endl;
        return;
    }
    
    // Inicializa a tabela de roteamento com informação local
    tabelaRoteamento[numeroNo] = 0.0;
    proximosSaltos[numeroNo] = numeroNo;
    destinosConhecidos.push_back(numeroNo);
    
    // Descobre vizinhos diretos e seus custos
    for (int i = 0; i < gateSize("portas"); ++i) {
        cGate *gateSaida = gate("portas$o", i);
        if (gateSaida->getChannel() != nullptr) {
            cChannel *canal = gateSaida->getChannel();
            cModule *vizinho = gateSaida->getPathEndGate()->getOwnerModule();
            
            // Lê o custo do canal (delay) - USANDO LINKS COM DELAY
            double custo = canal->par("delay").doubleValue();
            
            // Obtém o nome do vizinho
            std::string nomeVizinho = vizinho->getFullName();
            int numeroVizinho = extrairNumeroNo(nomeVizinho);
            
            // Verifica se a extração funcionou para o vizinho
            if (numeroVizinho != -1) {
                // Adiciona informação do vizinho direto
                tabelaRoteamento[numeroVizinho] = custo;
                proximosSaltos[numeroVizinho] = numeroVizinho;
                custoVizinhos[numeroVizinho] = custo;
                destinosConhecidos.push_back(numeroVizinho);
            }
        }
    }
    
    imprimirTabelaRoteamento("INICIAL - PI");
    
    // Apenas o nó inicial inicia a propagação de informação
    if (par("isStarter").boolValue()) {
        EV << "Nó " << nomeNo << " iniciando propagação de informação (PI) com relógio global..." << endl;
        simtime_t delayInicial = uniform(0, 0.01);
        scheduleAt(simTime() + delayInicial, new cMessage("IniciarPI"));
    }
}

void Roteador::handleMessage(cMessage *msg) {
    // Verifica se é a mensagem para iniciar PI
    if (strcmp(msg->getName(), "IniciarPI") == 0) {
        iniciarPropagacaoInformacao();
        delete msg;
        return;
    }
    
    // Processa mensagens de propagação de informação
    Mensagem *msgRecebida = check_and_cast<Mensagem *>(msg);
    registrarMensagemRecebida();
    
    processarInformacaoRecebida(msgRecebida);
    delete msgRecebida;
}

void Roteador::iniciarPropagacaoInformacao() {
    EV << "Nó " << getFullName() << " iniciando propagação de informação para vizinhos" << endl;
    propagarInformacao();
}

void Roteador::propagarInformacao() {
    // Atualiza relógio global baseado no tempo de simulação
    relogioGlobal = simTime();
    faseAtual++;
    
    EV << "Nó " << getFullName() << " - Fase " << faseAtual << " - Relógio Global: " << relogioGlobal << endl;
    
    // Propaga a tabela de roteamento atual para todos os vizinhos
    for (int i = 0; i < gateSize("portas"); ++i) {
        Mensagem *msgPI = new Mensagem("PropagacaoInformacao");
        msgPI->setIdNoOrigem(extrairNumeroNo(getFullName()));
        
        // Prepara arrays com informações de roteamento
        msgPI->setDestinosArraySize(tabelaRoteamento.size());
        msgPI->setCustosArraySize(tabelaRoteamento.size());
        
        int j = 0;
        for (std::map<int, double>::const_iterator it = tabelaRoteamento.begin(); 
             it != tabelaRoteamento.end(); ++it) {
            msgPI->setDestinos(j, it->first);
            msgPI->setCustos(j, it->second);
            j++;
        }
        
        // Envia com delay do canal (LINKS COM DELAY)
        send(msgPI->dup(), "portas$o", i);
        registrarMensagemEnviada();
    }
    
    EV << "Nó " << getFullName() << " propagou informação de roteamento para " 
       << gateSize("portas") << " vizinhos na fase " << faseAtual << endl;
}

void Roteador::processarInformacaoRecebida(Mensagem *msg) {
    int numeroVizinho = msg->getIdNoOrigem();
    bool tabelaAtualizada = false;
    
    // Atualiza relógio global baseado no tempo de chegada da mensagem
    simtime_t tempoChegada = simTime();
    if (tempoChegada > relogioGlobal) {
        relogioGlobal = tempoChegada;
    }
    
    EV << "Nó " << getFullName() << " recebeu mensagem de no" << numeroVizinho 
       << " no tempo " << tempoChegada << " (Relógio Global: " << relogioGlobal << ")" << endl;
    
    // Reconstrói a tabela do vizinho
    std::map<int, double> tabelaVizinho;
    for (unsigned int i = 0; i < msg->getDestinosArraySize(); i++) {
        tabelaVizinho[msg->getDestinos(i)] = msg->getCustos(i);
    }
    
    double custoAteVizinho = custoVizinhos[numeroVizinho];
    
    // Processa informações recebidas usando conceito de PI
    for (std::map<int, double>::const_iterator it = tabelaVizinho.begin(); 
         it != tabelaVizinho.end(); ++it) {
        int destino = it->first;
        double custoDoVizinho = it->second;
        double novoCusto = custoAteVizinho + custoDoVizinho;
        
        // Atualiza se encontrou caminho melhor ou destino novo
        if (tabelaRoteamento.find(destino) == tabelaRoteamento.end() || 
            novoCusto < tabelaRoteamento[destino]) {
            
            EV << "Nó " << getFullName() << " atualizou rota para no" << destino 
               << " via no" << numeroVizinho << " (custo: " << novoCusto << ") na fase " << faseAtual << endl;
            
            tabelaRoteamento[destino] = novoCusto;
            proximosSaltos[destino] = numeroVizinho;
            tabelaAtualizada = true;
            
            // Adiciona destino à lista se for novo
            bool encontrado = false;
            for (size_t k = 0; k < destinosConhecidos.size(); k++) {
                if (destinosConhecidos[k] == destino) {
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                destinosConhecidos.push_back(destino);
            }
        }
    }
    
    // Se a tabela foi atualizada, propaga a nova informação
    if (tabelaAtualizada) {
        imprimirTabelaRoteamento("Após PI");
        propagarInformacao();
    }
    
    verificarConvergencia();
}

void Roteador::verificarConvergencia() {
    // Verifica se convergiu (todos os nós conhecem todos os destinos)
    int totalNos = 8; // Para todas as topologias implementadas
    
    if (tabelaRoteamento.size() >= totalNos && !convergiu) {
        convergiu = true;
        tempoConvergencia = simTime() - tempoInicial;
        EV << "Nó " << getFullName() << " CONVERGIU em " << tempoConvergencia << "s" << endl;
        
        verificarConsistenciaRoteamento();
    }
}

void Roteador::imprimirTabelaRoteamento(const char* motivo) {
    EV << "=== Tabela de Roteamento do Nó " << getFullName() << " (" << motivo << ") ===" << endl;
    for (std::map<int, double>::const_iterator it = tabelaRoteamento.begin(); 
         it != tabelaRoteamento.end(); ++it) {
        int destino = it->first;
        double custo = it->second;
        EV << "  Destino: no" << destino << " | Custo: " << custo
           << " | Próximo Salto: no" << proximosSaltos[destino] << endl;
    }
    EV << "==========================================" << endl;
}

void Roteador::registrarMensagemEnviada() {
    totalMensagensEnviadas++;
    EV << "Nó " << getFullName() << " enviou mensagem #" << totalMensagensEnviadas << endl;
}

void Roteador::registrarMensagemRecebida() {
    totalMensagensRecebidas++;
    EV << "Nó " << getFullName() << " recebeu mensagem #" << totalMensagensRecebidas << endl;
}

void Roteador::verificarConsistenciaRoteamento() {
    EV << "=== Verificação de Consistência - Nó " << getFullName() << " ===" << endl;
    
    // Verifica se todos os caminhos são consistentes
    for (std::map<int, double>::const_iterator it = tabelaRoteamento.begin(); 
         it != tabelaRoteamento.end(); ++it) {
        int destino = it->first;
        double custo = it->second;
        int numeroNo = extrairNumeroNo(getFullName());
        if (destino != numeroNo) {
            int proximoSalto = proximosSaltos[destino];
            double custoDireto = custoVizinhos[proximoSalto];
            
            if (custoDireto > 0) {
                EV << "  Destino no" << destino << ": caminho via no" << proximoSalto 
                   << " (custo: " << custo << ")" << endl;
            }
        }
    }
    EV << "==========================================" << endl;
}

void Roteador::finish() {
    // Coleta estatísticas finais
    EV << "=== ESTATÍSTICAS FINAIS - Nó " << getFullName() << " ===" << endl;
    EV << "Total de mensagens enviadas: " << totalMensagensEnviadas << endl;
    EV << "Total de mensagens recebidas: " << totalMensagensRecebidas << endl;
    EV << "Tempo de convergência: " << tempoConvergencia << "s" << endl;
    EV << "Convergiu: " << (convergiu ? "SIM" : "NÃO") << endl;
    EV << "Destinos conhecidos: " << destinosConhecidos.size() << endl;
    EV << "Fase final: " << faseAtual << endl;
    EV << "Relógio global final: " << relogioGlobal << "s" << endl;
    EV << "==========================================" << endl;
    
    // Registra escalares para análise
    recordScalar("mensagens_enviadas", totalMensagensEnviadas);
    recordScalar("mensagens_recebidas", totalMensagensRecebidas);
    recordScalar("tempo_convergencia", tempoConvergencia);
    recordScalar("convergiu", convergiu ? 1 : 0);
    recordScalar("destinos_conhecidos", destinosConhecidos.size());
    recordScalar("fase_final", faseAtual);
    recordScalar("relogio_global_final", relogioGlobal);
}
