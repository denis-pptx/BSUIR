#include <sys/wait.h>

#include <unistd.h> // для pipe, fork, write, close, getpid
#include <stdio.h>  // для printf
#include <stdlib.h> // для exit

#include "integral.h"

#define NUM_AGENTS 5

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <start> <end>\n", argv[0]);
        exit(1);
    }

    double total_result = 0.0;
    double start = atof(argv[1]); 
    double end = atof(argv[2]);   

    // Массив для хранения файловых дескрипторов каналов
    int pipefd[NUM_AGENTS][2]; 

    // Создание каналов для каждого агента
    for (int i = 0; i < NUM_AGENTS; i++) {
        if (pipe(pipefd[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    double step = (end - start) / NUM_AGENTS;

    for (int i = 0; i < NUM_AGENTS; i++) {
        pid_t pid = fork();

        if (pid == 0) { 
            // Дочерний процесс (агент)

            double agent_start = start + i * step;
            double agent_end = start + (i + 1) * step;

            double result = compute_integral(agent_start, agent_end);

            // Записываем результат вычислений в канал
            if (write(pipefd[i][1], &result, sizeof(result)) == -1) {
                perror("write");
                exit(1);
            }

            // Закрываем записывающий конец канала
            close(pipefd[i][1]); 

            printf("Result of agent %d: %f\n", getpid(), result);

            exit(0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }

    // Ожидание завершения всех агентов
    for (int i = 0; i < NUM_AGENTS; i++) {
        int status;
        pid_t pid = waitpid(-1, &status, 0);
        if (pid == -1) {
            perror("waitpid");
            exit(1);
        } else {
            if (WIFEXITED(status)) {
                printf("Agent %d terminated successfully.\n", pid);
            } else {
                printf("Agent %d terminated abnormally.\n", pid);
                exit(1);
            }
        }
    }

    // Родительский процесс (менеджер)
    for (int i = 0; i < NUM_AGENTS; i++) {

        double agent_result;

        // Читаем результат вычислений из канала
        if (read(pipefd[i][0], &agent_result, sizeof(agent_result)) == -1) {
            perror("read");
            exit(1);
        }

        total_result += agent_result;

        close(pipefd[i][0]); // Закрываем читающий конец канала
    }

    printf("Total integral of sin(x) from %f to %f: %f\n", start, end, total_result);

    return 0;
}
