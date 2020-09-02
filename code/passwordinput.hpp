/*
 * This file contains an implementation of a password input field
 * This file is licensed under the MIT license. If you decide to use this
 *  file a copy of the following license must be provided. Giving credit in
 *  form of a mention inside your source code, documentation or the final
 *  product would be nice but is not required.
 * 
 * Example
 * +-------------------------------------------------------------+
 * | haevn::terminal::widgets::PasswordInput password_input;     |
 * | std::string in = password_input.getPassword();              |
 * +-------------------------------------------------------------+
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

#include <iostream>
#include <string>

#include "utils.hpp"

namespace haevn::terminal::widgets{
    /**
     */
    class PasswordInput{
    public:
        PasswordInput(){}

        std::string getPassword(char fill_character = ' '){
            char c;
            std::string password;
            std::cout << "Enter your password: ";
            while((c = utils::Getchar::getch()) != 10){
                if(c == 127){
                    if(password.size() > 0){
                        std::cout << "\b";
                    password.pop_back();
                    }
                }else{
                    password.push_back(c);
                    std::cout << fill_character;
                }
            }
            std::cout << std::endl;
            return password;
        }
    };
}