#include <iostream>

#include <SFML/Graphics.hpp>


#include <imgui.h>
#include <imgui-SFML.h>

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(512, 512), "Mikan", sf::Style::Titlebar | sf::Style::Close);
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Test");
        ImGui::Button("Test");
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
}