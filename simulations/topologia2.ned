// Topologia 2: Malha (Mesh) - 8 nós com conexões em malha
package prova.simulations;

import prova.src.Roteador;



network RedeTopologia2
{
    submodules:
        no0: Roteador {
            @display("p=100,100");
        }
        no1: Roteador {
            @display("p=200,100");
        }
        no2: Roteador {
            @display("p=300,100");
        }
        no3: Roteador {
            @display("p=400,100");
        }
        no4: Roteador {
            @display("p=100,200");
        }
        no5: Roteador {
            @display("p=200,200");
        }
        no6: Roteador {
            @display("p=300,200");
        }
        no7: Roteador {
            @display("p=400,200");
        }

    connections:
        // Primeira linha horizontal
        no0.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no1.portas++;
        no1.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no2.portas++;
        no2.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no3.portas++;
        
        // Segunda linha horizontal
        no4.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no5.portas++;
        no5.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no6.portas++;
        no6.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no7.portas++;
        
        // Conexões verticais
        no0.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no4.portas++;
        no1.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no5.portas++;
        no2.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no6.portas++;
        no3.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no7.portas++;
        
        // Conexões diagonais para formar malha
        no0.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no5.portas++;
        no1.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no6.portas++;
        no2.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no7.portas++;
        no4.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no1.portas++;
        no5.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no2.portas++;
        no6.portas++ <--> ned.DelayChannel { delay = uniform(1ms, 5ms); } <--> no3.portas++;
}
