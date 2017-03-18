// io v0.1 - c++ rapid game prototyping framework using Allegro 5
// Copyright 2017 Pär Arvidsson. All rights reserved.
// Licensed under the MIT license (https://github.com/arvidsson/io/blob/master/LICENSE).

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
#include <unordered_map>
#include <string>
#include <sstream>
#include <memory>
#include <cmath>
#include <ctime>
#include <cstdarg>

namespace io
{

#define io() io::GameServices::instance()
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

void init();
void throw_exception(const char *file, int line, const char *format, ...);

template <typename T>
class Math
{
public:
    static const T almost_zero;
    static const T pi;
    static const T two_pi;
    static const T pi_over_two;
    static const T pi_over_four;
    static const T deg_to_rad;
    static const T rad_to_deg;
    static const T e;

    static T to_radians(const T degrees)
    {
        return degrees * deg_to_rad;
    }

    static T to_degrees(const T radians)
    {
        return radians * rad_to_deg;
    }

    static T round(const T value)
    {
        return value > 0.0 ? std::floor(value + static_cast<T>(0.5)) : std::ceil(value - static_cast<T>(0.5));
    }

    static bool is_zero(const T value, const T epsilon = almost_zero)
    {
        return std::abs(value) <= epsilon;
    }

    static bool is_positive(const T value, const T epsilon = almost_zero)
    {
        return value > epsilon;
    }

    static bool is_negative(const T value, const T epsilon = almost_zero)
    {
        return value < -epsilon;
    }

    static bool is_equal(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return std::abs(x1 - x2) < epsilon;
    }

    static bool is_greater_than(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return x1 > (x2 + epsilon);
    }

    static bool is_less_than(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return x1 < (x2 - epsilon);
    }

    static bool is_greater_than_or_equal(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return !is_less_than(x1, x2, epsilon);
    }

    static bool is_less_than_or_equal(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return !is_greater_than(x1, x2, epsilon);
    }
};

template <typename T> const T Math<T>::almost_zero = static_cast<T>(0.001);
template <typename T> const T Math<T>::pi = static_cast<T>(3.141592653589793);
template <typename T> const T Math<T>::two_pi = static_cast<T>(2.0) * pi;
template <typename T> const T Math<T>::pi_over_two = pi / static_cast<T>(2.0);
template <typename T> const T Math<T>::pi_over_four = pi / static_cast<T>(4.0);
template <typename T> const T Math<T>::deg_to_rad = pi / static_cast<T>(180.0);
template <typename T> const T Math<T>::rad_to_deg = static_cast<T>(180.0) / pi;
template <typename T> const T Math<T>::e = static_cast<T>(2.718281828459045);

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
        return Math<T>::is_equal(values[0], v.values[0], epsilon) && Math<T>::is_equal(values[1], v.values[1], epsilon);
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

template <class Derived, typename T>
class VectorBase<Derived, T, 3>
{
protected:
    T values[3];
    VectorBase(T v0, T v1, T v2) : values{v0, v1, v2} {}
    
    bool operator==(const Derived& v) const 
    {
        return values[0] == v.values[0] && values[1] == v.values[1] && values[2] == v.values[2];
    }
    
    bool operator!=(const Derived& v) const 
    {
        return !(operator==(v));
    }
    
    bool is_equal(const Derived& v, T epsilon = 0.001) const 
    {
        return Math<T>::is_equal(values[0], v.values[0], epsilon) && Math<T>::is_equal(values[1], v.values[1], epsilon && Math<T>::is_equal(values[2], v.values[2], epsilon));
    }
    
    friend Derived operator+(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] + v2.values[0], v1.values[1] + v2.values[1], v1.values[2] + v2.values[2]};
    }

    Derived& operator+=(const Derived& v)
    {
        values[0] += v.values[0];
        values[1] += v.values[1];
        values[2] += v.values[2];
        return static_cast<Derived&>(*this);
    }
    
    friend Derived operator-(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] - v2.values[0], v1.values[1] - v2.values[1], v1.values[2] - v2.values[2]};
    }

    Derived operator-() const
    {
        return Derived{-values[0], -values[1], -values[2]};
    }

    Derived& operator-=(const Derived& v)
    {
        values[0] -= v.values[0];
        values[1] -= v.values[1];
        values[2] -= v.values[2];
        return static_cast<Derived&>(*this);
    }

    Derived operator*(T f) const
    {
        return Derived{values[0] * f, values[1] * f, values[2] * f};
    }

    Derived& operator*=(T f)
    {
        values[0] *= f;
        values[1] *= f;
        values[2] *= f;
        return static_cast<Derived&>(*this);
    }

    Derived operator/(T f) const
    {
        return Derived{values[0] / f, values[1] / f, values[2] / f};
    }

    Derived& operator/=(T f)
    {
        values[0] /= f;
        values[1] /= f;
        values[2] /= f;
        return static_cast<Derived&>(*this);
    }
};

template <class Derived, typename T>
class VectorBase<Derived, T, 4>
{
protected:
    T values[4];
    VectorBase(T v0, T v1, T v2, T v3) : values{v0, v1, v2, v3} {}
    
    bool operator==(const Derived& v) const 
    {
        return values[0] == v.values[0] && values[1] == v.values[1] && values[2] == v.values[2] && values[3] == v.values[3];
    }
    
    bool operator!=(const Derived& v) const 
    {
        return !(operator==(v));
    }
    
    bool is_equal(const Derived& v, T epsilon = 0.001) const 
    {
        return Math<T>::is_equal(values[0], v.values[0], epsilon) && Math<T>::is_equal(values[1], v.values[1], epsilon && Math<T>::is_equal(values[2], v.values[2], epsilon) && Math<T>::is_equal(values[3], v.values[3], epsilon));
    }
    
    friend Derived operator+(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] + v2.values[0], v1.values[1] + v2.values[1], v1.values[2] + v2.values[2], v1.values[3] + v2.values[3]};
    }

    Derived& operator+=(const Derived& v)
    {
        values[0] += v.values[0];
        values[1] += v.values[1];
        values[2] += v.values[2];
        values[3] += v.values[3];
        return static_cast<Derived&>(*this);
    }
    
    friend Derived operator-(const Derived& v1, const Derived& v2)
    {
        return Derived{v1.values[0] - v2.values[0], v1.values[1] - v2.values[1], v1.values[2] - v2.values[2], v1.values[3] - v2.values[3]};
    }

    Derived operator-() const
    {
        return Derived{-values[0], -values[1], -values[2], -values[3]};
    }

    Derived& operator-=(const Derived& v)
    {
        values[0] -= v.values[0];
        values[1] -= v.values[1];
        values[2] -= v.values[2];
        values[3] -= v.values[3];
        return static_cast<Derived&>(*this);
    }

    Derived operator*(T f) const
    {
        return Derived{values[0] * f, values[1] * f, values[2] * f, values[3] * f};
    }

    Derived& operator*=(T f)
    {
        values[0] *= f;
        values[1] *= f;
        values[2] *= f;
        values[3] *= f;
        return static_cast<Derived&>(*this);
    }

    Derived operator/(T f) const
    {
        return Derived{values[0] / f, values[1] / f, values[2] / f, values[3] / f};
    }

    Derived& operator/=(T f)
    {
        values[0] /= f;
        values[1] /= f;
        values[2] /= f;
        values[3] /= f;
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
class Size : public VectorBase<Size<T>, T, 2>
{
    using Base = VectorBase<Size<T>, T, 2>;
    
public:
    T& w;
    T& h;
    
    Size(T w = T(), T h = T()) : Base(w, h), w(Base::values[0]), h(Base::values[1]) {}
    Size& operator=(const Size& s) { w = s.w; h = s.h; return *this; }
    
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
    
    std::string to_string() const
    {
        std::stringstream ss;
        ss << "(" << w << "x" << h << ")";
        return ss.str();
    }
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

class Transform
{
public:
    Transform();
    Transform(const ALLEGRO_TRANSFORM &transform);
    Transform& operator=(const ALLEGRO_TRANSFORM &transform);
    ALLEGRO_TRANSFORM to_allegro_transform() const;
    void identity();
    void use();
    void translate(Vector2f position);
    void scale(Vector2f factor);
    void rotate(float angle);
private:
    ALLEGRO_TRANSFORM t;
};

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

using Bitmap = std::shared_ptr<ALLEGRO_BITMAP>;
using Font = std::shared_ptr<ALLEGRO_FONT>;
using Sound = std::shared_ptr<ALLEGRO_SAMPLE>;
using Music = std::shared_ptr<ALLEGRO_AUDIO_STREAM>;

Bitmap make_bitmap(int width, int height);
Bitmap load_bitmap(std::string filename);
Bitmap cut_bitmap(Bitmap parent, Vector2i pos, Size2i size);
Font load_font(std::string filename, int size);
Sound load_sound(std::string filename);
Music load_music(std::string filename);

class Resources
{
public:
    Bitmap get_bitmap(std::string filename);
    std::vector<Bitmap> get_sub_bitmaps(std::string filename, int width, int height);
    Font get_font(std::string filename, int size);
    Sound get_sound(std::string filename);
    Music get_music(std::string filename);
private:
    std::unordered_map<std::string, Bitmap> bitmaps;
    std::unordered_map<std::string, std::vector<Bitmap>> sub_bitmaps;
    std::unordered_map<std::string, Font> fonts;
    std::unordered_map<std::string, Sound> sounds;
    std::unordered_map<std::string, Music> music;
};

class Color : public VectorBase<Color, float, 4>
{
    using Base = VectorBase<Color, float, 4>;
    
public:
    float& r;
    float& g;
    float& b;
    float& a;
    
    Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f) : Base(r, g, b, a), r(Base::values[0]), g(Base::values[1]), b(Base::values[2]), a(Base::values[3]) {}
    Color(int r, int g, int b, int a) : Base(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f), r(Base::values[0]), g(Base::values[1]), b(Base::values[2]), a(Base::values[3]) {}
    Color& operator=(const Color& c) { r = c.r; g = c.g; b = c.b; a = c.a; return *this; }
    Color(const ALLEGRO_COLOR& color) : Color() { operator=(color); }
    Color& operator=(const ALLEGRO_COLOR& color) { al_unmap_rgba_f(color, &r, &g, &b, &a); return *this; }
    
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
    
    ALLEGRO_COLOR to_allegro_color() const
    {
        return al_map_rgba_f(r, g, b, a);
    }
    
    std::string to_string() const
    {
        std::stringstream ss;
        ss << "(" << r << "," << g << "," << b << "," << a << ")";
        return ss.str();
    }
};

class Camera2D
{
public:
    void use() { get_transform().use(); }
    void reset() { Transform t; t.use(); }
    void move_to(Vector2f new_pos) { pos = new_pos; }
    void move_by(Vector2f scroll) { pos -= scroll; }
    void zoom_to(float z) { this->z = z; }
    void zoom_by(float z) { this->z += z; }
    void rotate_to(float r) { this->r = r; }
    void rotate_by(float r) { this->r += r; }
    float x() const { return pos.x; }
    float y() const { return pos.y; }
    float zoom() const { return z; }
    float rotation() const { return r; }
    Vector2f to_screen(Vector2f coords) const;
    Vector2f to_world(Vector2f coords) const;
private:
    Transform get_transform() const;
    Vector2f pos;
    float z = 1.0;
    float r = 0.0f;
};

class Game
{
public:
    Game(std::string title, Size2i window_size, bool fullscreen);
    virtual ~Game();
    void run();
    void quit() { done = true; }
    virtual void update() = 0;
    virtual void render() = 0;
private:
    bool done = false;
    bool paused = false;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
    ALLEGRO_DISPLAY* display;
};

class GameServices
{
public:
    static GameServices& instance() { static GameServices gs; return gs; }
    Size2i window_size;
    Input input;
    Random random;
};

} // namespace io

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

Transform::Transform()
{
    identity();
}

Transform::Transform(const ALLEGRO_TRANSFORM &transform)
{
    al_copy_transform(&t, &transform);
}

Transform& Transform::operator=(const ALLEGRO_TRANSFORM &transform)
{
    al_copy_transform(&t, &transform);
    return *this;
}

ALLEGRO_TRANSFORM Transform::to_allegro_transform() const
{
    return t;
}

void Transform::identity()
{
    al_identity_transform(&t);
}

void Transform::use()
{
    al_use_transform(&t);
}

void Transform::translate(Vector2f position)
{
    al_translate_transform(&t, position.x, position.y);
}

void Transform::scale(Vector2f factor)
{
    al_scale_transform(&t, factor.x, factor.y);
}

void Transform::rotate(float angle)
{
    al_rotate_transform(&t, angle);
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

Bitmap make_bitmap(int width, int height)
{
    return Bitmap(al_create_bitmap(width, height), al_destroy_bitmap);
}
    
Bitmap load_bitmap(std::string filename)
{
    return Bitmap(al_load_bitmap(filename.c_str()), al_destroy_bitmap);   
}

Bitmap cut_bitmap(Bitmap parent, Vector2i pos, Size2i size)
{
    return Bitmap(al_create_sub_bitmap(parent.get(), pos.x, pos.y, size.w, size.h), al_destroy_bitmap);
}

Font load_font(std::string filename, int size)
{
    return Font(al_load_font(filename.c_str(), size, 0), al_destroy_font);   
}

Sound load_sound(std::string filename)
{
    return Sound(al_load_sample(filename.c_str()), al_destroy_sample);   
}

Music load_music(std::string filename)
{
    return Music(al_load_audio_stream(filename.c_str(), 4, 2048), al_destroy_audio_stream);   
}

Bitmap Resources::get_bitmap(std::string filename)
{
    if (bitmaps.find(filename) != bitmaps.end())
    {
        return bitmaps[filename];
    }

    Bitmap bitmap = load_bitmap(filename);
    if (!bitmap)
    {
        IO_THROW("Failed to load bitmap: %s", filename.c_str());
    }

    bitmaps[filename] = bitmap;
    return bitmap;
}

std::vector<Bitmap> Resources::get_sub_bitmaps(std::string filename, int width, int height)
{
    if (sub_bitmaps.find(filename) != sub_bitmaps.end()) {
        return sub_bitmaps[filename];
    }

    Bitmap bitmap = get_bitmap(filename);
    std::vector<Bitmap> sub_bmps;

    int cols = al_get_bitmap_width(bitmap.get()) / width;
    int rows = al_get_bitmap_height(bitmap.get()) / height;

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            Bitmap sub_bitmap = cut_bitmap(bitmap, { i * width, j * height }, { width, height });
            if (!sub_bitmap)
            {
                IO_THROW("Failed to create sub-bitmaps for: %s", filename.c_str());
            }
            sub_bmps.push_back(sub_bitmap);
        }
    }

    sub_bitmaps[filename] = sub_bmps;
    return sub_bmps;
}

Font Resources::get_font(std::string filename, int size)
{
    std::string font_name = filename + std::to_string(size);
    if (fonts.find(font_name) != fonts.end())
    {
        return fonts[font_name];
    }

    Font font = load_font(filename, size);
    if (!font)
    {
        IO_THROW("Failed to load font: %s (%d)", filename.c_str(), size);
    }

    fonts[font_name] = font;
    return font;
}

Sound Resources::get_sound(std::string filename)
{
    if (sounds.find(filename) != sounds.end())
    {
        return sounds[filename];
    }

    Sound sound = load_sound(filename);
    if (!sound)
    {
        IO_THROW("Failed to load sound: %s", filename.c_str());
    }

    sounds[filename] = sound;
    return sound;
}

Music Resources::get_music(std::string filename)
{
    if (music.find(filename) != music.end())
    {
        return music[filename];
    }

    Music song = load_music(filename);
    if (!song)
    {
        IO_THROW("Failed to load music: %s", filename.c_str());
    }

    al_attach_audio_stream_to_mixer(song.get(), al_get_default_mixer());
    al_set_audio_stream_playing(song.get(), false);

    music[filename] = song;
    return song;
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
    io().window_size = window_size;
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
    auto& input = io().input;
    
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
                    update();
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

} // namespace io

#endif // IO_IMPLEMENTATION

#endif // IO_HEADER