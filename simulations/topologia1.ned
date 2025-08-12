// Topologia 1: Linear - 8 nós em sequência
package prova.simulations;

import prova.src.Roteador;

channel CanalComCusto extends ned.DelayChannel
{
    delay = uniform(1ms, 4ms);
}

network RedeTopologia1
{
    submodules:
        no0: Roteador {
            @display("p=100,100");
        }
        no1: Roteador {
            @display("p=200,200");
        }
        no2: Roteador {
            @display("p=100,300");
        }
        no3: Roteador {
            @display("p=300,300");
        }
        no4: Roteador {
            @display("p=300,100");
        }
        no5: Roteador {
            @display("p=450,180");
        }
        no6: Roteador {
            @display("p=500,300");
        }
        no7: Roteador {
            @display("p=550,100");
        }

    connections:

        no0.portas++ <--> CanalComCusto <--> no2.portas++;
        no2.portas++ <--> CanalComCusto <--> no1.portas++;
        no1.portas++ <--> CanalComCusto <--> no3.portas++;
        no0.portas++ <--> CanalComCusto <--> no4.portas++;
        no4.portas++ <--> CanalComCusto <--> no7.portas++;
        no3.portas++ <--> CanalComCusto <--> no5.portas++;
        no5.portas++ <--> CanalComCusto <--> no6.portas++;
        no6.portas++ <--> CanalComCusto <--> no7.portas++;
}
