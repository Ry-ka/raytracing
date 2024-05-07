// POV-Ray Scene Description
#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"
#include "finish.inc"

// Camera setup
camera {
    location <13, 2, 3>
    look_at <0, 0, 0>
    angle 40
}

// Lighting
light_source {
    <150, 100, -100>
    color White
}

// Global settings
global_settings {
    ambient_light rgb <0.1, 0.1, 0.1>
    assumed_gamma 1.0
}

// Materials definition
#declare Metal = texture {
    pigment { color rgb <0.8, 0.8, 0.8> }
    finish { 
      reflection 0.9 
      specular 0.5 
    }
}

#declare Glass = texture {
    pigment { color rgbt <1, 1, 1, 0.95> }
    finish {
        reflection 0.1
        refraction 1.33
    }
}

// Static central sphere
sphere {
    <0, 0, 0>, 3
    texture { Metal }
}


// Hardcoded scattered spheres
sphere {
    <-5, -1, -4>, 0.2
    texture { pigment { color Red } }
}
sphere {
    <4, -1, 5>, 0.2
    texture { pigment { color Green } }
}
sphere {
    <5, -1, 2>, 0.2
    texture { pigment { color Blue } }
}
sphere {
    <4, -1, 1>, 0.2
    texture { pigment { color Yellow } }
}
sphere {
    <-6, -1, 3>, 0.2
    texture { pigment { color Cyan } }
}

// Animation setup
#declare Start_Clock = 0;
#declare End_Clock = 1;
#declare Frame = int(clock * 240);  // This maps clock from 0 to 1 to frames from 0 to 240

#declare Theta = 2*pi*Frame/120;
#declare Orbit_Pos = <cos(Theta) * 5, 0, sin(Theta) * 5>;

// Animate a sphere along an orbit
sphere {
    Orbit_Pos, 1
    texture { Glass }
}

