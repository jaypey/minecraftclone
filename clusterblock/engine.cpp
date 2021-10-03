#include "engine.h"
#include "transformation.h"
#include "player.h"
#include <algorithm>
#include <cmath>
#include <iostream>

Engine::Engine() : m_player(Vector3f(0,0,-5.f))
{
}

Engine::~Engine()
{
}

void Engine::Init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)Width() / (float)Height(), 0.0001f, 1000.0f);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);

    // Light
    GLfloat light0Pos[4] = { 0.0f, CHUNK_SIZE_Y, 0.0f, 1.0f };
    GLfloat light0Amb[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat light0Diff[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light0Spec[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0Spec);

    CenterMouse();
    HideCursor();
}

void Engine::DeInit()
{
}

void Engine::LoadResource()
{
    LoadTexture(m_textureFloor, TEXTURE_PATH "checker.png");
    LoadTexture(m_textureCube, TEXTURE_PATH "textureBlock.jpg");
}

void Engine::UnloadResource()
{
}

void Engine::Render(float elapsedTime)
{
    static float gameTime = elapsedTime;

    gameTime += elapsedTime;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Transformations initiales
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    m_player.Move(m_keyW, m_keyS, m_keyA, m_keyD, elapsedTime);
    //Player
    Transformation t;
    m_player.ApplyTransformation(t);
    t.Use();

    // Plancher
    // Les vertex doivent etre affiches dans le sens anti-horaire (CCW)
    m_textureFloor.Bind();
    float nbRep = 50.f;
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0); // Normal vector
    glTexCoord2f(0, 0);
    glVertex3f(-100.f, -2.f, 100.f);
    glTexCoord2f(nbRep, 0);
    glVertex3f(100.f, -2.f, 100.f);
    glTexCoord2f(nbRep, nbRep);
    glVertex3f(100.f, -2.f, -100.f);
    glTexCoord2f(0, nbRep);
    glVertex3f(-100.f, -2.f, -100.f);
    glEnd();


    //Cube
    m_textureCube.Bind();
    t.ApplyTranslation(0,0,-5.f);
    t.ApplyTranslation(sin(gameTime), 0, 0);
    t.ApplyRotation(gameTime * 100.f, 0, 0, 1.f);
    t.ApplyRotation(gameTime * 200.f, 0, 1.f, 0);
    t.Use();

//===============================================================
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);

    glTexCoord2f(0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glTexCoord2f(1, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);

    glTexCoord2f(1, 1);
    glVertex3f(0.5f, 0.5f, 0.5f);

    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
//=================================================================
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);

    glTexCoord2f(0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);

    glTexCoord2f(1, 0);
    glVertex3f(0.5f, -0.5f, -0.5f);

    glTexCoord2f(1, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);

    glTexCoord2f(0, 1);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glEnd();
//================================================================
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);

    glTexCoord2f(0, 0);
    glVertex3f(0.5f, -0.5f, -0.5f);

    glTexCoord2f(1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    glTexCoord2f(1, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    glTexCoord2f(0, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);
    
    glEnd();
//=================================================================
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);

    glTexCoord2f(0, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    glTexCoord2f(1, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glTexCoord2f(1, 1);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    
    glEnd();

    //===================================================================
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);

    glTexCoord2f(0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    glTexCoord2f(1, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);

    glTexCoord2f(1, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);

    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    
    glEnd();

    //===================================================================
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);

    glTexCoord2f(0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glTexCoord2f(1, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);

    glTexCoord2f(1, 1);
    glVertex3f(0.5f, -0.5f, -0.5f);

    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    
    glEnd();

}

void Engine::KeyPressEvent(unsigned char key)
{
    switch(key)
    {
        case 36: // ESC
            Stop();
            break;
        case 94: // F10
            SetFullscreen(!IsFullscreen());
            break;
        case 22: // W
            m_keyW = true;
            break;
        case 0:  // A
            m_keyA = true;
            break;
        case 18: // S
            m_keyS = true;
            break;
        case 3:  // D
            m_keyD = true;
            break;
        case 5: //F
            m_player.ToggleisFly();
            break;
        default:
            std::cout << "Unhandled key: " << (int)key << std::endl;
    }
}

void Engine::KeyReleaseEvent(unsigned char key)
{
    switch(key)
    {
        case 24: // Y
            m_wireframe = !m_wireframe;
            if(m_wireframe)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case 22: // W
            m_keyW = false;
            break;
        case 0:  // A
            m_keyA = false;
            break;
        case 18: // S
            m_keyS = false;
            break;
        case 3:  // D
            m_keyD = false;
            break;
    }
}

void Engine::MouseMoveEvent(int x, int y)
{
    // Centrer la souris seulement si elle n'est pas d�j� centr�e
    // Il est n�cessaire de faire la v�rification pour �viter de tomber
    // dans une boucle infinie o� l'appel � CenterMouse g�n�re un
    // MouseMoveEvent, qui rapelle CenterMouse qui rapelle un autre
    // MouseMoveEvent, etc

    if(x == (Width() / 2) && y == (Height() / 2))
        return;
    if(x < Width() / 2){
        m_player.TurnLeftRight(-0.2);
        std::cout << "left" << std::endl;
    }
    if(x > Width() / 2){
        m_player.TurnLeftRight(0.2);
        std::cout << "right" << std::endl;
    }
    if(y > Height() / 2){
        m_player.TurnTopBottom(0.2);
        std::cout << "back" << std::endl;
    }
    if(y < Height() / 2){
        m_player.TurnTopBottom(-0.2);
        std::cout << "front" << std::endl;
    }

    CenterMouse();
}

void Engine::MousePressEvent(const MOUSE_BUTTON& button, int x, int y)
{
}

void Engine::MouseReleaseEvent(const MOUSE_BUTTON& button, int x, int y)
{
}

bool Engine::LoadTexture(Texture& texture, const std::string& filename, bool stopOnError)
{
    texture.Load(filename);
    if(!texture.IsValid())
    {
        std::cerr << "Unable to load texture (" << filename << ")" << std::endl;
        if(stopOnError)
            Stop();

        return false;
    }

    return true;
}
