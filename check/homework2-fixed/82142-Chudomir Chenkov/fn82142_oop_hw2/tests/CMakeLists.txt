# Adds Catch2::Catch2
FetchContent_Declare(
    catch
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.9.1
)

FetchContent_MakeAvailable(catch)