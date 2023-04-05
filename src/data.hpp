#ifndef LAMINARFLOW_DATA_H
#define LAMINARFLOW_DATA_H

#include "./logger.hpp"
#include <cmath>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class Coordinate3 {
public:
    Coordinate3() : logger(Logger()) {}
    virtual ~Coordinate3() = default;

    Coordinate3(float a, float b, float c) : logger(Logger()) {
        set(a, b, c);
    }

    void set(float a, float b, float c) {
        standard(a, b, c);
        this->_a = a;
        this->_b = b;
        this->_c = c;
    }
    void set(glm::vec3 vc) {
        float a=vc.x;
        float b=vc.y;
        float c=vc.z;
        set(a, b, c);
    }
    [[nodiscard]] glm::vec3 get() const {
        return {_a, _b, _c};
    }

    virtual glm::vec3 getStd() {
		return {_a, _b, _c};
	}

protected:
    virtual void standard(float& a, float& b, float& c) {}
    Logger logger;
    float _a{}, _b{}, _c{};
};


class Spherical : Coordinate3 {
public:
    Spherical(float r, float theta, float phi) : Coordinate3{r, theta, phi} {}
	explicit Spherical(Coordinate3& co) : Spherical(
			co.getStd().x * co.getStd().x + co.getStd().y * co.getStd().y + co.getStd().z * co.getStd().z,
			std::acos(co.getStd().x / std::sqrt(co.getStd().x * co.getStd().x + co.getStd().y * co.getStd().y)),
			std::acos(co.getStd().z / std::sqrt(co.getStd().x * co.getStd().x + co.getStd().y * co.getStd().y + co.getStd().z * co.getStd().z))
			) {}

	glm::vec3 getStd() override {
        return glm::vec3{
            _a * std::sin(_c) * std::cos(_b),
            _a * std::sin(_c) * std::sin(_b),
            _a * std::cos(_c)
        };
    }
protected:
    void standard(float& r, float& theta, float& phi) override {
        float _r = r;
        float _theta = theta;
        float _phi = phi;

        if (_theta < 0 || _theta >= 360) {
            while (_theta < 0) {
                _theta += 360;
            }
            while (_theta >= 360) {
                _theta -= 360;
            }
            Logger::info("input theta not in [0,360), automatically modified");
        }

        if (_phi < 0 || _phi > 180) {
            while (_phi < -180) {
                _phi += 360;
            }
            while (_phi > 180) {
                _phi -= 360;
            }

            if (_phi < 0) {
                _phi = -_phi;
                if (_theta == 180)
                    _theta = 0;
                else if (_theta > 180)
                    _theta -= 180;
                else
                    _theta += 180;
            }
            Logger::warn("input phi not in [0,180], automatically modified");
        }

        if (_r < 0) {
            _r = -_r;

            if (_theta == 180)
                _theta = 0;
            else if (_theta > 180)
                _theta -= 180;
            else
                _theta += 180;

            _phi = 180 - _phi;

            Logger::warn("input r not in [0,+infinity), automatically modified");
        }
        r=_r;
        theta=_theta;
        phi=_phi;
    }
};

class Cartesian3 : Coordinate3 {
public:
    Cartesian3(float x, float y, float z) : Coordinate3{x, y, z} {}
    explicit Cartesian3(Coordinate3& co) : Cartesian3(co.getStd().x,co.getStd().y,co.getStd().z) {}
    Cartesian3& operator+=(const Cartesian3& r) {
        _a += r._a;
        _b += r._b;
        _c += r._c;
        return *this;
    }
    friend Cartesian3 operator+(const Cartesian3& l, const Cartesian3& r) {
        return {l._a + r._a, l._b + r._b, l._c + r._c};
    }
};


#endif // LAMINARFLOW_DATA_H