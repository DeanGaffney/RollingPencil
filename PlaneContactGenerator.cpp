#include "PlaneContactGenerator.h"

using namespace YAMPE;
using namespace P;

void PlaneContactGenerator::generate(YAMPE::P::ContactRegistry::Ref contactRegistry) {
	for (auto && p : particles) {
		float particleAngle = 90.0f + ofRadToDeg(atan2f(1, 0) - atan2f(p->position.y, p->position.x));

		float y = p->position.y - p->radius;
		if (particleAngle <= angle) {
			Contact::Ref contact(new Contact("GroundContactGenerator"));
			contact->contactNormal = n;
			contact->a = p;
			contact->b = Particle::Ref();
			contact->penetration = -n.length();
			contact->restitution = (isSticky) ? 0.4334f : 1.0f;
			contactRegistry->append(contact);
		}
	}
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
	ofSetColor(ofColor::blue);
}