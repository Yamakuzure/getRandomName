#ifndef PWX_GETRANDOMNAME_ENVIRONMENT_H
#define PWX_GETRANDOMNAME_ENVIRONMENT_H

/** @file environment.h
  *
  * This file is part of getRandomName
  *
  * (c) 2007 - 2018 PrydeWorX
  * @author Sven Eden, PrydeWorX - Bardowick, Germany
  *         sven.eden@prydeworx.com
  *         https://github.com/Yamakuzure/getRandomName ; https://prydeworx.com/getRandomName
  *
  * getRandomName is free software under MIT License
  * 
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  * 
  * The above copyright notice and this permission notice shall be included in all
  * copies or substantial portions of the Software.
  * 
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  *
  * History and change log are maintained in main.cpp
**/


#include <cmath>
#include <cstdlib>
#include <string>

using std::string;

/** @brief ENVIRONMENT
  *
  * This is not a real class, but a "classed" pImpl struct.
  * It is used to circumvent the necessity to add too many arguments to
  * global functions.
  **/

struct ENVIRONMENT {
    /** Default constructor */
    explicit ENVIRONMENT( int32_t aSeed = 0 );
    ENVIRONMENT()                                = delete;
    ENVIRONMENT( ENVIRONMENT const& )            = delete;
    ENVIRONMENT& operator=( ENVIRONMENT const& ) = delete;

    /** public members **/
    int32_t count        = 1;     //!< the number of names to generate
    bool    doWork       = true;  //!< is set to false if no work is to be done
    string  filename     = "";    //!< the name of the file to write the names to
    double  offsetX      = 0.0;   //!< Can be set by command line argument, defaults to -seed and +seed
    double  offsetY      = 0.0;   //!< Can be set by command line argument, defaults to -seed and +seed
    double  offsetZ      = 0.0;   //!< Can be set by command line argument, defaults to -seed and +seed
    double  offsetW      = 0.0;   //!< Can be set by command line argument, defaults to -seed and +seed
    int32_t maxChars     = 15;    //!< Can be set by command line argument, defaults to 15
    int32_t maxParts     = 3;     //!< Can be set by command line argument, defaults to 3
    int32_t maxSyllables = 5;     //!< Can be set by command line argument, defaults to 5
    double  modX         = 0.0;   //!< X-Coordinate modifier, can be set by modx argument, random -5 to +5 otherwise
    double  modY         = 0.0;   //!< Y-Coordinate modifier, can be set by modx argument, random -5 to +5 otherwise
    double  modZ         = 0.0;   //!< Z-Coordinate modifier, can be set by modx argument, random -5 to +5 otherwise
    double  modW         = 0.0;   //!< W-Coordinate modifier, can be set by modx argument, random -5 to +5 otherwise
    bool    useModVals   = false; //!< If one mod* argument is used, this becomes true. Negated by useRandom false.
    bool    useRandom    = true;  //!< If set to false by -n/--norandom, all four mods are used as +1.0
    bool    useSeedOff   = true;  //!< Is set to false by any of the x/y/z/w options
    int32_t seed;                 //!< If set by command line argument, sets a new seed for RNG

    /** non struct methods **/
    char const* getVersion() const;
    void        setOffsets( double dX = 0.0, double dY = 0.0, double dZ = 0.0, double dW = 0.0, bool useArg = false );

  private:
    string version = VERSION;
};

/** this is a callback functions for pwx::PAH **/
void envCallback( char const* arg, char const* value );

/** needed to make the callbacks work **/
void setGlobalEnv( ENVIRONMENT* env );

#endif // PWX_GETRANDOMNAME_ENVIRONMENT_H
