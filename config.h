#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by kumak98 on 05.12.2020.
//

#ifndef GRAFIKA3D_CONFIG_H
#define GRAFIKA3D_CONFIG_H

const GLfloat sunRadius = 1.0;
const GLfloat mercuryRadius = 0.05;
const GLfloat venusRadius =	0.18;
const GLfloat earthRadius = 0.19;
const GLfloat marsRadius = 0.09;
const GLfloat jupiterRadius = 0.6;
const GLfloat saturnRadius = 0.5;
const GLfloat uranusRadius = 0.3;
const GLfloat neptuneRadius = 0.3;
const GLfloat moonRadius = 0.04;

const GLfloat mercuryOrbitRadius = 1.5;
const GLfloat venusOrbitRadius = 2.5;
const GLfloat earthOrbitRadius = 3.5;
const GLfloat marsOrbitRadius = 4.5;
const GLfloat jupiterOrbitRadius = 7.0;
const GLfloat saturnOrbitRadius =  9.0;
const GLfloat uranusOrbitRadius = 10.5;
const GLfloat neptuneOrbitRadius = 11.5;
const GLfloat moonOrbitRadius = 0.5;

const GLfloat mercuryInclination = 7;
const GLfloat venusInclination = 3.4;
const GLfloat marsInclination = 1.9;
const GLfloat jupiterInclination = 1.3;
const GLfloat saturnInclination = 2.5;
const GLfloat uranusInclination = 0.8;
const GLfloat neptuneInclination = 1.8;
const GLfloat earthInclination = 0;

const GLfloat mercuryOrbitDuration = 88;
const GLfloat venusOrbitDuration = 224.7;
const GLfloat earthOrbitDuration = 365;
const GLfloat marsOrbitDuration = 687.0;
const GLfloat jupiterOrbitDuration = 4331;
const GLfloat saturnOrbitDuration = 10747;
const GLfloat uranusOrbitDuration = 30589;
const GLfloat neptuneOrbitDuration = 59800;
const GLfloat lunarCycle = 29.53;

const GLfloat mercuryRotationDuration = 1407.6 / 23.9;
const GLfloat venusRotationDuration = -5832.5 / 23.9;
const GLfloat marsRotationDuration = 1;
const GLfloat jupiterRotationDuration = 9.9/23.9;
const GLfloat saturnRotationDuration = 10.7/23.9;
const GLfloat uranusRotationDuration = -17.2/23.9;
const GLfloat neptuneRotationDuration = 16.1/23.9;

const GLfloat lightAmbient[] = {0.5, 0.5, 0.5, 0.5};
const GLfloat lightDiffuse[] = {0.5, 0.5, 0.5, 0.5};
const GLfloat lightSpecular[] = {1.0, 1.0, 1.0, 1.0};

const GLfloat light0Position[] = {0.0, 1.1, 0.0, 0.0};
const GLfloat light1Position[] = {0.0, -1.1, 0.0, 0.0};
const GLfloat light2Position[] = {1.1, 0.0, 0.0, 0.0};
const GLfloat light3Position[] = {-1.1, 0.0, 0.0, 0.0};

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
const std::string moonTexturePath = "Textures/moonmap.bmp";
#endif //GRAFIKA3D_CONFIG_H

#pragma clang diagnostic pop