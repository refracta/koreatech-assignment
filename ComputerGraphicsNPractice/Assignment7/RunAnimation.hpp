#pragma once

#include <gl/glut.h>
#include "Animation.hpp"
#include "MathUtils.h"

class RunAnimation : public Animation {
public:
    virtual void baseTransform();
    virtual void animateHead();
    virtual void animateBody();
    virtual void animateLeftArm();
    virtual void animateLeftHand();
    virtual void animateRightArm();
    virtual void animateRightHand();
    virtual void animateLeftLeg();
    virtual void animateLeftFoot();
    virtual void animateRightLeg();
    virtual void animateRightFoot();
};

void RunAnimation::baseTransform() {

}

void RunAnimation::animateHead() {
    glRotatef(-20 * COS(tick), 0, 1, 0);
}

void RunAnimation::animateBody() {
    glTranslated(0.0, 0.08 * SIN(2 * tick), 0);
    glRotatef(-SIN(2 * tick) - 10, 1, 0, 0);
    glRotatef(-SIN(tick), 0, 1, 0);
}

void RunAnimation::animateLeftArm() {
    glRotatef(65 * COS(tick), 1, 0, 0);
}

void RunAnimation::animateLeftHand() {
    glRotatef(45 * COS(tick) + 70, 1, 0, 0);
    glRotatef(20 * SIN(tick) + 20, 0, 1, 0);
}

void RunAnimation::animateRightArm() {
    glRotatef(-65 * COS(tick), 1, 0, 0);
}

void RunAnimation::animateRightHand() {
    glRotatef(-45 * COS(tick) + 70, 1, 0, 0);
    glRotatef(-20 * SIN(tick) - 20, 0, 1, 0);
}

void RunAnimation::animateLeftLeg() {
    glRotatef(-45 * COS(tick) + 35, 1, 0, 0);
}

void RunAnimation::animateLeftFoot() {
    glRotatef(-50 * SIN(tick) - 55, 1, 0, 0);
}

void RunAnimation::animateRightLeg() {
    glRotatef(45 * COS(tick) + 35, 1, 0, 0);
}

void RunAnimation::animateRightFoot() {

    glRotatef(50 * SIN(tick) - 55, 1, 0, 0);
}
