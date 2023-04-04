#ifndef LAMINARFLOW_DATA_H
#define LAMINARFLOW_DATA_H

#include "./logger.hpp"
#include <cmath>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <math.h>

class Coordinate3 {
public:
    Coordinate3() : logger(Logger()) {}
    virtual ~Coordinate3() {}

    Coordinate3(float a, float b, float c) : logger(Logger()) {
        set(a, b, c);
    }

    void set(float a, float b, float c) {
        standard(a, b, c);
        this->a = a;
        this->b = b;
        this->c = c;
    }
    void set(glm::vec3 vc) {
        float a=vc.x;
        float b=vc.y;
        float c=vc.z;
        set(a, b, c);
    }
    glm::vec3 get() {
        return glm::vec3(a, b, c);
    }

    virtual glm::vec3 getStd() {return glm::vec3(a,b,c);}

protected:
    virtual void standard(float& a, float& b, float& c) {}
    Logger logger;
    float a{}, b{}, c{};
};


class Spherical : Coordinate3 {
public:
    Spherical(float r, float theta, float phi) : Coordinate3{r, theta, phi} {}
    Spherical(Coordinate3& co) {
        float x = co.getStd().x;
        float y = co.getStd().y;
        float z = co.getStd().z;
        Spherical{
            x*x+y*y+z*z,
            std::acos(x/std::pow(x*x+y*y,0.5f)),
            std::acos(z/std::pow(x*x+y*y+z*z,0.5f))
        };
    }
    glm::vec3 getStd() override {
        return glm::vec3{
            a*std::sin(c)*std::cos(b),
            a*std::sin(c)*std::sin(b),
            a*std::cos(c)
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
            logger.Info("input theta not in [0,360), automatically modified");
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
            logger.Info("input phi not in [0,180], automatically modified");
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

            logger.Info("input r not in [0,+infinity), automatically modified");
        }
        r=_r;
        theta=_theta;
        phi=_phi;
    }
};

class Cartesian3 : Coordinate3 {
public:
    Cartesian3(float x, float y, float z) : Coordinate3{x, y, z} {}
    Cartesian3(Coordinate3& co) {
        Cartesian3(co.getStd().x,co.getStd().y,co.getStd().z);
    }
    Cartesian3& operator+=(const Cartesian3& r) {
        a+=r.a;
        b+=r.b;
        c+=r.c;
        return *this;
    }
    friend Cartesian3 operator+(Cartesian3 l, const Cartesian3& r) {
        return Cartesian3(l.a+r.a, l.b+r.b, l.c+r.c);
    }
};


#endif // LAMINARFLOW_DATA_H