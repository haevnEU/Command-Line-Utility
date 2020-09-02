#pragma once

#include "utils.hpp"

namespace haevn::terminal{
    enum Keys{
        _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
        
        A_UP, B_UP, C_UP, D_UP, E_UP, F_UP, G_UP, H_UP, I_UP, J_UP,
        K_UP, L_UP, M_UP, N_UP, O_UP, P_UP, Q_UP, R_UP, S_UP, T_UP,
        U_UP, V_UP, W_UP, X_UP, Y_UP, Z_UP,
        
        A_DOWN, B_DOWN, C_DOWN, D_DOWN, E_DOWN, F_DOWN, G_DOWN, H_DOWN, I_DOWN, J_DOWN,
        K_DOWN, L_DOWN, M_DOWN, N_DOWN, O_DOWN, P_DOWN, Q_DOWN, R_DOWN, S_DOWN, T_DOWN,
        U_DOWN, V_DOWN, W_DOWN, X_DOWN, Y_DOWN, Z_DOWN,
        
        ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT,
        SPACE, ENTER, TAB,
        CONTROL, SHIFT, ALT, CAPS_LOCK
    };

    class Keyboard{
    public:
        static bool key_up(Keys key){
            return !key_pressed(key);
        }

        static bool key_pressed(Keys key){
            bool is_pressed = false;
            switch(key){
                case Keys::_0: return get_pressed_state(48);
                case Keys::_1: return get_pressed_state(49);
                case Keys::_2: return get_pressed_state(50);
                case Keys::_3: return get_pressed_state(51);
                case Keys::_4: return get_pressed_state(52);
                case Keys::_5: return get_pressed_state(53);
                case Keys::_6: return get_pressed_state(54);
                case Keys::_7: return get_pressed_state(55);
                case Keys::_8: return get_pressed_state(56);
                case Keys::_9: return get_pressed_state(57);      

                case Keys::A_UP: return get_pressed_state(65);
                case Keys::B_UP: return get_pressed_state(66);
                case Keys::C_UP: return get_pressed_state(67);
                case Keys::D_UP: return get_pressed_state(68);
                case Keys::E_UP: return get_pressed_state(69);
                case Keys::F_UP: return get_pressed_state(70);
                case Keys::G_UP: return get_pressed_state(71);
                case Keys::H_UP: return get_pressed_state(72);
                case Keys::I_UP: return get_pressed_state(73);
                case Keys::J_UP: return get_pressed_state(74);
                case Keys::K_UP: return get_pressed_state(75);
                case Keys::L_UP: return get_pressed_state(76);
                case Keys::M_UP: return get_pressed_state(77);
                case Keys::N_UP: return get_pressed_state(78);
                case Keys::O_UP: return get_pressed_state(79);
                case Keys::P_UP: return get_pressed_state(80);
                case Keys::Q_UP: return get_pressed_state(81);
                case Keys::R_UP: return get_pressed_state(82);
                case Keys::S_UP: return get_pressed_state(83);
                case Keys::T_UP: return get_pressed_state(84);
                case Keys::U_UP: return get_pressed_state(85);
                case Keys::V_UP: return get_pressed_state(86);
                case Keys::W_UP: return get_pressed_state(87);
                case Keys::X_UP: return get_pressed_state(88);
                case Keys::Y_UP: return get_pressed_state(89);
                case Keys::Z_UP: return get_pressed_state(90);

                case Keys::A_DOWN: return get_pressed_state(97);
                case Keys::B_DOWN: return get_pressed_state(98);
                case Keys::C_DOWN: return get_pressed_state(99);
                case Keys::D_DOWN: return get_pressed_state(100);
                case Keys::E_DOWN: return get_pressed_state(101);
                case Keys::F_DOWN: return get_pressed_state(102);
                case Keys::G_DOWN: return get_pressed_state(103);
                case Keys::H_DOWN: return get_pressed_state(104);
                case Keys::I_DOWN: return get_pressed_state(105);
                case Keys::J_DOWN: return get_pressed_state(106);
                case Keys::K_DOWN: return get_pressed_state(107);
                case Keys::L_DOWN: return get_pressed_state(108);
                case Keys::M_DOWN: return get_pressed_state(109);
                case Keys::N_DOWN: return get_pressed_state(110);
                case Keys::O_DOWN: return get_pressed_state(111);
                case Keys::P_DOWN: return get_pressed_state(112);
                case Keys::Q_DOWN: return get_pressed_state(113);
                case Keys::R_DOWN: return get_pressed_state(114);
                case Keys::S_DOWN: return get_pressed_state(115);
                case Keys::T_DOWN: return get_pressed_state(116);
                case Keys::U_DOWN: return get_pressed_state(117);
                case Keys::V_DOWN: return get_pressed_state(118);
                case Keys::W_DOWN: return get_pressed_state(119);
                case Keys::X_DOWN: return get_pressed_state(120);
                case Keys::Y_DOWN: return get_pressed_state(121);
                case Keys::Z_DOWN: return get_pressed_state(122);

                case Keys::ARROW_UP: return get_pressed_state(0);
                case Keys::ARROW_DOWN: return get_pressed_state(0);
                case Keys::ARROW_LEFT: return get_pressed_state(0);
                case Keys::ARROW_RIGHT: return get_pressed_state(0);

                case Keys::SPACE: return get_pressed_state(32);
                case Keys::ENTER: return get_pressed_state(10);
                case Keys::TAB: return get_pressed_state(9);

                case Keys::CONTROL: return get_pressed_state(0);
                case Keys::SHIFT: return get_pressed_state(0);
                case Keys::ALT: return get_pressed_state(0);
                case Keys::CAPS_LOCK: return get_pressed_state(0);
            } 
            return false;
        }
    private:
        static bool get_pressed_state(int key_code){

            char c = haevn::utils::Getchar::getch();

            return c == key_code;
        }
    };

}


