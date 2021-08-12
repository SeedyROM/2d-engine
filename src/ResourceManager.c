//
// Created by rombus on 8/10/21.
//

#include <string.h>
#include <assert.h>

#include "ResourceManager.h"

#include "Error.h"

ResourceManager *
ResourceManager_Create() {
    ResourceManager *resourceManager = malloc(sizeof(ResourceManager));
    Resource *root = malloc(sizeof(Resource));

    if (resourceManager == NULL || root == NULL) {
        fprintf(stderr, "Failed to allocate ResourceManager");
        return NULL;
    }

    resourceManager->error = NULL;
    resourceManager->root = NULL;

    return resourceManager;
}

inline
const char *
ResourceManager_GetError(ResourceManager *resourceManager) {
    return resourceManager->error;
}

bool
ResourceManager_Add(ResourceManager *resourceManager, const char *name, uintptr_t data) {
    Resource *newResource = malloc(sizeof(Resource));

    if (newResource == NULL) {
        resourceManager->error = Error_BuildMessageF("Failed to allocate new resource: %s", name);
        return false;
    }

    newResource->name = name;
    newResource->data = data;
    newResource->next = NULL;

    assert(newResource->data != 0);

    Resource *resource = resourceManager->root;

    if (resource == NULL) {
        resourceManager->root = newResource;
    } else {
        while (resource->next != NULL) resource = resource->next;
        resource->next = newResource;
    }

    return true;
}

uintptr_t
ResourceManager_Get(ResourceManager *resourceManager, const char *name) {
    if (resourceManager->root == NULL) return 0;

    Resource *resource = resourceManager->root;

    while (resource != NULL) {
        if (strncmp(resource->name, name, strlen(name)) == 0) {
            return resource->data;
        }

        resource = resource->next;
    }

    return 0;
}

void ResourceManager_Destroy(ResourceManager *resourceManager) {
    if (resourceManager->root == NULL) {
        free(resourceManager);
        resourceManager = NULL;
        return;
    }

    Resource *resource = resourceManager->root;
    while (resource != NULL) {
        free((void *) resource->data);
        resource->data = 0;

        Resource *next = resource->next;
        if(next != NULL) {
            free(resource);
            resource = next->next;
        } else {
            free(resource);
            resource = NULL;
        }
    }

    free(resourceManager);
}

