#include <iostream>
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;

int main() {
  vector<rp3d::RigidBody*> bodies;

  cout << "Setting up simulation world" << endl;

  // rp3d::PhysicsCommon common;
  // rp3d::PhysicsWorld* world = common.createPhysicsWorld();
  rp3d::DynamicsWorld* world = new rp3d::DynamicsWorld(rp3d::Vector3(0, -10, 0));

  rp3d::RigidBody* body = world->createRigidBody(rp3d::Transform(rp3d::Vector3(0, 0, 0), rp3d::Quaternion::fromEulerAngles(0, 0, 0)));
  body->setAngularDamping(10);

  cout << "Starting simulation" << endl;

  for(int i = 0; i < 200; i++) {
    cout << "Step " << i << endl;
    cout << "Stepping 1/100 of a second" << endl;
    world->update(1/100.0);
    cout << "----------------------------------------------" << endl;
    rp3d::RigidBody* body;
    for (size_t i = 0; i < bodies.size(); i++) {
      body = bodies.at(i);
      rp3d::Transform trans = body->getTransform();
      rp3d::Vector3 pos = trans.getPosition();
      rp3d::Quaternion q = trans.getOrientation();
      rp3d::Vector3 lin_vel = body->getLinearVelocity();
      rp3d::Vector3 ang_vel = body->getAngularVelocity();
      cout << "Object " << i << " pos = (" << pos.x << ", " << pos.y << ", " << pos.z
        << "), orientation = (" << q.x << ", " << q.y << ", " << q.z << ", " << q.w
        << "), linear vel = (" << lin_vel.x << ", " << lin_vel.y << ", " << lin_vel.z
        << "), angular vel = (" << ang_vel.x << ", " << ang_vel.y << ", " << ang_vel.z << ")" << endl;
    }
    cout << "There are " << bodies.size() << " objects in the world" << endl;
    cout << "----------------------------------------------" << endl;
  }
}
