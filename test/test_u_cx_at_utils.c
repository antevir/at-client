#include <string.h>
#include <stdbool.h>

#include "unity.h"
#include "u_cx_at_util.h"

/* ----------------------------------------------------------------
 * STATIC VARIABLES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * STATIC FUNCTIONS
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * TEST FUNCTIONS
 * -------------------------------------------------------------- */

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uCxAtUtilByteToHex_expectedOutput(void)
{
    char buf[3];

    uCxAtUtilByteToHex(0x00, &buf[0]);
    TEST_ASSERT_EQUAL_STRING("00", buf);
    uCxAtUtilByteToHex(0x3F, &buf[0]);
    TEST_ASSERT_EQUAL_STRING("3F", buf);
    uCxAtUtilByteToHex(0xFF, &buf[0]);
    TEST_ASSERT_EQUAL_STRING("FF", buf);
}

void test_uCxAtUtilHexToByte_withValidInput_expectOutput(void)
{
    uint8_t byte = 11;
    TEST_ASSERT_EQUAL(0, uCxAtUtilHexToByte("00", &byte));
    TEST_ASSERT_EQUAL(0x00, byte);
    TEST_ASSERT_EQUAL(0, uCxAtUtilHexToByte("0000", &byte));
    TEST_ASSERT_EQUAL(0x00, byte);
    TEST_ASSERT_EQUAL(0, uCxAtUtilHexToByte("003F", &byte));
    TEST_ASSERT_EQUAL(0x00, byte);
    TEST_ASSERT_EQUAL(0, uCxAtUtilHexToByte("3F", &byte));
    TEST_ASSERT_EQUAL(0x3f, byte);
    TEST_ASSERT_EQUAL(0, uCxAtUtilHexToByte("FF", &byte));
    TEST_ASSERT_EQUAL(0xff, byte);
}

void test_uCxAtUtilHexToByte_withInvalidInput_expectError(void)
{
    uint8_t byte;
    TEST_ASSERT_LESS_THAN(0, uCxAtUtilHexToByte("0", &byte));
    TEST_ASSERT_LESS_THAN(0, uCxAtUtilHexToByte(" ", &byte));
    TEST_ASSERT_LESS_THAN(0, uCxAtUtilHexToByte("0x00", &byte));
    TEST_ASSERT_LESS_THAN(0, uCxAtUtilHexToByte("x", &byte));
}

void test_uCxAtUtilFindParamEnd_withValidInput_expectOutput(void)
{
    char testData[64];

    strcpy(testData, "123");
    TEST_ASSERT_EQUAL(&testData[0] + strlen("123"), uCxAtUtilFindParamEnd(testData));

    strcpy(testData, "123,");
    TEST_ASSERT_EQUAL(&testData[0] + strlen("123"), uCxAtUtilFindParamEnd(testData));

    strcpy(testData, "\"stringparam\",123");
    TEST_ASSERT_EQUAL(&testData[0] + strlen("\"stringparam\""), uCxAtUtilFindParamEnd(testData));

    strcpy(testData, "\"string, with comma\",123");
    TEST_ASSERT_EQUAL(&testData[0] + strlen("\"string, with comma\""), uCxAtUtilFindParamEnd(testData));

    strcpy(testData, "\"string, with comma\"");
    TEST_ASSERT_EQUAL(&testData[0] + strlen("\"string, with comma\""), uCxAtUtilFindParamEnd(testData));

    strcpy(testData, "\"string with esc \\\" \",123");
    TEST_ASSERT_EQUAL(&testData[0] + strlen("\"string with esc \\\" \""), uCxAtUtilFindParamEnd(testData));

    strcpy(testData, "string with escaped comma \\, ,123");
    TEST_ASSERT_EQUAL(&testData[0] + strlen("string with escaped comma \\, "), uCxAtUtilFindParamEnd(testData));

    strcpy(testData, ",123");
    TEST_ASSERT_EQUAL(&testData[0], uCxAtUtilFindParamEnd(testData));
}

void test_uCxAtUtilFindParamEnd_withInvalidInput_expectNull(void)
{
    TEST_ASSERT_EQUAL(NULL, uCxAtUtilFindParamEnd("\"missing end quote"));
    TEST_ASSERT_EQUAL(NULL, uCxAtUtilFindParamEnd("missing escape char\\"));
}


void test_uCxAtUtilParseParamsF_withValidInput_expectParsedParams(void)
{
    char *pStr;
    int32_t digit;
    char testData[64];

    strcpy(testData, "abc,123");
    TEST_ASSERT_EQUAL(2, uCxAtUtilParseParamsF(testData, "sd", &pStr, &digit, U_CX_AT_UTIL_PARAM_LAST));
    TEST_ASSERT_EQUAL_STRING("abc", pStr);
    TEST_ASSERT_EQUAL(123, digit);

    strcpy(testData, "\"def\",456");
    TEST_ASSERT_EQUAL(2, uCxAtUtilParseParamsF(testData, "sd", &pStr, &digit, U_CX_AT_UTIL_PARAM_LAST));
    TEST_ASSERT_EQUAL_STRING("def", pStr);
    TEST_ASSERT_EQUAL(456, digit);

    strcpy(testData, "\"\",789");
    TEST_ASSERT_EQUAL(2, uCxAtUtilParseParamsF(testData, "sd", &pStr, &digit, U_CX_AT_UTIL_PARAM_LAST));
    TEST_ASSERT_EQUAL_STRING("", pStr);
    TEST_ASSERT_EQUAL(789, digit);

    strcpy(testData, ",123");
    TEST_ASSERT_EQUAL(2, uCxAtUtilParseParamsF(testData, "sd", &pStr, &digit, U_CX_AT_UTIL_PARAM_LAST));
    TEST_ASSERT_EQUAL_STRING("", pStr);
    TEST_ASSERT_EQUAL(123, digit);
}

void test_uCxAtUtilParseParamsF_withInvalidInput_expectNegativeReturnValue(void)
{
    char *pStr;
    int32_t digit;
    char testData[64];

    strcpy(testData, "123,\"missing quote");
    TEST_ASSERT_LESS_THAN(0, uCxAtUtilParseParamsF(testData, "ds", &digit, &pStr, U_CX_AT_UTIL_PARAM_LAST));

    strcpy(testData, "123,missing esc char\\");
    TEST_ASSERT_LESS_THAN(0, uCxAtUtilParseParamsF(testData, "ds", &digit, &pStr, U_CX_AT_UTIL_PARAM_LAST));
}
