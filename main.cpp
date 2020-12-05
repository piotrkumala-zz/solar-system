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

Spherical camera(30.0f, 0.2f, 1.2f), light_position(4.0f, 0.2f, 1.2f);
sf::Vector3f pos(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f), rot(0.0f, 0.0f, 0.0f);
float fov = 45.0f;
float timer = 0.0;

void initOpenGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  LIGHT_AMBIENT);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  LIGHT_DIFFUSE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
    glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);

    glLightfv(GL_LIGHT1, GL_DIFFUSE,  LIGHT_DIFFUSE);
    glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT_SPECULAR);
    glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);

    glLightfv(GL_LIGHT2, GL_DIFFUSE,  LIGHT_DIFFUSE);
    glLightfv(GL_LIGHT2, GL_SPECULAR, LIGHT_SPECULAR);
    glLightfv(GL_LIGHT2, GL_POSITION, LIGHT_2_POSITION);

    glLightfv(GL_LIGHT3, GL_AMBIENT,  LIGHT_AMBIENT);
    glLightfv(GL_LIGHT3, GL_DIFFUSE,  LIGHT_DIFFUSE);
    glLightfv(GL_LIGHT3, GL_SPECULAR, LIGHT_SPECULAR);
    glLightfv(GL_LIGHT3, GL_POSITION, LIGHT_3_POSITION);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_ambient_global[4] = { 0.1,0.1,0.1, 0.1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient_global);
}

void reshapeScreen(sf::Vector2u size)
{
    glViewport(0, 0, (GLsizei)size.x, (GLsizei)size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (GLdouble)size.x / (GLdouble)size.y, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    sunTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/sunmap.bmp");
    glEnable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
    sf::Texture::bind(&sunTexture);
    gluQuadricTexture(quad, true);
    glTranslatef(0,0,0);
    gluSphere(quad,SUN_RADIUS,100,100);
    glPopMatrix();

    //Mercury
    glPushMatrix();
    sf::Texture mercuryTexture;
    mercuryTexture.setSmooth(true);
    mercuryTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/mercurymap.bmp");
    glColor3f(1,1,1);
    sf::Texture::bind(&mercuryTexture);
    gluQuadricTexture(quad, true);
    glTranslatef(MERCURY_ORBIT_RADIUS,0,0);
    gluSphere(quad,MERCURY_RADIUS,100,100);
    glPopMatrix();

    //Venus
    glPushMatrix();
    sf::Texture venusTexture;
    venusTexture.setSmooth(true);
    venusTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/venusmap.bmp");
    glColor3f(1,1,1);
    sf::Texture::bind(&venusTexture);
    gluQuadricTexture(quad, true);
    glTranslatef(VENUS_ORBIT_RADIUS,0,0);
    gluSphere(quad,VENUS_RADIUS,100,100);
    glPopMatrix();

    //Earth
    glPushMatrix();
    sf::Texture earthTexture;
    earthTexture.setSmooth(true);
    earthTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/earthmap.bmp");
    glColor3f(1,1,1);
    sf::Texture::bind(&earthTexture);
    gluQuadricTexture(quad, true);
    glRotatef( 90.0, 1.0, 0.0, 0.0 );
    glTranslatef(EARTH_ORBIT_RADIUS,0,0);
    gluSphere(quad, EARTH_RADIUS,100,100);
    glPopMatrix();


    //Mars
    glPushMatrix();
    sf::Texture matrixTexture;
    matrixTexture.setSmooth(true);
    matrixTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/marsmap.bmp");
    glColor3f(1,1,1);
    sf::Texture::bind(&matrixTexture);
    gluQuadricTexture(quad, true);
    glRotatef( 90.0, 1.0, 0.0, 0.0 );
    glTranslatef(MARS_ORBIT_RADIUS,0,0);
    gluSphere(quad, MARS_RADIUS,100,100);
    glPopMatrix();

    //Jupiter
    glPushMatrix();
    sf::Texture jupiterTexture;
    jupiterTexture.setSmooth(true);
    jupiterTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/jupitermap.bmp");
    glColor3f(1,1,1);
    sf::Texture::bind(&jupiterTexture);
    gluQuadricTexture(quad, true);
    glRotatef( 90.0, 1.0, 0.0, 0.0 );
    glTranslatef(JUPITER_ORBIT_RADIUS,0,0);
    gluSphere(quad, JUPITER_RADIUS,100,100);
    glPopMatrix();

    //Saturn
    glPushMatrix();
    sf::Texture saturnTexture;
    saturnTexture.setSmooth(true);
    saturnTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/saturnmap.bmp");
    glColor3f(1,1,1);
    sf::Texture::bind(&saturnTexture);
    gluQuadricTexture(quad, true);
    glRotatef( 90.0, 1.0, 0.0, 0.0 );
    glTranslatef(SATURN_ORBIT_RADIUS,0,0);
    gluSphere(quad, SATURN_RADIUS,100,100);
    glPopMatrix();

    //Saturn Rings
    glPushMatrix();
    sf::Texture saturnRingsTexture;
    saturnRingsTexture.setSmooth(true);
    saturnRingsTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/saturnringmap.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glPushMatrix();
    sf::Texture::bind(&saturnRingsTexture);
    gluQuadricTexture(quad, true);
    glTranslatef(SATURN_ORBIT_RADIUS, 0.0, 0.0 );
    glRotatef( 90.0, 1.0, 0.0, 0.0 );
    glScalef(1,1,.02);
    gluSphere(quad, SATURN_RADIUS*2, 100, 100);
    glPopMatrix();

    //Uranus
    glPushMatrix();
    sf::Texture uranusTexture;
    uranusTexture.setSmooth(true);
    uranusTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/uranusmap.bmp");
    glColor3f(1,1,1);
    sf::Texture::bind(&uranusTexture);
    gluQuadricTexture(quad, true);
    glRotatef( 90.0, 1.0, 0.0, 0.0 );
    glTranslatef(URANUS_ORBIT_RADIUS,0,0);
    gluSphere(quad, URANUS_RADIUS,100,100);
    glPopMatrix();

    //Neptune
    glPushMatrix();
    sf::Texture neptuneTexture;
    neptuneTexture.setSmooth(true);
    neptuneTexture.loadFromFile("/home/kumak98/CLionProjects/grafika3D/cmake-build-debug/Textures/neptunemap.bmp");
    glColor3f(1,1,1);
    sf::Texture::bind(&neptuneTexture);
    gluQuadricTexture(quad, true);
    glRotatef( 90.0, 1.0, 0.0, 0.0 );
    glTranslatef(NEPTUNE_ORBIT_RADIUS,0,0);
    gluSphere(quad, NEPTUNE_RADIUS,100,100);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}

int main()
{
    bool running = true;
    sf::ContextSettings context(24, 0, 4, 4, 5);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Open GL Lab1 04", 7U, context);
    int shift_key_state = 1;
    sf::Clock clock;
    sf::Vector2i mouse_last_position(0, 0); //new

    window.setVerticalSyncEnabled(true);
    reshapeScreen(window.getSize());
    initOpenGL();

    while (running)
    {
        sfe event;
        sf::Time elapsed = clock.restart();
        timer += elapsed.asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sfe::Closed || (event.type == sfe::KeyPressed && event.key.code == sfk::Escape) ) running = false;
            if (event.type == sfe::Resized) reshapeScreen(window.getSize());
            //---------------------- BEGIN new -------------------------------------------------------
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
            //---------------------- END new -------------------------------------------------------
        }
        if (sfk::isKeyPressed(sfk::Left)) camera.fi -= 0.01f;
        if (sfk::isKeyPressed(sfk::Right)) camera.fi += 0.01f;
        if (sfk::isKeyPressed(sfk::Up)) camera.theta += 0.01f;
        if (sfk::isKeyPressed(sfk::Down)) camera.theta -= 0.01f;

        if (sfk::isKeyPressed(sfk::I)) light_position.fi -= 0.01f;
        if (sfk::isKeyPressed(sfk::O)) light_position.fi += 0.01f;
        if (sfk::isKeyPressed(sfk::K)) light_position.theta += 0.01f;
        if (sfk::isKeyPressed(sfk::L)) light_position.theta -= 0.01f;

        if (sfk::isKeyPressed(sfk::LShift)) shift_key_state = -1;
        if (sfk::isKeyPressed(sfk::Q)) pos.x += 0.01f*shift_key_state;
        if (sfk::isKeyPressed(sfk::A)) pos.y += 0.01f*shift_key_state;
        if (sfk::isKeyPressed(sfk::Z)) pos.z += 0.01f*shift_key_state;
        if (sfk::isKeyPressed(sfk::W)) scale.x += 0.01f*shift_key_state;
        if (sfk::isKeyPressed(sfk::S)) scale.y += 0.01f*shift_key_state;
        if (sfk::isKeyPressed(sfk::X)) scale.z += 0.01f*shift_key_state;
        if (sfk::isKeyPressed(sfk::E)) rot.x += 0.5f*shift_key_state;
        if (sfk::isKeyPressed(sfk::D)) rot.y += 0.5f*shift_key_state;
        if (sfk::isKeyPressed(sfk::C)) rot.z += 0.5f*shift_key_state;

        if (sfk::isKeyPressed(sfk::LBracket)) { fov -= 1.0f; reshapeScreen(window.getSize()); }
        if (sfk::isKeyPressed(sfk::RBracket)) { fov += 1.0f; reshapeScreen(window.getSize()); }

        drawScene();
        window.display();
    }
    return 0;
}