/*
 *  LevelParser.hpp
 *
 *  Created on: Jan 10, 2018
 *      Author: mhillmann, mluetkedreim
 *
 *  Copyright (c) 2017 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#ifndef SRC_LEVELPARSER_HPP_
#define SRC_LEVELPARSER_HPP_

#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

#include "rendering/SpaceCraft.hpp"
#include "rendering/Skybox.hpp"
#include "util/AsteroidField.hpp"
#include "util/Util.hpp"
#include "io/BaseHdf5IO.hpp"

namespace asteroids
{

class LevelParser
{
public:
    
     ///////////////////////////////////////////////////////////////////
    /// TODO: Typedef IO reader object
    ///////////////////////////////////////////////////////////////////

    /**
     * A Parser that reads the given XML configuration file
     * given by the parameter file. It generates all known
     * elements and adds them to the given Level.
     * 
     * @param file the filename of the XML file
     * @param actor the Actorpointer
     * @param sky the Skyboxpointer
     * @param af the AsteroidFieldpointer
     */
    LevelParser(const std::string& file, SpaceCraft::Ptr& actor, Skybox::Ptr& sky, AsteroidField::Ptr& af);
};

} /* namespace asteriods */

#endif /* SRC_LEVELPARSER_HPP_ */
