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
    const int num_frames = 264; // Number of frames in the animation
    const double orbit_radius = 5.0;
    const double orbit_speed = 2 * pi / 120; // Complete orbit in every "5" seconds
    const double rotation_speed = 0.1; // Rotation speed for the icosphere
    
    // Scene setup
    hittable_list world;

    // Materials
    auto sphere_material   = make_shared<metal>(color(0.8, 0.8, 0.8),0.0);
    auto icosphere_material = make_shared<dielectric>(1.33);
    

    // Camera setup
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1200;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;
    cam.vfov = 40;
    cam.lookfrom = point3(13, 2, 3);
    cam.lookat = point3(0, 0, 0);
    cam.vup = vec3(0, 1, 0);
    cam.focus_dist = 12.0;
    cam.defocus_angle = 0.5;

    // Add stationary sphere
    world.add(make_shared<sphere>(point3(0, 0, 0), 3.0, sphere_material));
    
    // Random spheres
    for (int a = -5; a < 5; a++) {
        for (int b = -5; b < 5; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), -2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    // Animation loop
    for (int frame = 240; frame < num_frames; ++frame) {
        double theta = orbit_speed * frame;
    
        // Calculate orbit position
        point3 orbit_pos(cos(theta) * orbit_radius, 0, sin(theta) * orbit_radius);

       // Icosphere mesh
        shared_ptr<mesh> icosphere_mesh = make_shared<mesh>("icosphere.obj", icosphere_material);

        // Calculate the transformation matrix for translation only (orbit position)
        Eigen::Matrix4d translation_matrix = Transform::translate(vec3(orbit_pos.x(), orbit_pos.y(), orbit_pos.z()).toEigen()).matrix;
        icosphere_mesh->apply_transform(translation_matrix);

        // Calculate the rotation angle
        double rotation_angle = rotation_speed * frame;
        Eigen::Matrix4d rotation_matrix = Transform::rotateY(rotation_angle).matrix;
        icosphere_mesh->apply_transform(rotation_matrix);

        // Add the transformed icosphere mesh to the world
        world.add(icosphere_mesh);

        // Render the frame
        cam.render(world, frame);

        // Remove dynamic objects from the world
        world.remove(icosphere_mesh);
    }

    return 0;
}
