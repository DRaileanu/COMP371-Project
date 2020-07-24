//------------------------------------------------------
// Polyhedron subdividing icosahedron (20 tris) by N-times iteration
// The icosphere with N=1 (default) has 80 triangles by subdividing a triangle
// of icosahedron into 4 triangles. If N=0, it is identical to icosahedron.
// AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// Source: http://www.songho.ca/opengl/gl_sphere.html
// CREATED: 2018-07-23
// MODIFIED: 2020-07-22 by Dan Raileanu
//-------------------------------------------------------


#pragma once
#include "Drawable.h"
#include <glm/gtc/type_ptr.hpp>
#include <map>

class Sphere : public Drawable {
public:
	Sphere(float radius, int subdivisions);
	~Sphere();

private:
	float radius;
	int subdivision;

private:

	//methods to build IcoSphere from Icosahedron
	std::vector<float> computeIcosahedronVertices();
	void addVertex(float x, float y, float z);
	void addVertices(const float v1[3], const float v2[3], const float v3[3]);
	void addIndices(unsigned int, unsigned int, unsigned int);
	void addNormal(float nx, float ny, float nz);
	void addNormals(const float n1[3], const float n2[3], const float n3[3]);
	void buildVerticesFlat();
	void buildVerticesSmooth();
	void subdivideVerticesFlat();
	void subdivideVerticesSmooth();
	void computeHalfVertex(const float v1[3], const float v2[3], float length, float newV[3]);
	void computeHalfTexCoord(const float t1[2], const float t2[2], float newT[2]);
	float computeScaleForLength(const float v[3], float length);
	void computeVertexNormal(const float v[3], float normal[3]);
	void computeFaceNormal(const float v1[3], const float v2[3], const float v3[3], float n[3]);

	void addTexCoord(float s, float t);
	void addTexCoords(const float t1[2], const float t2[2], const float t3[2]);
	unsigned int addSubVertexAttribs(const float v[3], const float n[3], const float t[2]);
	bool isSharedTexCoord(const float t[2]);
	bool isOnLineSegment(const float a[2], const float b[2], const float c[2]);

	//note that the Icosahedron will have vertices defined as tightly packed floats instead of glm::vec3 as the Sphere, so have to reinterpret in Sphere constructor
	std::vector<float> icosahedronVertices;
	std::vector<float> icosahedronNormals;
	std::vector<float> icosahedronTexCoords;


	std::map<std::pair<float, float>, unsigned int> sharedIndices;
};


