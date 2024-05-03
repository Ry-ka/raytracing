#ifndef MESH_H
#define MESH_H

#include "hittable_list.h"
#include "triangle.h"
#include "transform.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class mesh : public hittable {
public:
    std::vector<point3> vertices;  // Stores the vertices of the mesh
    hittable_list triangles;
    shared_ptr<material> material_ptr;
    std::vector<int> indices;

    mesh() {}
    mesh(const std::string& filename, shared_ptr<material> m) : material_ptr(m) {
        load_from_obj(filename); // Function to load mesh from OBJ file
    }

    void load_from_obj(const std::string& filename) {
        // Load the mesh data from an OBJ file
        std::ifstream file(filename);
        std::string line;
        while (getline(file, line)) {
            std::istringstream iss(line);
            char trash;
            if (line.substr(0, 2) == "v ") {
                iss >> trash;
                double x, y, z;
                iss >> x >> y >> z;
                vertices.push_back(point3(x, y, z));
            } else if (line.substr(0, 2) == "f ") {
                int f[3];
                iss >> trash;
                for (int i = 0; i < 3; i++) {
                    iss >> f[i];
                    indices.push_back(f[i] - 1);
                    f[i]--;  // Convert from 1-based to 0-based index
                }
                triangles.add(make_shared<triangle>(
                    vertices[f[0]],
                    vertices[f[1]],
                    vertices[f[2]], material_ptr));
            }
        }
    }

    void apply_transform(const Eigen::Matrix4d& transform) {

        for (auto& vertex : vertices) {
            Eigen::Vector4d v(vertex.x(), vertex.y(), vertex.z(), 1);
            v = transform * v;
            vertex = point3(v[0], v[1], v[2]);  // Update the vertex
        }


        // Need to also rebuild triangles if their vertices changed
        rebuild_triangles();
    }

    void rebuild_triangles() {
        
        triangles.clear();
        for (size_t i = 0; i < indices.size(); i += 3) {
            triangles.add(make_shared<triangle>(
                vertices[indices[i]],
                vertices[indices[i+1]],
                vertices[indices[i+2]], material_ptr));
        }
    }

    virtual bool hit(const ray& r, interval t_range, hit_record& rec) const override {
        return triangles.hit(r, t_range, rec);
    }
};

#endif // MESH_H
