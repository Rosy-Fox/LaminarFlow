#ifndef LAMINARFLOW_H
#define LAMINARFLOW_H

#include "./data.hpp"
#include <memory>

class Layer {
public:
    Layer() {
		// TODO: Layer construction
    }
    ~Layer() {
		// TODO: Layer deconstruction
    }

private:
	// TODO: Layer class structure
};

class LightSource {
public:
    LightSource() : cd(new Coordinate3()) {}
    explicit LightSource(std::unique_ptr<Coordinate3> co) {
        this->cd = std::move(co);
    }

    ~LightSource() {
        // TODO: LightSource deconstruction
    }


private:
    std::unique_ptr<Coordinate3> cd;
};

class World
{
public:
    World() {
		// TODO: World construction
    }
    ~World() {
		// TODO: World deconstruction
    }

    void merge() {
		// TODO: Merge function
    }
    void merge(LightSource ls) {
		// TODO: Merge LightSource
    }
private:
    LightSource lightSource;

};



#endif //LAMINARFLOW_H