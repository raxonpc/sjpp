#include "sjpp/sjpp.hpp"
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border


#include <iostream>

int main() {
    using namespace ftxui;

    sjpp::SjpAPI sjp{};
    auto screen = ScreenInteractive::Fullscreen();

    std::string word{};
    std::pair<std::vector<sjpp::Entry>, sjpp::Code> entries{};
    auto entry_list = vbox();

    auto get_entries_element = [&]() {
        switch(entries.second) {
        case sjpp::Code::wordNotFound:
            return text("Word was not found in the dictionary");
        case sjpp::Code::missingEntries:
            return text("Word has got no meanings in the dictionary");
        case sjpp::Code::invalidFile:
        case sjpp::Code::curlError:
            return text("Internal error");
        case sjpp::Code::notConnected:
            return text("No connection to the internet");
        case sjpp::Code::ok: {
            auto elements = Elements{};
            for(const auto& entry : entries.first) {
                elements.emplace_back(hbox({ text(entry.word), text(": "), text(entry.meaning) }));
            }
            return vbox(elements);
        }
        }
    };

    auto enter_option = InputOption{};
    enter_option.on_enter = [&]() {
        entries = sjp.get_entries(word);
        entry_list = get_entries_element();
        word.clear();
    };
    auto input = Input(&word, "word to look up", enter_option);
    auto quit_button = Button("Quit", screen.ExitLoopClosure());


    auto component = Container::Horizontal({
        input, quit_button
    });


    auto renderer = Renderer(component, [&] {
        return vbox({
                        text("Słownik Języka Polskiego") | center,
                        separator(),
                        component->Render(),
                        separator(),
                        entry_list
                    });
    });

    screen.Loop(renderer);
}
