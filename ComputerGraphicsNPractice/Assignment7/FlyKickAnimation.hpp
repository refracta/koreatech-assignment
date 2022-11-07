#pragma once

#include <gl/glut.h>
#include "Animation.hpp"
#include "MathUtils.h"

class FlyKickAnimation : public Animation {
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

#define LIMIT(target, watch) (watch < target ? watch : target)

#define ANGLE 1080
#define ANGLE_2 540
#define ANGLE_4 270
int newTick;

void FlyKickAnimation::baseTransform() {
    newTick = tick - ANGLE_4;
    glRotatef(LIMIT(ANGLE, tick * 2), 0, 1, 0);
    if (tick * 2 < ANGLE_2) {
        glTranslated(0, LIMIT(0.8, tick / 250.0), 0);
        glRotatef(LIMIT(20, tick / 10.0), 1, 0, 1);
    } else if (tick * 2 < ANGLE) {
        glTranslated(0, 0.8 - LIMIT(0.8, newTick / 60.0), 0);
        glRotatef(20 - LIMIT(20, newTick / 10.0), 1, 0, 1);
    } else {
        tick = 0;
    }
}

void FlyKickAnimation::animateHead() {
    glRotatef(-5 * COS(tick), 0, 1, 0);
}

void FlyKickAnimation::animateBody() {
}

void FlyKickAnimation::animateLeftArm() {
    if (newTick < 0) {
        glTranslated(-LIMIT(0.04, tick / 1000.0), 0, 0);
        glRotatef(LIMIT(70, tick / 1.0), 0, 0, 1);
    } else {
        glTranslated(-0.04 + LIMIT(0.04, newTick / 1000.0), 0, 0);
        glRotatef(70 - LIMIT(70, newTick / 1.0), 0, 0, 1);
    }
    glRotatef(-5 * COS(tick), 0, 0, 1);
}

void FlyKickAnimation::animateLeftHand() {
    if (newTick < 0) {
        glRotatef(LIMIT(80, tick), 0, 0, 1);
    } else {
        glRotatef(80 - LIMIT(80, newTick), 0, 0, 1);
    }
}

void FlyKickAnimation::animateRightArm() {
    if (newTick < 0) {
        glTranslated(LIMIT(0.045, tick / 1000.0), 0, 0);
        glRotatef(-LIMIT(110, tick / 1.0), 0, 0, 1);
    } else {
        glTranslated(0.045 - LIMIT(0.045, newTick / 1000.0), 0, 0);
        glRotatef(-110 + LIMIT(110, newTick / 1.0), 0, 0, 1);
    }
    glRotatef(-5 * COS(tick), 0, 0, 1);
}

void FlyKickAnimation::animateRightHand() {
    if (newTick < 0) {
        glRotatef(LIMIT(80, tick), 0, 0, 1);
    } else {
        glRotatef(-80 + LIMIT(80, newTick), 0, 0, 1);
    }
}

void FlyKickAnimation::animateLeftLeg() {
    glRotatef(-5 * COS(tick) + 5, 1, 0, 0);
}

void FlyKickAnimation::animateLeftFoot() {
    glRotatef(-5 * SIN(tick) - 5, 1, 0, 0);
}


void FlyKickAnimation::animateRightLeg() {
    if (newTick < 0) {
        glRotatef(LIMIT(90, tick * 2), 1, 0, 0);
    } else {
        glRotatef(90 - LIMIT(90, newTick * 2), 1, 0, 0);
    }

    glRotatef(-5 * COS(tick) + 5, 1, 0, 0);
}

void FlyKickAnimation::animateRightFoot() {
    if (newTick < 0) {
        glRotatef(LIMIT(10, tick / 5.0), 1, 0, 0);
    } else {
        glRotatef(10 - LIMIT(10, newTick / 5.0), 1, 0, 0);
    }

    glRotatef(-5 * SIN(tick) - 5, 1, 0, 0);
}
