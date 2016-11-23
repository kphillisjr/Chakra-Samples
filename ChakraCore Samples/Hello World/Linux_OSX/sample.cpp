//-------------------------------------------------------------------------------------------------------
// Copyright (C) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
//-------------------------------------------------------------------------------------------------------

#include "ChakraCore.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>

#define FAIL_CHECK(cmd)                     \
    do                                      \
    {                                       \
        JsErrorCode errCode = cmd;          \
        if (errCode != JsNoError)           \
        {                                   \
            printf("Error %d at '%s'\n",    \
                errCode, #cmd);             \
            return 1;                       \
        }                                   \
    } while(0)

using namespace std;

int main()
{
    JsRuntimeHandle runtime;
    JsContextRef context;
    JsValueRef result;
    unsigned currentSourceContext = 0;

    // Your script; try replace hello-world with something else
    const char* script = "(()=>{return \'Hello World!\';})()";

    FAIL_CHECK(JsInitializeRuntime(0, nullptr));

    // Create a runtime.
    FAIL_CHECK(JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime));

    // Create an execution context.
    FAIL_CHECK(JsCreateContext(runtime, &context));

    // Now set the current execution context.
    FAIL_CHECK(JsSetCurrentContext(context));

    JsValueRef fname;
    FAIL_CHECK(JsCreateStringUtf8((const uint8_t*)"sample", strlen("sample"), &fname));

    JsValueRef scriptSource;
    FAIL_CHECK(JsCreateExternalArrayBuffer((void*)script, (unsigned int)strlen(script),
        nullptr, nullptr, &scriptSource));
    // Run the script.
    FAIL_CHECK(JsRun(scriptSource, currentSourceContext++, fname, JsParseScriptAttributeNone, &result));

    // Convert your script result to String in JavaScript; redundant if your script returns a String
    JsValueRef resultJSString;
    FAIL_CHECK(JsConvertValueToString(result, &resultJSString));

    // Project script result back to C++.
    uint8_t *resultSTR = nullptr;
    size_t stringLength;
    FAIL_CHECK(JsCopyStringUtf8(resultJSString, nullptr, 0, &stringLength));
    resultSTR = (uint8_t*) malloc(stringLength + 1);
    FAIL_CHECK(JsCopyStringUtf8(resultJSString, resultSTR, stringLength + 1, nullptr));
    resultSTR[stringLength] = 0;

    printf("Result -> %s \n", resultSTR);
    free(resultSTR);

    // Dispose runtime
    FAIL_CHECK(JsSetCurrentContext(JS_INVALID_REFERENCE));
    FAIL_CHECK(JsDisposeRuntime(runtime));
	FAIL_CHECK(JsFinalizeRuntime());

    return 0;
}
