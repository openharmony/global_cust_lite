/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CUST_NAPI_H
#define CUST_NAPI_H

#include <string>

#include "napi/native_common.h"
#include "napi/native_node_api.h"
#include "napi/native_api.h"

namespace OHOS {
namespace Global {
namespace Cust {
struct CustAsyncContext {
    bool success_ = true;
    napi_async_work work_;
    napi_deferred deferred_;
    napi_ref callbackRef_;
    std::string errMsg_;
    typedef napi_value (*CreateNapiValue)(napi_env env, CustAsyncContext &context);
    CreateNapiValue createValueFunc_;

    int32_t custType_ = 0;
    std::string relPath_;
    std::string pathValue_;
    std::vector<std::string> paths_;

    void SetErrorMsg(const std::string &msg);
};

class CustNapi {
public:
    CustNapi();
    ~CustNapi() = default;
    static napi_value Init(napi_env env, napi_value exports);

private:
    static napi_value NAPIGetOneCfgFile(napi_env env, napi_callback_info info);
    static napi_value NAPIGetCfgFiles(napi_env env, napi_callback_info info);
    static napi_value NAPIGetCfgDirList(napi_env env, napi_callback_info info);
    static napi_value CreateUndefined(napi_env env);
    static std::string GetStringFromNAPI(napi_env env, napi_value value);
    static napi_value HandleAsyncWork(napi_env env, CustAsyncContext *context, std::string workName,
        napi_async_execute_callback execute, napi_async_complete_callback complete);
    static bool MatchValueType(napi_env env, napi_value value, napi_valuetype targetType);
    static void NativeGetOneCfgFile(napi_env env, void *data);
    static void NativeGetCfgFiles(napi_env env, void *data);
    static void NativeGetCfgDirList(napi_env env, void *data);
    static void NativeCallbackComplete(napi_env env, napi_status status, void *data);
    static napi_value ParseRelPath(napi_env env, std::string &param, napi_value args);
};
} // namespace Cust
} // namespace Global
} // namespace OHOS
#endif