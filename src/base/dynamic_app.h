
typedef int (*app_func)(void);
void relocate_app(app_func *af, void* new_loc);
