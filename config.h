#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by kumak98 on 05.12.2020.
//

#ifndef GRAFIKA3D_CONFIG_H
#define GRAFIKA3D_CONFIG_H

const GLfloat sunRadius = 		1.0;
const GLfloat mercuryRadius =	0.05;
const GLfloat venusRadius =	0.18;
const GLfloat earthRadius =    0.19;
const GLfloat marsRadius = 	0.09;
const GLfloat jupiterRadius = 	0.6;
const GLfloat saturnRadius = 	0.5;
const GLfloat uranusRadius = 	0.3;
const GLfloat neptuneRadius = 	0.3;

const GLfloat mercuryOrbitRadius = 1.5;
const GLfloat venusOrbitRadius =	 2.0;
const GLfloat earthOrbitRadius = 	 2.5;
const GLfloat marsOrbitRadius = 	 3.0;
const GLfloat jupiterOrbitRadius = 5.0;
const GLfloat saturnOrbitRadius =  7.0;
const GLfloat uranusOrbitRadius =	 8.5;
const GLfloat neptuneOrbitRadius = 9.5;

const GLfloat lightAmbient[]       = {0.5, 0.5, 0.5, 0.5};
const GLfloat lightDiffuse[]       = {0.5, 0.5, 0.5, 0.5};
const GLfloat lightSpecular[]      = {1.0, 1.0, 1.0, 1.0};

const GLfloat light0Position[]    = {0.0, 1.1, 0.0, 0.0};
const GLfloat light1Position[]    = {0.0, -1.1, 0.0, 0.0};
const GLfloat light2Position[]    = {1.1, 0.0, 0.0, 0.0};
const GLfloat light3Position[]    = {-1.1, 0.0, 0.0, 0.0};

const std::string sunTexturePath = "Textures/sunmap.bmp";
const std::string mercuryTexturePath = "Textures/mercurymap.bmp";
const std::string venusTexturePath = "Textures/venusmap.bmp";
const std::string earthTexturePath = "Textures/earthmap.bmp";
const std::string marsTexturePath = "Textures/marsmap.bmp";
const std::string jupiterTexturePath = "Textures/jupitermap.bmp";
const std::string saturnTexturePath = "Textures/saturnmap.bmp";
const std::string saturnRingTexturePath = "Textures/saturnringmap.bmp";
const std::string uranusTexturePath = "Textures/uranusmap.bmp";
const std::string neptuneTexturePath = "Textures/neptunemap.bmp";

#endif //GRAFIKA3D_CONFIG_H

#pragma clang diagnostic pop