# PES-Project

Currently, this repository holds a simple proof-of-concept example consisting of a `base` (firmware) and an `app` that can be built using a CMake script similar to the one used in InfiniTime for the nRF52840-DK (PCA10056) board.

It can be built using the very same docker file provided by InfiniTime (see their [documentation](https://github.com/InfiniTimeOrg/InfiniTime/blob/develop/doc/buildWithDocker.md)) by issueing the command `docker run --rm -it -v $(pwd):/sources infinitime-build` in the project root directory.

Alternatively, it should be possible to build the app on the local system if `ARM_NONE_EABI_TOOLCHAIN_PATH` and `NRF5_SDK_PATH` are set in the environment with CMake (adapting the commands used in `./docker/build.sh`).

The resulting bin, obj, hex and map files can be found in `./build/src/{base,app}/dynamic_code-{base,app}.hex` and flashed using `nrfjprog` by using `nrfjprog -f NRF52 --program build/src/base/dynamic_code-base.hex --sectorerase --verify --reset` followed by `nrfjprog -f NRF52 --program build/src/app/dynamic_code-app.hex --sectorerase --verify --reset`.

The `nrfjprog` tool can be installed following the guide at https://infocenter.nordicsemi.com/topic/ug_nrf_cltools/UG/cltools/nrf_installation.html (Segger JLink needs to be installed as well).

## Misc info

The current content of the internal FLASH memory can be read using `/opt/nrf-command-line-tools/bin/nrfjprog --readcode flash.hex`.

Hex files can be analyzed using a [tool available online](http://www.dlwrr.com/electronics/tools/hexview/hexview.html) and the [Wikipedia page](https://en.wikipedia.org/wiki/Intel_HEX) explaining the syntax.
