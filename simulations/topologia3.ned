// Topologia 3: Estrela - 8 nós com nó central
package prova.simulations;

import prova.src.Roteador;



network RedeTopologia3
{
    submodules:
        no0: Roteador {
            @display("p=250,250");
        }
        no1: Roteador {
            @display("p=100,100");
        }
        no2: Roteador {
            @display("p=400,100");
        }
        no3: Roteador {
            @display("p=100,400");
        }
        no4: Roteador {
            @display("p=400,400");
        }
        no5: Roteador {
            @display("p=150,200");
        }
        no6: Roteador {
            @display("p=350,200");
        }
        no7: Roteador {
            @display("p=250,350");
        }

    connections:
        // Nó central (no0) conectado a todos os outros
        no0.portas++ <--> ned.DelayChannel { delay = uniform(2ms, 8ms); } <--> no1.portas++;
        no0.portas++ <--> ned.DelayChannel { delay = uniform(2ms, 8ms); } <--> no2.portas++;
        no0.portas++ <--> ned.DelayChannel { delay = uniform(2ms, 8ms); } <--> no3.portas++;
        no0.portas++ <--> ned.DelayChannel { delay = uniform(2ms, 8ms); } <--> no4.portas++;
        no0.portas++ <--> ned.DelayChannel { delay = uniform(2ms, 8ms); } <--> no5.portas++;
        no0.portas++ <--> ned.DelayChannel { delay = uniform(2ms, 8ms); } <--> no6.portas++;
        no0.portas++ <--> ned.DelayChannel { delay = uniform(2ms, 8ms); } <--> no7.portas++;
}
