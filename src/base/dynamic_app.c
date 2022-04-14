#include <stdint.h>
#include <stdlib.h>

#include <dynamic_app.h>

NRF_FSTORAGE_DEF(nrf_fstorage_t dyn_app_flash) =
{
    .evt_handler    = flash_op_callback,
    .start_addr     = 0x30000,
    .end_addr       = 0x40000,
};

//static uint32_t app_buffer[20];

void init_flash(){

    nrf_fstorage_api_t * p_fs_api;
    //p_fs_api = &nrf_fstorage_nvmc;
    nrf_fstorage_init(&dyn_app_flash, p_fs_api, NULL);

}
void relocate_app(){

    uint32_t dummy_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    nrf_fstorage_write(&dyn_app_flash, NEW_APP_ADDRESS_BASE, &dummy_data, sizeof(dummy_data), NULL);


    // Read app code into ram 
}

