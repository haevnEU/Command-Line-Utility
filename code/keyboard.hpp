#pragma once

#include "utils.hpp"

namespace haevn::utils{

    enum arrow_keys{
        UP, 
        DOWN,
        LEFT,
        RIGHT,
        ARROW_NONE
    };

    enum keys{
        EXCLAMATION_MARK = 33,
        DOUBLE_QUOTE,
        POUND,
        DOLLAR,
        PERCENTAGE,
        AND,
        SINGLE_QUOTE,
        OPEN_PARENTHESES,
        CLOSE_PARENTHESES,
        STAR,
        ADD,
        LOWER_SINGLE_QUOTE,
        MINUS,
        DOT,
        SLASH,
        ZERO,
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        DOUBLE_POINT,
        SEMICOLON,
        SMALLER,
        EQUALS,
        QUESTION_MARK,
        AT,

        CAPITAL_A,
        CAPITAL_B,
        CAPITAL_C,
        CAPITAL_D,
        CAPITAL_E,
        CAPITAL_F,
        CAPITAL_G,
        CAPITAL_H,
        CAPITAL_I,
        CAPITAL_J,
        CAPITAL_K,
        CAPITAL_L,
        CAPITAL_M,
        CAPITAL_N,
        CAPITAL_O,
        CAPITAL_P,
        CAPITAL_Q,
        CAPITAL_R,
        CAPITAL_S,
        CAPITAL_T,
        CAPITAL_U,
        CAPITAL_V,
        CAPITAL_W,
        CAPITAL_X,
        CAPITAL_Y,
        CAPITAL_Z,
        
        OPEN_BRACKET,
        BACKSLASH,
        CLOSE_BRACKET,
        UNK1, // ^ 
        UNDERSCORE,
        UNK2, // `

        LOWER_A,
        LOWER_B,
        LOWER_C,
        LOWER_D,
        LOWER_E,
        LOWER_F,
        LOWER_G,
        LOWER_H,
        LOWER_I,
        LOWER_J,
        LOWER_K,
        LOWER_L,
        LOWER_M,
        LOWER_N,
        LOWER_O,
        LOWER_P,
        LOWER_Q,
        LOWER_R,
        LOWER_S,
        LOWER_T,
        LOWER_U,
        LOWER_V,
        LOWER_W,
        LOWER_X,
        LOWER_Y,
        LOWER_Z,
        
        OPEN_CURLY_BRACKET,
        DOUBLE_LINES,
        CLOSE_CURLY_BRACKET,
        TILDE,

        TAB = 9,
        SPACE = 32,
        BACK_SPACE = 127,
        ENTER = 10,
    
        ESC = 27,

        F1 = 255,     
        F2,     
        F3,     
        F4,   
        F5,   

        ARROW_UP,
        ARROW_DOWN,
        ARROW_RIGHT,
        ARROW_LEFT,

        F6,   
        F7,
        F8,     
        F9,   
        F10,    
        F11,       
        F12,   
        
        INS,   
        POS,    
        BILDUP,
        ENTF,  
        END,    
        BILDOWN,
        NUM,     

        NONE 
    };

    class Keyboard{
    private:
     
    public:
        static Keyboard& getInstance(){
            static Keyboard instance;
            return instance;
        }

        ~Keyboard(){}

        bool keyPressed(keys key){  
            bool result = false;
            
            return result;
        }

        bool keyReleased(keys key){
            return !keyPressed(key);
        }

    private:

        Keyboard(){}



    };
}


