#include "dissect_mm_msg.hh"
#include "ts24007.hh"

/*
 * 8.2.6 Registration request
 */
extern const field_meta* nas_5gs_registration_req_flags[];
extern const element_meta  em_de_nas_5gs_mm_5gs_mobile_id;

int mm::nas_5gs_mm_registration_req(packet_info* pinfo,
                                    proto_node*  tree,
                                    tvbuff*      buf,
                                    int          offset,
                                    int          len,
                                    context*     ctx) {
    pinfo->dir = pi_dir::ul;
    // get private data

    /*   5GS registration type    5GS registration type 9.11.3.7    M    V    1/2  H0*/
    /*    ngKSI    NAS key set identifier 9.11.3.32    M    V    1/2 H1*/
    // tree->add_item(pinfo, buf, offset, 1, nas_5gs_registration_req_flags, enc::none);
    tree->add_subtree(pinfo, buf, offset, 1, nullptr);
    tree->set_bitmask_list(nas_5gs_registration_req_flags, enc::be);
    offset++;
    len--;

    /*    Mobile identity    5GS mobile identity 9.11.3.4    M    LV-E    6-n*/
    auto consumed = dissect_elem_lv_e(
        nullptr, &em_de_nas_5gs_mm_5gs_mobile_id, tree, pinfo, buf, offset, len);
    offset -= consumed;
    len -= consumed;

    return 0;
}

int mm::nas_5gs_mm_registration_accept(packet_info* pinfo,
                                       proto_node*  tree,
                                       tvbuff*      buf,
                                       int          offset,
                                       int          len,
                                       context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_registration_complete(packet_info* pinfo,
                                         proto_node*  tree,
                                         tvbuff*      buf,
                                         int          offset,
                                         int          len,
                                         context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_registration_rej(packet_info* pinfo,
                                    proto_node*  tree,
                                    tvbuff*      buf,
                                    int          offset,
                                    int          len,
                                    context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_de_reg_req_ue_orig(packet_info* pinfo,
                                      proto_node*  tree,
                                      tvbuff*      buf,
                                      int          offset,
                                      int          len,
                                      context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_de_registration_req_ue_term(packet_info* pinfo,
                                               proto_node*  tree,
                                               tvbuff*      buf,
                                               int          offset,
                                               int          len,
                                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_service_req(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_service_rej(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_service_acc(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_conf_upd_cmd(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_conf_update_comp(packet_info* pinfo,
                                    proto_node*  tree,
                                    tvbuff*      buf,
                                    int          offset,
                                    int          len,
                                    context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_req(packet_info* pinfo,
                                      proto_node*  tree,
                                      tvbuff*      buf,
                                      int          offset,
                                      int          len,
                                      context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_resp(packet_info* pinfo,
                                       proto_node*  tree,
                                       tvbuff*      buf,
                                       int          offset,
                                       int          len,
                                       context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_rej(packet_info* pinfo,
                                      proto_node*  tree,
                                      tvbuff*      buf,
                                      int          offset,
                                      int          len,
                                      context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_failure(packet_info* pinfo,
                                          proto_node*  tree,
                                          tvbuff*      buf,
                                          int          offset,
                                          int          len,
                                          context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_authentication_result(packet_info* pinfo,
                                         proto_node*  tree,
                                         tvbuff*      buf,
                                         int          offset,
                                         int          len,
                                         context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_id_req(packet_info* pinfo,
                          proto_node*  tree,
                          tvbuff*      buf,
                          int          offset,
                          int          len,
                          context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_id_resp(packet_info* pinfo,
                           proto_node*  tree,
                           tvbuff*      buf,
                           int          offset,
                           int          len,
                           context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_sec_mode_cmd(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_sec_mode_comp(packet_info* pinfo,
                                 proto_node*  tree,
                                 tvbuff*      buf,
                                 int          offset,
                                 int          len,
                                 context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_sec_mode_rej(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_5gmm_status(packet_info* pinfo,
                               proto_node*  tree,
                               tvbuff*      buf,
                               int          offset,
                               int          len,
                               context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_notification(packet_info* pinfo,
                                proto_node*  tree,
                                tvbuff*      buf,
                                int          offset,
                                int          len,
                                context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_notification_resp(packet_info* pinfo,
                                     proto_node*  tree,
                                     tvbuff*      buf,
                                     int          offset,
                                     int          len,
                                     context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_ul_nas_transp(packet_info* pinfo,
                                 proto_node*  tree,
                                 tvbuff*      buf,
                                 int          offset,
                                 int          len,
                                 context*     ctx) {
    return 0;
}

int mm::nas_5gs_mm_dl_nas_transp(packet_info* pinfo,
                                 proto_node*  tree,
                                 tvbuff*      buf,
                                 int          offset,
                                 int          len,
                                 context*     ctx) {
    return 0;
}
