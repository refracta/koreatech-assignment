#pragma once

class Animation {
public:
    unsigned int tick = 0;

    virtual void baseTransform() = 0;
    virtual void animateHead() = 0;
    virtual void animateBody() = 0;
    virtual void animateLeftArm() = 0;
    virtual void animateLeftHand() = 0;
    virtual void animateRightArm() = 0;
    virtual void animateRightHand() = 0;
    virtual void animateLeftLeg() = 0;
    virtual void animateLeftFoot() = 0;
    virtual void animateRightLeg() = 0;
    virtual void animateRightFoot() = 0;
};