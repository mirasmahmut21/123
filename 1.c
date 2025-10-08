#include <fcntl.h>    
#include <unistd.h>   
#include <stdio.h>    
#include <string.h>   

int main() {
    int fd;                   
    char text[] = "Сәлем, әлем!\n";
    char buffer[1024];       
    ssize_t bytes;            

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

    close(fd); 
    
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

    buffer[bytes] = '\0';
    close(fd);

    // 3️⃣ Экранға шығару
    printf("Файлдан оқылған: %s", buffer);

    return 0;
}
