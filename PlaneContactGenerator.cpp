#include "PlaneContactGenerator.h"

using namespace YAMPE;
using namespace P;

void PlaneContactGenerator::generate(YAMPE::P::ContactRegistry::Ref contactRegistry) {
	for (auto && p : particles) {
		float particleAngle = 90.0f + ofRadToDeg(atan2f(1, 0) - atan2f(p->position.y, p->position.x));

		cout << "Particle Angle: " << particleAngle << endl;
		//cout << "Plane angle: " << angle << endl;
		//cout << "Particle Position: " << p->position << endl;
		float y = p->position.y - p->radius;
		if (particleAngle <= angle) {
			Contact::Ref contact(new Contact("GroundContactGenerator"));
			contact->contactNormal = ofVec3f(0, 1, 0);
			contact->a = p;
			contact->b = Particle::Ref();
			contact->penetration = -y;
			contact->restitution = 1.0f;
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
}