/** @file main.cpp
  *
  * @brief main file for getRandomName
  *
  * This is the main file for getRandomName, a small tool to create random names
  * utilizing RNG of the pwxLib.
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
  @verbatim
  * History and Changelog:
  * ----------------------
  * Version   Date        Maintainer      Change(s)
  * 0.6.0     2010-05-19  sed, PrydeWorX  Initial public release
  * 0.6.1     2010-07-08  sed, PrydeWorX  added options to use own modifiers for the coordinates
  * 0.6.2     2010-07-09  sed, PrydeWorX  added norandom option and made random starting offsets used only when
  *                                       no manual offsets are set
  * 0.7.0     2010-11-09  sed, PrydeWorX  Version bump to new pwxLib release version
  * 0.7.0.1   2011-03-02  sed, PrydeWorX  changed from manual parsing to the usage of pwxArgs
  * 0.7.0.2   2011-03-06  sed, PrydeWorX  Patches for compatibility with Visual C++ 2008
  * 0.7.1     2011-03-26  sed, PrydeWorX  Version bump to new pwxLib release version
  * 0.7.2     2011-04-07  sed, PrydeWorX  Version bump to new pwxLib release version
  * 0.8.0     2011-07-14  sed, PrydeWorX  Version bump to new pwxLib release version
  * 0.8.1     2011-09-30  sed, PrydeWorX  Version bump to new pwxLib release version
  * 0.8.2     2011-10-07  sed, PrydeWorX  Version bump to new pwxLib release version
  * 0.8.3     2011-10-16  sed, PrydeWorX  Version bump to new pwxLib release version
  * 0.8.5     2012-03-01  sed, PrydeWorX  Welcome to 2012. Version bump to new pwxLib release version
  * 0.8.5.1   2012-03-20  sed, PrydeWorX  Fixed a memory leak introduced with version 0.7.0.2
  * 0.8.5.2   2012-03-23  sed, PrydeWorX  Fixed an Effective C++ issue
  * 0.8.6     2012-04-??  sed, PrydeWorX  Version bump to new pwxLib release version
  * 0.9.0     2018-12-19  sed, PrydeWorX  Updated to support the latest pwxLib version and fixed
  *                                       a possible memory leak when writing into an output file.
  @endverbatim
**/

#include <fstream>
#include <pwx_worker_RNG.h>
using pwx::RNG;

#include "main.h"

static int create_output(ENVIRONMENT* env, std::ostream &outStream, bool showProgress);

int main( int argc, char* argv[] ) {
    int32_t result = EXIT_SUCCESS;
    ENVIRONMENT* env = NULL;

    // Set a random seed first:
    RNG.setSeed( RNG.random( 10000, 25000 ) );

    try {
        env = new ENVIRONMENT( RNG.getSeed() );
        result = processArguments( env, argc, argv );
    } catch ( std::bad_alloc& e ) {
        cerr << "ERROR : Unable to create environment!" << endl;
        cerr << "REASON: \"" << e.what() << "\"" << endl;
        env = NULL;
        result = EXIT_FAILURE;
    }

    if ( ( EXIT_SUCCESS == result ) && env && env->doWork ) {
        RNG.setSeed( env->seed );
        if ( env->useSeedOff ) {
            double maxOffset = env->seed ? static_cast<double>( env->seed ) : 1000.0;
            double minOffset = env->seed ? static_cast<double>( env->seed ) * -1.0 : -1000.0;
            env->setOffsets( RNG.random( minOffset, maxOffset ),
                             RNG.random( minOffset, maxOffset ),
                             RNG.random( minOffset, maxOffset ),
                             RNG.random( minOffset, maxOffset ), true );
        }

        if ( env->filename.size() > 0 ) {
            std::ofstream ofs( env->filename.c_str() );

            if ( ofs.is_open() )
                    result = create_output(env, ofs, true);
            else
                cerr << "ERROR: Can't write into " << env->filename << "!" << endl;
        } else
                result = create_output(env, cout, false);
    }

    if ( env )
        delete env;

    return ( result );
}


static int create_output(ENVIRONMENT* env, std::ostream &outStream, bool showProgress) {
        char* xName = nullptr;
        char disp[32];

        for ( int32_t i = 0; i < env->count; ++i ) {
                xName = RNG.rndName( env->offsetX, env->offsetY, env->offsetZ, env->offsetW,
                                     env->maxChars, env->maxSyllables, env->maxParts );
                if ( xName ) {
                        outStream << xName << endl;
                        free ( xName );
                } else {
                        outStream << "Error: No name generated..." << endl;
                        return EXIT_FAILURE;
                }

                if (showProgress && (&outStream != &cout) ) {
                        memset( disp, '\b', strlen( disp ) );
                        cout << disp;
                        snprintf( disp, 31, "%d", i + 1 );
                        cout << disp;
                        cout.flush();
                }

                if ( env->useRandom && !env->useModVals )
                        env->setOffsets( RNG.random( -5.0L, 5.0L ),
                                         RNG.random( -5.0L, 5.0L ),
                                         RNG.random( -5.0L, 5.0L ),
                                         RNG.random( -5.0L, 5.0L ), true );
                        else
                                env->setOffsets();
        }

        return EXIT_SUCCESS;
}
