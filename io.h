#ifndef IO_HEADER
#define IO_HEADER

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <random>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <ctime>
#include <cstdarg>

/*
 * ===============================================================
 *
 *                          INTERFACE
 *
 * ===============================================================
 */

// MACROS
#define IO(T) \
int main(int argc, char** argv) try\
{\
    io::init();\
    auto game = std::make_unique<T>();\
    game->run();\
}\
catch(const std::exception& e)\
{\
    al_show_native_message_box(al_get_current_display(), "Error", "Exception!", e.what(), 0, ALLEGRO_MESSAGEBOX_ERROR);\
}
#define IO_THROW(...) (io::throw_exception(__FILE__, __LINE__, __VA_ARGS__))
#define IO_CHECK(cond, msg) if (!cond) { IO_THROW(msg); }

#define IO_FLAG(x) (1 << (x))
// http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/

#define IO_STRINGIFY(x) #x
#define IO_TOSTRING(x) IO_STRINGIFY(x)
#define IO_FILE_LINE __FILE__ ":" IO_TOSTRING(__LINE__)

namespace io
{

/*
 * ===============================================================
 *
 *                          MATH
 *
 * ===============================================================
 */

template <class Derived, typename T, int N>
class VectorBase;

template <class Derived, typename T>
class VectorBase<Derived, T, 2>
{
protected:
    T values[2];
    VectorBase(T v0, T v1) : values{v0, v1} {}
    
    bool operator==(const Derived& v) const 
    {
        return values[0] == v.values[0] && values[1] == v.values[1];
    }
    
    bool operator!=(const Derived& v) const 
    {
        return !(operator==(v));
    }
    
    bool is_equal(const Derived& v, T epsilon = 0.001) const 
    {
        return (std::abs(values[0] - v.values[0]) < epsilon) && (std::abs(values[1] - v.values[1]) < epsilon);
    }
    
    friend Derived operator+(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] + v2.values[0], v1.values[1] + v2.values[1]};
    }

    Derived& operator+=(const Derived& v)
    {
        values[0] += v.values[0];
        values[1] += v.values[1];
        return static_cast<Derived&>(*this);
    }
    
    friend Derived operator-(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] - v2.values[0], v1.values[1] - v2.values[1]};
    }

    Derived operator-() const
    {
        return Derived{-values[0], -values[1]};
    }

    Derived& operator-=(const Derived& v)
    {
        values[0] -= v.values[0];
        values[1] -= v.values[1];
        return static_cast<Derived&>(*this);
    }

    Derived operator*(T f) const
    {
        return Derived{values[0] * f, values[1] * f};
    }

    Derived& operator*=(T f)
    {
        values[0] *= f;
        values[1] *= f;
        return static_cast<Derived&>(*this);
    }

    Derived operator/(T f) const
    {
        return Derived{values[0] / f, values[1] / f};
    }

    Derived& operator/=(T f)
    {
        values[0] /= f;
        values[1] /= f;
        return static_cast<Derived&>(*this);
    }
};

template <typename T>
class Vector : public VectorBase<Vector<T>, T, 2>
{
    using Base = VectorBase<Vector<T>, T, 2>;
    
public:
    T& x;
    T& y;
    
    Vector(T x = T(), T y = T()) : Base(x, y), x(Base::values[0]), y(Base::values[1]) {}
    Vector& operator=(const Vector& v) { x = v.x; y = v.y; return *this; }
    
    using Base::operator==;
    using Base::operator!=;
    using Base::is_equal;
    using Base::operator+=;
    using Base::operator-;
    using Base::operator-=;
    using Base::operator*;
    using Base::operator*=;
    using Base::operator/;
    using Base::operator/=;
    
    T dot_product(const Vector& v) const
    {
        return x * v.x + y * v.y;
    }
    
    T cross_product(const Vector& v) const
    {
        return x * v.y - y * v.x;
    }
    
    T length() const
    {
        return std::sqrt(x * x + y * y);
    }
    
    T length_squared() const
    {
        return x * x + y * y;
    }
    
    void normalize()
    {
        T l = length();
        if (l) {
            x /= l;
            y /= l;
        }
    }

    Vector normalized() const
    {
        T l = length();
        return l ? Vector{x / l, y / l} : Vector();
    }

    Vector polar(T angle, T length) const
    {
        return Vector{length * std::cos(angle), length * std::sin(angle)};
    }

    T magnitude() const
    {
        return length();
    }

    T direction() const
    {
        return std::atan2(y, x);
    }

    T angle() const
    {
        return direction();
    }

    T distance_to(const Vector& v)
    {
        T dx = v.x - x;
        T dy = v.y - y;
        return std::sqrt(dx * dx + dy * dy);
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << "(" << x << "," << y << ")";
        return ss.str();
    }
};

using Vector2i = Vector<int>;
using Vector2f = Vector<float>;
 
template <typename T>
class Size : public VectorBase<Vector<T>, T, 2>
{
    using Base = VectorBase<Vector<T>, T, 2>;
    
public:
    T& w;
    T& h;
    
    Size(T w = T(), T h = T()) : Base(w, h), w(Base::values[0]), h(Base::values[1]) {}
    Size& operator=(const Size& s) { w = s.w; h = s.h; return *this; }
    
    using Base::operator==;
    using Base::operator!=;
    using Base::operator+=;
    using Base::operator-;
    using Base::operator-=;
    using Base::operator*;
    using Base::operator*=;
    using Base::operator/;
    using Base::operator/=;
};

using Size2i = Size<int>;
using Size2f = Size<float>;

template <typename T>
class Region
{
public:
    Vector<T> pos;
    Size<T> size;
    
    Region(T x, T y, T w, T h) : pos(x, y), size(w, h) {}
    Region(Vector<T> pos, Size<T> size) : pos(pos), size(size) {}

    T x() const { return pos.x; }
    T y() const { return pos.y; }
    T w() const { return size.w; }
    T h() const { return size.h; }
    T left() const { return x(); }
    T right() const { return x() + w(); }
    T top() const { return y(); }
    T bottom() const { return y() + h(); }
    Vector<T> top_left() const { return Vector<T>(left(), top()); }
    Vector<T> top_right() const { return Vector<T>(right(), top()); }
    Vector<T> bottom_left() const { return Vector<T>(left(), bottom()); }
    Vector<T> bottom_right() const { return Vector<T>(right(), bottom()); }
    T center_x() const { return x() + w() / 2; }
    T center_y() const { return y() + h() / 2; }
    Vector<T> center() const { return Vector<T>(center_x(), center_y()); }
    
    bool contains(T x, T y) const
    {
        return !(x < left() || x > right() || y < top() || y > bottom());
    }
    
    bool contains(const Vector<T>& v) const
    {
        return contains(v.x, v.y);
    }
    
    bool contains(const Region<T>& r) const
    {
        return contains(r.left(), r.top()) && contains(r.right(), r.bottom());
    }
    
    bool intersects(T x0, T y0, T x1, T y1) const
    {
        return !(x0 > right() || x1 < left() || y0 > bottom() || y1 < top());
    }
    
    bool intersects(const Region<T>& r) const
    {
        return intersects(r.left(), r.top(), r.right(), r.bottom());
    }
    
    bool intersects(const Vector<T>& v, T radius) const
    {
        return false;
    }
    
    std::string to_string() const
    {
        std::stringstream ss;
        ss << "((" << left() << "," + top() << "),(" << right() << "," << bottom() << "))";
        return ss.str();
    }
};

using Region2f = Region<float>;
using Region2i = Region<int>;

class Random
{
public:
    Random(unsigned int seed = (unsigned int)time(0));
    int get_next_int(int min, int max);
    float get_next_float(float min, float max);
    bool one_in(int chance);
    int roll_dice(int number, int sides);

private:
    std::mt19937 rng;
};
 
void init();
void throw_exception(const char *file, int line, const char *format, ...);

class Input;

class Game
{
public:
    Game(std::string title, Size2i window_size, bool fullscreen);
    virtual ~Game();
    void run();
    void quit() { done = true; }
    virtual void update(const Input& input) = 0;
    virtual void render() = 0;
    Size2i get_window_size() const { return window_size; }
private:
    bool done = false;
    bool paused = false;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* display;
    Size2i window_size;
};

class Input
{
public:
    bool is_key_down(int key) const { return keyboard.keys[key].down; }
    bool is_key_pressed(int key) const { return keyboard.keys[key].pressed; }
    bool is_key_released(int key) const { return keyboard.keys[key].released; }
    
    bool is_mouse_button_down(int button) const { return mouse.buttons[button].down; }
    bool is_mouse_button_pressed(int button) const { return mouse.buttons[button].pressed; }
    bool is_mouse_button_released(int button) const { return mouse.buttons[button].released; }
    int get_mouse_x() const { return mouse.x; }
    int get_mouse_y() const { return mouse.y; }
    
    static int wait_for_keypress();
    static void wait_for_any();
    
private:
    struct Pressable
    {
        bool down = false;
        bool pressed = false;
        bool released = false;
    };
    
    struct Keyboard
    {
        std::array<Pressable, ALLEGRO_KEY_MAX> keys;
    } keyboard;
    
    struct Mouse
    {
        std::array<Pressable, 10> buttons;
        int x, y, z;
        int old_x, old_y, old_z;
    } mouse;
    
    friend class Game;
};

}



/*
 * ==============================================================
 *
 *                        IMPLEMENTATION
 *
 * ===============================================================
 */

#ifdef IO_IMPLEMENTATION

namespace io
{

void init()
{
    IO_CHECK(al_init(), "Failed to initialize allegro");
    IO_CHECK(al_install_keyboard(), "Failed to install keyboard");
    IO_CHECK(al_install_mouse(), "Failed to install mouse");
    
    ALLEGRO_PATH* resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
    al_destroy_path(resource_path);
    
    IO_CHECK(al_init_primitives_addon(), "Failed to initialize primitives addon");
    IO_CHECK(al_init_image_addon(), "Failed to initialize image addon");
    IO_CHECK(al_init_font_addon(), "Failed to initialize font addon");
    IO_CHECK(al_init_ttf_addon(), "Failed to initialize ttf addon");
    IO_CHECK(al_install_audio(), "Failed to install audio addon");
    IO_CHECK(al_init_acodec_addon(), "Failed to initialize acodec addon");
    IO_CHECK(al_reserve_samples(32), "Failed to reserve samples");
}

void throw_exception(const char *file, int line, const char *format, ...)
{
    char buffer[4096];
    va_list ap;
    va_start(ap, format);
    vsprintf_s(buffer, format, ap);
    va_end(ap);
    std::stringstream ss;
    ss << buffer << " (" << file << ":" << line << ")";
    throw std::runtime_error(ss.str());
}

Game::Game(std::string title, Size2i window_size, bool fullscreen)
{
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);
    fullscreen ? al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW) : al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(window_size.w, window_size.h);
    al_set_window_title(display, title.c_str());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    this->window_size = window_size;
}
    
Game::~Game()
{
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}
    
void Game::run()
{
    bool redraw = true;
    al_start_timer(timer);
    Input input;
    
    while (!done)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        
        switch (event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                redraw = true;
                if (!paused)
                {
                    update(input);
                }
                
                // clear input state
                for (auto& key : input.keyboard.keys)
                {
                    key.pressed = false;
                    key.released = false;
                }
                for (auto& button : input.mouse.buttons)
                {
                    button.pressed = false;
                    button.released = false;
                }
                input.mouse.old_x = input.mouse.x;
                input.mouse.old_y = input.mouse.y;
                input.mouse.old_z = input.mouse.z;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                input.keyboard.keys[event.keyboard.keycode].down = true;
                input.keyboard.keys[event.keyboard.keycode].pressed = true;
                break;

            case ALLEGRO_EVENT_KEY_UP:
                input.keyboard.keys[event.keyboard.keycode].down = false;
                input.keyboard.keys[event.keyboard.keycode].released = true;
                break;

            case ALLEGRO_EVENT_KEY_CHAR:
                if ((event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT) && event.keyboard.keycode == ALLEGRO_KEY_ENTER)
                {
                    al_set_display_flag(display, ALLEGRO_FULLSCREEN_WINDOW, !(al_get_display_flags(display) & ALLEGRO_FULLSCREEN_WINDOW));
                }
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                input.mouse.x = event.mouse.x;
                input.mouse.y = event.mouse.y;
                input.mouse.z = event.mouse.z;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                input.mouse.buttons[event.mouse.button - 1].down = true;
                input.mouse.buttons[event.mouse.button - 1].pressed = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                input.mouse.buttons[event.mouse.button - 1].down = false;
                input.mouse.buttons[event.mouse.button - 1].released = true;
                break;
                
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
                paused = true;
                break;

            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
                paused = false;
                break;
        }

        if (redraw && al_is_event_queue_empty(queue))
        {
            redraw = false;
            al_set_target_bitmap(al_get_backbuffer(display));
            al_clear_to_color(al_map_rgb(0, 0, 0));
            render();
            al_flip_display();
        }
    }
}

int Input::wait_for_keypress()
{
    auto queue = std::shared_ptr<ALLEGRO_EVENT_QUEUE>(al_create_event_queue(), al_destroy_event_queue);
    al_register_event_source(queue.get(), al_get_keyboard_event_source());
    ALLEGRO_EVENT event;
    do {
        al_wait_for_event(queue.get(), &event);
    } while (event.type != ALLEGRO_EVENT_KEY_DOWN);
    return event.keyboard.keycode;
}

void Input::wait_for_any()
{
    auto queue = std::shared_ptr<ALLEGRO_EVENT_QUEUE>(al_create_event_queue(), al_destroy_event_queue);
    al_register_event_source(queue.get(), al_get_keyboard_event_source());
    ALLEGRO_EVENT event;
    do {
        al_wait_for_event(queue.get(), &event);
    } while (event.type != ALLEGRO_EVENT_KEY_DOWN || event.type != ALLEGRO_EVENT_MOUSE_BUTTON_DOWN);
}

Random::Random(unsigned int seed)
{
    rng.seed(seed);
}

int Random::get_next_int(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

float Random::get_next_float(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

bool Random::one_in(int chance)
{
    if (get_next_int(0, chance - 1) == 0)
        return true;
    return false;
}

int Random::roll_dice(int number, int sides)
{
    int result = 0;
    for (int i = 0; i < number; i++)
        result += get_next_int(1, sides);
    return result;
}

}

#endif // IO_IMPLEMENTATION

#endif // IO_HEADER