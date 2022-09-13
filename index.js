const bindings = require("bindings")("glfw.node");

module.exports.GLFW_VERSION_MAJOR = 3;
module.exports.GLFW_VERSION_MINOR = 3;
module.exports.GLFW_VERSION_REVISION = 7;
module.exports.GLFW_TRUE = 1;
module.exports.GLFW_FALSE = 0;
module.exports.GLFW_RELEASE = 0;
module.exports.GLFW_PRESS = 1;
module.exports.GLFW_REPEAT = 2;
module.exports.GLFW_HAT_CENTERED = 0;
module.exports.GLFW_HAT_UP = 1;
module.exports.GLFW_HAT_RIGHT = 2;
module.exports.GLFW_HAT_DOWN = 4;
module.exports.GLFW_HAT_LEFT = 8;
module.exports.GLFW_HAT_RIGHT_UP = module.exports.GLFW_HAT_RIGHT | module.exports.GLFW_HAT_UP;
module.exports.GLFW_HAT_RIGHT_DOWN = module.exports.GLFW_HAT_RIGHT | module.exports.GLFW_HAT_DOWN;
module.exports.GLFW_HAT_LEFT_UP = module.exports.GLFW_HAT_LEFT | module.exports.GLFW_HAT_UP;
module.exports.GLFW_HAT_LEFT_DOWN = module.exports.GLFW_HAT_LEFT | module.exports.GLFW_HAT_DOWN;
module.exports.GLFW_KEY_UNKNOWN = - 1;
module.exports.GLFW_KEY_SPACE = 32;
module.exports.GLFW_KEY_APOSTROPHE = 39;
module.exports.GLFW_KEY_COMMA = 44;
module.exports.GLFW_KEY_MINUS = 45;
module.exports.GLFW_KEY_PERIOD = 46;
module.exports.GLFW_KEY_SLASH = 47;
module.exports.GLFW_KEY_0 = 48;
module.exports.GLFW_KEY_1 = 49;
module.exports.GLFW_KEY_2 = 50;
module.exports.GLFW_KEY_3 = 51;
module.exports.GLFW_KEY_4 = 52;
module.exports.GLFW_KEY_5 = 53;
module.exports.GLFW_KEY_6 = 54;
module.exports.GLFW_KEY_7 = 55;
module.exports.GLFW_KEY_8 = 56;
module.exports.GLFW_KEY_9 = 57;
module.exports.GLFW_KEY_SEMICOLON = 59;
module.exports.GLFW_KEY_EQUAL = 61;
module.exports.GLFW_KEY_A = 65;
module.exports.GLFW_KEY_B = 66;
module.exports.GLFW_KEY_C = 67;
module.exports.GLFW_KEY_D = 68;
module.exports.GLFW_KEY_E = 69;
module.exports.GLFW_KEY_F = 70;
module.exports.GLFW_KEY_G = 71;
module.exports.GLFW_KEY_H = 72;
module.exports.GLFW_KEY_I = 73;
module.exports.GLFW_KEY_J = 74;
module.exports.GLFW_KEY_K = 75;
module.exports.GLFW_KEY_L = 76;
module.exports.GLFW_KEY_M = 77;
module.exports.GLFW_KEY_N = 78;
module.exports.GLFW_KEY_O = 79;
module.exports.GLFW_KEY_P = 80;
module.exports.GLFW_KEY_Q = 81;
module.exports.GLFW_KEY_R = 82;
module.exports.GLFW_KEY_S = 83;
module.exports.GLFW_KEY_T = 84;
module.exports.GLFW_KEY_U = 85;
module.exports.GLFW_KEY_V = 86;
module.exports.GLFW_KEY_W = 87;
module.exports.GLFW_KEY_X = 88;
module.exports.GLFW_KEY_Y = 89;
module.exports.GLFW_KEY_Z = 90;
module.exports.GLFW_KEY_LEFT_BRACKET = 91;
module.exports.GLFW_KEY_BACKSLASH = 92;
module.exports.GLFW_KEY_RIGHT_BRACKET = 93;
module.exports.GLFW_KEY_GRAVE_ACCENT = 96; 
module.exports.GLFW_KEY_WORLD_1 = 161;
module.exports.GLFW_KEY_WORLD_2 = 162;
module.exports.GLFW_KEY_ESCAPE = 256;
module.exports.GLFW_KEY_ENTER = 257;
module.exports.GLFW_KEY_TAB = 258;
module.exports.GLFW_KEY_BACKSPACE = 259;
module.exports.GLFW_KEY_INSERT = 260;
module.exports.GLFW_KEY_DELETE = 261;
module.exports.GLFW_KEY_RIGHT = 262;
module.exports.GLFW_KEY_LEFT = 263;
module.exports.GLFW_KEY_DOWN = 264;
module.exports.GLFW_KEY_UP = 265;
module.exports.GLFW_KEY_PAGE_UP = 266;
module.exports.GLFW_KEY_PAGE_DOWN = 267;
module.exports.GLFW_KEY_HOME = 268;
module.exports.GLFW_KEY_END = 269;
module.exports.GLFW_KEY_CAPS_LOCK = 280;
module.exports.GLFW_KEY_SCROLL_LOCK = 281;
module.exports.GLFW_KEY_NUM_LOCK = 282;
module.exports.GLFW_KEY_PRINT_SCREEN = 283;
module.exports.GLFW_KEY_PAUSE = 284;
module.exports.GLFW_KEY_F1 = 290;
module.exports.GLFW_KEY_F2 = 291;
module.exports.GLFW_KEY_F3 = 292;
module.exports.GLFW_KEY_F4 = 293;
module.exports.GLFW_KEY_F5 = 294;
module.exports.GLFW_KEY_F6 = 295;
module.exports.GLFW_KEY_F7 = 296;
module.exports.GLFW_KEY_F8 = 297;
module.exports.GLFW_KEY_F9 = 298;
module.exports.GLFW_KEY_F10 = 299;
module.exports.GLFW_KEY_F11 = 300;
module.exports.GLFW_KEY_F12 = 301;
module.exports.GLFW_KEY_F13 = 302;
module.exports.GLFW_KEY_F14 = 303;
module.exports.GLFW_KEY_F15 = 304;
module.exports.GLFW_KEY_F16 = 305;
module.exports.GLFW_KEY_F17 = 306;
module.exports.GLFW_KEY_F18 = 307;
module.exports.GLFW_KEY_F19 = 308;
module.exports.GLFW_KEY_F20 = 309;
module.exports.GLFW_KEY_F21 = 310;
module.exports.GLFW_KEY_F22 = 311;
module.exports.GLFW_KEY_F23 = 312;
module.exports.GLFW_KEY_F24 = 313;
module.exports.GLFW_KEY_F25 = 314;
module.exports.GLFW_KEY_KP_0 = 320;
module.exports.GLFW_KEY_KP_1 = 321;
module.exports.GLFW_KEY_KP_2 = 322;
module.exports.GLFW_KEY_KP_3 = 323;
module.exports.GLFW_KEY_KP_4 = 324;
module.exports.GLFW_KEY_KP_5 = 325;
module.exports.GLFW_KEY_KP_6 = 326;
module.exports.GLFW_KEY_KP_7 = 327;
module.exports.GLFW_KEY_KP_8 = 328;
module.exports.GLFW_KEY_KP_9 = 329;
module.exports.GLFW_KEY_KP_DECIMAL = 330;
module.exports.GLFW_KEY_KP_DIVIDE = 331;
module.exports.GLFW_KEY_KP_MULTIPLY = 332;
module.exports.GLFW_KEY_KP_SUBTRACT = 333;
module.exports.GLFW_KEY_KP_ADD = 334;
module.exports.GLFW_KEY_KP_ENTER = 335;
module.exports.GLFW_KEY_KP_EQUAL = 336;
module.exports.GLFW_KEY_LEFT_SHIFT = 340;
module.exports.GLFW_KEY_LEFT_CONTROL = 341;
module.exports.GLFW_KEY_LEFT_ALT = 342;
module.exports.GLFW_KEY_LEFT_SUPER = 343;
module.exports.GLFW_KEY_RIGHT_SHIFT = 344;
module.exports.GLFW_KEY_RIGHT_CONTROL = 345;
module.exports.GLFW_KEY_RIGHT_ALT = 346;
module.exports.GLFW_KEY_RIGHT_SUPER = 347;
module.exports.GLFW_KEY_MENU = 348;
module.exports.GLFW_KEY_LAST = module.exports.GLFW_KEY_MENU;
module.exports.GLFW_MOD_SHIFT = 0x0001;
module.exports.GLFW_MOD_CONTROL = 0x0002;
module.exports.GLFW_MOD_ALT = 0x0004;
module.exports.GLFW_MOD_SUPER = 0x0008;
module.exports.GLFW_MOD_CAPS_LOCK = 0x0010;
module.exports.GLFW_MOD_NUM_LOCK = 0x0020;
module.exports.GLFW_MOUSE_BUTTON_1 = 0;
module.exports.GLFW_MOUSE_BUTTON_2 = 1;
module.exports.GLFW_MOUSE_BUTTON_3 = 2;
module.exports.GLFW_MOUSE_BUTTON_4 = 3;
module.exports.GLFW_MOUSE_BUTTON_5 = 4;
module.exports.GLFW_MOUSE_BUTTON_6 = 5;
module.exports.GLFW_MOUSE_BUTTON_7 = 6;
module.exports.GLFW_MOUSE_BUTTON_8 = 7;
module.exports.GLFW_MOUSE_BUTTON_LAST = module.exports.GLFW_MOUSE_BUTTON_8;
module.exports.GLFW_MOUSE_BUTTON_LEFT = module.exports.GLFW_MOUSE_BUTTON_1;
module.exports.GLFW_MOUSE_BUTTON_RIGHT = module.exports.GLFW_MOUSE_BUTTON_2;
module.exports.GLFW_MOUSE_BUTTON_MIDDLE = module.exports.GLFW_MOUSE_BUTTON_3;
module.exports.GLFW_JOYSTICK_1 = 0;
module.exports.GLFW_JOYSTICK_2 = 1;
module.exports.GLFW_JOYSTICK_3 = 2;
module.exports.GLFW_JOYSTICK_4 = 3;
module.exports.GLFW_JOYSTICK_5 = 4;
module.exports.GLFW_JOYSTICK_6 = 5;
module.exports.GLFW_JOYSTICK_7 = 6;
module.exports.GLFW_JOYSTICK_8 = 7;
module.exports.GLFW_JOYSTICK_9 = 8;
module.exports.GLFW_JOYSTICK_10 = 9;
module.exports.GLFW_JOYSTICK_11 = 10;
module.exports.GLFW_JOYSTICK_12 = 11;
module.exports.GLFW_JOYSTICK_13 = 12;
module.exports.GLFW_JOYSTICK_14 = 13;
module.exports.GLFW_JOYSTICK_15 = 14;
module.exports.GLFW_JOYSTICK_16 = 15;
module.exports.GLFW_JOYSTICK_LAST = module.exports.GLFW_JOYSTICK_16;
module.exports.GLFW_GAMEPAD_BUTTON_A = 0;
module.exports.GLFW_GAMEPAD_BUTTON_B = 1;
module.exports.GLFW_GAMEPAD_BUTTON_X = 2;
module.exports.GLFW_GAMEPAD_BUTTON_Y = 3;
module.exports.GLFW_GAMEPAD_BUTTON_LEFT_BUMPER = 4;
module.exports.GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER = 5;
module.exports.GLFW_GAMEPAD_BUTTON_BACK = 6;
module.exports.GLFW_GAMEPAD_BUTTON_START = 7;
module.exports.GLFW_GAMEPAD_BUTTON_GUIDE = 8;
module.exports.GLFW_GAMEPAD_BUTTON_LEFT_THUMB = 9;
module.exports.GLFW_GAMEPAD_BUTTON_RIGHT_THUMB = 10;
module.exports.GLFW_GAMEPAD_BUTTON_DPAD_UP = 11;
module.exports.GLFW_GAMEPAD_BUTTON_DPAD_RIGHT = 12;
module.exports.GLFW_GAMEPAD_BUTTON_DPAD_DOWN = 13;
module.exports.GLFW_GAMEPAD_BUTTON_DPAD_LEFT = 14;
module.exports.GLFW_GAMEPAD_BUTTON_LAST = module.exports.GLFW_GAMEPAD_BUTTON_DPAD_LEFT;
module.exports.GLFW_GAMEPAD_BUTTON_CROSS = module.exports.GLFW_GAMEPAD_BUTTON_A;
module.exports.GLFW_GAMEPAD_BUTTON_CIRCLE = module.exports.GLFW_GAMEPAD_BUTTON_B;
module.exports.GLFW_GAMEPAD_BUTTON_SQUARE = module.exports.GLFW_GAMEPAD_BUTTON_X;
module.exports.GLFW_GAMEPAD_BUTTON_TRIANGLE = module.exports.GLFW_GAMEPAD_BUTTON_Y;
module.exports.GLFW_GAMEPAD_AXIS_LEFT_X = 0;
module.exports.GLFW_GAMEPAD_AXIS_LEFT_Y = 1;
module.exports.GLFW_GAMEPAD_AXIS_RIGHT_X = 2;
module.exports.GLFW_GAMEPAD_AXIS_RIGHT_Y = 3;
module.exports.GLFW_GAMEPAD_AXIS_LEFT_TRIGGER = 4;
module.exports.GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER = 5;
module.exports.GLFW_GAMEPAD_AXIS_LAST = module.exports.GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER;
module.exports.GLFW_NO_ERROR = 0;
module.exports.GLFW_NOT_INITIALIZED = 0x00010001;
module.exports.GLFW_NO_CURRENT_CONTEXT = 0x00010002;
module.exports.GLFW_INVALID_ENUM = 0x00010003;
module.exports.GLFW_INVALID_VALUE = 0x00010004;
module.exports.GLFW_OUT_OF_MEMORY = 0x00010005;
module.exports.GLFW_API_UNAVAILABLE = 0x00010006;
module.exports.GLFW_VERSION_UNAVAILABLE = 0x00010007;
module.exports.GLFW_PLATFORM_ERROR = 0x00010008;
module.exports.GLFW_FORMAT_UNAVAILABLE = 0x00010009;
module.exports.GLFW_NO_WINDOW_CONTEXT = 0x0001000A;
module.exports.GLFW_FOCUSED = 0x00020001;
module.exports.GLFW_ICONIFIED = 0x00020002;
module.exports.GLFW_RESIZABLE = 0x00020003;
module.exports.GLFW_VISIBLE = 0x00020004;
module.exports.GLFW_DECORATED = 0x00020005;
module.exports.GLFW_AUTO_ICONIFY = 0x00020006;
module.exports.GLFW_FLOATING = 0x00020007;
module.exports.GLFW_MAXIMIZED = 0x00020008;
module.exports.GLFW_CENTER_CURSOR = 0x00020009;
module.exports.GLFW_TRANSPARENT_FRAMEBUFFER = 0x0002000A;
module.exports.GLFW_HOVERED = 0x0002000B;
module.exports.GLFW_FOCUS_ON_SHOW = 0x0002000C;
module.exports.GLFW_RED_BITS = 0x00021001;
module.exports.GLFW_GREEN_BITS = 0x00021002;
module.exports.GLFW_BLUE_BITS = 0x00021003;
module.exports.GLFW_ALPHA_BITS = 0x00021004;
module.exports.GLFW_DEPTH_BITS = 0x00021005;
module.exports.GLFW_STENCIL_BITS = 0x00021006;
module.exports.GLFW_ACCUM_RED_BITS = 0x00021007;
module.exports.GLFW_ACCUM_GREEN_BITS = 0x00021008;
module.exports.GLFW_ACCUM_BLUE_BITS = 0x00021009;
module.exports.GLFW_ACCUM_ALPHA_BITS = 0x0002100A;
module.exports.GLFW_AUX_BUFFERS = 0x0002100B;
module.exports.GLFW_STEREO = 0x0002100C;
module.exports.GLFW_SAMPLES = 0x0002100D;
module.exports.GLFW_SRGB_CAPABLE = 0x0002100E;
module.exports.GLFW_REFRESH_RATE = 0x0002100F;
module.exports.GLFW_DOUBLEBUFFER = 0x00021010;
module.exports.GLFW_CLIENT_API = 0x00022001;
module.exports.GLFW_CONTEXT_VERSION_MAJOR = 0x00022002;
module.exports.GLFW_CONTEXT_VERSION_MINOR = 0x00022003;
module.exports.GLFW_CONTEXT_REVISION = 0x00022004;
module.exports.GLFW_CONTEXT_ROBUSTNESS = 0x00022005;
module.exports.GLFW_OPENGL_FORWARD_COMPAT = 0x00022006;
module.exports.GLFW_OPENGL_DEBUG_CONTEXT = 0x00022007;
module.exports.GLFW_OPENGL_PROFILE = 0x00022008;
module.exports.GLFW_CONTEXT_RELEASE_BEHAVIOR = 0x00022009;
module.exports.GLFW_CONTEXT_NO_ERROR = 0x0002200A;
module.exports.GLFW_CONTEXT_CREATION_API = 0x0002200B;
module.exports.GLFW_SCALE_TO_MONITOR = 0x0002200C;
module.exports.GLFW_COCOA_RETINA_FRAMEBUFFER = 0x00023001;
module.exports.GLFW_COCOA_FRAME_NAME = 0x00023002;
module.exports.GLFW_COCOA_GRAPHICS_SWITCHING = 0x00023003;
module.exports.GLFW_X11_CLASS_NAME = 0x00024001;
module.exports.GLFW_X11_INSTANCE_NAME = 0x00024002;
module.exports.GLFW_NO_API = 0;
module.exports.GLFW_OPENGL_API = 0x00030001;
module.exports.GLFW_OPENGL_ES_API = 0x00030002;
module.exports.GLFW_NO_ROBUSTNESS = 0;
module.exports.GLFW_NO_RESET_NOTIFICATION = 0x00031001;
module.exports.GLFW_LOSE_CONTEXT_ON_RESET = 0x00031002;
module.exports.GLFW_OPENGL_ANY_PROFILE = 0;
module.exports.GLFW_OPENGL_CORE_PROFILE = 0x00032001;
module.exports.GLFW_OPENGL_COMPAT_PROFILE = 0x00032002;
module.exports.GLFW_CURSOR = 0x00033001;
module.exports.GLFW_STICKY_KEYS = 0x00033002;
module.exports.GLFW_STICKY_MOUSE_BUTTONS = 0x00033003;
module.exports.GLFW_LOCK_KEY_MODS = 0x00033004;
module.exports.GLFW_RAW_MOUSE_MOTION = 0x00033005;
module.exports.GLFW_CURSOR_NORMAL = 0x00034001;
module.exports.GLFW_CURSOR_HIDDEN = 0x00034002;
module.exports.GLFW_CURSOR_DISABLED = 0x00034003;
module.exports.GLFW_ANY_RELEASE_BEHAVIOR = 0;
module.exports.GLFW_RELEASE_BEHAVIOR_FLUSH = 0x00035001;
module.exports.GLFW_RELEASE_BEHAVIOR_NONE = 0x00035002;
module.exports.GLFW_NATIVE_CONTEXT_API = 0x00036001;
module.exports.GLFW_EGL_CONTEXT_API = 0x00036002;
module.exports.GLFW_OSMESA_CONTEXT_API = 0x00036003;
module.exports.GLFW_ARROW_CURSOR = 0x00036001;
module.exports.GLFW_IBEAM_CURSOR = 0x00036002;
module.exports.GLFW_CROSSHAIR_CURSOR = 0x00036003;
module.exports.GLFW_HAND_CURSOR = 0x00036004;
module.exports.GLFW_HRESIZE_CURSOR = 0x00036005;
module.exports.GLFW_VRESIZE_CURSOR = 0x00036006;
module.exports.GLFW_CONNECTED = 0x00040001;
module.exports.GLFW_DISCONNECTED = 0x00040002;
module.exports.GLFW_JOYSTICK_HAT_BUTTONS = 0x00050001;
module.exports.GLFW_COCOA_CHDIR_RESOURCES = 0x00051001;
module.exports.GLFW_COCOA_MENUBAR = 0x00051002;
module.exports.GLFW_DONT_CARE = -1;

module.exports = {
    ...module.exports,
    ...bindings
}