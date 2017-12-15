#include "PencilContactGenerator.h"
#include "YAMPE\Particle\Constraints.h"


using namespace YAMPE;
using namespace P;

void PencilContactGenerator::generate(YAMPE::P::ContactRegistry::Ref contactRegstry) {

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
		ofDrawLine(particles[k]->position, particles[k + 1]->position);		//particle to particles side 1
		ofDrawLine(particles[k]->position, particles[sides]->position);		

		ofDrawLine(particles[k]->position, particles[k + (sides + 1)]->position);	//particle to opposite particle
		ofDrawLine(particles[k + sides]->position, particles[k + (sides + 1)]->position);	// particle to particle side 2
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
	//loop over particles and set the position
}

void PencilContactGenerator::setPosition(const ofPoint & offset, float angleZ) {
	float theta = M_TWO_PI / sides;
	particles[0]->setPosition(ofVec3f(offset.x, offset.y, length / 2));
	particles[particles.size() / 2]->setPosition(ofVec3f(offset.x, offset.y, -length / 2));
	for (int k = 1; k < sides + 1; ++k) {
		//get angle
		float angle{ theta * (k - 0.5f) };
		//finds position of particle using angle and z axis
		particles[k]->setPosition(ofVec3f(offset.x + radius * cosf(angle), offset.y + radius * sinf(angle), length / 2));
		particles[k + (sides + 1)]->setPosition(offset + ofVec3f(radius * cosf(angle), radius * sinf(angle), -length / 2));
		//EqualityConstraint::Ref constraint = EqualityConstraint::Ref(new EqualityConstraint(particles[k - 1], particles[k]));
		//constraints.push_back(constraint);
		createMeshTriangles(k);
	}
	createMesh();
	createConstraints();
}

void PencilContactGenerator::createConstraints() {

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