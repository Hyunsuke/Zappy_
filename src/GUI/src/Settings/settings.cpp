#include "gui.hpp"

Settings::Settings(int screenWidth, int screenHeight, std::string InstanceName)
    : open(false), instanceName(InstanceName),screenWidth(screenWidth), screenHeight(screenHeight), fps(60),
      selectedResolutionIndex(0), selectedFPSIndex(0),
      tempResolutionIndex(0), tempFPSIndex(0), selectedTimeUnitIndex(0), tempTimeUnitIndex(0),
      chat(screenWidth, screenHeight) {

    resolutions = { {1920, 1080}, {1280, 720}, {800, 600} };
    fpsOptions = { 30, 60, 120 };
    timeUnitOptions = { 5, 10, 20, 40, 80, 160, 320, 640, 1280};

    int currentFPS = 60;
    for (std::size_t i = 0; i < fpsOptions.size(); ++i) {
        if (fpsOptions[i] == currentFPS) {
            selectedFPSIndex = i;
            tempFPSIndex = i;
            break;
        }
    }

    if (InstanceName == "menu") {
        keyBindingsDescriptions = {
            "ENTER -> Connect",
            "ESCAPE -> Quit",
        };
    } else {
        keyBindingsDescriptions = {
            "Z -> Forward",
            "S -> Backward",
            "Q -> Left",
            "D -> Right",
            "A -> Up",
            "E -> Down",
            "Left Click -> Select island",
            "Right Click -> Select player",
            "P -> Select next player",
            "O -> Select free camera",
        };
    }

    UpdateLayout(screenWidth, screenHeight);
}

void Settings::Open() {
    open = true;
    tempResolutionIndex = selectedResolutionIndex;
    tempFPSIndex = selectedFPSIndex;
    UpdateLayout(screenWidth, screenHeight);
}

void Settings::Close() {
    open = false;
}

bool Settings::IsOpen() const {
    return open;
}

int Settings::GetScreenWidth() const {
    return resolutions[selectedResolutionIndex].x;
}

int Settings::GetScreenHeight() const {
    return resolutions[selectedResolutionIndex].y;
}

int Settings::GetFPS() const {
    return fpsOptions[selectedFPSIndex];
}

void Settings::ApplySettings() {
    selectedResolutionIndex = tempResolutionIndex;
    selectedFPSIndex = tempFPSIndex;
    selectedTimeUnitIndex = tempTimeUnitIndex;
    screenWidth = resolutions[selectedResolutionIndex].x;
    screenHeight = resolutions[selectedResolutionIndex].y;
    fps = fpsOptions[selectedFPSIndex];
    SetWindowSize(screenWidth, screenHeight);
    SetTargetFPS(fps);
    if (instanceName != "menu") {
        int newTimeUnit = timeUnitOptions[selectedTimeUnitIndex];
        game->SetTimeUnit(newTimeUnit);
    }
}

void Settings::Update() {
    if (!open) return;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), applyButton)) {
            ApplySettings();
            Close();
        } else if (CheckCollisionPointRec(GetMousePosition(), closeButton)) {
            tempResolutionIndex = selectedResolutionIndex;
            tempFPSIndex = selectedFPSIndex;
            Close();
        }
    }
}

void Settings::HandleMouseInput(Vector2 mousePosition, Rectangle settingsButton, Rectangle closeButton) {
    if (CheckCollisionPointRec(mousePosition, settingsButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Open();
    }
    if (CheckCollisionPointRec(mousePosition, closeButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        CloseWindow();
        std::exit(0);
    }
}

void Settings::HandleWindowResize(Sky& sky, UIManager& uiManager) {
    if (IsWindowResized()) {
        int newWidth = GetScreenWidth();
        int newHeight = GetScreenHeight();
        sky.OnWindowResized(newWidth, newHeight);
        uiManager.OnWindowResized(newWidth, newHeight);
        chat.OnWindowResized(newWidth, newHeight);
        UpdateLayout(newWidth, newHeight);
    }
}

void Settings::Draw() {
    if (instanceName != "menu")
        chat.Draw();

    if (!open) return;

    int dialogWidth = screenWidth * 3 / 4;
    int dialogHeight = screenHeight * 3 / 4;
    int dialogX = (screenWidth - dialogWidth) / 2;
    int dialogY = (screenHeight - dialogHeight) / 2;
    int i = 0;

    DrawRectangle(dialogX, dialogY, dialogWidth, dialogHeight, LIGHTGRAY);
    DrawRectangleLines(dialogX, dialogY, dialogWidth, dialogHeight, DARKGRAY);

    DrawText("Resolution:", resolutionBox.x - 100, resolutionBox.y + 5, 20, BLACK);
    std::vector<std::string> resolutionOptions = { "1920x1080", "1280x720", "800x600" };
    DrawDropDown(resolutionOptions, tempResolutionIndex, resolutionBox);

    DrawText("FPS:", fpsBox.x - 50, fpsBox.y + 5, 20, BLACK);
    std::vector<std::string> fpsOptionsText = { "30", "60", "120" };
    DrawDropDown(fpsOptionsText, tempFPSIndex, fpsBox);

    if (instanceName != "menu") {
        DrawText("Time Unit:", timeUnitBox.x - 100, timeUnitBox.y + 5, 20, BLACK);
        std::vector<std::string> timeUnitOptionsText = { "5", "10", "20", "40", "80", "160", "320", "640", "1280" };
        DrawDropDown(timeUnitOptionsText, tempTimeUnitIndex, timeUnitBox);
    }

    DrawText("Key Bindings:", keyBindingsBox.x - 150, keyBindingsBox.y - 25, 20, BLACK);

    for (const auto& description : keyBindingsDescriptions) {
        DrawText(description.c_str(), keyBindingsBox.x, keyBindingsBox.y + i * 20, 20, BLACK);
        i++;
    }

    DrawButton(applyButton, "Apply", 20);
    DrawButton(closeButton, "Close", 20);
}

void Settings::UpdateLayout(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    int centerX = screenWidth / 2;
    int baseY = screenHeight / 4;
    int spacing = 60;
    int keyBindingHeight = keyBindingsDescriptions.size() * 20;

    resolutionBox = { (float)(centerX - 100), (float)(baseY), 200, 30 };
    fpsBox = { (float)(centerX - 100), (float)(baseY + spacing), 200, 30 };

    if (instanceName != "menu") {
        timeUnitBox = { (float)(centerX - 100), (float)(baseY + 2 * spacing), 200, 30 };
        keyBindingsBox = { (float)(centerX - 100), (float)(baseY + 3 * spacing), 200, (float)keyBindingHeight };
        applyButton = { (float)(centerX - 110), (float)(baseY + 4 * spacing + keyBindingHeight), 100, 40 };
        closeButton = { (float)(centerX + 10), (float)(baseY + 4 * spacing + keyBindingHeight), 100, 40 };
    } else {
        keyBindingsBox = { (float)(centerX - 100), (float)(baseY + 2 * spacing), 200, (float)keyBindingHeight };
        applyButton = { (float)(centerX - 110), (float)(baseY + 3 * spacing + keyBindingHeight), 100, 40 };
        closeButton = { (float)(centerX + 10), (float)(baseY + 3 * spacing + keyBindingHeight), 100, 40 };
    }
}

void Settings::DrawDropDown(const std::vector<std::string>& options, int& selectedIndex, Rectangle box) {
    DrawRectangleRec(box, WHITE);
    DrawText(options[selectedIndex].c_str(), box.x + 5, box.y + 5, 20, BLACK);
    DrawRectangleLines(box.x, box.y, box.width, box.height, DARKGRAY);

    if (CheckCollisionPointRec(GetMousePosition(), box) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        selectedIndex = (selectedIndex + 1) % options.size();
    }
}

void Settings::SendMessage(int n, std::shared_ptr<Player> Player, std::string message)
{
    chat.AddMessage(n, Player->GetTeam(), message);
}

void Settings::SetGameInstance(std::shared_ptr<Game> gameInstance) {
    this->game = gameInstance;
}
