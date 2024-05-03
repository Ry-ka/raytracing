#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "mesh.h"
#include "sphere.h"
#include "vec3.h"
#include "transform.h" 
#include <memory>
#include <cmath>

int main() {
    using namespace std;

    // Constants for the animation
    const int num_frames = 2; // Number of frames in the animation
    const double orbit_radius = 5.0;
    const double orbit_speed = 2 * pi / 120; // Complete orbit in every "5" seconds
    
    // Scene setup
    hittable_list world;

    // Materials
    auto sphere_material   = make_shared<metal>(color(0.8, 0.8, 0.8),0.0);
    auto icosphere_material = make_shared<metal>(color(0.8, 0.8, 0.8),0.0);

    // Camera setup
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.vfov = 40;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);
    cam.focus_dist = 10.0;
    cam.defocus_angle = 0;

    // Animation loop
    for (int frame = 0; frame < num_frames; ++frame) {
        double theta = orbit_speed * frame;
    
        // Calculate orbit position
        point3 orbit_pos(cos(theta) * orbit_radius, 0, sin(theta) * orbit_radius);

        // Reset world and add stationary sphere
        world.clear();
        world.add(make_shared<sphere>(point3(0, 0, 0), 3.0, sphere_material));

       // Icosphere mesh
        shared_ptr<mesh> icosphere_mesh = make_shared<mesh>("icosphere.obj", icosphere_material);

        // Calculate the transformation matrix
        Eigen::Matrix4d translation_matrix = Transform::translate(vec3(orbit_pos.x(), orbit_pos.y(), orbit_pos.z()).toEigen()).matrix;
        icosphere_mesh->apply_transform(translation_matrix);
        Eigen::Matrix4d translation_matrix2 = Transform::rotateX(theta).matrix;
        icosphere_mesh->apply_transform(translation_matrix2);

        // Add the transformed icosphere mesh to the world
        world.add(icosphere_mesh);

        // Render the frame
        cam.render(world, frame);
    }

    return 0;
}

