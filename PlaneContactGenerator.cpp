#include "PlaneContactGenerator.h"

void PlaneContactGenerator::generate(YAMPE::P::ContactRegistry::Ref contactRegstry) {

}

void PlaneContactGenerator::applyForce(YAMPE::Particle::Ref particle, float dt) {

}

const YAMPE::String PlaneContactGenerator::toString() const {
	std::ostringstream outs;
	return outs.str();
}

void PlaneContactGenerator::draw() {
	ofSetColor(color);
	ofDrawPlane(width, height);
}