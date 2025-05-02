#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include <MinHook.h>
#include <codecvt>
#include <filesystem>
#include <format>
#include <fstream>
#include <il2cpp.h>
#include <imgui_internal.h>
#include <includes.h>
#include <wrapper.hpp>

struct LogString {
    std::string log;
    uint64_t time;
};

static uint64_t startTick = 0;
std::vector<LogString> LogQueue = {};
std::unique_ptr<Wrapper> SDK = nullptr;

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device *pDevice = NULL;
ID3D11DeviceContext *pContext = NULL;
ID3D11RenderTargetView *mainRenderTargetView;

void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    io.IniFilename = nullptr;
    ImGui::StyleColorsDark();
    ImGuiStyle &style = ImGui::GetStyle();
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);

    style.Alpha = 1.0f;
    style.WindowPadding = ImVec2(10, 10);
    style.WindowMinSize = ImVec2(100, 100);
    style.WindowRounding = 0.0f;
    style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
    style.ChildRounding = 0.0f;
    style.FramePadding = ImVec2(5, 5);
    style.FrameRounding = 0.0f;
    style.ItemSpacing = ImVec2(5, 5);
    style.ItemInnerSpacing = ImVec2(4, 4);
    style.TouchExtraPadding = ImVec2(0, 0);
    style.IndentSpacing = 21.0f;
    style.ColumnsMinSpacing = 6.0f;
    style.ScrollbarSize = 12.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 0.0f;
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    style.DisplayWindowPadding = ImVec2(22, 22);
    style.DisplaySafeAreaPadding = ImVec2(4, 4);
    style.AntiAliasedLines = true;
    style.AntiAliasedFill = true;
    style.CurveTessellationTol = 1.25f;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;

    if (uMsg == WM_CLOSE)
    {
        DestroyWindow(hWnd);
        return 0;
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

void DebugLogV(const char *fmt, va_list args)
{
    uint64_t milliseconds = GetTickCount64() - startTick;
    uint64_t minutes = milliseconds / 60000;
    uint64_t remainingMillisecondsAfterMinutes = milliseconds % 60000;
    uint64_t seconds = remainingMillisecondsAfterMinutes / 1000;
    uint64_t remainingMilliseconds = remainingMillisecondsAfterMinutes % 1000;

    ImGuiContext &g = *ImGui::GetCurrentContext();
    const int old_size = g.DebugLogBuf.size();
    g.DebugLogBuf.appendf("[%02llu:%02llu:%03llu] ", minutes, seconds, remainingMilliseconds);
    g.DebugLogBuf.appendfv(fmt, args);
    g.DebugLogIndex.append(g.DebugLogBuf.c_str(), old_size, g.DebugLogBuf.size());
}

void DebugLogQueue(const LogString &logStr)
{
    uint64_t milliseconds = logStr.time - startTick;
    uint64_t minutes = milliseconds / 60000;
    uint64_t remainingMillisecondsAfterMinutes = milliseconds % 60000;
    uint64_t seconds = remainingMillisecondsAfterMinutes / 1000;
    uint64_t remainingMilliseconds = remainingMillisecondsAfterMinutes % 1000;

    ImGuiContext &g = *ImGui::GetCurrentContext();
    const int old_size = g.DebugLogBuf.size();
    g.DebugLogBuf.appendf("[%02llu:%02llu:%03llu] ", minutes, seconds, remainingMilliseconds);
    g.DebugLogBuf.appendf("%s", logStr.log.c_str());
    g.DebugLogIndex.append(g.DebugLogBuf.c_str(), old_size, g.DebugLogBuf.size());
}

void DebugLog(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    DebugLogV(fmt, args);
    va_end(args);
}

static bool isShowMenu = true;
static bool isShowFps = true;
static bool isDmgMultiplierEnabled = false;
static bool isDmgReduceMultiplierEnabled = false;
static int dmgMultiplier = 1;
static int dmgReduceMultiplier = 1;

void MainLoop(ImDrawList *canvas, ImGuiIO &io)
{
    while (!LogQueue.empty())
    {
        const auto &log = LogQueue.front();
        DebugLogQueue(log);
        LogQueue.erase(LogQueue.begin());
    }

    if (ImGui::IsKeyPressed(ImGuiKey_F5))
        isShowMenu = !isShowMenu;

    if (isShowFps)
        ImGui::Text("FPS: %.1f", io.Framerate);

    if (isShowMenu)
    {
        ImGuiContext &g = *ImGui::GetCurrentContext();
        ImGui::SetNextWindowSize({320, 0}, ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2{16, 48}, ImGuiCond_Once);
        ImGui::Begin("Fakekey2k's Menu", &isShowMenu, ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Press [F5] to Show | Hide Menu");
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();
        if (ImGui::BeginTabBar("##TabBar"))
        {
            if (ImGui::BeginTabItem("Home"))
            {
                ImGui::Spacing();
                ImGui::Checkbox(" Show FPS", &isShowFps);
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
                    ImGui::SetTooltip("Seriously WTF!?");
                ImGui::Separator();
                ImGui::Spacing();
                ImGui::Checkbox(" Damage Multiplier", &isDmgMultiplierEnabled);
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
                    ImGui::SetTooltip("Make you strong as Eros. Changing below slider's value corresponds to the number of times your damage is multiplied.");
                ImGui::Separator();
                ImGui::Spacing();
                ImGui::Text("Your Damage: x%d", dmgMultiplier);
                ImGui::Spacing();
                ImGui::SetNextItemWidth(-FLT_MIN);
                ImGui::SliderInt("##Damage Slider", &dmgMultiplier, 1, 100);
                ImGui::Separator();
                ImGui::Spacing();
                ImGui::Checkbox(" Damage Reduce Multiplier", &isDmgReduceMultiplierEnabled);
                if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
                    ImGui::SetTooltip("Make enemies weak as fuck. Changing below slider's value corresponds to the number of times enemies's damage reduce is multiplied.");
                ImGui::Separator();
                ImGui::Spacing();
                ImGui::Text("Enemies's Damage Reduce: x%d", dmgReduceMultiplier);
                ImGui::Spacing();
                ImGui::SetNextItemWidth(-FLT_MIN);
                ImGui::SliderInt("##Damage Reduce Slider", &dmgReduceMultiplier, 1, 100);
                ImGui::Separator();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Logs"))
            {
                ImGui::Spacing();
                if (ImGui::SmallButton("Clear"))
                {
                    g.DebugLogBuf.clear();
                    g.DebugLogIndex.clear();
                    g.DebugLogSkippedErrors = 0;
                }
                ImGui::SameLine();
                if (ImGui::SmallButton("Copy"))
                    ImGui::SetClipboardText(g.DebugLogBuf.c_str());
                ImGui::Spacing();
                ImGui::BeginChild("##Logs", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Borders, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
                ImGuiListClipper clipper;
                clipper.Begin(g.DebugLogIndex.size());
                while (clipper.Step())
                    for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                        ImGui::DebugTextUnformattedWithLocateItem(g.DebugLogIndex.get_line_begin(g.DebugLogBuf.c_str(), line_no), g.DebugLogIndex.get_line_end(g.DebugLogBuf.c_str(), line_no));
                if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                    ImGui::SetScrollHereY(1.0f);
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("About"))
            {
                ImGui::Spacing();
                ImGui::BeginChild("##Logs", ImVec2(0.0f, 0.0f), ImGuiChildFlags_Borders, ImGuiWindowFlags_HorizontalScrollbar);
                ImGui::Text("Rise of Eros version: 3.3.2");
                ImGui::Text("Fakekey2k's Menu version: 1.0.0");
                ImGui::Text("Author: Fakekey");
                ImGui::EndChild();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();
    }
}

bool overlay_initialized = false;
HRESULT __stdcall hkPresent(IDXGISwapChain *pSwapChain, UINT SyncInterval, UINT Flags)
{
    if (!overlay_initialized)
    {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void **)&pDevice)))
        {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D *pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&pBackBuffer);
            D3D11_RENDER_TARGET_VIEW_DESC desc = {};
            desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
            pDevice->CreateRenderTargetView(pBackBuffer, &desc, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            overlay_initialized = true;
        }
        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiIO &io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos({0.f, 0.f});
    ImGui::Begin("##Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoTooltip);
    MainLoop(ImGui::GetWindowDrawList(), io);
    ImGui::End();

    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return oPresent(pSwapChain, SyncInterval, Flags);
}

HMODULE denuvo_anti_cheat_runtime = NULL;
uint64_t runtimeApiDriverHandshakeStatus = NULL;
void(__fastcall *stopServices)() = nullptr;

void StopDenuvo()
{
    stopServices();
    system(R"(sc stop "Denuvo Anti-Cheat" > NUL 2>&1)");
    system(R"(sc stop "Denuvo Anti-Cheat Update Service" > NUL 2>&1)");
}

void ClearLogs()
{
    std::string logDirectory = R"(C:\Program Files\Denuvo Anti-Cheat\Logs)";
    try
    {
        if (std::filesystem::exists(logDirectory) && std::filesystem::is_directory(logDirectory))
        {
            for (const auto &entry : std::filesystem::directory_iterator(logDirectory))
            {
                if (std::filesystem::is_regular_file(entry.path()))
                {
                    try
                    {
                        std::filesystem::remove(entry.path());
                        LogQueue.push_back({std::format("removed: {}\n", entry.path().string()), GetTickCount64()});
                    }
                    catch (const std::filesystem::filesystem_error &e)
                    {
                        LogQueue.push_back({std::format("{}\n", e.what()), GetTickCount64()});
                    }
                }
            }
        }
        else
        {
            LogQueue.push_back({"Directory does not exist or is not accessible.\n", GetTickCount64()});
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        LogQueue.push_back({std::format("{}\n", e.what()), GetTickCount64()});
    }

    auto recordDirectory = std::filesystem::temp_directory_path().parent_path().parent_path().parent_path();
    recordDirectory /= R"(LocalLow\Pinkcore\Rise of Eros\BattleRecord)";
    try
    {
        if (std::filesystem::exists(recordDirectory) && std::filesystem::is_directory(recordDirectory))
        {
            for (const auto &entry : std::filesystem::directory_iterator(recordDirectory))
            {
                if (std::filesystem::is_regular_file(entry.path()))
                {
                    try
                    {
                        std::filesystem::remove(entry.path());
                        LogQueue.push_back({std::format("removed: {}\n", entry.path().string()), GetTickCount64()});
                    }
                    catch (const std::filesystem::filesystem_error &e)
                    {
                        LogQueue.push_back({std::format("{}\n", e.what()), GetTickCount64()});
                    }
                }
            }
        }
        else
        {
            LogQueue.push_back({"Directory does not exist or is not accessible.\n", GetTickCount64()});
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        LogQueue.push_back({std::format("{}\n", e.what()), GetTickCount64()});
    }

    auto logFile = recordDirectory.parent_path();
    logFile /= "Player.log";
    try
    {
        if (std::filesystem::exists(logFile) && std::filesystem::is_regular_file(logFile))
        {
            try
            {
                std::ofstream ofs;
                ofs.open(logFile, std::ofstream::out | std::ofstream::trunc);
                ofs.close();
                LogQueue.push_back({std::format("cleared: {}\n", logFile.string()), GetTickCount64()});
            }
            catch (const std::filesystem::filesystem_error &e)
            {
                LogQueue.push_back({std::format("{}\n", e.what()), GetTickCount64()});
            }
        }
        else
        {
            LogQueue.push_back({"File does not exist or is not accessible.\n", GetTickCount64()});
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        LogQueue.push_back({std::format("{}\n", e.what()), GetTickCount64()});
    }
}

std::string To_UTF8(const std::u16string &s)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> conv;
    return conv.to_bytes(s);
}

std::string stringFrom(System_String_o *String)
{
    std::u16string data((char16_t *)&String->fields._firstChar, String->fields._stringLength);
    return To_UTF8(data);
}

typedef int32_t(__fastcall *get_CurrentHealth)(Pinkcore_Gameplay_Health_o *__this);
typedef Pinkcore_Gameplay_HealthChange_o *(__fastcall *DirectDamage)(Pinkcore_Gameplay_Health_o *__this, int32_t gaugeIndex, int32_t damagePoints);
typedef Pinkcore_Gameplay_HealthChange_o *(__fastcall *Damage)(Pinkcore_Gameplay_Health_o *__this, int32_t damagePoints);

bool denuvo_stopped = false;
bool g_initialized = false;

void(__fastcall *orig_HandleHealthEvent)(void *__this, void *caster, Pinkcore_Gameplay_CharacterUnit_o *receiver, Pinkcore_Gameplay_HealthViewInfo_o *healthViewInfo) = nullptr;
void hook_HandleHealthEvent(void *__this, void *caster, Pinkcore_Gameplay_CharacterUnit_o *receiver, Pinkcore_Gameplay_HealthViewInfo_o *healthViewInfo)
{
    if (healthViewInfo->fields._healthViewInfoType == 1)
        return orig_HandleHealthEvent(__this, caster, receiver, healthViewInfo);

    if (isDmgMultiplierEnabled && receiver->fields._playerId == 1)
    {
        auto real_damage = healthViewInfo->fields._totalHealthChangeApplied;
        auto health = (Pinkcore_Gameplay_Health_o *)receiver->fields._health;
        auto get_hp = (get_CurrentHealth)health->klass->vtable._12_Pinkcore_Gameplay_IHealthInfo_get_CurrentHealth.methodPtr;
        auto sub_hp = (Damage)health->klass->vtable._4_Pinkcore_Gameplay_IHealth_Damage.methodPtr;
        auto restore_hp = (DirectDamage)health->klass->vtable._5_Pinkcore_Gameplay_IHealth_DirectDamage.methodPtr;
        auto result_restore = restore_hp(health, 0, -real_damage);

        auto modified_damage = real_damage * dmgMultiplier;
        auto result_sub = sub_hp(health, modified_damage);
        auto received_damage = result_sub->fields._healthChangesReceived->fields._items->m_Items[0].fields.Item2;
        auto applied_damage = result_sub->fields._healthChangesApplied->fields._items->m_Items[0].fields.Item2;
        auto info_received = (System_Collections_Generic_List_ValueTuple_int__int___o *)healthViewInfo->fields._healthChangeReceivedCollection;
        auto info_applied = (System_Collections_Generic_List_ValueTuple_int__int___o *)healthViewInfo->fields._healthChangeAppliedCollection;
        info_received->fields._items->m_Items[0].fields.Item2 = received_damage;
        info_applied->fields._items->m_Items[0].fields.Item2 = applied_damage;
        healthViewInfo->fields._totalHealthChangeReceived = received_damage;
        healthViewInfo->fields._totalHealthChangeApplied = applied_damage;

        if (get_hp(health) <= 0)
            healthViewInfo->fields._isChangeToDeath = true;
        else
            healthViewInfo->fields._isChangeToDeath = false;
    }

    if (isDmgReduceMultiplierEnabled && receiver->fields._playerId == 0)
    {
        auto real_damage = healthViewInfo->fields._totalHealthChangeApplied;
        auto health = (Pinkcore_Gameplay_Health_o *)receiver->fields._health;
        auto get_hp = (get_CurrentHealth)health->klass->vtable._12_Pinkcore_Gameplay_IHealthInfo_get_CurrentHealth.methodPtr;
        auto sub_hp = (Damage)health->klass->vtable._4_Pinkcore_Gameplay_IHealth_Damage.methodPtr;
        auto restore_hp = (DirectDamage)health->klass->vtable._5_Pinkcore_Gameplay_IHealth_DirectDamage.methodPtr;
        auto result_restore = restore_hp(health, 0, -real_damage);

        auto modified_damage = real_damage / dmgReduceMultiplier;
        auto result_sub = sub_hp(health, modified_damage);
        auto received_damage = result_sub->fields._healthChangesReceived->fields._items->m_Items[0].fields.Item2;
        auto applied_damage = result_sub->fields._healthChangesApplied->fields._items->m_Items[0].fields.Item2;
        auto info_received = (System_Collections_Generic_List_ValueTuple_int__int___o *)healthViewInfo->fields._healthChangeReceivedCollection;
        auto info_applied = (System_Collections_Generic_List_ValueTuple_int__int___o *)healthViewInfo->fields._healthChangeAppliedCollection;
        info_received->fields._items->m_Items[0].fields.Item2 = received_damage;
        info_applied->fields._items->m_Items[0].fields.Item2 = applied_damage;
        healthViewInfo->fields._totalHealthChangeReceived = received_damage;
        healthViewInfo->fields._totalHealthChangeApplied = applied_damage;

        if (get_hp(health) <= 0)
            healthViewInfo->fields._isChangeToDeath = true;
        else
            healthViewInfo->fields._isChangeToDeath = false;
    }

    return orig_HandleHealthEvent(__this, caster, receiver, healthViewInfo);
}

__int64(__fastcall *orig_runtimeApiDriverHandshakeStatus)() = nullptr;
__int64 hook_runtimeApiDriverHandshakeStatus()
{
    if (!denuvo_stopped)
    {
        StopDenuvo();
        denuvo_stopped = true;
        LogQueue.push_back({"Bypass Denuvo successfully!\n", GetTickCount64()});

        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
            kiero::bind(8, (void **)&oPresent, (void *)hkPresent);
    }

    orig_runtimeApiDriverHandshakeStatus();
    ClearLogs();

    if (!g_initialized)
    {
        Il2cpp::initialize();
        SDK = std::make_unique<Wrapper>();

        const auto Assembly_CSharp = SDK->get_image("Assembly-CSharp.dll");
        const auto BattleStatistic = Assembly_CSharp->get_class("BattleStatistic", "Pinkcore.Heros.Gameplay");
        const auto _HandleHealthEvent = BattleStatistic->get_method("_HandleHealthEvent", 3);

        if (MH_CreateHook(UFUNC(_HandleHealthEvent), (void *)hook_HandleHealthEvent, (void **)&orig_HandleHealthEvent) == MH_OK)
            MH_EnableHook(UFUNC(_HandleHealthEvent));

        g_initialized = true;
    }

    return 1;
}

void Initialize()
{
    MH_Initialize();
    startTick = GetTickCount64();

    denuvo_anti_cheat_runtime = GetModuleHandleA("denuvo-anti-cheat-runtime.dll");
    runtimeApiDriverHandshakeStatus = (uint64_t)GetProcAddress(denuvo_anti_cheat_runtime, "runtimeApiDriverHandshakeStatus");
    stopServices = decltype(stopServices)((uint64_t)GetProcAddress(denuvo_anti_cheat_runtime, "stopServices"));

    if (MH_CreateHook((void *)runtimeApiDriverHandshakeStatus, (void *)hook_runtimeApiDriverHandshakeStatus, (void **)&orig_runtimeApiDriverHandshakeStatus) == MH_OK)
    {
        MH_EnableHook((void *)runtimeApiDriverHandshakeStatus);
        LogQueue.push_back({"Initializing...\n", GetTickCount64()});
    }
}

void Uninitialize()
{
    kiero::shutdown();
    MH_Uninitialize();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        Initialize();
        break;

    case DLL_PROCESS_DETACH:
        Uninitialize();
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    default:
        break;
    }

    return TRUE;
}