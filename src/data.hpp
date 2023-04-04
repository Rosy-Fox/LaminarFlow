#ifndef LAMINARFLOW_DATA_H
#define LAMINARFLOW_DATA_H

#include "./logger.hpp"

class Coordinate
{
    public:
        enum Spherical{r, theta, phi};
        enum Cartesian{x, y, z};

        Coordinate()
        {
            logger = new Logger();
        }
        ~Coordinate()
        {
            delete logger;
        }
        void setSpherical()
        {
            
        }
        void setCartesian()
        {
            
        }
        float getSpherical(enum Spherical t)
        {
            switch (t)
            {
                case Spherical::r       : return _r;    break;
                case Spherical::theta   : return _theta;break;
                case Spherical::phi     : return _phi;  break;
                default:
                    logger->Warn("invalid Spherical Coordinate type, return 0.");
                    return 0;
            }
        }
    
    private:
        float _r, _theta, _phi;
        float _x, _y, _z;
        Logger *logger;

};

#endif //LAMINARFLOW_DATA_H