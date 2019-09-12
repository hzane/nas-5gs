#pragma once

typedef unsigned char octet;

// NOLINTNEXTLINE
struct description {
    virtual const char* name() const                                = 0; // NOLINT
    virtual const char* pretty(const octet* data, int length) const = 0; // NOLINT
    virtual const char* alias() const                               = 0; // NOLINT
protected:
    virtual ~description(){}; // NOLINT
};
