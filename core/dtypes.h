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
