#include "use_context.hh"
#include "config.hh"
#include "dissector.hh"

void use_context::extraneous_data_check() const {
    if (maxlen < 0) return;
    if (length < 0 || length > maxlen)
        d.add_expert(-1, formats(
                         "extra %d bytes at %d under %s",
                         length - maxlen,
                         offset,
                         ctx->paths.back().c_str()));
    if (length < 0) {
        diag("underflow at %s %d:%d\n", paths(ctx).c_str(), offset, length);
    }
    if (length > maxlen) {
        diag("extraneous data (%d) bytes at %s %d\n",
             (length - maxlen),
             paths(ctx).c_str(),
             offset);
    }
}

use_context::use_context(context* ctx, const char* path, dissector const& d, const int maxlen )
: ctx(ctx), offset(d.offset), length(d.length), maxlen(maxlen), d(d) {
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
    if(!ctx) return;

    extraneous_data_check();
    ctx->paths.pop_back();
}