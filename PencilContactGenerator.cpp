#include "PencilContactGenerator.h"
#include "YAMPE\Particle\Constraints.h"


using namespace YAMPE;
using namespace P;

void PencilContactGenerator::generate(YAMPE::P::ContactRegistry::Ref contactRegistry) {
	for (auto constraint : constraints) {
		constraint->generate(contactRegistry);
	}
}

const YAMPE::String PencilContactGenerator::toString() const {
	std::ostringstream outs;
	return outs.str();
}

void PencilContactGenerator::draw() {
	for (auto p : particles) p->draw();
	ofSetColor(ofColor::white);
	mesh.draw();
	drawMeshEdges();
}

void PencilContactGenerator::drawMeshEdges() {
	ofSetColor(ofColor::black);
	for (int k = 1; k < sides + 1; ++k) {
		//surround particle lines
		int particleToParticleIndex = ((k + 1) % (sides + 1));
		particleToParticleIndex = (particleToParticleIndex == 0) ? 1 : particleToParticleIndex;
		ofSetColor(ofColor::red);
		ofDrawLine(particles[k]->position, particles[particleToParticleIndex]->position);
		ofDrawLine(particles[k + (sides + 1)]->position, particles[particleToParticleIndex + (sides + 1)]->position);

		ofSetColor(ofColor::darkCyan);
		ofDrawLine(particles[0]->position, particles[k % (sides + 1)]->position);
		ofDrawLine(particles[sides + 1]->position, particles[k + (sides + 1)]->position);

		ofSetColor(ofColor::purple);
		//edge lines
		ofDrawLine(particles[k]->position, particles[k + (sides + 1)]->position);
	}
}

void PencilContactGenerator::construct(int sides, float radius, float length) {
	for (int k = 0; k < sides; ++k) {
		//create particle and set attributes
		Particle::Ref particle = Particle::Ref(new Particle());
		//pick color for debugging
		ofColor color = (k == 1) ? ofColor::green :
			(k == 2) ? ofColor::blue :
			(k == 3) ? ofColor::red : ofColor::black;
			
		//create particle and set attributes
		particle->setRadius(0.1).setWireColor(color);
		particles.push_back(particle);
	}
}

void PencilContactGenerator::resetPosition() {
	
}

void PencilContactGenerator::setPosition(const ofPoint & offset, float angleZ) {
	float theta = M_TWO_PI / sides;
	particles[0]->setPosition(ofVec3f(offset.x, offset.y, length / 2));
	particles[particles.size() / 2]->setPosition(ofVec3f(offset.x, offset.y, -length / 2));
	
	for (int k = 1; k < sides + 1; ++k) {
		//get angle
		float angle{ theta * (k + 0.5f) - ofDegToRad(angleZ)};
		//finds position of particle using angle and z axis
		particles[k]->setPosition(ofVec3f(offset.x + radius * cosf(angle), offset.y + radius * sinf(angle), length / 2));
		particles[k + (sides + 1)]->setPosition(offset + ofVec3f(radius * cosf(angle), radius * sinf(angle), -length / 2));
		createMeshTriangles(k);
	}
	createConstraints();
	createMesh();
}

void PencilContactGenerator::createConstraints() {
	for (ParticleRegistry::iterator a = particles.begin(); a != particles.end(); ++a) {
		for (ParticleRegistry::iterator b = particles.begin(); b != a; ++b) {
			ofVec3f normal = (*a)->position - (*b)->position;
			float distance = normal.length();
			EqualityConstraint::Ref constraint = EqualityConstraint::Ref(new EqualityConstraint(*a, *b, distance));
			constraints.push_back(constraint);
		}
	}
	/*float distance = particles[1]->position.distance(particles[2]->position);
	for (int k = 1; k < sides + 1; ++k) {

		//surrounding particles to center constraints
		EqualityConstraint::Ref frontSurroundingConstraint = EqualityConstraint::Ref(new EqualityConstraint(particles[0], particles[k % (sides + 1)], radius));
		EqualityConstraint::Ref backSurroundingConstraint = EqualityConstraint::Ref(new EqualityConstraint(particles[sides + 1], particles[(k + (sides + 1)) % (sides + 1) + sides], radius));

		constraints.push_back(frontSurroundingConstraint);
		constraints.push_back(backSurroundingConstraint);

		//surrounding particle to particle constraints
		int particleToParticleIndex = ((k + 1) % (sides + 1));
		particleToParticleIndex = (particleToParticleIndex == 0) ? 1 : particleToParticleIndex;
		EqualityConstraint::Ref frontParticleToParticleConstraint = EqualityConstraint::Ref(new EqualityConstraint(particles[k], particles[particleToParticleIndex], distance));
		EqualityConstraint::Ref backParticleToParticleConstraint = EqualityConstraint::Ref(new EqualityConstraint(particles[k + (sides + 1)], particles[particleToParticleIndex + (sides + 1)], distance));

		constraints.push_back(frontParticleToParticleConstraint);
		constraints.push_back(backParticleToParticleConstraint);

		//add edge to edge constraints
		EqualityConstraint::Ref edgeConstraint = EqualityConstraint::Ref(new EqualityConstraint(particles[k], particles[k + (sides + 1)], length));
		constraints.push_back(edgeConstraint);

		//center to center constraint
		EqualityConstraint::Ref centerToCenterConstraint = EqualityConstraint::Ref(new EqualityConstraint(particles[0], particles[sides + 1], length));
		constraints.push_back(centerToCenterConstraint);
	}*/
}

void PencilContactGenerator::createMeshTriangles(int index) {
	if (index > 1) {
		mesh.addTriangle(index, 0, index - 1);
		mesh.addTriangle(sides + 1 + index, sides + 1, sides + 1 + index - 1);

		mesh.addTriangle(index - 1, index, sides + 1 + index);
		mesh.addTriangle(sides + index, index - 1, sides + 1 + index);
	}
	else {
		mesh.addTriangle(index, 0, sides);
		mesh.addTriangle(sides * 2 + 1, sides + 1, sides + 1 + index);

		mesh.addTriangle(sides, index, sides * 2 + 1);
		mesh.addTriangle(sides + 2, index, sides * 2 + 1);
	}
}

void PencilContactGenerator::createMesh() {
	for (auto p : particles) mesh.addVertex(p->position);
}

void PencilContactGenerator::updateMesh() {
	for (int k = 0; k < particles.size(); ++k) {
		mesh.setVertex(k, particles[k]->position);
	}
}