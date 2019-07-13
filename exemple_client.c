
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;


#include <stdio.h>
#include <stdlib.h>
#define PORT 23



int main(void)
{
        FILE* fichier = NULL;
        int erreur = 0;


    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[32] = "";
    char filePath = "";


        /* Création de la socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);

        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr("192.168.43.46");
        //sin.sin_addr.s_addr = inet_addr("172.0.0.1");
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);

        /* Si l'on a réussi à se connecter */
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        {
            printf("Connection à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
            printf("Entrer le chemin du fichier");
            scanf("%s",&filePath);
            send(sock, filePath, 32, 0);
            if(recv(sock, buffer, 32, 0) != SOCKET_ERROR)
            {
              printf("%s", buffer);
            }
        }
        /* sinon, on affiche "Impossible de se connecter" */
        else
        {
            printf("Impossible de se connecter\n");
        }

        /* On ferme la socket */
        close(sock);

    /* On attend que l'utilisateur tape sur une touche, puis on ferme */
    getchar();

    return EXIT_SUCCESS;
}
