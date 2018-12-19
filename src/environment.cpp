#include <cstring>
#include <pwx_macros.h>

#include "environment.h"

ENVIRONMENT* global_env = nullptr;

/** @brief default ctor
**/
ENVIRONMENT::ENVIRONMENT( int32_t aSeed )
  : seed( aSeed )
{ }

/** @brief return version as c-string
  *
  * @todo: document this function
**/
const char* ENVIRONMENT::getVersion() const {
    return( version.c_str() );
}

/** @brief setOffsets
  *
  * simply sets offsetX/Y/Z/W according to mod*, useModVals and useRandom
**/
void ENVIRONMENT::setOffsets( double dX, double dY, double dZ, double dW, bool useArg ) {
    if ( useArg ) {
        offsetX = dX;
        offsetY = dY;
        offsetZ = dZ;
        offsetW = dW;
    } else if ( useModVals ) {
        offsetX += modX;
        offsetY += modY;
        offsetZ += modZ;
        offsetW += modW;
    } else {
        offsetX++;
        offsetY++;
        offsetZ++;
        offsetW++;
    }
}

/** this is a callback functions for pwx::PAH **/
void envCallback( char const* arg, char const* value ) {
    if ( STREQ( arg, "x" ) ) {
        global_env->offsetX     = atof( value );
        global_env->useSeedOff  = false;
    } else if ( STREQ( arg, "y" ) ) {
        global_env->offsetY     = atof( value );
        global_env->useSeedOff  = false;
    } else if ( STREQ( arg, "z" ) ) {
        global_env->offsetZ     = atof( value );
        global_env->useSeedOff  = false;
    } else if ( STREQ( arg, "w" ) ) {
        global_env->offsetW     = atof( value );
        global_env->useSeedOff  = false;
    } else if ( STREQ( arg, "modx" ) ) {
        global_env->modX        = atof( value );
        global_env->useModVals  = true;
        global_env->useRandom   = false;
    } else if ( STREQ( arg, "mody" ) ) {
        global_env->modY        = atof( value );
        global_env->useModVals  = true;
        global_env->useRandom   = false;
    } else if ( STREQ( arg, "modz" ) ) {
        global_env->modZ        = atof( value );
        global_env->useModVals  = true;
        global_env->useRandom   = false;
    } else if ( STREQ( arg, "modw" ) ) {
        global_env->modW        = atof( value );
        global_env->useModVals  = true;
        global_env->useRandom   = false;
    }
}

void setGlobalEnv( ENVIRONMENT* env ) {
    global_env = env;
}
