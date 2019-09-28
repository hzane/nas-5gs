#pragma once

struct context;
struct dissector;
struct use_context {
    context*         ctx    = nullptr;
    int              offset = 0;
    int              length = 0;
    int              maxlen = 0;
    const dissector& d;

    use_context& operator=(const use_context&) = delete;
    use_context()                              = delete;
    use_context(const use_context&) = delete;
    void extraneous_data_check() const;

    use_context(context* ctx, const char* path, dissector const& d, const int maxlen = 0);
    ~use_context() ;
};