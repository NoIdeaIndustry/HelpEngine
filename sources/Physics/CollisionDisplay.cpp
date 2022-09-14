#include "Physics/CollisionDisplay.hpp"
#include "Resources/Model.hpp"

using namespace CollisionDisplay;
using namespace Core::myMath;
using namespace Resources;

void CollisionMesh::InitSphereMesh() {
    Model model;
    int triSize = 0;
    model.UVs.push_back(Vec2());
    model.normals.push_back(Vec3());
    model.positions.push_back(Vec3());
    for (int j = 0; j < 12; ++j) {
        float theta0 = ((j + 0) / 12.f) * mPI;
        float theta1 = ((j + 1) / 12.f) * mPI;

        for (int i = 0; i < 12; ++i) {
            float phi0 = ((i + 0) / 12.f) * 2.f * mPI;
            float phi1 = ((i + 1) / 12.f) * 2.f * mPI;

            Vec3 c0 = GetSphericalCoords(1, theta0, phi0);
            Vec3 c1 = GetSphericalCoords(1, theta0, phi1);
            Vec3 c2 = GetSphericalCoords(1, theta1, phi1);
            Vec3 c3 = GetSphericalCoords(1, theta1, phi0);

            model.positions.push_back(c0);
            model.positions.push_back(c1);
            model.positions.push_back(c2);
            model.positions.push_back(c3);
            model.triangles.push_back(triSize + 2);
            model.triangles.push_back(0);
            model.triangles.push_back(0);
            model.triangles.push_back(triSize + 0);
            model.triangles.push_back(0);
            model.triangles.push_back(0);
            model.triangles.push_back(triSize + 1);
            model.triangles.push_back(0);
            model.triangles.push_back(0);
            model.triangles.push_back(triSize + 2);
            model.triangles.push_back(0);
            model.triangles.push_back(0);
            model.triangles.push_back(triSize + 3);
            model.triangles.push_back(0);
            model.triangles.push_back(0);
            model.triangles.push_back(triSize + 0);
            model.triangles.push_back(0);
            model.triangles.push_back(0);
            triSize += 4;
        }
    }
    model.Bind();
    Sphere = model;

}

void CollisionMesh::InitCubeMesh() {
    Model model;
    model.positions.push_back(Vec3());
    model.positions.push_back(Vec3(1, -1, -1));
    model.positions.push_back(Vec3(1, -1, 1));
    model.positions.push_back(Vec3(-1, -1, 1));
    model.positions.push_back(Vec3(-1, -1, -1));

    model.positions.push_back(Vec3(1, 1,- 1));
    model.positions.push_back(Vec3(1, 1, 1));
    model.positions.push_back(Vec3(-1, 1, 1));
    model.positions.push_back(Vec3(-1, 1, -1));

    model.UVs.push_back(Vec2());
    model.normals.push_back(Vec3());

    model.triangles.push_back(2); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(3); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(4); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(8); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(7); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(6); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(5); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(6); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(2); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(6); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(7); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(3); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(3); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(7); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(8); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(1); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(4); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(8); model.triangles.push_back(0); model.triangles.push_back(0);


    model.triangles.push_back(1); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(2); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(4); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(5); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(8); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(6); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(1); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(5); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(2); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(2); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(6); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(3); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(4); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(3); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(8); model.triangles.push_back(0); model.triangles.push_back(0);

    model.triangles.push_back(5); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(1); model.triangles.push_back(0); model.triangles.push_back(0);
    model.triangles.push_back(8); model.triangles.push_back(0); model.triangles.push_back(0);




    model.Bind();
    Cube = model;
}