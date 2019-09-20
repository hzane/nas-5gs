#include "nas-nr.hh"
#include <string>
#include <cstring>
#include "dissect_nas5g.hh"

using string = std::string;

struct nas_nr_message_imp final : nas_nr_message {
    string              tag     NASNR_EQUAL_INIT ({});
    string              val     NASNR_EQUAL_INIT ({});
    const octet*        dat     NASNR_EQUAL_INIT (nullptr) ;
    int                 len     NASNR_EQUAL_INIT (0);
    int                 start   NASNR_EQUAL_INIT (0);
    int                 level   NASNR_EQUAL_INIT (0);
    const description*  meta    NASNR_EQUAL_INIT (nullptr);
    nas_nr_message_imp* child   NASNR_EQUAL_INIT (nullptr);
    nas_nr_message_imp* sibling NASNR_EQUAL_INIT (nullptr);

    [[nodiscard]] const char*           name() const override;
    [[nodiscard]] const char*           value() const override;
    [[nodiscard]] const octet*          data() const override;
    [[nodiscard]] int                   offset() const override;
    [[nodiscard]] int                   length() const override;
    [[nodiscard]] int                   indent() const override;
    [[nodiscard]] const description*    desc() const override;
    [[nodiscard]] const nas_nr_message* first_child() const override;
    [[nodiscard]] const nas_nr_message* next_sibling() const override;

    ~nas_nr_message_imp() final;
    nas_nr_message_imp() = default;
    nas_nr_message_imp(const nas_nr_message_imp&) = delete;
    nas_nr_message_imp(const nas_nr_message_imp&&) = delete;
    nas_nr_message_imp& operator=(const nas_nr_message_imp&&) = delete;
    nas_nr_message_imp& operator=(const nas_nr_message_imp&) = delete;
};

const description* nas_nr_message_imp::desc() const { return meta; }

const char* nas_nr_message_imp::value() const { return val.c_str(); }

const octet* nas_nr_message_imp::data() const { return dat; }

int nas_nr_message_imp::offset() const { return start; }

int nas_nr_message_imp::length() const { return len; }

int nas_nr_message_imp::indent() const { return level; }

const nas_nr_message* nas_nr_message_imp::first_child() const { return child; }

const nas_nr_message* nas_nr_message_imp::next_sibling() const { return sibling; }

nas_nr_message_imp::~nas_nr_message_imp() {
    delete child;
    delete sibling;
}

const char* nas_nr_message_imp::name() const { return tag.c_str(); }

void NASNRAPI nas_nr_message_free(nas_nr_message* p){
    const auto ne = dynamic_cast< nas_nr_message_imp* >(p);
    delete ne;
}

nas_nr_message_imp* export_proto_node(proto_node const* node, int indent) {
    auto ret = new nas_nr_message_imp();
    ret->tag = node->name;
    ret->val = node->text;
    ret->dat = node->data;
    ret->len = node->length;
    ret->start = node->offset;
    ret->level = indent;
    ret->meta  = node->meta;

    nas_nr_message_imp* next = nullptr;
    for (const auto n : node->children) {
        const auto child = export_proto_node(n, indent + 1);
        if (ret->child == nullptr) ret->child = child;
        if (next != nullptr)
            next->sibling = child;
        next = child;
    }
    return ret;
}

NASNRAPI int dissect_nas_nr(nas_nr_message** root,
                            const octet*     data,
                            int              length,
                            int              dir,
                            void*            env) {
    tvbuff          tvb   = NASNR_LIST_INIT(tvbuff, data, length);
    context         alt   = NASNR_LIST_INIT(context);
    packet_info     pinfo = NASNR_LIST_INIT(packet_info);
    proto_node      node  = NASNR_LIST_INIT(proto_node);
    *root                 = nullptr;
    pinfo.dir             = dir;
    context* ctx          = env ? static_cast< context* >(env) : &alt;

    const dissector d = {&pinfo, &node, &tvb, 0, length, nullptr};

    const auto ret = nas_5gs_module.dissector(d, ctx);
    if (!node.children.empty()) {
        *root = export_proto_node(node.children.front(), 0);
    }

    return ret;
}

#if defined _WIN32 || defined _WIN64
// NOLINTNEXTLINE
#define xstrdup _strdup
#else
#define xstrdup strdup
#endif

char NASNRAPI *pretty_format(const description* m, const octet* data, int length) {
    const auto fm   = static_cast< const field_meta* >(m); // NOLINT
    if (!fm) return nullptr;

    const auto  text = fm->format(data, length, enc::be);
    return xstrdup (text.c_str());
}

void NASNRAPI pretty_format_free(char* p) {
    free(p);
}

NASNRAPI const char* nas_nr_description(){
    return nas_5gs_module.full_name;
}
NASNRAPI void* nas_nr_context_new(){
    return new context{};
}
NASNRAPI void nas_nr_context_free(void*d){
    auto ctx = static_cast<context*>(d);
    delete ctx;
}
