//
// Created by rombus on 8/14/21.
//

#include "Configuration.h"

#include <stdio.h>

JSON_Object *ConfigurationJSON_FromFile(const char *filePath) {
    JSON_Value *configData = json_parse_file_with_comments(filePath);
    if (json_value_get_type(configData) != JSONObject) {
        fprintf(stderr, "Failed to load RenderContext_Settings from %s: Unable to parse config\n", filePath);
        return NULL;
    }
    return json_value_get_object(configData);
}
