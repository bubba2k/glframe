#ifndef BODY_HPP_
#define BODY_HPP_

#include "Mesh.hpp"

class EntityInstance;

class Entity
{
	friend class Renderer;
	friend class EntityInstance;
	friend int numTotalEntityInstances(); 

	int id;

	Mesh * meshPtr;

    int shaderID;

    glm::mat4 m_transformationMatrix;
    glm::vec3 locationVector,
              rotationVector, // Euler angles
              scalingVector;

	bool transformationHasChanged;

	Tracker<EntityInstance> instanceTracker; // tracks instances

	static Tracker<Entity> entityTracker;

public:
	Entity();
	~Entity();

	Entity (const Entity &);
	Entity& operator=(const Entity &);

	inline int getID() { return this->id; };

	glm::mat4 getTransformationMatrix();

	EntityInstance createInstance();
	inline int getNumInstances() { return instanceTracker.num(); };

	void setMesh(Mesh& mesh);

	void setShader(ShaderProgram &argShader);

    void setPosition(glm::vec3 argPosition);
    void setPosition(float argX, float argY, float argZ);

    void setRotation(glm::vec3 argRotation);
    void setRotation(float argX, float argY, float argZ);

    void setScale(glm::vec3 argScale);
    void setScale(float argX, float argY, float argZ);
    void setScale(float argUniformScale);
};

class EntityInstance
{
	int id;

	Entity * baseEntity;

	glm::mat4 m_transformationMatrix;
	glm::vec3 locationVector,
			  rotationVector, // Euler angles
			  scalingVector;

	bool transformationHasChanged;

public:
	EntityInstance(Entity &);
	~EntityInstance();

	EntityInstance(const EntityInstance &);
	EntityInstance& operator=(const EntityInstance &);

	inline int getID() { return this->id; }

	glm::mat4 getTransformationMatrix();

    void setPosition(glm::vec3 argPosition);
    void setPosition(float argX, float argY, float argZ);

    void setRotation(glm::vec3 argRotation);
    void setRotation(float argX, float argY, float argZ);

    void setScale(glm::vec3 argScale);
    void setScale(float argX, float argY, float argZ);
    void setScale(float argUniformScale);
};

#endif
