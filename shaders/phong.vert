#version 130

uniform vec4 global_ambient;

uniform vec4 light_ambient;
uniform vec4 light_diffuse;
uniform vec3 light_location;

uniform vec4 mat_ambient;
uniform vec4 mat_diffuse;

uniform mat4 modelview;
uniform mat4 normalmatrix;
uniform mat4 projection;

in vec3 position;
in vec3 normal;

out vec4 base_color;

float phong_weightCalc(
	in vec3 light_pos, // light position
	in vec3 frag_normal // geometry normal
) {
	// returns vec2( ambientMult, diffuseMult )
	float n_dot_pos = max( 0.3, dot(
		frag_normal, light_pos
	));
	return n_dot_pos;
}

void main() {
	
	gl_Position = projection * modelview * vec4(position, 1.0);
	vec3 transformed_normal = normalize(vec3(normalmatrix * vec4(normal, 0.0)));

	vec3 EC_Light_location = vec3(normalmatrix * vec4(light_location, 1.0));
	float diffuse_weight = phong_weightCalc(
		normalize(EC_Light_location),
		transformed_normal
	);
	
	base_color = clamp(
	(
		// global component
		(global_ambient * mat_ambient)
		// material's interaction with light's contribution
		// to the ambient lighting...
		+ (light_ambient * mat_ambient)
		// material's interaction with the direct light from
		// the light.
		+ (light_diffuse * mat_diffuse * diffuse_weight)
	), 0.0, 1.0);

	//base_color.r = (normal.x + 1) /2;
	//base_color.g = (normal.y + 1) /2;
	//base_color.b = (normal.z + 1) /2;
	base_color = mat_diffuse;
}
