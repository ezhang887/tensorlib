#include "storage.h"

#include <cstdlib>

Storage::Storage(size_t bytes) {
    bytes_ = bytes;
    data_ = malloc(bytes);
}

Storage::Storage(Storage&& other) {
    if (this == &other) return;

    data_ = other.data_;
    other.data_ = NULL;
}

Storage& Storage::operator=(Storage&& other) {
    if (this == &other) return *this;

    data_ = other.data_;
    other.data_ = NULL;
    return *this;
}

Storage::~Storage() {
    if (data_) {
        free(data_);
    }
}

void* Storage::data() const {
    return data_;
}
