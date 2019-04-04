#ifndef PhotometricFunction_h
#define PhotometricFunction_h
/**
 * @file
 * $Revision$
 * $Date$
 *
 *   Unless noted otherwise, the portions of Isis written by the USGS are
 *   public domain. See individual third-party library and package descriptions
 *   for intellectual property information, user agreements, and related
 *   information.
 *
 *   Although Isis has been used by the USGS, no warranty, expressed or
 *   implied, is made by the USGS as to the accuracy and functioning of such
 *   software and related material nor shall the fact of distribution
 *   constitute any such warranty, and no responsibility is assumed by the
 *   USGS in connection therewith.
 *
 *   For additional information, launch
 *   $ISISROOT/doc//documents/Disclaimers/Disclaimers.html
 *   in a browser or see the Privacy &amp; Disclaimers page on the Isis website,
 *   http://isis.astrogeology.usgs.gov, and the USGS privacy and disclaimers on
 *   http://www.usgs.gov/privacy.html.
 */

#include "IString.h"
#include "Camera.h"
#include "DbProfile.h"
#include "SpecialPixel.h"

#include <iostream>
#include <sstream>
#include <iomanip>

namespace Isis {

    /** Implement templatized MIN fumnction */
    template<typename T> inline T MIN ( const T &A, const T &B ) {
        if (A < B) {
            return (A);
        }
        else {
            return (B);
        }
    }

    /** Implement templatized MAX function */
    template<typename T> inline T MAX ( const T &A, const T &B ) {
        if (A > B) {
            return (A);
        }
        else {
            return (B);
        }
    }

    class PvlObject;
    class Camera;

    /**
     * @brief An implementation of the PhotometricFunction photometric function
     *
     * This class implements the PhotometricFunction-Buratti-Hill photometric
     * equation as outline in thier paper "Multispectral Photometry
     * of the Moon and Absolute Calibration of the Clementine UV/VIS
     * Camera", published in Icaris v141, pg. 205-255 (1999).
     *
     * @author  2010-02-15 Kris Becker
     *
     * @internal
     */
    class PhotometricFunction {
        public:
            /**
             * @brief Create Hilier photometric object
             *
             */
            PhotometricFunction ( PvlObject &pvl, Cube &cube, bool useCamera);

            //! Destructor
            virtual ~PhotometricFunction () {
            }
            ;

            void setCamera ( Camera *cam ) {
                _camera = cam;
            }

            static QString AlgorithmName ( const PvlObject &pvl ) {
                return pvl.findObject("PhotometricModel").findGroup("Algorithm", Pvl::Traverse).findKeyword("Name")[0];
            }

            virtual double Compute ( const double &line, const double &sample, int band = 1, bool useDem = false);
            virtual double photometry ( double i, double e, double g, int band = 1 ) const = 0;
            virtual void Report ( PvlContainer &pvl ) = 0;

            void SetMinimumIncidenceAngle (double angle) {
                p_minimumIncidenceAngle = angle;
            }
            void SetMaximumIncidenceAngle (double angle) {
                 p_maximumIncidenceAngle = angle;
            }
            void SetMinimumEmissionAngle (double angle) {
                 p_minimumEmissionAngle = angle;
            }
            void SetMaximumEmissionAngle (double angle) {
                 p_maximumEmissionAngle = angle;
            }
            void SetMinimumPhaseAngle (double angle) {
                 p_minimumPhaseAngle = angle;
            }
            void SetMaximumPhaseAngle (double angle) {
                 p_maximumPhaseAngle = angle;
            }

            double MinimumIncidenceAngle () {
                return p_minimumIncidenceAngle;
            }
            double MaximumIncidenceAngle () {
                return p_maximumIncidenceAngle;
            }
            double MinimumEmissionAngle () {
                return p_minimumEmissionAngle;
            }
            double MaximumEmissionAngle () {
                return p_maximumEmissionAngle;
            }
            double MinimumPhaseAngle () {
                return p_minimumPhaseAngle;
            }
            double MaximumPhaseAngle () {
                return p_maximumPhaseAngle;
            }

        protected:

            Camera *_camera;
            double _iRef; //!<  Incidence refernce angle
            double _eRef; //  Emission  reference angle
            double _gRef; //  Phase     reference angle

            double p_minimumIncidenceAngle;
            double p_maximumIncidenceAngle;
            double p_minimumEmissionAngle;
            double p_maximumEmissionAngle;
            double p_minimumPhaseAngle;
            double p_maximumPhaseAngle;

            DbProfile _normProf;

            /**
             * @brief Helper method to initialize parameters
             *
             * This method will check the existance of a keyword and extract the value
             * if it exists to the passed parameter (type).  If it doesn't exist, the
             * default values is returned.
             *
             * @param T Templated variable type
             * @param conf Parameter profile container
             * @param keyname Name of keyword to get a value from
             * @param defval Default value it keyword/value doesn't exist
             * @param index Optional index of the value for keyword arrays
             *
             * @return T Return type
             */
            template<typename T>
            T ConfKey ( const DbProfile &conf, const QString &keyname, const T &defval, int index = 0 ) const {
                if (!conf.exists(keyname)) {
                    return (defval);
                }
                if (conf.count(keyname) < index) {
                    return (defval);
                }
                return conf.value(keyname, index);
            }

    };

}
;

#endif

