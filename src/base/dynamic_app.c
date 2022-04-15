#include <stdint.h>
#include <stdlib.h>

#include <dynamic_app.h>

static void flash_op_callback(nrf_fstorage_evt_t * p_evt){};

// Flag set after all app relocation is complete
static int app_reloc_complete = 0;

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

void wait_for_flash_ready(nrf_fstorage_t const * p_fstorage)
{
    /* While fstorage is busy, sleep and wait for an event. */
    while (nrf_fstorage_is_busy(p_fstorage)){};
}

/* Returns a function pointer to the relocated app */
// TODO: Only supports one app right now
app_func get_addr_of_app(){
    if (is_app_reloc_complete())
        return APP_RELOC_BASE_ADR + 1; // +1 for thumb instructions;
    else 
        return NULL;
}


int is_app_reloc_complete(){
    return app_reloc_complete != 0; 
}

/* Returns the length of newly flashed app (in bytes) */
// TODO: Adapt for varying app length
int get_app_length(){
    return MAX_APP_SIZE_BYTES;
}

/* */
static uint8_t app_buffer[MAX_APP_SIZE_BYTES] = {0};
static int app_length_bytes = 0;
static uint8_t randombs[10] = {3};
void relocate_app(){
    
    // TODO: Verify that new app exists
    
    
    ret_code_t rc;

    // Read app code into ram 
    app_length_bytes = get_app_length(); 
    rc = nrf_fstorage_read(
        &dyn_app_flash, 
        DEFAULT_APP_ADR, 
        &app_buffer[0], 
        app_length_bytes
    );
    APP_ERROR_CHECK(rc);

    wait_for_flash_ready(&dyn_app_flash);

    // Write to new location
    rc=nrf_fstorage_write(
        &dyn_app_flash, 
        APP_RELOC_BASE_ADR, 
        &app_buffer[0], 
        app_length_bytes,
        NULL
    );
    APP_ERROR_CHECK(rc);
    wait_for_flash_ready(&dyn_app_flash);

    // Clean up old location (re-use app buffer for clearing)
    for(int i=0; i<MAX_APP_SIZE_BYTES; i++){app_buffer[i]=0xFF;}
    rc=nrf_fstorage_write(
        &dyn_app_flash, 
        DEFAULT_APP_ADR, 
        &randombs[0], 
        10,
        NULL
    );
    APP_ERROR_CHECK(rc);
    wait_for_flash_ready(&dyn_app_flash);

    // TODO: Move when supporting multiple apps
    app_reloc_complete = 1;
}

