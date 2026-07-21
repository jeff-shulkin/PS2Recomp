#include "MiniTest.h"
#include "ps2runtime/ps2_runtime.h"
#include "ps2runtime/ps2_runtime_macros.h"
#include <immintrin.h>
#include <smmintrin.h>

__m128i make_s32x4(int32_t a, int32_t b, int32_t c, int32_t d) {
    return _mm_set_epi32((int32_t)d, (int32_t)c, (int32_t)b, (int32_t)a);
}

void register_ee_inst_tests() {
    MiniTest::Case("FPU Instruction Tests", [](TestCase &tc)
                   {
    // PADDSW
    tc.Run("PADDSW - basic test", [](TestCase &t) {
        const __m128i a = make_s32x4(
            30,
            50,
            -20,
            -50,
        );
        const __m128i b = make_s32x4(
            10,
            -10,
            30,
            -50
        );
        const __m128i expected = make_s32x4(
            30 + 10,
            50 + -10,
            -20 + 30,
            -50 + -50
        );

        __m128i result = PS2_PADDSW(a, b);

        expect_s32x4_eq(t, "PADDSW edge non-overflow", r, {
            INT32_MAX,
            INT32_MIN,
            INT32_MAX - 1,
            INT32_MIN + 1
        });
    })
    tc.Run("PADDSW - min/max saturation", [](TestCase &t) {
        const __m128i a = make_s32x4(
            INT32_MAX,
            INT32_MIN,
            INT32_MAX,
            INT32_MIN
        );
        const __m128i b = make_s32x4(
            0,
            0,
            1,
            -1
        );
        const __m128i expected = make_s32x4(
            INT32_MAX,
            INT32_MIN,
            INT32_MAX,
            INT32_MAX
        );

        __m128i result = PS2_PADDSW(a, b);

        expect_s32x4_eq(t, "PADDSW edge non-overflow", r, {
            INT32_MAX,
            INT32_MIN,
            INT32_MAX - 1,
            INT32_MIN + 1
        });
    });
    // PSUBSW
    tc.Run("PSUBSW - basic test and min/max saturation", [](TestCase &t) {
        __m128i expected = make_s32x4();
    });
    tc.Run("PSUBSW - min/max saturation", [](TestCase &t) {
        __m128i expected = make_s32x4();

    }); 
    //

});
}