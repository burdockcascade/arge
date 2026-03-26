import json
import re
from jinja2 import Template

# This script processes the raylib.json file to generate C++ bindings for QuickJS.
# Some of these are not needed but we will keep them for future expansion.
TYPE_MAP = {
    "float": {"to": "JS_NewFloat64", "from": "JS_ToFloat64", "cast": "double"},
    "double": {"to": "JS_NewFloat64", "from": "JS_ToFloat64", "cast": "double"},
    "int": {"to": "JS_NewInt32", "from": "JS_ToInt32", "cast": "int32_t"},
    "unsigned char": {"to": "JS_NewInt32", "from": "JS_ToInt32", "cast": "int32_t"},
    "unsigned int": {"to": "JS_NewInt64", "from": "JS_ToInt64", "cast": "int64_t"},
    "bool": {"to": "JS_NewBool", "from": "JS_ToBool", "cast": "bool", "direct_return": True},
    "const char *": {"to": "JS_NewString", "from": "JS_ToCString", "cast": "const char *"},
    "char *": {"to": "JS_NewString", "from": "JS_ToCString", "cast": "char *"},
    "const void *": {"to": "JS_NULL", "from": None, "cast": "const void *"},
    "void *": {"to": "JS_NewInt64", "from": None, "cast": "void *"},
    "void": {"to": "JS_UNDEFINED", "from": None, "cast": "void"}
}

# We will only bind a subset of structs for simplicity. This can be expanded as needed.
STRUCT_WHITELIST = {
    "Vector2", "Vector3", "Vector4",
    "Matrix", "Color", "Rectangle", "Image", "Texture", "Texture2D",
}

# We will only bind a subset of functions for simplicity. This can be expanded as needed.
# Full binding is too complex for a first version, so we want to focus on the core window and drawing functions first.
FUNCTION_WHITELIST = {

    # Window related functions
    "IsWindowReady", "IsWindowFullscreen", "IsWindowHidden", "IsWindowMinimized", "IsWindowMaximized", "IsWindowResized", "IsWindowFocused",
    "IsWindowState", "SetWindowState", "ClearWindowState",
    "GetWindowWidth", "GetWindowHeight", "GetScreenWidth", "GetScreenHeight",
    "GetRenderWidth", "GetRenderHeight",

    # Monitor related functions
    "GetMonitorCount",
    "GetMonitorWidth", "GetMonitorHeight",
    "GetMonitorPhysicalWidth", "GetMonitorPhysicalHeight",
    "GetMonitorRefreshRate", "GetWindowPosition", "GetWindowScaleDPI",

    # Keyboard
    "IsKeyPressed", "IsKeyPressedRepeat", "IsKeyDown", "IsKeyReleased", "IsKeyUp", "GetKeyPressed", "SetExitKey",

    # Mouse
    "IsMouseButtonPressed", "IsMouseButtonDown", "IsMouseButtonReleased", "IsMouseButtonUp",
    "GetMouseX", "GetMouseY", "GetMousePosition", "SetMousePosition", "SetMouseOffset", "SetMouseScale",
    "GetMouseWheelMove", "GetMouseWheelMoveV",

    # Drawing related functions
    "DrawPixel", "DrawLine", "DrawCircle", "DrawRectangle", "DrawTexture", "DrawText", "DrawFPS",
    
    # Assets
    "LoadTexture", "UnloadTexture"
}

ENUM_WHITELIST = {
    "KeyboardKey", "MouseButton", "ShaderUniformDataV",
    "BlendMode", "GestureEvent", "CameraMode",
    "TextureParam", "TextureWrapMode", "TextureFilterMode"
}

def clean_type(t):
    return t.replace("const ", "").replace("*", "").strip()

def get_raylib_colors(data):
    """Extracts Color defines from raylib.json data."""
    colors = []
    # These are the standard colors defined in raylib.h
    target_colors = {
        "LIGHTGRAY", "GRAY", "DARKGRAY", "YELLOW", "GOLD", "ORANGE", "PINK",
        "RED", "MAROON", "GREEN", "LIME", "DARKGREEN", "SKYBLUE", "BLUE",
        "DARKBLUE", "PURPLE", "VIOLET", "DARKPURPLE", "BEIGE", "BROWN",
        "DARKBROWN", "WHITE", "BLACK", "BLANK", "MAGENTA", "RAYWHITE"
    }

    for define in data.get("defines", []):
        if define["name"] in target_colors:
            print(f"Processing color: {define['name']}")
            # Raylib defines colors like: (Color){ 200, 200, 200, 255 }
            # We need to extract the numbers from the 'value' string
            import re
            match = re.search(r'\{ *(\d+), *(\d+), *(\d+), *(\d+) *\}', define["value"])
            if match:
                colors.append({
                    "name": define["name"],
                    "r": match.group(1),
                    "g": match.group(2),
                    "b": match.group(3),
                    "a": match.group(4)
                })
    return colors

def process_bindings():
    with open('raylib.json', 'r') as f:
        data = json.load(f)

    known_structs = {s['name'] for s in data.get('structs', [])}
    processed_aliases = []

    all_items = [];

    # Process Alases
    print("Processing aliases...")
    for a in data.get('aliases', []):
        clean_alias_name = a['name'].replace('*', '').strip()
        print(f"Processing alias: {clean_alias_name}")

        all_items.append(clean_alias_name)

        if clean_alias_name not in STRUCT_WHITELIST:
            continue

        known_structs.add(clean_alias_name)
        processed_aliases.append({
            "name": clean_alias_name,
            "target": a['type'],
            "is_ptr": '*' in a['name']
        })

    # Process Structs (Existing logic)
    print("Processing structs...")
    processed_structs = []
    for s in data.get('structs', []):

        all_items.append(s['name'])

        if s['name'] not in STRUCT_WHITELIST:
            continue

        print(f"Processing struct: {s['name']}")

        struct_fields = []
        for f in s['fields']:
            f_type = f['type'].replace("const ", "").strip()
            is_ptr = '*' in f_type
            is_struct = clean_type(f_type) in known_structs

            mapping = TYPE_MAP.get(f_type if not is_struct else "int", TYPE_MAP["int"])

            struct_fields.append({
                "name": f['name'],
                "type": f_type,
                "is_struct": is_struct,
                "is_ptr": is_ptr,
                "cast": mapping["cast"],
                "to_js": mapping["to"],
                "from_js": mapping["from"],
                "direct_return": mapping.get("direct_return", False)
            })
        processed_structs.append({"name": s['name'], "fields": struct_fields})

    # Process Functions
    print("Processing functions...")
    processed_functions = []
    for func in data.get('functions', []):

        all_items.append(func['name'])

        if func['name'] not in FUNCTION_WHITELIST:
            continue

        print(f"Processing function: {func['name']}")

        params = []
        for i, p in enumerate(func.get('params', [])):
            p_type = p['type']
            clean_p = clean_type(p_type)
            is_struct = clean_p in known_structs
            is_ptr = '*' in p_type
            is_buffer = p_type == "const void *"

            # CHANGE: If it's a pointer to a struct, we don't want the 'int' mapping
            # We want to use the class_id logic in the template
            if is_struct and is_ptr:
                mapping = {"from": None, "cast": p_type} # Template will handle the rest
            else:
                mapping = TYPE_MAP.get(p_type if not is_struct else "int", TYPE_MAP["int"])

            params.append({
                "name": p['name'],
                "type": p_type,
                "clean_type": clean_p,
                "is_struct": is_struct,
                "is_const": "const" in p_type,
                "is_buffer": is_buffer,
                "is_ptr": is_ptr,
                "from_js": mapping.get("from"),
                "cast": mapping["cast"],
                "direct_return": mapping.get("direct_return", False),
                "index": i
            })

        ret_type = func['returnType']
        clean_ret = clean_type(ret_type)
        is_ret_struct = clean_ret in known_structs
        ret_mapping = TYPE_MAP.get(ret_type if not is_ret_struct else "int", TYPE_MAP.get("void"))

        processed_functions.append({
            "name": func['name'],
            "params": params,
            "return_type": ret_type,
            "clean_return_type": clean_ret,
            "is_ret_struct": is_ret_struct,
            "is_ret_void": ret_type == "void",
            "to_js": ret_mapping["to"],
            "cast": ret_mapping.get("cast", "double")
        })

    print("Processing enums...")
    processed_enums = []
    for e in data.get('enums', []):
        values = []
        for v in e.get('values', []):
            values.append({
                "name": v['name'],
                "value": v['value']
            })
            all_items.append(v['name'])
        processed_enums.append({
            "name": e['name'],
            "vals": values
        })

    # Render
    context = {
        "all": all_items,
        "structs": processed_structs,
        "aliases": processed_aliases,
        "functions": processed_functions,
        "enum_list": processed_enums,
        "color": get_raylib_colors(data)
    }

    # We will assume new templates 'functions.hpp.jinja2' and 'functions.cpp.jinja2' exist
    print("Rendering templates...")
    for file_base in ['rl_bindings', 'rl_module', 'rl_structs', 'rl_functions', 'rl_enums']:
        template_path = f'{file_base}.cppm.jinja2'
        print(f"Processing template: {template_path}")
        # Fallback to check if user updated existing templates or created new ones
        try:
            with open(template_path, 'r') as f:
                template = Template(f.read(), trim_blocks=True, lstrip_blocks=True)
            output_path = f'../../src/raylib/{file_base}.cppm'
            with open(output_path, 'w') as f:
                f.write(template.render(**context))
        except FileNotFoundError:
            print(f"Skipping {template_path}, file not found.")

if __name__ == "__main__":
    print("Processing bindings...")
    process_bindings()
    print("Done!")