#include "io/Read3DS.hpp"
#include "io/ReadPLY.hpp"
#include "io/ReadOBJ.hpp"
#include "io/TextureFactory.hpp"

namespace asteroids
{

namespace hdf5features
{

template<typename Derived>
template<typename Mesh>
Mesh ModelIO<Derived>::load(std::string groupName, std::string datasetName)
{
    return load < Mesh > (
            hdf5util::getGroup(m_fileAccess->m_hdf5_file, groupName + "/" + datasetName, false));
}

template<typename Derived>
template<typename Mesh>
Mesh ModelIO<Derived>::load(HighFive::Group group)
{
    Mesh mesh;
    std::vector<size_t> dims;
    shared_array<float> data = m_fileAccess->template loadArray<float>(group, "vertices", dims);
    mesh.setVertexBuffer(data, dims[0]);

    data = m_fileAccess->template loadArray<float>(group, "normals", dims);
    mesh.setNormalBuffer(data);

    shared_array<int> dataFaces = m_fileAccess->template loadArray<int>(group, "faces", dims);
    mesh.setIndexBuffer(dataFaces, dims[0]);

    data = m_fileAccess->template loadArray<float>(group, "textureCoords", dims);
    mesh.setTextureBuffer(data);

    auto materialsAttr = group.getAttribute("materials");
    std::string materialLocation;
    materialsAttr.read(materialLocation);
    auto materialGroup = hdf5util::getGroup(m_fileAccess->m_hdf5_file, materialLocation, false);
    auto materials = materialGroup.listObjectNames();

    // sort materials according to their index, otherwise they get added to the texture in the wrong order
    // and the faces references the wrong materials
    std::sort(materials.begin(), materials.end(), [](const std::string& a, const std::string& b)
    {
        return std::stoi(a) < std::stoi(b);
    });

    std::vector<float> color;
    for (auto material: materials)
    {
        Material::Ptr mat(new Material);
        auto materialGroupIndex = hdf5util::getGroup(m_fileAccess->m_hdf5_file, materialLocation + "/" + material,
                                                     false);
        auto materialAttr = materialGroupIndex.getAttribute("ambient");
        materialAttr.read(color);
        mat->m_ambient.r = color[0];
        mat->m_ambient.g = color[1];
        mat->m_ambient.b = color[2];

        materialAttr = materialGroupIndex.getAttribute("diffuse");
        materialAttr.read(color);
        mat->m_diffuse.r = color[0];
        mat->m_diffuse.g = color[1];
        mat->m_diffuse.b = color[2];

        materialAttr = materialGroupIndex.getAttribute("specular");
        materialAttr.read(color);
        mat->m_specular.r = color[0];
        mat->m_specular.g = color[1];
        mat->m_specular.b = color[2];

        materialAttr = materialGroupIndex.getAttribute("shininess");
        materialAttr.read(mat->m_shininess);

        if (materialGroupIndex.hasAttribute("texture"))
        {
            materialAttr = materialGroupIndex.getAttribute("texture");
            std::string texture;
            materialAttr.read(texture);
            mat->m_texture = TextureFactory::instance().getTexture(texture);
        }
        else
        {
            mat->m_texture = nullptr;
        }

        mesh.addMaterial(mat);

        auto materialFaces = materialGroupIndex.listObjectNames();
        for (auto materialFace: materialFaces)
        {
            MaterialFaceList::Ptr matFaceList(new MaterialFaceList);
            shared_array<int> faces = m_fileAccess->template loadArray<int>(materialGroupIndex, materialFace, dims);
            matFaceList->m_matIndex = std::stoi(material);
            for (size_t i = 0; i < dims[0]; i++)
            {
                matFaceList->m_faces.push_back(faces[i]);
            }
            mesh.addMaterialFaceList(matFaceList);
        }
    }

    return mesh;
}

template<typename Derived>
void ModelIO<Derived>::save(std::string groupName,
                            std::string datasetName,
                            TexturedMesh* mesh)
{
    save(hdf5util::getGroup(m_fileAccess->m_hdf5_file, groupName + "/" + datasetName, true), datasetName, mesh);
}

template<typename Derived>
void ModelIO<Derived>::save(HighFive::Group group,
                            std::string datasetName,
                            TexturedMesh* mesh)
{
    shared_array<float> data(new float[mesh->getNumVertices() * 3]);

    for (int i = 0; i < 3 * mesh->getNumVertices(); i++)
    {
        data[i] = mesh->getVertexBuffer()[i];
    }
    std::vector<size_t> dims = std::vector<size_t>{(size_t) mesh->getNumVertices(), 3};
    std::vector<hsize_t> chunks = std::vector<hsize_t>{(size_t) dims[0], (size_t) dims[1]};
    m_fileAccess->save(group, "vertices", dims, chunks, data);

    for (int i = 0; i < 3 * mesh->getNumVertices(); i++)
    {
        data[i] = mesh->getNormalBuffer()[i];
    }
    m_fileAccess->save(group, "normals", dims, chunks, data);

    shared_array<int> dataFaces(new int[mesh->getNumFaces() * 3]);
    for (int i = 0; i < 3 * mesh->getNumFaces(); i++)
    {
        dataFaces[i] = mesh->getIndexBuffer()[i];
    }
    dims = std::vector<size_t>{(size_t) mesh->getNumFaces(), 3};
    chunks = std::vector<hsize_t>{(size_t) dims[0], (size_t) dims[1]};
    m_fileAccess->save(group, "faces", dims, chunks, dataFaces);

    shared_array<float> dataTexCoords(new float[mesh->getNumVertices() * 2]);
    for (int i = 0; i < 2 * mesh->getNumVertices(); i++)
    {
        dataTexCoords[i] = mesh->getTextureCoords()[i];
    }
    dims = std::vector<size_t>{(size_t) mesh->getNumVertices(), 2};
    chunks = std::vector<hsize_t>{(size_t) dims[0], (size_t) dims[1]};
    m_fileAccess->save(group, "textureCoords", dims, chunks, dataTexCoords);

    std::string materialGroupName = "materials/" + datasetName;
    auto materialGroup = hdf5util::getGroup(m_fileAccess->m_hdf5_file, materialGroupName, true);
    hdf5util::setAttribute(group, "materials", materialGroupName);
    materialGroupName += "/";

    std::vector<float> color;
    color.resize(3);
    auto materials = mesh->getMaterials();
    for (int i = 0; i < materials.size(); i++)
    {
        auto materialGroupIndex = hdf5util::getGroup(m_fileAccess->m_hdf5_file, materialGroupName + std::to_string(i),
                                                     true);
        color[0] = materials[i]->m_ambient.r;
        color[1] = materials[i]->m_ambient.g;
        color[2] = materials[i]->m_ambient.b;
        materialGroupIndex.createAttribute("ambient", color);

        color[0] = materials[i]->m_diffuse.r;
        color[1] = materials[i]->m_diffuse.g;
        color[2] = materials[i]->m_diffuse.b;
        materialGroupIndex.createAttribute("diffuse", color);

        color[0] = materials[i]->m_specular.r;
        color[1] = materials[i]->m_specular.g;
        color[2] = materials[i]->m_specular.b;
        materialGroupIndex.createAttribute("specular", color);

        hdf5util::setAttribute(materialGroupIndex, "shininess", materials[i]->m_shininess);
        if (materials[i]->m_texture)
        {
            std::string textureName = materials[i]->m_texture->getName();
            hdf5util::setAttribute(materialGroupIndex, "texture", textureName);
        }
    }

    int i = 0;
    auto materialFaces = mesh->getMatFaceLists();
    for (const auto& materialFace: materialFaces)
    {
        shared_array<int> faces(new int[materialFace->m_faces.size()]);
        auto materialGroupIndex = hdf5util::getGroup(m_fileAccess->m_hdf5_file,
                                                     materialGroupName + std::to_string(materialFace->m_matIndex),
                                                     true);
        int j = 0;
        for (auto face: materialFace->m_faces)
        {
            faces[j++] = face;
        }
        dims = std::vector<size_t>{(size_t) materialFace->m_faces.size()};
        chunks = std::vector<hsize_t>{(size_t) dims[0]};
        m_fileAccess->save(materialGroupIndex, "faces" + std::to_string(i++), dims, chunks, faces);
    }
}

template<typename Derived>
void ModelIO<Derived>::saveMesh(std::string groupName, std::string datasetName, const string& meshFileName)
{
    MeshReader* io = nullptr;

    // Get file extension
    if (meshFileName.substr(meshFileName.find_last_of('.') + 1) == "ply")
    {
        io = new ReadPLY(meshFileName);
    }
    else if (meshFileName.substr(meshFileName.find_last_of('.') + 1) == "3ds")
    {
        io = new Read3DS(meshFileName);
    }
    else if (meshFileName.substr(meshFileName.find_last_of('.') + 1) == "obj")
    {
        io = new ReadOBJ(meshFileName);
    }

    // Get mesh from io
    if (io)
    {
        TexturedMesh::Ptr mesh = std::static_pointer_cast<TexturedMesh>(io->getMesh());
        save(groupName, datasetName, mesh.get());
    }
    else
    {
        cout << "Unable to parse file " << meshFileName << "." << endl;
    }
    delete io;
}
} // namespace hdf5features

} // namespace asteroids
