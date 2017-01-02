[vertex]


layout(location=0) in highp vec4 vertex_attrib;


void main() {

	gl_Position = vertex_attrib;
	gl_Position.z=1.0;
}

[fragment]


uniform sampler2D source_ssao; //texunit:0
uniform sampler2D source_depth; //texunit:1


layout(location = 0) out float visibility;


//////////////////////////////////////////////////////////////////////////////////////////////
// Tunable Parameters:

/** Increase to make depth edges crisper. Decrease to reduce flicker. */
#define EDGE_SHARPNESS     (1.0)

/** Step in 2-pixel intervals since we already blurred against neighbors in the
    first AO pass.  This constant can be increased while R decreases to improve
    performance at the expense of some dithering artifacts.

    Morgan found that a scale of 3 left a 1-pixel checkerboard grid that was
    unobjectionable after shading was applied but eliminated most temporal incoherence
    from using small numbers of sample taps.
    */
#define SCALE               (3)

/** Filter radius in pixels. This will be multiplied by SCALE. */
#define R                   (4)


//////////////////////////////////////////////////////////////////////////////////////////////


// Gaussian coefficients
const float gaussian[R + 1] =
//    float[](0.356642, 0.239400, 0.072410, 0.009869);
//    float[](0.398943, 0.241971, 0.053991, 0.004432, 0.000134);  // stddev = 1.0
    float[](0.153170, 0.144893, 0.122649, 0.092902, 0.062970);  // stddev = 2.0
//      float[](0.111220, 0.107798, 0.098151, 0.083953, 0.067458, 0.050920, 0.036108); // stddev = 3.0

/** (1, 0) or (0, 1)*/
uniform ivec2       axis;

uniform float camera_z_far;
uniform float camera_z_near;

void main() {

	ivec2 ssC = ivec2(gl_FragCoord.xy);

	float depth = texelFetch(source_depth, ssC, 0).r;

	depth = depth * 2.0 - 1.0;
	depth = 2.0 * camera_z_near * camera_z_far / (camera_z_far + camera_z_near - depth * (camera_z_far - camera_z_near));

	float depth_divide = 1.0 / camera_z_far;

	depth*=depth_divide;

	//if (depth > camera_z_far*0.999) {
	//	discard;//skybox
	//}

	float sum = texelFetch(source_ssao, ssC, 0).r;

	// Base weight for depth falloff.  Increase this for more blurriness,
	// decrease it for better edge discrimination
	float BASE = gaussian[0];
	float totalWeight = BASE;
	sum *= totalWeight;


	for (int r = -R; r <= R; ++r) {
		// We already handled the zero case above.  This loop should be unrolled and the static branch optimized out,
		// so the IF statement has no runtime cost
		if (r != 0) {

			ivec2 ppos = ssC + axis * (r * SCALE);
			float value = texelFetch(source_ssao, ppos, 0).r;
			float temp_depth = texelFetch(source_depth, ssC, 0).r;

			temp_depth = temp_depth * 2.0 - 1.0;
			temp_depth = 2.0 * camera_z_near * camera_z_far / (camera_z_far + camera_z_near - temp_depth * (camera_z_far - camera_z_near));
			temp_depth *= depth_divide;

			// spatial domain: offset gaussian tap
			float weight = 0.3 + gaussian[abs(r)];

			// range domain (the "bilateral" weight). As depth difference increases, decrease weight.
			weight *= max(0.0, 1.0
				      - (EDGE_SHARPNESS * 2000.0) * abs(temp_depth - depth)
				      );

			sum += value * weight;
			totalWeight += weight;
		}
	}

	const float epsilon = 0.0001;
	visibility = sum / (totalWeight + epsilon);
}
