/**
 * This file contains an implementation of a menu
 * This file is licensed under the MIT license. If you decide to use this
 *  file a copy of the following license must be provided. Giving credit in
 *  form of a mention inside your source code, documentation or the final
 *  product would be nice but is not required.
 *
 * Example
 * +--------------------------------------------------------------------+
 * |   // Create and populate a std::vector                             |
 * |  std::vector<std::string> entries;                                 |
 * |                                                                    |
 * |  // Create the checkbox                                            |
 * |  haevn::terminal::widgets::Menu menu(entries, txt);                |
 * |  int choice = menu.getSelection();                                 |
 * +--------------------------------------------------------------------+ 
 * 
 * MIT License
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

namespace haevn::terminal::widgets{
    
    /**
     * @brief Contains menu information 
     * @details Contains all settings for generating a menu
     */
    struct MenuSettings{
        /**
         * @brief Enables the over/underflow of line selection
         */
        bool row_selection_overflow = true;

        /**
         * @brief Clears the the input cache
         */
        bool clear_cache = false;

        /**
         * @brief Previous selected row
         */
        int preselected_row = 0;

        /**
         * @brief Optional error message
         */
        std::string sub_header;

        /**
         * @brief Background color
         */
        const char* background = terminal::colors::background::CYAN;

        /**
         * @brief Hightlighting color
         */
        const char* foreground = terminal::colors::foreground::BLACK;

        /**
         * @brief Row selection indicator
         */
        const char* line_selector[2] = {" >", "< "};

        /**
         * @brief Navigate UP keybind
         */
        char up_key = 'w';
        
        /**
         * @brief Navigate DOWN keybind
         */
        char down_key = 's';
    };


    class Menu{
        private:
            std::vector<std::string>& entries;
            std::string& message;
            MenuSettings* settings_t;
        public:
            Menu(std::vector<std::string>& entries_t, std::string& message_t)
             : entries(entries_t), message(message_t){
                settings_t = new MenuSettings();
             }

            ~Menu(){
                delete settings_t;
            }

            MenuSettings* settings(){
                return settings_t;
            }
       
            /**
             * @brief Prints a menu on the terminal
             * @details This method prints every menu entry on the terminal and allows the selection
             *          with specified keys. The menu is customizable via a settings argument.
             *          The result value correspond to the provided entries, e.g. result 0 <=> entries[0]
             *          A known bug is that the input stream is filled after some operation, therefore
             *          setting the settings entry clear_cache is recommended
             * @param entries Menu entries which should be printed
             * @param amount_entries Amount of the entries
             * @param menu_header Header of the menu
             * @param settings Settings object
             * @return int Selected 0 based index
            */
            int getSelection(){
                char c = 'D';
                int row = settings()->preselected_row;

                if(settings()->clear_cache){
                    char c2;
                    while ((c2 = haevn::utils::Getchar::getch()) != '\n' && c2 != EOF) { }
                }

                while(true){
                    std::system("clear");
                    std::cout << terminal::colors::CLEAR << message << " " << utils::dateTime() << std::endl;

                    std::cout << "Use " << settings()->up_key << "/" << settings()->down_key <<" to navigate and <ENTER> to select" << std::endl;
                    
                    if(settings()->sub_header.size() > 0){
                        std::cout << settings()->sub_header << std::endl;
                    }

                    std::cout << std::endl;
                    
                    for(int i = 0; i < entries.size(); i++){
                        printEntry(entries.at(i), i, row);
                    }

                    c = utils::Getchar::getch();

                    if(c == settings()->up_key){
                        row--;
                        if(row < 0){
                            row = ((settings()->row_selection_overflow) ? entries.size() - 1 : 0);
                        }
                    }

                    if(c == settings()->down_key){
                        row++;
                        if(row >= (entries.size())){
                            row = ((settings()->row_selection_overflow) ? 0 : entries.size() - 1);
                        }
                    }

                    if(c == 10){
                        break;
                    }
                }

                return row;
            }
        private:   
            /**
             * @brief Prints a menu entry to the terminal
             * @param message Message to be printed
             * @param row Row index
             * @param current_row Current row index
             */
            void inline printEntry(std::string message, int row, int current_row){
                const char* color = settings()->background;

                if(row == current_row){
                    std::cout << color << settings()->foreground << settings()->line_selector[0]; 
                }else{
                    std::cout << ' ' << haevn::terminal::colors::RESET;     
                }

                std::cout << message; 

                if(row == current_row){
                    std::cout << color << settings()->foreground << settings()->line_selector[1]; 
                }else{
                    std::cout << ' ';
                }

                std::cout << haevn::terminal::colors::RESET << std::endl;     
            }
    };
}