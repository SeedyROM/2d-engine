//
// Created by rombus on 8/15/21.
//

#include "Scripting.h"

#include <stdlib.h>
#include <stdio.h>
#include <lauxlib.h>
#include <lualib.h>

#include "Error.h"

ScriptingContext *ScriptingContext_Create() {
    ScriptingContext *scriptingContext = malloc(sizeof(ScriptingContext));
    if (scriptingContext == NULL) {
        fprintf(stderr, "Failed to allocate ScriptingEngine");
        return NULL;
    }

    scriptingContext->L =  NULL;
    scriptingContext->result = SCRIPT_NO_ERROR;
    scriptingContext->errorMessage = NULL;

    scriptingContext->L = luaL_newstate();
    if(scriptingContext->L == NULL) {
        scriptingContext->errorMessage = Error_BuildMessageF("Failed to create a lua_State for the ScriptingContext");
        return scriptingContext;
    }
    luaL_openlibs(scriptingContext->L);

    return scriptingContext;
}

void ScriptingContext_Destroy(ScriptingContext *scriptingContext) {
    lua_close(scriptingContext->L);
    free(scriptingContext);
}

const char *ScriptingContext_GetError(ScriptingContext *scriptingContext) {
    return scriptingContext->errorMessage;
}
