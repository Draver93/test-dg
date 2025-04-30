#include "GameContext.h"

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <GLES3/gl3.h>
#include <memory>
#include <vector>
#include <android/imagedecoder.h>

#include "AndroidOut.h"
#include "Utility.h"
#include "TextureAsset.h"
#include "scripts/RotationScript.h"
#include "core/system/EventDispatcher.h"
#include "core/system/ResourceDirector.h"

//! executes glGetString and outputs the result to logcat
#define PRINT_GL_STRING(s) {aout << #s": "<< glGetString(s) << std::endl;}

/*!
 * @brief if glGetString returns a space separated list of elements, prints each one on a new line
 *
 * This works by creating an istringstream of the input c-style string. Then that is used to create
 * a vector -- each element of the vector is a new element in the input string. Finally a foreach
 * loop consumes this and outputs it to logcat using @a aout
 */
#define PRINT_GL_STRING_AS_LIST(s) { \
std::istringstream extensionStream((const char *) glGetString(s));\
std::vector<std::string> extensionList(\
        std::istream_iterator<std::string>{extensionStream},\
        std::istream_iterator<std::string>());\
aout << #s":\n";\
for (auto& extension: extensionList) {\
    aout << extension << "\n";\
}\
aout << std::endl;\
}

//! Color for cornflower blue. Can be sent directly to glClearColor
#define CORNFLOWER_BLUE 100 / 255.f, 149 / 255.f, 237 / 255.f, 1

GameContext::GameContext(android_app *pApp) :
        m_App(pApp),
        m_Display(EGL_NO_DISPLAY),
        m_Surface(EGL_NO_SURFACE),
        m_Context(EGL_NO_CONTEXT),
        m_PreviousTime(Clock::now()) {
        DGEngine::GLTFLoader::Init(pApp->activity->assetManager);

        m_ActiveScene = std::make_shared<DGEngine::GameScene>();
        initRenderer();
    }


GameContext::~GameContext() {
    if (m_Display != EGL_NO_DISPLAY) {
        eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (m_Context != EGL_NO_CONTEXT) {
            eglDestroyContext(m_Display, m_Context);
            m_Context = EGL_NO_CONTEXT;
        }
        if (m_Surface != EGL_NO_SURFACE) {
            eglDestroySurface(m_Display, m_Surface);
            m_Surface = EGL_NO_SURFACE;
        }
        eglTerminate(m_Display);
        m_Display = EGL_NO_DISPLAY;
    }
    DGEngine::ResourceDirector::Clear();
}

void GameContext::update() {
    // clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    TimePoint currentTime = Clock::now();
    std::chrono::duration<float> deltaTime = currentTime - m_PreviousTime;
    m_PreviousTime = currentTime;

    if(m_ActiveScene) {
        m_ActiveScene->Update(deltaTime.count());
    }
    handleInput();
    // Present the rendered image. This is an implicit glFlush.
    auto swapResult = eglSwapBuffers(m_Display, m_Surface);
    assert(swapResult == EGL_TRUE);
}

void GameContext::initRenderer() {
    // Choose your render attributes
    constexpr EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
    };

    // The default display is probably what you want on Android
    auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    // figure out how many configs there are
    EGLint numConfigs;
    eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);

    // get the list of configurations
    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

    // Find a config we like.
    // Could likely just grab the first if we don't care about anything else in the config.
    // Otherwise hook in your own heuristic
    auto config = *std::find_if(
            supportedConfigs.get(),
            supportedConfigs.get() + numConfigs,
            [&display](const EGLConfig &config) {
                EGLint red, green, blue, depth;
                if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red)
                    && eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green)
                    && eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue)
                    && eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth)) {

                    aout << "Found config with " << red << ", " << green << ", " << blue << ", "
                         << depth << std::endl;
                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }
                return false;
            });

    aout << "Found " << numConfigs << " configs" << std::endl;
    aout << "Chose " << config << std::endl;

    // create the proper window surface
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    EGLSurface surface = eglCreateWindowSurface(display, config, m_App->window, nullptr);

    // Create a GLES 3 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext context = eglCreateContext(display, config, nullptr, contextAttribs);

    // Get some window metrics
    auto madeCurrent = eglMakeCurrent(display, surface, surface, context);
    assert(madeCurrent);

    m_Display = display;
    m_Surface = surface;
    m_Context = context;

    PRINT_GL_STRING(GL_VENDOR);
    PRINT_GL_STRING(GL_RENDERER);
    PRINT_GL_STRING(GL_VERSION);
    PRINT_GL_STRING_AS_LIST(GL_EXTENSIONS);

    // setup any other gl related global states
    glClearColor(CORNFLOWER_BLUE);

    // enable alpha globally for now, you probably don't want to do this in a game
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Get some demo models into memory
    createModels();
}

void GameContext::createModels() {
    if(m_ActiveScene) {
        std::shared_ptr<DGEngine::GameObject> model = DGEngine::GameDirector::CreateModel("Cube/Cube.gltf");
        model->AddComponent<RotationScript>();
        m_ActiveScene->AddGameObject(model);

        std::shared_ptr<DGEngine::GameObject> camera = DGEngine::GameDirector::CreateCamera( m_Display, m_Surface );
        DGEngine::Transform* transform = camera->GetComponent<DGEngine::Transform>();
        transform->position[2] = -10;
        m_ActiveScene->AddGameObject(camera);

        std::shared_ptr<DGEngine::GameObject> l1 = DGEngine::GameDirector::CreateLight( glm::vec3(1.0f, 0.0f, 1.0f), 1.0f );
        transform = l1->GetComponent<DGEngine::Transform>();
        transform->position = glm::vec3{10, 10, 0};
        m_ActiveScene->AddGameObject(l1);

        std::shared_ptr<DGEngine::GameObject> l2 = DGEngine::GameDirector::CreateLight( glm::vec3(0.0f, 1.0f, 1.0f), 1.0f );
        transform = l2->GetComponent<DGEngine::Transform>();
        transform->position = glm::vec3{-10, 10, 0};
        m_ActiveScene->AddGameObject(l2);

        std::shared_ptr<DGEngine::GameObject> l3 = DGEngine::GameDirector::CreateLight( glm::vec3(1.0f, 1.0f, 0.0f), 1.0f );
        transform = l3->GetComponent<DGEngine::Transform>();
        transform->position = glm::vec3{0, 0, -10};
        m_ActiveScene->AddGameObject(l3);
    }
}

void GameContext::handleInput() {
    auto *inputBuffer = android_app_swap_input_buffers(m_App);
    if (!inputBuffer) return;

    auto& eventDispatcher = DGEngine::EventDispatcher::Get();

    // Handle motion (touch) events
    for (int i = 0; i < inputBuffer->motionEventsCount; ++i) {
        auto& motionEvent = inputBuffer->motionEvents[i];
        auto action = motionEvent.action;
        int pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

        const auto& pointer = motionEvent.pointers[pointerIndex];
        glm::vec2 pointer_pos = { GameActivityPointerAxes_getX(&pointer), GameActivityPointerAxes_getY(&pointer) };

        using TouchType = DGEngine::TouchEvent::Type;
        TouchType type;

        switch (action & AMOTION_EVENT_ACTION_MASK) {
            case AMOTION_EVENT_ACTION_DOWN:
            case AMOTION_EVENT_ACTION_POINTER_DOWN:
                type = TouchType::Down;
                break;
            case AMOTION_EVENT_ACTION_UP:
            case AMOTION_EVENT_ACTION_POINTER_UP:
            case AMOTION_EVENT_ACTION_CANCEL:
                type = TouchType::Up;
                break;
            case AMOTION_EVENT_ACTION_MOVE:
                // For move, push events for all active pointers
                for (int j = 0; j < motionEvent.pointerCount; ++j) {
                    const auto& p = motionEvent.pointers[j];
                    glm::vec2 pos = { GameActivityPointerAxes_getX(&p), GameActivityPointerAxes_getY(&p) };
                    auto evt = std::make_unique<DGEngine::TouchEvent>(DGEngine::TouchEvent{p.id, pos, TouchType::Move, m_App});
                    eventDispatcher.QueueEvent(std::move(evt));
                }
                continue;
            default:
                continue;
        }

        auto evt = std::make_unique<DGEngine::TouchEvent>(DGEngine::TouchEvent{pointer.id, pointer_pos, type, m_App});
        eventDispatcher.QueueEvent(std::move(evt));
    }

    android_app_clear_motion_events(inputBuffer);

    // Handle key events
    for (int i = 0; i < inputBuffer->keyEventsCount; ++i) {
        auto& keyEvent = inputBuffer->keyEvents[i];
        using KeyType = DGEngine::KeyEvent::Type;

        KeyType type;
        switch (keyEvent.action) {
            case AKEY_EVENT_ACTION_DOWN: type = KeyType::Down; break;
            case AKEY_EVENT_ACTION_UP:   type = KeyType::Up;   break;
            default: continue;
        }

        auto evt = std::make_unique<DGEngine::KeyEvent>(DGEngine::KeyEvent{keyEvent.keyCode, type, m_App});
        eventDispatcher.QueueEvent(std::move(evt));
    }

    android_app_clear_key_events(inputBuffer);
    eventDispatcher.PumpEvents();
}