#include "core/tensor.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
    Tensor t({10, 20, 30, 40}, Dtype::INT32, true);

    auto accessor = t.accessor<int32_t, 4>();
    accessor[0][0][0][0] = 254;
    accessor[9][0][28][0] = 123;

    std::cout << accessor[0][0][0][0] << std::endl;
    std::cout << accessor[9][0][28][0] << std::endl;
    std::cout << accessor[9][0][28][1] << std::endl;
}
