#include "Component.h"

using namespace std;
using namespace glm;

namespace Component
{
	Component::Component(const string& name)
		:	_name(name),
			_positionMatrix(),
			_positionData(0,0,0),
			_rotationMatrix(),
			_rotationData(0,0,0),
			_scaleMatrix(),
			_scaleData(1,1,1)
	{
#ifdef _DEBUG
		cout << "[Component " << _name << "] [Component(string name)]..." << endl;
		cout << "[Component " << _name << "] [Component(string name)]...\tsuccess" << endl;
#endif
	}

	Component::~Component()
	{
#ifdef _DEBUG
		cout << "[Component " << _name << "] [~Component()]..." << endl;
		cout << "[Component " << _name << "] [~Component()]...\tsuccess" << endl;
#endif
	}

	const mat4& Component::getPositionMatrix() const
	{
		return _positionMatrix;
	}

	const mat4& Component::getRotationMatrix() const
	{
		return _rotationMatrix;
	}

	const mat4& Component::getScaleMatrix() const
	{
		return _scaleMatrix;
	}

	const vec3& Component::getPositionData() const
	{
		return _positionData;
	}

	const vec3& Component::getRotationData() const
	{
		return _rotationData;
	}

	const vec3& Component::getScaleData() const
	{
		return _scaleData;
	}

	void Component::setPosition(const vec3& position)
	{
		_positionData = position;
		_positionMatrix = glm::translate(mat4(), _positionData);
	}

	void Component::setRotation(const vec3& rotation)
	{
		_rotationData = rotation;
		_rotationMatrix = glm::rotate(mat4(), _rotationData.x, vec3(1, 0, 0));
		_rotationMatrix = glm::rotate(_rotationMatrix, _rotationData.y, vec3(0, 1, 0));
		_rotationMatrix = glm::rotate(_rotationMatrix, _rotationData.z, vec3(0, 0, 1));
	}
	void Component::setScale(const vec3& scaleData)
	{
		_scaleData = scaleData;
		_scaleMatrix = scale(mat4(), _scaleData);
	}

	void Component::addPosition(const vec3& position)
	{
		_positionData += position;
		_positionMatrix = glm::translate(_positionMatrix, _positionData);
	}

	void Component::addRotation(const vec3& rotation)
	{
		_rotationData = rotation;
		_rotationMatrix = glm::rotate(_rotationMatrix, _rotationData.x, vec3(1, 0, 0));
		_rotationMatrix = glm::rotate(_rotationMatrix, _rotationData.y, vec3(0, 1, 0));
		_rotationMatrix = glm::rotate(_rotationMatrix, _rotationData.z, vec3(0, 0, 1));
	}
	void Component::addScale(const vec3& scaleData)
	{
		_scaleData += scaleData;
		_scaleMatrix = scale(_scaleMatrix, _scaleData);
	}
}