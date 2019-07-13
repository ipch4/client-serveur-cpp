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
#include <string.h>
#define PORT 23



int main(void)
{
    FILE* fichier = NULL;
    int erreur = 0;

    SOCKET sock;
    SOCKADDR_IN sin;
    SOCKET csock;
    SOCKADDR_IN csin;
    char chaine[32] = "";
    socklen_t recsize = sizeof(csin);
    int sock_err;


        sock = socket(AF_INET, SOCK_STREAM, 0);

        /* Si la socket est valide */
        if(sock != INVALID_SOCKET)
        {
            printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

            /* Configuration */
            sin.sin_addr.s_addr    = htonl(INADDR_ANY);   /* Adresse IP automatique */
            sin.sin_family         = AF_INET;             /* Protocole familial (IP) */
            sin.sin_port           = htons(PORT);         /* Listage du port */
            sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));

            /* Si la socket fonctionne */
            if(sock_err != SOCKET_ERROR)
            {
                /* Démarrage du listage (mode server) */
                sock_err = listen(sock, 5);
                printf("Listage du port %d...\n", PORT);

                if(sock_err != SOCKET_ERROR)
                    {
                        fichier = fopen("file.txt", "r");
                        if (fichier != NULL)
                        {
                            sock_err = send(csock, "START\n", 32, 0);
                            printf("\nSTART\n");
                            while (fgets(chaine, 32, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
                            {
                                printf("%s", chaine);
                                sock_err = send(csock, chaine, 32, 0);
                            }
                            printf("STOP\n\n");
                            sock_err = send(csock, "STOP", 32, 0);

                            fclose(fichier);
                        }
                        else
                        {
                            // On affiche un message d'erreur si on veut
                            printf("Impossible d'ouvrir le fichier test.txt\n");
                        }
                    }else
                        printf("Erreur de transmission\n");

                    /* Il ne faut pas oublier de fermer la connexion (fermée dans les deux sens) */
                    shutdown(csock, 2);
                }
            }

            /* Fermeture de la socket */
            printf("Fermeture de la socket...\n");
            close(sock);
            printf("Fermeture du serveur terminee\n");

    /* On attend que l'utilisateur tape sur une touche, puis on ferme */
    getchar();

    return EXIT_SUCCESS;
}
