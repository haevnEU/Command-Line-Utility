#include "widgets.hpp"
#include "colors.hpp"
#include "utils.hpp"

#include "keyboard.hpp"

#include <string>
int main(){
    std::string str = "STRING";
    std::vector<haevn::terminal::widgets::CheckBoxEntry> entries = {haevn::terminal::widgets::CheckBoxEntry{"Entry 1"}, haevn::terminal::widgets::CheckBoxEntry{"Entry 2"}};
    char c;
    c = haevn::utils::Getchar::getch();
    std::cout << (int)c << std::endl;
    c = haevn::utils::Getchar::getch();
    std::cout << (int)c << std::endl;
    c = haevn::utils::Getchar::getch();
    std::cout << (int)c << std::endl;
    c = haevn::utils::Getchar::getch();
    std::cout << (int)c << std::endl;
    
    return 0;
}