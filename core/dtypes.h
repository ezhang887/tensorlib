#pragma once

enum class Dtype {
    INT8,
    INT16,
    INT32,
    INT64,
    FLOAT,
    DOUBLE,
};

inline size_t dtype_to_size(Dtype dtype) {
    switch (dtype) {
        case Dtype::INT8:
            return sizeof(int8_t);
        case Dtype::INT16:
            return sizeof(int16_t);
        case Dtype::INT32:
            return sizeof(int32_t);
        case Dtype::INT64:
            return sizeof(int64_t);
        case Dtype::FLOAT:
            return sizeof(float);
        case Dtype::DOUBLE:
            return sizeof(double);
        default:
            return 0;
    }
}

template <typename T>
bool is_of_type(Dtype dtype) {
    T var = T();
    switch (dtype) {
        case Dtype::INT8:
            return typeid(var) == typeid(int8_t);
        case Dtype::INT16:
            return typeid(var) == typeid(int16_t);
        case Dtype::INT32:
            return typeid(var) == typeid(int32_t);
        case Dtype::INT64:
            return typeid(var) == typeid(int64_t);
        case Dtype::FLOAT:
            return typeid(var) == typeid(float);
        case Dtype::DOUBLE:
            return typeid(var) == typeid(double);
        default:
            return false;
    }
}
