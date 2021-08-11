//
// Created by rombus on 8/10/21.
//
// ==========================================================
// Original idea (no format BS, keep around for later):
// char *reason = "Failed to allocate new resource ";
// size_t errorLength = strlen(reason) + strlen(name);
// char *error = calloc(errorLength, sizeof(char));
// resourceManager->error = strncat(reason, error, errorLength);
// ==========================================================
//

#pragma once

#define ERROR_MESSAGE_LENGTH 256

const char *Error_BuildMessageF(const char *, ...);
