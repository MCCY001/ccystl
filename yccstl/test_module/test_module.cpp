// external headers
#include "yccstl/test_module/test_module_header_1.h"
// internal headers
#include "calculation/add.h"
#include "calculation/mult.h"

int OutsideAdd(int a, int b, int c) {
    return SimplyAdd(a, b) + c;
}

float OutsideMult(float a, float b, float c) {
    return SimplyMult(a, b) * c;
}