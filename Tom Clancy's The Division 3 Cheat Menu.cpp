#include <iostream>
#include <string>
#include <CEGUI/CEGUI.h>
#include <CEGUI/CEGUILogger.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <CEGUI/WidgetLookManager/WidgetLookManager.h>
#include <CEGUI/WindowManager/WindowManager.h>
#include <CEGUI/System/WindowTypes/DefaultWindow.h>
#include <CEGUI/System/WindowTypes/Editbox.h>
#include <CEGUI/System/WindowTypes/Button.h>
#include <CEGUI/System/WindowTypes/FrameWindow.h>
#include <CEGUI/System/WindowTypes/StaticText.h>
#include <CEGUI/System/WindowTypes/Listbox.h>

// Replace these with actual addresses and values
#define ADDRESS 0x00000000
#define VALUE 0

// Forward declarations
void initGUI();
void createMenu();
void createAddressEntry();
void createValueEntry();
void createActivateButton();
void createDeactivateButton();

// Global variables
CEGUI::Window* menuWindow;
CEGUI::Editbox* addressEntry;
CEGUI::Editbox* valueEntry;
CEGUI::Button* activateButton;
CEGUI::Button* deactivateButton;
bool enabled = false;

// Initialization
void Initialize() {
    initGUI();
    createMenu();
}

// GUI initialization
void initGUI() {
    CEGUI::OpenGLRenderer* renderer = static_cast<CEGUI::OpenGLRenderer*>(CEGUI::System::getSingleton().getRenderer());
    CEGUI::DefaultResourceProvider* resourceProvider = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
    resourceProvider->setResourceGroupDirectory("schemes", "TaharezLook");
    resourceProvider->setResourceGroupDirectory("imagesets", "TaharezLook");
    resourceProvider->setResourceGroupDirectory("fonts", "TaharezLook");
    resourceProvider->setResourceGroupDirectory("layouts", "layouts");
    renderer->setRenderCacheSize(1024);
    CEGUI::WidgetLookManager::getSingleton().setDefaultLookName("TaharezLook");
    CEGUI::WindowManager::getSingleton().loadScheme("TaharezLook.scheme");
    CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
}

// Create the main menu window
void createMenu() {
    menuWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("cheat_menu.layout");
    CEGUI::System::getSingleton().setGUISheet(menuWindow);
    createAddressEntry();
    createValueEntry();
    createActivateButton();
    createDeactivateButton();
}

// Create the address entry field
void createAddressEntry() {
    addressEntry = static_cast<CEGUI::Editbox*>(menuWindow->getChild("AddressEntry"));
    addressEntry->setText(CEGUI::String(ADDRESS));
}

// Create the value entry field
void createValueEntry() {
    valueEntry = static_cast<CEGUI::Editbox*>(menuWindow->getChild("ValueEntry"));
    valueEntry->setText(CEGUI::String(VALUE));
}

// Create the activate button
void createActivateButton() {
    activateButton = static_cast<CEGUI::Button*>(menuWindow->getChild("ActivateButton"));
    activateButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&activateButton_Clicked));
}

// Activate button event handler
bool activateButton_Clicked(const CEGUI::EventArgs& e) {
    if (!enabled) {
        enabled = true;
        VALUE = std::stoi(valueEntry->getText().c_str());
        std::cout << "Activated. Address: " << ADDRESS << ", Value: " << VALUE << std::endl;
    }
    return true;
}

// Create the deactivate button
void createDeactivateButton() {
    deactivateButton = static_cast<CEGUI::Button*>(menuWindow->getChild("DeactivateButton"));
    deactivateButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&deactivateButton_Clicked));
}

// Deactivate button event handler
bool deactivateButton_Clicked(const CEGUI::EventArgs& e) {
    if (enabled) {
        enabled = false;
        VALUE = 0;
        std::cout << "Deactivated. Address: " << ADDRESS << ", Value: " << VALUE << std::endl;
    }
    return true;
}