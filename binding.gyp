{
  "targets": [{
    "target_name": "terainternals",
    "sources": ["src/main/process.cpp", "src/main/main.cpp"]
  },
  {
    "target_name": "teraguard",
    "type": "shared_library",
    "sources": ["src/guard/socket.cpp", "src/guard/hook.cpp", "src/guard/funcs.cpp", "src/guard/dllmain.cpp"],
    "libraries": ["ws2_32.lib"]
  }]
}
