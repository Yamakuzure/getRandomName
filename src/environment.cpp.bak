/** @file environment.cpp
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
