#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "nrf.h"
#include "nrf_soc.h"
#include "nordic_common.h"
#include "boards.h"
#include "app_timer.h"
#include "app_util.h"
#include "nrf_drv_clock.h"
#include "nrf_fstorage.h"
#include "nrf_fstorage_nvmc.h"

#define DEFAULT_APP_ADR         0x30000
#define MAX_APP_SIZE_BYTES      1024
#define APP_RELOC_BASE_ADR      (DEFAULT_APP_ADR + MAX_APP_SIZE_BYTES) 

typedef int (*app_func)(void);

void init_flash();
void relocate_app();


