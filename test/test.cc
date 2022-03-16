#include "core/tensor.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
    /*
    Tensor t({10, 20, 30, 40}, Dtype::INT32, true);

    auto accessor = t.accessor<int32_t, 4>();
    accessor[0][0][0][0] = 254;
    accessor[9][0][28][0] = 123;

    cout << accessor[0][0][0][0] << endl;
    cout << accessor[9][0][28][0] << endl;
    cout << accessor[9][0][28][1] << endl;
    */

    Tensor t({10, 20}, Dtype::INT32, true);

    Tensor u = t[1];
    auto accessor = u.accessor<int32_t, 1>();
    accessor[0] = 12345;
    cout << accessor[0] << endl;

    auto accessor2 = t.accessor<int32_t, 2>();
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 20; j++) {
            cout << accessor2[i][j] << " ";
        }
        cout << endl;
    }
}
