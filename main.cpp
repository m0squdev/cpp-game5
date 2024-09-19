#include "window.h"

GLfloat vertices[] = {
 // Vertex pos     // Tex coord // Normal
    -1.f, -1.f, -.6f, 0.f, 0.f,    0.f, 0.f, 0.f,
     0.f, -1.f,  1.f, .5f, 0.f,    0.f, 0.f, 0.f,
     1.f, -1.f, -.6f, 1.f, 0.f,    0.f, 0.f, 0.f,
     0.f,  1.f,  0.f, .5f, 1.f,    0.f, 0.f, 0.f
};
GLuint indices[] = {
    0, 3, 1,
    1, 3, 2,
    2, 3, 0,
    0, 1, 2
};
GLuint brickTexture, southAfricaTexture;
bool cursor = true;
bool fullscreen;
float light;

void loop()
{
    // Listen for keypresses and mouse movements
    if (Listener::GetKeyDown(KEY_ESCAPE))
        Window::ExitLoop();
    else if (Listener::GetKeyDown(KEY_F9))
    {
        cursor = !cursor;
        info(cursor);
        Window::SetCursor(cursor);
    }
    else if (Listener::GetKeyDown(KEY_F11))
    {
        fullscreen = !fullscreen;
        Window::SetFullscreen(fullscreen);
    }
    Listener::FirstPersonListener();
    // Bind
    Mesh::BindWithProg();
    // Render
    /*for (int n = 0; n < MAX_POINT_LIGHTS; n++)
    {
        //char locationBuffer[100] = { '\0' };
        //snprintf(locationBuffer, sizeof(locationBuffer), "pointLights[%d].color", n);
        Prog::BindUniform(strcat(strcat("pointLights[", (char*)n), "].color"));
    }*/
    Prog::UpdatePos();
    Prog::UpdateView();
    if (light < 1.f)
    {
        light += .01f;
        //Light::SetAmbient(light);
        //Light::SetDiffuse(2.f, -1.f, -2.f, light);
    }
    for (int y = 0; y <= 4; y += 4)
    {
        switch (y)
        {
        case 0:
            Material::Set(32.f);
            Texture::Set(brickTexture);
            break;
        case 4:
            Material::Set(4.f, .3f);
            Texture::Set(southAfricaTexture);
            break;
        }
        Prog::TranslateModel(0.f, y, 0.f);
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
    Window::Create("Hello World", 1366, 768);
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
    // Create the camera
    Camera::Create(1.f, 1.f);
    // Create the shape
    Mesh::CalcNormals(indices, 12, vertices, 32, 8, 5);
    Mesh::CreateWithProgFromShaderFiles(indices, sizeof(indices), vertices, sizeof(vertices), "res/shaders/Vertex.glsl", "res/shaders/Fragment.glsl");
    info(Prog::GetCurrentProg());
    info(Mesh::GetCurrentVao());
    info(Mesh::GetCurrentVbo());
    info(Mesh::GetCurrentIbo());
    Prog::SetProjection(bufferWidth, bufferHeight, .1f, 100.f);
    brickTexture = Texture::Create("res/textures/bricks.png");
    southAfricaTexture = Texture::Create("res/textures/southafrica.jpg");
    Light::SetAmbient(.2f);
    Light::SetDiffuse(2.f, -1.f, -2.f, .3f);
    Light::CreatePoint(.3f, .2f, .1f, 0.f, 2.f, 0.f, 0.f, 1.f, 0.f);
    Light::SetPoints();
    Mesh::UnbindWithProg();
    // Main loop
    Window::RunLoop(&loop);
    // Delete anything!!!1!1!1!11
    Mesh::DeleteWithProg();
    Window::Delete();
    return 0;
}
