#pragma once
#include<glm\glm.hpp>
#include<string>
#include<iostream>

namespace GL
{
	class Texture;
}

namespace Assets
{
	class Map;

	class Material
	{

		private :

			std::string _name;
			glm::vec3 _Ka_ambient;
			glm::vec3 _Kd_diffuse;
			glm::vec3 _Ks_specular;
			glm::vec3 _Tf_transmissionFilter;
			int _illum_illumination;
			float _d_dissolve;
			bool _halo;
			float _NS_specularExponent;
			float _sharpness_sharpness;
			float _Ni_opticalDensity;
			glm::vec3 _Ke;
			Map* _Ka_map;
			Map* _Kd_map;
			Map* _Ks_map;
			Map* _Ns_map;
			Map* _d_map;
			Map* _disp_map;
			Map* _decal_map;
			Map* _bump_map;

		public:

			Material(const std::string&);
			~Material();

			const std::string& getName() const;
			const glm::vec3& getAmbient() const;
			const glm::vec3& getDiffuse() const;
			const glm::vec3& getSpecular() const;
			const glm::vec3& getTransmissionFilter() const;
			int getIllumination() const;
			float getDissolve() const;
			bool getHalo() const;
			float getSpecularExponent() const;
			float getSharpness() const;
			float getopticalDensity() const;
			Map* getKamap() const;
			Map* getKdmap() const;
			Map* getKsmap() const;
			Map* getNsmap() const;
			Map* getdmap() const;
			Map* getDecalmap() const;
			Map* getDispmap() const;
			Map* getBumpmap() const;

			void setAmbient(const glm::vec3&);
			void setDiffuse(const glm::vec3&);
			void setSpecular(const glm::vec3&);
			void setTransmissionFilter(const glm::vec3&);
			void setIllumination(int);
			void setDissolve(float);
			void setHalo(bool);
			void setSpecularExponent(float);
			void setSharpness(float);
			void setopticalDensity(float);
			void setEmissiveCoeficient(const glm::vec3&);
			void setKamap(const std::string&) throw(...);
			void setKdmap(const std::string&) throw(...);
			void setKsmap(const std::string&) throw(...);
			void setNsmap(const std::string&) throw(...);
			void setdmap(const std::string&) throw(...);
			void setDecalmap(const std::string&) throw(...);
			void setDispmap(const std::string&) throw(...);
			void setBumpmap(const std::string&) throw(...);

			std::ostream& print(std::ostream&) const;
	};

	std::ostream& operator<<(std::ostream&, const Material&);

}

