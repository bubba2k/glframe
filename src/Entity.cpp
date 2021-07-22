#include "Entity.hpp"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

Tracker<Entity> Entity::entityTracker;

Entity::Entity()
	: meshPtr(nullptr), texturePtr(nullptr),
	  shaderID(-1), locationVector{0, 0, 0},
	  rotationVector{0, 0, 0}, scalingVector{1, 1, 1},
	  transformationHasChanged(true)
{
	this->id = Entity::entityTracker.track(this);
}

Entity::~Entity()
{
	Entity::entityTracker.forget(this->id);
}

EntityInstance Entity::createInstance()
{
	return EntityInstance(*this);
}

glm::mat4 Entity::getTransformationMatrix()
{
    if(transformationHasChanged)
	{
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), 
									  locationVector);
        glm::mat4 scalingMatrix = glm::scale(scalingVector);

        glm::quat rotationQuaternion(rotationVector);
        glm::mat4 rotationMatrix = glm::toMat4(rotationQuaternion);


		m_transformationMatrix = translationMatrix * rotationMatrix * 
								 scalingMatrix;

	    transformationHasChanged = false;
    }

	return m_transformationMatrix;
}

void Entity::setMesh(Mesh& mesh)
{
	meshPtr = &mesh;
}

void Entity::setShader(ShaderProgram &argShader)
{
	shaderID = argShader.getID();
}

void Entity::setTexture(Texture &texture)
{
	texturePtr = &texture;
}

void Entity::setPosition(glm::vec3 argPosition)
{
	locationVector = argPosition;
	transformationHasChanged = true;
}
void Entity::setPosition(float argPosX, float argPosY, float argPosZ)
{
	locationVector = {argPosX, argPosY, argPosZ};
	transformationHasChanged = true;
}

void Entity::setRotation(glm::vec3 argRotation)
{	
	rotationVector = argRotation;
	for(int i = 0; i < rotationVector.length(); i++)
	{
		rotationVector[i] = glm::radians(rotationVector[i]);
	}
	transformationHasChanged = true;
}
void Entity::setRotation(float argRotX, float argRotY, float argRotZ)
{
	rotationVector = {argRotX, argRotY, argRotZ};
	for(int i = 0; i < rotationVector.length(); i++)
	{
		rotationVector[i] = glm::radians(rotationVector[i]);
	}
	transformationHasChanged = true;
}

void Entity::setScale(glm::vec3 argScale)
{
	scalingVector = argScale;
	transformationHasChanged = true;
}
void Entity::setScale(float argScaleX, float argScaleY, float argScaleZ)
{
	scalingVector = {argScaleX, argScaleY, argScaleZ};
	transformationHasChanged = true;
}
void Entity::setScale(float argUniformScale)
{
	scalingVector = {argUniformScale, argUniformScale, argUniformScale};
	transformationHasChanged = true;
}

EntityInstance::EntityInstance(Entity& entity)
	: locationVector{0, 0, 0}, rotationVector{0, 0, 0}, scalingVector{1, 1, 1},
	  transformationHasChanged(true),
	  _isVisible(true)
{
	entity.instanceTracker.track(this);
	this->baseEntity = &entity;
}

EntityInstance::~EntityInstance()
{
	baseEntity->instanceTracker.forget(this->id);
}

// copy constructor
EntityInstance::EntityInstance(const EntityInstance &old)
{
	this->rotationVector = old.rotationVector;
	this->locationVector = old.locationVector;
	this->scalingVector  = old.scalingVector;
	this->baseEntity = old.baseEntity;
	this->transformationHasChanged = true;

	this->id = baseEntity->instanceTracker.track(this);
}

// copy assignment operator
EntityInstance& EntityInstance::operator=(const EntityInstance &old)
{
	this->rotationVector = old.rotationVector;
	this->locationVector = old.locationVector;
	this->scalingVector  = old.scalingVector;
	this->baseEntity = old.baseEntity;
	this->transformationHasChanged = true;

	this->id = baseEntity->instanceTracker.track(this);

	return *this;
}

void EntityInstance::setPosition(glm::vec3 argPosition)
{
	locationVector = argPosition;
	transformationHasChanged = true;
}
void EntityInstance::setPosition(float argPosX, float argPosY, float argPosZ)
{
	locationVector = {argPosX, argPosY, argPosZ};
	transformationHasChanged = true;
}

void EntityInstance::setRotation(glm::vec3 argRotation)
{	
	rotationVector = argRotation;
	for(int i = 0; i < rotationVector.length(); i++)
	{
		rotationVector[i] = glm::radians(rotationVector[i]);
	}
	transformationHasChanged = true;
}
void EntityInstance::setRotation(float argRotX, float argRotY, float argRotZ)
{
	rotationVector = {argRotX, argRotY, argRotZ};
	for(int i = 0; i < rotationVector.length(); i++)
	{
		rotationVector[i] = glm::radians(rotationVector[i]);
	}
	transformationHasChanged = true;
}

void EntityInstance::setScale(glm::vec3 argScale)
{
	scalingVector = argScale;
	transformationHasChanged = true;
}

void EntityInstance::setScale(float argScaleX, float argScaleY, float argScaleZ)
{
	scalingVector = {argScaleX, argScaleY, argScaleZ};
	transformationHasChanged = true;
}

void EntityInstance::setScale(float argUniformScale)
{
	scalingVector = {argUniformScale, argUniformScale, argUniformScale};
	transformationHasChanged = true;
}

glm::mat4 EntityInstance::getTransformationMatrix()
{
    if(transformationHasChanged || baseEntity->transformationHasChanged)
	{
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), 
									  locationVector);
        glm::mat4 scalingMatrix = glm::scale(scalingVector);

        glm::quat rotationQuaternion(rotationVector);
        glm::mat4 rotationMatrix = glm::toMat4(rotationQuaternion);


		m_transformationMatrix = translationMatrix * rotationMatrix * 
								 scalingMatrix;

	    transformationHasChanged = false;
    }

	return m_transformationMatrix;
}
