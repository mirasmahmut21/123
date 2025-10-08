#include <fcntl.h>    // open() үшін
#include <unistd.h>   // write(), read(), close() үшін
#include <stdio.h>    // printf(), perror() үшін
#include <string.h>   // strlen() үшін

int main() {
    int fd;                   // файл дескрипторы
    char text[] = "Сәлем, әлем!\n";
    char buffer[1024];        // оқу буфері
    ssize_t bytes;            // оқылған байттар саны

    // 1️⃣ Файлға жазу
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Файлды ашу қатесі");
        return 1;
    }

    if (write(fd, text, strlen(text)) != strlen(text)) {
        perror("Жазу қатесі");
        close(fd);
        return 1;
    }

    close(fd); // Файлды жабу

    // 2️⃣ Файлдан оқу
    fd = open("output.txt", O_RDONLY);
    if (fd < 0) {
        perror("Файлды оқу үшін ашу қатесі");
        return 1;
    }

    bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes < 0) {
        perror("Оқу қатесі");
        close(fd);
        return 1;
    }

    buffer[bytes] = '\0'; // мәтінді соңына '\0' қою керек (жолдың соңы)
    close(fd);

    // 3️⃣ Экранға шығару
    printf("Файлдан оқылған: %s", buffer);

    return 0;
}
