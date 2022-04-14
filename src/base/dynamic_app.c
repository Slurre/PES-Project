#include <stdint.h>
#include <stdlib.h>

#include <dynamic_app.h>

static void flash_op_callback(nrf_fstorage_evt_t * p_evt){};

NRF_FSTORAGE_DEF(nrf_fstorage_t dyn_app_flash) =
{
    .evt_handler    = flash_op_callback,
    .start_addr     = 0x30000,
    .end_addr       = 0x40000,
};

void wait_for_flash_ready(nrf_fstorage_t const * p_fstorage)
{
    while (nrf_fstorage_is_busy(p_fstorage)){};
}

void init_flash(){
    nrf_fstorage_api_t * p_fs_api;
    p_fs_api = &nrf_fstorage_nvmc;
    nrf_fstorage_init(&dyn_app_flash, p_fs_api, NULL);
}

void relocate_app(){
    uint32_t app_buffer[4] = {0};
    int app_length_bytes = 0x10; // TODO: Adapt for varying app length
    
    // Read app code into ram 
    nrf_fstorage_read(
        &dyn_app_flash, 
        DEFAULT_APP_ADDRESS, 
        &app_buffer[0], 
        app_length_bytes
    );

    // Write to new location
    nrf_fstorage_write(
        &dyn_app_flash, 
        NEW_APP_ADDRESS_BASE, 
        &app_buffer[0], 
        app_length_bytes,
        NULL
    );
}

