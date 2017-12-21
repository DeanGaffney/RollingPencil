#include "PlaneContactGenerator.h"

using namespace YAMPE;
using namespace P;

void PlaneContactGenerator::generate(YAMPE::P::ContactRegistry::Ref contactRegistry) {
	for (auto && p : particles) {
		ofVec3f planeTestVec = ofVec3f(p->position - a);
		float dot = planeTestVec.dot(n) - p->radius;
		if (dot < 0.0f) {
			Contact::Ref contact(new Contact("GroundContactGenerator"));
			contact->contactNormal = n;
			contact->a = p;
			contact->b = Particle::Ref();
			contact->penetration = -dot;
			contact->restitution = 1.0f;
			contactRegistry->append(contact);
		}
	}
}

void PlaneContactGenerator::applyForce(YAMPE::Particle::Ref particle, float dt) {
	ofVec3f planeTestVec = ofVec3f(particle->position - a);
	float dot = planeTestVec.dot(n) - particle->radius;
	if (isSticky && dot <= 0.0f) {
		particle->velocity = ofVec3f::zero();
	}
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