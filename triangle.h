#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"
#include "interval.h"
#include "ray.h"
#include "rtweekend.h"

class triangle : public hittable {
public:
    point3 vertices[3];
    shared_ptr<material> mat_ptr;

    triangle() {}
    triangle(point3 v0, point3 v1, point3 v2, shared_ptr<material> m)
        : vertices{v0, v1, v2}, mat_ptr(m) {}

    virtual bool hit(const ray& r, interval t_range, hit_record& rec) const override {
      const vec3& origin = r.origin();
      const vec3& direction = r.direction();

      vec3 edge1 = vertices[1] - vertices[0];
      vec3 edge2 = vertices[2] - vertices[0];
      vec3 h = cross(direction, edge2);
      double a = dot(edge1, h);

      if (fabs(a) < 1e-8) return false; // Parallel ray

      double f = 1.0 / a;
      vec3 s = origin - vertices[0];
      double u = f * dot(s, h);
      if (u < 0.0 || u > 1.0) return false;

      vec3 q = cross(s, edge1);
      double v = f * dot(direction, q);
      if (v < 0.0 || u + v > 1.0) return false;

      double t = f * dot(edge2, q);
      if (t_range.contains(t)) {
        rec.t = t;
        rec.p = r.at(t);
        vec3 outward_normal = unit_vector(cross(edge1, edge2)); // Normalize the normal vector
        set_face_normal(r, outward_normal, rec); // Set the correct normal
        rec.mat = mat_ptr;
        return true;
      }

      return false;
  }


    virtual void set_face_normal(const ray& r, const vec3& outward_normal, hit_record& rec) const {
    // Calculate whether the ray hits the front or the back of the surface
    rec.front_face = dot(r.direction(), outward_normal) < 0;
    rec.normal = rec.front_face ? outward_normal : -outward_normal;
  }

};

#endif // TRIANGLE_H
