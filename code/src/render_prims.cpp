#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

// Boolean variables allow to show/hide the primitives
bool renderSphere = false;
bool renderCapsule = false;
bool renderParticles = false;
bool renderCloth = false;
bool renderCube = false;

//Variables param esfera
extern float SpherePos[3];
extern float SphereRadius;

//Variables param capsule
extern float CapsulePosA[3];
extern float CapsulePosB[3];
extern float CapsuleRadius;

//Variables param particles

namespace Sphere {
	extern void setupSphere(glm::vec3 pos = glm::vec3(SpherePos[0], SpherePos[1], SpherePos[2]), float radius = SphereRadius);
	extern void cleanupSphere();
	extern void updateSphere(glm::vec3 pos, float radius = SphereRadius);
	extern void drawSphere();
}
namespace Capsule {
	extern void setupCapsule(glm::vec3 posA = glm::vec3(CapsulePosA[0], CapsulePosA[1], CapsulePosA[2]), glm::vec3 posB = glm::vec3(CapsulePosB[0], CapsulePosB[1], CapsulePosB[2]), float radius = CapsuleRadius);
	extern void cleanupCapsule();
	extern void updateCapsule(glm::vec3 posA, glm::vec3 posB, float radius = CapsuleRadius);
	extern void drawCapsule();
}
namespace LilSpheres {
	extern const int maxParticles;
	extern void setupParticles(int numTotalParticles, float radius = 0.05f);
	extern void cleanupParticles();
	extern void updateParticles(int startIdx, int count, float* array_data);
	extern void drawParticles(int startIdx, int count);
}
namespace ClothMesh {
	extern void setupClothMesh();
	extern void cleanupClothMesh();
	extern void updateClothMesh(float* array_data);
	extern void drawClothMesh();
}

namespace Cube {
	extern void setupCube();
	extern void cleanupCube();
	extern void updateCube(const glm::mat4& transform);
	extern void drawCube();
}

void setupPrims() {
	Sphere::setupSphere();
	Capsule::setupCapsule();
	LilSpheres::setupParticles(LilSpheres::maxParticles);
	ClothMesh::setupClothMesh();
	Cube::setupCube();
}
void cleanupPrims() {
	Sphere::cleanupSphere();
	Capsule::cleanupCapsule();
	LilSpheres::cleanupParticles();
	ClothMesh::cleanupClothMesh();
	Cube::cleanupCube();
}

void renderPrims() {
	if (renderSphere)
		Sphere::drawSphere();
	if (renderCapsule)
		Capsule::drawCapsule();

	if (renderParticles) {
		// You may need to rethink this piece of code...
		int startDrawingFromParticle = 0;
		int numParticlesToDraw = LilSpheres::maxParticles;
		LilSpheres::drawParticles(startDrawingFromParticle, numParticlesToDraw);
		// .............................................
	}
	
	if (renderCloth)
		ClothMesh::drawClothMesh();

	if (renderCube)
		Cube::drawCube();
}
