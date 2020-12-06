#include "pch.h"

typedef sf::Event sfe;
typedef sf::Keyboard sfk;

struct Spherical
{
    float distance, theta, fi;
    Spherical(float gdistance, float gtheta, float gfi) : distance(gdistance) , theta(gtheta), fi(gfi) { }
    float getX() const { return distance * std::cos(theta)*std::cos(fi); }
    float getY() const { return distance * std::sin(theta); }
    float getZ() const { return distance * std::cos(theta)*std::sin(fi); }
};

void drawPlanet(GLUquadric *quad, const std::string &textureName, GLfloat orbitRadius, GLfloat planetRadius,
                GLfloat orbitInclination, GLfloat CurrentEarthRotation, GLfloat rotationDuration,
                GLfloat orbitDuration);
void initOpenGL();
void reshapeScreen(sf::Vector2u size, float fov);
void
drawScene(Spherical camera, sf::Vector3f pos, sf::Vector3f scale, sf::Vector3f rot, GLfloat CurrentEarthRotation);


int main()
{
    Spherical camera(20.0f, 0.2f, 1.2f);
    sf::Vector3f pos(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), rot(0.0f, 0.0f, 0.0f);
    float fov = 45.0f, timer = 0.0, shift_key_state = 1.0f;
    GLfloat CurrentEarthRotation, EarthDayIncrement = 1;
    bool running = true;
    sf::ContextSettings context(24, 0, 10, 4, 5);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Solar system", 7U, context);
    sf::Clock clock;
    sf::Vector2i mouse_last_position(0, 0);

    window.setVerticalSyncEnabled(true);
    reshapeScreen(window.getSize(), fov);
    initOpenGL();

    while (running)
    {
        sfe event;
        sf::Time elapsed = clock.restart();
        timer += elapsed.asSeconds();

        CurrentEarthRotation = timer * EarthDayIncrement;

        while (window.pollEvent(event))
        {
            shift_key_state = 1.0f;

            if (event.type == sfe::Closed || (event.type == sfe::KeyPressed && event.key.code == sfk::Escape) ) running = false;
            if (event.type == sfe::Resized) reshapeScreen(window.getSize(), fov);

            if (event.type == sfe::MouseButtonPressed &&  event.mouseButton.button == sf::Mouse::Left)
            {
                mouse_last_position = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            }
            if (event.type == sfe::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                camera.fi += 2.0f / window.getSize().x *(event.mouseMove.x - mouse_last_position.x);
                camera.theta += 2.0f / window.getSize().y*(event.mouseMove.y - mouse_last_position.y);
                mouse_last_position = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            }
        }
        if (sfk::isKeyPressed(sfk::Left)) camera.fi -= 0.01f;
        if (sfk::isKeyPressed(sfk::Right)) camera.fi += 0.01f;
        if (sfk::isKeyPressed(sfk::Up)) camera.theta += 0.01f;
        if (sfk::isKeyPressed(sfk::Down)) camera.theta -= 0.01f;

        if (sfk::isKeyPressed(sfk::LShift)) shift_key_state = -1.0f;
        if (sfk::isKeyPressed(sfk::Q)) pos.x += 0.05f*shift_key_state;
        if (sfk::isKeyPressed(sfk::A)) pos.y += 0.05f*shift_key_state;
        if (sfk::isKeyPressed(sfk::Z)) pos.z += 0.05f*shift_key_state;
        if (sfk::isKeyPressed(sfk::W)) scale.x += 0.05f*shift_key_state;
        if (sfk::isKeyPressed(sfk::S)) scale.y += 0.05f*shift_key_state;
        if (sfk::isKeyPressed(sfk::X)) scale.z += 0.05f*shift_key_state;
        if (sfk::isKeyPressed(sfk::E)) rot.x += 0.5f*shift_key_state;
        if (sfk::isKeyPressed(sfk::D)) rot.y += 0.5f*shift_key_state;
        if (sfk::isKeyPressed(sfk::C)) rot.z += 0.5f*shift_key_state;

        if (sfk::isKeyPressed(sfk::LBracket)) { fov -= 1.0f; reshapeScreen(window.getSize(), fov); }
        if (sfk::isKeyPressed(sfk::RBracket)) { fov += 1.0f; reshapeScreen(window.getSize(), fov); }

        if (sfk::isKeyPressed(sfk::Num9)) { EarthDayIncrement -=1; }
        if (sfk::isKeyPressed(sfk::Num0)) { EarthDayIncrement +=1; }
        drawScene(camera, pos, scale, rot, CurrentEarthRotation);
        window.display();
    }
    return 0;
}

void drawPlanet(GLUquadric *quad, const std::string &textureName, const GLfloat orbitRadius, const GLfloat planetRadius,
                const GLfloat orbitInclination, const GLfloat CurrentEarthRotation, const GLfloat rotationDuration,
                const GLfloat orbitDuration) {
    glPushMatrix();
        sf::Texture mercuryTexture;
        mercuryTexture.setSmooth(true);
        mercuryTexture.loadFromFile(textureName);
        glColor3f(1,1,1);
        sf::Texture::bind(&mercuryTexture);
        gluQuadricTexture(quad, true);
        glRotatef( orbitInclination, 0.0, 0.0, 1.0);
        glRotatef( 360.0 * (CurrentEarthRotation/orbitDuration), 0.0, 1.0, 0.0);
        glTranslatef(orbitRadius,0,0);
        glRotatef( 360.0 * (CurrentEarthRotation /
        rotationDuration), 0.0, 1.0, 0.0 );
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluSphere(quad,planetRadius,100,100);
    glPopMatrix();
}

void reshapeScreen(sf::Vector2u size, float fov) {
    glViewport(0, 0, (GLsizei)size.x, (GLsizei)size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (GLdouble)size.x / (GLdouble)size.y, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);

    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);

    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2Position);

    glLightfv(GL_LIGHT3, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT3, GL_POSITION, light3Position);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
}

void drawScene(Spherical camera, sf::Vector3f pos, sf::Vector3f scale, sf::Vector3f rot,
               const GLfloat CurrentEarthRotation) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)
    glLoadIdentity();

    Spherical north_of_camera(camera.distance, camera.theta + 0.01f, camera.fi);
    gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
              0.0, 0.0, 0.0,
              north_of_camera.getX(), north_of_camera.getY(), north_of_camera.getZ());

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-100.0, 0, 0); glVertex3f(100.0, 0, 0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0, -100.0, 0); glVertex3f(0, 100.0, 0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0, 0, -100.0); glVertex3f(0, 0, 100.0);
    glEnd();


    glTranslatef(pos.x, pos.y, pos.z);
    glRotatef(rot.x, 1, 0, 0);
    glRotatef(rot.y, 0, 1, 0);
    glRotatef(rot.z, 0, 0, 1);
    glScalef(scale.x, scale.y, scale.z);

    glEnable(GL_LIGHTING);
    GLUquadric *quad;
    quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);

    // Sun
    glPushMatrix();
    sf::Texture sunTexture;
    sunTexture.setSmooth(true);
    sunTexture.loadFromFile(sunTexturePath);
    glEnable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
    sf::Texture::bind(&sunTexture);
    gluQuadricTexture(quad, true);
    glTranslatef(0,0,0);
    gluSphere(quad, sunRadius, 100, 100);
    glPopMatrix();

    //Mercury
    drawPlanet(quad, mercuryTexturePath, mercuryOrbitRadius, mercuryRadius, mercuryInclination, CurrentEarthRotation,
               mercuryRotationDuration, mercuryOrbitDuration);

    //Venus
    drawPlanet(quad, venusTexturePath, venusOrbitRadius, venusRadius, venusInclination, CurrentEarthRotation,
               venusRotationDuration, venusOrbitDuration);


    //Earth
    glPushMatrix();
        glPushMatrix();
            sf::Texture earthTexture;
            earthTexture.setSmooth(true);
            earthTexture.loadFromFile(earthTexturePath);
            glColor3f(1,1,1);
            sf::Texture::bind(&earthTexture);
            gluQuadricTexture(quad, true);
            glRotatef(earthInclination, 0.0, 0.0, 1.0);
            glRotatef( 360.0 * (CurrentEarthRotation/earthOrbitDuration), 0.0, 1.0, 0.0);
            glTranslatef(earthOrbitRadius,0,0);
            glRotatef( 360.0 * (CurrentEarthRotation), 0.0, 1.0, 0.0 );
            glRotatef( 90.0, 1.0, 0.0, 0.0 );
            gluSphere(quad, earthRadius, 100, 100);
        glPopMatrix();
        glRotatef(earthInclination, 0.0, 0.0, 1.0);
        glRotatef( 360.0 * (CurrentEarthRotation/earthOrbitDuration), 0.0, 1.0, 0.0);
        glTranslatef(earthOrbitRadius, 0.0, 0.0 );
        glRotatef( 360.0 * (CurrentEarthRotation / lunarCycle), 0.0, 1.0, 0.0 );
        glTranslatef(moonOrbitRadius  , 0.0, 0.0 );
        sf::Texture moonTexture;
        moonTexture.setSmooth(true);
        moonTexture.loadFromFile(moonTexturePath);
        glColor3f(1,1,1);
        sf::Texture::bind(&moonTexture);
        gluQuadricTexture(quad, true);
        gluSphere(quad, moonRadius, 48, 48);
    glPopMatrix();


    //Mars
    drawPlanet(quad, marsTexturePath, marsOrbitRadius, marsRadius, marsInclination, CurrentEarthRotation,
               marsRotationDuration, marsOrbitDuration);

    //Jupiter
    drawPlanet(quad, jupiterTexturePath, jupiterOrbitRadius, jupiterRadius, jupiterInclination, CurrentEarthRotation, jupiterRotationDuration, jupiterOrbitDuration);

    //Saturn
    drawPlanet(quad, saturnTexturePath, saturnOrbitRadius, saturnRadius, saturnInclination, CurrentEarthRotation, saturnRotationDuration, saturnOrbitDuration);


    //Saturn Rings
    glPushMatrix();
        sf::Texture saturnRingsTexture;
        saturnRingsTexture.setSmooth(true);
        saturnRingsTexture.loadFromFile(saturnRingTexturePath);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glPushMatrix();
        sf::Texture::bind(&saturnRingsTexture);
        gluQuadricTexture(quad, true);
        glRotatef(saturnInclination, 0.0, 0.0, 1.0);
        glRotatef( 360.0 * (CurrentEarthRotation/saturnOrbitDuration), 0.0, 1.0, 0.0);
        glTranslatef(saturnOrbitRadius, 0.0, 0.0 );
        glRotatef( 360.0 * (CurrentEarthRotation /
                            saturnRotationDuration), 0.0, 1.0, 0.0 );
        glRotatef( 90.0, 1.0, 0.0, 0.0 );
        glScalef(1,1,.02);
        gluSphere(quad, saturnRadius * 2, 100, 100);
    glPopMatrix();

    //Uranus
    drawPlanet(quad, uranusTexturePath, uranusOrbitRadius, uranusRadius, uranusInclination, CurrentEarthRotation, uranusRotationDuration, uranusOrbitDuration);

    //Neptune
    drawPlanet(quad, neptuneTexturePath, neptuneOrbitRadius, neptuneRadius, neptuneInclination, CurrentEarthRotation, neptuneRotationDuration, neptuneOrbitDuration);

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}
