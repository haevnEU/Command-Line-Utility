/**
 * @file This file contains various definition and utility functions.
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

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>
#include <iomanip>
#include <chrono>
#include <cstring>

#include <cstdint>

extern "C"
{
    #include <termios.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
    #include <sys/stat.h>
    #include <unistd.h>
}


#define getter
#define setter

#define attributes
#define methods


#define static_attributes
#define static_methods

namespace haevn::utils{


    /**
     * @brief This method waits until enter is pressed
     * @details This method prints a message that the user should press 
     *          enter to continue and waits until the user pressed the enter
     *          key. It will wait on the std::cin stream, to use another stream
     *          use the overloaded wait(std::istream&) method.
     */
    static void wait(){ 
        std::cout << "Press [RETURN] to continue ...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');        
 
    }

    /**
     * @brief This method waits until enter is pressed
     * @details This method prints a message that the user should press 
     *          enter to continue and waits until the user pressed the enter
     *          key.
     * @param in The stream on which the method should wait
     */
    static void wait(std::istream& in){
        std::cout << "Press [RETURN] to continue ...";
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');        
    }

    /**
     * @brief This methods gets the current date and time
     * @details This methods requests the current time from the OS and 
     *          converts it into a usable string representation
     * @return String representing the current date and time
     */
    static inline const char* dateTime(){
        auto end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        char* time = std::ctime(&end_time);
        // Cut the new line away
        if (time[strlen(time)-1] == '\n'){
            time[strlen(time)-1] = '\0'; 
        }

        return time;
    }


    class Getchar{
        public:

        char static getch(){
            static Getchar instance;
            return instance.getch_(0);
        }

        std::string static getch(int amount){
            static Getchar instance;
            std::string str;
            for(int i = 0; i < amount; i++){
                char c = instance.getch_(0);
                str.push_back(c);
            }
            return str;
        }

        private:

            struct termios old, current;

            Getchar(){}

            /**
             * @brief Initializes a new terminal settings
             * @param echo Enables/Disabled echo mode
             */
            void initTermios(int echo){
                tcgetattr(0, &old); /* grab old terminal i/o settings */
                current = old; /* make new settings same as old settings */
                current.c_lflag &= ~ICANON; /* disable buffered i/o */
                if (echo) {
                    current.c_lflag |= ECHO; /* set echo mode */
                } else {
                    current.c_lflag &= ~ECHO; /* set no echo mode */
                }
                tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
            }

            /**
             * @brief Resets the old terminal
             */
            void resetTermios(void){
                tcsetattr(0, TCSANOW, &old);
            }

            /**
             * @brief Read 1 char from terminal
             * @param echo Enables/Disables echo mode
             * @return char Character which was read
             */
            char getch_(int echo){
                char ch;
                initTermios(echo);
                ch = getchar();
                resetTermios();
                return ch;
            }
    };
}