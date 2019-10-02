#pragma once
#include "context.hh"

struct dissector;
struct context;
struct use_context {
    const dissector* d      = nullptr;
    context*         ctx    = nullptr;
    int              offset = 0;
    int              length = 0;
    int              maxlen = 0;

    use_context& operator=(const use_context&) = delete;
    use_context()                              = delete;
    use_context(const use_context&)            = delete;

    use_context(dissector const* d, context* ctx, const char* path, int maxlen = 0);
    ~use_context();
    void extraneous_data_check();
};
