#ifndef LAMINARFLOW_H
#define LAMINARFLOW_H

#include "./data.hpp"

class Layer
{
    public:
        Layer()
        {

        }
        ~Layer()
        {

        }

    private:


};

class LightSource
{
    public:
        LightSource()
        {

        }

        ~LightSource()
        {

        }

        /**
         * @brief Set the Coordinate of Light Source
         *
         * @param r
         * @param theta (0,360)
         * @param phi (0,180)
         */
        void setCoordinate(float r, float theta, float phi)
        {
            if(theta>360 || theta<0 || phi>180 || phi<0)
                return;

                /// TODO: logger required
        }
        float getR()
        {
            return r;
        }
        float getTheta()
        {
            return theta;
        }
        float getPhi()
        {
            return phi;
        }
    private:
        float r;
        float phi;
        float theta;
};

class World
{
    public:
        World()
        {

        }
        ~World()
        {

        }

        void merge()
        {

        }
        void merge(Coordinate coordinate)
        {

        }
    private:
        LightSource lightsource;

};



#endif //LAMINARFLOW_H