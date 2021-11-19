#include "player.h"

Player::Player(const Vector3f& position, float rotX, float rotY) : m_RotX(rotX), m_RotY(rotY), m_isFly(false), 
                                                                    m_isFalling(false), m_fallTime(0.f), m_jumpTime(0.f),
                                                                    m_speed(WALK_SPEED)
{
    m_Position.x = position.x;
    m_Position.y = position.y;
    m_Position.z = position.z;
}


Player::~Player(){

}

bool Player::GetIsFalling() const{
    return m_isFalling;
}

void Player::SetIsFalling(bool isFalling){
    m_isFalling = isFalling;
}

void Player::ToggleisFly(){
    if(m_isFly)
        m_isFalling = true;
    else
        m_isFalling = false;
    m_isFly = !m_isFly;
}

void Player::TurnLeftRight(float value){
    m_RotY += value;
}

void Player::TurnTopBottom(float value){
    m_RotX += value;
    if(m_RotX > 90)
        m_RotX = 90;
    if(m_RotX < -90)
        m_RotX = -90;
}

void Player::CheckJump(float elapsedTime){
    if (m_isJumping && m_isFalling == false)
    {
        float transfY = 0.f;
        m_jumpTime += elapsedTime;
        transfY = .23f - 1.f * m_jumpTime;
        m_Position.y += transfY;
        if(m_Position.y > m_jumpHeight){
            m_isFalling = true;
            m_isJumping = false;
            m_jumpTime = 0;
        }
    }
    
}

void Player::SetIsJumping(bool isJumping){
    m_isJumping = isJumping;
}

void Player::SetSpeed(float speed){
    m_speed = speed;
}

bool Player::GetIsJumping() const{
    return m_isJumping;
}

void Player::SetMaxHeight(){
    m_jumpHeight = m_Position.y + 1.3f;
}

void Player::Jump(){
   if (m_isJumping == false && m_isFalling == false)
   {
       m_jumpTime = 0;
       m_isJumping = true;
   }


}

Vector3f Player::GetPosition() const{
    return m_Position;
}

void Player::SetPosition(Vector3f pos)
{
    m_Position = pos;
}

void Player::SetFallTime(float floatTime){
    m_fallTime = floatTime;
}

float Player::GetFallTime() const{
    return m_fallTime;
}

void Player::ApplyTransformation(Transformation& transformation) const{
    transformation.ApplyRotation(-m_RotX , 1.f, 0, 0);
    transformation.ApplyRotation(-m_RotY , 0, 1.f, 0);
    transformation.ApplyTranslation(-m_Position);
}

Vector3f Player::SimulateMove(bool front , bool back , bool left , bool right, float elapsedTime)
{
    float vitesse = m_speed;
    if(m_isFalling){
        vitesse = vitesse / 2;
    }

    Vector3f positionSimu(0,0,0);

    if (front)
    {
        float yrotrad;
        yrotrad = (m_RotY / 180 * 3.141592654f);
        
        positionSimu.x += float(sin(yrotrad)) * elapsedTime * vitesse;
        
        positionSimu.z -= float(cos(yrotrad))* elapsedTime * vitesse;

        if (m_isFly)
        {
            float xrotrad;
            xrotrad = (m_RotX / 180 * 3.141592654f);
            m_Position.y -= float(sin(xrotrad));
        }
    }
    if (back)
    {
        float yrotrad;
        yrotrad = (m_RotY / 180 * 3.141592654f);        
        positionSimu.x -= float(sin(yrotrad))* elapsedTime * vitesse;
        positionSimu.z += float(cos(yrotrad))* elapsedTime * vitesse;
        if (m_isFly)
        {
            float xrotrad;
            xrotrad = (m_RotX / 180 * 3.141592654f);
            m_Position.y += float(sin(xrotrad))* elapsedTime * vitesse;
        }
    }
    if (left)
    {
        float yrotrad;
        yrotrad = (m_RotY / 180 * 3.141592654f);
        positionSimu.x -= float(cos(yrotrad)) * elapsedTime * vitesse;
        positionSimu.z -= float(sin(yrotrad)) * elapsedTime * vitesse;
    }
    if (right)
    {
        float yrotrad;
        yrotrad = (m_RotY / 180 * 3.141592654f);
        positionSimu.x += float(cos(yrotrad)) * elapsedTime * vitesse;
        positionSimu.z +=  float(sin(yrotrad)) * elapsedTime * vitesse;
    }
    return positionSimu;
}
