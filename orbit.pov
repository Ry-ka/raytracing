// POV-Ray Scene Description
#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"
#include "finish.inc"

// Camera setup
camera {
    location <13, 2, -3>
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
    finish { reflection 0.0 }
}

#declare Glass = texture {
    pigment { color rgbt <1, 1, 1, 0.95> }
    finish {
        reflection 0.1
        refraction 1.33
    }
}

#declare Diffuse = texture {
    pigment { color rgb <rand(), rand(), rand()> }
}

// Static central sphere
sphere {
    <0, 0, 0>, 3
    texture { Metal }
}

// Randomly placed spheres
#declare I = -5;
#while (I < 5)
    #declare J = -5;
    #while (J < 5)
        #if ((I*I + J*J) > 0.81)
            sphere {
                <I+0.9*rand(), -2, J+0.9*rand()>, 0.2
                texture {
                    case(rand(3))
                        Glass
                    case(2)
                        Metal
                    else
                        Diffuse
                    endcase
                }
            }
        #end
        #declare J = J + 1;
    #end
    #declare I = I + 1;
#end

// Animation setup
#declare Start_Frame = 0;
#declare End_Frame = 240;
#declare Frame = Start_Frame;

#while (Frame <= End_Frame)
    #declare Theta = 2*pi*Frame/120;
    #declare Orbit_Pos = <cos(Theta) * 5, 0, sin(Theta) * 5>;

    // Animate a sphere along an orbit
    sphere {
        Orbit_Pos, 1
        texture { Glass }
        rotate <0, Frame * 0.1, 0>
    }

    // Output each frame to a file
    #declare Filename = concat("C:\\Users\\ryan1\\Desktop\\frames\\", str(Frame, -4, 0), ".png");
    #write(Filename, "File to render: ", 1, Filename)
    #write(stdout, Filename, 1, Filename)
    #declare Frame = Frame + 1;
#end
