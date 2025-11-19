#include "../include/SinglyLinkedListMeth.hpp"
#include "../include/CustomerInterface.hpp"
#include "../include/EmployeeInterface.hpp"

#include <iostream>
#include <string>
using namespace std;

#define SDL_MAIN_HANDLED

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include <SDL.h>

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "ImGui Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        400, 300,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Initialize ImGui SDL2 + SDLRenderer2 bindings
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                running = false;
        }

        // Start ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Demo window
        ImGui::Begin("Hello!");
        ImGui::Text("This is some text");
        if (ImGui::Button("Click Me")) {
            cout << "Button clicked!" << endl;
        }
        ImGui::End();

        // Render
        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 114, 144, 154, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);

    }

    // Cleanup ImGui and SDL
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Banking system menu
    bool reloop;
    string input;

    cout << "----------------------------------------------------------------------------\n";
    cout <<
    "  ____              _    _               ____            _                  \n"
    " | __ )  __ _ _ __ | | _(_)_ __   __ _  / ___| _   _ ___| |_ ___ _ __ ___  \n"
    " |  _ \\ / _` | '_ \\| |/ / | '_ \\ / _` | \\___ \\| | | / __| __/ _ \\ '_ ` _ \\ \n"
    " | |_) | (_| | | | |   <| | | | | (_| |  ___) | |_| \\__ \\ ||  __/ | | | | |\n"
    " |____/ \\__,_|_| |_|_|\\_\\_|_| |_|\\__, | |____/ \\__, |___/\\__\\___|_| |_| |_| \n"
    "                                 |___/         |___/                        \n";
    cout << "----------------------------------------------------------------------------\n";
    cout <<
    "___  _    ____ ____ ____ ____    ____ _  _ ____ ____ ____ ____    ____ _  _ ____     \n"
    "|__] |    |___ |__| [__  |___    |    |__| |  | |  | [__  |___    |  | |\\ | |___    .\n"
    "|    |___ |___ |  | ___] |___    |___ |  | |__| |__| ___] |___    |__| | \\| |___    .\n\n";

    cout << "1-Customer Interface\n2-Employee Interface\n3-Exit\n";

    do {
        cout << "Please give your choice: ";
        getline(cin, input);
        reloop = !(input == "1" || input == "2" || input == "3");
    } while (reloop);

    if (input == "1") {
        customerInterface();
    } else if (input == "2") {
        employeeInterface();
    }

    return 0;
}
