#ifndef __PROVA_ROTEADOR_H_
#define __PROVA_ROTEADOR_H_

#include <omnetpp.h>
#include <map>
#include <vector>
#include "Mensagem_m.h"

using namespace omnetpp;

class Roteador : public cSimpleModule {
  private:
    int meuId;
    std::map<int, double> tabelaRoteamento;  // Tabela de custos para cada destino
    std::map<int, int> proximosSaltos;       // Próximo salto para cada destino
    std::map<int, double> custoVizinhos;     // Custo direto para cada vizinho
    
    // Métricas para coleta de dados
    int totalMensagensEnviadas;
    int totalMensagensRecebidas;
    simtime_t tempoInicial;
    simtime_t tempoConvergencia;
    bool convergiu;
    
    // Para verificação de consistência
    std::vector<int> destinosConhecidos;

    // Relógio global
    simtime_t relogioGlobal;
    int faseAtual;
    bool aguardandoSincronizacao;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    
    // Função para extrair número do nó do nome (ex: "no0" -> 0)
    int extrairNumeroNo(const std::string& nomeNo);
    
    // Métodos baseados em PI (Propagação de Informação)
    void iniciarPropagacaoInformacao();
    void propagarInformacao();
    void processarInformacaoRecebida(Mensagem *msg);
    void verificarConvergencia();
    void imprimirTabelaRoteamento(const char* motivo);
    
    // Métricas e análise
    void registrarMensagemEnviada();
    void registrarMensagemRecebida();
    void verificarConsistenciaRoteamento();
};

#endif
