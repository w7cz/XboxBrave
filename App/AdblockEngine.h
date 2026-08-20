#pragma once
#include <cstdint>

extern "C" {
    void* engine_new(const char* rules);
    bool engine_match(void* engine, const char* url, const char* source);
    void engine_free(void* engine);
}
