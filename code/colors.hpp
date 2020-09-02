/**
 * @file This file contains various definition for colorization of the terminal,
 *        example: std::cout << colors::foreground::BLUE << "TEXT" << colors::RESET;
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

namespace haevn::terminal::colors{

#ifdef WIN
    /**
     * @brief Line ending.
     */
    const static char* endl = "\r\n";
#else
    /**
     * @brief Line ending.
     */
    const static char* endl = "\n";
#endif

    /**
     * @brief Resets the colorization
     */
    const static char* RESET     = "\x1B[0m";
    
    /**
     * @brief Clears the terminal
     */
    const static char* CLEAR = "\e[1;1H\e[2J";

}

namespace haevn::terminal::colors::foreground{
    
    /**
     * @brief Colors the foreground in black
     */
    const static char* BLACK     = "\x1B[30m";
    
    /**
     * @brief Colors the foreground in red
     */
    const static char* RED       = "\x1B[31m";
    
    /**
     * @brief Colors the foreground in green
     */
    const static char* GREEN     = "\x1B[32m";
    
    /**
     * @brief Colors the foreground in yellow
     */
    const static char* YELLOW    = "\x1B[33m";
    
    /**
     * @brief Colors the foreground in blue
     */
    const static char* BLUE      = "\x1B[34m";
    
    /**
     * @brief Colors the foreground in magenta
     */
    const static char* MAGENTA   = "\x1B[35m";
    
    /**
     * @brief Colors the foreground in cyan
     */
    const static char* CYAN      = "\x1B[36m";
    
    /**
     * @brief Colors the foreground in white
     */
    const static char* WHITE     = "\x1B[37m";
}

namespace haevn::terminal::colors::attributes{

    /**
     * @brief Enables bold font in foreground
     */
    const static char* BOLD      = "\x1B[1m";
    
    /**
     * @brief Enables underlined font in foreground
     */
    const static char* UNDERLINE = "\x1B[4m";
}

namespace haevn::terminal::colors::background{
    const static char* TRANSPARENT = "";

    /**
     * @brief Colors the ground black
     */
    const static char* BLACK     = "\x1B[40m";

    /**
     * @brief Colors the background red
     */
    const static char* RED       = "\x1B[41m";
    
    /**
     * @brief Colors the background green
     */
    const static char* GREEN     = "\x1B[42m";
    
    /**
     * @brief Colors the background yellow
     */
    const static char* YELLOW    = "\x1B[43m";
    
    /**
     * @brief Colors the background blue
     */
    const static char* BLUE      = "\x1B[44m";
    
    /**
     * @brief Colors the background magenta
     */
    const static char* MAGENTA   = "\x1B[45m";
    
    /**
     * @brief Colors the background cyan
     */
    const static char* CYAN      = "\x1B[46m";
    
    /**
     * @brief Colors the background white
     */
    const static char* WHITE     = "\x1B[47m";
}

namespace haevn::terminal::colors::icons{

    /**
     * @brief This is accpet icon without colorization
     */
    const static char* ICON_ACCEPT_RAW = "✓";// "\xE2\x9C\x93";
    
    /**
     * @brief This is denied/decline icon without colorization
     */
    const static char* ICON_DENIED_RAW = "✗";

    /**
     * @brief This is accpet icon with green colorization
     */
    const static char* ICON_ACCEPT = "\x1B[32m✓\x1B[0m";

    /**
     * @brief This is denied/decline icon with red colorization
     */
    const static char* ICON_DENIED = "\x1B[31m✗\x1B[0m";
}