#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dynamic_app.h>

/*  Searches for and returns the address where the hex EOF record is,
    starting the search from a given address. */
void* get_hex_eof_address(void* ad_ptr){
    uint64_t EOF_record = 0x00000001FF;
    while((*(uint64_t*)ad_ptr) != EOF_record){
        ad_ptr = (uint32_t*)ad_ptr + 1; // Cortex M4 uses word aligned addresses
    }
    return ad_ptr;
}

void relocate_app(app_func *af, void* new_loc){
    long app_len_bytes;
    void* app_end = NULL;
    
    // find length of app
    app_end = get_hex_eof_address((void*)af);
    app_len_bytes = (uint8_t*)*af - (uint8_t*)app_end;
    
    // move app to new location
    memcpy(*af, new_loc, app_len_bytes);

    // clean the old location
    memset(*af, 0, app_len_bytes);

    // point func to new location
    *af = (app_func)new_loc;
}

