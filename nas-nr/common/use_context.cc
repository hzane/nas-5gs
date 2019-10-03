#include "use_context.hh"

#include "context.hh"
#include "core.hh"
#include "definitions.hh"

use_context::use_context(dissector const* d,
                         context*         ctx,
                         const char*      path,
                         const int        maxlen)
    : ctx(ctx), offset(d->offset), length(d->length), maxlen(maxlen), d(d) {
    if (!ctx) return;
    if (path == nullptr) path = ".";
    ctx->paths.emplace_back(path);
    diag("%s%s %d-%d\n",
         string(ctx->paths.size() << 1u, ' ').c_str(),
         path,
         offset,
         length);
}
use_context::~use_context() {
    extraneous_data_check();
    if (ctx) {
        ctx->paths.pop_back();
    }
}
void use_context::extraneous_data_check() {
    if (maxlen < 0) return;
    if (d->length <= maxlen) return;
    if (!ctx) return;

    diag("extraneous data %d bytes, %s\n", d->length, join(ctx->paths).c_str());
}

int use_context::consumed() const { return d->offset - offset; }
