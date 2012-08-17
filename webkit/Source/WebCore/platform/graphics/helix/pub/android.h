#ifndef _ANDROID_H_
#define _ANDROID_H_

#ifdef ANDROID_DEBUG // For debug on Android device
/*
 * Code name       Version                    API level
 * (no code name)  1.0                        API level 1
 * (no code name)  1.1                        API level 2
 * Cupcake         1.5                        API level 3, NDK 1
 * Donut           1.6                        API level 4, NDK 2
 * Eclair          2.0                        API level 5
 * Eclair          2.0.1                      API level 6
 * Eclair          2.1 (incl. 2.1-update 1)   API level 7, NDK 3
 * Froyo           2.2.x                      API level 8, NDK 4
 * Gingerbread     2.3 - 2.3.2                API level 9, NDK 5
 * Gingerbread     2.3.3 - 2.3.4              API level 10
 * Honeycomb       3.0                        API level 11
 * Honeycomb       3.1                        API level 12
 */

 #ifndef LOG_TAG
  #define LOG_TAG "HELIX"
 #endif
 #include <utils/Log.h>

 #define HX_ENABLE_LOGGING(...)
 #define HXLoggingEnabled() FALSE
 #define HXEnableLogging(...) FALSE
 #define HX_DISABLE_LOGGING()
 #define HXLOGL1(a, format_va_args...) LOGW(format_va_args)
 #define HXLOGL2(a, format_va_args...) LOGI(format_va_args)
 #define HXLOGL3(a, format_va_args...) LOGD(format_va_args)
 #define HXLOGL4(a, format_va_args...) LOGD(format_va_args)

 #define HXLog1(a, format_va_args...) LOGW(format_va_args)
 #define HXLog2(a, format_va_args...) LOGI(format_va_args)
 #define HXLog3(a, format_va_args...) LOGD(format_va_args)
 #define HXLog4(a, format_va_args...) LOGD(format_va_args)

 #define HXLOGHDRL1(a, format_va_args...) LOGW(format_va_args)
 #define HXLOGHDRL2(a, format_va_args...) LOGI(format_va_args)
 #define HXLOGHDRL3(a, format_va_args...) LOGD(format_va_args)
 #define HXLOGHDRL4(a, format_va_args...) LOGD(format_va_args)

 #define HXLOGPKTL1(a, format_va_args...) LOGW(format_va_args)
 #define HXLOGPKTL2(a, format_va_args...) LOGI(format_va_args)
 #define HXLOGPKTL3(a, format_va_args...) LOGD(format_va_args)
 #define HXLOGPKTL4(a, format_va_args...) LOGD(format_va_args)
#elif defined(X86_DEBUG) // For debug on x86-PC
 #include "hxtick.h"
 #include "stdio.h"
 #define HX_ENABLE_LOGGING(...)
 #define HXLoggingEnabled() FALSE
 #define HXEnableLogging(...) FALSE
 #define HX_DISABLE_LOGGING()
 #define HXLOGL1(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLOGL2(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLOGL3(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLOGL4(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)

 #define HXLog1(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLog2(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLog3(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLog4(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)

 #define HXLOGHDRL1(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLOGHDRL2(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLOGHDRL3(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLOGHDRL4(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)

 #define HXLOGPKTL1(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLOGPKTL2(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLOGPKTL3(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
 #define HXLOGPKTL4(a, format_va_args...) printf("\n%lu  ", HX_GET_BETTERTICKCOUNT());printf(format_va_args)
#else // For release
 #define HX_ENABLE_LOGGING(...)
 #define HXLoggingEnabled() FALSE
 #define HXEnableLogging(...) FALSE
 #define HX_DISABLE_LOGGING()
 #define HXLOGL1(a, format_va_args...)
 #define HXLOGL2(a, format_va_args...)
 #define HXLOGL3(a, format_va_args...)
 #define HXLOGL4(a, format_va_args...)

 #define HXLog1(a, format_va_args...)
 #define HXLog2(a, format_va_args...)
 #define HXLog3(a, format_va_args...)
 #define HXLog4(a, format_va_args...)

 #define HXLOGHDRL1(a, format_va_args...)
 #define HXLOGHDRL2(a, format_va_args...)
 #define HXLOGHDRL3(a, format_va_args...)
 #define HXLOGHDRL4(a, format_va_args...)

 #define HXLOGPKTL1(a, format_va_args...)
 #define HXLOGPKTL2(a, format_va_args...)
 #define HXLOGPKTL3(a, format_va_args...)
 #define HXLOGPKTL4(a, format_va_args...)
#endif

#define HX_I64d_ARG(x) (x)
#define HX_I64d_SUBST "%lld"

#endif
