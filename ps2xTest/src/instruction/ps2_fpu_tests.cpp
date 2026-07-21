#include "MiniTest.h"
#include "ps2_runtime.h"
#include "ps2_runtime_macros.h"
#include <limits>

void register_ps2_fpu_inst_tests() {
    MiniTest::Case("FPU Instruction Tests", [](TestCase &tc)
                   {
    // FPU_SET_ACC
    tc.Run("FPU_SET_ACC - basic test", [](TestCase &t) {
        R5900Context ctx{};
        constexpr float expected = std::numeric_limits<float>::max();
        
        FPU_SET_ACC(&ctx, expected);

        t.Equals(ctx.f_acc, expected, "ctx.f_acc should equal expected");
    });
    // // ADD.S
    tc.Run("ADD.S - basic test", [](TestCase &t) {
        constexpr float a = 100.0;
        constexpr float b = -50.0;
        constexpr float expected = a + b;

        constexpr float result = FPU_ADD_S(a, b);

        t.Equals(result, expected, "result should equal expected");
    });
    // tc.Run("ADD.S - under/overflow test", [](TestCase &t) {
    //     constexpr float a = INT32_MAX;
    //     constexpr float b = 1.0;

    //     constexpr float result = FPU_ADD_S(a, b);

    //     t.Equals();
    // });
    // // SUB.S
    tc.Run("SUB.S - basic test", [](TestCase &t) {
        constexpr float a = 100.0;
        constexpr float b = 50.0;
        constexpr float expected = a - b;

        constexpr float result = FPU_SUB_S(a, b);

        t.Equals(result, expected, "result should equal expected");
    });
    // tc.Run("SUB.S - under/overflow test", [](TestCase &t) {
    //     constexpr float a = INT32_MAX;
    //     constexpr float b = -1.0;
    //     constexpr float c = INT32_MIN;
    //     constexpr float d = 1.0; 

    //     constexpr float expected_ab = INT32_MAX;
    //     constexpr uint8_t flags_ab = 
    //     constexpr float expected_cd = INT32_MIN;

    //     constexpr float result = FPU_SUB_S(a, b);

    //     t.Equals();
    //     t.Equals();

    // }); 
    // MUL.S
    tc.Run("MUL.S - basic test", [](TestCase &t) {
        constexpr float a = 100.0;
        constexpr float b = 50.0;
        constexpr float expected = a * b;

        constexpr float result = FPU_MUL_S(a, b);

        t.Equals(result, expected, "FPU_MUL_S result should equal a * b");
    });
    tc.Run("MUL.S - under/overflow test", [](TestCase &t) {
        R5900Context ctx{};
        constexpr float a = std::numeric_limits<float>::max();
        constexpr float b = 2.0;
        constexpr float overflow_expected = a * b;

        constexpr float overflow_result = FPU_MUL_S(a, b);

        constexpr float c = std::numeric_limits<float>::min();
        constexpr float d = -2.0;
        constexpr float underflow_expected = c * d;

        constexpr float underflow_result = FPU_MUL_S(c, d);

        t.Equals(overflow_result, overflow_expected, );
        t.Equals();

        t.Equals(underflow_result, /* TODO */);
        t.Equals(/* TODO */);
    });
    // DIV.S
    tc.Run("DIV.S - basic test", [](TestCase &t) {
        constexpr float a = 100.0;
        constexpr float b = 25.0;
        constexpr float expected = a / b;

        constexpr float result = FPU_DIV_S(a, b);

        t.Equals(result, expected, "result should equal expected");
    });
    tc.Run("DIV.S - divide by zero", [](TestCase &t) {
        constexpr float a = 100.0;
        constexpr float b = 0.0;

        constexpr float result = FPU_DIV_S(a, b);

        t.Equals(/* TODO */);
        t.Equals(/* TODO */);
    });
    tc.Run("DIV.S - both operands zero", [](TestCase &t) {
        constexpr float a = 0.0;
        constexpr float b = 0.0;
        constexpr float expected = std::numeric_limits<float>::max();

        constexpr float result = FPU_DIV_S(a, b);
    });
    tc.Run("DIV.S - exponent under/overflow", [](TestCase &t) {
        constexpr float a = /* TODO */;
        constexpr float b = /* TODO */;
        constexpr float expected = /* TODO */;

        constexpr float result = /* TODO*/;

        t.Equals(/* TODO */);
        t.Equals(/* TODO */);

    });
    // // SQRT.S
    // tc.Run("SQRT.S - basic test", [](TestCase &t) {

    // });
    // tc.Run("SQRT.S - negative zero", [](TestCase &t) {

    // });
    // tc.Run("SQRT.S - less than zero", [](TestCase &t) {

    // });
    // ABS.S
    tc.Run("ABS.S - basic test", [](TestCase &t) {
        constexpr float a = 100.0;
        constexpr float b = -100.0;
        constexpr float expected = a;
        
        constexpr float pos_result = FPU_ABS_S(a);
        constexpr float neg_result = FPU_ABS_S(b);

        t.Equals(pos_result, expected, "result should equal a");
        t.Equals(neg_result, expected, "result should equal a");
    });
    tc.Run("ABS.S - zeros OU flags", [](TestCase &t) {
        R5900Context ctx{};
        constexpr float a = 0.0;
        constexpr uint8_t expected_flags = 0;
        
        // Set both Overflow and Underflow flags to 1
        ctx.fcr31 |= (0b11 << 15);

        constexpr float result = FPU_ABS_S(a); 

        t.Equals(ctx.fcr31, expected_flags, "OU flags should be set to zero");
    });
    // // MOV.S
    tc.Run("MOV.S - basic test", [](TestCase &t) {
        R5900Context ctx{};
        constexpr uint8_t regA = 1;
        constexpr uint8_t regB = 2;
        constexpr float expected = 500.0;
    
        // Set register 1 to expected
        ctx.f[regA] = expected;

        ctx.f[regB] = FPU_MOV_S(ctx.f[regA]);

        t.Equals(ctx.f[regA], ctx.f[regB], "regA and regB should be equal");
    });
    // // NEG.S
    tc.Run("NEG.S - basic test", [](TestCase &t) {
        constexpr float a = 100.0;
        constexpr float expected = -a;

        constexpr float result = FPU_NEG_S(a);
        
        t.Equals(result, expected, "result should equal negated value");
    });
    tc.Run("NEG.S - zeroes OU flags", [](TestCase &t) {
        R5900Context ctx{};
        constexpr float a = 100.0;
        constexpr uint32_t expected_flags = 0;

        // Set both Overflow and Underflow flags to 1
        ctx.fcr31 |= (0b11 << 15);

        constexpr float result = FPU_NEG_S(a);

        t.Equals(ctx.fcr31, expected_flags, "OU flags should be set to zero");
    });
    // // MULA.S
    // tc.Run("MULA.S - basic test", [](TestCase &t) {
    //     R5900Context ctx;
    //     constexpr float a = 100.0;
    //     constexpr float b = -100.0;
    //     constexpr float expected = a * b;

    //     constexpr float result = FPU_SET_ACC(&ctx, FPU_MULA_S(a, b));

    //     t.Equals(ctx.f_acc, expected, "Accumulator register should equal expected");
    // });
    // tc.Run("MULA.S - underflow/overflow test", [](TestCase &t) {

    // });
    // // ROUND.L.S
    // tc.Run("ROUND.L.S - basic test", [](TestCase &t) {

    // });
    // // TRUNC.L.S
    // tc.Run("TRUNC.L.S - basic test", [](TestCase &t) {

    // });
    // // CEIL.L.S
    // tc.Run("MULA.S - basic test", [](TestCase &t) {

    // });
    // // FLOOR.L.S
    // tc.Run("MULA.S - basic test", [](TestCase &t) {

    // });
    // // ROUND.W.S
    // tc.Run("MULA.S - basic test", [](TestCase &t) {

    // });
    // // TRUNC.W.S
    // tc.Run("MULA.S - basic test", [](TestCase &t) {

    // });
    // // FLOOR.W.S
    // tc.Run("MULA.S - basic test", [](TestCase &t) {

    // });
    // CVT.S.W
    tc.Run("MULA.S - basic test", [](TestCase &t) {

    });
    // CVT.S.L
    tc.Run("MULA.S - basic test", [](TestCase &t) {

    });
    // CVT.W.S
    tc.Run("CVT.W.S - basic test", [](TestCase &t) {

    });
    tc.Run("CVT.W.S - clamping", [](TestCase &t) {

    });
    tc.Run("CVT.W.S - operand zero", [](TestCase &t) {

    });
    // CVT.S.L
    tc.Run("CVT.S.L - basic test", [](TestCase &t) {

    });
    // C.F.S
    tc.Run("C.F.S - basic test", [](TestCase &t) {
        R5900Context ctx{};
        constexpr float a = 100;
        constexpr float b = 99;
        constexpr uint32_t expected_flags = 0;

        // Set the Comparsion Flag
        ctx.fcr31 |= (0b1 << 23);

        FPU_C_F_S(a, b);

        t.Equals(ctx.fcr31, expected_flags, "FCR31 C flag should be zero");
    });
    // C.UN.S
    tc.Run("C.UN.S - basic test", [](TestCase &t) {
        R5900Context ctx{};
        constexpr float a = 100;
        constexpr float b = 99;

        // Set the TODO flag
        ctx.fcr31 |= (0b1 << TODO);

        FPU_C_UN_S(a, b);
        
        t.Equals(ctx.fcr31, expected, "TODO");
    });
    // C.EQ.S
    tc.Run("C.EQ.S - basic test", [](TestCase &t) {
        R5900Context ctx{};
        constexpr float a = 100;
        constexpr float b = 100;
        constexpr uint8_t expected = (0b1 << 23);

        constexpr uint8_t result = FPU_C_EQ_S(a, b);

        t.Equals(ctx.fcr31, expected, "Expected FCR31 C flag to be set to 1");
    });
    // // C.UEQ.S
    // tc.Run("C.UEQ.S - basic test", [](TestCase &t) {

    // });
    // // C.OLT.S
    // tc.Run("C.OLT.S - basic test", [](TestCase &t) {

    // });
    // // C.ULT.S
    // tc.Run("C.ULT.S - basic test", [](TestCase &t) {

    // });
    // // C.SF.S
    // tc.Run("C.SF.S - basic test", [](TestCase &t) {

    // });
    // // C.NGLE.S
    // tc.Run("C.NGLE.S - basic test", [](TestCase &t) {

    // });
    // // C.NGL.S
    // tc.Run("C.NGL.S - basic test", [](TestCase &t) {

    // });
    // C.LT.S
    tc.Run("C.LT.S - basic test", [](TestCase &t) {
        R5900Context

    });
    // // C.NGE.S
    // tc.Run("C.NGE.S - basic test", [](TestCase &t) {

    // });
    // // C.LE.S
    // tc.Run("C.LE.S - basic test", [](TestCase &t) {

    // });
    // // C.NGT.S
    // tc.Run("C.NGT.S - basic test", [](TestCase &t) {

    // });
});
}

