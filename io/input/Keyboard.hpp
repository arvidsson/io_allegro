#pragma once

#include "Pressable.hpp"
#include <allegro5/allegro.h>
#include <vector>

namespace io
{

class Keyboard
{
public:
    /*
        Initializes keyboard input.
    */
    Keyboard();

    /*
        Keyboard key codes.
    */
    enum Key
    {
        A = ALLEGRO_KEY_A,
        B = ALLEGRO_KEY_B,
        C = ALLEGRO_KEY_C,
        D = ALLEGRO_KEY_D,
        E = ALLEGRO_KEY_E,
        F = ALLEGRO_KEY_F,
        G = ALLEGRO_KEY_G,
        H = ALLEGRO_KEY_H,
        I = ALLEGRO_KEY_I,
        J = ALLEGRO_KEY_J,
        K = ALLEGRO_KEY_K,
        L = ALLEGRO_KEY_L,
        M = ALLEGRO_KEY_M,
        N = ALLEGRO_KEY_N,
        O = ALLEGRO_KEY_O,
        P = ALLEGRO_KEY_P,
        Q = ALLEGRO_KEY_Q,
        R = ALLEGRO_KEY_R,
        S = ALLEGRO_KEY_S,
        T = ALLEGRO_KEY_T,
        U = ALLEGRO_KEY_U,
        V = ALLEGRO_KEY_V,
        W = ALLEGRO_KEY_W,
        X = ALLEGRO_KEY_X,
        Y = ALLEGRO_KEY_Y,
        Z = ALLEGRO_KEY_Z,
        Num0 = ALLEGRO_KEY_0,
        Num1 = ALLEGRO_KEY_1,
        Num2 = ALLEGRO_KEY_2,
        Num3 = ALLEGRO_KEY_3,
        Num4 = ALLEGRO_KEY_4,
        Num5 = ALLEGRO_KEY_5,
        Num6 = ALLEGRO_KEY_6,
        Num7 = ALLEGRO_KEY_7,
        Num8 = ALLEGRO_KEY_8,
        Num9 = ALLEGRO_KEY_9,
        NumPad0 = ALLEGRO_KEY_PAD_0,
        NumPad1 = ALLEGRO_KEY_PAD_1,
        NumPad2 = ALLEGRO_KEY_PAD_2,
        NumPad3 = ALLEGRO_KEY_PAD_3,
        NumPad4 = ALLEGRO_KEY_PAD_4,
        NumPad5 = ALLEGRO_KEY_PAD_5,
        NumPad6 = ALLEGRO_KEY_PAD_6,
        NumPad7 = ALLEGRO_KEY_PAD_7,
        NumPad8 = ALLEGRO_KEY_PAD_8,
        NumPad9 = ALLEGRO_KEY_PAD_9,
        F1 = ALLEGRO_KEY_F1,
        F2 = ALLEGRO_KEY_F2,
        F3 = ALLEGRO_KEY_F3,
        F4 = ALLEGRO_KEY_F4,
        F5 = ALLEGRO_KEY_F5,
        F6 = ALLEGRO_KEY_F6,
        F7 = ALLEGRO_KEY_F7,
        F8 = ALLEGRO_KEY_F8,
        F9 = ALLEGRO_KEY_F9,
        F10 = ALLEGRO_KEY_F10,
        F11 = ALLEGRO_KEY_F11,
        F12 = ALLEGRO_KEY_F12,
        Escape = ALLEGRO_KEY_ESCAPE,
        Backspace = ALLEGRO_KEY_BACKSPACE,
        Tab = ALLEGRO_KEY_TAB,
        Enter = ALLEGRO_KEY_ENTER,
        Space = ALLEGRO_KEY_SPACE,
        Insert = ALLEGRO_KEY_INSERT,
        Delete = ALLEGRO_KEY_DELETE,
        Home = ALLEGRO_KEY_HOME,
        End = ALLEGRO_KEY_END,
        PageUp = ALLEGRO_KEY_PGUP,
        PageDown = ALLEGRO_KEY_PGDN,
        Left = ALLEGRO_KEY_LEFT,
        Right = ALLEGRO_KEY_RIGHT,
        Up = ALLEGRO_KEY_UP,
        Down = ALLEGRO_KEY_DOWN,
        LeftShift = ALLEGRO_KEY_LSHIFT,
        RightShift = ALLEGRO_KEY_RSHIFT,
        LeftControl = ALLEGRO_KEY_LCTRL,
        RightControl = ALLEGRO_KEY_RCTRL,
        Alt = ALLEGRO_KEY_ALT,
        AltGr = ALLEGRO_KEY_ALTGR,
        ScrollLock = ALLEGRO_KEY_SCROLLLOCK,
        NumLock = ALLEGRO_KEY_NUMLOCK,
        CapsLock = ALLEGRO_KEY_CAPSLOCK,
        Max = ALLEGRO_KEY_MAX
    };
    
    /*
        Keyboard input getters.
    */
    bool IsKeyDown(int keycode) const;
    bool IsKeyPressed(int keycode) const;
    bool IsKeyReleased(int keycode) const;

    /*
        Waits until keypress, then returns which key was pressed.
    */
    int WaitForKeypress();

private:
    /*
        Clears keyboard input state, should be done each frame.
    */
    void Clear();

    /*
        Keyboard input setters.
    */
    void KeyWasPressed(int keycode);
    void KeyWasReleased(int keycode);
    
    std::vector<Pressable> keys;
    
    friend class Input;
};

}