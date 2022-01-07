#include "window.h"

bool fullscreen = false;
GLfloat vertices[] = {
    // Vertex pos    // Texture coordinate
    -1.f, -1.f, 0.f, 0.f, 0.f,
     0.f, -1.f, 1.f, .5f, 0.f,
     1.f, -1.f, 0.f, 1.f, 0.f,
     0.f,  1.f, 0.f, .5f, 1.f
};
GLuint indices[] = {
    0, 3, 1,
    1, 3, 2,
    2, 3, 0,
    0, 1, 2
};
GLuint brickTexture, southAfricaTexture;
float light = 0.f;

void loop()
{
    // Set the background color
    Window::SetBgColor(0.f, 0.f, 0.f);
    // Clear the color and the depth buffers
    //Window::ResetBuffers();
    // key and mouse listener
    if (Listener::GetKeyPress(KEY_ESCAPE))
        Window::ExitLoop();
    else if (Listener::GetKeyPress(KEY_F11))
    {
        fullscreen = !fullscreen;
        Window::SetFullscreen(fullscreen);
    }
    Listener::FirstPersonListener();
    // Bind
    Mesh::BindWithProg();
    // Render
    Prog::UpdateView();
    if (light < 1.f)
    {
        light += .01f;
        Light::SetAmbient(light);
    }
    for (int y = -1; y <= 0; y++)
    {
        switch (y)
        {
        case -1:
            Texture::SetUniform(brickTexture);
            break;
        case 0:
            Texture::SetUniform(southAfricaTexture);
            break;
        }
        Prog::TranslateModel(0.f, y, 0.f);
        Prog::ScaleModel(.4f, .4f, 1.f);
        Prog::UpdateModel();
        Mesh::Render(sizeof(indices));
    }
    // Unbind
    Mesh::UnbindWithProg();
}

int main()
{
    // Initialise GLFW
    if(!glfwInit())
        err("Cannot initialise GLFW", nullptr);
    // Create the window
    Window::Create("Hello World", 800, 600);
    int bufferWidth = Window::GetBufferWidth();
    int bufferHeight = Window::GetBufferHeight();
    Window::InitLib();
    // Initialise GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        err("Cannot initialise GLEW", nullptr);
    // Set some window's stuff
    Window::SetViewport();
    Window::Enable3D();
    Window::DisableCursor();
    // Create the camera
    Camera::Create(1.f, 1.f);
    // Create the shape
    Mesh::CreateWithProgFromShaderFiles(indices, sizeof(indices), vertices, sizeof(vertices), "res/shaders/Vertex.glsl", "res/shaders/Fragment.glsl");
    info("Prog:", false);
    info(Prog::GetCurrentProg());
    info("Vao:", false);
    info(Mesh::GetCurrentVao());
    info("Vbo:", false);
    info(Mesh::GetCurrentVbo());
    info("Ibo:", false);
    info(Mesh::GetCurrentIbo());
    Prog::SetProjection(bufferWidth, bufferHeight, .1f, 100.f);
    brickTexture = Texture::Create("res/textures/bricks.png");
    southAfricaTexture = Texture::Create("res/textures/southafrica.jpg");
    Light::SetAmbient(light, 1.f, 1.f, 1.f);
    Mesh::UnbindWithProg();
    // Main loop
    Window::SetLoop(&loop);
    // Delete anything!!!1!1!1!11
    Mesh::DeleteWithProg();
    Window::Delete();
    return 0;
}