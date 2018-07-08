#pragma once

#include <iostream>
#include <glm\glm.hpp>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

namespace Component
{

	class Component
	{
		private:

			std::string _name;
			glm::mat4 _positionMatrix;
			glm::vec3 _positionData;
			glm::mat4 _rotationMatrix;
			glm::vec3 _rotationData;
			glm::mat4 _scaleMatrix;
			glm::vec3 _scaleData;

		public :

			Component(const std::string&);
			~Component();

			const glm::mat4& getPositionMatrix() const;
			const glm::mat4& getRotationMatrix() const;
			const glm::mat4& getScaleMatrix() const;
			const glm::vec3& getPositionData() const;
			const glm::vec3& getRotationData() const;
			const glm::vec3& getScaleData() const;

			void setPosition(const glm::vec3&);
			void setRotation(const glm::vec3&);
			void setScale(const glm::vec3&);

			void addPosition(const glm::vec3&);
			void addRotation(const glm::vec3&);
			void addScale(const glm::vec3&);
	};
}