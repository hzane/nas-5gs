#pragma once
#include "nas-nr-compiler-detection.hh"
#include "description.hh"

#if defined NASNRTS24501_EXPORTS

#if defined _WIN32 || defined _WIN64
// NOLINTNEXTLINE
#define NASNRAPI __declspec(dllexport)
#else
#define NASNRAPI __attribute__((visibility("default")))
#endif

#else
#define NASNRAPI
#endif

struct description;

// NOLINTNEXTLINE
struct nas_nr_message {
    virtual const char*           name() const         NASNR_EQUAL_INIT(0); // NOLINT
    virtual const char*           value() const        = 0; // NOLINT -use-nodiscard
    virtual const octet*          data() const         = 0; // NOLINT -use-nodiscard
    virtual int                   offset() const       = 0; // NOLINT -use-nodiscard
    virtual int                   length() const       = 0; // NOLINT -use-nodiscard
    virtual int                   indent() const       = 0; // NOLINT
    virtual const description*    desc() const         = 0; // NOLINT
    virtual const nas_nr_message* first_child() const  = 0; // NOLINT
    virtual const nas_nr_message* next_sibling() const = 0; // NOLINT
protected:    virtual ~nas_nr_message(){};                            // NOLINT
};

NASNRAPI void nas_nr_message_free(nas_nr_message* p);

NASNRAPI int dissect_nas_nr(nas_nr_message** root,
                            const octet*     data,
                            int              length,
                            void*            nas_nr = nullptr);

NASNRAPI char* pretty_format(const description* m, const octet* data, int length);

NASNRAPI void  pretty_format_free(char* p);

NASNRAPI void* nas_nr_new();
NASNRAPI void  nas_nr_free(void* nn);
