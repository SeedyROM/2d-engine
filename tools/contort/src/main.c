#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

#include "Tokenizer.h"

static char *
readFile(const char *filePath) {
    // Allocate some space
    char *buffer = NULL;

    // Try and open the file
    FILE *file = fopen(filePath, "r");
    if(!file) {
        fprintf(stderr, "Failed to open %s: %s\n", filePath, strerror(errno));
        return NULL;
    }

    // Check the file type
    struct stat fileInfo;
    int fileType = stat(filePath, &fileInfo);
    if (fileType != 0 || !S_ISREG(fileInfo.st_mode)) {
        fprintf(stderr, "Cannot open directory %s\n", filePath);
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    off_t fileSize = ftello(file);
    fseek(file, 0, SEEK_SET);

    // Allocate the space
    buffer = malloc(fileSize + 1);
    fread(buffer, fileSize, 1, file);
    // 0 Terminate the buffer
    buffer[fileSize] = '\0';
    // Close the file
    fclose(file);

    return buffer;
}

static const char* DEFER_KEYWORD = "defer";

int
main() {
    char *sourceFile = readFile("../../../tools/contort/tests/data/example.c");
    if(sourceFile == NULL) return 1;

    Tokenizer tokenizer = {
        .position = sourceFile,
    };

    bool parsing = true;
    while(parsing) {
        Token token = Tokenizer_GetToken(&tokenizer);

        switch(token.type) {
            case TOKEN_IDENTIFIER:
                if (strncmp(token.text, DEFER_KEYWORD, strlen(DEFER_KEYWORD)) == 0) {
                    printf("Found the defer keyword!");
                }
                break;
            case TOKEN_UNKNOWN:
                break;
            case TOKEN_EOF:
                parsing = false;
                break;
            default:
//                printf("%d: %.*s\n", token.type, token.length, token.text);
                break;
        }
    }

    return 0;
}