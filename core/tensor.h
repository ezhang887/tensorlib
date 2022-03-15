#pragma once

#include <vector>
#include <memory>

#include "storage.h"

using std::vector;

class Tensor {
    private:
        vector<size_t> dims_;
        vector<size_t> strides_;
        size_t offset_;
        std::shared_ptr<Storage> storage_;

    public:
        Tensor() = delete;
        Tensor(vector<size_t> dims);
};
