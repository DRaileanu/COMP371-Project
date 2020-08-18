#pragma once

#include "Drawable.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "Camera.h"
#include <vector>
#include <string>


/**
 * ParticleEffect class that demonstrates one possible implementation for
 * billboard particles.
 */

class ParticleEffect : public Drawable {
    static const unsigned int MAX_PARTICLES = 1000;
public:
    ParticleEffect(unsigned int numParticles = 0);
    virtual ~ParticleEffect();

    //void draw();

    void SetCamera(Camera* pCamera);
    void SetParticleEmitter(ParticleEmitter* pEmitter);

    // Test method to randomize the particles in an interesting way
    void RandomizeParticles();
    void EmitParticles();

    virtual void Update(float fDeltaTime);

    // Resize the particle buffer with numParticles
    void Resize(unsigned int numParticles);

protected:
    void setupBufferData() override;
    void RandomizeParticle(Particle& particle);
    void EmitParticle(Particle& particle);
public:
    // Build the vertex buffer from the particle buffer
    void BuildVertexBuffer();
private:
    Camera* m_pCamera;
    ParticleEmitter* m_pParticleEmitter;

    std::vector<Particle>      m_Particles;
    glm::mat4x4         m_LocalToWorldMatrix;

    // Apply this force to every particle in the effect
    //glm::vec3           m_Force;
};