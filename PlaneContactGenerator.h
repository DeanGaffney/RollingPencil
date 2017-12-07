#pragma once
#ifndef PLANE_CONTACT_GENERATOR_H
#define PLANE_CONTACT_GENERATOR_H

#include "YAMPE/Particle.h"
#include "YAMPE/Particle/ContactGenerators.h"
#include "YAMPE/Particle/ForceGenerators.h"

class PlaneContactGenerator : public YAMPE::P::ContactGenerator, public YAMPE::P::ForceGenerator {
public:
	typedef ofPtr<PlaneContactGenerator> Ref;

	ofVec3f a;  ///< arbitrary point on the plane
	ofVec3f n;  ///< unit normal on 'front' face
	bool isSticky;
	float width, height;
	ofColor color;

	YAMPE::ParticleRegistry particles;

	PlaneContactGenerator(const ofVec3f a = ofVec3f(0, 0, 0), const ofVec3f n = ofVec3f(1, 1, 0), bool isSticky = true, float width = 15, float height = 20, const YAMPE::String label = "PlaneContactGenerator")
		: YAMPE::P::ContactGenerator(label), a(a), n(n), isSticky(isSticky), width(width), height(height), color(ofColor::seaGreen) {
	};

	void generate(YAMPE::P::ContactRegistry::Ref contactRegstry);
	void applyForce(YAMPE::Particle::Ref particle, float dt);

	const YAMPE::String toString() const;

	void draw();
	void setPosition(const ofVec3f a) { this->a = a; }
	void setNormal(const ofVec3f n) { this->n = n; }

};

/*
class PlaneForceGenerator : public YAMPE::P::ForceGenerator {
public:
PlaneContactGenerator::Ref plane;

void applyForce(YAMPE::Particle::Ref particle, float dt);

};


class PlaneFrictionForceGenerator : public YAMPE::P::ForceGenerator {

private:

PlaneContactGenerator::Ref plane;

public:

PlaneFrictionForceGenerator(PlaneContactGenerator::Ref plane,
const YAMPE::String label="PlaneFrictionForceGenerator");

virtual void applyForce(YAMPE::Particle::Ref particle, float dt);

const YAMPE::String toString() const;
};
*/

#endif
