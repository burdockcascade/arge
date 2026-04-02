#include "rl_bindings.hpp"
#include "../qjs/qjs_wrapper.hpp"

namespace RaylibBindings {

    void InitAllStructs(qjs::ObjectBinder &ns) {
        
        // Vector2 
        ns.register_class<Vector2>("Vector2")
            .constructor()
            .constructor<float, float>()
            .field("x", &Vector2::x)
            .field("y", &Vector2::y);

        // Vector3 
        ns.register_class<Vector3>("Vector3")
            .constructor()
            .constructor<float, float, float>()
            .field("x", &Vector3::x)
            .field("y", &Vector3::y)
            .field("z", &Vector3::z);

        // Vector4 
        ns.register_class<Vector4>("Vector4")
            .constructor()
            .constructor<float, float, float, float>()
            .field("x", &Vector4::x)
            .field("y", &Vector4::y)
            .field("z", &Vector4::z)
            .field("w", &Vector4::w);

        // Matrix 
        ns.register_class<Matrix>("Matrix")
            .constructor()
            .field("m0", &Matrix::m0)
            .field("m4", &Matrix::m4)
            .field("m8", &Matrix::m8)
            .field("m12", &Matrix::m12)
            .field("m1", &Matrix::m1)
            .field("m5", &Matrix::m5)
            .field("m9", &Matrix::m9)
            .field("m13", &Matrix::m13)
            .field("m2", &Matrix::m2)
            .field("m6", &Matrix::m6)
            .field("m10", &Matrix::m10)
            .field("m14", &Matrix::m14)
            .field("m3", &Matrix::m3)
            .field("m7", &Matrix::m7)
            .field("m11", &Matrix::m11)
            .field("m15", &Matrix::m15);

        // Color 
        ns.register_class<Color>("Color")
            .constructor()
            .constructor<uint8_t, uint8_t, uint8_t, uint8_t>()
            .field("r", &Color::r)
            .field("g", &Color::g)
            .field("b", &Color::b)
            .field("a", &Color::a)
            .static_constant("LIGHTGRAY", LIGHTGRAY)
            .static_constant("GRAY", GRAY)
            .static_constant("DARKGRAY", DARKGRAY)
            .static_constant("YELLOW", YELLOW)
            .static_constant("GOLD", GOLD)
            .static_constant("ORANGE", ORANGE)
            .static_constant("PINK", PINK)
            .static_constant("RED", RED)
            .static_constant("MAROON", MAROON)
            .static_constant("GREEN", GREEN)
            .static_constant("LIME", LIME)
            .static_constant("DARKGREEN", DARKGREEN)
            .static_constant("SKYBLUE", SKYBLUE)
            .static_constant("BLUE", BLUE)
            .static_constant("DARKBLUE", DARKBLUE)
            .static_constant("PURPLE", PURPLE)
            .static_constant("VIOLET", VIOLET)
            .static_constant("DARKPURPLE", DARKPURPLE)
            .static_constant("BEIGE", BEIGE)
            .static_constant("BROWN", BROWN)
            .static_constant("DARKBROWN", DARKBROWN)
            .static_constant("WHITE", WHITE)
            .static_constant("BLACK", BLACK)
            .static_constant("BLANK", BLANK)
            .static_constant("MAGENTA", MAGENTA)
            .static_constant("RAYWHITE", RAYWHITE);

        // Rectangle 
        ns.register_class<Rectangle>("Rectangle")
            .constructor()
            .constructor<float, float, float, float>()
            .field("x", &Rectangle::x)
            .field("y", &Rectangle::y)
            .field("width", &Rectangle::width)
            .field("height", &Rectangle::height);

        // Image 
        ns.register_class<Image>("Image")
            .constructor()
            .field("data", &Image::data)
            .field("width", &Image::width)
            .field("height", &Image::height)
            .field("mipmaps", &Image::mipmaps)
            .field("format", &Image::format);

        // Texture 
        ns.register_class<Texture>("Texture")
            .constructor()
            .field("id", &Texture::id)
            .field("width", &Texture::width)
            .field("height", &Texture::height)
            .field("mipmaps", &Texture::mipmaps)
            .field("format", &Texture::format);


    }

}