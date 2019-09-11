#pragma once

#if defined(NASNRTS24501_EXPORTS)
#define NASNRAPI __declspec(dllexport)
#else
#define NASNRAPI
#endif

typedef unsigned char octet_t;

// NOLINTNEXTLINE
struct nas_nr_message {
    virtual const char*           name() const         = 0; // NOLINT
    virtual const char*           value() const        = 0; // NOLINT -use-nodiscard
    virtual const octet_t*        data() const         = 0; // NOLINT -use-nodiscard
    virtual int                   offset() const       = 0; // NOLINT -use-nodiscard
    virtual int                   length() const       = 0; // NOLINT -use-nodiscard
    virtual int                   indent() const       = 0; // NOLINT
    virtual const nas_nr_message* first_child() const  = 0; // NOLINT
    virtual const nas_nr_message* next_sibling() const = 0; // NOLINT
protected:    virtual ~nas_nr_message(){};                            // NOLINT
};

void NASNRAPI nas_nr_message_free(nas_nr_message* p);

int NASNRAPI dissect_nas_nr(nas_nr_message * * root, const octet_t* data, int length);
