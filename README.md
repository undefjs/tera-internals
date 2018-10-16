# tera-internals: ToDo List

## Main (Node)
* **process.cpp** - fix getting 32bits kernel32-LoadLibraryA so 64bits node is able to injects into 32bits tera

## Guard (DLL)
* **socket.cpp** - be multithread and keep the listener socket open, and use new sockets for accepted clients
* **dllmain.cpp** - better RPC parser and a JSON library
