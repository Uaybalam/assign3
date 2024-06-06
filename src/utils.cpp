#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "tiny_obj_loader.h"

bool loadOBJ(const std::string& filename) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str());

    if (!ret) {
        std::cerr << "Failed to load/parse .obj file: " << filename << "\n";
        std::cerr << warn << err << std::endl;
        return false;
    }
    return true;
}

void renderOBJ(const std::string& filename) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str());

    if (!ret) return;

    for (const auto& shape : shapes) {
        glBegin(GL_TRIANGLES);
        for (const auto& index : shape.mesh.indices) {
            glVertex3f(attrib.vertices[3 * index.vertex_index + 0],
                       attrib.vertices[3 * index.vertex_index + 1],
                       attrib.vertices[3 * index.vertex_index + 2]);
        }
        glEnd();
    }
}

void saveScreenshot(const std::string& filename) {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    std::vector<unsigned char> buffer(3 * width * height);

    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    std::ofstream out(filename, std::ios::binary);
    if (out.is_open()) {
        out << "P6\n" << width << " " << height << "\n255\n";
        out.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
        out.close();
    } else {
        std::cerr << "Failed to save screenshot!" << std::endl;
    }
}
