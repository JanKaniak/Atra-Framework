// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL2/SDL_opengl.h>
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

#include "libs/Headers/ControlComponents/Formular.h"

// Main code
int main(int, char **)
{
    AttributeDescriptions *attributeDesc = new AttributeDescriptions();
    Attributes *attributes = new Attributes(attributeDesc);
    Formular *formular = new Formular(attributes);
    bool mainWindows = true;
    bool hl_editacne_okno = false;
    bool numericke_editacne_okno = false;
    bool char_editacne_okno = false;
    bool boolean_edticane_okno = false;
    int numberOfLoadedAtributes = INT_MAX;
    bool kontrola = false;
    char buffer[40] = "Atribut";
    char bufferMin[40] = "0";
    char bufferMax[40] = "50";
    int volbaTypu = 0;
    int volbaPosuvaca = 0;
    std::string typPosuvacov[] = {"SLIDER", "VSLIDER", "DRAG"};
    EditTypeDouble typPosuvacovDouble[] = {EditTypeDouble::SLIDER, EditTypeDouble::VSLIDER, EditTypeDouble::DRAG};
    AttributeType NumtypAttributov[] = {AttributeType::INT, AttributeType::DOUBLE};
    AttributeType CharTypAtributov[] = {AttributeType::CHAR};
    const char *numericke_volbyTypu[] = {"Int", "Double", "Float"};
    const char *char_volbyTypu[] = {"Char", "String"};
    const char *volby[] = {"Slider", "VS_Slider", "Drag"};

    bool moznost1 = false;
    bool moznost2 = false;

    int selected = 0;

    bool selectedMenu = false;

    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char *glsl_version = "#version 100";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
    // GL 3.2 Core + GLSL 150
    const char *glsl_version = "#version 150";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window *window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    if (window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    bool done = false;
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!done)
#endif
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // 2. Základné okno
        {
            static float f = 0.0f;
            static int counter = 0;

            int minHeight = (formular->getNumberOfComponents() * 30) + 100;
            //ImGui::SetNextWindowSizeConstraints(ImVec2(500, minHeight), ImVec2(FLT_MAX, FLT_MAX));
            ImGuiViewport *mainViewPort = ImGui::GetMainViewport();
            ImVec2 pos = mainViewPort->Pos;
            ImVec2 size = mainViewPort->Size;
            ImGui::SetNextWindowPos(pos);
            ImGui::SetNextWindowSize(ImVec2(size.x / 3, size.y));
            ImGui::Begin("Main", &mainWindows, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
            ImGui::BeginMenuBar();
            if (ImGui::MenuItem("Load","L",&selectedMenu)) {
                selectedMenu = true;
            }
            ImGui::EndMenuBar();
            if (ImGui::Button("Add an atribute"))
            {
                hl_editacne_okno = true;
            }

            // 2.1 Výpis
            ImGui::SetNextWindowPos(ImVec2(pos.x+(size.x/3)+5, pos.y));
            ImGui::SetNextWindowSize(ImVec2(size.x / 3, size.y));
            //ImGui::SameLine();
            ImGui::Begin("Atributes", &mainWindows, ImGuiWindowFlags_NoCollapse);
            formular->draw();
            ImGui::End();

            if (ImGui::Button("Load Attribute description", ImVec2(150, 30)))
            {
                numberOfLoadedAtributes = formular->readFileDescriptions("atributy.json");
            }

            if (ImGui::Button("Load Control types", ImVec2(150, 30)))
            {
                bool gg = formular->readFileControlTypes("controlTypes.json");
            }

            if (numberOfLoadedAtributes == 0)
            {
                if (formular->showWarning())
                {
                    numberOfLoadedAtributes = INT_MAX;
                }
                ImGui::End();
            } else if (numberOfLoadedAtributes > 0 && numberOfLoadedAtributes != INT_MAX){
                ImGui::Begin("Info");
                ImGui::Text("Succesfully loaded %d attributes.",numberOfLoadedAtributes);
                if (ImGui::Button("OK", ImVec2(70, 50)))
                {
                    numberOfLoadedAtributes = INT_MAX;
                }
                ImGui::End();
            }

            if (ImGui::Button("Save", ImVec2(70, 30)))
            {
                formular->saveToFile();
            }

            ImVec2 windowSize = ImGui::GetWindowSize();
            ImGui::SetCursorPos(ImVec2(20, windowSize.y - 20));
            if (formular->getNumberOfAttributes() < 500000)
            {
                ImGui::Text("Current number of atributes: %d", formular->getNumberOfAttributes());
            }
            else
            {
                ImGui::Text("Current number of atributes: 500000+");
            }
            ImGui::End();
        }

        // 3. Okno na pridávanie atribútov
        if (hl_editacne_okno)
        {
            AttributeType vybranyTyp;

            ImGui::Begin("Edtiacne okno", &hl_editacne_okno);
            if (ImGui::RadioButton("Numeric", selected == 0))
            {
                selected = 0;
            }
            ImGui::SameLine();
            if (ImGui::RadioButton("Charakter", selected == 1))
            {
                selected = 1;
            }

            ImGui::SameLine();
            if (ImGui::RadioButton("Boolean", selected == 2))
            {
                selected = 2;
            }

            ImGui::InputText("Názov atribútut", buffer, sizeof(buffer));
            if (kontrola)
            {
                ImGui::Text("Meno atributu už existuje!");
            }
            switch (selected)
            {

            case 0:
                ImGui::Combo("Atribute type", &volbaTypu, numericke_volbyTypu, sizeof(numericke_volbyTypu) / sizeof(numericke_volbyTypu[0]));
                if (volbaTypu == 0)
                {
                    ImGui::Combo("Edit type", &volbaPosuvaca, volby, sizeof(volby) / sizeof(volby[0]));
                }

                ImGui::InputText("Minimum", bufferMin, sizeof(bufferMin));
                ImGui::InputText("Maximum", bufferMax, sizeof(bufferMax));

                vybranyTyp = NumtypAttributov[volbaTypu];
                break;

            case 1:
                ImGui::Combo("Atribute type", &volbaTypu, char_volbyTypu, sizeof(char_volbyTypu) / sizeof(char_volbyTypu[0]));
                vybranyTyp = CharTypAtributov[volbaTypu];
                break;

            default:
                break;
            }
            if (ImGui::Button("Save"))
            {
                kontrola = formular->sameName(buffer);
                if (!kontrola)
                {
                    formular->addAttribute(std::string(buffer), typPosuvacov[volbaPosuvaca], vybranyTyp, std::atoi(bufferMin), std::atoi(bufferMax));
                    hl_editacne_okno = false;
                }
            }

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window *backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
