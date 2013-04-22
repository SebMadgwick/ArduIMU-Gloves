//==============================================================================
// I2CBus.h
//==============================================================================
/*
    <description, licence, etc.>

    Algorithm code adapted from:
    http://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/

    Date        Author          Notes
    dd/mm/yyyy  Seb Madgwick    Initial release
*/
//==============================================================================
#ifndef AHRS_h
#define AHRS_h

//------------------------------------------------------------------------------
// Class declaration

class AHRS {
    public:
        // Variables
        float twoKp;            // 2 * proportional gain (Kp)
        float q0, q1, q2, q3;   // quaternion describing Earth relative to sensor

        // Functions
        AHRS();
        void update(float gx, float gy, float gz, float ax, float ay, float az);

    private:
        float invSqrt(float x);
};

//------------------------------------------------------------------------------
// Macros

#define DegToRad(degrees) (0.01745329252f * degrees)
#define RadToDeg(radians) (57.29577951308f * radians)

#endif
//==============================================================================
// End of file
//==============================================================================