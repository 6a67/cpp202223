/*
 *  LevelParser.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: mhillmann, mluetkedreim
 *
 *  Copyright (c) 2017 Thomas Wiemann.
 *  Restricted usage. Licensed for participants of the course "The C++ Programming Language" only.
 *  No unauthorized distribution.
 */

#include "io/ModelIO.hpp"
#include "LevelParser.hpp"
#include "io/TextureFactory.hpp"
#include "io/TriangleMeshFactory.hpp"

using namespace boost::property_tree;

namespace asteroids
{

LevelParser::LevelParser(const std::string& file, SpaceCraft::Ptr& spaceCraft, Skybox::Ptr& sky, AsteroidField::Ptr& af)
{
    // Create empty property tree object
    ptree tree;

    try
    {
        // Parse the XML into the property tree.
        read_xml(file, tree);
    }
    catch (xml_parser_error& xpe)
    {
        std::cerr << "Unable to open file " << file << std::endl;
        return;
    }

    // get path
    const std::string path = GetPathFromFileName(file);

    LevelHdf5IO io;
    io.open(path + tree.get<std::string>("level.<xmlattr>.resources"));
    TextureFactory::instance().setHdf5IO(io);
    TriangleMeshFactory::instance().setHdf5IO(io);

    BOOST_FOREACH(ptree::value_type& v, tree.get_child("level"))
    {
        if (v.first == "skybox")
        {
            string names[6];
            names[0] = v.second.get<std::string>("file1", "error");
            names[1] = v.second.get<std::string>("file2", "error");
            names[2] = v.second.get<std::string>("file3", "error");
            names[3] = v.second.get<std::string>("file4", "error");
            names[4] = v.second.get<std::string>("file5", "error");
            names[5] = v.second.get<std::string>("file6", "error");

            sky = std::make_shared<Skybox>(Skybox(v.second.get<int>("<xmlattr>.width", 1024), names));
        }
        else if (v.first == "asteroids")
        {
            af = std::make_shared<AsteroidField>(AsteroidField(v.second.get<int>("count", 0), 
                v.second.get<std::string>("<xmlattr>.filename", "error"),
                v.second.get<float>("range_max", 2500.0f),
                v.second.get<float>("size_min", 3.0f),
                v.second.get<float>("size_max", 5.0f)
            ));
        }
        else if (v.first == "actor")
        {
            spaceCraft = make_shared<SpaceCraft>(SpaceCraft(v.second.get<std::string>("<xmlattr>.filename", "error"),
                Vector3f(v.second.get<int>("spawn_x", 0),
                    v.second.get<int>("spawn_y", 0),
                    v.second.get<int>("spawn_z", 0)),
                v.second.get<float>("move_speed", 3),
                v.second.get<float>("rotate_speed", 0.05)
            ));
        }
    }
}

} /* namespace asteroids */
