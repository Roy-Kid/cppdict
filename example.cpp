#include <variant>
#include <iostream>
int main()
{

    auto v1 = std::variant<int, double>(1);
    auto i = v1.index();
    std::cout << std::get<i>(v1) << std::endl;

}