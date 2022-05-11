/* This file needs to be included to ensure proper linking */

#ifdef __cplusplus
extern "C" {
#endif

int app_main(void) __attribute__((section(".text.start")));

#ifdef __cplusplus
}
#endif
