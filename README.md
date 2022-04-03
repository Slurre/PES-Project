# PES-Project

Currently, this repository holds a simple example app that can be built using a CMake script similar to the one used in InfiniTime for the nRF52840-DK (PCA10056) board.

It can be built using the very same docker file provided by InfiniTime (see their [documentation](https://github.com/InfiniTimeOrg/InfiniTime/blob/develop/doc/buildWithDocker.md)) by issueing the command `docker run --rm -it -v $(pwd):/sources infinitime-build` in the project root directory.

Alternatively, it should be possible to build the app on the local system if `ARM_NONE_EABI_TOOLCHAIN_PATH` and `NRF5_SDK_PATH` are set in the environment with CMake (adapting the commands used in `./docker/build.sh`).

The resulting bin, obj, hex and map files can be found in `./build/src/dynamic_code-app.hex` and flashed using `nrfjprog` by using `nrfjprog -f NRF52 --program build/src/dynamic_code-app.hex --verify --chiperase --reset`.

The `nrfjprog` tool can be installed following the guide at https://infocenter.nordicsemi.com/topic/ug_nrf_cltools/UG/cltools/nrf_installation.html (Segger JLink needs to be installed as well).
