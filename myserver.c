
#define PORT 8080
#define PI 3.14159265358979323846
#define _POSIX_C_SOURCE 200809L
#define CHALLENGES 12
#define ANSWER_SIZE 50
#define BUFFER_SIZE 1024
#define LOWER 70
#define UPPER 100
#define MIN_CHAR 33
#define MAX_CHAR 126
#define ERROR_CHECK(x, msg)                                                                              \
    do {                                                                                                 \
        int retval = (x);                                                                                \
        if (retval == -1) {                                                                              \
            fprintf(stderr, "Runtime error: %s returned %d at %s:%d\n", #x, retval, __FILE__, __LINE__); \
            perror(msg);                                                                                 \
            exit(-1);                                                                                    \
        }                                                                                                \
    } while (0)

#include <math.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

static void challenge0(int index);
static void challenge1(int index);
static void challenge2(int index);
static void challenge3(int index);
static void challenge4(int index);
static void challenge5(int index);
static void challenge6(int index);
static void challenge7(int index);
static void challenge8(int index);
static void challenge9(int index);
static void challenge10(int index);
static void challenge11(int index);
static void clearScreen();
static void challengeMessage();
static void researchMessage();
static int processAnswer(char *answer, char *received);

typedef struct {
    void (*level)(int index);
    char answer[ANSWER_SIZE];
} challenge_t;

static challenge_t challenges[CHALLENGES] = {{&challenge0, "entendido\n"}, {&challenge1, "itba\n"}, {&challenge2, "M4GFKZ289aku\n"}, {&challenge3, "fk3wfLCm3QvS\n"}, {&challenge4, "too_easy\n"}, {&challenge5, ".RUN_ME\n"}, {&challenge6, "K5n2UFfpFMUN\n"}, {&challenge7, "BUmyYq5XxXGt\n"}, {&challenge8, "u^v\n"}, {&challenge9, "chin_chu_lan_cha\n"}, {&challenge10, "gdb_rules\n"}, {&challenge11, "normal\n"}};

int main(int argc, char const *argv[]) {
    int serverFd, socketFd, opt = 1, current = 0;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char *buffer = NULL;
    ssize_t read;
    size_t bufferSize = 0;
    FILE *socketFile;

    // Creating socket file descriptor
    ERROR_CHECK((serverFd = socket(AF_INET, SOCK_STREAM, 0)), "Socket Failed");

    // Forcefully attaching socket to the port 8080
    ERROR_CHECK(setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)), "Setting socket options failed");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    ERROR_CHECK(bind(serverFd, (struct sockaddr *)&address, sizeof(address)), "Bind failed");
    ERROR_CHECK(listen(serverFd, 1), "Listen failed");
    ERROR_CHECK((socketFd = accept(serverFd, (struct sockaddr *)&address, (socklen_t *)&addrlen)), "Accept failed");

    if ((socketFile = fdopen(socketFd, "r")) == NULL)
        ERROR_CHECK(-1, "Error opening file");

    int reading = 1;
    srand(time(0));

    while (current < CHALLENGES && reading) {
        challenge_t challenge = challenges[current];
        (challenge.level)(current);
        if ((read = getline(&buffer, &bufferSize, socketFile)) > 0)
            current += processAnswer(challenge.answer, buffer);
        else
            reading = 0;
    }

    if (current >= CHALLENGES)
        printf("Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto\n");

    ERROR_CHECK(close(serverFd), "Error closing file descriptor");
    return 0;
}

static void challenge0(int index) {
    challengeMessage();
    printf("%s\n\n", "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos.\nNo basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\nDeberán estar atentos a los easter eggs\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'\n");
    researchMessage();
    printf("¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?\n");
}

static void challenge1(int index) {
    challengeMessage();
    printf("The Wire S1E5\n");
    printf("5295 888 6288\n\n");
    researchMessage();
    printf("¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?\n");
}

static void challenge2(int index) {
    challengeMessage();
    printf("https://ibb.co/tc0Hb6w\n");
    researchMessage();
    printf("¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?\n");
}

static void challenge3(int index) {
    challengeMessage();
    char *aux = "La respuesta es fk3wfLCm3QvS\n";
    printf("%s\n\n", "EBADF...");

    if (write(13, aux, strlen(aux)) == -1)
        perror("write");

    researchMessage();
    printf("¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?\n");
}

static void challenge4(int index) {
    challengeMessage();
    printf("respuesta = strings: 129\n\n");
    researchMessage();
    printf("¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?\n");
}

__attribute__((section(".RUN_ME"))) static void challenge5(int index) {
    challengeMessage();
    printf(".plt .text ? .fini .rodata .eh_frame_hdr .eh_frame\n\n");
    researchMessage();
    printf("Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?\n");
}

static void challenge6(int index) {
    challengeMessage();
    printf("Filter error\n\n");
    char *answer = challenges[index].answer;
    int answerLen = strlen(answer);
    char aux[2];
    aux[1] = 0;

    int num = (rand() % (UPPER - LOWER + 1)) + LOWER;
    int i,j;
    for ( i = 0, j = 0; i < num || j < answerLen;) {
        if ((rand() % 2) && j < answerLen) {
            aux[0] = answer[j++];
            write(STDOUT_FILENO, aux, 1);
        } else {
            aux[0] = (rand() % (MAX_CHAR - MIN_CHAR + 1)) + MIN_CHAR;
            write(STDERR_FILENO, aux, 1);
            i++;
        }
    }

    researchMessage();
    printf("¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?\n");
}

static void challenge7(int index) {
    challengeMessage();
    printf("¿?\n\n");
    printf("\033[30;40m");

    printf("La respuesta es BUmyYq5XxXGt\033[0m\n");

    researchMessage();
    printf("¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?\n");
}

static void challenge8(int index) {
    challengeMessage();
    printf("Latexme\n\n");
    printf("Si\n \\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u}) entonces\ny =");
    researchMessage();
    printf("sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?\n");
}

static void challenge9(int index) {
    challengeMessage();
    printf("quine\n\n");

    if (system("gcc quine.c -o quine") != 0)
        puts("\n\nENTER para reintentar.\n");

    puts("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.");

    if (system("./quine | diff - quine.c") != 0) {
        printf("\n%s\n", "diff encontró diferencias.");
        puts("\n\nENTER para reintentar.\n");
    } else
        printf("La respuesta es chin_chu_lan_cha");

    researchMessage();
    printf("¿Cuáles son las características del protocolo SCTP?\n");
}

static void gdbme() {
    long long pid = getpid();
    if (pid == 0x123456789)
        printf("la respuesta es gdb_rules");
}

static void challenge10(int index) {
    challengeMessage();
    printf("b gdbme y encontrá el valor magico\n");

    researchMessage();
    printf("¿Qué es un RFC?");

    gdbme();
}

static void challenge11(int index) {
    challengeMessage();
    printf("Me conoces\n\n");

    double x, y, aux;
    int i;
    for ( i = 0; i < 1000; i++) {
        x = rand() / ((double)RAND_MAX + 1);
        y = rand() / ((double)RAND_MAX + 1);
        aux = sqrt(-2 * log(x)) * cos(2 * PI * y);
        printf("%.6f ", aux);
    }
    putchar('\n');

    researchMessage();
    printf("¿Fue divertido?\n");
}
static void challengeMessage() {
    puts("\n------------- DESAFIO -------------\n");
}

static void researchMessage() {
    puts("\n----- PREGUNTA PARA INVESTIGAR -----\n");
}

static int processAnswer(char *answer, char *received) {
    int ans = 1;
    if (strcmp(answer, received) != 0) {
        printf("\nWrong answer: %s\n", received);
        sleep(2);
        ans = 0;
    }
    clearScreen();
    return ans;
}

static void clearScreen() {
    printf("\033[1;1H\033[2J");
}