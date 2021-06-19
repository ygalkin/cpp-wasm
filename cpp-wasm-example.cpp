#include <string>
#include <algorithm>
#include <emscripten.h>

static std::string base64_encode(const std::string& in) {

    std::string out;

    int val = 0, valb = -6;
    for (auto c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

extern "C" {
    EMSCRIPTEN_KEEPALIVE const char* hello_wasm_str() {
        return "Hello WASM!";
    }

    EMSCRIPTEN_KEEPALIVE int EMSCRIPTEN_KEEPALIVE hello_wasm_int(int n) {
        return n;
    }

    EMSCRIPTEN_KEEPALIVE void encode_base64_string(const char* s, char* buff, size_t size) {
        if (s == nullptr || buff == nullptr || size == 0) {
            return;
        }

        auto encoded = base64_encode(s);
        strncpy(buff, encoded.c_str(), std::min(size, encoded.size()));
    }
}
