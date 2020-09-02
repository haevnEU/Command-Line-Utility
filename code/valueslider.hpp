/*
 * This file contains an implementation of a value slider
 * This file is licensed under the MIT license. If you decide to use this
 *  file a copy of the following license must be provided. Giving credit in
 *  form of a mention inside your source code, documentation or the final
 *  product would be nice but is not required.
 *
 * Example
 * +---------------------------------------------+   
 * | haevn::terminal::widgets::ValueSlider sd;   |
 * | int value = sd.getValue();                  |
 * +---------------------------------------------+
 * 
 *  MIT License
 *
 * Copyright (c) 2020 Nils Milewski (haevn)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

 * author Nils Milewski
 * version 1.0.0.0 
 */
#pragma once

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdint>

extern "C"
{
    #include <termios.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <sys/stat.h>
    #include <unistd.h>


}

#include "utils.hpp"
#include "colors.hpp"

namespace haevn::terminal::widgets{

    struct ValueSliderSettings{
        std::string message = "";
        char fill_character = ' ';
        int maximum = 100;
        int minimum = 49;
        int step = 1;
        bool clear_cache = false;
        /**
         * @brief Background color
         */
        const char* background = terminal::colors::background::CYAN;
        const char* fill = terminal::colors::background::MAGENTA;

        /**
         * @brief foregrounds color
         */
        const char* foreground = terminal::colors::foreground::BLUE;
        char increment_key = 'd';
        char decrement_key = 'a';
    };

    class ValueSlider{
    private:
        ValueSliderSettings* settings_m;
        int value = 0;
    public:

        ValueSlider(){
            settings_m = new ValueSliderSettings();
        }

        ValueSlider(ValueSliderSettings* settings_t) : settings_m(settings_t){}

        ~ValueSlider(){
            delete settings_m;
        }

        ValueSliderSettings* settings(){
            return settings_m;
        }

        int getValue(){
            if(settings()->minimum > settings()->maximum){
                return -1;
            }
            if(settings()->clear_cache){
                char c2;
                while ((c2 = haevn::utils::Getchar::getch()) != '\n' && c2 != EOF) { }
            }
 
            value = settings()->minimum;
            int step = (settings()->maximum - settings()->minimum) / 50;
            step = (step == 0 ? 1 : step);
            char c;
            while(true){
                
                std::system("clear");
                std::cout << terminal::colors::CLEAR << settings()->message << " " << utils::dateTime() << std::endl;
                std::cout << "Use " << settings()->decrement_key << "/" << settings()->increment_key <<" to change the value and <ENTER> to select" << std::endl
                          << std::endl << "("<< settings()->minimum << ")[" << settings()->foreground;
                    
                
                for(int i = 0; i < 50; i++){
                    if(i < ((value - settings()->minimum) / step)){
                        std::cout << settings()->fill << settings()->fill_character;
                    }else{
                        std::cout << settings()->background << " ";
                    }
                }
                std::cout << haevn::terminal::colors::RESET << "](" << (value) << "/" << settings()->maximum << ")";

                c = utils::Getchar::getch();
                if(c == settings()->decrement_key){
                    value -= step;
                    if(value < settings()->minimum){
                        value = settings()->minimum;
                    }
                }

                if(c == settings()->increment_key){
                    value += step;
                    if(value >= settings()->maximum){
                        value = settings()->maximum;
                    }
                }
                if(c == 10){
                    break;
                }
            }
            return value;
        }
    };

}