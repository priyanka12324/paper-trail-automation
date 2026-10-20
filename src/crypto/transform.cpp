#include "crypto/transform.hpp"

namespace hes {

CharClass classify(uint8_t b) {
    if ((b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z')) return CharClass::Alpha;
    if (b >= '0' && b <= '9') return CharClass::Numeric;
    return CharClass::Special;
}

namespace {
struct SpecialTable {
    uint8_t list[256];
    int index[256];
    int count = 0;
    SpecialTable() {
        for (int b = 0; b < 256; ++b) {
            if (classify(static_cast<uint8_t>(b)) == CharClass::Special) {
                index[b] = count;
                list[count++] = static_cast<uint8_t>(b);
            } else {
                index[b] = -1;
            }
        }
    }
};
const SpecialTable &specials() { static const SpecialTable t; return t; }

int rotate(int pos, uint32_t shift, int modulus, bool forward) {
    int off = static_cast<int>(shift % static_cast<uint32_t>(modulus));
    return forward ? (pos + off) % modulus : (pos - off + modulus) % modulus;
}
}

uint8_t shift_byte(uint8_t b, uint32_t shift, bool forward) {
    switch (classify(b)) {
        case CharClass::Alpha: {
            uint8_t base = (b >= 'a') ? 'a' : 'A';
            return static_cast<uint8_t>(base + rotate(b - base, shift, 26, forward));
        }
        case CharClass::Numeric:
            return static_cast<uint8_t>('0' + rotate(b - '0', shift, 10, forward));
        default: {
            const SpecialTable &t = specials();
            return t.list[rotate(t.index[b], shift, t.count, forward)];
        }
    }
}

}
