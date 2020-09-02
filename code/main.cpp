#include "widgets.hpp"
#include "colors.hpp"
#include "utils.hpp"


int main(){
   
   haevn::terminal::widgets::PasswordInput password_input;
   std::string in = password_input.getPassword('*');

    haevn::terminal::widgets::ValueSlider sd;
    int value = sd.getValue();
    std::cout << value << std::endl;
    return 0;
}