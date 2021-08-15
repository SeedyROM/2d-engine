//
// Created by rombus on 8/15/21.
//

#pragma once

#include <lua.h>

typedef enum {
        SCRIPT_NO_ERROR      = 0,
        SCRIPT_SYNTAX_ERROR  = LUA_ERRSYNTAX,
        SCRIPT_MEMORY_ERROR  = LUA_ERRMEM,
        SCRIPT_RUNTIME_ERROR = LUA_ERRRUN,
        SCRIPT_MESSAGE_ERROR = LUA_ERRERR,
} ScriptResult;

typedef struct ScriptingContext {
    lua_State *L;
    ScriptResult result;
    const char *errorMessage;
} ScriptingContext;

ScriptingContext *
ScriptingContext_Create();

void
ScriptingContext_Destroy(ScriptingContext *);

const char*
ScriptingContext_GetError(ScriptingContext *);
