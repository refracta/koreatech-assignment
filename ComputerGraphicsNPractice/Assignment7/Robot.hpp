#pragma once

#include <iomanip>
#include <gl/glut.h>
#include "Mesh.hpp"
#include "EmptyAnimation.hpp"
#include "Animation.hpp"
#include "RunAnimation.hpp"
#include "FlyKickAnimation.hpp"

#define ROBOT_MESH_PATH "parts\\"
#define ROBOT_MESH_LENGTH 10
#define TO_SCALED_F(x, y, z, scale) x / scale, y / scale, z / scale
using namespace std;

class Robot {
    Mesh Head;
    Mesh Body;
    Mesh LeftArm;
    Mesh LeftHand;
    Mesh LeftLeg;
    Mesh LeftFoot;
    Mesh RightArm;
    Mesh RightHand;
    Mesh RightLeg;
    Mesh *meshes[ROBOT_MESH_LENGTH] = {&Head,
                                       &Body,
                                       &LeftArm,
                                       &LeftFoot,
                                       &LeftHand,
                                       &LeftLeg,
                                       &RightArm,
                                       &RightFoot,
                                       &RightHand,
                                       &RightLeg
    };

    Mesh RightFoot;
    char const *paths[ROBOT_MESH_LENGTH] = {ROBOT_MESH_PATH "S_Head.ase",
                                            ROBOT_MESH_PATH "S_Body.ase",
                                            ROBOT_MESH_PATH "S_LeftArm.ase",
                                            ROBOT_MESH_PATH "S_LeftFoot.ase",
                                            ROBOT_MESH_PATH "S_LeftHand.ase",
                                            ROBOT_MESH_PATH "S_LeftLeg.ase",
                                            ROBOT_MESH_PATH "S_RightArm.ase",
                                            ROBOT_MESH_PATH "S_RightFoot.ase",
                                            ROBOT_MESH_PATH "S_RightHand.ase",
                                            ROBOT_MESH_PATH "S_RightLeg.ase"};

public:
    float scale = 100;
    bool bCoord = true;
    EmptyAnimation defaultAnimation;
    Animation* animation = &defaultAnimation;

    Robot() {
        cout << "Loading ASE files...................." << endl;
        for (int i = 0; i < ROBOT_MESH_LENGTH; i++) {
            const char *path = paths[i];
            Mesh *mesh = meshes[i];
            mesh->readAse(path);
            cout << "  loading " << left << setfill('.') << setw(25) << path << "OK." << endl;
        }
    }

    Robot(float scale, bool bCoord) : Robot() {
        this->scale = scale;
        this->bCoord = bCoord;
    }

    void draw() {
        animation->baseTransform();
        glPushMatrix();
            animation->animateBody();
            Body.draw(TO_COLOR_F(0x88C8C8), scale, bCoord);

            glPushMatrix();
                glTranslated(TO_SCALED_F(0, 28, 0, scale));
                animation->animateHead();
                Head.draw(TO_COLOR_F(0x01ADF0), scale);
            glPopMatrix();

            glPushMatrix();
                glTranslated(TO_SCALED_F(16, 8, 0, scale));
                animation->animateLeftArm();
                LeftArm.draw(TO_COLOR_F(0xA8A7AC), scale);
                    glPushMatrix();
                        glTranslated(TO_SCALED_F(0, -26, 0, scale));
                        animation->animateLeftHand();
                        LeftHand.draw(TO_COLOR_F(0x0D457A), scale);
                    glPopMatrix();
            glPopMatrix();

            glPushMatrix();
                glTranslated(TO_SCALED_F(5, -21, 0, scale));
                animation->animateLeftLeg();
                LeftLeg.draw(TO_COLOR_F(0xA8A7AC), scale);
                    glPushMatrix();
                        glTranslated(TO_SCALED_F(0, -19, 0, scale));
                        animation->animateLeftFoot();
                        LeftFoot.draw(TO_COLOR_F(0x0D457A), scale);
                    glPopMatrix();
            glPopMatrix();

            glPushMatrix();
                glTranslated(TO_SCALED_F(-16, 8, 0, scale));
                animation->animateRightArm();
                RightArm.draw(TO_COLOR_F(0xA8A7AC), scale);
                    glPushMatrix();
                        glTranslated(TO_SCALED_F(0, -26, 0, scale));
                        animation->animateRightHand();
                        RightHand.draw(TO_COLOR_F(0x0D457A), scale);
                    glPopMatrix();
            glPopMatrix();

            glPushMatrix();
                glTranslated(TO_SCALED_F(-5, -21, 0, scale));
                animation->animateRightLeg();
                RightLeg.draw(TO_COLOR_F(0xA8A7AC), scale);
                    glPushMatrix();
                        glTranslated(TO_SCALED_F(0, -19, 0, scale));
                        animation->animateRightFoot();
                        RightFoot.draw(TO_COLOR_F(0x0D457A), scale);
                    glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    }
};