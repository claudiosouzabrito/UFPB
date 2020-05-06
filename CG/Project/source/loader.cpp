#include "loader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp" //biblioteca para as
#include <fstream>
#include <sstream>

#include <iterator>
//-----------------------------------------------------------------------------
// Funções referentes a carregar um obj.

static void splitString(std::string t_string, const char t_delimiter, std::vector<std::string> &t_vector)
{

    std::string temp = "";
    for (char &c : t_string)
    {
        if (c != t_delimiter)
        {
            temp.insert(temp.end(), c);
        }
        else
        {
            if (!temp.empty())
            {
                t_vector.push_back(temp);
            }
            temp = "";
        }
    }

    if (!temp.empty())
    {
        t_vector.push_back(temp);
    }
}

static void processVertex(std::vector<unsigned int> &t_indices_vector, std::vector<float> &t_vertices_vector,
                          std::vector<float> &t_normals_vector, std::vector<float> &t_texture_vector,
                          std::vector<std::string> &t_vertex_str, std::vector<glm::vec2> &t_temp_texture,
                          std::vector<glm::vec3> &t_temp_normals, std::vector<glm::vec3> &t_temp_vertices, int *index_cout)
{

    // Push vertex refered by the index
    t_vertices_vector.push_back(t_temp_vertices[std::stoi(t_vertex_str[0]) - 1].x);
    t_vertices_vector.push_back(t_temp_vertices[std::stoi(t_vertex_str[0]) - 1].y);
    t_vertices_vector.push_back(t_temp_vertices[std::stoi(t_vertex_str[0]) - 1].z);

    // Push texture coords refered by the index
    t_texture_vector.push_back(t_temp_texture[std::stoi(t_vertex_str[1]) - 1].x);
    t_texture_vector.push_back(t_temp_texture[std::stoi(t_vertex_str[1]) - 1].y);

    // Push normals refered by the index
    t_normals_vector.push_back(t_temp_normals[std::stoi(t_vertex_str[2]) - 1].x);
    t_normals_vector.push_back(t_temp_normals[std::stoi(t_vertex_str[2]) - 1].y);
    t_normals_vector.push_back(t_temp_normals[std::stoi(t_vertex_str[2]) - 1].z);

    // Push the index in order
    for (int v = 0; v < 3; v++)
    {
        t_indices_vector.push_back(*index_cout);
        (*index_cout)++;
    }
}

bool loadOBJ(const char *t_file, std::vector<float> &t_vertices_vector,
             std::vector<float> &t_texture_vector, std::vector<float> &t_normals_vector,
             std::vector<unsigned int> &t_indices_vector)
{

    std::ifstream file_stream(t_file, std::ios::in);

    // ve se o qervio existe
    if (!file_stream.is_open())
    {

        std::cerr << "Could not read  file " << t_file << " File does not exist" << std::endl;
        return false;
    }

    // Initialize temporary variables
    std::string line = "";

    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_texture;
    std::vector<glm::vec3> temp_normals;

    std::vector<int> uv_indices;
    std::vector<int> normal_indices;

    int index_count = 0;

    while (1)
    {

        std::getline(file_stream, line);

        // Check if file is empty
        if (line.empty())
        {
            break;
        }

        // Split line by white space
        std::istringstream iss(line);
        std::vector<std::string> result{std::istream_iterator<std::string>(iss), {}};

        // Identify line by the first element
        if (result[0].compare("v") == 0)
        {

            temp_vertices.push_back(glm::vec3(std::strtof(result[1].c_str(), 0), std::strtof(result[2].c_str(), 0), std::strtof(result[3].c_str(), 0)));
        }
        else if (result[0].compare("vt") == 0)
        {

            temp_texture.push_back(glm::vec2(std::strtof(result[1].c_str(), 0), std::strtof(result[2].c_str(), 0)));
        }
        else if (result[0].compare("vn") == 0)
        {

            temp_normals.push_back(glm::vec3(std::strtof(result[1].c_str(), 0), std::strtof(result[2].c_str(), 0), std::strtof(result[3].c_str(), 0)));
        }
        else if (result[0].compare("f") == 0)
        {

            std::vector<std::string> first_vertex;

            splitString(result[1], '/', first_vertex);

            processVertex(t_indices_vector, t_vertices_vector, t_normals_vector, t_texture_vector, first_vertex, temp_texture, temp_normals, temp_vertices, &index_count);

            std::vector<std::string> second_vertex;

            splitString(result[2], '/', second_vertex);

            processVertex(t_indices_vector, t_vertices_vector, t_normals_vector, t_texture_vector, second_vertex, temp_texture, temp_normals, temp_vertices, &index_count);

            std::vector<std::string> third_vertex;

            splitString(result[3], '/', third_vertex);

            processVertex(t_indices_vector, t_vertices_vector, t_normals_vector, t_texture_vector, third_vertex, temp_texture, temp_normals, temp_vertices, &index_count);
        }
    }
    file_stream.close();
    return true;
}

Model Loader::loadVAO(const std::vector<float> &position, const std::vector<unsigned int> &indices, const std::vector<float> &textureCoords, const std::vector<float> &normalVector)
{
    // Create VAO
    unsigned int vaoId = createVAO();
    bindIndicesBuffer(indices);
    // Store model positionitions on VAO 0
    storeDataInAttributeList(0, 3, position);
    storeDataInAttributeList(1, 2, textureCoords);
    storeDataInAttributeList(2, 3, normalVector);
    // Unbind
    unbindVAO();
    // Return RawModel

    return Model(vaoId, indices.size());
}

Player Loader::loadVAOPlayer(const std::vector<float> &position, const std::vector<unsigned int> &indices, const std::vector<float> &textureCoords, const std::vector<float> &normalVector)
{
    // Create VAO
    unsigned int vaoId = createVAO();
    bindIndicesBuffer(indices);
    // Store model positionitions on VAO 0
    storeDataInAttributeList(0, 3, position);
    storeDataInAttributeList(1, 2, textureCoords);
    storeDataInAttributeList(2, 3, normalVector);
    // Unbind
    unbindVAO();
    // Return RawModel

    return Player(vaoId, indices.size());
}

unsigned int Loader::createVAO()
{

    unsigned int vaoId;
    // Create one Vertex Array (VAO) and keep address
    glGenVertexArrays(1, &vaoId);
    // Add VAO to vectorz
    vaos.push_back(vaoId);
    // Bind VAO
    glBindVertexArray(vaoId);
    return vaoId;
}

void Loader::storeDataInAttributeList(const unsigned int attributeNumber, const unsigned int size, const std::vector<float> &data)
{
    unsigned int vboID;
    // Generate buffer object of size 1 and store it in vboID
    glGenBuffers(1, &vboID);
    // Add VBO to vector
    vbos.push_back(vboID);
    // Bind the Buffer
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    // Put the data on the buffer, the data will be modified once and will be used many times with GL drawing commands
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, size, GL_FLOAT, false, 0, 0);
    // Unbind Buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
    // Unbind the Vertex Array
    glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(std::vector<unsigned int> indices)
{

    unsigned int vboID;
    // Generate buffer object of size 1 and store it in vboID
    glGenBuffers(1, &vboID);
    // Add VBO to vector
    vbos.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    // Put the data on the buffer, the data will be modified once and will be used many times with GL drawing commands
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices.at(0)), indices.data(), GL_STATIC_DRAW);
}

// função para carregar texturas "container.jpg"
unsigned int Loader::loadTexture(const std::string fileName)
{
    unsigned int textureId;
    int width, height, nrChannels;

    glGenTextures(1, &textureId);            //recebe qtd de texturas como entrada e armazena em texture;
    glBindTexture(GL_TEXTURE_2D, textureId); //gera textura

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    unsigned char *image = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);

    return textureId;
}

//funcao p/ carregar obj
Model Loader::loadObj(const char *t_file)
{
    //carrega os vetores do obj
    std::vector<float> vertices_vector;
    std::vector<float> texture_vector;
    std::vector<float> normals_vector;
    std::vector<unsigned int> indices_vector;
    loadOBJ(t_file, vertices_vector, texture_vector, normals_vector, indices_vector);

    return loadVAO(vertices_vector, indices_vector, texture_vector, normals_vector);
}

Player Loader::loadObjPlayer(const char *t_file)
{
    //carrega os vetores do obj
    std::vector<float> vertices_vector;
    std::vector<float> texture_vector;
    std::vector<float> normals_vector;
    std::vector<unsigned int> indices_vector;
    loadOBJ(t_file, vertices_vector, texture_vector, normals_vector, indices_vector);

    return loadVAOPlayer(vertices_vector, indices_vector, texture_vector, normals_vector);
}
