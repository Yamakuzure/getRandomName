#ifndef PWX_GETRANDOMNAME_ENVIRONMENT_H
#define PWX_GETRANDOMNAME_ENVIRONMENT_H

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

struct ENVIRONMENT
{
  /** Default constructor */
  explicit ENVIRONMENT(int32_t aSeed = 0);
  ENVIRONMENT()                   = delete;
  ENVIRONMENT(ENVIRONMENT const&) = delete;
  ENVIRONMENT& operator=(ENVIRONMENT const&) = delete;

  /** public members **/
  int32_t count;        //!< the number of names to generate
  bool    doWork;       //!< is set to false if no work is to be done
  string  filename;     //!< the name of the file to write the names to
  double  offsetX;      //!< Can be set by command line argument, defaults to -seed and +seed
  double  offsetY;      //!< Can be set by command line argument, defaults to -seed and +seed
  double  offsetZ;      //!< Can be set by command line argument, defaults to -seed and +seed
  double  offsetW;      //!< Can be set by command line argument, defaults to -seed and +seed
  int32_t maxChars;     //!< Can be set by command line argument, defaults to 15
  int32_t maxParts;     //!< Can be set by command line argument, defaults to 3
  int32_t maxSyllables; //!< Can be set by command line argument, defaults to 5
  double  modX;         //!< X-Coordinate modifier, can be set by modx argument, random -5 to +5 otherwise
  double  modY;         //!< Y-Coordinate modifier, can be set by modx argument, random -5 to +5 otherwise
  double  modZ;         //!< Z-Coordinate modifier, can be set by modx argument, random -5 to +5 otherwise
  double  modW;         //!< W-Coordinate modifier, can be set by modx argument, random -5 to +5 otherwise
  bool    useModVals;   //!< If one mod* argument is used, this becomes true. Negated by useRandom false.
  bool    useRandom;    //!< If set to false by -n/--norandom, all four mods are used as +1.0
  bool    useSeedOff;   //!< Is set to false by any of the x/y/z/w options
  int32_t seed;         //!< If set by command line argument, sets a new seed for RNG

  /** non struct methods **/
  const char * getVersion() const;
  void         setOffsets(double dX = 0.0, double dY = 0.0, double dZ = 0.0, double dW = 0.0, bool useArg = false);

private:
  string version;
};

/** this is a callback functions for pwx::PAH **/
void envCallback(char const* arg, char const* value);

/** needed to make the callbacks work **/
void setGlobalEnv(ENVIRONMENT* env);

#endif // PWX_GETRANDOMNAME_ENVIRONMENT_H
