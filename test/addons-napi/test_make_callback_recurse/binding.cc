#include <node_api.h>
#include "../common.h"
#include <vector>

namespace {

napi_value MakeCallback(napi_env env, napi_callback_info info) {
  size_t argc = 2;
  napi_value args[2];
  NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));

  napi_value recv = args[0];
  napi_value func = args[1];

  napi_make_callback(env, nullptr /* async_context */,
    recv, func, 0 /* argc */, nullptr /* argv */, nullptr /* result */);

  return recv;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_value fn;
  NAPI_CALL(env, napi_create_function(env, NULL, MakeCallback, NULL, &fn));
  NAPI_CALL(env, napi_set_named_property(env, exports, "makeCallback", fn));
  return exports;
}

}  // namespace

NAPI_MODULE(binding, Init)
