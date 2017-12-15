#pragma once

#ifndef PENCIL_CONTACT_GENERATOR_H
#define PENCIL_CONTACT_GENERATOR_H

#include "YAMPE/Particle.h"
#include "YAMPE/Particle/ContactGenerators.h"
#include "YAMPE/Particle/Constraints.h"

class PencilContactGenerator : public YAMPE::P::ContactGenerator {
public:
	int     sides;             ///< number of sides (>=3)
	float   radius;
	float   length;
	ofMesh	mesh;
	vector<YAMPE::P::Constraint::Ref> constraints;

	typedef ofPtr<PencilContactGenerator> Ref;

	YAMPE::ParticleRegistry particles;

	PencilContactGenerator(int sides = 6, float radius = 1.0, float length = 10.0,
		const YAMPE::String label = "PencilContactGenerator")
		: YAMPE::P::ContactGenerator(label), sides(sides), radius(radius), length(length) {};

	void generate(YAMPE::P::ContactRegistry::Ref contactRegstry);

	const YAMPE::String toString() const;

	void draw();

	void construct(int sides = 6, float radius = 1, float length = 10);

	void resetPosition();
	void setPosition(const ofPoint & offset, float angleZ);
	void drawMeshEdges();
	void createMeshTriangles(int index);
	void createMesh();
	void createConstraints();
	void updateMesh();
};

#endif
