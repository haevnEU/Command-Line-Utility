/*
 * This file contains an implementation of a radiobutton
 * This file is licensed under the MIT license. If you decide to use this
 *  file a copy of the following license must be provided. Giving credit in
 *  form of a mention inside your source code, documentation or the final
 *  product would be nice but is not required.
 * 
 * 
 * Example
 * +--------------------------------------------------------------------+
 * |   // Create and populate a std::vector                             |
 * |  std::vector<haevn::terminal::widgets::RadioButtonEntry> entries;  |
 * |                                                                    |
 * |  std::string txt = "HELLO WORLD";                                  |
 * |  // Create the checkbox                                            |
 * |  haevn::terminal::widgets::RadioButton cb(entries, txt);           |
 * |  cb.selectItems();                                                 |
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
 *
 * author Nils Milewski
 * version 1.0.0.0 
 */
#pragma once

#include <string>
#include <vector>

namespace haevn::terminal::widgets{

    struct RadioButtonEntry{
        std::string text;
        bool selected;
    };

    struct RadioButtonSettings{
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

    class RadioButton{
    private:
            std::vector<RadioButtonEntry>& entries;
            std::string& message;
            RadioButtonSettings* settings_t;
    
    public:
        RadioButton(std::vector<RadioButtonEntry>& entries_t, std::string& message_t)
             : entries(entries_t), message(message_t){
            settings_t = new RadioButtonSettings();
        }

        ~RadioButton(){
            delete settings_t;
        }

        RadioButtonSettings* settings(){
            return settings_t;
        }
        
        void selectItems(){
            char c = 'D';
            int row = settings()->preselected_row;

            if(settings()->clear_cache){
                char c2;
                while ((c2 = haevn::utils::Getchar::getch()) != '\n' && c2 != EOF) { }
            }

            while(true){
                std::system("clear");
                std::cout << terminal::colors::CLEAR << message << " " << utils::dateTime() << std::endl;

                std::cout << "Use " << settings()->up_key << "/" << settings()->down_key <<" to navigate, <ENTER> to check/uncheck and q to return" << std::endl;
                    
                if(settings()->sub_header.size() > 0){
                    std::cout << settings()->sub_header << std::endl;
                }

                std::cout << std::endl;
                    
                for(int i = 0; i < entries.size(); i++){
                    printEntry(entries.at(i).text, i, row);
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
                    check(row);   
                }
                if(c == 'q'){
                    break;
                }
            }
        }
        
    private:
        
        void check(int index){
            for(int i = 0; i < entries.size(); i++){
                entries.at(i).selected = false;
            }
            entries.at(index).selected = true;
        }

        void inline printEntry(std::string message, int row, int current_row){
            const char* color = settings()->background;

            if(row == current_row){
                std::cout << color << settings()->foreground << '[' << (entries.at(row).selected ? "•" : " ") << ']'; 
            }else{
                std::cout << '[' << (entries.at(row).selected ? "•" : " ") << ']';     
            }

            std::cout << message; 

            std::cout << haevn::terminal::colors::RESET << std::endl;     
        }

    };
}