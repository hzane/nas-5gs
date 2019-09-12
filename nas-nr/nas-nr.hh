#pragma once
#include "description.hh"

#if defined(NASNRTS24501_EXPORTS)
// NOLINTNEXTLINE
#define NASNRAPI __declspec(dllexport)
#else
#define NASNRAPI
#endif

struct description;

// NOLINTNEXTLINE
struct nas_nr_message {
    virtual const char*           name() const         = 0; // NOLINT
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

void NASNRAPI nas_nr_message_free(nas_nr_message* p);

int NASNRAPI dissect_nas_nr(nas_nr_message** root, const octet* data, int length);
