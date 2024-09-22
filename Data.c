#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define CONTENT_LENGTH 100

// Seviye verisini dosyadan çeken fonksiyon
void getLevelData(int level) {
    FILE *file = fopen("EXPdat.txt", "r");
    if (file == NULL) {
        printf("Content-type: text/html\n\n");
        printf("<p>Dosya açýlamadý!</p>\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int levelData[3];

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d %d %d", &levelData[0], &levelData[1], &levelData[2]);

        if (levelData[0] == level) {
            printf("Content-type: text/html\n\n");
            printf("<p>Seviye: %d</p>\n", levelData[0]);
            printf("<p>XP: %d</p>\n", levelData[1]);
            printf("<p>Toplam XP: %d</p>\n", levelData[2]);
            fclose(file);
            return;
        }
    }

    printf("Content-type: text/html\n\n");
    printf("<p>Veri bulunamadý.</p>\n");
    fclose(file);
}

int main() {
    char *data;
    char *contentLength = getenv("CONTENT_LENGTH");
    int length = 0;

    if (contentLength != NULL) {
        length = atoi(contentLength);
    }

    if (length > 0) {
        data = (char *)malloc(length + 1);
        fread(data, 1, length, stdin);
        data[length] = '\0';

        // "level=" kýsmýndan sonra gelen sayýyý çekiyoruz
        int level = atoi(data + strlen("level="));

        // Seviye verisini bulma
        getLevelData(level);

        free(data);
    } else {
        printf("Content-type: text/html\n\n");
        printf("<p>Seviye verisi alýnamadý.</p>\n");
    }

    return 0;
}
