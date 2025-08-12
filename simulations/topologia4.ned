// Topologia 4: Anel - 8 nós em formato circular
package prova.simulations;

import prova.src.Roteador;



network RedeTopologia4
{
    submodules:
        no0: Roteador {
            @display("p=300,100");
        }
        no1: Roteador {
            @display("p=450,150");
        }
        no2: Roteador {
            @display("p=500,300");
        }
        no3: Roteador {
            @display("p=450,450");
        }
        no4: Roteador {
            @display("p=300,500");
        }
        no5: Roteador {
            @display("p=150,450");
        }
        no6: Roteador {
            @display("p=100,300");
        }
        no7: Roteador {
            @display("p=150,150");
        }

    connections:
        // Conexões em anel
        no0.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no1.portas++;
        no1.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no2.portas++;
        no2.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no3.portas++;
        no3.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no4.portas++;
        no4.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no5.portas++;
        no5.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no6.portas++;
        no6.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no7.portas++;
        no7.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no0.portas++;
        
        // Conexões cruzadas para adicionar complexidade
        no0.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no4.portas++;
        no1.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no5.portas++;
        no2.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no6.portas++;
        no3.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 6ms); } <--> no7.portas++;
}
