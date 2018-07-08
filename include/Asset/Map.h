#pragma once
#include<string>
#include<glm\glm.hpp>
#include<iostream>

namespace GL
{
	class Texture;
}

namespace Assets
{
	enum mapType
	{
		Ka,
		Kd,
		Ks,
		Ns,
		d,
		decal,
		disp,
		bump
	};

	class Map
	{

		private:

			std::string _name;
			mapType _mapType;
			GL::Texture* _texture;
			bool _blendu;
			bool _blendv;
			bool _cc;
			bool _clamp;
			glm::vec3 _imfchanrgb;
			glm::vec3 _imfchanmlz;
			float _base;
			float _gain;
			glm::vec3 _o;
			glm::vec3 _s;
			glm::vec3 _t;
			int _textres;
			float _mult;
			float _boost;
			bool _map_aat;

		public:

			Map(mapType, const std::string&) throw(...);
			~Map();

			GL::Texture* getTexture() const;
			const std::string& getName() const;
			bool getBlendu() const;
			bool getBlendv() const;
			bool getCc() const throw(...);
			bool getClamp() const throw(...);
			const glm::vec3& getImfchanrgb() const;
			const glm::vec3& getImfchanmlz() const;
			float getBase() const;
			float getGain() const;
			const glm::vec3& getO() const;
			const glm::vec3& getS() const;
			const glm::vec3& getT() const;
			int getTextres() const;
			float getMult() const;
			float getBoost() const;
			float getMapaat() const;

			void setBlendu(bool);
			void setBlendv(bool);
			void setCc(bool) throw(...);
			void setClamp(bool) throw(...);
			void setImfchanrgb(const glm::vec3&);
			void setImfchanmlz(const glm::vec3&);
			void setBase(float);
			void setGain(float);
			void setO(const glm::vec3&);
			void setS(const glm::vec3&);
			void setT(const glm::vec3&);
			void setTextres(int);
			void setMult(float);
			void setBoost(float);
			void setMapaat(bool);

			std::ostream& print(std::ostream&) const;
	};

	std::ostream& operator<<(std::ostream&, const Map&);

}


