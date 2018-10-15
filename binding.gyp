{
  "targets": [{
    "target_name": "terainternals",
    "sources": ["src/main/process.cpp", "src/main/main.cpp"]
  },
  {
    "target_name": "teraguard",
    "type": "shared_library",
    "sources": ["src/guard/socket.cpp", "src/guard/guard.cpp"],
    "libraries": ["ws2_32.lib"]
  }]
}
