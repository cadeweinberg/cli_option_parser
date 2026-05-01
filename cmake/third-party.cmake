# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.10)

include(FetchContent)

FetchContent_Declare(
    cmocka
    GIT_REPOSITORY https://gitlab.com/cmocka/cmocka.git
    GIT_TAG fefa2b8a023121f7235e18ed17249e4012dd144f # v2.0.2
)

FetchContent_MakeAvailable(cmocka)
