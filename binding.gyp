{
    "targets": [
        {
            "target_name": "glfw",
            "sources": [
                "src/bindings.cc"
            ],
            "include_dirs": [
                "<!(node -p \"require('node-addon-api').include_dir\")",
                "<(module_root_dir)/include"
            ],
            "defines": [
                "_HAS_EXCEPTIONS=1",
                "GLFW_INCLUDE_NONE"
            ],
            "cflags!": [
                "-fno-exceptions"
            ],
            "cflags_cc!": [
                "-fno-exceptions"
            ],
            "conditions": [
                ["OS=='win'",
                {
                    "defines": [
                        "_WIN32",
                    ],
                    "libraries": [
                        "<(module_root_dir)/lib/win32/glfw3dll.lib",
                        "opengl32.lib",
                    ],
                    "copies": [{
                        "destination": "<(PRODUCT_DIR)",
                        "files": [
                            "<(module_root_dir)/lib/win32/glfw3.dll"
                        ]
                    }],
                    "msvs_settings": {
                        "VCCLCompilerTool": {
                            "ExceptionHandling": 1,
                            "AdditionalOptions": [
                                "/O2",
                                "/Oy",
                                "/GL",
                                "/GF",
                                "/Gm-",
                                "/EHsc",
                                "/MT",
                                "/GS",
                                "/Gy",
                                "/GR-",
                                "/Gd"
                            ]
                        },
                        "VCLinkerTool": {
                            "AdditionalOptions": [
                                "/OPT:REF",
                                "/OPT:ICF",
                                "/LTCG"
                            ]
                        }
                    }
                }],
                ["OS=='mac'", {
                    "defines": [
                        "__APPLE__"
                    ],
                    "conditions": [
                        ["OS_ARCH=='x64'", {
                            "libraries": [
                                "<(module_root_dir)/lib/darwin/x86_64/libglfw.a"
                            ],
                        }],
                        ["OS_ARCH=='arm'", {
                            "libraries": [
                                "<(module_root_dir)/lib/darwin/arm64/libglfw3.a"
                            ]
                        }]
                    ]
                }]
            ]
        }
    ]
}