# Mise en place du container coté serveur:

> docker pull debian:latest
>
>docker run -d --name ftp_compose_server -p 8080:8080 debian:latest tail -f /dev/null
>
>docker cp ftp-compose/. ftp_compose_server:/lftp_serv
>
>docker exec -it ftp_compose_server bash
>
>apt update && apt upgrade -y
>
>apt install -y build-essential gdb cmake

Se rendre dans le dossier du code et lancer la compilation

Lancer le programme sur le port 8080

# Mise en place du conatiner coté client

>docker run -d --name ftp_compose_client debian:latest tail -f /dev/null
>
>docker cp ftp-compose/. ftp_compose_client:/lftp_clt
>
>docker exec -it ftp_compose_client bash
>
>apt update && apt upgrade -y
>
>apt install -y build-essential gdb cmake

Se rendre dans le dossier du code et lancer la compilation

Lancer le programme sur le port 8080
