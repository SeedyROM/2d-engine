//
// Created by rombus on 8/10/21.
//

#include "Error.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *
Error_BuildMessageF(const char *format, ...) {
    char *errorMessage = calloc(ERROR_MESSAGE_LENGTH, sizeof(char));

    va_list arguments;
    va_start(arguments, format);

    int messageError = vsnprintf(errorMessage, ERROR_MESSAGE_LENGTH, format, arguments);
    if (messageError < 0) {
        fprintf(stderr, "Failed to build error message: %s\n", strerror(messageError));
        return NULL;
    }

    va_end(arguments);

    return errorMessage;
}
