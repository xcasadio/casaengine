@echo off
rem tolua++cegui -o ../lua_CEGUI.cpp -L exceptions.lua CEGUI.pkg
rem tolua++ -o ../lua_CasaEngine.cpp -L exceptions.lua CasaEngine.pkg
tolua++ -o ../lua_CasaEngine.cpp CasaEngine.pkg
pause
