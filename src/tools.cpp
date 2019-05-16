/** @file tools.cpp
 * 
 * This file is part of getRandomName
 *
 * (c) 2007 - 2019 PrydeWorX
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


#include "tools.h"

#include <PAH>
#include <PStreamHelpers>

using pwx::CAdjRight;
using pwx::PAH;
using pwx::to_string;

int32_t processArguments( ENVIRONMENT* env, int argc, char* argv[] ) {
    int32_t result     = EXIT_SUCCESS;
    bool    doShowHelp = false;
    bool    doShowVers = false;
    assert( env );
    setGlobalEnv( env );

    // The arguments for the coordinates and the modificators have a combined help text
    // Therefore they neither have a description, nor a component name.
    PAH.addArg( "-x", "",     envCallback, nullptr, nullptr );
    PAH.addArg( "-y", "",     envCallback, nullptr, nullptr );
    PAH.addArg( "-z", "",     envCallback, nullptr, nullptr );
    PAH.addArg( "-w", "",     envCallback, nullptr, nullptr );
    PAH.addArg( "", "--modx", envCallback, nullptr, nullptr );
    PAH.addArg( "", "--mody", envCallback, nullptr, nullptr );
    PAH.addArg( "", "--modz", envCallback, nullptr, nullptr );
    PAH.addArg( "", "--modw", envCallback, nullptr, nullptr );

    // The rest of the arguments are set up normally
    PAH.addArg( "-c",    "--count",    pwx::ATT_SET,  &env->count,
                "Generate <count> names",                                     "count" );
    PAH.addArg( "-C", "--chars",    pwx::ATT_SET,  &env->maxChars,
                "Set maximum characters to generate.",                        "value" );
    PAH.addArg( "-h",    "--help",     pwx::ATT_TRUE, &doShowHelp,
                "Show this help and exit",                                    nullptr );
    PAH.addArg( "-n",    "--norandom", pwx::ATT_TRUE, &env->useRandom,
                "Increase coordinates by 1 instead of random modifiers. (*)", nullptr );
    PAH.addArg( "-o",    "--out",      pwx::ATT_SET,  &env->filename,
                "Write generated name(s) into <file>.",                       "filename" );
    PAH.addArg( "-P", "--parts",    pwx::ATT_SET,  &env->maxParts,
                "Set maximum parts to generate.",                             "value" );
    PAH.addArg( "-s",    "--seed",     pwx::ATT_SET,  &env->seed,
                "Set the seed to <value>.",                                   "value" );
    PAH.addArg( "-S", "--sylls",    pwx::ATT_SET,  &env->maxSyllables,
                "Set maximum syllables to generate.",                         "value" );
    PAH.addArg( "-v",    "--version",  pwx::ATT_TRUE, &doShowVers,
                "Show program version and exit",                              nullptr );

    // Load arguments and check for errors:
    PAH.parseArgs( argc, argv );

    size_t errC = PAH.getErrorCount();
    if ( errC ) {
        int32_t errSize = to_string( errC ).size();
        doShowHelp = true;
        result     = EXIT_FAILURE;

        cerr << errC << " errors occurred:" << endl;
        for ( size_t i = 0 ; i < errC ; ++i )
            cerr << CAdjRight( errSize, 0 ) << i + 1 << ": " << PAH.getError( i ) << endl;
    }

    // Opt out via help or version display?
    if ( doShowHelp ) {
        showHelp( env );
        env->doWork = false;
    } else if ( doShowVers ) {
        showVersion( env );
        env->doWork = false;
    }

    // clean up arguments:
    PAH.clearArgs();

    return ( result );
}

void showHelp( ENVIRONMENT* env ) {
    cout << "getRandomName - ";
    showVersion( env );
    cout << "----------------";
    showVerDash( env );
    cout << endl << endl;
    cout << "  Usage:" << endl;
    cout << "getrn [options]" << endl << endl;
    cout << "The default behavior, when no options are given, is to write" << endl;
    cout << "one random name with 1-3 parts, 2-5 syllables and  6-15" << endl;
    cout << "characters to stdout." << endl << endl;
    cout << "  Options:" << endl;
    cout << "  -x,y,z,w      <value>    set value for the x,y,z or w coordinate. If" << endl;
    cout << "                           no offset is set, the program uses random ones" << endl;
    cout << PAH.getHelpStr( "-c", 60, 2 ) << endl;
    cout << PAH.getHelpStr( "-C", 60, 2 ) << endl;
    cout << PAH.getHelpStr( "-h", 60, 2 ) << endl;
    cout << "    --mod<xyzw> <value>    set modifier for x, y, z or w coordinate" << endl;
    cout << "                           instead of using random ones (*)" << endl;
    cout << PAH.getHelpStr( "-n", 60, 2 ) << endl;
    cout << PAH.getHelpStr( "-o", 60, 2 ) << endl;
    cout << PAH.getHelpStr( "-P", 60, 2 ) << endl;
    cout << PAH.getHelpStr( "-S", 60, 2 ) << endl;
    cout << PAH.getHelpStr( "-s", 60, 2 ) << endl;
    cout << PAH.getHelpStr( "-v", 60, 2 ) << endl;
    cout << endl << "(*) : Note on mod* and norandom:" << endl;
    cout << "      If you set at least one modifier, no random values will be used," << endl;
    cout << "      but the value(s) you set, and 0.0 for all you omit. The norandom" << endl;
    cout << "      option is only taken into account if you do not set any modifier" << endl;
    cout << "      and sets all four to 1.0." << endl;
}

void showVersion( ENVIRONMENT* env ) {
    cout << "Version " << env->getVersion() << endl;
}

void showVerDash( ENVIRONMENT* env ) {
    int32_t length = 8 + strlen( env->getVersion() );
    for ( int32_t i = 0; i < length; ++i )
        cout << "-";
}
