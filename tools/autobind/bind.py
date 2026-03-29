import json
import re
import os
from jinja2 import Template

RAYLIB_GLOBAL_NAMESPACE = "_rl"

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

    # Init
    "InitWindow", "BeginDrawing", "EndDrawing", "CloseWindow", "WindowShouldClose", "SetTargetFPS", "GetFrameTime",

    # Window related functions
    "IsWindowReady", "IsWindowFullscreen", "IsWindowHidden", "IsWindowMinimized", "IsWindowMaximized", "IsWindowResized", "IsWindowFocused",
    "IsWindowState", "SetWindowState", "ClearWindowState",
    "GetWindowWidth", "GetWindowHeight", "GetScreenWidth", "GetScreenHeight",
    "GetRenderWidth", "GetRenderHeight",
    "ClearBackground",

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
    "DrawPixel", "DrawPixelV",
    "DrawLine", "DrawLineV", "DrawLineEx", "DrawLineStrip", "DrawLineBezier",
    "DrawCircle",
    "DrawRectangle",
    "DrawTexture",
    "DrawText",
    "DrawFPS",

    # Assets
    "LoadTexture", "UnloadTexture",

    # Other
    "TraceLog"
}

ENUM_WHITELIST = {
    "KeyboardKey", "GamepadButton", "GamepadAxis",
    "MouseButton", "MouseCursor",
    "ConfigFlags",
    "CameraMode", "CameraProjection",
    "TraceLogLevel"
}

# --- Helper Functions ---

def clean_type(t):
    """Removes qualifiers to find the base type name."""
    return t.replace("const ", "").replace("*", "").strip()

def get_mapping(type_str, is_struct):
    """Retrieves the JS conversion mapping for a given type."""
    # Logic: if it's a raw struct (not a pointer), treat as int/ID for now,
    # otherwise look up in map.
    key = type_str if not is_struct else "int"
    return TYPE_MAP.get(key, TYPE_MAP.get("int"))

# --- Processing Modules ---

def process_aliases(data, known_structs, all_items):
    processed = []
    for a in data.get('aliases', []):
        name = a['name'].replace('*', '').strip()
        all_items.append(name)

        if name in STRUCT_WHITELIST:
            known_structs.add(name)
            processed.append({
                "name": name,
                "target": a['type'],
                "is_ptr": '*' in a['name']
            })
    return processed

def process_structs(data, known_structs, all_items):
    processed = []
    for s in data.get('structs', []):
        all_items.append(s['name'])
        if s['name'] not in STRUCT_WHITELIST:
            continue

        fields = []
        for f in s['fields']:
            f_type = f['type'].replace("const ", "").strip()
            is_struct = clean_type(f_type) in known_structs
            mapping = get_mapping(f_type, is_struct)

            fields.append({
                "name": f['name'],
                "type": f_type,
                "is_struct": is_struct,
                "is_ptr": '*' in f_type,
                "cast": mapping["cast"],
                "to_js": mapping["to"],
                "from_js": mapping["from"],
                "direct_return": mapping.get("direct_return", False)
            })
        processed.append({"name": s['name'], "fields": fields})
    return processed

def process_functions(data, known_structs, all_items):
    processed = []
    for func in data.get('functions', []):
        all_items.append(func['name'])
        if func['name'] not in FUNCTION_WHITELIST:
            continue

        params = []
        for i, p in enumerate(func.get('params', [])):
            p_type = p['type']
            clean_p = clean_type(p_type)
            is_struct = clean_p in known_structs
            is_ptr = '*' in p_type

            if is_struct and is_ptr:
                mapping = {"from": None, "cast": p_type}
            else:
                mapping = get_mapping(p_type, is_struct)

            params.append({
                "name": p['name'],
                "type": p_type,
                "clean_type": clean_p,
                "is_struct": is_struct,
                "is_const": "const" in p_type,
                "is_buffer": p_type == "const void *",
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

        processed.append({
            "name": func['name'],
            "params": params,
            "return_type": ret_type,
            "clean_return_type": clean_ret,
            "is_ret_struct": is_ret_struct,
            "is_ret_void": ret_type == "void",
            "to_js": ret_mapping["to"],
            "cast": ret_mapping.get("cast", "double")
        })
    return processed

def process_enums(data, all_items):
    processed = []
    for e in data.get('enums', []):
        if e['name'] not in ENUM_WHITELIST:
            continue
        values = []
        for v in e.get('values', []):
            values.append({"name": v['name'], "value": v['value']})
            all_items.append(v['name'])
        processed.append({"name": e['name'], "vals": values})
    return processed

def get_raylib_colors(data):
    colors = []
    target_colors = {
        "LIGHTGRAY", "GRAY", "DARKGRAY", "YELLOW", "GOLD", "ORANGE", "PINK",
        "RED", "MAROON", "GREEN", "LIME", "DARKGREEN", "SKYBLUE", "BLUE",
        "DARKBLUE", "PURPLE", "VIOLET", "DARKPURPLE", "BEIGE", "BROWN",
        "DARKBROWN", "WHITE", "BLACK", "BLANK", "MAGENTA", "RAYWHITE"
    }
    for define in data.get("defines", []):
        if define["name"] in target_colors:
            match = re.search(r'\{ *(\d+), *(\d+), *(\d+), *(\d+) *\}', define["value"])
            if match:
                colors.append({
                    "name": define["name"],
                    "r": match.group(1), "g": match.group(2),
                    "b": match.group(3), "a": match.group(4)
                })
    return colors

def write_if_changed(file_path, new_content):
    """Writes content to file only if it differs from existing content."""
    if os.path.exists(file_path):
        with open(file_path, 'r') as f:
            existing_content = f.read()

        if existing_content == new_content:
            print(f"Skipping {os.path.basename(file_path)} (No changes)")
            return False

    # If file doesn't exist or content is different, write it
    with open(file_path, 'w') as f:
        f.write(new_content)
    return True

# --- Main Execution ---

def run_generator():
    print("Loading raylib.json...")
    with open('raylib.json', 'r') as f:
        data = json.load(f)

    # Shared state for the generation process
    known_structs = {s['name'] for s in data.get('structs', [])}
    all_items = []

    # Execute processing steps
    print("Processing components...")
    context = {
        "aliases": process_aliases(data, known_structs, all_items),
        "structs": process_structs(data, known_structs, all_items),
        "functions": process_functions(data, known_structs, all_items),
        "enum_list": process_enums(data, all_items),
        "color": get_raylib_colors(data),
        "all": all_items,
        "raylib_ns": RAYLIB_GLOBAL_NAMESPACE
    }

    # Render Templates
    for file_base in ['rl_bindings', 'rl_structs', 'rl_enums', 'rl_functions']:
        for ext in ['hpp', 'cpp']:
            template_path = f'{file_base}.{ext}.jinja2'
            output_path = f'../../src/raylib/{file_base}.{ext}'

            try:
                with open(template_path, 'r') as f:
                    template = Template(f.read(), trim_blocks=True, lstrip_blocks=True)

                rendered_content = template.render(**context)

                # Use the check-before-write logic here
                if write_if_changed(output_path, rendered_content):
                    print(f"Updated: {output_path}")

            except FileNotFoundError:
                print(f"Skipping {template_path} (Not found)")

if __name__ == "__main__":
    run_generator()
    print("Done!")