#ifndef _DEBUG_H
#define _DEBUG_H

#include <bullet/btBulletDynamicsCommon.h>
#include <GL/glew.h>
#include <vector>

class DebugDraw : public btIDebugDraw {
  private:
    GLuint VBO, VAO;
    int mode;
    GLfloat* points;
    std::vector<btVector3>* lineData;

  private:
    void renderLines();
  public:
    DebugDraw();
    void start();
    void end();
    void clean();
    void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);
    void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);
    void reportErrorWarning(const char* warningString);
    void draw3dText(const btVector3& location, const char* textString);
    void setDebugMode(int debugMode);
    int getDebugMode() const;
};

#endif
