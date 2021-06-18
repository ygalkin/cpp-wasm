del out-app.*
emcc cpp-wasm-example.cpp -O3 -s WASM=1 --no-entry -o ./out-app.js -s EXPORTED_RUNTIME_METHODS="['allocateUTF8OnStack', 'UTF8ToString', 'stackSave', 'stackRestore', 'stackAlloc']" 

