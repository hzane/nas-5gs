#include "nas-nr.hh"
#include <string>
#include <cstring>
#include "dissect_nas5g.hh"

#if NASNR_COMPILER_CXX_USING_ALIAS
using string = std::string;
#else
using std::string;
#endif

struct nas_nr_message_imp NASNR_FINAL : nas_nr_message {
    string              tag     NASNR_EQUAL_INIT ({});
    string              val     NASNR_EQUAL_INIT ({});
    const octet*        dat     NASNR_EQUAL_INIT (nullptr) ;
    int                 len     NASNR_EQUAL_INIT (0);
    int                 start   NASNR_EQUAL_INIT (0);
    int                 level   NASNR_EQUAL_INIT (0);
    const description*  meta    NASNR_EQUAL_INIT (nullptr);
    nas_nr_message_imp* child   NASNR_EQUAL_INIT (nullptr);
    nas_nr_message_imp* sibling NASNR_EQUAL_INIT (nullptr);

    const char*           name() const override;
    const char*           value() const override;
    const octet*          data() const override;
    int                   offset() const override;
    int                   length() const override;
    int                   indent() const override;
    const description*    desc() const override;
    const nas_nr_message* first_child() const override;
    const nas_nr_message* next_sibling() const override;

    ~nas_nr_message_imp() NASNR_FINAL;
    nas_nr_message_imp() NASNR_DEFAULT_FUNCTION;
    nas_nr_message_imp(const nas_nr_message_imp&) NASNR_DELETED_FUNCTION; 
#if NASNR_COMPILER_CXX_DELETED_FUNCTIONS   
    nas_nr_message_imp(const nas_nr_message_imp&&) NASNR_DELETED_FUNCTION;
    nas_nr_message_imp& operator=(const nas_nr_message_imp&&) NASNR_DELETED_FUNCTION;
#endif
    nas_nr_message_imp& operator=(const nas_nr_message_imp&) NASNR_DELETED_FUNCTION;
};

#if !NASNR_COMPILER_CXX_DEFAULT_FUNCTIONS
nas_nr_message_imp::nas_nr_message_imp(){
}
#endif

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
    const NASNR_AUTO(nas_nr_message_imp*) ne = dynamic_cast< nas_nr_message_imp* >(p);
    delete ne;
}

nas_nr_message_imp* export_proto_node(proto_node const* node, int indent) {
    NASNR_AUTO(nas_nr_message_imp*) ret = new nas_nr_message_imp();
    ret->tag = node->name;
    ret->val = node->text;
    ret->dat = node->data;
    ret->len = node->length;
    ret->start = node->offset;
    ret->level = indent;
#if NASNR_COMPILER_CXX_TYPE_DEDUCE
	ret->meta = node->meta;
#else
    ret->meta  = (const description*) node->meta;
#endif
    nas_nr_message_imp* next = nullptr;
	for (NASNR_AUTO(std::list<proto_node*>::const_iterator) n = node->children.begin(); n!=node->children.end(); ++n) {
        NASNR_AUTO(nas_nr_message_imp*) const child = export_proto_node(*n, indent + 1);
        if (ret->child == nullptr) ret->child = child;
        if (next != nullptr)
            next->sibling = child;
        next = child;
    }
    return ret;
}

int dissect_nas_nr(nas_nr_message * * root, const octet* data, int length) {
    tvbuff          tvb   = NASNR_LIST_INIT(tvbuff, data, length);
    context         ctx   = NASNR_LIST_INIT(context);
    packet_info     pinfo = NASNR_LIST_INIT(packet_info);
    proto_node      node  = NASNR_LIST_INIT(proto_node);
    *root                 = nullptr;

    const dissector d = {&pinfo, &node, &tvb, 0, length, nullptr};

    const NASNR_AUTO(int) ret = nas_5gs_module.dissector(d, &ctx);
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
#if NASNR_COMPILER_CXX_TYPE_DEDUCE
	const auto fm = static_cast<const field_meta*>(m);
#else
    NASNR_AUTO(const field_meta*) fm   = reinterpret_cast< const field_meta* >(m); // NOLINT
#endif
    if (!fm) return nullptr;

    const NASNR_AUTO(string)  text = field_meta_format(fm, data, length, enc::be);
    return xstrdup (text.c_str());
}

void NASNRAPI pretty_format_free(char* p) {
    free(p);
    return;
}
