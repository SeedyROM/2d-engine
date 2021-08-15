//
// Created by rombus on 8/15/21.
//

#pragma once

#include <lua.h>

typedef struct ScriptingContext {
    lua_State *L;
    const char *status;
    const char *error;
} ScriptingContext;

ScriptingContext *
ScriptingContext_Create();

void
ScriptingContext_Destroy(ScriptingContext *);

const char*
ScriptingContext_GetError(ScriptingContext *);
