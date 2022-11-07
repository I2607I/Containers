#include <iostream>
#include <list>

std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list)
        ostr << " " << i;
 
    return ostr;
}

int main() {
    // std::list<int> a = {1, 2, 3, 5, 7, 9, 100};
    // std::list<int> b = {2, 6, 99};
    // a.merge(b);
    // for (int item: a) {
    //     std::cout << item << " ";
    // }


    std::list<int> list1 = {1, 2, 3, 4, 5};
    std::list<int> list2 = {10, 20, 30, 40, 50};
 
    auto it = list1.begin();
    std::advance(it, 5);
 
    list1.splice(it, list2);
 
    std::cout << "list1:" << list1 << "\n";
    std::cout << "list2:" << list2 << "\n";
}