#include "honey.h"

int main(int argc, char** argv)
{
    honey_options opts;
    if (!honey_parse_options(&opts, argc, argv)) {
        return 0;
    }

    lua_State* L;

    if (!honey_setup(&L))
        return 1;

    bool success = honey_run(L, opts);

    if (!success)
        return 1;
    
    return 0;
}
