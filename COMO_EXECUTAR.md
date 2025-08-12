# Como Executar o Projeto

## No OMNeT++ IDE:

1. **Abrir o projeto** no OMNeT++ IDE
2. **Compilar** o projeto (Project → Build Project)
3. **Abrir** o arquivo `simulations/omnetpp.ini`
4. **Selecionar** a configuração desejada no menu "Run Configuration":
   - `topologia1` - Topologia Linear
   - `topologia2` - Topologia Malha  
   - `topologia3` - Topologia Estrela
   - `topologia4` - Topologia Anel
   - `topologia5` - Topologia Hierárquica
5. **Clicar** em "Run" para executar

## Via Linha de Comando:

```bash
# Topologia 1 (Linear)
PROVA.exe -u Cmdenv -c topologia1 simulations/omnetpp.ini

# Topologia 2 (Malha)
PROVA.exe -u Cmdenv -c topologia2 simulations/omnetpp.ini

# Topologia 3 (Estrela)
PROVA.exe -u Cmdenv -c topologia3 simulations/omnetpp.ini

# Topologia 4 (Anel)
PROVA.exe -u Cmdenv -c topologia4 simulations/omnetpp.ini

# Topologia 5 (Hierárquica)
PROVA.exe -u Cmdenv -c topologia5 simulations/omnetpp.ini
```

## Resultados:

Os resultados serão salvos em `simulations/results/` e incluem:
- **Scalar files**: Estatísticas finais
- **Vector files**: Evolução temporal
- **Event log**: Log detalhado
