#ifndef LAMINARFLOW_H
#define LAMINARFLOW_H

#include "./data.hpp"
#include <memory>

class Layer {
public:
    Layer() {

    }
    ~Layer() {

    }

private:


};

class LightSource {
public:
    LightSource() : cd(new Coordinate3()) {}
    LightSource(std::unique_ptr<Coordinate3> co) {
        this->cd = std::move(co);
    }

    ~LightSource() {
        
    }


private:
    std::unique_ptr<Coordinate3> cd;
};

class World
{
public:
    World() {

    }
    ~World() {

    }

    void merge() {

    }
    void merge(LightSource ls) {

    }
private:
    LightSource lightsource;

};



#endif //LAMINARFLOW_H