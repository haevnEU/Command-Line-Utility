/**
 * @file This file contains an implementation of a progressbar
 * @details This file is licensed under the MIT license. If you decide to use this
 *          file a copy of the following license must be provided. Giving credit in
 *          form of a mention inside your source code, documentation or the final
 *          product would be nice but is not required.
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

 * @author Nils Milewski
 * @version 1.0.0.0 
 */
#pragma once

#include <iostream>
#include <fstream>

extern "C"{
    #include <sys/ioctl.h>
    #include <unistd.h>
    #include <unistd.h>
}

#include "colors.hpp"

namespace haevn::terminal::widgets{

/**
 * @brief This is a settings structure for the progressbar
 * @details 
 * @author Nils Milewski
 * @version 1.0
 */
struct ProgressbarSettings{
    const char* fill_color = colors::background::TRANSPARENT;

    /**
     * @brief This attribute is the color of the progressbar
     */
    const char* progress_color = colors::foreground::WHITE;
    
    /**
     * @brief This attribute is the color of finish state
     */
    const char* done_color = colors::foreground::GREEN;
    
    /**
     * @brief This attribute is the color of abort state
     */
    const char* abort_color = colors::foreground::YELLOW;
    
    /**
     * @brief This attribute is the color of cancel state
     */
    const char* cancel_color = colors::foreground::RED;
    
    /**
     * @brief This attribute is the color of error state
     */
    const char* error_color = colors::foreground::RED;

    /**
     * @brief This is the total maximum of the progressbar
     */
    unsigned int maximum = 100;

    /**
     * @brief Ths is the minium of the progressbar
     */
    unsigned int minimum = 0;

    /**
     * @brief this is the possible bar width
     * @details IMPORTANT Note this attribute should never be changed
     */
    const int bar_width = 50;

    /**
     * @brief This attribtue is the progress bar fill character
     * @details Default is '='
     */
    char bar_character = '=';

    /**
     * @brief this is the tail of the progressbar
     * @details Default is >
     */
    char bar_tail_character = '>';
    
    /**
     * @brief this is the first character of the progressbar
     * @details Default is [
     */
    char bar_start = '[';

    /**
     * @brief this is the last character of the progressbar
     * @details Default is ]
     */
    char bar_end = ']';

    /**
     * @brief this is the first character of the percentage indicator
     * @details Default is (
     */
    char percentage_start = '(';

    /**
     * @brief this is the last character of the percentage indicator
     * @details Default is 
     */
    char percentage_end = ')';

};

/**
    * @brief This class contains a progressbar for CLI
    * @details This class will handle a progessbar.
    *          The object will only work for a command line interface.
    *          The progressbar will look like
    *          \code [====================>                    ] (50%) \endcode
    *          There are different visual states of the progressbar
    *          <table>
    *              <caption id="colore_codes">Possible color codes</caption>
    *              <tr><th>Color</th><th>Description</th></tr>
    *              <tr><td>Green</td><td>Progressbar finished and the operation associated should be successfull</td></tr>
    *              <tr><td>Yellow</td><td></td>The operation was canceled</tr>
    *              <tr><td>Red</td><td>The operation failed or was aborted</td></tr>
    *          </table>
    * @author Nils Milewski
    * @version 1.0
    */
class ProgressBar{
private:

    ProgressbarSettings* settings_t;
    /**
     * @brief The current value of the progressbar
     * @details This attribute should never be manipulated by hand
     */
    double progress_bar_value;


    /**
     * @brief This attribute indicates if the progressbar reached 100%
     * @details If this attribute is true no operation, except reset will be possible
     */
    bool done = false;
 
public:
    /**
     * @brief Construct a new progressbar object
     * @param os Stream where the progressbar should be drawn, default std::cout
     */
    explicit ProgressBar(){
        settings_t = new ProgressbarSettings();
    }

    ~ProgressBar(){
        delete settings_t;
    }

    ProgressbarSettings* settings(){
        return settings_t;
    }

    /**
     * @brief updates the value
     * @details Updates the progressbar by \p step . Default is 1
     * @param step Step to increment, default 1. If negative the progressbar will rewind
     */
    void update(double step = 1) {
        progress_bar_value += step;
        if(progress_bar_value >= maximum()){
            finish();
        }else{
            for(int i = 0; i < 10; ++i){
                std::cout << settings()->progress_color; 
                render();
                std::cout << haevn::terminal::colors::RESET;
            }
        }
    }

    /**
     * @brief Sets the maximum value
     * @param max New maximum
     */
    void maximum(int max){
        if(max > settings()->maximum){
            max = settings()->maximum;
        }else if(max < 0){
            max = 0;
        }
        settings()->maximum = max;
    }

    /**
     * @brief Gets the maximum value
     * @return int Maximum value of the progressbar
     */
    int maximum(){
        return settings()->maximum;
    }

    /**
     * @brief Gets the current value
     * @return int Current value of the progressbar
     */
    int value(){
        return progress_bar_value;
    }

    /**
     * @brief Sets the current value
     */
    void value(int value){
        if(value > settings()->maximum){
            value = settings()->maximum;
        }else if(value < 0){
            value = 0;
        }
        progress_bar_value = value;
        render();
    }

    /**
     * @brief Cancels the progressbar
     * @details This method cancel the progressbar. The progressbar will be rendered in yellow indicating a cancel state.
     *          This operation aborts if the progressbar is allready at 100%.
     */
    void cancel(){
        if(done){
            return;
        }
        std::cout << settings()->cancel_color;
        render();
        std::cout << haevn::terminal::colors::RESET;
        done = true;
    }

    /**
     * @brief Aborts the progressbar
     * @details This method aborts the progressbar. The progressbar will be rendered in red indicating a abort state.
     *          This operation aborts if the progressbar is allready at 100%.
     *          Note this method can be used as a error indication
     */
    void abort(){
        if(done){
            return;
        }
        std::cout << settings()->abort_color;
        render();
        std::cout << haevn::terminal::colors::RESET;
        done = true;
    }

    /**
     * @brief Finishes the progressbar
     * @details This method finishes the progressbar. The progressbar will be rendered in green indicating a successfull state
     *          This operation aborts if the progressbar is allready at 100%
     */
    void finish(){
        if(done){
            return;
        }
        std::cout << settings()->done_color;
        render();
        std::cout << haevn::terminal::colors::RESET << std::endl;
        done = true;
    }

    /**
     * @brief This method resets the progressbar
     * @details The current value will be set to 0.
     *          If the progressbar was finished, all methods will be available again.
     *          It will also render the progressbar empty
     */
    void reset(){
        done = false;
        progress_bar_value = 0;
        render();
    }

private:

    /**
     * @brief This method renders the progressbar
     * @details The method will calculate how wide the progessbar should be rendered.
     *          Later it will override the previous progressbar with a new one based on previous previous calculated width.
     */
    void render(){
        int amountOfFiller = (int)((progress_bar_value / maximum())*(double)settings()->bar_width);

        std::cout << "\r" << settings()->fill_color << settings()->bar_start;
        for (int a = 0; a < amountOfFiller; a++) {
            std::cout << settings()->bar_character;
        }
        std::cout << settings()->bar_tail_character;
        for (int b = 0; b < settings()->bar_width - amountOfFiller; b++) {
            std::cout << " ";
        }
        std::cout << settings()->bar_end << colors::RESET << " " << settings()->percentage_start << (int)(100*(progress_bar_value / maximum())) << "%" << settings()->percentage_end << std::flush;

    }
};

} // ns: haevn::terminal::widgets