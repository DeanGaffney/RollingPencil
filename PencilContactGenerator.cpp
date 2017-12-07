#include "PencilContactGenerator.h"


using namespace YAMPE;

void PencilContactGenerator::generate(YAMPE::P::ContactRegistry::Ref contactRegstry) {

}

const YAMPE::String PencilContactGenerator::toString() const {
	std::ostringstream outs;
	return outs.str();
}

void PencilContactGenerator::draw() {
	for (auto p : particles) p->draw();
}

void PencilContactGenerator::construct(int sides, float radius, float length) {
	float theta = M_TWO_PI / sides;

	for (int k = 0; k < sides; ++k) {
		float angle{ theta * (k - 0.5f) };		//get angle

		//pick color for debugging
		ofColor color = (k == 0) ? ofColor::green : 
						(k == 1) ? ofColor::blue : 
						(k == 2) ? ofColor::red : ofColor::black;

		ofVec3f centerPos = ofVec3f::zero();

		//find if z is positive or negative
		float z{(k >= (sides / 2) - 1) ? -length : length};

		//fins position of particle using angle and z axis
		ofVec3f position = centerPos + ofVec3f(radius * cosf(angle), radius * sinf(angle), z / 2);

		//create particle and set attributes
		Particle::Ref particle = Particle::Ref(new Particle());
		particle->setPosition(position).setRadius(0.1)
									   .setWireColor(color);
		particles.push_back(particle);
	}
}

void PencilContactGenerator::resetPosition() {

}

void PencilContactGenerator::setPosition(const ofPoint & offset, float angleZ) {

}