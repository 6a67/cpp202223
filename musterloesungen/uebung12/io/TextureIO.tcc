

namespace asteroids {

namespace hdf5features {

template<typename Derived>
Bitmap TextureIO<Derived>::load(std::string groupName, std::string datasetName) {
    return load(hdf5util::getGroup(m_fileAccess->m_hdf5_file, groupName, false), datasetName);
}

template<typename Derived>
Bitmap TextureIO<Derived>::load(HighFive::Group group, std::string datasetName) {
    std::vector<size_t> dims;
    shared_array<unsigned char> pixels
            = m_fileAccess->template loadArray<unsigned char>(group, datasetName, dims);

    return Bitmap(pixels, dims[1], dims[0], dims[2]);
}

template<typename Derived>
void TextureIO<Derived>::save(std::string groupName, std::string datasetName, Bitmap* texture) {
    return save(
            hdf5util::getGroup(m_fileAccess->m_hdf5_file, groupName, true), datasetName, texture);
}

template<typename Derived>
void TextureIO<Derived>::save(HighFive::Group group, std::string datasetName, Bitmap* texture) {
    shared_array<unsigned char> data(new unsigned char[texture->getWidth() * texture->getHeight() * texture->getDepth()]);
    for (int i = 0; i < texture->getWidth() * texture->getHeight() * texture->getDepth(); i++)
    {
        data[i] = texture->getPixels()[i];
    }

    // save array
    std::vector<size_t> dims = std::vector<size_t>{static_cast<size_t>(texture->getHeight()),
                                                   static_cast<size_t>(texture->getWidth()),
                                                   static_cast<size_t>(texture->getDepth())};
    std::vector<hsize_t> chunks = std::vector<hsize_t>{dims[0], dims[1], dims[2]};
    m_fileAccess->save(group, datasetName, dims, chunks, data);
}

template<typename Derived>
void TextureIO<Derived>::saveImage(std::string groupName,
                                   std::string datasetName,
                                   const std::string &imageFileName) {
    std::shared_ptr<Bitmap> reader;

    // Get file extension
    if (imageFileName.substr(imageFileName.find_last_of('.') + 1) == "ppm") {
        std::shared_ptr<ReadPPM> read_ppm(new ReadPPM(imageFileName));
        reader = std::static_pointer_cast<Bitmap>(read_ppm);
    } else if (imageFileName.substr(imageFileName.find_last_of('.') + 1) == "tga") {
        std::shared_ptr<ReadTGA> read_tga(new ReadTGA(imageFileName));
        reader = std::static_pointer_cast<Bitmap>(read_tga);
    } else if (imageFileName.substr(imageFileName.find_last_of('.') + 1) == "jpg") {
        std::shared_ptr<ReadJPG> read_jpg(new ReadJPG(imageFileName));
        reader = std::static_pointer_cast<Bitmap>(read_jpg);
    }

    if (reader) {
        save(groupName, datasetName, reader.get());
    } else {
        cout << "TextureIO: Unable to read file " << imageFileName << endl;
    }
}

} // namespace hdf5features

} // namespace asteroids
