//
// Created by rombus on 8/14/21.
//

#pragma once

#include <parson/parson.h>

typedef JSON_Object ConfigurationJSON;

ConfigurationJSON *
ConfigurationJSON_FromFile(const char *);
