#pragma once

#include "Animation.hpp"
#include <gl/glut.h>

class EmptyAnimation : public Animation {
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

void EmptyAnimation::baseTransform() {

}

void EmptyAnimation::animateHead() {

}

void EmptyAnimation::animateBody() {

}

void EmptyAnimation::animateLeftArm() {

}

void EmptyAnimation::animateLeftHand() {

}

void EmptyAnimation::animateRightArm() {

}

void EmptyAnimation::animateRightHand() {

}

void EmptyAnimation::animateLeftLeg() {

}

void EmptyAnimation::animateLeftFoot() {

}

void EmptyAnimation::animateRightLeg() {

}

void EmptyAnimation::animateRightFoot() {

}

