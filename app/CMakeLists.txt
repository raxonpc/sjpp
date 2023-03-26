include(FetchContent)
FetchContent_Declare(
        ftxui
        GIT_REPOSITORY  https://github.com/ArthurSonzogni/FTXUI.git
        GIT_TAG         v4.0.0
)
FetchContent_MakeAvailable(ftxui)

add_executable(sjp-tui App.cpp)
target_compile_features(sjp-tui PRIVATE cxx_std_20)
target_link_libraries(sjp-tui PRIVATE sjpp ftxui::screen ftxui::component)