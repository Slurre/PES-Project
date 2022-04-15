#include <stdint.h>
#include <stdlib.h>

#include <dynamic_app.h>

static void flash_op_callback(nrf_fstorage_evt_t * p_evt){};


/* 
Flash handler must be allowed to read new app and write to 
area in which to place it. End address can be changed during 
run-time to grow and allow writing more apps.
*/ 
NRF_FSTORAGE_DEF(nrf_fstorage_t dyn_app_flash) =
{
    .evt_handler    = flash_op_callback,
    .start_addr     = DEFAULT_APP_ADR,
    .end_addr       = APP_RELOC_BASE_ADR + MAX_APP_SIZE_BYTES,
};

/* Sets the backend of flash handler to NVMC */
void init_flash(){
    nrf_fstorage_api_t * p_fs_api;
    p_fs_api = &nrf_fstorage_nvmc;
    nrf_fstorage_init(&dyn_app_flash, p_fs_api, NULL);
}

app_func get_addr_of_app(){
    return APP_RELOC_BASE_ADR;
}

/* Returns the length of newly flashed app (in bytes) */
// TODO: Adapt for varying app length
int get_app_length(){
    return 16;
}

/* */
void relocate_app(){
    uint8_t app_buffer[MAX_APP_SIZE_BYTES] = {0};
    int app_length_bytes = 0;
    
    
    // TODO: Verify that new app exists
    
    
    // Read app code into ram 
    app_length_bytes = get_app_length(); 
    nrf_fstorage_read(
        &dyn_app_flash, 
        DEFAULT_APP_ADR, 
        &app_buffer[0], 
        app_length_bytes
    );

    // Write to new location
    nrf_fstorage_write(
        &dyn_app_flash, 
        APP_RELOC_BASE_ADR, 
        &app_buffer[0], 
        app_length_bytes,
        NULL
    );

    // Clean up old location (re-use app buffer for clearing)
    for(int i=0; i<MAX_APP_SIZE_BYTES; i++){app_buffer[i]=0;}
    nrf_fstorage_write(
        &dyn_app_flash, 
        DEFAULT_APP_ADR, 
        &app_buffer[0], 
        app_length_bytes,
        NULL
    );
}

