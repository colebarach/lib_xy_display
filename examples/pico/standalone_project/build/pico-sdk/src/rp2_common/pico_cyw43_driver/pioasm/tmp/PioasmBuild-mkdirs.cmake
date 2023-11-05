# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/Library/Software/Developers/Raspberry-Pi/Raspberry-Pi-Pico-C-SDK/source/pico-sdk/tools/pioasm"
  "/mnt/Library/Software/Developers/Cole-Barach/lib_xy_test/build/pioasm"
  "/mnt/Library/Software/Developers/Cole-Barach/lib_xy_test/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm"
  "/mnt/Library/Software/Developers/Cole-Barach/lib_xy_test/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/mnt/Library/Software/Developers/Cole-Barach/lib_xy_test/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/mnt/Library/Software/Developers/Cole-Barach/lib_xy_test/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/mnt/Library/Software/Developers/Cole-Barach/lib_xy_test/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/Library/Software/Developers/Cole-Barach/lib_xy_test/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/Library/Software/Developers/Cole-Barach/lib_xy_test/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
