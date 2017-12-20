#include "PencilContactGenerator.h"
#include "YAMPE\Particle\Constraints.h"
#include <math.h>
#include <cmath>


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
		ofColor color = (k == 1) ? ofColor::red :
			(k == 2) ? ofColor::green :
			(k == 3) ? ofColor::blue : ofColor::black;
			
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
	
	for (int k = 0; k < sides; ++k) {
		//get angle
		float angle = theta * (k - 0.5f) - M_PI_2;

		//finds position of particle using angle and z axis
		particles[k + 1]->setPosition(offset + ofVec3f(radius * cosf(angle), radius * sinf(angle), length / 2));
		particles[k + 1 + (sides + 1)]->setPosition(offset + ofVec3f(radius * cosf(angle), radius * sinf(angle), -length / 2));
		createMeshTriangles(k + 1);
	}

	ofMatrix4x4 m;
	m.makeRotationMatrix(angleZ, ofVec3f(0, 0, 1), 0, ofVec3f(1, 0, 0), 0, ofVec3f(0, 1, 0));
	for (auto p : particles) p->position = m.preMult(p->position);
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

void PencilContactGenerator::setTippingAngle(float planeAngle) {
	this->tippingAngle = 360 / (2 * sides);
}