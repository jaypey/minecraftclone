#ifndef PLAYER_H__
#define PLAYER_H__

#include "vector3.h"
#include "transformation.h"

class Player
{
private:
    Vector3f m_Position;
    float m_RotX;
    float m_RotY;
    bool m_isFly;
    bool m_isFalling;
    bool m_isJumping;
    float m_fallTime;
    float m_jumpTime;

public:
    Player(const Vector3f& position , float rotX = 0, float rotY = 0);
    ~Player();

    void ToggleisFly();
    void CheckFallState(const float &elapsedTime);
    Vector3f GetPosition() const;
    bool GetIsFalling() const;
    void Jump();
    void CheckJump(const float &elapsedTime);
    void TurnLeftRight(float value);
    void TurnTopBottom(float value);
    void Move(bool front , bool back , bool left , bool right , float elapsedTime);
    void ApplyTransformation(Transformation& transformation) const;

};

#endif