#include "../common/dissector.hh"
#include "../common/use_context.hh"

int dissect_codec_bitmap(dissector d, int idx, context* ctx) {
    const use_context uc(ctx, "codec-bitmap", d, 0);

    return uc.length;
}

// 9.11.3.62	Supported codec list
// See subclause 10.5.4.32 in 3GPP TS 24.008 [12].
int dissect_supported_codec_list(dissector d, context* ctx) {
    const use_context uc(ctx, "supported-codec-list", d, 0);

    auto              i = 1;
    return uc.length;
}
