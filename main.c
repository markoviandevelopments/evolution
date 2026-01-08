#include <stdio.h>
#include <stdlib.h>

struct Agent {
    int id;
    float nodes[4];
    float weights[56];
};

void run(struct Agent* agent) {
    float nodes[4];
    for (int i=0;i<4;i++) {
        nodes[i] = 0.0f;
    }

    int w_idx=0;
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++){
            if (i == j) {
                continue;
            }
            nodes[i] += agent->nodes[j] * agent->weights[w_idx] / 4;
            w_idx++;
        }
        nodes[i] += agent->weights[w_idx];
        w_idx++;
        if (nodes[i] < 0.0f) {
            nodes[i] = 0.0f;
        }
    }

    for (int i=0;i<4;i++) {
        agent->nodes[i] = nodes[i];
    }

    return;
}

int main() {
    srand(42);
    struct Agent agents[50];
    for (int i=0;i<4;i++) {
        agents[0].nodes[i] = (rand() % 100) / 100.0f;
        printf("Initial Node %d value is %f\n",i,agents[0].nodes[i]);
    }
    for (int i=0;i<56;i++) {
        agents[0].weights[i] = ((rand() % 1000) / 1000.0f - 0.5f) * 4.0f;
    }

    for (int j=0;j<10;j++) {
        agents[0].nodes[0] = (j % 2) * 1.0f;
        run(&agents[0]);
        for (int i=0;i<4;i++) {
            printf("Node %d value is %f\n",i,agents[0].nodes[i]);
        }
        printf("~~~~~~~~~~~~~~\n");
    }
    return 1;
}
