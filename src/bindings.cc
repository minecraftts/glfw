#define GLFW_INCLUDE_NONE

#include <napi.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <map>

// Callbacks

// Initialization, version and error callbacks
Napi::FunctionReference *errorCallback;

// Input callbacks
std::map<GLFWwindow *, Napi::FunctionReference *> keyCallbacks;
std::map<GLFWwindow *, Napi::FunctionReference *> mouseButtonCallbacks;
std::map<GLFWwindow *, Napi::FunctionReference *> cursorPosCallbacks;
std::map<GLFWwindow *, Napi::FunctionReference *> cursorEnterCallbacks;
std::map<GLFWwindow *, Napi::FunctionReference *> scrollCallbacks;
std::map<GLFWwindow *, Napi::FunctionReference *> charCallbacks;
std::map<GLFWwindow *, Napi::FunctionReference *> charModsCallbacks;
std::map<GLFWwindow *, Napi::FunctionReference *> dropCallbacks;
Napi::FunctionReference *joystickCallback;

// Monitor callbacks
Napi::FunctionReference *monitorCallback;

// Window callbacks
Napi::FunctionReference *windowPosCallback;
Napi::FunctionReference *windowSizeCallback;
Napi::FunctionReference *windowCloseCallback;
Napi::FunctionReference *windowRefreshCallback;
Napi::FunctionReference *windowFocusCallback;
Napi::FunctionReference *windowIconifyCallback;
Napi::FunctionReference *windowMaximizeCallback;
std::map<GLFWwindow *, Napi::FunctionReference *> framebufferSizeCallbacks;
Napi::FunctionReference *windowContentScaleCallback;

void setObjPtr(Napi::Env env, Napi::Value obj, Napi::Value value) {
    obj.As<Napi::Object>().Set("$", value);
}

template <typename T>
T getObjPtr(Napi::Env env, Napi::Object obj) {
    return obj.Get("$").As<T>();
}

// Define context functions
void __glfwMakeContextCurrent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    glfwMakeContextCurrent(window);
}

Napi::External<GLFWwindow> __glfwGetCurrentContext(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = glfwGetCurrentContext();
    return Napi::External<GLFWwindow>::New(env, window);
}

void __glfwSwapInterval(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int interval = info[0].As<Napi::Number>().Int32Value();
    glfwSwapInterval(interval);
}

Napi::Boolean __glfwExtensionSupported(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    std::string extension = info[0].As<Napi::String>().Utf8Value();
    return Napi::Boolean::New(env, glfwExtensionSupported(extension.c_str()) == GLFW_TRUE);
}

// Define initialization, version and error functions
Napi::Boolean __glfwInit(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Boolean::New(env, glfwInit() == GLFW_TRUE);
}

void __glfwTerminate(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    glfwTerminate();
}

void __glfwInitHint(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int hint = info[0].As<Napi::Number>().Int32Value();
    int value = info[1].As<Napi::Number>().Int32Value();
    glfwInitHint(hint, value);
}

void __glfwGetVersion(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int major = 0, minor = 0, rev = 0;
    glfwGetVersion(&major, &minor, &rev);

    setObjPtr(env, info[0], Napi::Number::New(env, major));
    setObjPtr(env, info[1], Napi::Number::New(env, minor));
    setObjPtr(env, info[2], Napi::Number::New(env, rev));
}

Napi::String __glfwGetVersionString(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::String::New(env, glfwGetVersionString());
}

Napi::Number __glfwGetError(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    const char* desc = new char[1024];
    int code = glfwGetError(&desc);

    if (info.Length() > 0 && info[0].IsObject()) {
        setObjPtr(env, info[0], Napi::String::New(env, desc, 1024));
    }

    delete[] desc;

    return Napi::Number::New(env, code);
}

void __glfwSetErrorCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsFunction()) {
        errorCallback = new Napi::FunctionReference();
        errorCallback->Reset(info[0].As<Napi::Function>());
    } else {
        errorCallback = nullptr;
    }

    glfwSetErrorCallback([](int code, const char* desc) {
        if (errorCallback != nullptr) {
            Napi::Env env = errorCallback->Env();
            Napi::HandleScope scope(env);

            Napi::Number codeNum = Napi::Number::New(env, code);
            Napi::String str = Napi::String::New(env, desc);

            errorCallback->Call({ codeNum, str });
        }
    });
}

// Define input handling functions
Napi::Number __glfwGetInputMode(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int mode = info[1].As<Napi::Number>().Int32Value();

    return Napi::Number::New(env, glfwGetInputMode(window, mode));
}

void __glfwSetInputMode(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int mode = info[1].As<Napi::Number>().Int32Value();
    int value = info[2].As<Napi::Number>().Int32Value();

    glfwSetInputMode(window, mode, value);
}

Napi::Boolean __glfwRawMouseMotionSupported(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Boolean::New(env, glfwRawMouseMotionSupported() == GLFW_TRUE);
}

Napi::String __glfwGetKeyName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int key = info[0].As<Napi::Number>().Int32Value();
    const char* name = glfwGetKeyName(key, 0);

    return Napi::String::New(env, name);
}

Napi::Number __glfwGetKeyScancode(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int key = info[0].As<Napi::Number>().Int32Value();

    return Napi::Number::New(env, glfwGetKeyScancode(key));
}

Napi::Number __glfwGetKey(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int key = info[1].As<Napi::Number>().Int32Value();

    return Napi::Number::New(env, glfwGetKey(window, key));
}

Napi::Number __glfwGetMouseButton(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int button = info[1].As<Napi::Number>().Int32Value();

    return Napi::Number::New(env, glfwGetMouseButton(window, button));
}

void __glfwGetCursorPos(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    setObjPtr(env, info[1], Napi::Number::New(env, xpos));
    setObjPtr(env, info[2], Napi::Number::New(env, ypos));
}

void __glfwSetCursorPos(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    double xpos = info[1].As<Napi::Number>().DoubleValue();
    double ypos = info[2].As<Napi::Number>().DoubleValue();

    glfwSetCursorPos(window, xpos, ypos);
}

Napi::External<GLFWcursor> __glfwCreateCursor(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Object jsImage = info[0].As<Napi::Object>();
    int width = jsImage.Get("width").As<Napi::Number>().Int32Value();
    int height = jsImage.Get("height").As<Napi::Number>().Int32Value();
    unsigned char *pixels = jsImage.Get("pixels").As<Napi::ArrayBuffer>().As<Napi::Uint8Array>().Data();

    const GLFWimage image = { width, height, pixels };

    int xhot = info[1].As<Napi::Number>().Int32Value();
    int yhot = info[2].As<Napi::Number>().Int32Value();

    GLFWcursor *cursor = glfwCreateCursor(&image, xhot, yhot);

    return Napi::External<GLFWcursor>::New(env, cursor);
}

Napi::External<GLFWcursor> __glfwCreateStandardCursor(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int shape = info[0].As<Napi::Number>().Int32Value();

    GLFWcursor *cursor = glfwCreateStandardCursor(shape);

    return Napi::External<GLFWcursor>::New(env, cursor);
}

void __glfwDestroyCursor(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWcursor *cursor = info[0].As<Napi::External<GLFWcursor>>().Data();

    glfwDestroyCursor(cursor);
}

void __glfwSetCursor(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    GLFWcursor *cursor = info[1].As<Napi::External<GLFWcursor>>().Data();

    glfwSetCursor(window, cursor);
}

void __glfwSetKeyCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (info[1].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[1].As<Napi::Function>());
        keyCallbacks[window] = ref;
    } else {
        delete keyCallbacks[window];
    }

    glfwSetKeyCallback(window, [] (GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (keyCallbacks.find(window) != keyCallbacks.end()) {
            Napi::FunctionReference *callback = keyCallbacks[window];
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::External<GLFWwindow> windowRef = Napi::External<GLFWwindow>::New(env, window);
            Napi::Number keyNum = Napi::Number::New(env, key);
            Napi::Number scancodeNum = Napi::Number::New(env, scancode);
            Napi::Number actionNum = Napi::Number::New(env, action);
            Napi::Number modsNum = Napi::Number::New(env, mods);

            callback->Call({ windowRef, keyNum, scancodeNum, actionNum, modsNum });
        }
    });
}

void __glfwSetCharCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (info[1].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[1].As<Napi::Function>());
        charCallbacks[window] = ref;
    } else {
        delete charCallbacks[window];
    }

    glfwSetCharCallback(window, [] (GLFWwindow *window, unsigned int codepoint) {
        if (charCallbacks.find(window) != charCallbacks.end()) {
            Napi::FunctionReference *callback = charCallbacks[window];
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::External<GLFWwindow> windowRef = Napi::External<GLFWwindow>::New(env, window);
            Napi::Number codepointNum = Napi::Number::New(env, codepoint);

            callback->Call({ windowRef, codepointNum });
        }
    });
}

void __glfwSetCharModsCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (info[1].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[1].As<Napi::Function>());
        charModsCallbacks[window] = ref;
    } else {
        delete charModsCallbacks[window];
    }

    glfwSetCharModsCallback(window, [] (GLFWwindow *window, unsigned int codepoint, int mods) {
        if (charModsCallbacks.find(window) != charModsCallbacks.end()) {
            Napi::FunctionReference *callback = charModsCallbacks[window];
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::External<GLFWwindow> windowRef = Napi::External<GLFWwindow>::New(env, window);
            Napi::Number codepointNum = Napi::Number::New(env, codepoint);
            Napi::Number modsNum = Napi::Number::New(env, mods);

            callback->Call({ windowRef, codepointNum, modsNum });
        }
    });
}

void __glfwSetMouseButtonCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (info[1].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[1].As<Napi::Function>());
        mouseButtonCallbacks[window] = ref;
    } else {
        delete mouseButtonCallbacks[window];
    }

    glfwSetMouseButtonCallback(window, [] (GLFWwindow *window, int button, int action, int mods) {
        if (mouseButtonCallbacks.find(window) != mouseButtonCallbacks.end()) {
            Napi::FunctionReference *callback = mouseButtonCallbacks[window];
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::External<GLFWwindow> windowRef = Napi::External<GLFWwindow>::New(env, window);
            Napi::Number buttonNum = Napi::Number::New(env, button);
            Napi::Number actionNum = Napi::Number::New(env, action);
            Napi::Number modsNum = Napi::Number::New(env, mods);

            callback->Call({ windowRef, buttonNum, actionNum, modsNum });
        }
    });
}

void __glfwSetCursorPosCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (info[1].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[1].As<Napi::Function>());
        cursorPosCallbacks[window] = ref;
    } else {
        delete cursorPosCallbacks[window];
    }

    glfwSetCursorPosCallback(window, [] (GLFWwindow *window, double xpos, double ypos) {
        if (cursorPosCallbacks.find(window) != cursorPosCallbacks.end()) {
            Napi::FunctionReference *callback = cursorPosCallbacks[window];
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::External<GLFWwindow> windowRef = Napi::External<GLFWwindow>::New(env, window);
            Napi::Number xposNum = Napi::Number::New(env, xpos);
            Napi::Number yposNum = Napi::Number::New(env, ypos);

            callback->Call({ windowRef, xposNum, yposNum });
        }
    });
}

void __glfwSetCursorEnterCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (info[1].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[1].As<Napi::Function>());
        cursorEnterCallbacks[window] = ref;
    } else {
        delete cursorEnterCallbacks[window];
    }

    glfwSetCursorEnterCallback(window, [] (GLFWwindow *window, int entered) {
        if (cursorEnterCallbacks.find(window) != cursorEnterCallbacks.end()) {
            Napi::FunctionReference *callback = cursorEnterCallbacks[window];
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::External<GLFWwindow> windowRef = Napi::External<GLFWwindow>::New(env, window);
            Napi::Number enteredNum = Napi::Number::New(env, entered);

            callback->Call({ windowRef, enteredNum });
        }
    });
}

void __glfwSetScrollCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (info[1].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[1].As<Napi::Function>());
        scrollCallbacks[window] = ref;
    } else {
        delete scrollCallbacks[window];
    }

    glfwSetScrollCallback(window, [] (GLFWwindow *window, double xoffset, double yoffset) {
        if (scrollCallbacks.find(window) != scrollCallbacks.end()) {
            Napi::FunctionReference *callback = scrollCallbacks[window];
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::External<GLFWwindow> windowRef = Napi::External<GLFWwindow>::New(env, window);
            Napi::Number xoffsetNum = Napi::Number::New(env, xoffset);
            Napi::Number yoffsetNum = Napi::Number::New(env, yoffset);

            callback->Call({ windowRef, xoffsetNum, yoffsetNum });
        }
    });
}

void __glfwSetDropCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (info[1].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[1].As<Napi::Function>());
        dropCallbacks[window] = ref;
    } else {
        delete dropCallbacks[window];
    }

    glfwSetDropCallback(window, [] (GLFWwindow *window, int count, const char **paths) {
        if (dropCallbacks.find(window) != dropCallbacks.end()) {
            Napi::FunctionReference *callback = dropCallbacks[window];
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::External<GLFWwindow> windowRef = Napi::External<GLFWwindow>::New(env, window);
            Napi::Array pathsArray = Napi::Array::New(env, count);

            for (int i = 0; i < count; i++) {
                pathsArray[i] = Napi::String::New(env, paths[i]);
            }

            callback->Call({ windowRef, pathsArray });
        }
    });
}

Napi::Boolean __glfwJoystickPresent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int joy = info[0].As<Napi::Number>().Int32Value();

    return Napi::Boolean::New(env, glfwJoystickPresent(joy) == GLFW_TRUE);
}

Napi::Float32Array __glfwGetJoystickAxes(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int joy = info[0].As<Napi::Number>().Int32Value();
    int count;
    const float *axes = glfwGetJoystickAxes(joy, &count);

    Napi::Float32Array array = Napi::Float32Array::New(env, count);

    for (int i = 0; i < count; i++) {
        array.Set(i, axes[i]);
    }

    setObjPtr(env, info[1], Napi::Number::New(env, count));

    return array;
}

Napi::Uint8Array __glfwGetJoystickButtons(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int joy = info[0].As<Napi::Number>().Int32Value();
    int count;
    const unsigned char *buttons = glfwGetJoystickButtons(joy, &count);

    Napi::Uint8Array array = Napi::Uint8Array::New(env, count);

    for (int i = 0; i < count; i++) {
        array.Set(i, buttons[i]);
    }

    setObjPtr(env, info[1], Napi::Number::New(env, count));

    return array;
}

Napi::Uint8Array __glfwGetJoystickHats(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int joy = info[0].As<Napi::Number>().Int32Value();
    int count;
    const unsigned char *hats = glfwGetJoystickHats(joy, &count);

    Napi::Uint8Array array = Napi::Uint8Array::New(env, count);

    for (int i = 0; i < count; i++) {
        array.Set(i, hats[i]);
    }

    setObjPtr(env, info[1], Napi::Number::New(env, count));

    return array;
}

Napi::String __glfwGetJoystickName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int joy = info[0].As<Napi::Number>().Int32Value();

    return Napi::String::New(env, glfwGetJoystickName(joy));
}

Napi::String __glfwGetJoystickGUID(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int joy = info[0].As<Napi::Number>().Int32Value();

    return Napi::String::New(env, glfwGetJoystickGUID(joy));
}

Napi::Boolean __glfwJoystickIsGamepad(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int joy = info[0].As<Napi::Number>().Int32Value();

    return Napi::Boolean::New(env, glfwJoystickIsGamepad(joy) == GLFW_TRUE);
}

void __glfwSetJoystickCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info[0].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[0].As<Napi::Function>());
        joystickCallback = ref;
    } else {
        delete joystickCallback;
    }

    glfwSetJoystickCallback([](int joy, int event) {
        if (joystickCallback != nullptr) {
            Napi::FunctionReference *callback = joystickCallback;
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::Number joyNum = Napi::Number::New(env, joy);
            Napi::Number eventNum = Napi::Number::New(env, event);

            callback->Call({ joyNum, eventNum });
        }
    });
}

Napi::Boolean __glfwUpdateGamepadMappings(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    const char* string = info[0].As<Napi::String>().Utf8Value().c_str();

    return Napi::Boolean::New(env, glfwUpdateGamepadMappings(string) == GLFW_TRUE);
}

Napi::String __glfwGetGamepadName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int joy = info[0].As<Napi::Number>().Int32Value();

    return Napi::String::New(env, glfwGetGamepadName(joy));
}

Napi::Boolean __glfwGetGamepadState(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int joy = info[0].As<Napi::Number>().Int32Value();
    GLFWgamepadstate *state = info[1].As<Napi::External<GLFWgamepadstate>>().Data();

    return Napi::Boolean::New(env, glfwGetGamepadState(joy, state) == GLFW_TRUE);
}

void __glfwSetClipboardString(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    const char* string = info[1].As<Napi::String>().Utf8Value().c_str();

    glfwSetClipboardString(window, string);
}

Napi::String __glfwGetClipboardString(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    return Napi::String::New(env, glfwGetClipboardString(window));
}

Napi::Number __glfwGetTime(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, glfwGetTime());
}

void __glfwSetTime(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    double time = info[0].As<Napi::Number>().DoubleValue();

    glfwSetTime(time);
}

Napi::Number __glfwGetTimerValue(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, glfwGetTimerValue());
}

Napi::Number __glfwGetTimerFrequency(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Number::New(env, glfwGetTimerFrequency());
}

// Monitor functions
Napi::Array __glfwGetMonitors(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);

    Napi::Array array = Napi::Array::New(env, count);

    for (int i = 0; i < count; i++) {
        array.Set(i, Napi::External<GLFWmonitor>::New(env, monitors[i]));
    }

    setObjPtr(env, info[0], Napi::Number::New(env, count));

    return array;
}

Napi::External<GLFWmonitor> __glfwGetPrimaryMonitor(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::External<GLFWmonitor>::New(env, glfwGetPrimaryMonitor());
}

void __glfwGetMonitorPos(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();
    int xpos = 0, ypos = 0;

    glfwGetMonitorPos(monitor, &xpos, &ypos);

    setObjPtr(env, info[1], Napi::Number::New(env, xpos));
    setObjPtr(env, info[2], Napi::Number::New(env, ypos));
}

void __glfwGetMonitorWorkarea(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();
    int xpos = 0, ypos = 0, width = 0, height = 0;

    glfwGetMonitorWorkarea(monitor, &xpos, &ypos, &width, &height);

    setObjPtr(env, info[1], Napi::Number::New(env, xpos));
    setObjPtr(env, info[2], Napi::Number::New(env, ypos));
    setObjPtr(env, info[3], Napi::Number::New(env, width));
    setObjPtr(env, info[4], Napi::Number::New(env, height));
}

void __glfwGetMonitorPhysicalSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();
    int widthMM = 0, heightMM = 0;

    glfwGetMonitorPhysicalSize(monitor, &widthMM, &heightMM);

    setObjPtr(env, info[1], Napi::Number::New(env, widthMM));
    setObjPtr(env, info[2], Napi::Number::New(env, heightMM));
}

void __glfwGetMonitorContentScale(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();
    float xscale = 0, yscale = 0;

    glfwGetMonitorContentScale(monitor, &xscale, &yscale);

    setObjPtr(env, info[1], Napi::Number::New(env, xscale));
    setObjPtr(env, info[2], Napi::Number::New(env, yscale));
}

Napi::String __glfwGetMonitorName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();

    return Napi::String::New(env, glfwGetMonitorName(monitor));
}

void __glfwSetMonitorCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0 && info[0].IsFunction()) {
        if (monitorCallback == nullptr) {
            monitorCallback = new Napi::FunctionReference();
        }

        monitorCallback->Reset(info[0].As<Napi::Function>());
    } else {
        monitorCallback->Reset();
    }

    glfwSetMonitorCallback([](GLFWmonitor *monitor, int event) {
        if (monitorCallback == nullptr || monitorCallback->IsEmpty()) return;

        Napi::Env env = monitorCallback->Env();
        Napi::HandleScope scope(env);

        monitorCallback->Call({ Napi::External<GLFWmonitor>::New(env, monitor), Napi::Number::New(env, event) });
    });
}

Napi::Array __glfwGetVideoModes(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();
    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(monitor, &count);

    Napi::Array array = Napi::Array::New(env, count);

    for (int i = 0; i < count; i++) {
        Napi::Object obj = Napi::Object::New(env);

        obj.Set("width", Napi::Number::New(env, modes[i].width));
        obj.Set("height", Napi::Number::New(env, modes[i].height));
        obj.Set("redBits", Napi::Number::New(env, modes[i].redBits));
        obj.Set("greenBits", Napi::Number::New(env, modes[i].greenBits));
        obj.Set("blueBits", Napi::Number::New(env, modes[i].blueBits));
        obj.Set("refreshRate", Napi::Number::New(env, modes[i].refreshRate));

        array.Set(i, obj);
    }

    setObjPtr(env, info[1], Napi::Number::New(env, count));

    return array;
}

Napi::Object __glfwGetVideoMode(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    Napi::Object obj = Napi::Object::New(env);

    obj.Set("width", Napi::Number::New(env, mode->width));
    obj.Set("height", Napi::Number::New(env, mode->height));
    obj.Set("redBits", Napi::Number::New(env, mode->redBits));
    obj.Set("greenBits", Napi::Number::New(env, mode->greenBits));
    obj.Set("blueBits", Napi::Number::New(env, mode->blueBits));
    obj.Set("refreshRate", Napi::Number::New(env, mode->refreshRate));

    return obj;
}

void __glfwSetGamma(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();
    float gamma = info[1].As<Napi::Number>().FloatValue();

    glfwSetGamma(monitor, gamma);
}

Napi::Object __glfwGetGammaRamp(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();
    const GLFWgammaramp *gamma = glfwGetGammaRamp(monitor);

    Napi::Object obj = Napi::Object::New(env);

    obj.Set("red", Napi::Array::New(env, gamma->size));
    obj.Set("green", Napi::Array::New(env, gamma->size));
    obj.Set("blue", Napi::Array::New(env, gamma->size));
    obj.Set("size", Napi::Number::New(env, gamma->size));

    for (unsigned int i = 0; i < gamma->size; i++) {
        obj.Get("red").As<Napi::Array>().Set(i, Napi::Number::New(env, gamma->red[i]));
        obj.Get("green").As<Napi::Array>().Set(i, Napi::Number::New(env, gamma->green[i]));
        obj.Get("blue").As<Napi::Array>().Set(i, Napi::Number::New(env, gamma->blue[i]));
    }

    return obj;
}

void __glfwSetGammaRamp(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWmonitor *monitor = info[0].As<Napi::External<GLFWmonitor>>().Data();
    Napi::Object gamma = info[1].As<Napi::Object>();

    GLFWgammaramp ramp;

    ramp.size = gamma.Get("size").As<Napi::Number>().Uint32Value();
    ramp.red = new unsigned short[ramp.size];
    ramp.green = new unsigned short[ramp.size];
    ramp.blue = new unsigned short[ramp.size];

    for (unsigned int i = 0; i < ramp.size; i++) {
        ramp.red[i] = gamma.Get("red").As<Napi::Array>().Get(i).As<Napi::Number>().Uint32Value();
        ramp.green[i] = gamma.Get("green").As<Napi::Array>().Get(i).As<Napi::Number>().Uint32Value();
        ramp.blue[i] = gamma.Get("blue").As<Napi::Array>().Get(i).As<Napi::Number>().Uint32Value();
    }

    glfwSetGammaRamp(monitor, &ramp);

    delete[] ramp.red;
    delete[] ramp.green;
    delete[] ramp.blue;
}

// Define window functions

void __glfwDefaultWindowHints(const Napi::CallbackInfo &info) {
    glfwDefaultWindowHints();
}

void __glfwWindowHint(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int target = info[0].As<Napi::Number>().Int32Value();
    int hint = info[1].As<Napi::Number>().Int32Value();

    glfwWindowHint(target, hint);
}

void __glfwWindowHintString(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int target = info[0].As<Napi::Number>().Int32Value();
    std::string hint = info[1].As<Napi::String>().Utf8Value();

    glfwWindowHintString(target, hint.c_str());
}

Napi::External<GLFWwindow> __glfwCreateWindow(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int width = info[0].As<Napi::Number>().Int32Value();
    int height = info[1].As<Napi::Number>().Int32Value();
    std::string title = info[2].As<Napi::String>().Utf8Value();
    GLFWmonitor *monitor;
    GLFWwindow *share;

    if (info[3].IsExternal()) {
        monitor = info[3].As<Napi::External<GLFWmonitor>>().Data();
    } else {
        monitor = NULL;
    }

    if (info[4].IsExternal()) {
        share = info[4].As<Napi::External<GLFWwindow>>().Data();
    } else {
        share = NULL;
    }

    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), monitor, share);

    return Napi::External<GLFWwindow>::New(env, window);
}

void __glfwDestroyWindow(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    glfwDestroyWindow(window);
}

Napi::Boolean __glfwWindowShouldClose(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    return Napi::Boolean::New(env, glfwWindowShouldClose(window));
}

void __glfwSetWindowShouldClose(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int value = info[1].As<Napi::Number>().Int32Value();

    glfwSetWindowShouldClose(window, value);
}

void __glfwSetWindowTitle(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    std::string title = info[1].As<Napi::String>().Utf8Value();

    glfwSetWindowTitle(window, title.c_str());
}

void __glfwSetWindowIcon(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    int count = info[1].As<Napi::Number>().Int32Value();
    Napi::Array array = info[2].As<Napi::Array>();

    GLFWimage *images = new GLFWimage[count];

    for (int i = 0; i < count; i++) {
        Napi::Object obj = array.Get(i).As<Napi::Object>();

        images[i].width = obj.Get("width").As<Napi::Number>().Int32Value();
        images[i].height = obj.Get("height").As<Napi::Number>().Int32Value();
        images[i].pixels = obj.Get("pixels").As<Napi::Uint8Array>().Data();
    }

    glfwSetWindowIcon(window, count, images);

    delete[] images;
}

void __glfwGetWindowPos(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int xpos = 0, ypos = 0;

    glfwGetWindowPos(window, &xpos, &ypos);

    setObjPtr(env, info[1], Napi::Number::New(env, xpos));
    setObjPtr(env, info[2], Napi::Number::New(env, ypos));
}

void __glfwSetWindowPos(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int xpos = info[1].As<Napi::Number>().Int32Value();
    int ypos = info[2].As<Napi::Number>().Int32Value();

    glfwSetWindowPos(window, xpos, ypos);
}

void __glfwGetWindowSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int width = 0, height = 0;

    glfwGetWindowSize(window, &width, &height);

    setObjPtr(env, info[1], Napi::Number::New(env, width));
    setObjPtr(env, info[2], Napi::Number::New(env, height));
}

void __glfwSetWindowSizeLimits(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int minwidth = info[1].As<Napi::Number>().Int32Value();
    int minheight = info[2].As<Napi::Number>().Int32Value();
    int maxwidth = info[3].As<Napi::Number>().Int32Value();
    int maxheight = info[4].As<Napi::Number>().Int32Value();

    glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight);
}

void __glfwSetWindowAspectRatio(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int numer = info[1].As<Napi::Number>().Int32Value();
    int denom = info[2].As<Napi::Number>().Int32Value();

    glfwSetWindowAspectRatio(window, numer, denom);
}

void __glfwSetWindowSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int width = info[1].As<Napi::Number>().Int32Value();
    int height = info[2].As<Napi::Number>().Int32Value();

    glfwSetWindowSize(window, width, height);
}

void __glfwGetFramebufferSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int width = 0, height = 0;

    glfwGetFramebufferSize(window, &width, &height);

    setObjPtr(env, info[1], Napi::Number::New(env, width));
    setObjPtr(env, info[2], Napi::Number::New(env, height));
}

void __glfwGetWindowFrameSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int left = 0, top = 0, right = 0, bottom = 0;

    glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);

    setObjPtr(env, info[1], Napi::Number::New(env, left));
    setObjPtr(env, info[2], Napi::Number::New(env, top));
    setObjPtr(env, info[3], Napi::Number::New(env, right));
    setObjPtr(env, info[4], Napi::Number::New(env, bottom));
}

void __glfwGetWindowContentScale(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    float xscale = 0, yscale = 0;

    glfwGetWindowContentScale(window, &xscale, &yscale);

    setObjPtr(env, info[1], Napi::Number::New(env, xscale));
    setObjPtr(env, info[2], Napi::Number::New(env, yscale));
}

Napi::Number __glfwGetWindowOpacity(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    return Napi::Number::New(env, glfwGetWindowOpacity(window));
}

void __glfwSetWindowOpacity(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    float opacity = info[1].As<Napi::Number>().FloatValue();

    glfwSetWindowOpacity(window, opacity);
}

void __glfwIconifyWindow(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    glfwIconifyWindow(window);
}

void __glfwRestoreWindow(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    glfwRestoreWindow(window);
}

void __glfwMaximizeWindow(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    glfwMaximizeWindow(window);
}

void __glfwShowWindow(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    glfwShowWindow(window);
}

void __glfwHideWindow(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    glfwHideWindow(window);
}

void __glfwFocusWindow(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    glfwFocusWindow(window);
}

void __glfwRequestWindowAttention(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    glfwRequestWindowAttention(window);
}

Napi::External<GLFWmonitor> __glfwGetWindowMonitor(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    return Napi::External<GLFWmonitor>::New(env, glfwGetWindowMonitor(window));
}

void __glfwSetWindowMonitor(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int xpos = info[2].As<Napi::Number>().Int32Value();
    int ypos = info[3].As<Napi::Number>().Int32Value();
    int width = info[4].As<Napi::Number>().Int32Value();
    int height = info[5].As<Napi::Number>().Int32Value();
    int refreshRate = info[6].As<Napi::Number>().Int32Value();

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    
    if (info[1].IsExternal()) {
        GLFWmonitor *monitor = info[1].As<Napi::External<GLFWmonitor>>().Data();
        glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate);
    } else {
        glfwSetWindowMonitor(window, NULL, xpos, ypos, width, height, refreshRate);
    }
}

Napi::Number __glfwGetWindowAttrib(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int attrib = info[1].As<Napi::Number>().Int32Value();

    return Napi::Number::New(env, glfwGetWindowAttrib(window, attrib));
}

void __glfwSetWindowAttrib(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();
    int attrib = info[1].As<Napi::Number>().Int32Value();
    int value = info[2].As<Napi::Number>().Int32Value();

    glfwSetWindowAttrib(window, attrib, value);
}

void __glfwSetWindowPosCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (windowPosCallback == nullptr) {
        windowPosCallback = new Napi::FunctionReference();
    }

    if (info.Length() > 1 && info[0].IsFunction()) {
        windowPosCallback->Reset(info[1].As<Napi::Function>());
    } else {
        windowPosCallback->Reset();
    }

    glfwSetWindowPosCallback(window, [](GLFWwindow *window, int xpos, int ypos) {
        if (windowPosCallback == nullptr || windowPosCallback->IsEmpty()) {
            return;
        }

        Napi::Env env = windowPosCallback->Env();
        Napi::HandleScope scope(env);

        Napi::External<GLFWwindow> windowObject = Napi::External<GLFWwindow>::New(env, window);

        windowPosCallback->Call({ windowObject, Napi::Number::New(env, xpos), Napi::Number::New(env, ypos) });
    });
}

void __glfwSetWindowSizeCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (windowSizeCallback == nullptr) {
        windowSizeCallback = new Napi::FunctionReference();
    }

    if (info.Length() > 1 && info[0].IsFunction()) {
        windowSizeCallback->Reset(info[1].As<Napi::Function>());
    } else {
        windowSizeCallback->Reset();
    }

    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        if (windowSizeCallback == nullptr || windowSizeCallback->IsEmpty()) {
            return;
        }

        Napi::Env env = windowSizeCallback->Env();
        Napi::HandleScope scope(env);

        Napi::External<GLFWwindow> windowObject = Napi::External<GLFWwindow>::New(env, window);

        windowSizeCallback->Call({ windowObject, Napi::Number::New(env, width), Napi::Number::New(env, height) });
    });
}

void __glfwSetWindowCloseCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (windowCloseCallback == nullptr) {
        windowCloseCallback = new Napi::FunctionReference();
    }

    if (info.Length() > 1 && info[0].IsFunction()) {
        windowCloseCallback->Reset(info[1].As<Napi::Function>());
    } else {
        windowCloseCallback->Reset();
    }

    glfwSetWindowCloseCallback(window, [](GLFWwindow *window) {
        if (windowCloseCallback == nullptr || windowCloseCallback->IsEmpty()) {
            return;
        }

        Napi::Env env = windowCloseCallback->Env();
        Napi::HandleScope scope(env);

        Napi::External<GLFWwindow> windowObject = Napi::External<GLFWwindow>::New(env, window);

        windowCloseCallback->Call({ windowObject });
    });
}

void __glfwSetWindowRefreshCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (windowRefreshCallback == nullptr) {
        windowRefreshCallback = new Napi::FunctionReference();
    }

    if (info.Length() > 1 && info[0].IsFunction()) {
        windowRefreshCallback->Reset(info[1].As<Napi::Function>());
    } else {
        windowRefreshCallback->Reset();
    }

    glfwSetWindowRefreshCallback(window, [](GLFWwindow *window) {
        if (windowRefreshCallback == nullptr || windowRefreshCallback->IsEmpty()) {
            return;
        }

        Napi::Env env = windowRefreshCallback->Env();
        Napi::HandleScope scope(env);

        Napi::External<GLFWwindow> windowObject = Napi::External<GLFWwindow>::New(env, window);

        windowRefreshCallback->Call({ windowObject });
    });
}

void __glfwSetWindowFocusCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (windowFocusCallback == nullptr) {
        windowFocusCallback = new Napi::FunctionReference();
    }

    if (info.Length() > 1 && info[0].IsFunction()) {
        windowFocusCallback->Reset(info[1].As<Napi::Function>());
    } else {
        windowFocusCallback->Reset();
    }

    glfwSetWindowFocusCallback(window, [](GLFWwindow *window, int focused) {
        if (windowFocusCallback == nullptr || windowFocusCallback->IsEmpty()) {
            return;
        }

        Napi::Env env = windowFocusCallback->Env();
        Napi::HandleScope scope(env);

        Napi::External<GLFWwindow> windowObject = Napi::External<GLFWwindow>::New(env, window);

        windowFocusCallback->Call({ windowObject, Napi::Boolean::New(env, focused) });
    });
}

void __glfwSetWindowIconifyCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (windowIconifyCallback == nullptr) {
        windowIconifyCallback = new Napi::FunctionReference();
    }

    if (info.Length() > 1 && info[0].IsFunction()) {
        windowIconifyCallback->Reset(info[1].As<Napi::Function>());
    } else {
        windowIconifyCallback->Reset();
    }

    glfwSetWindowIconifyCallback(window, [](GLFWwindow *window, int iconified) {
        if (windowIconifyCallback == nullptr || windowIconifyCallback->IsEmpty()) {
            return;
        }

        Napi::Env env = windowIconifyCallback->Env();
        Napi::HandleScope scope(env);

        Napi::External<GLFWwindow> windowObject = Napi::External<GLFWwindow>::New(env, window);

        windowIconifyCallback->Call({ windowObject, Napi::Boolean::New(env, iconified) });
    });
}

void __glfwSetWindowMaximizeCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (windowMaximizeCallback == nullptr) {
        windowMaximizeCallback = new Napi::FunctionReference();
    }

    if (info.Length() > 1 && info[0].IsFunction()) {
        windowMaximizeCallback->Reset(info[1].As<Napi::Function>());
    } else {
        windowMaximizeCallback->Reset();
    }

    glfwSetWindowMaximizeCallback(window, [](GLFWwindow *window, int maximized) {
        if (windowMaximizeCallback == nullptr || windowMaximizeCallback->IsEmpty()) {
            return;
        }

        Napi::Env env = windowMaximizeCallback->Env();
        Napi::HandleScope scope(env);

        Napi::External<GLFWwindow> windowObject = Napi::External<GLFWwindow>::New(env, window);

        windowMaximizeCallback->Call({ windowObject, Napi::Boolean::New(env, maximized) });
    });
}

void __glfwSetFramebufferSizeCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (info[1].IsFunction()) {
        Napi::FunctionReference *ref = new Napi::FunctionReference();
        *ref = Napi::Persistent(info[1].As<Napi::Function>());
        framebufferSizeCallbacks[window] = ref;
    } else {
        delete framebufferSizeCallbacks[window];
    }

    glfwSetFramebufferSizeCallback(window, [] (GLFWwindow *window, int width, int height) {
        if (framebufferSizeCallbacks.find(window) != framebufferSizeCallbacks.end()) {
            Napi::FunctionReference *callback = framebufferSizeCallbacks[window];
            Napi::Env env = callback->Env();
            Napi::HandleScope scope(env);

            if (callback->IsEmpty()) {
                return;
            }

            Napi::External<GLFWwindow> windowRef = Napi::External<GLFWwindow>::New(env, window);
            Napi::Number widthNum = Napi::Number::New(env, width);
            Napi::Number heightNum = Napi::Number::New(env, height);

            callback->Call({ windowRef, widthNum, heightNum });
        }
    });
}

void __glfwSetWindowContentScaleCallback(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    if (windowContentScaleCallback == nullptr) {
        windowContentScaleCallback = new Napi::FunctionReference();
    }

    if (info.Length() > 1 && info[0].IsFunction()) {
        windowContentScaleCallback->Reset(info[1].As<Napi::Function>());
    } else {
        windowContentScaleCallback->Reset();
    }

    glfwSetWindowContentScaleCallback(window, [](GLFWwindow *window, float xscale, float yscale) {
        if (windowContentScaleCallback == nullptr || windowContentScaleCallback->IsEmpty()) {
            return;
        }

        Napi::Env env = windowContentScaleCallback->Env();
        Napi::HandleScope scope(env);

        Napi::External<GLFWwindow> windowObject = Napi::External<GLFWwindow>::New(env, window);

        windowContentScaleCallback->Call({ windowObject, Napi::Number::New(env, xscale), Napi::Number::New(env, yscale) });
    });
}

void __glfwPollEvents(const Napi::CallbackInfo &info) {
    glfwPollEvents();
}

void __glfwWaitEvents(const Napi::CallbackInfo &info) {
    glfwWaitEvents();
}

void __glfwWaitEventsTimeout(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    double timeout = info[0].As<Napi::Number>().DoubleValue();

    glfwWaitEventsTimeout(timeout);
}

void __glfwPostEmptyEvent(const Napi::CallbackInfo &info) {
    glfwPostEmptyEvent();
}

void __glfwSwapBuffers(const Napi::CallbackInfo &info) {
    GLFWwindow *window = info[0].As<Napi::External<GLFWwindow>>().Data();

    glfwSwapBuffers(window);
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
    // Context functions
    exports.Set("glfwMakeContextCurrent", Napi::Function::New(env, __glfwMakeContextCurrent));
    exports.Set("glfwGetCurrentContext", Napi::Function::New(env, __glfwGetCurrentContext));
    exports.Set("glfwSwapInterval", Napi::Function::New(env, __glfwSwapInterval));
    exports.Set("glfwExtensionSupported", Napi::Function::New(env, __glfwExtensionSupported));
    
    // Initialization, version and error functions
    exports.Set("glfwInit", Napi::Function::New(env, __glfwInit));
    exports.Set("glfwTerminate", Napi::Function::New(env, __glfwTerminate));
    exports.Set("glfwInitHint", Napi::Function::New(env, __glfwInitHint));
    exports.Set("glfwGetVersion", Napi::Function::New(env, __glfwGetVersion));
    exports.Set("glfwGetVersionString", Napi::Function::New(env, __glfwGetVersionString));
    exports.Set("glfwGetError", Napi::Function::New(env, __glfwGetError));
    exports.Set("glfwSetErrorCallback", Napi::Function::New(env, __glfwSetErrorCallback));

    // Input functions
    exports.Set("glfwGetInputMode", Napi::Function::New(env, __glfwGetInputMode));
    exports.Set("glfwSetInputMode", Napi::Function::New(env, __glfwSetInputMode));
    exports.Set("glfwRawMouseMotionSupported", Napi::Function::New(env, __glfwRawMouseMotionSupported));
    exports.Set("glfwGetKeyName", Napi::Function::New(env, __glfwGetKeyName));
    exports.Set("glfwGetKeyScancode", Napi::Function::New(env, __glfwGetKeyScancode));
    exports.Set("glfwGetKey", Napi::Function::New(env, __glfwGetKey));
    exports.Set("glfwGetMouseButton", Napi::Function::New(env, __glfwGetMouseButton));
    exports.Set("glfwGetCursorPos", Napi::Function::New(env, __glfwGetCursorPos));
    exports.Set("glfwSetCursorPos", Napi::Function::New(env, __glfwSetCursorPos));
    exports.Set("glfwCreateCursor", Napi::Function::New(env, __glfwCreateCursor));
    exports.Set("glfwCreateStandardCursor", Napi::Function::New(env, __glfwCreateStandardCursor));
    exports.Set("glfwDestroyCursor", Napi::Function::New(env, __glfwDestroyCursor));
    exports.Set("glfwSetCursor", Napi::Function::New(env, __glfwSetCursor));
    exports.Set("glfwSetKeyCallback", Napi::Function::New(env, __glfwSetKeyCallback));
    exports.Set("glfwSetCharCallback", Napi::Function::New(env, __glfwSetCharCallback));
    exports.Set("glfwSetCharModsCallback", Napi::Function::New(env, __glfwSetCharModsCallback));
    exports.Set("glfwSetMouseButtonCallback", Napi::Function::New(env, __glfwSetMouseButtonCallback));
    exports.Set("glfwSetCursorPosCallback", Napi::Function::New(env, __glfwSetCursorPosCallback));
    exports.Set("glfwSetCursorEnterCallback", Napi::Function::New(env, __glfwSetCursorEnterCallback));
    exports.Set("glfwSetScrollCallback", Napi::Function::New(env, __glfwSetScrollCallback));
    exports.Set("glfwSetDropCallback", Napi::Function::New(env, __glfwSetDropCallback));
    exports.Set("glfwJoystickPresent", Napi::Function::New(env, __glfwJoystickPresent));
    exports.Set("glfwGetJoystickAxes", Napi::Function::New(env, __glfwGetJoystickAxes));
    exports.Set("glfwGetJoystickButtons", Napi::Function::New(env, __glfwGetJoystickButtons));
    exports.Set("glfwGetJoystickHats", Napi::Function::New(env, __glfwGetJoystickHats));
    exports.Set("glfwGetJoystickName", Napi::Function::New(env, __glfwGetJoystickName));
    exports.Set("glfwGetJoystickGUID", Napi::Function::New(env, __glfwGetJoystickGUID));
    exports.Set("glfwJoystickIsGamepad", Napi::Function::New(env, __glfwJoystickIsGamepad));
    exports.Set("glfwSetJoystickCallback", Napi::Function::New(env, __glfwSetJoystickCallback));
    exports.Set("glfwUpdateGamepadMappings", Napi::Function::New(env, __glfwUpdateGamepadMappings));
    exports.Set("glfwGetGamepadName", Napi::Function::New(env, __glfwGetGamepadName));
    exports.Set("glfwGetGamepadState", Napi::Function::New(env, __glfwGetGamepadState));
    exports.Set("glfwSetClipboardString", Napi::Function::New(env, __glfwSetClipboardString));
    exports.Set("glfwGetClipboardString", Napi::Function::New(env, __glfwGetClipboardString));
    exports.Set("glfwGetTime", Napi::Function::New(env, __glfwGetTime));
    exports.Set("glfwSetTime", Napi::Function::New(env, __glfwSetTime));
    exports.Set("glfwGetTimerValue", Napi::Function::New(env, __glfwGetTimerValue));
    exports.Set("glfwGetTimerFrequency", Napi::Function::New(env, __glfwGetTimerFrequency));

    // Monitor functions
    exports.Set("glfwGetMonitors", Napi::Function::New(env, __glfwGetMonitors));
    exports.Set("glfwGetPrimaryMonitor", Napi::Function::New(env, __glfwGetPrimaryMonitor));
    exports.Set("glfwGetMonitorPos", Napi::Function::New(env, __glfwGetMonitorPos));
    exports.Set("glfwGetMonitorWorkarea", Napi::Function::New(env, __glfwGetMonitorWorkarea));
    exports.Set("glfwGetMonitorPhysicalSize", Napi::Function::New(env, __glfwGetMonitorPhysicalSize));
    exports.Set("glfwGetMonitorContentScale", Napi::Function::New(env, __glfwGetMonitorContentScale));
    exports.Set("glfwGetMonitorName", Napi::Function::New(env, __glfwGetMonitorName));
    exports.Set("glfwSetMonitorCallback", Napi::Function::New(env, __glfwSetMonitorCallback));
    exports.Set("glfwGetVideoModes", Napi::Function::New(env, __glfwGetVideoModes));
    exports.Set("glfwGetVideoMode", Napi::Function::New(env, __glfwGetVideoMode));
    exports.Set("glfwSetGamma", Napi::Function::New(env, __glfwSetGamma));
    exports.Set("glfwGetGammaRamp", Napi::Function::New(env, __glfwGetGammaRamp));
    exports.Set("glfwSetGammaRamp", Napi::Function::New(env, __glfwSetGammaRamp));

    // Window functions
    exports.Set("glfwDefaultWindowHints", Napi::Function::New(env, __glfwDefaultWindowHints));
    exports.Set("glfwWindowHint", Napi::Function::New(env, __glfwWindowHint));
    exports.Set("glfwWindowHintString", Napi::Function::New(env, __glfwWindowHintString));
    exports.Set("glfwCreateWindow", Napi::Function::New(env, __glfwCreateWindow));
    exports.Set("glfwDestroyWindow", Napi::Function::New(env, __glfwDestroyWindow));
    exports.Set("glfwWindowShouldClose", Napi::Function::New(env, __glfwWindowShouldClose));
    exports.Set("glfwSetWindowShouldClose", Napi::Function::New(env, __glfwSetWindowShouldClose));
    exports.Set("glfwSetWindowTitle", Napi::Function::New(env, __glfwSetWindowTitle));
    exports.Set("glfwSetWindowIcon", Napi::Function::New(env, __glfwSetWindowIcon));
    exports.Set("glfwGetWindowPos", Napi::Function::New(env, __glfwGetWindowPos));
    exports.Set("glfwSetWindowPos", Napi::Function::New(env, __glfwSetWindowPos));
    exports.Set("glfwGetWindowSize", Napi::Function::New(env, __glfwGetWindowSize));
    exports.Set("glfwSetWindowSizeLimits", Napi::Function::New(env, __glfwSetWindowSizeLimits));
    exports.Set("glfwSetWindowAspectRatio", Napi::Function::New(env, __glfwSetWindowAspectRatio));
    exports.Set("glfwSetWindowSize", Napi::Function::New(env, __glfwSetWindowSize));
    exports.Set("glfwGetFramebufferSize", Napi::Function::New(env, __glfwGetFramebufferSize));
    exports.Set("glfwGetWindowFrameSize", Napi::Function::New(env, __glfwGetWindowFrameSize));
    exports.Set("glfwGetWindowContentScale", Napi::Function::New(env, __glfwGetWindowContentScale));
    exports.Set("glfwGetWindowOpacity", Napi::Function::New(env, __glfwGetWindowOpacity));
    exports.Set("glfwSetWindowOpacity", Napi::Function::New(env, __glfwSetWindowOpacity));
    exports.Set("glfwIconifyWindow", Napi::Function::New(env, __glfwIconifyWindow));
    exports.Set("glfwRestoreWindow", Napi::Function::New(env, __glfwRestoreWindow));
    exports.Set("glfwMaximizeWindow", Napi::Function::New(env, __glfwMaximizeWindow));
    exports.Set("glfwShowWindow", Napi::Function::New(env, __glfwShowWindow));
    exports.Set("glfwHideWindow", Napi::Function::New(env, __glfwHideWindow));
    exports.Set("glfwFocusWindow", Napi::Function::New(env, __glfwFocusWindow));
    exports.Set("glfwRequestWindowAttention", Napi::Function::New(env, __glfwRequestWindowAttention));
    exports.Set("glfwGetWindowMonitor", Napi::Function::New(env, __glfwGetWindowMonitor));
    exports.Set("glfwSetWindowMonitor", Napi::Function::New(env, __glfwSetWindowMonitor));
    exports.Set("glfwGetWindowAttrib", Napi::Function::New(env, __glfwGetWindowAttrib));
    exports.Set("glfwSetWindowAttrib", Napi::Function::New(env, __glfwSetWindowAttrib));
    exports.Set("glfwSetWindowPosCallback", Napi::Function::New(env, __glfwSetWindowPosCallback));
    exports.Set("glfwSetWindowSizeCallback", Napi::Function::New(env, __glfwSetWindowSizeCallback));
    exports.Set("glfwSetWindowCloseCallback", Napi::Function::New(env, __glfwSetWindowCloseCallback));
    exports.Set("glfwSetWindowRefreshCallback", Napi::Function::New(env, __glfwSetWindowRefreshCallback));
    exports.Set("glfwSetWindowFocusCallback", Napi::Function::New(env, __glfwSetWindowFocusCallback));
    exports.Set("glfwSetWindowIconifyCallback", Napi::Function::New(env, __glfwSetWindowIconifyCallback));
    exports.Set("glfwSetWindowMaximizeCallback", Napi::Function::New(env, __glfwSetWindowMaximizeCallback));
    exports.Set("glfwSetFramebufferSizeCallback", Napi::Function::New(env, __glfwSetFramebufferSizeCallback));
    exports.Set("glfwSetWindowContentScaleCallback", Napi::Function::New(env, __glfwSetWindowContentScaleCallback));
    exports.Set("glfwPollEvents", Napi::Function::New(env, __glfwPollEvents));
    exports.Set("glfwWaitEvents", Napi::Function::New(env, __glfwWaitEvents));
    exports.Set("glfwWaitEventsTimeout", Napi::Function::New(env, __glfwWaitEventsTimeout));
    exports.Set("glfwPostEmptyEvent", Napi::Function::New(env, __glfwPostEmptyEvent));
    exports.Set("glfwSwapBuffers", Napi::Function::New(env, __glfwSwapBuffers));

    return exports;
}


NODE_API_MODULE(NODE_GYP_MODULE_NAME, init);