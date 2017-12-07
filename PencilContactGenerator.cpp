#include "PencilContactGenerator.h"


using namespace YAMPE;

void PencilContactGenerator::generate(YAMPE::P::ContactRegistry::Ref contactRegstry) {

}

const YAMPE::String PencilContactGenerator::toString() const {
	std::ostringstream outs;
	return outs.str();
}

void PencilContactGenerator::draw() {
	
}

void PencilContactGenerator::construct(int sides = 6, float radius = 1, float length = 10) {
	float theta = M_TWO_PI / sides;

	for (int k = 0; k < sides; k++) {
		float angle{ theta * (k - 0.5) };

		//THE 0 NEEDS TO BE CENTER POINT POSITION, NEED TO KNOW HOW TO GET THAT
		ofVec3f position = 0 + ofVec3f(radius * cosf(angle), radius * sinf(angle), 0);

		Particle::Ref particle = Particle::Ref(new Particle());
		particle->setPosition(position).setRadius(0.5);
		particles.push_back(particle);
	}
}

void PencilContactGenerator::resetPosition() {

}

void PencilContactGenerator::setPosition(const ofPoint & offset, float angleZ) {

}