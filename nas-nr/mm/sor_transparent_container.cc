#include "../common/dissector.hh"
#include "../common/messages.hh"
#include "../common/use_context.hh"

// SOR transparent container   9.11.3.51
result_t die_sor_transparent_container(dissector                    d,
                                       context*                     ctx,
                                       sor_transparent_container_t* ret) {
    /* Layout differs depending on SOR data type*/
    const use_context uc(&d, ctx, "sor-transparent-container", 0);
    de_uint8(d, ctx, &ret->header.sor_data_type, 0x01u);
    de_uint8(d, ctx, &ret->header.list_ind, 0x02u);
    de_uint8(d, ctx, &ret->header.list_type, 0x04u);
    de_uint8(d, ctx, &ret->header.ack, 0x08u).step(d);

    de_fixed(d, ctx, ret->maci).step(d);
    if (ret->header.sor_data_type == 1) {
        return {uc.length};
    }
    de_uint16(d, ctx, &ret->counter).step(d);

    if (ret->header.list_type == 1) {
        ret->access_technology =
            std::make_shared< std::vector< sor_transparent_container_t::plmn_id_t > >();
        for (auto i = ret->counter; i > 0; --i) {
            sor_transparent_container_t::plmn_id_t v = {};
            de_fixed(d, ctx, v.id).step(d);
            de_uint16(d, ctx, &v.access_technology_id).step(d);
            ret->access_technology->push_back(v);
        }
        return {uc.length};
    }

    ret->packet = std::make_shared< octet_t >();
    de_octet(d, ctx, ret->packet.get()).step(d);

    return {uc.length};
}
