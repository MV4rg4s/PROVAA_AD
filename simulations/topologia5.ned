// Topologia 5: Hierárquica - 8 nós em estrutura de árvore
package prova.simulations;

import prova.src.Roteador;



network RedeTopologia5
{
    submodules:
        no0: Roteador {
            @display("p=300,100");
        }
        no1: Roteador {
            @display("p=200,200");
        }
        no2: Roteador {
            @display("p=400,200");
        }
        no3: Roteador {
            @display("p=150,300");
        }
        no4: Roteador {
            @display("p=250,300");
        }
        no5: Roteador {
            @display("p=350,300");
        }
        no6: Roteador {
            @display("p=450,300");
        }
        no7: Roteador {
            @display("p=300,400");
        }

    connections:
        // Nível 1: Raiz
        no0.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no1.portas++;
        no0.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no2.portas++;
        
        // Nível 2: Filhos do primeiro nível
        no1.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no3.portas++;
        no1.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no4.portas++;
        no2.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no5.portas++;
        no2.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no6.portas++;
        
        // Nível 3: Folhas
        no3.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no7.portas++;
        no4.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no7.portas++;
        no5.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no7.portas++;
        no6.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no7.portas++;
        
        // Conexões adicionais para redundância
        no0.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no7.portas++;
        no1.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 10ms); } <--> no2.portas++;
}
