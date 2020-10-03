// Vector3 CLASS HEADER

/// Class used to represent and perform operations with 3-Dimensional vectors

#include<iostream>

class Vector3 {
	private:
		float x, y, z;
	public:
		// FUNCTION DECLARATIONS
		/********************************************/ /**
		 * Creates a new Vector3 object with all coordinates set to 0
		 ***********************************************/
		Vector3();

		/********************************************/ /**
		 * Function used to load a Binary image
		 *
		 * @param _x The x coordinate to be assigned to the new Vector3
		 * @param _y The y coordinate to be assigned to the new Vector3
		 * @param _z The z coordinate to be assigned to the new Vector3
		 ***********************************************/
		Vector3(float _x, float _y, float _z);

		/********************************************/ /**
		 * Function used to get the Vector3's x coordinate
		 *
		 * @return x The Vector3's current x coordinate
		 ***********************************************/
		float getX();

		/********************************************/ /**
		 * Function used to get the Vector3's y coordinate
		 *
		 * @return y The Vector3's current y coordinate
		 ***********************************************/
		float getY();

		/********************************************/ /**
		 * Function used to get the Vector3's z coordinate
		 *
		 * @return z The Vector3's current z coordinate
		 ***********************************************/
		float getZ();

		/********************************************/ /**
		 * Function used to set the Vector3's x coordinate
		 * @param _x The new x coordinate we want to assign to our vector
		 ***********************************************/
		void setX(float _x);

		/********************************************/ /**
		 * Function used to set the Vector3's y coordinate
		 * @param _y The new x coordinate we want to assign to our vector
		 ***********************************************/
		void setY(float _y);

		/********************************************/ /**
		 * Function used to set the Vector3's z coordinate
		 * @param _z The new x coordinate we want to assign to our vector
		 ***********************************************/
		void setZ(float _z);

		/********************************************/ /**
		 * Overloading of the + operator when summing two Vector3
		 *
		 * @param vec The Vector3 we want to sum with our Vector3
		 * @return vecSum The sum of the two vectors
		 ***********************************************/
		Vector3 operator+(const Vector3& vec);

		/********************************************/ /**
		 * Overloading of the - operator when subtracting two Vector3
		 *
		 * @param vec The Vector3 we want to subtract with our Vector3
		 * @return vecSub The subtraction of the two vectors
		 ***********************************************/
		Vector3 operator-(const Vector3& vec);

		/********************************************/ /**
		 * Overloading of the += operator. Assigns new coordinates to our vector
		 *
		 * @param vec The Vector3 we want to sum to our Vector3
		 ***********************************************/
		Vector3& operator+=(const Vector3& vec);

		/********************************************/ /**
		 * Overloading of the -= operator. Assigns new coordinates to our vector
		 *
		 * @param vec The Vector3 we want to sub with our Vector3
		 ***********************************************/
		Vector3& operator-=(const Vector3& vec);

		/********************************************/ /**
		 * Overloading of the * operator. Gets the multiplication of our vector by a scalar
		 *
		 * @param scal The scalar we want to use to multiply
		 * @return vecMul The resulting multiplication
		 ***********************************************/
		Vector3 operator*(float scalar);

		/********************************************/ /**
		 * Overloading of the *= operator. Assigns new coordinates to our vector
		 *
		 * @param scal The scalar we want to use to multiply
		 * @return vecMul The resulting multiplication
		 ***********************************************/
		Vector3& operator*=(float scalar);

		/********************************************/ /**
		 * Overloading of the / operator. Gets the division of our vector by a scalar
		 *
		 * @param scal The scalar we want to use to divide
		 * @return vecDiv The resulting division
		 ***********************************************/
		Vector3 operator/(float scalar);

		/********************************************/ /**
		 * Overloading of the /= operator. Assigns new coordinates to our vector
		 *
		 * @param scal The scalar we want to use to divide our vector by
		 ***********************************************/
		Vector3& operator/=(float scalar);

		/********************************************/ /**
		 * Overloading of the = operator. Assigns new coordinates to our vector
		 *
		 * @param vec The vector with the coordenates to be copied
		 ***********************************************/
		Vector3& operator=(const Vector3& vec);

		/********************************************/ /**
		 * Overloading of the << operator. Prints our vector's coordinates
		 ***********************************************/
		friend std::ostream& operator<<(std::ostream& output, const Vector3& vec);

		/********************************************/ /**
		 * Returns the vector's magnitude
		 *
		 * @return mag The vector's magnitude
		 ***********************************************/
		float magnitude();

		/********************************************/ /**
		 * Returns the Vector normalized
		 *
		 * @return norm The normalized equivalent of our vector
		 ***********************************************/
		Vector3 normalized();

		/********************************************/ /**
		 * Returns the Dot product of two vectors
		 *
		 * @param vec The vector we want to do the Dot product with
		 * @return dot The resulting Dot product of the vectors
		 ***********************************************/
		float dotProd(const Vector3& vec);

		/********************************************/ /**
		 * Returns the Cross product of two vectors
		 *
		 * @param vec The vector we want to do the Cross product with
		 * @return dot The resulting Cross product of the vectors
		 ***********************************************/
		Vector3 crossProd(const Vector3& vec);
};