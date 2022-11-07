#include <iostream>
#include <vector>

int main() {
    std::vector<int> a = {1, 200000, 4};
    std::cout << a[0] << std::endl;
    std::cout << *a.begin()+1 << std::endl;
}