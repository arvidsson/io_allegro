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
#define IO_BEGIN_MAIN int main(int argc, char** argv) try
#define IO_END_MAIN catch(const std::exception& e) { al_show_native_message_box(al_get_current_display(), "Error", "Exception!", e.what(), 0, ALLEGRO_MESSAGEBOX_ERROR); }
#define IO_THROW(...) (io::throw_exception(__FILE__, __LINE__, __VA_ARGS__))
#define IO_CHECK(cond, msg) if (!cond) { IO_THROW(msg); }

#define IO_FLAG(x) (1 << (x))
// http://www.learncpp.com/cpp-tutorial/3-8a-bit-flags-and-bit-masks/

#define IO_STRINGIFY(x) #x
#define IO_TOSTRING(x) IO_STRINGIFY(x)
#define IO_FILE_LINE __FILE__ ":" IO_TOSTRING(__LINE__)

namespace io
{

void init();
void throw_exception(const char *file, int line, const char *format, ...);

class Input;

class Game
{
public:
    Game(std::string title, int width, int height, bool fullscreen);
    virtual ~Game();
    void run();
    void quit();
    virtual void update(const Input& input) = 0;
    virtual void render() = 0;
    int get_width() const;
    int get_height() const;
private:
    bool done = false;
    bool paused = false;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* display;
    int width, height;
};

class Input
{
public:
    bool is_key_down(int key) const;
    bool is_key_pressed(int key) const;
    bool is_key_released(int key) const;
    
    bool is_mouse_button_down(int button) const;
    bool is_mouse_button_pressed(int button) const;
    bool is_mouse_button_released(int button) const;
    int get_mouse_x() const;
    int get_mouse_y() const;
    
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
    
    friend Game;
};

template <typename T>
class Vec2
{
public:
    T x, y;

    friend Vec2<T> operator+(const Vec2<T> &v1, const Vec2<T> &v2)
    {
        return Vec2<T>{v1.x + v2.x, v1.y + v2.y};
    }

    Vec2<T>& operator+=(const Vec2<T> &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    friend Vec2<T> operator-(const Vec2<T> &v1, const Vec2<T> &v2)
    {
        return Vec2<T>{v1.x - v2.x, v1.y - v2.y};
    }

    Vec2<T> operator-() const
    {
        return Vec2<T>{-x, -y};
    }

    Vec2<T>& operator-=(const Vec2<T> &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    Vec2<T> operator*(T f) const
    {
        return Vec2<T>{x * f, y * f};
    }

    Vec2<T>& operator*=(T f)
    {
        x *= f;
        y *= f;
        return *this;
    }

    Vec2<T> operator/(T f) const
    {
        return Vec2<T>{x / f, y / f};
    }

    Vec2<T>& operator/=(T f)
    {
        x /= f;
        y /= f;
        return *this;
    }
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

template <typename T>
class Rect
{
public:
    T x, y, w, h;

    T left() const { return x; }
    T right() const{ return x + width; }
    T top() const { return y; }
    T bottom() const { return y + height; }

    bool contains(T x, T y) const
    {
        return !(x < left() || x > right() || y < top() || y > bottom());
    }

    bool contains(const Vec2<T>& point) const
    {
        return contains(point.x, point.y);
    }

    bool contains(const Rect<T>& r) const
    {
        return contains(r.left(), r.top()) && contains(r.right(), r.bottom());
    }

    bool intersects(T l, T t, T r, T b) const
    {
        return !(l > right() || r < left() || t > bottom() || b < top());
    }

    bool intersects(const Rect<T>& r) const
    {
        return intersects(r.left(), r.top(), r.right(), r.bottom());
    }

    bool intersects(const Vec2<T>& point, T radius)
    {
        auto dist_x = std::abs(point.x - (x - w / 2));
        auto dist_y = std::abs(point.y - (y - h / 2));
        if (dist_x > (w / 2 + radius)) { return false; }
        if (dist_y > (h / 2 + radius)) { return false; }
        if (dist_x <= w / 2) { return true; }
        if (dist_y <= h / 2) { return true; }
        auto dx = dist_x - w / 2;
        auto dy = dist_y - h / 2;
        return (dx*dx + dy*dy <= (radius*radius));
    }
};

using Rectf = Rect<float>;
using Recti = Rect<int>;

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

Game::Game(std::string title, int width, int height, bool fullscreen)
{
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);
    fullscreen ? al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW) : al_set_new_display_flags(ALLEGRO_WINDOWED);
    display = al_create_display(width, height);
    al_set_window_title(display, title.c_str());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_display_event_source(display));
    this->width = width;
    this->height = height;
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

void Game::quit()
{
    done = true;
}

int Game::get_width() const
{
    return width;
}

int Game::get_height() const
{
    return height;
}

bool Input::is_key_down(int key) const
{
    return keyboard.keys[key].down;
}

bool Input::is_key_pressed(int key) const
{
    return keyboard.keys[key].pressed;
}

bool Input::is_key_released(int key) const
{
    return keyboard.keys[key].released;
}

bool Input::is_mouse_button_down(int button) const
{
    return mouse.buttons[button].down;
}

bool Input::is_mouse_button_pressed(int button) const
{
    return mouse.buttons[button].pressed;
}

bool Input::is_mouse_button_released(int button) const
{
    return mouse.buttons[button].released;
}

int Input::get_mouse_x() const
{
    return mouse.x;
}

int Input::get_mouse_y() const
{
    return mouse.y;
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