#include "Physics/Collision.hpp"
#include "Utils/Debug.hpp"
#include <iostream>
#include "Utils/Time.hpp"

using namespace Physics;
using namespace Core::myMath;
using namespace std;

Vec3 Support(const Collider& c1, const Collider& c2, Vec3 direction) {
	return c1.FindFurthestPoint(direction ) - c2.FindFurthestPoint(-direction);
}

bool ManageLine(vector<Vec3>& simplex, Vec3& direction) {
	Vec3 a, b; 
	a = simplex[0]; 
	b = simplex[1];

	Vec3 ab, ao; 
	ab = b - a; 
	ao = -a;

	if (ab * ao > 0) {
		direction = (ab ^ ao) ^ ab;
	} else {
		simplex = { a };
		direction = ao;
	}

	return false;
}

bool ManageTriangle(vector<Vec3>& simplex, Vec3& direction) {
	Vec3 a, b, c;
	a = simplex[0];
	b = simplex[1];
	c = simplex[2];

	Vec3 ab, ac, ao;
	ab = b - a;
	ac = c - a;
	ao = -a;

	Vec3 abc = ab ^ ac;

	if ((abc ^ ac) * ao > 0) {
		if (ac * ao > 0) {
			simplex.erase(simplex.begin() + 1);
			direction = (ac ^ ao) ^ ac;
		} else {
			return ManageLine(simplex = {a, b}, direction);
		}
	} else {
		if ((ab ^ abc) * ao > 0) {
			return ManageLine(simplex = { a, b }, direction);
		} else {
			if (abc * ao > 0) {
				direction = abc;
			} else {
				simplex = { a, c, b };
				direction = -abc;
			}
		}
	}

	return false;
}

bool ManageTetraHedra(vector<Vec3>& simplex, Vec3& direction) {
	Vec3 a = simplex[0];
	Vec3 b = simplex[1];
	Vec3 c = simplex[2];
	Vec3 d = simplex[3];

	Vec3 ab = b - a;
	Vec3 ac = c - a;
	Vec3 ad = d - a;
	Vec3 ao = -a;

	Vec3 abc = ab ^ ac;
	Vec3 acd = ac ^ ad;
	Vec3 adb = ad ^ ab;

	if (abc * ao > 0) {
		return ManageTriangle(simplex = { a, b, c }, direction);
	}

	if (acd * ao > 0) {
		return ManageTriangle(simplex = { a, c, d }, direction);
	}

	if (adb * ao > 0) {
		return ManageTriangle(simplex = { a, d, b }, direction);
	}

	return true;
}

bool ManageSimplex(vector<Vec3>& simplex, Vec3& direction) {
	switch (simplex.size()) {
		case 2: return ManageLine(simplex, direction); 
		case 3: return ManageTriangle(simplex, direction); 
		case 4: return ManageTetraHedra(simplex, direction); 
		default: DEBUG_LOGERROR("Simplex Invalid"); return false;
	}
}

CollisionHit Collision::CheckCollision(const Collider& c1, const Collider& c2) {
	if (typeid(c1) == typeid(SphereCollider) && typeid(c2) == typeid(SphereCollider)) {
		//Sphere collision
		SphereCollider& s1 = (SphereCollider&)c1;
		SphereCollider& s2 = (SphereCollider&)c2;
		CollisionHit hit;
		hit.isColliding = Distance(s1.gameObject->transform.GetGlobalPosition(), s2.gameObject->transform.GetGlobalPosition()) <= s1.radius + s2.radius;

		if (hit.isColliding) {
			hit.resolutionNormal = s2.gameObject->transform.GetGlobalPosition() - s1.gameObject->transform.GetGlobalPosition();
			hit.resolutionDistance = (s1.radius + s2.radius) - Distance(s1.gameObject->transform.GetGlobalPosition(), s2.gameObject->transform.GetGlobalPosition());
		}
		return hit;
	}

	bool res = false;
	
	Vec3 direction = c1.gameObject->transform.GetGlobalPosition() - c2.gameObject->transform.GetGlobalPosition(); // Maybe normalize it;

	vector<Vec3> simplex = { Support(c1, c2, direction) };

	direction = -simplex[0];

	int n = 0;

	while (n < 50) {
		n++;
		Vec3 a = Support(c1, c2, direction);

		if (a * direction < 0) {
			res = false;
			break;
		}

		simplex.insert(simplex.begin(), a);

		if (ManageSimplex(simplex, direction)) {
			res = true;
			break;
		}
		
	}

	if (res) {
		return ResolveCollision(c1, c2, simplex);
	}
	else {
		CollisionHit hit;
		hit.isColliding = false;
		hit.resolutionDistance = 0;
		hit.resolutionNormal = Vec3();
		return hit;
	}
}

pair<vector<Vec4>, size_t> GetFaceNormals(const vector<Vec3>& polytope, const vector<size_t>& faces) {
	std::vector<Vec4> normals;
	size_t minTriangle = 0;
	float  minDistance = FLT_MAX;

	for (size_t i = 0; i < faces.size(); i += 3) {
		Vec3 a = polytope[faces[i]];
		Vec3 b = polytope[faces[i + 1]];
		Vec3 c = polytope[faces[i + 2]];

		Vec3 normal = ((b - a) ^ (c - a)).Normalized();
		float distance = normal * a;

		if (distance < 0) {
			normal *= -1;
			distance *= -1;
		}

		normals.emplace_back(normal, distance);

		if (distance < minDistance) {
			minTriangle = i / 3;
			minDistance = distance;
		}
	}

	return { normals, minTriangle };
}

void AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, const std::vector<size_t>& faces, size_t a, size_t b) {
	auto reverse = std::find(
		edges.begin(),
		edges.end(),
		std::make_pair(faces[b], faces[a])
	);

	if (reverse != edges.end()) {
		edges.erase(reverse);
	}

	else {
		edges.emplace_back(faces[a], faces[b]);
	}
}

CollisionHit Collision::ResolveCollision(const Collider& c1, const Collider& c2, const vector<Vec3> simplex) /* Finish and understand*/ {
	vector<Vec3> polytope(simplex.begin(), simplex.end());
	vector<size_t>  faces = {
		0, 1, 2,
		0, 3, 1,
		0, 2, 3,
		1, 3, 2
	};

	auto [normals, minFace] = GetFaceNormals(polytope, faces);
	if (normals.size() <= 0) {
		CollisionHit hit;

		hit.resolutionNormal = Vec3();
		hit.resolutionDistance = 0;
		hit.isColliding = true;

		return hit;
	}

	Vec3 minNormal;
	float   minDistance = FLT_MAX;

	int n = 0;
	while (minDistance == FLT_MAX) {
		minNormal = normals[minFace].toVec3();
		minDistance = normals[minFace].w;

		Vec3 support = Support(c1, c2, minNormal);
		float sDistance = minNormal * support;
		float test = abs(sDistance - minDistance);

		n++;
		if (n > 50) {
			CollisionHit hit;

			hit.resolutionNormal = minNormal;
			hit.resolutionDistance = minDistance;
			hit.isColliding = true;

			return hit;
		}


		if (abs(sDistance - minDistance) > 0.001f) {
			minDistance = FLT_MAX;

			std::vector<std::pair<size_t, size_t>> uniqueEdges;

			for (size_t i = 0; i < normals.size(); i++) {
				if (normals[i].toVec3() * support > 0) {
					size_t f = i * 3;

					AddIfUniqueEdge(uniqueEdges, faces, f, f + 1);
					AddIfUniqueEdge(uniqueEdges, faces, f + 1, f + 2);
					AddIfUniqueEdge(uniqueEdges, faces, f + 2, f);

					faces[f + 2] = faces.back(); faces.pop_back();
					faces[f + 1] = faces.back(); faces.pop_back();
					faces[f] = faces.back(); faces.pop_back();

					normals[i] = normals.back(); normals.pop_back();

					i--;
				}
			}

			std::vector<size_t> newFaces;
			for (auto [edgeIndex1, edgeIndex2] : uniqueEdges) {
				newFaces.push_back(edgeIndex1);
				newFaces.push_back(edgeIndex2);
				newFaces.push_back(polytope.size());
			}

			polytope.push_back(support);

			auto [newNormals, newMinFace] = GetFaceNormals(polytope, newFaces);
			if (normals.size() <= 0) {
				CollisionHit hit;

				hit.resolutionNormal = Vec3();
				hit.resolutionDistance = 0;
				hit.isColliding = true;

				return hit;
			}

			float oldMinDistance = FLT_MAX;
			for (size_t i = 0; i < normals.size(); i++) {
				if (normals[i].w < oldMinDistance) {
					oldMinDistance = normals[i].w;
					minFace = i;
				}
			}

			if (newMinFace < newNormals.size() &&  newNormals[newMinFace].w < oldMinDistance) {
				minFace = newMinFace + normals.size();
			}

			faces.insert(faces.end(), newFaces.begin(), newFaces.end());
			normals.insert(normals.end(), newNormals.begin(), newNormals.end());
		}
		
	}

	CollisionHit hit;

	hit.resolutionNormal = minNormal;
	hit.resolutionDistance = minDistance + 0.001f;
	hit.isColliding = true;

	return hit;
}

void Collision::UpdateCollision() {
	for (RigidBody* rb : rigidBodies) {
		rb->isGrounded = false;
	}


	for (unsigned int i = 0; i < colliders.size(); i++) {
		colliders[i]->Render();
		for (unsigned int j = i + 1; j < colliders.size(); j++) {
			if (!colliders[i]->rigidBody && !colliders[j]->rigidBody) {
				continue;
			}

			Vec3 offsetI = colliders[i]->rigidBody ? (colliders[i]->rigidBody->velocity) * Time::deltaTime : Vec3();
			Vec3 offsetJ = colliders[j]->rigidBody ? (colliders[j]->rigidBody->velocity) * Time::deltaTime : Vec3();

			colliders[i]->gameObject->transform.position += offsetI;
			colliders[j]->gameObject->transform.position += offsetJ;

			CollisionHit hit = CheckCollision(*colliders[i], *colliders[j]);
			if (hit.isColliding) {
				if (colliders[i]->rigidBody) {
					if (colliders[j]->rigidBody) {
						colliders[i]->rigidBody->velocity -= (hit.resolutionNormal * hit.resolutionDistance * 0.5f) / Time::deltaTime;
						colliders[j]->rigidBody->velocity += (hit.resolutionNormal * hit.resolutionDistance * 0.5f) / Time::deltaTime;

						if (hit.resolutionNormal.y > 0.05f)
							colliders[j]->rigidBody->isGrounded = true;
					} else {
						colliders[i]->rigidBody->velocity -= (hit.resolutionNormal * hit.resolutionDistance) / Time::deltaTime;
					}

					if (hit.resolutionNormal.y < -0.05f)
						colliders[i]->rigidBody->isGrounded = true;
				} else {
					colliders[j]->rigidBody->velocity += (hit.resolutionNormal * hit.resolutionDistance) / Time::deltaTime;
					if (hit.resolutionNormal.y > 0.05f)
						colliders[j]->rigidBody->isGrounded = true;
				}
			}
			colliders[i]->gameObject->transform.position -= offsetI;
			colliders[j]->gameObject->transform.position -= offsetJ;
		}
	}

	for (RigidBody* rb : rigidBodies) {
		rb->gameObject->transform.position += rb->velocity * Time::deltaTime;
	}
}
