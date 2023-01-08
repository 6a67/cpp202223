#ifndef TRIANGLEMESHFACTORY_HPP
#define TRIANGLEMESHFACTORY_HPP

#include <string>
#include <map>
#include "rendering/TriangleMesh.hpp"

namespace asteroids
{

class TriangleMeshFactory
{
public:
    /**
     * @brief   Get the singleton instance of the factory
     *
     * @return  The instance
     */
    static TriangleMeshFactory& getInstance()
    {
        static TriangleMeshFactory instance;
        return instance;
    }

    /**
     * @brief   Set the base path in which meshes are searched
     *
     * @param   base    The base path
     */
    void setBasePath(const string& base) noexcept(false);

    /**
     * @brief   Get a mesh by its filename
     *
     * @param   filename    The filename
     * @return  The mesh
     */
    TriangleMesh* getMesh(const string& filename) const noexcept(false);

    /**
     * @brief   Destructor
     */
    ~TriangleMeshFactory();

private:
    // Overload functions and make then private to prevent usage of them outside of the class
    TriangleMeshFactory() {}
    TriangleMeshFactory(const TriangleMeshFactory&);
    TriangleMeshFactory& operator=(const TriangleMeshFactory&);

    std::string                          m_basePath;
    // std::map<std::string, TriangleMesh*> m_meshes;
};

}  // namespace asteroids


#endif  // TRIANGLEMESHFACTORY_HPP