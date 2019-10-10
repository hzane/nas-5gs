#include "../common/dissector.hh"
#include "../common/ies.hh"
#include "../common/use_context.hh"

// Mapped EPS  bearer contexts     9.11.4.8
result_t die_mapped_eps_bearer_contexts(dissector                     d,
                                        context*                      ctx,
                                        mapped_eps_bearer_contexts_t* ret) {
    const use_context uc(&d, ctx, "mapped-eps-bearer-contexts", 0);
    while(d.length>0){
        mapped_eps_bearer_contexts_t::context_t v = {};
        de_uint8(d, ctx, &v.id).step(d);
        auto l = d.uint8(true);
        de_uint8(d, ctx, &v.parameters_n, 0x0fu);
        de_uint8(d, ctx, &v.ebit, 0x10u);
        de_uint8(d, ctx, &v.operation_code, 0xc0u).step(d);

        for (auto i = 0; i < v.parameters_n;++i) {
            mapped_eps_bearer_contexts_t::parameter_t p = {};
            de_uint8(d, ctx, &p.id).step(d);
            de_l_octet(d, ctx, &p.content).step(d);
            v.parameters.push_back(p);
        }
        ret->contexts.push_back(v);
    }
    return {uc.length};
}
