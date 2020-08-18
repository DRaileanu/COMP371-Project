#include "ParticleEmitter.h"
#include "Camera.h"
#include "Random.h"
#include "ParticleEffect.h"
#include <algorithm>


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

ParticleEffect::ParticleEffect(unsigned int numParticles)
    : m_pCamera(NULL)
    , m_pParticleEmitter(NULL)
    , m_LocalToWorldMatrix(1)
    //, m_Force(0, -9.81f, 0)
{
    Resize(numParticles);
    setupBufferData();
}

ParticleEffect::~ParticleEffect() {}

void ParticleEffect::SetCamera(Camera* pCamera)
{
    m_pCamera = pCamera;
}

void ParticleEffect::SetParticleEmitter(ParticleEmitter* pEmitter)
{
    m_pParticleEmitter = pEmitter;
}


void ParticleEffect::RandomizeParticle(Particle& particle)
{
    particle.m_fAge = 0.0f;
    particle.m_fLifeTime = RandRange(0.75, 1.5);

    glm::vec3 unitVec = RandUnitVec();

    particle.m_Position = unitVec * 1.0f;
    particle.m_Velocity = unitVec * RandRange(2.0, 5.0);
}

void ParticleEffect::RandomizeParticles()
{
    for (unsigned int i = 0; i < m_Particles.size(); ++i)
    {
        RandomizeParticle(m_Particles[i]);
    }
}

void ParticleEffect::EmitParticle(Particle& particle)
{
    assert(m_pParticleEmitter != NULL);
    m_pParticleEmitter->EmitParticle(particle);
}

void ParticleEffect::EmitParticles()
{
    if (m_pParticleEmitter == NULL)
    {
        RandomizeParticles();
    }
    else
    {
        for (unsigned int i = 0; i < m_Particles.size(); ++i)
        {
            EmitParticle(m_Particles[i]);
        }
    }
}

void ParticleEffect::BuildVertexBuffer()
{
    const glm::vec3 X(0.5, 0, 0);
    const glm::vec3 Y(0, 0.5, 0);
    const glm::vec3 Z(0, 0, 0.5);

    glm::quat cameraRotation;

    if (m_pCamera != NULL)
    {
        //cameraRotation = glm::quat(glm::radians(m_pCamera->GetRotation()));
        cameraRotation = glm::quat(glm::radians(glm::vec3(m_pCamera->Pitch, 90 + m_pCamera->Yaw, 0.0f)));
    }



    for (unsigned int i = 0; i < m_Particles.size(); ++i)
    {
        Particle& particle = m_Particles[i];
        glm::quat rotation = glm::angleAxis(particle.m_fRotate, glm::vec3(0.75, 0.5, 1.0f));

        unsigned int vertexIndex = i * 8;
        unsigned int indicesIndex = i * 36;
        // Bottom-left-front
        vertices[vertexIndex + 0] = particle.m_Position + (rotation * (-X - Y + Z) * particle.m_fSize);
        colours[vertexIndex + 0] = particle.m_Color;
        // Bottom-right-front
        vertices[vertexIndex + 1] = particle.m_Position + (rotation * (X - Y + Z) * particle.m_fSize);
        colours[vertexIndex + 1] = particle.m_Color;
        // Top-right-front
        vertices[vertexIndex + 2] = particle.m_Position + (rotation * (X + Y + Z) * particle.m_fSize);
        colours[vertexIndex + 2] = particle.m_Color;
        // Top-left-front
        vertices[vertexIndex + 3] = particle.m_Position + (rotation * (-X + Y + Z) * particle.m_fSize);
        colours[vertexIndex + 3] = particle.m_Color;    
        // Bottom-left-back
        vertices[vertexIndex + 4] = particle.m_Position + (rotation * (-X - Y - Z) * particle.m_fSize);
        colours[vertexIndex + 4] = particle.m_Color;
        // Bottom-right-back
        vertices[vertexIndex + 5] = particle.m_Position + (rotation * (X - Y - Z) * particle.m_fSize);
        colours[vertexIndex + 5] = particle.m_Color;
        // Bottom-right-back
        vertices[vertexIndex + 6] = particle.m_Position + (rotation * (X + Y - Z) * particle.m_fSize);
        colours[vertexIndex + 6] = particle.m_Color;
        // Bottom-left-back
        vertices[vertexIndex + 7] = particle.m_Position + (rotation * (-X + Y - Z) * particle.m_fSize);
        colours[vertexIndex + 7] = particle.m_Color;

        indices[indicesIndex + 0] = vertexIndex + 0;
        indices[indicesIndex + 1] = vertexIndex + 1;
        indices[indicesIndex + 2] = vertexIndex + 2;

        indices[indicesIndex + 3] = vertexIndex + 0;
        indices[indicesIndex + 4] = vertexIndex + 2;
        indices[indicesIndex + 5] = vertexIndex + 3;

        indices[indicesIndex + 6] = vertexIndex + 5;
        indices[indicesIndex + 7] = vertexIndex + 4;
        indices[indicesIndex + 8] = vertexIndex + 7;

        indices[indicesIndex + 9] = vertexIndex + 5;
        indices[indicesIndex + 10] = vertexIndex + 7;
        indices[indicesIndex + 11] = vertexIndex + 6;

        indices[indicesIndex + 12] = vertexIndex + 4;
        indices[indicesIndex + 13] = vertexIndex + 0;
        indices[indicesIndex + 14] = vertexIndex + 3;

        indices[indicesIndex + 15] = vertexIndex + 4;
        indices[indicesIndex + 16] = vertexIndex + 3;
        indices[indicesIndex + 17] = vertexIndex + 7;

        indices[indicesIndex + 18] = vertexIndex + 1;
        indices[indicesIndex + 19] = vertexIndex + 5;
        indices[indicesIndex + 20] = vertexIndex + 6;

        indices[indicesIndex + 21] = vertexIndex + 1;
        indices[indicesIndex + 22] = vertexIndex + 6;
        indices[indicesIndex + 23] = vertexIndex + 2;

        indices[indicesIndex + 24] = vertexIndex + 4;
        indices[indicesIndex + 25] = vertexIndex + 5;
        indices[indicesIndex + 26] = vertexIndex + 1;

        indices[indicesIndex + 27] = vertexIndex + 4;
        indices[indicesIndex + 28] = vertexIndex + 1;
        indices[indicesIndex + 29] = vertexIndex + 0;

        indices[indicesIndex + 30] = vertexIndex + 3;
        indices[indicesIndex + 31] = vertexIndex + 2;
        indices[indicesIndex + 32] = vertexIndex + 6;

        indices[indicesIndex + 33] = vertexIndex + 3;
        indices[indicesIndex + 34] = vertexIndex + 6;
        indices[indicesIndex + 35] = vertexIndex + 7;


    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[VERTEX_BUFFER]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * vertices.size(), &vertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[COLOUR_BUFFER]);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * colours.size(), &colours[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjects[INDEX_BUFFER]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * indices.size(), &indices[0]);
    glBindVertexArray(0);
}

void ParticleEffect::Update(float fDeltaTime)
{
    for (unsigned int i = 0; i < m_Particles.size(); ++i)
    {
        Particle& particle = m_Particles[i];

        particle.m_fAge += fDeltaTime;
        if (particle.m_fAge > particle.m_fLifeTime)
        {
            if (m_pParticleEmitter != NULL) EmitParticle(particle);
            else RandomizeParticle(particle);
        }

        float lifeRatio = glm::clamp(particle.m_fAge / particle.m_fLifeTime, 0.0f, 1.0f);
       // particle.m_Velocity += (m_Force * fDeltaTime);
        particle.m_Position += (particle.m_Velocity * fDeltaTime);
        particle.m_Color = glm::vec3(1.0f, 0.0f, 0.0f);
        particle.m_fRotate = glm::lerp<float>(0.0f, 90.0f, lifeRatio);
        particle.m_fSize = glm::lerp<float>(0.050f, 0.025f, lifeRatio);
    }

    BuildVertexBuffer();
}


/*
void ParticleEffect::Render()
{
    glDisable(GL_DEPTH_TEST);           // Disables Depth Testing
    glEnable(GL_BLEND);                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // Type Of Blending To Perform
    glEnable(GL_TEXTURE_2D);            // Enable textures

    glPushMatrix();
    glMultMatrixf(glm::value_ptr(m_LocalToWorldMatrix));

    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Pos));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), &(m_VertexBuffer[0].m_Diffuse));

    glDrawArrays(GL_QUADS, 0, m_VertexBuffer.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindTexture(GL_TEXTURE_2D, 0);


    glPopMatrix();

}
*/

void ParticleEffect::Resize(unsigned int numParticles)
{
    numParticles = std::min(numParticles, MAX_PARTICLES);
    m_Particles.resize(numParticles, Particle());
    vertices.resize(8 * numParticles);
    colours.resize(8 * numParticles);
    indices.resize(36 * numParticles);
}

void ParticleEffect::setupBufferData() {
    glBindVertexArray(VAO);
    //positions
    glGenBuffers(1, &bufferObjects[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 8 * MAX_PARTICLES, NULL, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_BUFFER);
    
    //colours
    glGenBuffers(1, &bufferObjects[COLOUR_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObjects[COLOUR_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 8 * MAX_PARTICLES, NULL, GL_STATIC_DRAW);
    glVertexAttribPointer(COLOUR_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(COLOUR_BUFFER);
    
    glGenBuffers(1, &bufferObjects[INDEX_BUFFER]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjects[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 36 * MAX_PARTICLES, NULL, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

/*
void ParticleEffect::draw() {
    GLboolean cullFaceState;
    glGetBooleanv(GL_CULL_FACE, &cullFaceState);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);           // Disables Depth Testing
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Drawable::draw();
    glCullFace(cullFaceState);
    glEnable(GL_DEPTH_TEST);
}
*/