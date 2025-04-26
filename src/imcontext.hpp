#ifndef WINDOWSCOLORBLASTER_IMCONTEXT_HPP
#define WINDOWSCOLORBLASTER_IMCONTEXT_HPP
#include "imgui.h"
#include "implot.h"
#include <unordered_map>
#include <memory>
namespace ImGui { extern ImGuiKeyData* GetKeyData(ImGuiKey key); }

enum class display_mode_t {
    Manual,
    AutoFit,
    TimeWindow
};

class imcontext {
public:
    imcontext();
    bool update();
    ~imcontext();
    const ImVec4 background_color = ImVec4(0.f, 0.f, 0.f, 1.00f);
private:
};


#endif //WINDOWSCOLORBLASTER_IMCONTEXT_HPP
